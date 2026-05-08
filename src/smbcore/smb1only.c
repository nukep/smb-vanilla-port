#include "types.h"
#include "vars.h"

// SMB:8808
// Signature: [A] -> []
void WriteGameText(byte param_1) {
  // param_1 is 0,1,2,3, 4,5,6

  static byte p1_l[7] = {0,2,5,7,9,9,9};
  static byte p2_l[7] = {0,2,4,6,8,8,8};

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


// SMB:92af
// Signature: [] -> []
void DoNothing2(void) { return; }


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
  byte bVar1;
  byte bVar2;
  byte bVar3;
  struct_ycr07 sVar4;

  sVar4 = ChkLrgObjLength(param_1);
  bVar3 = sVar4.r07;
  if (sVar4.c != false) {
    MushroomLedgeHalfLen[param_1] = AreaObjectLength[param_1] >> 1;
    NoUnder(0x19, bVar3);
    return;
  }
  bVar2 = AreaObjectLength[param_1];
  if (bVar2 == 0) {
    NoUnder(0x1b, bVar3);
    return;
  }
  bVar1 = MushroomLedgeHalfLen[param_1];
  MetatileBuffer[bVar3] = 0x1a;
  if (bVar2 == bVar1) {
    MetatileBuffer[(byte)(bVar3 + 1)] = 0x4f;
    RenderUnderPart(0x50, bVar3 + 2, 0xf);
  }
}


// SMB:afc4
// Signature: [Y] -> []
void ScrollScreen(byte param_1) {
  ScrollThirtyTwo = param_1 + ScrollThirtyTwo;
  HorizontalScroll = param_1 + ScreenEdgeOrLeft_X_Pos[0];
  ScreenEdgeOrLeft_PageLoc[0] += CARRY1(param_1, ScreenEdgeOrLeft_X_Pos[0]);
  Mirror_PPU_CTRL_REG1 = (Mirror_PPU_CTRL_REG1 & 0xfe) | (ScreenEdgeOrLeft_PageLoc[0] & 1);
  ScreenEdgeOrLeft_X_Pos[0] = HorizontalScroll;
  ScrollAmount = param_1;
  GetScreenPosition();
  ScrollIntervalTimer = 8;
  ChkPOffscr();
}


// SMB:d2f2
// Signature: [X] -> []
void GameTimerFireworks(byte param_1) {
  if (GameTimerDisplay[2] == 1) {
    Enemy_State[param_1] = 5;
    FireworksCounter = 1;
  } else if (GameTimerDisplay[2] == 3) {
    Enemy_State[param_1] = 3;
    FireworksCounter = 3;
  } else if (GameTimerDisplay[2] == 6) {
    Enemy_State[param_1] = 0;
    FireworksCounter = 6;
  } else {
    Enemy_State[param_1] = 0;
    FireworksCounter = 0xff;
  }
  StarFlagTaskControl = StarFlagTaskControl + 1;
}


// SMB:e01b
// Signature: [A, X] -> []
void ChkToStunEnemies(byte param_1, byte param_2) {
  if (param_1 < 9) {
    SetStun(param_2);
  } else if (param_1 > 0x10) {
    SetStun(param_2);
  } else if ((param_1 >= 10) && (param_1 < 0xd)) {
    SetStun(param_2);
  } else {
    Enemy_ID[param_2] = param_1 & 1;
    SetStun(param_2);
  }
}


// SMB:e02f
// Signature: [X] -> []
void SetStun(byte param_1) {
  Enemy_State[param_1] = (Enemy_State[param_1] & 0xf0) | 2;
  SetStun2(param_1);
}


// SMB:e1ae
// Signature: [X] -> [A, X, Z, r02, r04, r06, r07]
struct_axzr02r04r06r07 ChkUnderEnemy_Ext(byte param_1) {
  return BlockBufferChk_Enemy_Ext(0, param_1, 0x15);
}


// SMB:e388
// Signature: [A, X, Y] -> [A, X, Z, r02, r04, r06, r07]
struct_axzr02r04r06r07 BlockBufferChk_Enemy_Ext(byte param_1, byte param_2, byte param_3) {
  struct_axzr02r04r06r07 sVar2;
  struct_azr02r04r06r07 sVar3;

  sVar3 = BlockBufferCollision(param_1, param_2 + 1, param_3);
  sVar2.a = sVar3.a;
  sVar2.x = ObjectOffset;
  sVar2.z = sVar3.a == 0;
  sVar2.r02 = sVar3.r02;
  sVar2.r04 = sVar3.r04;
  sVar2.r06 = sVar3.r06;
  sVar2.r07 = sVar3.r07;
  return sVar2;
}
