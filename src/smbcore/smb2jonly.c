#include "types.h"
#include "vars.h"

// SM2MAIN:n/a
// Signature: [A, r00] -> []
void jumptable_OperModeExecutionTree(byte param_1, byte param_2) {
  if (param_1 == 0) {
    AttractModeSubs();
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


// SM2MAIN:n/a
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
    EndCastleAward();
    return;
  }
  if (param_1 == 5) {
    PlayerEndWorld();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// SM2MAIN:n/a
// Signature: [A, r00] -> []
void jumptable_VictoryModeSubroutines_forW8(byte param_1, byte param_2) {
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
    StartVMDelay();
    return;
  }
  if (param_1 == 4) {
    ContinueVMDelay();
    return;
  }
  if (param_1 == 5) {
    VictoryModeDiskRoutines();
    return;
  }
  if (param_1 == 6) {
    ScreenSubsForFinalRoom();
    return;
  }
  if (param_1 == 7) {
    PrintVictoryMsgsForWorld8();
    return;
  }
  if (param_1 == 8) {
    EndCastleAward();
    return;
  }
  if (param_1 == 9) {
    AwardExtraLives();
    return;
  }
  if (param_1 == 10) {
    FadeToBlue();
    return;
  }
  if (param_1 == 0xb) {
    EraseLivesLines();
    return;
  }
  if (param_1 == 0xc) {
    RunMushroomRetainers();
    return;
  }
  if (param_1 == 0xd) {
    EndingDiskRoutines();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// SM2MAIN:n/a
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
    DemoReset();
    return;
  }
  if (param_1 == 8) {
    ResetSpritesAndScreenTimer();
    return;
  }
  if (param_1 == 9) {
    AreaParserTaskControl();
    return;
  }
  if (param_1 == 10) {
    GetAreaPalette();
    return;
  }
  if (param_1 == 0xb) {
    GetBackgroundColor();
    return;
  }
  if (param_1 == 0xc) {
    GetAlternatePalette1();
    return;
  }
  if (param_1 == 0xd) {
    DrawTitleScreen();
    return;
  }
  if (param_1 == 0xe) {
    ClearBuffersDrawIcon();
    return;
  }
  if (param_1 == 0xf) {
    WriteTopScore();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// Common: jumptable_GameOverMode
// Common: jumptable_AreaParserTasks


// SM2MAIN:n/a
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
    UpsideDownPipe_High(param_2);
    return;
  }
  if (param_1 == 0x17) {
    UpsideDownPipe_Low(param_2);
    return;
  }
  if (param_1 == 0x18) {
    QuestionBlock(param_2, param_3);
    return;
  }
  if (param_1 == 0x19) {
    QuestionBlock(param_2, param_3);
    return;
  }
  if (param_1 == 0x1a) {
    QuestionBlock(param_2, param_3);
    return;
  }
  if (param_1 == 0x1b) {
    QuestionBlock(param_2, param_3);
    return;
  }
  if (param_1 == 0x1c) {
    Hidden1UpBlock(param_2, param_3);
    return;
  }
  if (param_1 == 0x1d) {
    QuestionBlock(param_2, param_3);
    return;
  }
  if (param_1 == 0x1e) {
    QuestionBlock(param_2, param_3);
    return;
  }
  if (param_1 == 0x1f) {
    BrickWithItem(param_2, param_3);
    return;
  }
  if (param_1 == 0x20) {
    BrickWithItem(param_2, param_3);
    return;
  }
  if (param_1 == 0x21) {
    BrickWithItem(param_2, param_3);
    return;
  }
  if (param_1 == 0x22) {
    BrickWithItem(param_2, param_3);
    return;
  }
  if (param_1 == 0x23) {
    BrickWithCoins(param_2, param_3);
    return;
  }
  if (param_1 == 0x24) {
    BrickWithItem(param_2, param_3);
    return;
  }
  if (param_1 == 0x25) {
    WaterPipe(param_2);
    return;
  }
  if (param_1 == 0x26) {
    EmptyBlock(param_2);
    return;
  }
  if (param_1 == 0x27) {
    Jumpspring(param_2);
    return;
  }
  if (param_1 == 0x28) {
    IntroPipe(param_2);
    return;
  }
  if (param_1 == 0x29) {
    FlagpoleObject();
    return;
  }
  if (param_1 == 0x2a) {
    AxeObj(param_3);
    return;
  }
  if (param_1 == 0x2b) {
    ChainObj(param_3);
    return;
  }
  if (param_1 == 0x2c) {
    CastleBridgeObj(param_2, param_3);
    return;
  }
  if (param_1 == 0x2d) {
    ScrollLockObject_Warp();
    return;
  }
  if (param_1 == 0x2e) {
    ScrollLockObject();
    return;
  }
  if (param_1 == 0x2f) {
    ScrollLockObject();
    return;
  }
  if (param_1 == 0x30) {
    AreaFrenzy(param_3);
    return;
  }
  if (param_1 == 0x31) {
    AreaFrenzy(param_3);
    return;
  }
  if (param_1 == 0x32) {
    AreaFrenzy(param_3);
    return;
  }
  if (param_1 == 0x33) {
    LoopCmdE();
    return;
  }
  if (param_1 == 0x34) {
    WindOn();
    return;
  }
  if (param_1 == 0x35) {
    WindOff();
    return;
  }
  if (param_1 == 0x36) {
    AlterAreaAttributes(param_2);
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// SM2MAIN:n/a
// Signature: [A, X] -> []
void jumptable_AreaStyleObject(byte param_1, byte param_2) {
  if (param_1 == 0) {
    TreeLedge(param_2);
    return;
  }
  if (param_1 == 1) {
    CloudLedge(param_2);
    return;
  }
  if (param_1 == 2) {
    BulletBillCannon(param_2);
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// SM2MAIN:n/a
// Signature: [A] -> []
void jumptable_GameMode(byte param_1) {
  if (param_1 == 0) {
    GameModeDiskRoutines();
    return;
  }
  if (param_1 == 1) {
    InitializeArea();
    return;
  }
  if (param_1 == 2) {
    ScreenRoutines();
    return;
  }
  if (param_1 == 3) {
    SecondaryGameSetup();
    return;
  }
  if (param_1 == 4) {
    GameCoreRoutine();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// Common: jumptable_GameRoutines
// Common: jumptable_PlayerMovementSubs


// SM2MAIN:n/a
// Signature: [A, X] -> []
void jumptable_BumpBlock(byte param_1, byte param_2) {
  if (param_1 == 0) {
    MushFlowerBlock(param_2);
    return;
  }
  if (param_1 == 1) {
    PoisonMushBlock(param_2);
    return;
  }
  if (param_1 == 2) {
    CoinBlock(param_2, false);
    return;
  }
  if (param_1 == 3) {
    CoinBlock(param_2, false);
    return;
  }
  if (param_1 == 4) {
    ExtraLifeMushBlock(param_2);
    return;
  }
  if (param_1 == 5) {
    PoisonMushBlock(param_2);
    return;
  }
  if (param_1 == 6) {
    MushFlowerBlock(param_2);
    return;
  }
  if (param_1 == 7) {
    MushFlowerBlock(param_2);
    return;
  }
  if (param_1 == 8) {
    PoisonMushBlock(param_2);
    return;
  }
  if (param_1 == 9) {
    VineBlock();
    return;
  }
  if (param_1 == 10) {
    StarBlock(param_2);
    return;
  }
  if (param_1 == 0xb) {
    CoinBlock(param_2, false);
    return;
  }
  if (param_1 == 0xc) {
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


// SM2MAIN:n/a
// Signature: [A] -> []
void jumptable_AttractModeSubs(byte param_1) {
  if (param_1 == 0) {
    AttractModeDiskRoutines();
    return;
  }
  if (param_1 == 1) {
    InitializeGame();
    return;
  }
  if (param_1 == 2) {
    ScreenRoutines();
    return;
  }
  if (param_1 == 3) {
    PrimaryGameSetup();
    return;
  }
  if (param_1 == 4) {
    GameMenuRoutine();
    return;
  }
  if (param_1 == 5) {
    HardWorldsCheckpoint();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// SM2MAIN:n/a
// Signature: [A] -> []
void jumptable_HardWorldsCheckpoint(byte param_1) {
  if (param_1 == 0) {
    DiskScreen();
    return;
  }
  if (param_1 == 1) {
    LoadHardWorlds();
    return;
  }
  if (param_1 == 2) {
    WaitForEject();
    return;
  }
  if (param_1 == 3) {
    WaitForReinsert();
    return;
  }
  if (param_1 == 4) {
    ResetDiskVars();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// SM2MAIN:n/a
// Signature: [A] -> []
void jumptable_AttractModeDiskRoutines(byte param_1) {
  if (param_1 == 0) {
    DiskScreen();
    return;
  }
  if (param_1 == 1) {
    LoadWorlds1Thru4();
    return;
  }
  if (param_1 == 2) {
    WaitForEject();
    return;
  }
  if (param_1 == 3) {
    WaitForReinsert();
    return;
  }
  if (param_1 == 4) {
    ResetDiskVars();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// SM2MAIN:n/a
// Signature: [A] -> []
void jumptable_GameModeDiskRoutines(byte param_1) {
  if (param_1 == 0) {
    DiskScreen();
    return;
  }
  if (param_1 == 1) {
    LoadWorlds5Thru8();
    return;
  }
  if (param_1 == 2) {
    WaitForEject();
    return;
  }
  if (param_1 == 3) {
    WaitForReinsert();
    return;
  }
  if (param_1 == 4) {
    ResetDiskVars();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// SM2MAIN:n/a
// Signature: [A] -> []
void jumptable_VictoryModeDiskRoutines(byte param_1) {
  if (param_1 == 0) {
    DiskScreen();
    return;
  }
  if (param_1 == 1) {
    LoadEnding();
    return;
  }
  if (param_1 == 2) {
    WaitForEject();
    return;
  }
  if (param_1 == 3) {
    WaitForReinsert();
    return;
  }
  if (param_1 == 4) {
    ResetDiskVars();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}


// Common: PauseRoutine
// Common: SpriteShuffler
// Common: OperModeExecutionTree
// Common: MoveAllSpritesOffscreen
// Common: MoveSpritesOffscreen
// Common: VictoryMode
// Common: VictoryModeSubroutines
// Common: SetupVictoryMode


// SM2MAIN:632a
// Signature: [] -> []
void DrawTitleScreen(void) {
  if (OperMode == 0) {
    VRAM_Buffer_AddrCtrl = 5;
    ScreenRoutineTask = ScreenRoutineTask + 1;
    return;
  }
  OperMode_Task = OperMode_Task + 1;
  return;
}


// Common: PlayerVictoryWalk


// SM2MAIN:636d
// Signature: [] -> []
void PrintVictoryMessages(void) {
  bool bVar1;

  if ((SecondaryMsgCounter == 0)
      && ((PrimaryMsgCounter == 0 || ((PrimaryMsgCounter < 8 && (PrimaryMsgCounter != 0)))))) {
    if (PrimaryMsgCounter != 0) {
      bVar1 = PrimaryMsgCounter > 2;
      if (bVar1) {
        goto SetEndTimer;
      }
      if (PrimaryMsgCounter > 1) {
        goto IncMsgCounter;
      }
    }
    VRAM_Buffer_AddrCtrl = PrimaryMsgCounter + 0xc;
  }
IncMsgCounter:
  PrimaryMsgCounter += SecondaryMsgCounter >= 0xfc;
  bVar1 = PrimaryMsgCounter > 5;
  SecondaryMsgCounter = SecondaryMsgCounter + 4;
SetEndTimer:
  if (bVar1) {
    WorldEndTimer = 8;
    OperMode_Task += 1;
  }
  return;
}


// SM2MAIN:63af
// Signature: [] -> []
void EndCastleAward(void) {
  if (WorldEndTimer < 6) {
    AwardTimerCastle();
    if ((byte)(GameTimerDisplay[0] | GameTimerDisplay[1] | GameTimerDisplay[2]) == 0) {
      SelectTimer = 0x30;
      WorldEndTimer = 6;
      OperMode_Task += 1;
    }
  }
  return;
}


// Common: PlayerEndWorld
// Common: FloateyNumbersRoutine
// Common: ScreenRoutines
// Common: InitScreen


// SM2MAIN:64f6
// Signature: [] -> []
void InitScreenPalette(void) {
  VRAM_Buffer_AddrCtrl = 3;
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}


// Common: SetupIntermediate
// Common: GetAreaPalette
// Common: GetBackgroundColor
// Common: GetPlayerColors
// Common: GetAlternatePalette1
// Common: WriteTopStatusLine
// Common: WriteBottomStatusLine


// SM2MAIN:65e6
// Signature: [] -> [A]
byte GetWorldNumForDisplay(void) {
  byte bVar1;

  bVar1 = WorldNumber;
  if (HardWorldFlag != 0) {
    bVar1 = (WorldNumber & 3) + 9;
  }
  return bVar1 + 1;
}


// Common: DisplayTimeUp
// Common: DisplayIntermediate
// Common: AreaParserTaskControl


// SM2MAIN:671b
// Signature: [A] -> []
void WriteGameText(byte param_1) {
  byte offset = GameTextOffsets[param_1];

  bool terminated = false;
  for (int i = 0; i < 256; i++) {
    if (TopStatusBarLine[offset] == 0xff) {
      VRAM_Buffer1[i] = 0;
      terminated = true;
      break;
    }
    VRAM_Buffer1[i] = TopStatusBarLine[offset];
    offset += 1;
  }
  if (!terminated) {
    VRAM_Buffer1[0] = 0;
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
    VRAM_Buffer1[19] = GetWorldNumForDisplay();
    VRAM_Buffer1[21] = LevelNumber + 1;
  }
}


// SM2MAIN:675e
// Signature: [A] -> []
void WriteWarpZoneMessage(byte param_1) {
  byte bVar1;

  bVar1 = 0xff;
  do {
    bVar1 += 1;
    VRAM_Buffer1[bVar1] = WarpZone[bVar1];
  } while (WarpZone[bVar1] != 0);
  VRAM_Buffer1[27] = WarpZoneNumbers[(byte)(param_1 + 0x80)];
  VRAM_Buffer1_Offset = 0x24;
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
// Common: InitializeArea
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
// Common: AreaParserTaskHandler
// Common: AreaParserTasks
// Common: IncrementColumnPos
// Common: AreaParserCore
// Common: ProcessAreaData
// Common: IncAreaObjOffset
// Common: DecodeAreaData
// Common: LoopCmdE
// Common: AlterAreaAttributes


// SM2MAIN:7513
// Signature: [] -> []
void ScrollLockObject_Warp(void) {
  WarpZoneControl = 0x80;
  if (HardWorldFlag == 0) {
    if (WorldNumber == 0) {
      if (AreaType != 1) {
        if (AreaAddrsLOffset == 0) {
          goto DumpWarpCtrl;
        }
        WarpZoneControl = 0x81;
      }
      WarpZoneControl += 1;
      goto DumpWarpCtrl;
    }
  } else {
    WarpZoneControl = LevelNumber + 0x87;
    if (WarpZoneControl != 0) {
      goto DumpWarpCtrl;
    }
  }
  WarpZoneControl = 0x83;
  if (WorldNumber == 2) {
    goto DumpWarpCtrl;
  }
  WarpZoneControl = 0x84;
  if (WorldNumber == 4) {
    if (AreaAddrsLOffset == 0xb) {
      goto DumpWarpCtrl;
    }
    if (AreaType == 1) {
      goto W5Warp3;
    }
  } else {
    WarpZoneControl = 0x85;
W5Warp3:
    WarpZoneControl += 1;
  }
  WarpZoneControl += 1;
DumpWarpCtrl:
  WriteWarpZoneMessage(WarpZoneControl);
  KillEnemies(0xd);
  ScrollLockObject();
  return;
}


// Common: ScrollLockObject
// Common: KillEnemies
// Common: AreaFrenzy
// Common: AreaStyleObject
// Common: TreeLedge


// SM2MAIN:75cf
// Signature: [X] -> []
void CloudLedge(byte param_1) {
  byte bVar1;
  struct_ycr07 sVar2;

  sVar2 = ChkLrgObjLength(param_1);
  bVar1 = sVar2.r07;
  if (sVar2.c != false) {
    MushroomLedgeHalfLen[param_1] = AreaObjectLength[param_1] >> 1;
    NoUnder(0x8a, bVar1);
    return;
  }
  if (AreaObjectLength[param_1] == 0) {
    NoUnder(0x8c, bVar1);
    return;
  }
  MetatileBuffer[bVar1] = 0x8b;
  return;
}


// Common: NoUnder
// Common: PulleyRopeObject
// Common: CastleObject
// Common: WaterPipe
// Common: IntroPipe
// Common: ExitPipe
// Common: RenderSidewaysPipe


// SM2MAIN:7731
// Signature: [X, r00] -> []
void VerticalPipe(byte param_1, byte param_2) {
  byte bVar1;
  byte bVar2;
  struct_yr06r07 sVar3;
  struct_xc sVar4;
  byte bStack0000;

  sVar3 = GetPipeHeight(param_1);
  bVar2 = sVar3.r07;
  bVar1 = sVar3.r06;
  bStack0000 = sVar3.y;
  if (param_2 != 0) {
    bStack0000 += 4;
  }
  if (AreaObjectLength[param_1] != 0) {
    sVar4 = FindEmptyEnemySlot();
    if (!sVar4.c) {
      SetupPiranhaPlant(0xd, sVar4.x, bVar2);
    }
  }
  MetatileBuffer[bVar2] = VerticalPipeData[bStack0000];
  RenderUnderPart(VerticalPipeData[bStack0000 + 2], bVar2 + 1, bVar1 - 1);
  return;
}


// Common: GetPipeHeight


// SM2MAIN:7772
// Signature: [A, X, r07] -> []
void SetupPiranhaPlant(byte param_1, byte param_2, byte param_3) {
  byte bVar1;

  Enemy_ID[param_2] = param_1;
  bVar1 = GetAreaObjXPosition();
  Enemy_X_Position[param_2] = bVar1 + 8;
  Enemy_PageLoc[param_2] = CurrentPageLoc + (bVar1 >= 0xf8);
  Enemy_Y_HighPos[param_2] = 1;
  Enemy_Flag[param_2] = 1;
  bVar1 = GetAreaObjYPosition(param_3);
  Enemy_Y_Position[param_2] = bVar1;
  InitPiranhaPlant(param_2);
  return;
}


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
// Common: GameMode
// Common: GameCoreRoutine
// Common: UpdScrollVar
// Common: ScrollHandler
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


// SM2MAIN:87c3
// Signature: [] -> [X]
byte GiveOneCoin(void) {
  byte bVar1;

  DigitModifier[5] = 1;
  DigitsMathRoutine(0x11);
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


// SM2MAIN:87e8
// Signature: [] -> [X]
byte AddToScore(void) {
  byte bVar1;

  DigitsMathRoutine(0xb);
  bVar1 = WriteScoreAndCoinTally();
  return bVar1;
}


// SM2MAIN:87ed
// Signature: [] -> [X]
byte WriteScoreAndCoinTally(void) {
  byte bVar1;

  bVar1 = WriteDigits(1);
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


// SM2MAIN:89a1
// Signature: [X] -> []
void PoisonMushBlock(byte param_1) {
  PowerUpType = 4;
  SetupPowerUp(param_1);
  return;
}


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


// SM2MAIN:9f27
// Signature: [X] -> []
void GameTimerFireworks(byte param_1) {
  if (GameTimerDisplay[2] == CoinDisplay[1]) {
    // only show fireworks if the last digit of the timer
    // is the last digit of the coins

    if ((GameTimerDisplay[2] & 1) == 0) {
      // timer is even
      Enemy_State[param_1] = 0;
      FireworksCounter = 6;
    } else {
      // timer is odd
      Enemy_State[param_1] = 3;
      FireworksCounter = 3;
    }
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


// SM2MAIN:9f70
// Signature: [] -> [X]
byte EndAreaPoints(void) {
  DigitsMathRoutine(0xb);
  return WriteDigits(2);
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


// SM2MAIN:a4ab
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
      if (((byte)(PlayerSpriteVarData2[0] - 1) < 0x80)
          || (((Enemy_ID[param_1] >= 7 && ((byte)(SprObject_Y_Position[0] + 0xc) < Enemy_Y_Position[param_1]))
               || (StompTimer != 0)))) {
        if (Enemy_ID[param_1] == 0x12) {
          bVar1 = InjurePlayer();
          return bVar1;
        }
        Square1SoundQueue = 4;
        bVar1 = Enemy_ID[param_1];
        bVar2 = 0;
        if (((((bVar1 != 0x14) && (bVar1 != 8)) && ((bVar1 != 0x33 && ((bVar1 != 0xc && (bVar2 = 1, bVar1 != 5))))))
             && (bVar2 = 2, bVar1 != 0x11))
            && (bVar2 = 3, bVar1 != 7)) {
          if (bVar1 < 9) {
            Enemy_State[param_1] = 4;
            StompChainCounter += 1;
            SetupFloateyNumber(StompChainCounter + StompTimer, param_1);
            StompTimer += 1;
            EnemyIntervalTimer[param_1] = RevivalRateData[PrimaryHardMode];
            SetBounce(param_1);
            return param_1;
          }
          bVar1 = SetBounce(param_1);
          Enemy_ID[param_1] = bVar1 & 1;
          Enemy_State[param_1] = 0;
          SetupFloateyNumber(3, param_1);
          InitVStf(param_1);
          bVar1 = EnemyFacePlayer(param_1);
          SpriteVarData1[param_1] = DemotedKoopaXSpdData[bVar1];
          return param_1;
        }
        SetupFloateyNumber(StompedEnemyPtsData[bVar2], param_1);
        bStack0000 = Enemy_MovingDir[param_1];
        NoDemote(bStack0000, param_1);
        Enemy_MovingDir[param_1] = bStack0000;
        Enemy_State[param_1] = 0x20;
        bVar1 = InitVStf(param_1);
        SpriteVarData1[param_1] = bVar1;
        SetBounce(param_1);
        return param_1;
      }
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
    Enemy_CollisionBits[ObjectOffset] = Enemy_CollisionBits[ObjectOffset] & 0xfe;
  }
  return param_1;
}


// Common: InjurePlayer
// Common: ForceInjury
// Common: SetPRout


// SM2MAIN:a64e
// Signature: [X] -> [A]
byte SetBounce(byte param_1) {
  byte bVar1;

  PlayerSpriteVarData2[0] = 0xfa;
  bVar1 = Enemy_ID[param_1];
  if ((bVar1 == 0xf) || (bVar1 == 0x10)) {
    PlayerSpriteVarData2[0] = 0xf8;
  }
  return bVar1;
}


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


// SM2MAIN:ab40
// Signature: [A] -> [Z]
bool ChkInvisibleMTiles(byte mtile) {
  return mtile == 0x5e || mtile == 0x5f || mtile == 0x60 || mtile == 0x61;
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


// SM2MAIN:aca3
// Signature: [X] -> []
void ChkToStunEnemies(byte param_1) {
  byte bVar1;

  bVar1 = Enemy_ID[param_1];
  if (bVar1 < 9) {
    NoDemote(bVar1, param_1);
    return;
  }
  if (bVar1 > 0x10) {
    NoDemote(bVar1, param_1);
    return;
  }
  if (bVar1 == 0xd) {
    NoDemote(0xd, param_1);
    return;
  }
  if (bVar1 == 4) {
    NoDemote(4, param_1);
    return;
  }
  if ((bVar1 >= 10) && (bVar1 < 0xd)) {
    NoDemote(bVar1, param_1);
    return;
  }
  Enemy_ID[param_1] = bVar1 & 1;
  NoDemote(bVar1 & 1, param_1);
  return;
}


// SM2MAIN:acc1
// Signature: [A, X] -> []
void NoDemote(byte param_1, byte param_2) {
  if ((param_1 != 0x2e) && (param_1 != 6)) {
    Enemy_State[param_2] = 2;
  }
  SetStun2(param_2);
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


// SM2MAIN:bfb0
// Signature: [] -> []
void AttractModeSubs(void) {
  jumptable_AttractModeSubs(OperMode_Task);
  return;
}


// SM2MAIN:bfc2
// Signature: [] -> []
void HardWorldsCheckpoint(void) {
  jumptable_HardWorldsCheckpoint(DiskIOTask);
  return;
}


// SM2MAIN:bfd2
// Signature: [] -> []
void LoadHardWorlds(void) {
  byte bVar1;
  bool bVar2;
  struct_ayz sVar3;

  if (HardWorldFlag != 0) {
    FileListNumber = 3;
    sVar3 = LoadFiles();
    bVar1 = sVar3.a;
    if (sVar3.z != false) {
      bVar2 = CheckFileCount(sVar3.y);
      if (bVar2) {
        goto NoLoadHW;
      }
      bVar1 = 0x40;
    }
    DiskIOTask += 1;
    DiskErrorHandler(bVar1);
    return;
  }
NoLoadHW:
  LoadAreaPointer();
  if (HardWorldFlag != 0) {
    ChangeHalfwayPages();
  }
  Hidden1UpFlag = Hidden1UpFlag + 1;
  FetchNewGameTimerFlag = FetchNewGameTimerFlag + 1;
  OperMode = OperMode + 1;
  DiskIOTask = 0;
  OperMode_Task = 0;
  DemoTimer = 0;
  return;
}


// SM2MAIN:c006
// Signature: [] -> []
void AttractModeDiskRoutines(void) {
  jumptable_AttractModeDiskRoutines(DiskIOTask);
  return;
}


// SM2MAIN:c016
// Signature: [] -> []
void LoadWorlds1Thru4(void) {
  byte bVar1;
  bool bVar2;
  struct_ayz sVar3;

  if ((NotColdFlag != 0) && ((HardWorldFlag != 0 || (WorldNumber >= 4)))) {
    FileListNumber = 0;
    sVar3 = LoadFiles();
    bVar1 = sVar3.a;
    if (sVar3.z != false) {
      bVar2 = CheckFileCount(sVar3.y);
      if (bVar2) {
        goto InitWorldPos;
      }
      bVar1 = 0x40;
    }
    DiskIOTask += 1;
    DiskErrorHandler(bVar1);
    return;
  }
InitWorldPos:
  NotColdFlag = 1;
  WorldNumber = 0;
  HardWorldFlag = 0;
  ResetDiskIOTask();
  return;
}


// SM2MAIN:c04d
// Signature: [] -> []
void GameModeDiskRoutines(void) {
  jumptable_GameModeDiskRoutines(DiskIOTask);
  return;
}


// SM2MAIN:c05d
// Signature: [] -> []
void LoadWorlds5Thru8(void) {
  byte bVar1;
  bool bVar2;
  struct_ayz sVar3;

  if (WorldNumber < 4) {
    ResetDiskIOTask();
    return;
  }
  if (FileListNumber != 0) {
    ResetDiskIOTask();
    return;
  }
  FileListNumber = 1;
  sVar3 = LoadFiles();
  bVar1 = sVar3.a;
  if (sVar3.z != false) {
    bVar2 = CheckFileCount(sVar3.y);
    if (bVar2) {
      ResetDiskIOTask();
      return;
    }
    bVar1 = 0x40;
  }
  DiskIOTask += 1;
  DiskErrorHandler(bVar1);
  return;
}


// SM2MAIN:c078
// Signature: [] -> []
void ResetDiskIOTask(void) {
  DiskIOTask = 0;
  VMDelay();
  return;
}


// SM2MAIN:c07d
// Signature: [] -> []
void VMDelay(void) {
  OperMode_Task = OperMode_Task + 1;
  return;
}


// SM2MAIN:c081
// Signature: [] -> []
void StartVMDelay(void) {
  WorldEndTimer = 0x10;
  VMDelay();
  return;
}


// SM2MAIN:c088
// Signature: [] -> []
void ContinueVMDelay(void) {
  if (WorldEndTimer == 0) {
    VMDelay();
    return;
  }
  return;
}


// SM2MAIN:c08e
// Signature: [] -> []
void VictoryModeDiskRoutines(void) {
  jumptable_VictoryModeDiskRoutines(DiskIOTask);
  return;
}


// SM2MAIN:c09e
// Signature: [] -> []
void LoadEnding(void) {
  bool bVar1;
  struct_ayz sVar2;

  FileListNumber = 2;
  sVar2 = LoadFiles();
  if (sVar2.z != false) {
    bVar1 = CheckFileCount(sVar2.y);
    if (!bVar1) {
      GamesBeatenCount = 0;
    }
    GamesBeatenCount += 1;
    if (GamesBeatenCount > 0x18) {
      GamesBeatenCount = 0x18;
    }
    InitializeNameTables();
    ResetDiskIOTask();
    WriteNameToVictoryMsg();
    return;
  }
  DiskIOTask += 1;
  DiskErrorHandler(sVar2.a);
  return;
}


// SM2MAIN:c0ca
// Signature: [Y] -> [Z]
bool CheckFileCount(byte param_1) { return param_1 == FileCount[FileListNumber]; }


// SM2MAIN:c113
// Signature: [] -> []
void DiskScreen(void) {
  Mirror_PPU_CTRL_REG2 = 0;
  ppumask(0);
  DisableScreenFlag = DisableScreenFlag + 1;
  VRAM_Buffer_AddrCtrl = 0x1a;
  DiskIOTask = DiskIOTask + 1;
  return;
}


// SM2MAIN:c126
// Signature: [] -> []
void WaitForEject(void) {
  byte bVar1;

  NameTableSelect = 0;
  DisableScreenFlag = 0;
  bVar1 = FDS_drive_status();
  if ((bVar1 & 1) != 0) {
    DiskIOTask += 1;
  }
  return;
}


// SM2MAIN:c138
// Signature: [] -> []
void WaitForReinsert(void) {
  byte bVar1;

  bVar1 = FDS_drive_status();
  if ((bool)(bVar1 & 1) == false) {
    DiskIOTask += 1;
  } else if (!(bool)(bVar1 & 1)) {
    ResetDiskVars();
    return;
  }
  return;
}


// SM2MAIN:c140
// Signature: [] -> []
void ResetDiskVars(void) {
  DiskIOTask = 0;
  FileListNumber = 0;
  return;
}


// SM2MAIN:c182
// Signature: [A] -> []
void DiskErrorHandler(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bStack0000;

  DiskErrorMainMsg[19] = param_1 & 0xf;
  DiskErrorMainMsg[18] = param_1 >> 4;
  bVar1 = 3;
  if (((param_1 != 7) && (bVar1 = 2, param_1 != 2)) && (bVar1 = 1, param_1 != 1)) {
    bVar1 = 0;
  }
  bVar1 = DiskErrorMsgOffsets[bVar1];
  bVar2 = 7;
  do {
    DiskErrorMainMsg[bVar2 + 3] = DiskErrorMsgs[bVar1];
    bVar1 -= 1;
  } Nplus1_TIMES(bVar2);
  VRAM_Buffer_AddrCtrl = 0x19;
  bStack0000 = param_1;
  MoveAllSpritesOffscreen();
  InitializeNameTables();
  return;
}


// SM2MAIN:c1c2
// Signature: [] -> []
void GameOverMenu(void) {
  byte bVar1;

  if ((SavedJoypadBits[0] & BUTTON_START) == 0) {
    if (((SavedJoypadBits[0] & BUTTON_SELECT) != 0) && (SelectTimer == 0)) {
      if ((SavedJoypadBits[0] & BUTTON_SELECT) != 0) {
        SelectTimer = 0x10;
      } else {
        SelectTimer = 0;
      }
      ContinueMenuSelect ^= 1;
    }
    bVar1 = 2;
    do {
      Sprite_Data[bVar1 + 1] = GameOverCursorData[bVar1];
    } Nplus1_TIMES(bVar1);
    Sprite_Data[0] = GameOverCursorY[ContinueMenuSelect];
    return;
  }
  if (ContinueMenuSelect != 0) {
    CompletedWorlds = 0;
    TerminateGame();
    return;
  }
  NumberofLives = 2;
  LevelNumber = ContinueMenuSelect;
  AreaNumber = ContinueMenuSelect;
  CoinTally = ContinueMenuSelect;
  for (int i = 0; i < 12; i++) {
    PlayerScoreDisplay_Or_ScoreAndCoinDisplay[i] = 0;
  }
  Hidden1UpFlag += 1;
  ContinueGame();
  return;
}

static void LoadLuigiPhysics(void);

// SM2MAIN:c241
// Signature: [] -> []
void LoadPhysicsData(void) {
  if (CurrentPlayer == 0) {
    LoadMarioPhysics();
  } else {
    LoadLuigiPhysics();
  }
}


// SM2MAIN:c24a
// Signature: [] -> []
void LoadMarioPhysics(void) {
  // The original game modifies an instruction to "ASL" (restores a bitshift intruction that's there by default)
  PhysicsInstructionOpcode = 0x0e;

  for (int i = 0; i < 7; i++) {
    JumpMForceData[i] = JumpMForceData_Mario[i];
  }
  for (int i = 0; i < 7; i++) {
    FallMForceData[i] = FallMForceData_Mario[i];
  }
  for (int i = 0; i < 3; i++) {
    FrictionData[i] = FrictionData_Mario[i];
  }
}

static void LoadLuigiPhysics(void) {
  // The original game modifies an instruction to "RTS" (early-returns from that subroutine)
  PhysicsInstructionOpcode = 0x60;

  for (int i = 0; i < 7; i++) {
    JumpMForceData[i] = JumpMForceData_Luigi[i];
  }
  for (int i = 0; i < 7; i++) {
    FallMForceData[i] = FallMForceData_Luigi[i];
  }
  for (int i = 0; i < 3; i++) {
    FrictionData[i] = FrictionData_Luigi[i];
  }
}


// Common: LoadAreaPointer
// Common: GetAreaType
// Common: FindAreaPointer


// SM2MAIN:c2c3
// Signature: [] -> []
void GetAreaDataAddrs(void) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;

  bVar3 = GetAreaType(AreaPointer);
  AreaAddrsLOffset = AreaPointer & 0x1f;
  bVar3 = (EnemyAddrHOffsets[bVar3] + AreaAddrsLOffset) * 2;
  EnemyData.hi = EnemyDataAddrs[bVar3 + 1];
  EnemyData.lo = EnemyDataAddrs[bVar3];
  bVar2 = (AreaDataHOffsets[AreaType] + AreaAddrsLOffset) * 2;
  bVar1 = AreaDataAddrs[bVar2];
  AreaData = CONCAT11(AreaDataAddrs[bVar2 + 1], bVar1);
  bVar3 = *AreaData;
  bVar4 = bVar3 & 7;
  ForegroundScenery = bVar4;
  if (bVar4 >= 4) {
    ForegroundScenery = 0;
    BackgroundColorCtrl = bVar4;
  }
  PlayerEntranceCtrl = (bVar3 & 0x38) >> 3;
  GameTimerSetting = bVar3 >> 6;
  bVar3 = AreaData[1];
  TerrainControl = bVar3 & 0xf;
  BackgroundScenery = (bVar3 & 0x30) >> 4;
  AreaStyle = bVar3 >> 6;
  if (AreaStyle == 3) {
    AreaStyle = 0;
    CloudTypeOverride = 3;
  }
  AreaData = CONCAT11(AreaDataAddrs[bVar2 + 1] + (bVar1 >= 0xfe), bVar1 + 2);
  return;
}


// SM2MAIN:c46e
// Signature: [] -> []
void GameMenuRoutine(void) {
  byte bVar1;
  bool bVar2;

  if ((SavedJoypadBits[0] & BUTTON_START) != 0) {
    CompletedWorlds = 0;
    DiskIOTask = 0;
    HardWorldFlag = 0;
    if ((GamesBeatenCount >= 8) && ((SavedJoypadBits[0] & BUTTON_A) != 0)) {
      HardWorldFlag = 1;
    }
    if (DemoTimer != 0) {
      OperMode_Task += 1;
      PatchPlayerNamePal();
      WorldNumber = 0;
      LevelNumber = 0;
      AreaNumber = 0;
      for (int i = 0; i < 12; i++) {
        PlayerScoreDisplay_Or_ScoreAndCoinDisplay[i] = 0;
      }
      return;
    }
    goto ResetTitle;
  }
  if (SavedJoypadBits[0] == BUTTON_SELECT) {
SelectLogic:
    if (DemoTimer == 0) {
      goto ResetTitle;
    }
    DemoTimer = 0x18;
    FrameCounter &= 0xfe;
    if (SelectTimer == 0) {
      SelectTimer = 0x10;
      CurrentPlayer ^= 1;
      DrawMenuCursor();
    }
NullJoypad:
    SavedJoypadBits[0] = 0;
  } else {
    if (DemoTimer != 0) {
      goto NullJoypad;
    }
    SelectTimer = SavedJoypadBits[0];
    bVar2 = DemoEngine();
    if (bVar2) {
      goto ResetTitle;
    }
    if (bVar2) {
      goto SelectLogic;
    }
  }
  GameCoreRoutine();
  if (GameEngineSubroutine != 6) {
    return;
  }
ResetTitle:
  OperMode = 0;
  OperMode_Task = 0;
  IRQUpdateFlag = 0;
  DisableScreenFlag = DisableScreenFlag + 1;
  return;
}


// SM2MAIN:c51b
// Signature: [] -> []
void DrawMenuCursor(void) {
  VRAM_Buffer_AddrCtrl = 0x1c;
  SetupMenuCursor();
  return;
}


// SM2MAIN:c520
// Signature: [] -> []
void SetupMenuCursor(void) {
  MenuCursorTemplate[3] = MenuCursorTiles[CurrentPlayer];
  MenuCursorTemplate[5] = MenuCursorTiles[CurrentPlayer + 1];
  return;
}


// SM2MAIN:c553
// Signature: [] -> [C]
bool DemoEngine(void) {
  byte bVar1;

  if (DemoActionTimer == 0) {
    bVar1 = DemoAction + 1;
    DemoAction += 1;
    DemoActionTimer = DemoActionData[bVar1 + 0x10];
    if (DemoActionTimer == 0) {
      return true;
    }
  }
  DemoActionTimer = DemoActionTimer - 1;
  SavedJoypadBits[0] = DemoActionData[DemoAction - 1];
  return false;
}


// SM2MAIN:c573
// Signature: [] -> []
void ClearBuffersDrawIcon(void) {
  byte bVar1;

  if (OperMode == 0) {
    for (int i = 0; i < 256; i++) {
      VRAM_Page[i] = 0;
      SprObject_X_MoveForce[i] = 0;
    }
    DrawMenuCursor();
    ScreenRoutineTask = ScreenRoutineTask + 1;
    return;
  }
  OperMode_Task = OperMode_Task + 1;
  return;
}


// Common: WriteTopScore


// SM2MAIN:c592
// Signature: [] -> []
void InitializeGame(void) {
  CompletedWorlds = 0;
  HardWorldFlag = 0;
  CurrentPlayer = 0;
  PatchPlayerNamePal();
  SetupMenuCursor();

  // Draw a star for each beaten game on the title screen

  for (int i = 0; i < 12; i++) {
    TitleScreenGfxData[0x33 + i] = i < GamesBeatenCount ? 0xf1 : 0x26;
  }
  for (int i = 12; i < 24; i++) {
    TitleScreenGfxData[0x4d + i-12] = i < GamesBeatenCount ? 0xf1 : 0x26;
  }

  InitializeMemory(0x6f);
  for (int i = 0; i < 0x20; i++) {
    SoundMemory[i] = 0;
  }
  DemoReset();
  return;
}


// SM2MAIN:c5d0
// Signature: [] -> []
void DemoReset(void) {
  DemoTimer = 0x18;
  LoadAreaPointer();
  InitializeArea();
  return;
}


// SM2MAIN:c5db
// Signature: [] -> []
void PrimaryGameSetup(void) {
  FetchNewGameTimerFlag = 1;
  PlayerSize = 1;
  NumberofLives = 2;
  SecondaryGameSetup();
  return;
}


// SM2MAIN:c5ff
// Signature: [] -> []
void PatchPlayerNamePal(void) {
  byte off = PlayerNameOffsets[CurrentPlayer];
  for (int i = 0; i < 5; i++) {
    byte j = (byte)(off-4 + i);
    TopStatusBarLine[i + 3] = PlayerNameData[j];
    ThankYouMessage[i + 13] = PlayerNameData[j];
  }

  for (int i = 0; i < 4; i++) {
    byte j = (byte)(off-4-CurrentPlayer + i);
    PlayerColors[i] = PlayerPaletteData[j];
  }
}


// SM2DATA2+SM2DATA4:c470
// Signature: [X] -> []
void UpsideDownPipe_High(byte param_1) {
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  struct_xc sVar6;
  struct_yr06r07 sVar7;
  byte bStack0000;

  bStack0000 = 1;
  sVar7 = GetPipeHeight(param_1);
  bVar3 = sVar7.r06;
  bVar5 = bStack0000;
  bStack0000 = sVar7.y;
  if (AreaObjectLength[param_1] != 0) {
    sVar6 = FindEmptyEnemySlot();
    bVar4 = sVar6.x;
    if (!sVar6.c) {
      SetupPiranhaPlant(4, bVar4, bVar5);
      cVar1 = bVar3 * 0x10 + Enemy_Y_Position[bVar4];
      bVar2 = cVar1 - 10;
      Enemy_Y_Position[bVar4] = bVar2;
      CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[bVar4] = bVar2;
      BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[bVar4] = cVar1 + 0xe;
      SpriteVarData2[bVar4] = SpriteVarData2[bVar4] + 1;
    }
  }
  bVar5 = RenderUnderPart(VerticalPipeData[bStack0000 + 2], bVar5, bVar3 - 1);
  MetatileBuffer[bVar5] = VerticalPipeData[bStack0000];
  return;
}


// SM2DATA2+SM2DATA4:c475
// Signature: [X] -> []
void UpsideDownPipe_Low(byte param_1) {
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  struct_yr06r07 sVar6;
  struct_xc sVar7;
  byte bStack0000;

  bStack0000 = 4;
  sVar6 = GetPipeHeight(param_1);
  bVar3 = sVar6.r06;
  bVar5 = bStack0000;
  bStack0000 = sVar6.y;
  if (AreaObjectLength[param_1] != 0) {
    sVar7 = FindEmptyEnemySlot();
    bVar4 = sVar7.x;
    if (!sVar7.c) {
      SetupPiranhaPlant(4, bVar4, bVar5);
      cVar1 = bVar3 * 0x10 + Enemy_Y_Position[bVar4];
      bVar2 = cVar1 - 10;
      Enemy_Y_Position[bVar4] = bVar2;
      CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[bVar4] = bVar2;
      BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[bVar4] = cVar1 + 0xe;
      SpriteVarData2[bVar4] = SpriteVarData2[bVar4] + 1;
    }
  }
  bVar5 = RenderUnderPart(VerticalPipeData[bStack0000 + 2], bVar5, bVar3 - 1);
  MetatileBuffer[bVar5] = VerticalPipeData[bStack0000];
  return;
}


// SM2DATA2+SM2DATA4:c4c0
// Signature: [X] -> []
void MoveUpsideDownPiranhaP(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  if ((Enemy_State[param_1] == 0) && (EnemyFrameTimer[param_1] == 0)) {
    if (SpriteVarData2[param_1] == 0) {
      SpriteVarData1[param_1] = NEGATE(SpriteVarData1[param_1]);
      SpriteVarData2[param_1] = SpriteVarData2[param_1] + 1;
    }
    bVar3 = BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1];
    if (SpriteVarData1[param_1] >= 0x80) {
      bVar3 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];
    }
    if ((TimerControl == 0)
        && (bVar1 = Enemy_Y_Position[param_1], bVar2 = SpriteVarData1[param_1],
            Enemy_Y_Position[param_1] = bVar1 + bVar2, (byte)(bVar1 + bVar2) == bVar3)) {
      SpriteVarData2[param_1] = 0;
      EnemyFrameTimer[param_1] = 0x20;
    }
  }
  return;
}


// SM2DATA2+SM2DATA4:c4fe
// Signature: [] -> []
void BlowPlayerAround(void) {
  byte bVar1;

  if ((WindFlag != 0) && (AreaType == 1)) {
    bVar1 = 1;
    if (!(bool)(FrameCounter >> 7)) {
      bVar1 = 3;
    }
    if ((FrameCounter & bVar1) == 0) {
      SprObject_PageLoc[0] += SprObject_X_Position[0] == 0xff;
      Player_X_Scroll += 1;
      SprObject_X_Position[0] = SprObject_X_Position[0] + 1;
    }
  }
  return;
}


// SM2DATA2+SM2DATA4:c550
// Signature: [] -> []
void SimulateWind(void) {
  byte bVar1;
  byte bVar2;

  if (WindFlag != 0) {
    NoiseSoundQueue = 4;
    ModifyLeavesPos();
    bVar1 = 0;
    bVar2 = Enemy_SprDataOffset[6];
    do {
      Sprite_Data[bVar2] = LeavesYPos[bVar1];
      Sprite_Data[bVar2 + 1] = LeavesTile[bVar1];
      Sprite_Data[bVar2 + 2] = 0x41;
      Sprite_Data[bVar2 + 3] = LeavesXPos[bVar1];
      bVar1 += 1;
      bVar2 = bVar2 + 4;
      if (bVar1 == 6) {
        bVar2 = AltOrBlock_SprDataOffset[0];
      }
    } while (bVar1 != 0xc);
  }
  return;
}


// SM2DATA2+SM2DATA4:c5a1
// Signature: [] -> []
void ModifyLeavesPos(void) {
  for (int i = 0; i < 12; i++) {
    LeavesXPos[i] = LeavesXPos[i] + LeavesPosAdder[i] + LeavesPosAdder[i] + CARRY1(LeavesXPos[i], LeavesPosAdder[i]);
    LeavesYPos[i] = LeavesYPos[i] + LeavesPosAdder[i];
  }
}


// SM2DATA2+SM2DATA4:c5be
// Signature: [] -> []
void WindOn(void) {
  WindFlag = 1;
  return;
}


// SM2DATA2+SM2DATA4:c5c2
// Signature: [] -> []
void WindOff(void) {
  WindFlag = 0;
  return;
}


// SM2DATA3:c5fe
// Signature: [] -> []
void ScreenSubsForFinalRoom(void) {
  if (ScreenRoutineTask == 0) {
    InitScreenPalette();
    return;
  }
  if (ScreenRoutineTask == 1) {
    WriteTopStatusLine();
    return;
  }
  if (ScreenRoutineTask == 2) {
    WriteBottomStatusLine();
    return;
  }
  if (ScreenRoutineTask == 3) {
    DrawFinalRoom();
    return;
  }
  if (ScreenRoutineTask == 4) {
    GetAreaPalette();
    return;
  }
  if (ScreenRoutineTask == 5) {
    GetBackgroundColor();
    return;
  }
  if (ScreenRoutineTask == 6) {
    RevealPrincess();
    return;
  }
  jmpengine_overflow(ScreenRoutineTask);
  return;
}


// SM2DATA3:c612
// Signature: [] -> []
void DrawFinalRoom(void) {
  VRAM_Buffer_AddrCtrl = 0x1b;
  IRQUpdateFlag = 0x1b;
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}


// SM2DATA3:c61e
// Signature: [] -> []
void RevealPrincess(void) {
  PrintStatusBarNumbers(0xa2);
  RAM(0x611d) = 0x5f;
  AreaMusicQueue = 1;
  Left_Right_Buttons = 0;
  NameTableSelect = 0;
  IRQUpdateFlag = 0;
  DisableScreenFlag = 0;
  OperMode_Task = OperMode_Task + 1;
  return;
}


// SM2DATA3:c642
// Signature: [] -> []
void PrintVictoryMsgsForWorld8(void) {
  bool bVar1;

  if (SecondaryMsgCounter == 0) {
    if (PrimaryMsgCounter >= 10) {
      WorldEndTimer = 0xc;
      OperMode_Task += 1;
      EraseEndingCounters();
      return;
    }
    if (PrimaryMsgCounter == 2) {
      EventMusicQueue = 4;
    }
    VRAM_Buffer_AddrCtrl = PrimaryMsgCounter + 0xf;
  }
  bVar1 = SecondaryMsgCounter >= 0xfc;
  SecondaryMsgCounter = SecondaryMsgCounter + 4;
  PrimaryMsgCounter = PrimaryMsgCounter + bVar1;
  return;
}


// SM2DATA3:c67a
// Signature: [] -> []
void EraseEndingCounters(void) {
  EndControlCntr = 0;
  BlueColorOfs = 0;
  BlueDelayFlag = 0;
  return;
}


// SM2DATA3:c686
// Signature: [] -> []
void AwardExtraLives(void) {
  if (WorldEndTimer == 0) {
    if (NumberofLives >= 0x80) {
      OperMode_Task += 1;
      EraseEndingCounters();
      return;
    }
    if (SelectTimer == 0) {
      SelectTimer = 0x30;
      Square2SoundQueue = 0x40;
      NumberofLives -= 1;
      DigitModifier[1] = 1;
      EndAreaPoints();
      return;
    }
  }
  return;
}


// SM2DATA3:c6ca
// Signature: [] -> []
void FadeToBlue(void) {
  byte bVar1;
  byte bVar2;

  EndControlCntr += 1;
  if (BlueDelayFlag == 0) {
    if (EndControlCntr != 0) {
      return;
    }
    BlueDelayFlag = 1;
  } else if ((EndControlCntr & 0xf) != 0) {
    return;
  }
  bVar2 = 0x13;
  do {
    VRAM_Buffer1[bVar2] = BlueTransPalette[bVar2];
    bVar1 = BlueColorOfs;
  } Nplus1_TIMES(bVar2);
  bVar2 = 0xc;
  do {
    VRAM_Buffer1[bVar2 + 3] = BlueTints[bVar1];
    bVar2 -= 4;
  } while (bVar2 < 0x80);
  if ((byte)(BlueColorOfs + 1) == 4) {
    OperMode_Task += 1;
  }
  BlueColorOfs = BlueColorOfs + 1;
  return;
}


// SM2DATA3:c710
// Signature: [] -> []
void EraseLivesLines(void) {
  byte bVar1;

  bVar1 = 8;
  do {
    VRAM_Buffer1[bVar1] = TwoBlankRows[bVar1];
  } Nplus1_TIMES(bVar1);
  OperMode_Task += 1;
  EraseEndingCounters();
  MushroomRetDelay = 0x60;
  return;
}


// SM2DATA3:c727
// Signature: [] -> []
void RunMushroomRetainers(void) {
  MushroomRetainersForW8();
  if (Block_Buffer_2[56] == 0) {
    if (HardWorldFlag != 0) {
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
        if (WorldNumber >= 8) {
          WorldNumber = 8;
        }
        LoadAreaPointer();
        FetchNewGameTimerFlag = FetchNewGameTimerFlag + 1;
        OperMode = 1;
        return;
      }
      CompletedWorlds = 0;
      OperMode = 0;
      AttractModeSubs();
      return;
    }
    OperMode_Task += 1;
  }
  return;
}


// SM2DATA3:c738
// Signature: [] -> []
void EndingDiskRoutines(void) {
  if (DiskIOTask == 0) {
    DiskScreen();
    return;
  }
  if (DiskIOTask == 1) {
    UpdateGamesBeaten();
    return;
  }
  if (DiskIOTask == 2) {
    WaitForEject();
    return;
  }
  if (DiskIOTask == 3) {
    WaitForReinsert();
    return;
  }
  if (DiskIOTask == 4) {
    ResetDiskVars();
    return;
  }
  jmpengine_overflow(DiskIOTask);
  return;
}


// SM2DATA3:c7bd
// Signature: [] -> []
void MushroomRetainersForW8(void) {
  byte bVar1;
  byte bStack0000;

  if (MushroomRetDelay != 0) {
    MushroomRetDelay = MushroomRetDelay - 1;
    return;
  }
  MoveSpritesOffscreen();
  if (BlueColorOfs == 7) {
    if (((EndControlCntr & 0x1f) == 0) && (BlueDelayFlag += 1, BlueDelayFlag >= 0xb)) {
      BlueDelayFlag = 4;
    }
  } else if ((EndControlCntr & 0x1f) == 0) {
    BlueColorOfs += 1;
    Square2SoundQueue = 1;
  }
  bVar1 = BlueColorOfs;
  EndControlCntr += 1;
  bStack0000 = WorldNumber;
  do {
    if ((BlueDelayFlag < 4)
        || (FlashMRSpriteDataOfs[(byte)((BlueDelayFlag - 4) - (BlueDelayFlag < 4))] != MRSpriteDataOfs[BlueColorOfs])) {
      Enemy_SprDataOffset[0] = MRSpriteDataOfs[BlueColorOfs];
      Enemy_ID[0] = 0x35;
      Enemy_Y_Position[0] = MRetainerYPos[BlueColorOfs];
      Enemy_Rel_XPos = MRetainerXPos[BlueColorOfs];
      WorldNumber = 0;
      ObjectOffset = 0;
      EnemyGfxHandler(0);
    }
  } N_TIMES(BlueColorOfs);
  BlueColorOfs = bVar1;
  WorldNumber = bStack0000;
  Enemy_SprDataOffset[0] = 0x30;
  Enemy_Y_Position[0] = 0xb8;
  return;
}


// SM2DATA3:c858
// Signature: [] -> []
void WriteNameToVictoryMsg(void) {
  ScreenRoutineTask = 0;
  if (CurrentPlayer == 0) {
    for (int i = 0; i < 5; i++) {
      ThankYouMessageFinal[i + 0xd] = EndPlayerName_Mario[i];
      HurrahMsg[i + 0xe] = EndPlayerName_Mario[i];
    }
  } else {
    for (int i = 0; i < 5; i++) {
      ThankYouMessageFinal[i + 0xd] = EndPlayerName_Luigi[i];
      HurrahMsg[i + 0xe] = EndPlayerName_Luigi[i];
    }
  }
}


// SM2DATA4:c2c3
// Signature: [] -> []
void AltHard_GetAreaDataAddrs(void) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;

  bVar3 = GetAreaType(AreaPointer);
  AreaAddrsLOffset = AreaPointer & 0x1f;
  bVar3 = (AltHard_EnemyAddrHOffsets[bVar3] + AreaAddrsLOffset) * 2;
  EnemyData.hi = AltHard_EnemyDataAddrs[bVar3 + 1];
  EnemyData.lo = AltHard_EnemyDataAddrs[bVar3];
  bVar2 = (AltHard_AreaDataHOffsets[AreaType] + AreaAddrsLOffset) * 2;
  bVar1 = AltHard_AreaDataAddrs[bVar2];
  AreaData = CONCAT11(AltHard_AreaDataAddrs[bVar2 + 1], bVar1);
  bVar3 = *AreaData;
  bVar4 = bVar3 & 7;
  ForegroundScenery = bVar4;
  if (bVar4 >= 4) {
    ForegroundScenery = 0;
    BackgroundColorCtrl = bVar4;
  }
  PlayerEntranceCtrl = (bVar3 & 0x38) >> 3;
  GameTimerSetting = bVar3 >> 6;
  bVar3 = AreaData[1];
  TerrainControl = bVar3 & 0xf;
  BackgroundScenery = (bVar3 & 0x30) >> 4;
  AreaStyle = bVar3 >> 6;
  if (AreaStyle == 3) {
    AreaStyle = 0;
    CloudTypeOverride = 3;
  }
  AreaData = CONCAT11(AltHard_AreaDataAddrs[bVar2 + 1] + (bVar1 >= 0xfe), bVar1 + 2);
  return;
}


// SM2DATA4:c3d6
// Signature: [] -> []
void ChangeHalfwayPages(void) {
  for (int i = 0; i < 8; i++) {
    HalfwayPageNybbles[i] = AtoDHalfwayPages[i];
  }
}
