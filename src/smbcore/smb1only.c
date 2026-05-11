#include "types.h"
#include "vars.h"

// SMB:8808
// Signature: [A] -> []
void WriteGameText(byte param_1) {
  // param_1 is 0,1,2,3, 4,5,6

  static byte const p1_l[7] = {0,2,5,7,9,9,9};
  static byte const p2_l[7] = {0,2,4,6,8,8,8};

  byte offset;
  if (NumberOfPlayers == 0) {
    offset = GameTextOffsets[p1_l[param_1]];
  } else {
    offset = GameTextOffsets[p2_l[param_1]];
  }

  bool terminated = false;
  for (int i = 0; i < 256; i++) {
    if (GameText[offset] == 0xff) {
      VRAM_Buffer1[i] = 0;
      terminated = true;
      break;
    }
    VRAM_Buffer1[i] = GameText[offset];
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

    // Write number of lives (and crown if over 9)
    VRAM_Buffer1[8] = NumberofLives + 1;
    if (VRAM_Buffer1[8] >= 10) {
      VRAM_Buffer1[8] = NumberofLives - 9;
      VRAM_Buffer1[7] = 0x9f;
    }

    // Write the world and level numbers
    VRAM_Buffer1[19] = WorldNumber + 1;
    VRAM_Buffer1[21] = LevelNumber + 1;
    return;
  }

  if (NumberOfPlayers != 0) {
    byte bVar1;
    if ((param_1 == 2) && (OperMode != 3)) {
      bVar1 = CurrentPlayer ^ 1;
    } else {
      bVar1 = CurrentPlayer;
    }
    if ((bVar1 & 1) != 0) {
      for (int i = 0; i < 5; i++) {
        VRAM_Buffer1[i + 3] = LuigiName[i];
      }
    }
  }
}


// SMB:96f2
// Signature: [] -> []
void ScrollLockObject_Warp(void) {
  if (WorldNumber == 0) {
    WarpZoneControl = 4;
  } else if (AreaType != 1) {
    WarpZoneControl = 5;
  } else {
    WarpZoneControl = 6;
  }
  WriteGameText(WarpZoneControl);
  KillEnemies(0xd);
  ScrollLockObject();
}


// SMB:9778
// Signature: [X] -> []
void MushroomLedge(byte param_1) {
  struct_ycr07 sVar4 = ChkLrgObjLength(param_1);
  byte bVar3 = sVar4.r07;
  if (sVar4.c) {
    MushroomLedgeHalfLen[param_1] = AreaObjectLength[param_1] >> 1;
    NoUnder(0x19, bVar3);
    return;
  }
  byte bVar2 = AreaObjectLength[param_1];
  if (bVar2 == 0) {
    NoUnder(0x1b, bVar3);
    return;
  }
  byte bVar1 = MushroomLedgeHalfLen[param_1];
  MetatileBuffer[bVar3] = 0x1a;
  if (bVar2 == bVar1) {
    MetatileBuffer[(byte)(bVar3 + 1)] = 0x4f;
    RenderUnderPart(0x50, bVar3 + 2, 0xf);
  }
}


// SMB:afc4
// Signature: [Y] -> []
void ScrollScreen(byte param_1) {
  ScrollAmount = param_1;
  ScrollThirtyTwo += param_1;
  ADD_UNSIGNED_16_8(ScreenEdgeOrLeft_PageLoc[0], ScreenEdgeOrLeft_X_Pos[0],
                    param_1);
  HorizontalScroll = ScreenEdgeOrLeft_X_Pos[0];
  Mirror_PPU_CTRL_REG1 &= 0xfe;
  Mirror_PPU_CTRL_REG1 |= ScreenEdgeOrLeft_PageLoc[0] & 1;
  GetScreenPosition();
  ScrollIntervalTimer = 8;
  ChkPOffscr();
}


// SMB:e01b
// Signature: [A, X] -> []
void ChkToStunEnemies(byte param_1, byte param_2) {
  // Turn these enemies into koopas
  if (param_1 == 9)  { Enemy_ID[param_2] = 1; }
  if (param_1 == 13) { Enemy_ID[param_2] = 1; }
  if (param_1 == 14) { Enemy_ID[param_2] = 0; }
  if (param_1 == 15) { Enemy_ID[param_2] = 1; }
  if (param_1 == 16) { Enemy_ID[param_2] = 0; }

  // Inlined: SetStun

  Enemy_State[param_2] = (Enemy_State[param_2] & 0xf0) | 2;
  SetStun2(param_2);
}
