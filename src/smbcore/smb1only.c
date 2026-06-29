#include "types.h"
#include "vars.h"
#include "consts.h"


// SMB:8000
// Signature: [] -> []
void Reset(void) {
  ppuctrl(0x10);
  // ppu_waituntilvblank();   // wait until ppustatus() & 0x80 == 1
  // ppu_waituntilvblank();   // wait until ppustatus() & 0x80 == 1

  u8 initialize_upto = WarmBootValidation == 0xa5 ? 0xd6 : 0xfe;

  for (int i = 0; i < 6; i++) {
    if (DisplayDigits[i] > 9) {
      initialize_upto = 0xfe;
      break;
    }
  }

  InitializeMemory(initialize_upto);
  OperMode = OM_TITLESCREEN;
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
void NMI(void) {
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

  struct sprite sprites[64];

  // The NES wrote to OAM registers to initiate copying sprites
  // $2003 = 0
  // $4014 = 2
  transfer_sprite_data(&sprites[0], &Sprite_Data[0]);

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

  u8 const prev_mirror_ppu_ctrl = Mirror_PPU_CTRL_REG1;
  ppuctrl(Mirror_PPU_CTRL_REG1);
  if ((GamePauseStatus & 1) == 0) {
    OperModeExecutionTree();
  }
  ppustatus();

  // Enable NMI (our port ignores this)
  ppuctrl(prev_mirror_ppu_ctrl | 0x80);

  draw_graphics(&sprites[0]);
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


// SMB:83f6
// Signature: [] -> []
void PrintVictoryMessages(void) {
  bool inc_msg_counter = true;

  static const u8 addrctrl_world8_lookup[] = {
    ADDRCTRL_SMB1_YOURQUESTISOVER,
    ADDRCTRL_SMB1_WEPRESENTYOUANEWQUEST,
    ADDRCTRL_SMB1_PUSHBUTTONB,
    ADDRCTRL_SMB1_TOSELECTAWORLD,
  };

  if (SecondaryMsgCounter == 0) {
    if (PrimaryMsgCounter == 0) {
      VRAM_Buffer_AddrCtrl = (CurrentPlayer == 0) ? ADDRCTRL_SMB1_THANKYOUMARIO : ADDRCTRL_SMB1_THANKYOULUIGI;
    } else if (PrimaryMsgCounter < 9) {
      if (WorldNumber != 7) {
        if (PrimaryMsgCounter == 2) {
          VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB1_BUTOURPRINCESSISINANOTHERCASTLE;
        }

        if (PrimaryMsgCounter >= 4) {
          inc_msg_counter = false;
        }
      } else {
        if (PrimaryMsgCounter >= 3) {
            if (PrimaryMsgCounter == 3) {
              EventMusicQueue = MUSIC_EVENT_PRINCESS;
            }

            // Anything over 6 would overflow the address control lookup
            expect(PrimaryMsgCounter <= 6);

            VRAM_Buffer_AddrCtrl = addrctrl_world8_lookup[PrimaryMsgCounter - 3];
        }
      }
    }
  }

  if (inc_msg_counter) {
    ADD_UNSIGNED_16_8(PrimaryMsgCounter, SecondaryMsgCounter,
                      4);

    if (PrimaryMsgCounter <= 6) {
      return;
    }
  }

  WorldEndTimer = 6;

  expect(OperMode_Task == OMT_VICTORY_PRINTVICTORYMESSAGES);
  OperMode_Task = OMT_VICTORY_PLAYERENDWORLD;
}


// SMB:8808
// Signature: [A] -> []
void WriteGameText(const u8 param_1) {
  // param_1 is 0,1,2,3, 4,5,6

  // param_1=0: 0: Top status bar line

  // param_1=1: 2: World and Lives display

  // param_1=2: 5: One-player time-up message: "TIME UP"
  // param_1=2: 4: Two-player time up message: "MARIO TIME UP"

  // param_1=3: 7: One-player game over message: "GAME OVER"
  // param_1=3: 6: Two-player game over message: "MARIO GAME OVER"

  // param_1=4,5,6: 9 and 8: Warp zone message: "WELCOME TO WARP ZONE!"

  static u8 const p1_l[7] = {0,2,5,7,9,9,9};
  static u8 const p2_l[7] = {0,2,4,6,8,8,8};

  u8 offset;
  if (NumberOfPlayers == 0) {
    offset = GameTextOffsets[p1_l[param_1]];
  } else {
    offset = GameTextOffsets[p2_l[param_1]];
  }

  bool terminated = false;
  for (int i = 0; i < 256; i++) {
    const u8 val = GameText[offset];
    if (val == 0xff) {
      VRAM_Buffer1[i] = 0;
      terminated = true;
      break;
    }
    VRAM_Buffer1[i] = val;
    offset += 1;
  }
  if (!terminated) {
    VRAM_Buffer1[0] = 0;
  }

  if (param_1 >= 4) {
    // Wrote the "Welcome to warp zone!" message

    // Write the specific warp zone numbers
    for (int i = 0; i < 3; i++) {
      VRAM_Buffer1[0x1b + i*4] = WarpZoneNumbers[(param_1 - 4) * 4 + i];
    }
    VRAM_Buffer1_Offset = 0x2c;
    return;
  }

  if (param_1 == 1) {
    // Wrote the world and lives display screen

    const u8 lives_tile = NumberofLives + 1;

    if (lives_tile < 10) {
      // Draw the number of lives if under 10
      VRAM_Buffer1[8] = lives_tile;
    } else {
      // Draw crown tile, then the number of lives
      VRAM_Buffer1[7] = 0x9f;
      VRAM_Buffer1[8] = lives_tile - 10;
    }

    // Write the world and level numbers
    const u8 world_number_display = WorldNumber + 1;
    const u8 level_number_display = LevelNumber + 1;
    VRAM_Buffer1[19] = world_number_display;
    VRAM_Buffer1[21] = level_number_display;

    return;
  }

  if (NumberOfPlayers != 0) {
    bool set_name_to_luigi = (CurrentPlayer & 1) != 0;

    if ((param_1 == 2) && (OperMode != OM_GAMEOVER)) {
      // Time up message
      set_name_to_luigi = !set_name_to_luigi;
    }

    if (set_name_to_luigi) {
      for (int i = 0; i < 5; i++) {
        VRAM_Buffer1[i + 3] = LuigiName[i];
      }
    }
  }
}


// SMB:afc4
// Signature: [Y] -> []
void ScrollScreen(const u8 param_1) {
  ScrollAmount = param_1;
  ScrollThirtyTwo += param_1;
  ADD_UNSIGNED_16_8(ScreenLeft_PageLoc, ScreenLeft_X_Pos,
                    param_1);
  HorizontalScroll = ScreenLeft_X_Pos;
  Mirror_PPU_CTRL_REG1 &= 0xfe;
  Mirror_PPU_CTRL_REG1 |= ScreenLeft_PageLoc & 1;
  GetScreenPosition();
  ScrollIntervalTimer = 8;
  ChkPOffscr();
}


// SMB:e01b
// Signature: [A, X] -> []
void ChkToStunEnemies(const u8 enemy_id, const u8 param_2) {
  // Turn these enemies into koopas
  switch (enemy_id) {
  case A_GREEN_PARATROOPA_INPLACE:
  case A_RED_PARATROOPA:
  case A_PIRANHA_PLANT:
    Enemy_ID[param_2] = A_RED_KOOPA_GREENLIKE;
    break;

  case A_GREEN_PARATROOPA:
  case A_GREEN_PARATROOPA_HORIZONTAL:
    Enemy_ID[param_2] = A_GREEN_KOOPA;
    break;
  }

  // Inlined: SetStun

  Enemy_State[param_2] = (Enemy_State[param_2] & 0xf0) | 2;
  SetStun2(param_2);
}
