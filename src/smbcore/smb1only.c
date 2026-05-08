#include "types.h"
#include "vars.h"

enum DecodeAreaData_jumptable_item {
  DECODEAREADATA_VERTICALPIPE_1,
  DECODEAREADATA_AREASTYLEOBJECT,
  DECODEAREADATA_ROWOFBRICKS,
  DECODEAREADATA_ROWOFSOLIDBLOCKS,
  DECODEAREADATA_ROWOFCOINS,
  DECODEAREADATA_COLUMNOFBRICKS,
  DECODEAREADATA_COLUMNOFSOLIDBLOCKS,
  DECODEAREADATA_VERTICALPIPE_2,
  DECODEAREADATA_HOLE_EMPTY,
  DECODEAREADATA_PULLEYROPEOBJECT,
  DECODEAREADATA_BRIDGE_HIGH,
  DECODEAREADATA_BRIDGE_MIDDLE,
  DECODEAREADATA_BRIDGE_LOW,
  DECODEAREADATA_HOLE_WATER,
  DECODEAREADATA_QUESTIONBLOCKROW_HIGH,
  DECODEAREADATA_QUESTIONBLOCKROW_LOW,
  DECODEAREADATA_ENDLESSROPE,
  DECODEAREADATA_BALANCEPLATROPE,
  DECODEAREADATA_CASTLEOBJECT,
  DECODEAREADATA_STAIRCASEOBJECT,
  DECODEAREADATA_EXITPIPE,
  DECODEAREADATA_FLAGBALLS_RESIDUAL,
  DECODEAREADATA_QUESTIONBLOCK_1,
  DECODEAREADATA_QUESTIONBLOCK_2,
  DECODEAREADATA_QUESTIONBLOCK_3,
  DECODEAREADATA_HIDDEN1UPBLOCK,
  DECODEAREADATA_BRICKWITHITEM_1,
  DECODEAREADATA_BRICKWITHITEM_2,
  DECODEAREADATA_BRICKWITHITEM_3,
  DECODEAREADATA_BRICKWITHCOINS,
  DECODEAREADATA_BRICKWITHITEM_4,
  DECODEAREADATA_WATERPIPE,
  DECODEAREADATA_EMPTYBLOCK,
  DECODEAREADATA_JUMPSPRING,
  DECODEAREADATA_INTROPIPE,
  DECODEAREADATA_FLAGPOLEOBJECT,
  DECODEAREADATA_AXEOBJ,
  DECODEAREADATA_CHAINOBJ,
  DECODEAREADATA_CASTLEBRIDGEOBJ,
  DECODEAREADATA_SCROLLLOCKOBJECT_WARP,
  DECODEAREADATA_SCROLLLOCKOBJECT_1,
  DECODEAREADATA_SCROLLLOCKOBJECT_2,
  DECODEAREADATA_AREAFRENZY_1,
  DECODEAREADATA_AREAFRENZY_2,
  DECODEAREADATA_AREAFRENZY_3,
  DECODEAREADATA_NOOP,
  DECODEAREADATA_ALTERAREAATTRIBUTES,
};


// SMB:n/a
// Signature: [A, X, r00] -> []
void jumptable_DecodeAreaData(byte param_1, byte param_2, byte param_3) {
  switch (param_1) {
  case DECODEAREADATA_VERTICALPIPE_1:
  case DECODEAREADATA_VERTICALPIPE_2:
    VerticalPipe(param_2, param_3);
    return;

  case DECODEAREADATA_AREASTYLEOBJECT:
    AreaStyleObject(param_2);
    return;

  case DECODEAREADATA_ROWOFBRICKS:
    RowOfBricks(param_2);
    return;

  case DECODEAREADATA_ROWOFSOLIDBLOCKS:
    RowOfSolidBlocks(param_2);
    return;

  case DECODEAREADATA_ROWOFCOINS:
    RowOfCoins(param_2);
    return;

  case DECODEAREADATA_COLUMNOFBRICKS:
    ColumnOfBricks(param_2);
    return;

  case DECODEAREADATA_COLUMNOFSOLIDBLOCKS:
    ColumnOfSolidBlocks(param_2);
    return;

  case DECODEAREADATA_HOLE_EMPTY:
    Hole_Empty(param_2);
    return;

  case DECODEAREADATA_PULLEYROPEOBJECT:
    PulleyRopeObject(param_2);
    return;

  case DECODEAREADATA_BRIDGE_HIGH:
    Bridge_High(param_2);
    return;

  case DECODEAREADATA_BRIDGE_MIDDLE:
    Bridge_Middle(param_2);
    return;

  case DECODEAREADATA_BRIDGE_LOW:
    Bridge_Low(param_2);
    return;

  case DECODEAREADATA_HOLE_WATER:
    Hole_Water(param_2);
    return;

  case DECODEAREADATA_QUESTIONBLOCKROW_HIGH:
    QuestionBlockRow_High(param_2);
    return;

  case DECODEAREADATA_QUESTIONBLOCKROW_LOW:
    QuestionBlockRow_Low(param_2);
    return;

  case DECODEAREADATA_ENDLESSROPE:
    EndlessRope();
    return;

  case DECODEAREADATA_BALANCEPLATROPE:
    BalancePlatRope(param_2);
    return;

  case DECODEAREADATA_CASTLEOBJECT:
    CastleObject(param_2);
    return;

  case DECODEAREADATA_STAIRCASEOBJECT:
    StaircaseObject(param_2);
    return;

  case DECODEAREADATA_EXITPIPE:
    ExitPipe(param_2);
    return;

  case DECODEAREADATA_FLAGBALLS_RESIDUAL:
    FlagBalls_Residual(param_2);
    return;

  case DECODEAREADATA_QUESTIONBLOCK_1:
  case DECODEAREADATA_QUESTIONBLOCK_2:
  case DECODEAREADATA_QUESTIONBLOCK_3:
    QuestionBlock(param_2, param_3);
    return;

  case DECODEAREADATA_HIDDEN1UPBLOCK:
    Hidden1UpBlock(param_2, param_3);
    return;

  case DECODEAREADATA_BRICKWITHITEM_1:
  case DECODEAREADATA_BRICKWITHITEM_2:
  case DECODEAREADATA_BRICKWITHITEM_3:
  case DECODEAREADATA_BRICKWITHITEM_4:
    BrickWithItem(param_2, param_3);
    return;

  case DECODEAREADATA_BRICKWITHCOINS:
    BrickWithCoins(param_2, param_3);
    return;

  case DECODEAREADATA_WATERPIPE:
    WaterPipe(param_2);
    return;

  case DECODEAREADATA_EMPTYBLOCK:
    EmptyBlock(param_2);
    return;

  case DECODEAREADATA_JUMPSPRING:
    Jumpspring(param_2);
    return;

  case DECODEAREADATA_INTROPIPE:
    IntroPipe(param_2);
    return;

  case DECODEAREADATA_FLAGPOLEOBJECT:
    FlagpoleObject();
    return;

  case DECODEAREADATA_AXEOBJ:
    AxeObj(param_3);
    return;

  case DECODEAREADATA_CHAINOBJ:
    ChainObj(param_3);
    return;

  case DECODEAREADATA_CASTLEBRIDGEOBJ:
    CastleBridgeObj(param_2, param_3);
    return;

  case DECODEAREADATA_SCROLLLOCKOBJECT_WARP:
    ScrollLockObject_Warp();
    return;

  case DECODEAREADATA_SCROLLLOCKOBJECT_1:
  case DECODEAREADATA_SCROLLLOCKOBJECT_2:
    ScrollLockObject();
    return;

  case DECODEAREADATA_AREAFRENZY_1:
  case DECODEAREADATA_AREAFRENZY_2:
  case DECODEAREADATA_AREAFRENZY_3:
    AreaFrenzy(param_3);
    return;

  case DECODEAREADATA_NOOP:
    // No-op
    return;

  case DECODEAREADATA_ALTERAREAATTRIBUTES:
    AlterAreaAttributes(param_2);
    return;

  default:
    jmpengine_overflow(param_1);
  }
}


enum GameMode_jumptable_item {
  GAMEMODE_INITIALIZEAREA,
  GAMEMODE_SCREENROUTINES,
  GAMEMODE_SECONDARYGAMESETUP,
  GAMEMODE_GAMECOREROUTINE,
};


// SMB:n/a
// Signature: [A] -> []
void jumptable_GameMode(byte param_1) {
  switch (param_1) {
  case GAMEMODE_INITIALIZEAREA:
    InitializeArea();
    return;

  case GAMEMODE_SCREENROUTINES:
    ScreenRoutines();
    return;

  case GAMEMODE_SECONDARYGAMESETUP:
    SecondaryGameSetup();
    return;

  case GAMEMODE_GAMECOREROUTINE:
    GameCoreRoutine();
    return;

  default:
    jmpengine_overflow(param_1);
  }
}


enum BumpBlock_jumptable_item {
  BUMPBLOCK_MUSHFLOWERBLOCK_1,
  BUMPBLOCK_COINBLOCK_1,
  BUMPBLOCK_COINBLOCK_2,
  BUMPBLOCK_EXTRALIFEMUSHBLOCK_1,
  BUMPBLOCK_MUSHFLOWERBLOCK_2,
  BUMPBLOCK_VINEBLOCK,
  BUMPBLOCK_STARBLOCK,
  BUMPBLOCK_COINBLOCK_3,
  BUMPBLOCK_EXTRALIFEMUSHBLOCK_2,
};


// SMB:n/a
// Signature: [A, X] -> []
void jumptable_BumpBlock(byte param_1, byte param_2) {
  switch (param_1) {
  case BUMPBLOCK_MUSHFLOWERBLOCK_1:
  case BUMPBLOCK_MUSHFLOWERBLOCK_2:
    MushFlowerBlock(param_2);
    return;

  case BUMPBLOCK_COINBLOCK_1:
  case BUMPBLOCK_COINBLOCK_2:
  case BUMPBLOCK_COINBLOCK_3:
    CoinBlock(param_2);
    return;

  case BUMPBLOCK_EXTRALIFEMUSHBLOCK_1:
  case BUMPBLOCK_EXTRALIFEMUSHBLOCK_2:
    ExtraLifeMushBlock(param_2);
    return;

  case BUMPBLOCK_VINEBLOCK:
    VineBlock();
    return;

  case BUMPBLOCK_STARBLOCK:
    StarBlock(param_2);
    return;

  default:
    jmpengine_overflow(param_1);
  }
}


static void GameMenuRoutine_ResetTitle() {
  OperMode = 0;
  OperMode_Task = 0;
  Sprite0HitDetectFlag = 0;
  DisableScreenFlag = DisableScreenFlag + 1;
}

static void GameMenuRoutine_StartGame(bool button_a_pushed) {
  if (button_a_pushed) {
    GoContinue(ContinueWorld);
  }
  LoadAreaPointer();
  Hidden1UpFlag += 1;
  OffScr_Hidden1UpFlag += 1;
  FetchNewGameTimerFlag += 1;
  OperMode += 1;
  PrimaryHardMode = WorldSelectEnableFlag;
  OperMode_Task = 0;
  DemoTimer = 0;
  for (int i = 0; i < 12*2; i++) {
    PlayerScoreDisplay_Or_ScoreAndCoinDisplay[i] = 0;
  }
}

// SMB:8245
// Signature: [] -> []
void GameMenuRoutine(void) {
  byte buttons = SavedJoypadBits[0] | SavedJoypadBits[1];

  bool button_start_and_maybe_a_pushed_only = (buttons == BUTTON_START) || (buttons == (BUTTON_A | BUTTON_START));
  bool button_a_pushed = (buttons & BUTTON_A) != 0;
  bool button_select_pushed_only = buttons == BUTTON_SELECT;
  bool button_b_pushed_only = buttons == BUTTON_B;

  // if the demo is running...
  if (DemoTimer == 0) {
    // and Start or Select is pushed...
    if (button_start_and_maybe_a_pushed_only || button_select_pushed_only) {
      // then reset to the title
      GameMenuRoutine_ResetTitle();
      return;
    }

    // not really sure why this is done. seems pointless
    SelectTimer = buttons;

    if (DemoEngine()) {
      // when the demo is finished, then reset to the title
      GameMenuRoutine_ResetTitle();
      return;
    }

    GameCoreRoutine();
    if (GameEngineSubroutine == 6) {
      GameMenuRoutine_ResetTitle();
    }
    return;
  }

  // demo is not running

  if (button_start_and_maybe_a_pushed_only) {
    // Let'sa go!
    // (start the game)
    GameMenuRoutine_StartGame(button_a_pushed);
    return;
  }

  if (button_select_pushed_only) {
    DemoTimer = 0x18;
    if (SelectTimer == 0) {
      SelectTimer = 0x10;
      NumberOfPlayers ^= 1;
      DrawMushroomIcon();
    }
  }

  if (button_b_pushed_only && (WorldSelectEnableFlag != 0)) {
    DemoTimer = 0x18;
    if (SelectTimer == 0) {
      SelectTimer = 0x10;
      WorldSelectNumber = (WorldSelectNumber + 1) & 7;
      GoContinue(WorldSelectNumber);
      for (int i = 0; i < 6; i++) {
        VRAM_Page[i] = WSelectBufferTemplate[i];
      }
      VRAM_Page[4] = WorldNumber + 1;
    }
  }

  SavedJoypadBits[0] = 0;

  GameCoreRoutine();
  if (GameEngineSubroutine == 6) {
    GameMenuRoutine_ResetTitle();
  }
}


// SMB:830e
// Signature: [A] -> [X]
byte GoContinue(byte param_1) {
  WorldNumber = param_1;
  OffScr_WorldNumber = param_1;
  AreaNumber = 0;
  OffScr_AreaNumber = 0;
  return 0;
}


// SMB:8325
// Signature: [] -> []
void DrawMushroomIcon(void) {
  for (int i = 0; i < 8; i++) {
    VRAM_Page[i] = MushroomIconData[i];
  }
  if (NumberOfPlayers != 0) {
    VRAM_Buffer1[3] = 0x24;
    VRAM_Buffer1[5] = 0xce;
  }
}


// SMB:83f6
// Signature: [] -> []
void PrintVictoryMessages(void) {
  byte bVar1;
  byte bVar2;
  bool bVar3;

  if (SecondaryMsgCounter == 0) {
    bVar1 = PrimaryMsgCounter;
    if (PrimaryMsgCounter == 0) {
      goto ThankPlayer;
    }
    if (PrimaryMsgCounter < 9) {
      if (WorldNumber == 7) {
        if (PrimaryMsgCounter >= 3) {
          bVar1 = (PrimaryMsgCounter - 1) - (PrimaryMsgCounter < 3);
ThankPlayer:
          if (bVar1 == 0) {
            bVar2 = bVar1;
            if (CurrentPlayer != 0) {
              bVar2 = 1;
            }
          } else {
            bVar2 = bVar1 + 1;
            if (WorldNumber != 7) {
              bVar3 = bVar1 >= 4;
              if (bVar3) {
                goto SetEndTimer;
              }
              bVar2 = bVar1;
              if (bVar1 > 2) {
                goto IncMsgCounter;
              }
            }
          }
          if (bVar2 == 3) {
            EventMusicQueue = 4;
          }
          VRAM_Buffer_AddrCtrl = bVar2 + 0xc;
        }
      } else if (PrimaryMsgCounter > 1) {
        goto ThankPlayer;
      }
    }
  }
IncMsgCounter:
  PrimaryMsgCounter += SecondaryMsgCounter >= 0xfc;
  bVar3 = PrimaryMsgCounter > 6;
  SecondaryMsgCounter = SecondaryMsgCounter + 4;
SetEndTimer:
  if (bVar3) {
    WorldEndTimer = 6;
    OperMode_Task += 1;
  }
}


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


// SMB:8fcf
// Signature: [] -> []
void InitializeGame(void) {
  InitializeMemory(0x6f);
  for (int i = 0; i < 0x20; i++) {
    SoundMemory[i] = 0;
  }
  DemoTimer = 0x18;
  LoadAreaPointer();
  InitializeArea();
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
