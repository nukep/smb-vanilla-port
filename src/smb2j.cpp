#define SMB2J_MODE
#include "foundation.h"

extern "C" {
bool load_smb2j(struct SMB_state *state, size_t disk_offset);
void SMB2J_Reset();
void SMB2J_NMI();
}

struct FdsFile {
  const char *name;
  size_t file_offset;
  ushort size;
  ushort org;
  int type;
};

#define TYPE_PRGRAM 0
#define TYPE_CHRRAM 1

#define SMB2J_FDS_FILES_COUNT 6

// hard-code some offsets for now
// the offsets are relative to after the 16-byte FDS header
static FdsFile SMB2J_FDS_FILES[SMB2J_FDS_FILES_COUNT] = {
    {"SM2CHAR1", 0x013C, 0x2000, 0x0000, TYPE_CHRRAM},
    {"SM2CHAR2", 0x214D, 0x0040, 0x0760, TYPE_CHRRAM},
    {"SM2MAIN ", 0x219E, 0x8000, 0x6000, TYPE_PRGRAM},
    {"SM2DATA2", 0xA1AF, 0x0E2F, 0xC470, TYPE_PRGRAM},
    {"SM2DATA3", 0xAFEF, 0x0CCF, 0xC5D0, TYPE_PRGRAM},
    {"SM2DATA4", 0xBCCF, 0x0F4C, 0xC2B4, TYPE_PRGRAM},
};

bool smb2j_load_file(struct SMB_state *state, const char *name) {
  if (strncmp(name, "SM2SAVE ", 8) == 0) {
    // treat the save byte specially

    state->rammem[0xD29F] = smb2j_load_games_beaten(state);

    return true;
  }

  for (int i = 0; i < SMB2J_FDS_FILES_COUNT; i++) {
    const FdsFile &a = SMB2J_FDS_FILES[i];
    bool eq = strncmp(name, a.name, 8) == 0;
    if (eq) {
      // Found it!
      byte *copy_to;
      if (a.type == TYPE_CHRRAM) {
        // Copy the bytes over to CHRRAM
        copy_to = state->chrrom + a.org;
      } else if (a.type == TYPE_PRGRAM) {
        // Copy the bytes over to RAM
        copy_to = state->rammem + a.org;
      }
      if (!seek_rom(state, state->smb2j_disk_offset + a.file_offset)) { return false; }
      if (!read_rom_bytes(state, copy_to, a.size)) { return false; }

      if (a.type == TYPE_CHRRAM) {
        update_pattern_tables(state);
      }

      return true;
    }
  }
  return false;
}

bool load_smb2j(struct SMB_state *state, size_t disk_offset) {
  // In this case, the 16 bit header is this:
  static char fds_disk_verification[16] = {0x01, '*', 'N', 'I', 'N', 'T', 'E', 'N', 'D', 'O', '-', 'H', 'V', 'C', '*', 0x01};
  byte headerbuf[16];
  if (!seek_rom(state, disk_offset)) { return false; }
  if (!read_rom_bytes(state, headerbuf, 16)) { return false; }

  bool match = memcmp(headerbuf, fds_disk_verification, 16) == 0;
  if (!match) { return false; }
  state->which_game = GAME_SMB2J;
  state->smb2j_disk_offset = disk_offset;

  // Load these automatically
  smb2j_load_file(state, "SM2CHAR1");
  smb2j_load_file(state, "SM2MAIN ");
  smb2j_load_file(state, "SM2SAVE ");
  return true;
}

#include "generated/smb2j_romarrays.h"
#include "generated/vars.h"
#define AreaAddrOffsets RAMARRAY_CONST(0xC360, 0x28)

// read $4032
byte FDS_drive_status() { return 0; }

#include "generated/smb2j.h"

void ScrollScreen(byte);
struct_ayz LoadFiles();
void UpdateGamesBeaten();

#define GameTimerDisplay GameTimerDisplaySMB2J

#include "common.h"
#include "common_inc.h"
#include "generated/smb2j.c"

void IRQHandler();

static bool RUN_IRQ = false;

void trigger_scroll_irq_if_havent_yet() {
  if (RUN_IRQ) {
    IRQHandler();
    RUN_IRQ = false;
    if (IRQAckFlag != 0) {
      printf("IRQAckFlag is non-zero after the IRQ handler. This shouldn't happen!\n");
    }
  }
}

void disable_interrupt() {}
void enable_interrupt() {}

byte FDS_AcknowledgeIrq() {
  return 0x01;
}
void FDSBIOS_Delay132(byte _) {}
void FDS_IrqTimer_Ctrl(byte _) {}

// SM2MAIN:c0f4
// Signature: [] -> [A, Y, Z]
struct_ayz LoadFiles() {
  // The FDS version calls FDS BIOS subroutines to read the files from disk, but in the port, we're just gonna load from a buffer.
  // The BIOS call is responsible for a lot of lag frames on the original hardware! Fortunately we don't deal with those here.

  byte files = 0;
  bool success = false;

  switch (FileListNumber) {
  case 0: // Worlds 1-4: SM2CHAR1, SM2MAIN, SM2SAVE
    if (!smb2j_load_file(SMB_STATE, "SM2CHAR1")) { goto end; }
    if (!smb2j_load_file(SMB_STATE, "SM2MAIN ")) { goto end; }
    if (!smb2j_load_file(SMB_STATE, "SM2SAVE ")) { goto end; }
    success = true;
    files = 3;
    break;
  case 1: // Worlds 5-8: SM2DATA2
    if (!smb2j_load_file(SMB_STATE, "SM2DATA2")) { goto end; }
    success = true;
    files = 1;
    break;
  case 2: // Ending, w9: SM2CHAR2, SM2DATA3, SM2SAVE
    if (!smb2j_load_file(SMB_STATE, "SM2CHAR2")) { goto end; }
    if (!smb2j_load_file(SMB_STATE, "SM2DATA3")) { goto end; }
    if (!smb2j_load_file(SMB_STATE, "SM2SAVE ")) { goto end; }
    success = true;
    files = 3;

    // The FDS BIOS call overwrites some zero-page variables that are used during the ending.
    // This is a supremely gross hack.
    // Omitting this hack doesn't break the game, but it'd cause different conditionals to occur regarding Mario's sprites and fail RAM regression tests.

    // This isn't an issue for the other file loads, because when the worlds are loaded,
    // the memory is unused and is cleared on the next frame with InitializeMemory.

    // These are values when FileListNumber = 2, during a specific run of the game (idk if this changes):
    // TODO - set these to their corresponding variables when we're more sure what's going on
    RAM(0x08) = 0x0F;
    RAM(0x09) = 0x00;
    RAM(0x0A) = 0xA0;
    RAM(0x0B) = 0xD2;
    RAM(0x0C) = 0xFF;
    RAM(0x0D) = 0xFF;
    RAM(0x0E) = 0x03;
    RAM(0x0F) = 0x01;
    RAM(0xF9) = 0xF7;
    RAM(0xFA) = 0x27;
    break;
  case 3: // Worlds A-D: SM2DATA4
    smb2j_load_file(SMB_STATE, "SM2DATA4");
    success = true;
    files = 1;
    break;
  default:
    break;
  }

end:
  // this runs long enough for the scroll code of the irq to trigger
  trigger_scroll_irq_if_havent_yet();

  // A is the error code, should there be an error
  // Y is how many files were read
  // Z is set to 1 if the load is successful
  struct_ayz res;
  res.a = 0;
  res.y = files;
  res.z = success;
  return res;
}

void FDS_Ctrl(byte ctrl) {
  // $4025
}

// SM2MAIN:6000
// Signature: [] -> []
void SMB2J_Reset() {
  FDS_Ctrl(RAM(0xfa) & ~0x08);

  // On a hard reset, the World number is a value such as 0xFF
  // assuming a hard reset:
  WorldNumber = 0xFF;

  byte last_worldnumber = WorldNumber;

  byte initialize_upto = WarmBootValidation == 0xa5 ? 0xd6 : 0xfe;

  for (int i = 0; i < 6; i++) {
    if (DisplayDigits_Or_TopScoreDisplay[i] > 9) {
      initialize_upto = 0xfe;
      break;
    }
  }

  InitializeMemory(initialize_upto);
  OperMode = 0;
  apu_dmc_raw(0);
  WorldNumber = last_worldnumber;
  WarmBootValidation = 0xa5;
  PseudoRandomBitReg[0] = 0xa5;
  apu_snd_chn(0xf);
  ppumask(6);
  DiskIOTask = 0;
  MoveAllSpritesOffscreen();
  InitializeNameTables();
  DisableScreenFlag += 1;

  FDSBIOS_IRQFlag = 0xc0;
  enable_interrupt();

  Mirror_PPU_CTRL_REG1 |= 0x80;
  ppuctrl(Mirror_PPU_CTRL_REG1);

  // There was an infinite do-nothing loop here for the FDS.
  // At this point, the NMI would interrupt the loop each frame.
  // But as for the port, we just call the NMI ourselves.
}

// SM2MAIN:60a0
// Signature: [] -> []
void SMB2J_NMI() {
  Mirror_PPU_CTRL_REG1 = Mirror_PPU_CTRL_REG1 & ~0x81;
  ppuctrl(Mirror_PPU_CTRL_REG1);

  disable_interrupt();

  RUN_IRQ = false;

  if (IRQUpdateFlag != 0) {
    // Set IRQ timer to 0x1658 (until the scanline reaches the bottom of the status bar)
    // $4020 = 0x58
    // $4021 = 0x16
    // Enable IRQ timer
    // $4022 = 0x02
    IRQAckFlag += 1;
    RUN_IRQ = true;
  }

  if (DisableScreenFlag == 0) {
    Mirror_PPU_CTRL_REG2 |= 0x1e;
  } else {
    Mirror_PPU_CTRL_REG2 &= 0xe6;
  }
  ppumask(Mirror_PPU_CTRL_REG2 & 0xe7);

  ppustatus();
  ppuscroll(0);
  ppuscroll(0);

  // The NES wrote to OAM registers to initiate copying sprites
  // $2003 = 0
  // $4014 = 2
  transfer_sprite_data(&Sprite_Data);

  // Unlike SMB1, SMB2J's address table is 16-bit words, not segmented in hi and lo portions
  // Also unlike SMB1, index 5 (the title screen) is from the ROM.
  // VRAM_Buffer_AddrCtrl of 0, 6, 7 are in RAM ($301, $341, $341 respectively). All other ones are in ROM.
  UpdateScreen(&RAM(VRAM_AddrTable[VRAM_Buffer_AddrCtrl * 2 + 1] * 0x100 + VRAM_AddrTable[VRAM_Buffer_AddrCtrl * 2]));

  if (VRAM_Buffer_AddrCtrl == 6) {
    // in SMB ROM, VRAM_Buffer_Offset[1] = 0x40
    RAM(0x300 + VRAM_Buffer_Offset[1]) = 0;
    VRAM_Buffer1[VRAM_Buffer_Offset[1]] = 0;
  } else {
    // in SMB ROM, VRAM_Buffer_Offset[0] = 0x00
    RAM(0x300 + VRAM_Buffer_Offset[0]) = 0;
    VRAM_Buffer1[VRAM_Buffer_Offset[0]] = 0;
  }

  VRAM_Buffer_AddrCtrl = 0;
  ppumask(Mirror_PPU_CTRL_REG2);
  enable_interrupt();
  SoundEngine();
  apu_end_frame(SMB_STATE);
  ReadJoypads();
  PauseRoutine();
  UpdateTopScore();
  if ((GamePauseStatus & 1) == 0) {
    dectimers();
    FrameCounter += 1;
  }

  // Update PRNG (pseudo-random number generator)
  update_prng(&PseudoRandomBitReg);

  if ((GamePauseStatus & 1) == 0) {
    if (IRQUpdateFlag != 0) {
      MoveSpritesOffscreen();
      SpriteShuffler();
    }
    if (WorldNumber > 8) {
      TerminateGame();
    }
    OperModeExecutionTree();
  }

  // The FDS version loops here until IRQAckFlag is 0.
  trigger_scroll_irq_if_havent_yet();

  // The scroll is known
  announce_main_scroll(SMB_STATE->ppu.t.NN * 256 + SMB_STATE->ppu.t.XXXXX * 8 + SMB_STATE->ppu.x);
  draw_graphics(SMB_STATE);

  ppustatus();

  // Enable NMI (our port ignores this)
  Mirror_PPU_CTRL_REG1 |= 0x80;
  ppuctrl(Mirror_PPU_CTRL_REG1);
}

// SM2MAIN:61a2
// Signature: [] -> []
void IRQHandler() {
  disable_interrupt();
  byte status = FDS_AcknowledgeIrq();

  if ((status & 0x02) == 0) {
    if ((status & 0x01) != 0) {
      // Scrolling the screen right below the status bar
      // first 2 bits are 01: not transferring bytes, and an irq occurred

      Mirror_PPU_CTRL_REG1 = (Mirror_PPU_CTRL_REG1 & ~0x08) | NameTableSelect;
      ppuctrl(Mirror_PPU_CTRL_REG1);
      FDS_IrqTimer_Ctrl(0x00); // disable IRQ timer for the rest of the frame
      ppuscroll(HorizontalScroll);
      ppuscroll(VerticalScroll);
      IRQAckFlag = 0;
    }
  } else {
    // FDS is transferring bytes
    FDSBIOS_Delay132(status);
  }
  enable_interrupt();
}

// SM2MAIN:7b20
// Signature: [Y] -> []
void ScrollScreen(byte scroll_amount) {
  // The FDS version loops here until IRQAckFlag is 0.
  trigger_scroll_irq_if_havent_yet();

  int x_pos = ScreenLeft_X_Pos + scroll_amount;

  ScrollThirtyTwo = ScrollThirtyTwo + scroll_amount;
  HorizontalScroll = x_pos % 256;
  if (x_pos >= 256) {
    ScreenLeft_PageLoc += 1;
  }
  NameTableSelect = ScreenLeft_PageLoc % 2;
  ScreenLeft_X_Pos = HorizontalScroll;
  ScrollAmount = scroll_amount;
  GetScreenPosition();
  ScrollIntervalTimer = 8;
  ChkPOffscr();
}

// SM2DATA3::c759
// Signature: [] -> []
void UpdateGamesBeaten() {
  // The FDS version would use an FDS BIOS subroutine
  bool success = smb2j_save_games_beaten(SMB_STATE, GamesBeatenCount[0]);
  byte error_code = 0;

  if (!success) {
    DiskIOTask += 1;
    DiskErrorHandler(error_code);
    return;
  }

  // Revert "JSR SoundEngine" in the NMI back to the original address
  RAM(0x611e) = 0xd2;
  RAM(0x611d) = 0xa0;

  DiskIOTask = 0;
  OperMode_Task = 0;
  if ((HardWorldFlag == 0) && (CompletedWorlds == 0xff)) {
    CompletedWorlds = 0;
    NumberofLives = 0;
    FantasyW9MsgFlag = 0;
    AreaNumber = 0;
    LevelNumber = 0;
    OperMode_Task = 0;
    WorldNumber += 1;
    if (WorldNumber > 7) {
      WorldNumber = 8;
    }
    LoadAreaPointer();
    FetchNewGameTimerFlag = FetchNewGameTimerFlag + 1;
    OperMode = 1;
  } else {
    CompletedWorlds = 0;
    OperMode = 0;
    AttractModeSubs();
  }
}
