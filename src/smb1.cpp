#define SMB1_MODE
#include "smbcore.h"

extern "C" {
void SMB1_Reset();
void SMB1_NMI();
}

#include "smbcore/smb_romarrays.h"
#include "smbcore/vars.h"
#include "smbcore/smb1.h"
#include "smbcore/types.h"

void DrawTitleScreen();
bool TransposePlayers();

#define GameTimerDisplay GameTimerDisplaySMB1

#include "smbcommon.h"
#include "smbcore/common_sound.c"
#include "smbcore/area.h"
#include "smbcore/common.c"
#include "smbcore/smb1only.c"
#include "smbcore/area.c"

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

static const u8 * vram_buffer(u8 addr_ctrl, u16 *length) {
  // The VRAM buffers are tightly coupled with the code, so those are hard-coded in here.

  switch (addr_ctrl) {
  case ADDRCTRL_VRAM_BUFFER1:
    *length = 0x10000 - 0x301;
    return &VRAM_Buffer1[0];

  case ADDRCTRL_SMB1_VRAM_PAGE:
    // This addr_ctrl is only ever used for the title screen, and it's exactly this length
    // It's not different unless the ROM is modded
    *length = 0x13A;
    return &VRAM_Page[0];

  case ADDRCTRL_VRAM_BUFFER2:
  case ADDRCTRL_VRAM_BUFFER2_unused:
    *length = 0x10000 - 0x341;
    return &VRAM_Buffer2[0];

  default:
    {
      // Get the other ones from ROM

      const u8 hi = VRAM_AddrTable_High[addr_ctrl];
      const u8 lo = VRAM_AddrTable_Low[addr_ctrl];
      const u16 addr = (hi << 8) | lo;

      // TODO - get actual length of the arrays
      *length = 0x10000 - addr;

      return rom_ptr(addr);
    }
  }
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
  transfer_sprite_data(&Sprite_Data[0]);

  u16 vram_length = 0;
  const u8 *buf = vram_buffer(VRAM_Buffer_AddrCtrl, &vram_length);
  update_screen(buf, vram_length);
  
  if (VRAM_Buffer_AddrCtrl != ADDRCTRL_VRAM_BUFFER2) {
    VRAM_Buffer1_Offset = 0;
    VRAM_Buffer1[0] = 0;
  } else {
    VRAM_Buffer2_Offset = 0;
    VRAM_Buffer2[0] = 0;
  }

  VRAM_Buffer_AddrCtrl = ADDRCTRL_VRAM_BUFFER1;
  ppumask(Mirror_PPU_CTRL_REG2);
  SoundEngine();
  apu_end_frame();
  ReadJoypads();
  PauseRoutine();
  UpdateTopScore();
  if ((GamePauseStatus & 1) == 0) {
    dectimers();
    FrameCounter += 1;
  }

  // Update PRNG (pseudo-random number generator)
  update_prng(&PseudoRandomBitReg[0]);

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

  byte const prev_mirror_ppu_ctrl = Mirror_PPU_CTRL_REG1;
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
      VRAM_SMB1_TitleScreen[i] = CHRROM(0x1EC0 + i);
    }
    VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB1_VRAM_PAGE;
    ScreenRoutineTask = ScreenRoutineTask + 1;
  } else {
    OperMode_Task = OperMode_Task + 1;
  }
}

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
