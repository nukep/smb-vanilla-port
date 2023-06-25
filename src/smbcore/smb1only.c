#include "types.h"
#include "vars.h"

// SMB:n/a
// Signature: [A, r00] -> []
void jumptable_OperModeExecutionTree(byte param_1, byte param_2) {
  if (param_1 == 0) {
    TitleScreenMode();
    return;
  }
  if (param_1 == 1) {
    GameMode();
    return;
  }
  if (param_1 == 2) {
    VictoryMode(param_2);
    return;
  }
  if (param_1 == 3) {
    GameOverMode();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// SMB:n/a
// Signature: [A] -> []
void jumptable_TitleScreenMode(byte param_1) {
  if (param_1 == 0) {
    InitializeGame();
    return;
  }
  if (param_1 == 1) {
    ScreenRoutines();
    return;
  }
  if (param_1 == 2) {
    PrimaryGameSetup();
    return;
  }
  if (param_1 == 3) {
    GameMenuRoutine();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// SMB:n/a
// Signature: [A, r00] -> []
void jumptable_VictoryModeSubroutines(byte param_1, byte param_2) {
  if (param_1 == 0) {
    BridgeCollapse(param_2);
    return;
  }
  if (param_1 == 1) {
    SetupVictoryMode();
    return;
  }
  if (param_1 == 2) {
    PlayerVictoryWalk();
    return;
  }
  if (param_1 == 3) {
    PrintVictoryMessages();
    return;
  }
  if (param_1 == 4) {
    PlayerEndWorld();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// SMB:n/a
// Signature: [A] -> []
void jumptable_ScreenRoutines(byte param_1) {
  if (param_1 == 0) {
    InitScreen();
    return;
  }
  if (param_1 == 1) {
    SetupIntermediate();
    return;
  }
  if (param_1 == 2) {
    WriteTopStatusLine();
    return;
  }
  if (param_1 == 3) {
    WriteBottomStatusLine();
    return;
  }
  if (param_1 == 4) {
    DisplayTimeUp();
    return;
  }
  if (param_1 == 5) {
    ResetSpritesAndScreenTimer();
    return;
  }
  if (param_1 == 6) {
    DisplayIntermediate();
    return;
  }
  if (param_1 == 7) {
    ResetSpritesAndScreenTimer();
    return;
  }
  if (param_1 == 8) {
    AreaParserTaskControl();
    return;
  }
  if (param_1 == 9) {
    GetAreaPalette();
    return;
  }
  if (param_1 == 10) {
    GetBackgroundColor();
    return;
  }
  if (param_1 == 0xb) {
    GetAlternatePalette1();
    return;
  }
  if (param_1 == 0xc) {
    DrawTitleScreen();
    return;
  }
  if (param_1 == 0xd) {
    ClearBuffersDrawIcon();
    return;
  }
  if (param_1 == 0xe) {
    WriteTopScore();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// Common: jumptable_GameOverMode
// Common: jumptable_AreaParserTasks


// SMB:n/a
// Signature: [A, X, r00] -> []
void jumptable_DecodeAreaData(byte param_1, byte param_2, byte param_3) {
  if (param_1 == 0) {
    VerticalPipe(param_2, param_3);
    return;
  }
  if (param_1 == 1) {
    AreaStyleObject(param_2);
    return;
  }
  if (param_1 == 2) {
    RowOfBricks(param_2);
    return;
  }
  if (param_1 == 3) {
    RowOfSolidBlocks(param_2);
    return;
  }
  if (param_1 == 4) {
    RowOfCoins(param_2);
    return;
  }
  if (param_1 == 5) {
    ColumnOfBricks(param_2);
    return;
  }
  if (param_1 == 6) {
    ColumnOfSolidBlocks(param_2);
    return;
  }
  if (param_1 == 7) {
    VerticalPipe(param_2, param_3);
    return;
  }
  if (param_1 == 8) {
    Hole_Empty(param_2);
    return;
  }
  if (param_1 == 9) {
    PulleyRopeObject(param_2);
    return;
  }
  if (param_1 == 10) {
    Bridge_High(param_2);
    return;
  }
  if (param_1 == 0xb) {
    Bridge_Middle(param_2);
    return;
  }
  if (param_1 == 0xc) {
    Bridge_Low(param_2);
    return;
  }
  if (param_1 == 0xd) {
    Hole_Water(param_2);
    return;
  }
  if (param_1 == 0xe) {
    QuestionBlockRow_High(param_2);
    return;
  }
  if (param_1 == 0xf) {
    QuestionBlockRow_Low(param_2);
    return;
  }
  if (param_1 == 0x10) {
    EndlessRope();
    return;
  }
  if (param_1 == 0x11) {
    BalancePlatRope(param_2);
    return;
  }
  if (param_1 == 0x12) {
    CastleObject(param_2);
    return;
  }
  if (param_1 == 0x13) {
    StaircaseObject(param_2);
    return;
  }
  if (param_1 == 0x14) {
    ExitPipe(param_2);
    return;
  }
  if (param_1 == 0x15) {
    FlagBalls_Residual(param_2);
    return;
  }
  if (param_1 == 0x16) {
    QuestionBlock(param_2, param_3);
    return;
  }
  if (param_1 == 0x17) {
    QuestionBlock(param_2, param_3);
    return;
  }
  if (param_1 == 0x18) {
    QuestionBlock(param_2, param_3);
    return;
  }
  if (param_1 == 0x19) {
    Hidden1UpBlock(param_2, param_3);
    return;
  }
  if (param_1 == 0x1a) {
    BrickWithItem(param_2, param_3);
    return;
  }
  if (param_1 == 0x1b) {
    BrickWithItem(param_2, param_3);
    return;
  }
  if (param_1 == 0x1c) {
    BrickWithItem(param_2, param_3);
    return;
  }
  if (param_1 == 0x1d) {
    BrickWithCoins(param_2, param_3);
    return;
  }
  if (param_1 == 0x1e) {
    BrickWithItem(param_2, param_3);
    return;
  }
  if (param_1 == 0x1f) {
    WaterPipe(param_2);
    return;
  }
  if (param_1 == 0x20) {
    EmptyBlock(param_2);
    return;
  }
  if (param_1 == 0x21) {
    Jumpspring(param_2);
    return;
  }
  if (param_1 == 0x22) {
    IntroPipe(param_2);
    return;
  }
  if (param_1 == 0x23) {
    FlagpoleObject();
    return;
  }
  if (param_1 == 0x24) {
    AxeObj(param_3);
    return;
  }
  if (param_1 == 0x25) {
    ChainObj(param_3);
    return;
  }
  if (param_1 == 0x26) {
    CastleBridgeObj(param_2, param_3);
    return;
  }
  if (param_1 == 0x27) {
    ScrollLockObject_Warp();
    return;
  }
  if (param_1 == 0x28) {
    ScrollLockObject();
    return;
  }
  if (param_1 == 0x29) {
    ScrollLockObject();
    return;
  }
  if (param_1 == 0x2a) {
    AreaFrenzy(param_3);
    return;
  }
  if (param_1 == 0x2b) {
    AreaFrenzy(param_3);
    return;
  }
  if (param_1 == 0x2c) {
    AreaFrenzy(param_3);
    return;
  }
  if (param_1 == 0x2d) {
    LoopCmdE();
    return;
  }
  if (param_1 == 0x2e) {
    AlterAreaAttributes(param_2);
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// SMB:n/a
// Signature: [A, X] -> []
void jumptable_AreaStyleObject(byte param_1, byte param_2) {
  if (param_1 == 0) {
    TreeLedge(param_2);
    return;
  }
  if (param_1 == 1) {
    MushroomLedge(param_2);
    return;
  }
  if (param_1 == 2) {
    BulletBillCannon(param_2);
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// SMB:n/a
// Signature: [A] -> []
void jumptable_GameMode(byte param_1) {
  if (param_1 == 0) {
    InitializeArea();
    return;
  }
  if (param_1 == 1) {
    ScreenRoutines();
    return;
  }
  if (param_1 == 2) {
    SecondaryGameSetup();
    return;
  }
  if (param_1 == 3) {
    GameCoreRoutine();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// Common: jumptable_GameRoutines
// Common: jumptable_PlayerMovementSubs


// SMB:n/a
// Signature: [A, X] -> []
void jumptable_BumpBlock(byte param_1, byte param_2) {
  if (param_1 == 0) {
    MushFlowerBlock(param_2);
    return;
  }
  if (param_1 == 1) {
    CoinBlock(param_2, false);
    return;
  }
  if (param_1 == 2) {
    CoinBlock(param_2, false);
    return;
  }
  if (param_1 == 3) {
    ExtraLifeMushBlock(param_2);
    return;
  }
  if (param_1 == 4) {
    MushFlowerBlock(param_2);
    return;
  }
  if (param_1 == 5) {
    VineBlock();
    return;
  }
  if (param_1 == 6) {
    StarBlock(param_2);
    return;
  }
  if (param_1 == 7) {
    CoinBlock(param_2, false);
    return;
  }
  if (param_1 == 8) {
    ExtraLifeMushBlock(param_2);
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// Common: jumptable_CheckpointEnemyID
// Common: jumptable_InitEnemyFrenzy
// Common: jumptable_RunEnemyObjectsCore
// Common: jumptable_EnemyMovementSubs
// Common: jumptable_LargePlatformSubroutines
// Common: jumptable_RunStarFlagObj
// Common: PauseRoutine
// Common: SpriteShuffler
// Common: OperModeExecutionTree
// Common: MoveAllSpritesOffscreen
// Common: MoveSpritesOffscreen


// SMB:8231
// Signature: [] -> []
void TitleScreenMode(void) {
  jumptable_TitleScreenMode(OperMode_Task);
  return;
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
      WorldSelectNumber = WorldSelectNumber + 1 & 7;
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
  return;
}


// SMB:836b
// Signature: [] -> [C]
bool DemoEngine(void) {
  byte bVar1;

  if (DemoActionTimer == 0) {
    bVar1 = DemoAction + 1;
    DemoAction += 1;
    DemoActionTimer = DemoActionData[bVar1 + 0x14];
    if (DemoActionTimer == 0) {
      return true;
    }
  }
  DemoActionTimer = DemoActionTimer - 1;
  SavedJoypadBits[0] = DemoActionData[DemoAction - 1];
  return false;
}


// Common: VictoryMode
// Common: VictoryModeSubroutines
// Common: SetupVictoryMode
// Common: PlayerVictoryWalk


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
  return;
}


// Common: PlayerEndWorld
// Common: FloateyNumbersRoutine
// Common: ScreenRoutines
// Common: InitScreen
// Common: SetupIntermediate
// Common: GetAreaPalette
// Common: GetBackgroundColor
// Common: GetPlayerColors
// Common: GetAlternatePalette1
// Common: WriteTopStatusLine
// Common: WriteBottomStatusLine
// Common: DisplayTimeUp
// Common: DisplayIntermediate
// Common: AreaParserTaskControl


// SMB:8732
// Signature: [] -> []
void ClearBuffersDrawIcon(void) {
  if (OperMode == 0) {
    for (int i = 0; i < 256; i++) {
      VRAM_Page[i] = 0;
      SprObject_X_MoveForce[i] = 0;
    }
    DrawMushroomIcon();
    ScreenRoutineTask = ScreenRoutineTask + 1;
    return;
  }
  OperMode_Task = OperMode_Task + 1;
  return;
}


// Common: WriteTopScore


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
  return;
}


// Common: ResetSpritesAndScreenTimer
// Common: ResetScreenTimer
// Common: RenderAreaGraphics
// Common: RenderAttributeTables
// Common: ColorRotation
// Common: RemoveCoin_Axe
// Common: ReplaceBlockMetatile
// Common: DestroyBlockMetatile
// Common: WriteBlockMetatile
// Common: MoveVOffset
// Common: PutBlockMetatile
// Common: RemBridge
// Common: InitializeNameTables
// Common: WritePPUReg1
// Common: PrintStatusBarNumbers
// Common: OutputNumbers
// Common: DigitsMathRoutine
// Common: UpdateTopScore
// Common: TopScoreCheck


// SMB:8fcf
// Signature: [] -> []
void InitializeGame(void) {
  byte bVar1;
  byte bVar2;

  InitializeMemory(0x6f);
  for (int i = 0; i < 0x20; i++) {
    SoundMemory[i] = 0;
  }
  DemoTimer = 0x18;
  LoadAreaPointer();
  InitializeArea();
  return;
}


// Common: InitializeArea


// SMB:9061
// Signature: [] -> []
void PrimaryGameSetup(void) {
  FetchNewGameTimerFlag = 1;
  PlayerSize = 1;
  NumberofLives = 2;
  OffScr_NumberofLives = 2;
  SecondaryGameSetup();
  return;
}


// Common: SecondaryGameSetup
// Common: GetAreaMusic
// Common: Entrance_GameTimerSetup
// Common: PlayerLoseLife
// Common: GameOverMode
// Common: SetupGameOver
// Common: RunGameOver
// Common: TerminateGame
// Common: ContinueGame
// Common: DoNothing


// SMB:92af
// Signature: [] -> []
void DoNothing2(void) { return; }


// Common: AreaParserTaskHandler
// Common: AreaParserTasks
// Common: IncrementColumnPos
// Common: AreaParserCore
// Common: ProcessAreaData
// Common: IncAreaObjOffset
// Common: DecodeAreaData
// Common: LoopCmdE
// Common: AlterAreaAttributes


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


// Common: ScrollLockObject
// Common: KillEnemies
// Common: AreaFrenzy
// Common: AreaStyleObject
// Common: TreeLedge


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
    return;
  }
  return;
}


// Common: NoUnder
// Common: PulleyRopeObject
// Common: CastleObject
// Common: WaterPipe
// Common: IntroPipe
// Common: ExitPipe
// Common: RenderSidewaysPipe


// SMB:98e5
// Signature: [X, r00] -> []
void VerticalPipe(byte param_1, byte param_2) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  struct_yr06r07 sVar5;
  struct_xc sVar6;
  byte bStack0000;

  sVar5 = GetPipeHeight(param_1);
  bVar2 = sVar5.r07;
  bVar1 = sVar5.r06;
  bStack0000 = sVar5.y;
  if (param_2 != 0) {
    bStack0000 += 4;
  }
  if (((AreaNumber | WorldNumber) != 0) && (AreaObjectLength[param_1] != 0)) {
    sVar6 = FindEmptyEnemySlot();
    bVar4 = sVar6.x;
    if (!sVar6.c) {
      bVar3 = GetAreaObjXPosition();
      Enemy_X_Position[bVar4] = bVar3 + 8;
      Enemy_PageLoc[bVar4] = CurrentPageLoc + (bVar3 >= 0xf8);
      Enemy_Y_HighPos[bVar4] = 1;
      Enemy_Flag[bVar4] = 1;
      bVar3 = GetAreaObjYPosition(bVar2);
      Enemy_Y_Position[bVar4] = bVar3;
      Enemy_ID[bVar4] = 0xd;
      InitPiranhaPlant(bVar4);
    }
  }
  MetatileBuffer[bVar2] = VerticalPipeData[bStack0000];
  RenderUnderPart(VerticalPipeData[bStack0000 + 2], bVar2 + 1, bVar1 - 1);
  return;
}


// Common: GetPipeHeight
// Common: FindEmptyEnemySlot
// Common: Hole_Water
// Common: QuestionBlockRow_High
// Common: QuestionBlockRow_Low
// Common: Bridge_High
// Common: Bridge_Middle
// Common: Bridge_Low
// Common: FlagBalls_Residual
// Common: FlagpoleObject
// Common: EndlessRope
// Common: BalancePlatRope
// Common: RowOfCoins
// Common: CastleBridgeObj
// Common: AxeObj
// Common: ChainObj
// Common: EmptyBlock
// Common: RowOfBricks
// Common: RowOfSolidBlocks
// Common: ColumnOfBricks
// Common: ColumnOfSolidBlocks
// Common: BulletBillCannon
// Common: StaircaseObject
// Common: Jumpspring
// Common: Hidden1UpBlock
// Common: QuestionBlock
// Common: BrickWithCoins
// Common: BrickWithItem
// Common: GetAreaObjectID
// Common: Hole_Empty
// Common: RenderUnderPart
// Common: ChkLrgObjLength
// Common: ChkLrgObjFixedLength
// Common: GetLrgObjAttrib
// Common: GetAreaObjXPosition
// Common: GetAreaObjYPosition
// Common: GetBlockBufferAddr
// Common: LoadAreaPointer
// Common: GetAreaType
// Common: FindAreaPointer


// SMB:9c22
// Signature: [] -> []
void GetAreaDataAddrs(void) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  bVar2 = GetAreaType(AreaPointer);
  AreaAddrsLOffset = AreaPointer & 0x1f;
  EnemyData.lo = EnemyDataAddrLow[(byte)(EnemyAddrHOffsets[bVar2] + AreaAddrsLOffset)];
  EnemyData.hi = EnemyDataAddrHigh[(byte)(EnemyAddrHOffsets[bVar2] + AreaAddrsLOffset)];
  bVar1 = AreaDataAddrLow[(byte)(AreaDataHOffsets[AreaType] + AreaAddrsLOffset)];
  AreaData = CONCAT11(AreaDataAddrHigh[(byte)(AreaDataHOffsets[AreaType] + AreaAddrsLOffset)], bVar1);
  bVar2 = *AreaData;
  bVar3 = bVar2 & 7;
  ForegroundScenery = bVar3;
  if (bVar3 >= 4) {
    ForegroundScenery = 0;
    BackgroundColorCtrl = bVar3;
  }
  PlayerEntranceCtrl = (bVar2 & 0x38) >> 3;
  GameTimerSetting = bVar2 >> 6;
  bVar2 = AreaData[1];
  TerrainControl = bVar2 & 0xf;
  BackgroundScenery = (bVar2 & 0x30) >> 4;
  AreaStyle = bVar2 >> 6;
  if (AreaStyle == 3) {
    AreaStyle = 0;
    CloudTypeOverride = 3;
  }
  AreaData
      = CONCAT11(AreaDataAddrHigh[(byte)(AreaDataHOffsets[AreaType] + AreaAddrsLOffset)] + (bVar1 >= 0xfe), bVar1 + 2);
  return;
}


// Common: GameMode
// Common: GameCoreRoutine
// Common: UpdScrollVar
// Common: ScrollHandler


// SMB:afc4
// Signature: [Y] -> []
void ScrollScreen(byte param_1) {
  ScrollThirtyTwo = param_1 + ScrollThirtyTwo;
  HorizontalScroll = param_1 + ScreenEdgeOrLeft_X_Pos[0];
  ScreenEdgeOrLeft_PageLoc[0] += CARRY1(param_1, ScreenEdgeOrLeft_X_Pos[0]);
  Mirror_PPU_CTRL_REG1 = Mirror_PPU_CTRL_REG1 & 0xfe | ScreenEdgeOrLeft_PageLoc[0] & 1;
  ScreenEdgeOrLeft_X_Pos[0] = HorizontalScroll;
  ScrollAmount = param_1;
  GetScreenPosition();
  ScrollIntervalTimer = 8;
  ChkPOffscr();
  return;
}


// Common: ChkPOffscr
// Common: GetScreenPosition
// Common: GameRoutines
// Common: PlayerEntrance
// Common: AutoControlPlayer
// Common: PlayerCtrlRoutine
// Common: Vine_AutoClimb
// Common: SetEntr
// Common: VerticalPipeEntry
// Common: MovePlayerYAxis
// Common: SideExitPipeEntry
// Common: ChgAreaMode
// Common: EnterSidePipe
// Common: PlayerChangeSize
// Common: PlayerInjuryBlink
// Common: InitChangeSize
// Common: PlayerDeath
// Common: DonePlayerTask
// Common: PlayerFireFlower
// Common: CyclePlayerPalette
// Common: ResetPalStar
// Common: FlagpoleSlide
// Common: PlayerEndLevel
// Common: NextArea
// Common: PlayerMovementSubs
// Common: OnGroundStateSub
// Common: FallingSub
// Common: JumpSwimSub
// Common: LRAir
// Common: ClimbingSub
// Common: PlayerPhysicsSub
// Common: GetPlayerAnimSpeed
// Common: ImposeFriction
// Common: ProcFireball_Bubble
// Common: FireballObjCore
// Common: BubbleCheck
// Common: SetupBubble
// Common: MoveBubl
// Common: RunGameTimer
// Common: WarpZoneObject
// Common: ProcessWhirlpools
// Common: FlagpoleRoutine
// Common: JumpspringHandler
// Common: Setup_Vine
// Common: VineObjectHandler
// Common: ProcessCannons
// Common: BulletBillHandler
// Common: SpawnHammerObj
// Common: ProcHammerObj
// Common: CoinBlock
// Common: SetupJumpCoin
// Common: JCoinC
// Common: FindEmptyMiscSlot
// Common: MiscObjectsCore


// SMB:bbfe
// Signature: [] -> [X]
byte GiveOneCoin(void) {
  byte bVar1;

  DigitModifier[5] = 1;
  DigitsMathRoutine(CoinTallyOffsets[CurrentPlayer]);
  CoinTally += 1;
  if (CoinTally == 100) {
    CoinTally = 0;
    NumberofLives += 1;
    Square2SoundQueue = 0x40;
  }
  DigitModifier[4] = 2;
  bVar1 = AddToScore();
  return bVar1;
}


// SMB:bc27
// Signature: [] -> [X]
byte AddToScore(void) {
  byte bVar1;

  DigitsMathRoutine(ScoreOffsets[CurrentPlayer]);
  bVar1 = GetSBNybbles();
  return bVar1;
}


// SMB:bc30
// Signature: [] -> [X]
byte GetSBNybbles(void) {
  byte bVar1;

  bVar1 = WriteDigits(StatusBarNybbles[CurrentPlayer]);
  return bVar1;
}


// Common: WriteDigits
// Common: SetupPowerUp
// Common: PwrUpJmp
// Common: PowerUpObjHandler
// Common: PlayerHeadCollision
// Common: InitBlock_XY_Pos
// Common: BumpBlock
// Common: MushFlowerBlock
// Common: StarBlock
// Common: ExtraLifeMushBlock
// Common: VineBlock
// Common: BlockBumpedChk
// Common: BrickShatter
// Common: CheckTopOfBlock
// Common: SpawnBrickChunks
// Common: BlockObjectsCore
// Common: BlockObjMT_Updater
// Common: MoveEnemyHorizontally
// Common: MovePlayerHorizontally
// Common: MoveObjectHorizontally
// Common: MovePlayerVertically
// Common: MoveD_EnemyVertically
// Common: MoveFallingPlatform
// Common: MoveRedPTroopaDown
// Common: MoveRedPTroopaUp
// Common: MoveDropPlatform
// Common: MoveEnemySlowVert
// Common: MoveJ_EnemyVertically
// Common: SetXMoveAmt
// Common: ImposeGravityBlock
// Common: ImposeGravitySprObj
// Common: MovePlatformDown
// Common: MovePlatformUp
// Common: RedPTroopaGrav
// Common: ImposeGravity
// Common: EnemiesAndLoopsCore
// Common: ExecGameLoopback
// Common: ProcLoopCommand
// Common: InitEnemyObject
// Common: CheckThreeBytes
// Common: Inc2B
// Common: CheckpointEnemyID
// Common: NoInitCode
// Common: InitGoomba
// Common: InitPodoboo
// Common: InitRetainerObj
// Common: InitNormalEnemy
// Common: InitRedKoopa
// Common: InitHammerBro
// Common: InitHorizFlySwimEnemy
// Common: InitBloober
// Common: SmallBBox
// Common: InitRedPTroopa
// Common: InitVStf
// Common: InitBulletBill
// Common: InitCheepCheep
// Common: InitLakitu
// Common: SetupLakitu
// Common: LakituAndSpinyHandler
// Common: InitLongFirebar
// Common: InitShortFirebar
// Common: InitFlyingCheepCheep
// Common: InitBowser
// Common: DuplicateEnemyObj
// Common: InitBowserFlame
// Common: PutAtRightExtent
// Common: InitFireworks
// Common: BulletBillCheepCheep
// Common: HandleGroupEnemies
// Common: InitPiranhaPlant
// Common: InitEnemyFrenzy
// Common: NoFrenzyCode
// Common: EndFrenzy
// Common: InitJumpGPTroopa
// Common: InitBalPlatform
// Common: InitDropPlatform
// Common: InitHoriPlatform
// Common: InitVertPlatform
// Common: SPBBox
// Common: LargeLiftUp
// Common: LargeLiftDown
// Common: PlatLiftUp
// Common: PlatLiftDown
// Common: PosPlatform
// Common: EndOfEnemyInitCode
// Common: RunEnemyObjectsCore
// Common: NoRunCode
// Common: RunRetainerObj
// Common: RunNormalEnemies
// Common: EnemyMovementSubs
// Common: NoMoveCode
// Common: RunBowserFlame
// Common: RunFirebarObj
// Common: RunSmallPlatform
// Common: RunLargePlatform
// Common: LargePlatformSubroutines
// Common: EraseEnemyObject
// Common: MovePodoboo
// Common: ProcHammerBro
// Common: SetHJ
// Common: MoveHammerBroXDir
// Common: MoveNormalEnemy
// Common: MoveDefeatedEnemy
// Common: MoveJumpingEnemy
// Common: ProcMoveRedPTroopa
// Common: MoveFlyGreenPTroopa
// Common: XMoveCntr_GreenPTroopa
// Common: XMoveCntr_Platform
// Common: MoveWithXMCntrs
// Common: MoveBloober
// Common: ProcSwimmingB
// Common: MoveBulletBill
// Common: MoveSwimmingCheepCheep
// Common: ProcFirebar
// Common: DrawFirebar_Collision
// Common: FirebarCollision
// Common: GetFirebarPosition
// Common: MoveFlyingCheepCheep
// Common: MoveLakitu
// Common: PlayerLakituDiff
// Common: BridgeCollapse
// Common: MoveD_Bowser
// Common: RunBowser
// Common: KillAllEnemies
// Common: BowserGfxHandler
// Common: ProcessBowserHalf
// Common: SetFlameTimer
// Common: ProcBowserFlame
// Common: RunFireworks
// Common: RunStarFlagObj


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
  return;
}


// Common: StarFlagExit
// Common: AwardGameTimerPoints
// Common: AwardTimerCastle


// SMB:d336
// Signature: [] -> [X]
byte EndAreaPoints(void) {
  DigitsMathRoutine(CurrentPlayer == 0 ? 0xb : 0x11);
  return WriteDigits(CurrentPlayer << 4 | 4);
}


// Common: RaiseFlagSetoffFWorks
// Common: DrawStarFlag
// Common: DelayToAreaEnd
// Common: MovePiranhaPlant
// Common: FirebarSpin
// Common: BalancePlatform
// Common: SetupPlatformRope
// Common: InitPlatformFall
// Common: StopPlatforms
// Common: PlatformFall
// Common: YMovingPlatform
// Common: ChkYPCollision
// Common: XMovingPlatform
// Common: PositionPlayerOnHPlat
// Common: DropPlatform
// Common: RightPlatform
// Common: MoveLargeLiftPlat
// Common: MoveSmallPlatform
// Common: MoveLiftPlatforms
// Common: ChkSmallPlatCollision
// Common: OffscreenBoundsCheck
// Common: FireballEnemyCollision
// Common: HandleEnemyFBallCol
// Common: ShellOrBlockDefeat
// Common: EnemySmackScore
// Common: PlayerHammerCollision
// Common: HandlePowerUpCollision


// SMB:d853
// Signature: [X] -> [X]
byte PlayerEnemyCollision(byte param_1) {
  byte bVar1;
  byte bVar2;
  bool bVar3;
  struct_ay sVar4;
  byte bStack0000;

  if ((bool)(FrameCounter & 1)) {
    return param_1;
  }
  bVar3 = CheckPlayerVertical();
  if ((((!bVar3) && (EnemyOffscrBitsMasked[param_1] == 0)) && (GameEngineSubroutine == 8))
      && ((Enemy_State[param_1] & 0x20) == 0)) {
    sVar4 = GetEnemyBoundBoxOfs();
    bVar3 = PlayerCollisionCore(sVar4.y);
    param_1 = ObjectOffset;
    if (bVar3) {
      bVar1 = Enemy_ID[ObjectOffset];
      if (bVar1 == 0x2e) {
        bVar1 = HandlePowerUpCollision(ObjectOffset);
        return bVar1;
      }
      if (StarInvincibleTimer != 0) {
        bVar1 = ObjectOffset;
        ShellOrBlockDefeat(ObjectOffset);
        return bVar1;
      }
      if ((Enemy_CollisionBits[ObjectOffset] & 1 | EnemyOffscrBitsMasked[ObjectOffset]) != 0) {
        return param_1;
      }
      Enemy_CollisionBits[ObjectOffset] = Enemy_CollisionBits[ObjectOffset] | 1;
      if ((bVar1 != 0x12) && (SMB1_ONLY || (SMB2J_ONLY && bVar1 != 0x33))) {
        if (bVar1 == 0xd || (SMB2J_ONLY && bVar1 == 4) || bVar1 == 0xc) {
          bVar1 = InjurePlayer();
          return bVar1;
        }
        if (SMB2J_ONLY || bVar1 != 0x33) {
          if (bVar1 > 0x14) {
            bVar1 = InjurePlayer();
            return bVar1;
          }
          if (AreaType == 0) {
            bVar1 = InjurePlayer();
            return bVar1;
          }
          if ((!(bool)(Enemy_State[param_1] >> 7)) && (1 < (Enemy_State[param_1] & 7))) {
            if (Enemy_ID[param_1] == 6) {
              return param_1;
            }
            Square1SoundQueue = 8;
            Enemy_State[param_1] = Enemy_State[param_1] | 0x80;
            bVar1 = EnemyFacePlayer(param_1);
            SpriteVarData1[param_1] = KickedShellXSpdData[bVar1];
            bVar1 = StompChainCounter + 3;
            if (EnemyIntervalTimer[param_1] < 3) {
              bVar1 = KickedShellPtsData[EnemyIntervalTimer[param_1]];
            }
            SetupFloateyNumber(bVar1, param_1);
            return param_1;
          }
        }
      }
      if ((((PlayerSpriteVarData2[0] >= 0x80) || (PlayerSpriteVarData2[0] == 0))
           && ((Enemy_ID[param_1] < 7 || (Enemy_Y_Position[param_1] <= (byte)(SprObject_Y_Position[0] + 0xc)))))
          && (StompTimer == 0)) {
        if (InjuryTimer != 0) {
          return ObjectOffset;
        }
        if (SprObject_Rel_XPos[0] < Enemy_Rel_XPos) {
          if (Enemy_MovingDir[param_1] == 1) {
            bVar1 = LInj(param_1);
            return bVar1;
          }
          bVar1 = InjurePlayer();
          return bVar1;
        }
        bVar1 = ChkEnemyFaceRight(param_1);
        return bVar1;
      }
      if (Enemy_ID[param_1] == 0x12) {
        bVar1 = InjurePlayer();
        return bVar1;
      }
      Square1SoundQueue = 4;
      bVar1 = Enemy_ID[param_1];
      bVar2 = 0;
      if (((((bVar1 != 0x14) && (bVar1 != 8)) && (bVar1 != 0x33)) && ((bVar1 != 0xc && (bVar2 = 1, bVar1 != 5))))
          && ((bVar2 = 2, bVar1 != 0x11 && (bVar2 = 3, bVar1 != 7)))) {
        if (bVar1 < 9) {
          Enemy_State[param_1] = 4;
          StompChainCounter += 1;
          SetupFloateyNumber(StompChainCounter + StompTimer, param_1);
          StompTimer += 1;
          EnemyIntervalTimer[param_1] = RevivalRateData[PrimaryHardMode];
        } else {
          Enemy_ID[param_1] = bVar1 & 1;
          Enemy_State[param_1] = 0;
          SetupFloateyNumber(3, param_1);
          InitVStf(param_1);
          bVar1 = EnemyFacePlayer(param_1);
          SpriteVarData1[param_1] = DemotedKoopaXSpdData[bVar1];
        }
        PlayerSpriteVarData2[0] = 0xfc;
        return param_1;
      }
      SetupFloateyNumber(StompedEnemyPtsData[bVar2], param_1);
      bStack0000 = Enemy_MovingDir[param_1];
      SetStun(param_1);
      Enemy_MovingDir[param_1] = bStack0000;
      Enemy_State[param_1] = 0x20;
      bVar1 = InitVStf(param_1);
      SpriteVarData1[param_1] = bVar1;
      PlayerSpriteVarData2[0] = 0xfd;
      return param_1;
    }
    Enemy_CollisionBits[ObjectOffset] = Enemy_CollisionBits[ObjectOffset] & 0xfe;
  }
  return param_1;
}


// Common: InjurePlayer
// Common: ForceInjury
// Common: SetPRout
// Common: ChkEnemyFaceRight
// Common: LInj
// Common: EnemyFacePlayer
// Common: SetupFloateyNumber
// Common: EnemiesCollision
// Common: ProcEnemyCollisions
// Common: EnemyTurnAround
// Common: RXSpd
// Common: LargePlatformCollision
// Common: ChkForPlayerC_LargeP
// Common: SmallPlatformCollision
// Common: ProcLPlatCollisions
// Common: PositionPlayerOnS_Plat
// Common: PositionPlayerOnVPlat
// Common: CheckPlayerVertical
// Common: GetEnemyBoundBoxOfs
// Common: GetEnemyBoundBoxOfsArg
// Common: PlayerBGCollision
// Common: ErACM
// Common: HandleClimbing


// SMB:debd
// Signature: [A] -> [Z]
bool ChkInvisibleMTiles(byte mtile) {
  return mtile == 0x5f || mtile == 0x60;
}


// Common: ChkForLandJumpSpring
// Common: ChkJumpspringMetatiles
// Common: HandlePipeEntry
// Common: ImpedePlayerMove
// Common: CheckForSolidMTiles
// Common: CheckForClimbMTiles
// Common: CheckForCoinMTiles
// Common: GetMTileAttrib
// Common: EnemyToBGCollisionDet


// SMB:e01b
// Signature: [A, X] -> []
void ChkToStunEnemies(byte param_1, byte param_2) {
  if (param_1 < 9) {
    SetStun(param_2);
    return;
  }
  if (param_1 > 0x10) {
    SetStun(param_2);
    return;
  }
  if ((param_1 >= 10) && (param_1 < 0xd)) {
    SetStun(param_2);
    return;
  }
  Enemy_ID[param_2] = param_1 & 1;
  SetStun(param_2);
  return;
}


// SMB:e02f
// Signature: [X] -> []
void SetStun(byte param_1) {
  Enemy_State[param_1] = Enemy_State[param_1] & 0xf0 | 2;
  SetStun2(param_1);
}


// Common: SetStun2
// Common: ChkForRedKoopa
// Common: DoEnemySideCheck
// Common: ChkForBump_HammerBroJ
// Common: PlayerEnemyDiff
// Common: EnemyLanding
// Common: SubtEnemyYPos
// Common: EnemyJump
// Common: HammerBroBGColl
// Common: KillEnemyAboveBlock
// Common: ChkUnderEnemy


// SMB:e1ae
// Signature: [X] -> [A, X, Z, r02, r04, r06, r07]
struct_axzr02r04r06r07 ChkUnderEnemy_Ext(byte param_1) {
  struct_axzr02r04r06r07 sVar1;

  sVar1 = BlockBufferChk_Enemy_Ext(0, param_1, 0x15);
  return sVar1;
}


// Common: ChkForNonSolids
// Common: FireballBGCollision
// Common: GetFireballBoundBox
// Common: GetMiscBoundBox
// Common: GetEnemyBoundBox
// Common: SmallPlatformBoundBox
// Common: GetMaskedOffScrBits
// Common: LargePlatformBoundBox
// Common: SetupEOffsetFBBox
// Common: MoveBoundBoxOffscreen
// Common: BoundingBoxCore
// Common: CheckRightScreenBBox
// Common: PlayerCollisionCore
// Common: SprObjectCollisionCore
// Common: BlockBufferChk_Enemy


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


// Common: BlockBufferChk_FBall
// Common: BlockBufferColli_Feet
// Common: BlockBufferColli_Head
// Common: BlockBufferColli_Side
// Common: BlockBufferCollision
// Common: DrawVine
// Common: SixSpriteStacker
// Common: DrawHammer
// Common: FlagpoleGfxHandler
// Common: MoveSixSpritesOffscreen
// Common: DumpSixSpr
// Common: DumpFourSpr
// Common: DumpThreeSpr
// Common: DumpTwoSpr
// Common: DrawLargePlatform
// Common: JCoinGfxHandler
// Common: DrawPowerUp
// Common: EnemyGfxHandler
// Common: DrawEnemyObject
// Common: SprObjectOffscrChk
// Common: DrawEnemyObjRow
// Common: DrawOneSpriteRow
// Common: MoveESprRowOffscreen
// Common: MoveESprColOffscreen
// Common: DrawBlock
// Common: ChkLeftCo
// Common: MoveColOffscreen
// Common: DrawBrickChunks
// Common: DrawFireball
// Common: DrawFirebar
// Common: DrawExplosion_Fireball
// Common: DrawExplosion_Fireworks
// Common: DrawSmallPlatform
// Common: DrawBubble
// Common: PlayerGfxHandler
// Common: FindPlayerAction
// Common: PlayerGfxProcessing
// Common: DrawPlayer_Intermediate
// Common: RenderPlayerSub
// Common: DrawPlayerLoop
// Common: ProcessPlayerAction
// Common: GetCurrentAnimOffset
// Common: FourFrameExtent
// Common: ThreeFrameExtent
// Common: AnimationControl
// Common: GetGfxOffsetAdder
// Common: HandleChangeSize
// Common: GetOffsetFromAnimCtrl
// Common: ChkForPlayerAttrib
// Common: RelativePlayerPosition
// Common: RelativeBubblePosition
// Common: RelativeFireballPosition
// Common: RelativeMiscPosition
// Common: RelativeEnemyPosition
// Common: RelativeBlockPosition
// Common: VariableObjOfsRelPos
// Common: GetObjRelativePosition
// Common: GetPlayerOffscreenBits
// Common: GetFireballOffscreenBits
// Common: GetBubbleOffscreenBits
// Common: GetMiscOffscreenBits
// Common: GetProperObjOffset
// Common: GetEnemyOffscreenBits
// Common: GetBlockOffscreenBits
// Common: GetOffScreenBitsSet
// Common: RunOffscrBitsSubs
// Common: GetXOffscreenBits
// Common: GetYOffscreenBits
// Common: DividePDiff
// Common: DrawSpriteObject
