#include "types.h"
#include "vars.h"
#include "consts.h"


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
