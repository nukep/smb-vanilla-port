#define SMB1_MODE
#include "foundation.h"

extern "C" {
bool load_smb1(struct SMB_state *state, size_t prg_offset, size_t chr_offset);
void SMB1_Reset();
void SMB1_NMI();
}

bool load_smb1(struct SMB_state *state, size_t prg_offset, size_t chr_offset) {
  if (!seek_rom(state, prg_offset)) { return false; }
  if (!read_rom_bytes(state, state->rammem + 0x8000, 0x8000)) { return false; }
  if (!seek_rom(state, chr_offset)) { return false; }
  if (!read_rom_bytes(state, state->chrrom, 0x2000)) { return false; }
  state->which_game = GAME_SMB1;
  update_pattern_tables(state);
  return true;
}

#include "generated/smb_romarrays.h"
#include "generated/vars.h"
#include "generated/smb1.h"

void DrawTitleScreen();
bool TransposePlayers();

#define GameTimerDisplay GameTimerDisplaySMB1

#include "common.h"
#include "common_inc.h"
#include "generated/smb1.c"

// SMB:8000
// Signature: [] -> []
void SMB1_Reset() {
  ppuctrl(0x10);
  // ppu_waituntilvblank();   // wait until ppustatus() & 0x80 == 1
  // ppu_waituntilvblank();   // wait until ppustatus() & 0x80 == 1

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
  WarmBootValidation = 0xa5;
  PseudoRandomBitReg[0] = 0xa5;
  apu_snd_chn(0xf);
  ppumask(6);
  MoveAllSpritesOffscreen();
  InitializeNameTables();
  DisableScreenFlag += 1;

  Mirror_PPU_CTRL_REG1 |= 0x80;
  ppuctrl(Mirror_PPU_CTRL_REG1);

  // There was an infinite do-nothing loop here for the NES.
  // At this point, the NMI would interrupt the loop each frame.
  // But as for the port, we just call the NMI ourselves.
}

// SMB:8082
// Signature: [] -> []
void SMB1_NMI() {
  Mirror_PPU_CTRL_REG1 = Mirror_PPU_CTRL_REG1 & ~0x80;
  ppuctrl(Mirror_PPU_CTRL_REG1 & ~0x81);

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

  // VRAM_Buffer_AddrCtrl of 0, 5, 6, 7 are in RAM ($301, $300, $341, $341 respectively). All other ones are in ROM.
  UpdateScreen(&RAM(VRAM_AddrTable_High[VRAM_Buffer_AddrCtrl] * 0x100 + VRAM_AddrTable_Low[VRAM_Buffer_AddrCtrl]));

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

  if (Sprite0HitDetectFlag != 0) {
    // In the NES version, the game waits here until a Sprite 0 hit (the bottom of the status bar).
    if ((GamePauseStatus & 1) == 0) {
      MoveSpritesOffscreen();
      SpriteShuffler();
    }
    // In the NES version, the game waits here until Sprite 0 is no longer being hit.
    // In the NES version, the game wastes 101 CPU cycles here to get the PPU off the bottom of the status bar.
  }
  ppuscroll(HorizontalScroll);
  ppuscroll(VerticalScroll);

  byte prev_mirror_ppu_ctrl = Mirror_PPU_CTRL_REG1;
  ppuctrl(Mirror_PPU_CTRL_REG1);
  if ((GamePauseStatus & 1) == 0) {
    OperModeExecutionTree();
  }
  ppustatus();

  // Enable NMI (our port ignores this)
  ppuctrl(prev_mirror_ppu_ctrl | 0x80);

  // The scroll is known
  announce_main_scroll(SMB_STATE->ppu.t.NN * 256 + SMB_STATE->ppu.t.XXXXX * 8 + SMB_STATE->ppu.x);
  draw_graphics(SMB_STATE);
}

// SMB:86ff
// Signature: [] -> []
void DrawTitleScreen() {
  if (OperMode == 0) {
    // The drawing data for the title screen is stored in CHR ROM!
    for (int i = 0; i < 0x13A; i++) {
      RAM(0x300 + i) = CHRROM(0x1EC0 + i);
    }
    VRAM_Buffer_AddrCtrl = 5;
    ScreenRoutineTask = ScreenRoutineTask + 1;
  } else {
    OperMode_Task = OperMode_Task + 1;
  }
}

#define SWAP(a, b) \
  do {             \
    byte tmp = a;  \
    a = b;         \
    b = tmp;       \
  } while (0)

// Switch between Mario and Luigi.
// Save and restore their states.
//
// SMB:9282
// Signature: [] -> [C]
bool TransposePlayers() {
  // If there are two players, and the other one isn't out of lives
  if ((NumberOfPlayers != 0) && (OffScr_NumberofLives < 0x80)) {
    CurrentPlayer ^= 1;
    // We unrolled a loop here
    SWAP(NumberofLives, OffScr_NumberofLives);
    SWAP(HalfwayPage, OffScr_HalfwayPage);
    SWAP(LevelNumber, OffScr_LevelNumber);
    SWAP(Hidden1UpFlag, OffScr_Hidden1UpFlag);
    SWAP(CoinTally, OffScr_CoinTally);
    SWAP(WorldNumber, OffScr_WorldNumber);
    SWAP(AreaNumber, OffScr_AreaNumber);

    return false;
  } else {
    return true;
  }
}
