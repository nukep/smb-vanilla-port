#include "smb2j.h"

// SM2MAIN:3000
// Signature: [] -> []
void FUN_3000(void) {
  if (FileListNumber != 3) {
    GetAreaDataAddrs();
    return;
  }
  AltHard_GetAreaDataAddrs();
  return;
}

// SM2MAIN:300f
// Signature: [A, r00] -> []
void FUN_300f(byte param_1, byte param_2) {
  if (param_1 == 0) {
    AttractModeSubs();
    return;
  }
  if (param_1 == 1) {
    GameModeSubs();
    return;
  }
  if (param_1 == 2) {
    VictoryModeMain(param_2);
    return;
  }
  if (param_1 == 3) {
    GameOverSubs();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}

// SM2MAIN:3023
// Signature: [A, r00] -> []
void FUN_3023(byte param_1, byte param_2) {
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
    EndWorld1Thru7();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}

// SM2MAIN:303f
// Signature: [A, r00] -> []
void FUN_303f(byte param_1, byte param_2) {
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

// SM2MAIN:307b
// Signature: [A] -> []
void FUN_307b(byte param_1) {
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

// SM2MAIN:30bf
// Signature: [A] -> []
void FUN_30bf(byte param_1) {
  if (param_1 == 0) {
    SetupGameOver();
    return;
  }
  if (param_1 == 1) {
    ScreenRoutines();
    return;
  }
  if (param_1 == 2) {
    RunGameOver();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}

// SM2MAIN:30cf
// Signature: [A] -> []
void FUN_30cf(byte param_1) {
  if (param_1 == 0) {
    IncrementColumnPos();
    return;
  }
  if (param_1 == 1) {
    RenderAreaGraphics();
    return;
  }
  if (param_1 == 2) {
    RenderAreaGraphics();
    return;
  }
  if (param_1 == 3) {
    AreaParserCore();
    return;
  }
  if (param_1 == 4) {
    IncrementColumnPos();
    return;
  }
  if (param_1 == 5) {
    RenderAreaGraphics();
    return;
  }
  if (param_1 == 6) {
    RenderAreaGraphics();
    return;
  }
  if (param_1 == 7) {
    AreaParserCore();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}

// SM2MAIN:30f3
// Signature: [A, X, r00] -> []
void FUN_30f3(byte param_1, byte param_2, byte param_3) {
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

// SM2MAIN:31d3
// Signature: [A, X] -> []
void FUN_31d3(byte param_1, byte param_2) {
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

// SM2MAIN:31e3
// Signature: [A] -> []
void FUN_31e3(byte param_1) {
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

// SM2MAIN:31fb
// Signature: [A] -> []
void FUN_31fb(byte param_1) {
  if (param_1 == 0) {
    Entrance_GameTimerSetup(0x6f);
    return;
  }
  if (param_1 == 1) {
    Vine_AutoClimb();
    return;
  }
  if (param_1 == 2) {
    SideExitPipeEntry();
    return;
  }
  if (param_1 == 3) {
    VerticalPipeEntry();
    return;
  }
  if (param_1 == 4) {
    FlagpoleSlide();
    return;
  }
  if (param_1 == 5) {
    PlayerEndLevel();
    return;
  }
  if (param_1 == 6) {
    PlayerLoseLife();
    return;
  }
  if (param_1 == 7) {
    PlayerEntrance();
    return;
  }
  if (param_1 == 8) {
    PlayerCtrlRoutine();
    return;
  }
  if (param_1 == 9) {
    PlayerChangeSize();
    return;
  }
  if (param_1 == 10) {
    PlayerInjuryBlink();
    return;
  }
  if (param_1 == 0xb) {
    PlayerDeath();
    return;
  }
  if (param_1 == 0xc) {
    PlayerFireFlower();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}

// SM2MAIN:3233
// Signature: [A] -> []
void FUN_3233(byte param_1) {
  if (param_1 == 0) {
    OnGroundStateSub();
    return;
  }
  if (param_1 == 1) {
    JumpSwimSub();
    return;
  }
  if (param_1 == 2) {
    FallingSub();
    return;
  }
  if (param_1 == 3) {
    ClimbingSub();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}

// SM2MAIN:3247
// Signature: [A, X] -> []
void FUN_3247(byte param_1, byte param_2) {
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

// SM2MAIN:327f
// Signature: [A, X] -> []
void FUN_327f(byte param_1, byte param_2) {
  if (param_1 == 0) {
    InitNormalEnemy(param_2);
    return;
  }
  if (param_1 == 1) {
    InitNormalEnemy(param_2);
    return;
  }
  if (param_1 == 2) {
    InitNormalEnemy(param_2);
    return;
  }
  if (param_1 == 3) {
    InitRedKoopa(param_2);
    return;
  }
  if (param_1 == 4) {
    InitPiranhaPlant(param_2);
    return;
  }
  if (param_1 == 5) {
    InitHammerBro(param_2);
    return;
  }
  if (param_1 == 6) {
    InitGoomba(param_2);
    return;
  }
  if (param_1 == 7) {
    InitBloober(param_2);
    return;
  }
  if (param_1 == 8) {
    InitBulletBill(param_2);
    return;
  }
  if (param_1 == 9) {
    NoInitCode();
    return;
  }
  if (param_1 == 10) {
    InitCheepCheep(param_2);
    return;
  }
  if (param_1 == 0xb) {
    InitCheepCheep(param_2);
    return;
  }
  if (param_1 == 0xc) {
    InitPodoboo(param_2);
    return;
  }
  if (param_1 == 0xd) {
    InitPiranhaPlant(param_2);
    return;
  }
  if (param_1 == 0xe) {
    InitJumpGPTroopa(param_2);
    return;
  }
  if (param_1 == 0xf) {
    InitRedPTroopa(param_2, false);
    return;
  }
  if (param_1 == 0x10) {
    InitHorizFlySwimEnemy(param_2);
    return;
  }
  if (param_1 == 0x11) {
    InitLakitu(param_2);
    return;
  }
  if (param_1 == 0x12) {
    InitEnemyFrenzy(param_2);
    return;
  }
  if (param_1 == 0x13) {
    NoInitCode();
    return;
  }
  if (param_1 == 0x14) {
    InitEnemyFrenzy(param_2);
    return;
  }
  if (param_1 == 0x15) {
    InitEnemyFrenzy(param_2);
    return;
  }
  if (param_1 == 0x16) {
    InitEnemyFrenzy(param_2);
    return;
  }
  if (param_1 == 0x17) {
    InitEnemyFrenzy(param_2);
    return;
  }
  if (param_1 == 0x18) {
    EndFrenzy(param_2);
    return;
  }
  if (param_1 == 0x19) {
    NoInitCode();
    return;
  }
  if (param_1 == 0x1a) {
    NoInitCode();
    return;
  }
  if (param_1 == 0x1b) {
    InitShortFirebar(param_2);
    return;
  }
  if (param_1 == 0x1c) {
    InitShortFirebar(param_2);
    return;
  }
  if (param_1 == 0x1d) {
    InitShortFirebar(param_2);
    return;
  }
  if (param_1 == 0x1e) {
    InitShortFirebar(param_2);
    return;
  }
  if (param_1 == 0x1f) {
    InitLongFirebar(param_2);
    return;
  }
  if (param_1 == 0x20) {
    NoInitCode();
    return;
  }
  if (param_1 == 0x21) {
    NoInitCode();
    return;
  }
  if (param_1 == 0x22) {
    NoInitCode();
    return;
  }
  if (param_1 == 0x23) {
    NoInitCode();
    return;
  }
  if (param_1 == 0x24) {
    InitBalPlatform(param_2);
    return;
  }
  if (param_1 == 0x25) {
    InitVertPlatform(param_2);
    return;
  }
  if (param_1 == 0x26) {
    LargeLiftUp(param_2);
    return;
  }
  if (param_1 == 0x27) {
    LargeLiftDown(param_2);
    return;
  }
  if (param_1 == 0x28) {
    InitHoriPlatform(param_2);
    return;
  }
  if (param_1 == 0x29) {
    InitDropPlatform(param_2);
    return;
  }
  if (param_1 == 0x2a) {
    InitHoriPlatform(param_2);
    return;
  }
  if (param_1 == 0x2b) {
    PlatLiftUp(param_2);
    return;
  }
  if (param_1 == 0x2c) {
    PlatLiftDown(param_2);
    return;
  }
  if (param_1 == 0x2d) {
    InitBowser(param_2);
    return;
  }
  if (param_1 == 0x2e) {
    PwrUpJmp();
    return;
  }
  if (param_1 == 0x2f) {
    Setup_Vine(param_2, 0x60);
    return;
  }
  if (param_1 == 0x30) {
    NoInitCode();
    return;
  }
  if (param_1 == 0x31) {
    NoInitCode();
    return;
  }
  if (param_1 == 0x32) {
    NoInitCode();
    return;
  }
  if (param_1 == 0x33) {
    NoInitCode();
    return;
  }
  if (param_1 == 0x34) {
    NoInitCode();
    return;
  }
  if (param_1 == 0x35) {
    InitRetainerObj(param_2);
    return;
  }
  if (param_1 == 0x36) {
    EndOfEnemyInitCode();
    return;
  }
  jmpengine_overflow(param_1);
  return;
}

// SM2MAIN:335f
// Signature: [A, X] -> []
void FUN_335f(byte param_1, byte param_2) {
  if (param_1 == 0) {
    LakituAndSpinyHandler(param_2);
    return;
  }
  if (param_1 == 1) {
    NoFrenzyCode();
    return;
  }
  if (param_1 == 2) {
    InitFlyingCheepCheep(param_2);
    return;
  }
  if (param_1 == 3) {
    InitBowserFlame(param_2);
    return;
  }
  if (param_1 == 4) {
    InitFireworks(param_2);
    return;
  }
  if (param_1 == 5) {
    BulletBillCheepCheep(param_2);
    return;
  }
  jmpengine_overflow(param_1);
  return;
}

// SM2MAIN:337b
// Signature: [A, X] -> [X]
byte FUN_337b(byte param_1, byte param_2) {
  byte bVar1;

  if (param_1 == 0) {
    bVar1 = RunNormalEnemies(param_2);
    return bVar1;
  }
  if (param_1 == 1) {
    bVar1 = RunBowserFlame(param_2);
    return bVar1;
  }
  if (param_1 == 2) {
    bVar1 = RunFireworks(param_2);
    return bVar1;
  }
  if (param_1 == 3) {
    NoRunCode();
    return param_2;
  }
  if (param_1 == 4) {
    NoRunCode();
    return param_2;
  }
  if (param_1 == 5) {
    NoRunCode();
    return param_2;
  }
  if (param_1 == 6) {
    NoRunCode();
    return param_2;
  }
  if (param_1 == 7) {
    bVar1 = RunFirebarObj(param_2);
    return bVar1;
  }
  if (param_1 == 8) {
    bVar1 = RunFirebarObj(param_2);
    return bVar1;
  }
  if (param_1 == 9) {
    bVar1 = RunFirebarObj(param_2);
    return bVar1;
  }
  if (param_1 == 10) {
    bVar1 = RunFirebarObj(param_2);
    return bVar1;
  }
  if (param_1 == 0xb) {
    bVar1 = RunFirebarObj(param_2);
    return bVar1;
  }
  if (param_1 == 0xc) {
    bVar1 = RunFirebarObj(param_2);
    return bVar1;
  }
  if (param_1 == 0xd) {
    bVar1 = RunFirebarObj(param_2);
    return bVar1;
  }
  if (param_1 == 0xe) {
    bVar1 = RunFirebarObj(param_2);
    return bVar1;
  }
  if (param_1 == 0xf) {
    NoRunCode();
    return param_2;
  }
  if (param_1 == 0x10) {
    bVar1 = RunLargePlatform(param_2);
    return bVar1;
  }
  if (param_1 == 0x11) {
    bVar1 = RunLargePlatform(param_2);
    return bVar1;
  }
  if (param_1 == 0x12) {
    bVar1 = RunLargePlatform(param_2);
    return bVar1;
  }
  if (param_1 == 0x13) {
    bVar1 = RunLargePlatform(param_2);
    return bVar1;
  }
  if (param_1 == 0x14) {
    bVar1 = RunLargePlatform(param_2);
    return bVar1;
  }
  if (param_1 == 0x15) {
    bVar1 = RunLargePlatform(param_2);
    return bVar1;
  }
  if (param_1 == 0x16) {
    bVar1 = RunLargePlatform(param_2);
    return bVar1;
  }
  if (param_1 == 0x17) {
    bVar1 = RunSmallPlatform(param_2);
    return bVar1;
  }
  if (param_1 == 0x18) {
    bVar1 = RunSmallPlatform(param_2);
    return bVar1;
  }
  if (param_1 == 0x19) {
    bVar1 = RunBowser(param_2);
    return bVar1;
  }
  if (param_1 == 0x1a) {
    bVar1 = PowerUpObjHandler();
    return bVar1;
  }
  if (param_1 == 0x1b) {
    bVar1 = VineObjectHandler(param_2);
    return bVar1;
  }
  if (param_1 == 0x1c) {
    NoRunCode();
    return param_2;
  }
  if (param_1 == 0x1d) {
    bVar1 = RunStarFlagObj(param_2);
    return bVar1;
  }
  if (param_1 == 0x1e) {
    bVar1 = JumpspringHandler(param_2);
    return bVar1;
  }
  if (param_1 == 0x1f) {
    NoRunCode();
    return param_2;
  }
  if (param_1 == 0x20) {
    WarpZoneObject(param_2);
    return param_2;
  }
  if (param_1 == 0x21) {
    bVar1 = RunRetainerObj(param_2);
    return bVar1;
  }
  jmpengine_overflow(param_1);
  return param_2;
}

// SM2MAIN:3407
// Signature: [A, X] -> [X]
byte FUN_3407(byte param_1, byte param_2) {
  byte bVar1;

  if (param_1 == 0) {
    bVar1 = MoveNormalEnemy(param_2);
    return bVar1;
  }
  if (param_1 == 1) {
    bVar1 = MoveNormalEnemy(param_2);
    return bVar1;
  }
  if (param_1 == 2) {
    bVar1 = MoveNormalEnemy(param_2);
    return bVar1;
  }
  if (param_1 == 3) {
    bVar1 = MoveNormalEnemy(param_2);
    return bVar1;
  }
  if (param_1 == 4) {
    MoveUpsideDownPiranhaP(param_2);
    return param_2;
  }
  if (param_1 == 5) {
    bVar1 = ProcHammerBro(param_2);
    return bVar1;
  }
  if (param_1 == 6) {
    bVar1 = MoveNormalEnemy(param_2);
    return bVar1;
  }
  if (param_1 == 7) {
    bVar1 = MoveBloober(param_2, false);
    return bVar1;
  }
  if (param_1 == 8) {
    bVar1 = MoveBulletBill(param_2);
    return bVar1;
  }
  if (param_1 == 9) {
    NoMoveCode();
    return param_2;
  }
  if (param_1 == 10) {
    bVar1 = MoveSwimmingCheepCheep(param_2);
    return bVar1;
  }
  if (param_1 == 0xb) {
    bVar1 = MoveSwimmingCheepCheep(param_2);
    return bVar1;
  }
  if (param_1 == 0xc) {
    bVar1 = MovePodoboo(param_2);
    return bVar1;
  }
  if (param_1 == 0xd) {
    MovePiranhaPlant(param_2);
    return param_2;
  }
  if (param_1 == 0xe) {
    bVar1 = MoveJumpingEnemy(param_2);
    return bVar1;
  }
  if (param_1 == 0xf) {
    bVar1 = ProcMoveRedPTroopa(param_2);
    return bVar1;
  }
  if (param_1 == 0x10) {
    bVar1 = MoveFlyGreenPTroopa(param_2);
    return bVar1;
  }
  if (param_1 == 0x11) {
    bVar1 = MoveLakitu(param_2);
    return bVar1;
  }
  if (param_1 == 0x12) {
    bVar1 = MoveNormalEnemy(param_2);
    return bVar1;
  }
  if (param_1 == 0x13) {
    NoMoveCode();
    return param_2;
  }
  if (param_1 == 0x14) {
    bVar1 = MoveFlyingCheepCheep(param_2);
    return bVar1;
  }
  jmpengine_overflow(param_1);
  return param_2;
}

// SM2MAIN:345f
// Signature: [A, X] -> [X]
byte FUN_345f(byte param_1, byte param_2) {
  byte bVar1;

  if (param_1 == 0) {
    bVar1 = BalancePlatform(param_2);
    return bVar1;
  }
  if (param_1 == 1) {
    bVar1 = YMovingPlatform(param_2);
    return bVar1;
  }
  if (param_1 == 2) {
    MoveLargeLiftPlat(param_2);
    return param_2;
  }
  if (param_1 == 3) {
    MoveLargeLiftPlat(param_2);
    return param_2;
  }
  if (param_1 == 4) {
    bVar1 = XMovingPlatform(param_2);
    return bVar1;
  }
  if (param_1 == 5) {
    bVar1 = DropPlatform(param_2);
    return bVar1;
  }
  if (param_1 == 6) {
    bVar1 = RightPlatform(param_2);
    return bVar1;
  }
  jmpengine_overflow(param_1);
  return param_2;
}

// SM2MAIN:347f
// Signature: [A, X] -> [X]
byte FUN_347f(byte param_1, byte param_2) {
  byte bVar1;

  if (param_1 == 0) {
    StarFlagExit();
    return param_2;
  }
  if (param_1 == 1) {
    GameTimerFireworks(param_2);
    return param_2;
  }
  if (param_1 == 2) {
    bVar1 = AwardGameTimerPoints(param_2);
    return bVar1;
  }
  if (param_1 == 3) {
    bVar1 = RaiseFlagSetoffFWorks(param_2);
    return bVar1;
  }
  if (param_1 == 4) {
    bVar1 = DelayToAreaEnd(param_2);
    return bVar1;
  }
  jmpengine_overflow(param_1);
  return param_2;
}

// SM2MAIN:3497
// Signature: [A] -> []
void FUN_3497(byte param_1) {
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

// SM2MAIN:34b3
// Signature: [A] -> []
void FUN_34b3(byte param_1) {
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

// SM2MAIN:34cb
// Signature: [A] -> []
void FUN_34cb(byte param_1) {
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

// SM2MAIN:34e3
// Signature: [A] -> []
void FUN_34e3(byte param_1) {
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

// SM2MAIN:34fb
// Signature: [A] -> []
void FUN_34fb(byte param_1) {
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

// SM2MAIN:61e9
// Signature: [] -> []
void PauseRoutine(void) {
  if ((OperMode == 2) || ((OperMode == 1 && (OperMode_Task == 4)))) {
    if (GamePauseTimer != 0) {
      GamePauseTimer = GamePauseTimer - 1;
      return;
    }
    if ((SavedJoypadBits[0] & 0x10) == 0) {
      GamePauseStatus &= 0x7f;
    } else if ((GamePauseStatus & 0x80) == 0) {
      GamePauseTimer = 0x2b;
      PauseSoundQueue = GamePauseStatus + 1;
      GamePauseStatus = GamePauseStatus ^ 1 | 0x80;
    }
  }
  return;
}

// SM2MAIN:622d
// Signature: [] -> []
void SpriteShuffler(void) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  bVar2 = 0xe;
  do {
    bVar3 = PlayerOrSprDataOffset[bVar2];
    if (0x27 < bVar3) {
      bVar1 = bVar3 + SprShuffleAmt[SprShuffleAmtOffset];
      if (CARRY1(bVar3, SprShuffleAmt[SprShuffleAmtOffset])) {
        bVar1 += 0x28;
      }
      PlayerOrSprDataOffset[bVar2] = bVar1;
    }
    bVar2 -= 1;
  } while (bVar2 < 0x80);
  SprShuffleAmtOffset += 1;
  if (SprShuffleAmtOffset == 3) {
    SprShuffleAmtOffset = 0;
  }
  bVar2 = 8;
  bVar3 = 2;
  do {
    bVar1 = Enemy_SprDataOffset[bVar3 + 4];
    FBall_SprDataOffset[bVar2] = bVar1;
    FBall_SprDataOffset[bVar2 + 1] = bVar1 + 8;
    Misc_SprDataOffset[bVar2] = bVar1 + 0x10;
    bVar2 -= 3;
    bVar3 -= 1;
  } while (bVar3 < 0x80);
  return;
}

// SM2MAIN:6279
// Signature: [] -> []
void OperModeExecutionTree(void) {
  byte in_r00 = 0;

  FUN_300f(OperMode, in_r00);
  return;
}

// SM2MAIN:6287
// Signature: [] -> []
void MoveAllSpritesOffscreen(void) {
  byte bVar1;

  bVar1 = 0;
  do {
    Sprite_Data[bVar1] = 0xf8;
    bVar1 += 4;
  } while (bVar1 != 0);
  return;
}

// SM2MAIN:628a
// Signature: [] -> []
void MoveSpritesOffscreen(void) {
  byte bVar1;

  bVar1 = 4;
  do {
    Sprite_Data[bVar1] = 0xf8;
    bVar1 += 4;
  } while (bVar1 != 0);
  return;
}

// SM2MAIN:6298
// Signature: [r00] -> []
void VictoryModeMain(byte param_1) {
  VictoryModeSubroutines(param_1);
  if (OperMode_Task != 0) {
    if ((WorldNumber == 7) && ((OperMode_Task == 5 || (OperMode_Task == 0xd)))) {
      return;
    }
    ObjectOffset = 0;
    EnemiesAndLoopsCore(0);
  }
  RelativePlayerPosition();
  PlayerGfxHandler();
  return;
}

// SM2MAIN:62bc
// Signature: [r00] -> []
void VictoryModeSubroutines(byte param_1) {
  if (WorldNumber != 7) {
    FUN_3023(OperMode_Task, param_1);
    return;
  }
  FUN_303f(OperMode_Task, param_1);
  return;
}

// SM2MAIN:62ff
// Signature: [] -> []
void SetupVictoryMode(void) {
  VictoryDestPageLoc = ScreenRight_PageLoc + 1;
  CompletedWorlds = WorldBits[WorldNumber] | CompletedWorlds;
  if ((HardWorldFlag != 0) && (2 < WorldNumber)) {
    WorldNumber = 7;
  }
  EventMusicQueue = 8;
  OperMode_Task = OperMode_Task + 1;
  return;
}

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

// SM2MAIN:6334
// Signature: [] -> []
void PlayerVictoryWalk(void) {
  bool bVar1;
  byte bVar2;

  bVar2 = 0;
  VictoryWalkControl = 0;
  if ((SprObject_PageLoc[0] != VictoryDestPageLoc)
      || (SprObject_X_Position[0] < 0x60)) {
    VictoryWalkControl = 1;
    bVar2 = 1;
  }
  AutoControlPlayer(bVar2);
  if (ScreenEdgeOrLeft_PageLoc[0] != VictoryDestPageLoc) {
    bVar1 = 0x7f < ScrollFractional;
    ScrollFractional = ScrollFractional + 0x80;
    ScrollScreen(bVar1 + 1);
    UpdScrollVar();
    VictoryWalkControl += 1;
  }
  if (VictoryWalkControl != 0) {
    return;
  }
  OperMode_Task = OperMode_Task + 1;
  return;
}

// SM2MAIN:636d
// Signature: [] -> []
void PrintVictoryMessages(void) {
  bool bVar1;

  if ((SecondaryMsgCounter == 0)
      && ((PrimaryMsgCounter == 0 || ((PrimaryMsgCounter < 8 && (PrimaryMsgCounter != 0)))))) {
    if (PrimaryMsgCounter != 0) {
      bVar1 = 2 < PrimaryMsgCounter;
      if (bVar1) {
        goto SetEndTimer;
      }
      if (1 < PrimaryMsgCounter) {
        goto IncMsgCounter;
      }
    }
    VRAM_Buffer_AddrCtrl = PrimaryMsgCounter + 0xc;
  }
IncMsgCounter:
  PrimaryMsgCounter += 0xfb < SecondaryMsgCounter;
  bVar1 = 5 < PrimaryMsgCounter;
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
    if ((byte)(GameTimerDisplaySMB2J[0] | GameTimerDisplaySMB2J[1] | GameTimerDisplaySMB2J[2]) == 0) {
      SelectTimer = 0x30;
      WorldEndTimer = 6;
      OperMode_Task += 1;
    }
  }
  return;
}

// SM2MAIN:63d2
// Signature: [] -> []
void EndWorld1Thru7(void) {
  if (WorldEndTimer == 0) {
    AreaNumber = 0;
    LevelNumber = 0;
    OperMode_Task = 0;
    WorldNumber += 1;
    if (7 < WorldNumber) {
      WorldNumber = 8;
    }
    LoadAreaPointer();
    FetchNewGameTimerFlag += 1;
    OperMode = 1;
  }
  return;
}

// SM2MAIN:6421
// Signature: [X] -> [X]
byte FloateyNumbersRoutine(byte param_1) {
  bool bVar1;
  byte bVar2;
  byte bVar3;
  bool bVar4;

  bVar2 = FloateyNum_Control[param_1];
  if (bVar2 == 0) {
    return param_1;
  }
  if (10 < bVar2) {
    bVar2 = 0xb;
    FloateyNum_Control[param_1] = 0xb;
  }
  bVar3 = FloateyNum_Timer[param_1];
  if (bVar3 == 0) {
    FloateyNum_Control[param_1] = 0;
    return param_1;
  }
  FloateyNum_Timer[param_1] = FloateyNum_Timer[param_1] - 1;
  if (bVar3 == 0x2b) {
    if (bVar2 == 0xb) {
      NumberofLives += 1;
      Square2SoundQueue = 0x40;
    }
    DigitModifier[ScoreUpdateData[bVar2] >> 4] = ScoreUpdateData[bVar2] & 0xf;
    param_1 = AddToScore();
  }
  bVar3 = Enemy_SprDataOffset[param_1];
  bVar2 = Enemy_ID[param_1];
  if (((bVar2 != 0x12) && (bVar2 != 0xd))
      && ((bVar2 == 5 || (((bVar2 != 10 && (bVar2 != 0xb)) && ((8 < bVar2 || (Enemy_State[param_1] < 2)))))))) {
    bVar3 = AltOrBlock_SprDataOffset[SprDataOffset_Ctrl];
    param_1 = ObjectOffset;
  }
  bVar2 = FloateyNum_Y_Pos[param_1];
  bVar4 = 0x17 < bVar2;
  if (bVar4) {
    bVar1 = !bVar4;
    bVar4 = 0x17 < bVar2 || !bVar4 && 1 < bVar2;
    FloateyNum_Y_Pos[param_1] = (bVar2 - 1) - bVar1;
  }
  DumpTwoSpr((FloateyNum_Y_Pos[param_1] - 8) - !bVar4, bVar3);
  bVar2 = FloateyNum_X_Pos[param_1];
  Sprite_Data[bVar3 + 3] = bVar2;
  Sprite_Data[bVar3 + 7] = bVar2 + 8;
  Sprite_Data[bVar3 + 2] = 2;
  Sprite_Data[bVar3 + 6] = 2;
  bVar2 = FloateyNum_Control[param_1];
  Sprite_Data[bVar3 + 1] = FloateyNumTileData[(byte)(bVar2 << 1)];
  Sprite_Data[bVar3 + 5] = FloateyNumTileData[(byte)(bVar2 << 1) + 1];
  return ObjectOffset;
}

// SM2MAIN:64c5
// Signature: [] -> []
void ScreenRoutines(void) {
  FUN_307b(ScreenRoutineTask);
  return;
}

// SM2MAIN:64eb
// Signature: [] -> []
void InitScreen(void) {
  MoveAllSpritesOffscreen();
  InitializeNameTables();
  if (OperMode != 0) {
    VRAM_Buffer_AddrCtrl = 3;
  }
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}

// SM2MAIN:64f6
// Signature: [] -> []
void InitScreenPalette(void) {
  VRAM_Buffer_AddrCtrl = 3;
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}

// SM2MAIN:64fb
// Signature: [] -> []
void SetupIntermediate(void) {
  byte bVar1;
  byte bStack0000;

  bVar1 = PlayerStatus;
  bStack0000 = BackgroundColorCtrl;
  PlayerStatus = 0;
  BackgroundColorCtrl = 2;
  GetPlayerColors();
  PlayerStatus = bVar1;
  BackgroundColorCtrl = bStack0000;
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}

// SM2MAIN:651f
// Signature: [] -> []
void GetAreaPalette(void) {
  VRAM_Buffer_AddrCtrl = AreaPalette[AreaType];
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}

// SM2MAIN:653f
// Signature: [] -> []
void GetBackgroundColor(void) {
  if (BackgroundColorCtrl != 0) {
    VRAM_Buffer_AddrCtrl = BGColorCtrl_Addr[BackgroundColorCtrl - 4];
  }
  ScreenRoutineTask += 1;
  GetPlayerColors();
  return;
}

// SM2MAIN:654d
// Signature: [] -> [X]
byte GetPlayerColors(void) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  bVar3 = 0;
  if (PlayerStatus == 2) {
    bVar3 = 4;
  }
  bVar1 = 3;
  bVar2 = VRAM_Buffer1_Offset;
  do {
    VRAM_Buffer1[bVar2 + 3] = PlayerColors[bVar3];
    bVar3 += 1;
    bVar2 += 1;
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  bVar1 = VRAM_Buffer1_Offset;
  bVar3 = BackgroundColorCtrl;
  if (BackgroundColorCtrl == 0) {
    bVar3 = AreaType;
  }
  VRAM_Buffer1[VRAM_Buffer1_Offset + 3] = BackgroundColors[bVar3];
  VRAM_Buffer1[VRAM_Buffer1_Offset] = 0x3f;
  VRAM_Buffer1[VRAM_Buffer1_Offset + 1] = 0x10;
  VRAM_Buffer1[VRAM_Buffer1_Offset + 2] = 4;
  VRAM_Buffer1[VRAM_Buffer1_Offset + 7] = 0;
  VRAM_Buffer1_Offset = VRAM_Buffer1_Offset + 7;
  return bVar1;
}

// SM2MAIN:6598
// Signature: [] -> []
void GetAlternatePalette1(void) {
  if (AreaStyle == 1) {
    VRAM_Buffer_AddrCtrl = 0xb;
  }
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}

// SM2MAIN:65a7
// Signature: [] -> []
void WriteTopStatusLine(void) {
  WriteGameText(0);
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}

// SM2MAIN:65af
// Signature: [] -> []
void WriteBottomStatusLine(void) {
  byte bVar1;
  byte bVar2;

  WriteScoreAndCoinTally();
  bVar2 = VRAM_Buffer1_Offset;
  VRAM_Buffer1[VRAM_Buffer1_Offset] = 0x20;
  VRAM_Buffer1[bVar2 + 1] = 0x73;
  VRAM_Buffer1[bVar2 + 2] = 3;
  bVar1 = GetWorldNumForDisplay();
  VRAM_Buffer1[bVar2 + 3] = bVar1;
  VRAM_Buffer1[bVar2 + 4] = 0x28;
  VRAM_Buffer1[bVar2 + 5] = LevelNumber + 1;
  VRAM_Buffer1[bVar2 + 6] = 0;
  VRAM_Buffer1_Offset = bVar2 + 6;
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}

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

// SM2MAIN:65f8
// Signature: [] -> []
void DisplayTimeUp(void) {
  if (GameTimerExpiredFlag != 0) {
    GameTimerExpiredFlag = 0;
    OtherInter(2);
    return;
  }
  ScreenRoutineTask = ScreenRoutineTask + 2;
  return;
}

// SM2MAIN:6604
// Signature: [A] -> []
void OtherInter(byte param_1) {
  WriteGameText(param_1);
  ResetScreenTimer();
  DisableScreenFlag = 0;
  return;
}

// SM2MAIN:6617
// Signature: [] -> []
void DisplayIntermediate(void) {
  if (OperMode == 0) {
    ScreenRoutineTask = 9;
    return;
  }
  if (OperMode == 3) {
    WriteGameText(3);
    if (WorldNumber != 8) {
      OperMode_Task = OperMode_Task + 1;
      return;
    }
  } else {
    if (AltEntranceControl != 0) {
      ScreenRoutineTask = 9;
      return;
    }
    if ((AreaType != 3) && (DisableIntermediate != 0)) {
      ScreenRoutineTask = 9;
      return;
    }
    DrawPlayer_Intermediate();
    OtherInter(1);
    if (WorldNumber == 8) {
      DisableScreenFlag = DisableScreenFlag + 1;
      return;
    }
  }
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}

// SM2MAIN:6659
// Signature: [] -> []
void AreaParserTaskControl(void) {
  DisableScreenFlag += 1;
  do {
    AreaParserTaskHandler();
  } while (AreaParserTaskNum != 0);
  ColumnSets -= 1;
  if (0x7f < ColumnSets) {
    ScreenRoutineTask += 1;
  }
  VRAM_Buffer_AddrCtrl = 6;
  return;
}

// SM2MAIN:671b
// Signature: [A] -> []
void WriteGameText(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bStack0000;

  bVar1 = GameTextOffsets[param_1];
  bVar2 = 0;
  do {
    if (TopStatusBarLine[bVar1] == 0xff)
      break;
    VRAM_Buffer1[bVar2] = TopStatusBarLine[bVar1];
    bVar1 += 1;
    bVar2 += 1;
  } while (bVar2 != 0);
  VRAM_Buffer1[bVar2] = 0;
  if ((param_1 != 0) && (param_1 == 1)) {
    VRAM_Buffer1[8] = NumberofLives + 1;
    if (VRAM_Buffer1[8] >= 10) {
      VRAM_Buffer1[8] = (NumberofLives - 9) - (VRAM_Buffer1[8] < 10);
      VRAM_Buffer1[7] = 0x9f;
    }
    bStack0000 = param_1;
    VRAM_Buffer1[19] = GetWorldNumForDisplay();
    VRAM_Buffer1[21] = LevelNumber + 1;
  }
  return;
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

// SM2MAIN:677a
// Signature: [] -> []
void ResetSpritesAndScreenTimer(void) {
  if (ScreenTimer == 0) {
    MoveAllSpritesOffscreen();
    ResetScreenTimer();
    return;
  }
  return;
}

// SM2MAIN:6782
// Signature: [] -> []
void ResetScreenTimer(void) {
  ScreenTimer = 7;
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}

// SM2MAIN:678b
// Signature: [] -> []
void RenderAreaGraphics(void) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;

  bVar7 = CurrentColumnPos & 1;
  VRAM_Buffer2[VRAM_Buffer2_Offset + 1] = CurrentNTAddr_Low;
  VRAM_Buffer2[VRAM_Buffer2_Offset] = CurrentNTAddr_High;
  VRAM_Buffer2[VRAM_Buffer2_Offset + 2] = 0x9a;
  bVar9 = 0;
  bVar5 = 0;
  do {
    bVar4 = VRAM_Buffer2_Offset;
    bVar1 = MetatileBuffer[bVar9];
    bVar8 = bVar1 & 0xc0;
    bVar3 = (bVar1 >> 7) << 1 | (byte)(bVar8 << 1) >> 7;
    bVar6 = MetatileGraphics_Low[bVar3];
    bVar3 = MetatileGraphics_High[bVar3];
    bVar2 = (AreaParserTaskNum & 1 ^ 1) * 2 + MetatileBuffer[bVar9] * 4;
    VRAM_Buffer2[bVar4 + 3] = RAM(CONCAT11(bVar3, bVar6) + (ushort)bVar2);
    VRAM_Buffer2[bVar4 + 4] = RAM(CONCAT11(bVar3, bVar6) + (ushort)(byte)(bVar2 + 1));
    bVar6 = bVar5;
    if (bVar7 == 0) {
      if ((bool)(bVar9 & 1)) {
        bVar8 >>= 2;
NextMTRow:
        bVar6 = bVar5 + 1;
      } else {
        bVar8 = ((bVar9 & 1) << 1 | bVar1 >> 7) << 1 | (byte)(bVar8 << 1) >> 7;
      }
    } else {
      if ((bool)(bVar9 & 1)) {
        goto NextMTRow;
      }
      bVar8 >>= 4;
    }
    AttributeBuffer[bVar5] = AttributeBuffer[bVar5] | bVar8;
    bVar9 += 1;
    VRAM_Buffer2_Offset = bVar4 + 2;
    bVar5 = bVar6;
    if (0xc < bVar9) {
      VRAM_Buffer2[(byte)(bVar4 + 5)] = 0;
      VRAM_Buffer2_Offset = bVar4 + 5;
      CurrentNTAddr_Low += 1;
      if ((CurrentNTAddr_Low & 0x1f) == 0) {
        CurrentNTAddr_Low = 0x80;
        CurrentNTAddr_High ^= 4;
      }
      VRAM_Buffer_AddrCtrl = 6;
      return;
    }
  } while (true);
}

// SM2MAIN:6847
// Signature: [] -> []
void RenderAttributeTables(void) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  bVar1 = (CurrentNTAddr_Low & 0x1f) - 4 & 0x1f;
  bVar2 = CurrentNTAddr_High;
  if ((CurrentNTAddr_Low & 0x1f) < 4) {
    bVar2 = CurrentNTAddr_High ^ 4;
  }
  bVar1 = ((bVar1 >> 2) - 0x40) + (bVar1 >> 1 & 1);
  bVar3 = 0;
  do {
    VRAM_Buffer2[VRAM_Buffer2_Offset] = bVar2 & 4 | 0x23;
    bVar1 += 8;
    VRAM_Buffer2[VRAM_Buffer2_Offset + 1] = bVar1;
    VRAM_Buffer2[VRAM_Buffer2_Offset + 3] = AttributeBuffer[bVar3];
    VRAM_Buffer2[VRAM_Buffer2_Offset + 2] = 1;
    AttributeBuffer[bVar3] = 0;
    VRAM_Buffer2_Offset += 4;
    bVar3 += 1;
  } while (bVar3 < 7);
  VRAM_Buffer2[VRAM_Buffer2_Offset] = 0;
  VRAM_Buffer_AddrCtrl = 6;
  return;
}

// SM2MAIN:68be
// Signature: [] -> []
void ColorRotation(void) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  if (((FrameCounter & 7) == 0) && (VRAM_Buffer1_Offset < 0x31)) {
    bVar3 = 0;
    bVar1 = VRAM_Buffer1_Offset;
    do {
      VRAM_Buffer1[bVar1] = BlankPalette[bVar3];
      bVar1 += 1;
      bVar3 += 1;
    } while (bVar3 < 8);
    bVar1 = 3;
    bVar3 = AreaType << 2;
    bVar2 = VRAM_Buffer1_Offset;
    do {
      VRAM_Buffer1[bVar2 + 3] = Palette3Data[bVar3];
      bVar3 += 1;
      bVar2 += 1;
      bVar1 -= 1;
    } while (bVar1 < 0x80);
    VRAM_Buffer1[VRAM_Buffer1_Offset + 4] = ColorRotatePalette[ColorRotateOffset];
    VRAM_Buffer1_Offset += 7;
    ColorRotateOffset += 1;
    if (5 < ColorRotateOffset) {
      ColorRotateOffset = 0;
    }
  }
  return;
}

// SM2MAIN:692a
// Signature: [r02, r06] -> [r05]
byte RemoveCoin_Axe(byte param_1, byte param_2) {
  byte bVar1;

  bVar1 = 3;
  if (AreaType == 0) {
    bVar1 = 4;
  }
  bVar1 = PutBlockMetatile(bVar1, AreaType, 0x41, param_1, param_2);
  VRAM_Buffer_AddrCtrl = 6;
  return bVar1;
}

// SM2MAIN:693e
// Signature: [A, X, r02, r06] -> []
void ReplaceBlockMetatile(byte param_1, byte param_2, byte param_3, byte param_4) {
  WriteBlockMetatile(param_1, param_2, param_3, param_4);
  Block_ResidualCounter += 1;
  Block_RepFlag[param_2] = Block_RepFlag[param_2] - 1;
  return;
}

// SM2MAIN:6948
// Signature: [X, r02, r06] -> []
void DestroyBlockMetatile(byte param_1, byte param_2, byte param_3) {
  WriteBlockMetatile(0, param_1, param_2, param_3);
  return;
}

// SM2MAIN:694a
// Signature: [A, X, r02, r06] -> []
void WriteBlockMetatile(byte param_1, byte param_2, byte param_3, byte param_4) {
  byte bVar1;
  byte bVar2;

  bVar1 = 3;
  if ((((param_1 != 0) && (bVar1 = 0, param_1 != 0x56)) && (param_1 != 0x4f))
      && ((bVar1 = 1, param_1 != 0x5c && (param_1 != 0x50)))) {
    bVar1 = 2;
  }
  bVar2 = VRAM_Buffer1_Offset + 1;
  PutBlockMetatile(bVar1, param_2, bVar2, param_3, param_4);
  MoveVOffset(bVar2);
  return;
}

// SM2MAIN:696c
// Signature: [Y] -> []
void MoveVOffset(byte param_1) {
  VRAM_Buffer1_Offset = param_1 + 9;
  return;
}

// SM2MAIN:6974
// Signature: [A, X, Y, r02, r06] -> [r05]
byte PutBlockMetatile(byte param_1, byte param_2, byte param_3, byte param_4, byte param_5) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;

  cVar4 = 0x20;
  if (0xcf < param_5) {
    cVar4 = 0x24;
  }
  bVar2 = (param_5 & 0xf) * 2;
  bVar1 = param_4 + 0x20;
  bVar3 = ((bVar1 >> 7) << 1 | (byte)(bVar1 * 2) >> 7) + CARRY1(bVar1 * 4, bVar2) + cVar4;
  RemBridge(param_1 << 2, param_3, param_2, bVar1 * 4 + bVar2, bVar3);
  return bVar3;
}

// SM2MAIN:69aa
// Signature: [X, Y, r00, r04, r05] -> []
void RemBridge(byte param_1, byte param_2, byte param_3, byte param_4, byte param_5) {
  VRAM_Buffer1[param_2 + 2] = BlockGfxData[param_1];
  VRAM_Buffer1[param_2 + 3] = BlockGfxData[param_1 + 1];
  VRAM_Buffer1[param_2 + 7] = BlockGfxData[param_1 + 2];
  VRAM_Buffer1[param_2 + 8] = BlockGfxData[param_1 + 3];
  VRAM_Buffer1[param_2] = param_4;
  VRAM_Buffer1[param_2 + 5] = param_4 + 0x20;
  (&VRAM_Buffer1_Offset)[force_byte(param_2)] = param_5;
  VRAM_Buffer1[param_2 + 4] = param_5;
  VRAM_Buffer1[param_2 + 1] = 2;
  VRAM_Buffer1[param_2 + 6] = 2;
  VRAM_Buffer1[param_2 + 9] = 0;
  return;
}

// SM2MAIN:6c92
// Signature: [] -> []
void InitializeNameTables(void) {
  byte bVar1;

  bVar1 = ppustatus();
  WritePPUReg1(Mirror_PPU_CTRL_REG1 & 0xf0 | 0x10);
  WriteNTAddr(0x24);
  WriteNTAddr(0x20);
  return;
}

// SM2MAIN:6d66
// Signature: [A] -> []
void WritePPUReg1(byte param_1) {
  ppuctrl(param_1);
  Mirror_PPU_CTRL_REG1 = param_1;
  return;
}

// SM2MAIN:6d79
// Signature: [A] -> []
void PrintStatusBarNumbers(byte param_1) {
  OutputNumbers(param_1);
  OutputNumbers(param_1 >> 4);
  return;
}

// SM2MAIN:6d84
// Signature: [A] -> []
void OutputNumbers(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  bVar1 = param_1 + 1 & 0xf;
  if (bVar1 < 6) {
    bVar3 = bVar1 * 2;
    bVar2 = 0x20;
    if (bVar1 == 0) {
      bVar2 = 0x22;
    }
    VRAM_Buffer1[VRAM_Buffer1_Offset] = bVar2;
    VRAM_Buffer1[VRAM_Buffer1_Offset + 1] = StatusBarData[bVar3];
    bVar2 = StatusBarData[bVar3 + 1];
    VRAM_Buffer1[VRAM_Buffer1_Offset + 2] = bVar2;
    bVar1 = StatusBarOffset[bVar1] - StatusBarData[bVar3 + 1];
    do {
      bVar3 = VRAM_Buffer1_Offset;
      VRAM_Buffer1[bVar3 + 3] = DisplayDigits_Or_TopScoreDisplay[bVar1];
      bVar1 += 1;
      bVar2 -= 1;
      VRAM_Buffer1_Offset = bVar3 + 1;
    } while (bVar2 != 0);
    VRAM_Buffer1[(byte)(bVar3 + 1) + 3] = 0;
    VRAM_Buffer1_Offset = bVar3 + 4;
  }
  return;
}

// SM2MAIN:6dd2
// Signature: [Y] -> []
void DigitsMathRoutine(byte param_1) {
  byte bVar1;
  byte bVar2;

  if (OperMode != 0) {
    bVar2 = 5;
    do {
      bVar1 = DigitModifier[bVar2] + DisplayDigits_Or_TopScoreDisplay[param_1];
      if (bVar1 < 0x80) {
        if (9 < bVar1) {
          bVar1 -= 10;
          DigitModifier_Minus1[bVar2] = DigitModifier_Minus1[bVar2] + 1;
        }
      } else {
        DigitModifier_Minus1[bVar2] = DigitModifier_Minus1[bVar2] - 1;
        bVar1 = 9;
      }
      DisplayDigits_Or_TopScoreDisplay[param_1] = bVar1;
      param_1 -= 1;
      bVar2 -= 1;
    } while (bVar2 < 0x80);
  }
  bVar2 = 6;
  do {
    DigitModifier_Minus1[bVar2] = 0;
    bVar2 -= 1;
  } while (bVar2 < 0x80);
  return;
}

// SM2MAIN:6e08
// Signature: [] -> []
void UpdateTopScore(void) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  bool bVar4;
  byte bVar5;
  byte bVar6;
  bool bVar7;

  bVar5 = 5;
  bVar3 = 5;
  bVar4 = true;
  do {
    bVar7 = bVar4;
    bVar6 = bVar3;
    bVar1 = PlayerScoreDisplay_Or_ScoreAndCoinDisplay[bVar5];
    bVar2 = DisplayDigits_Or_TopScoreDisplay[bVar6];
    bVar5 -= 1;
    bVar3 = bVar6 - 1;
    bVar4 = bVar7 && bVar2 <= bVar1 || !bVar7 && bVar2 < bVar1;
  } while ((byte)(bVar6 - 1) < 0x80);
  if (bVar7 && bVar2 <= bVar1 || !bVar7 && bVar2 < bVar1) {
    do {
      bVar5 += 1;
      DisplayDigits_Or_TopScoreDisplay[bVar6] = PlayerScoreDisplay_Or_ScoreAndCoinDisplay[bVar5];
      bVar6 += 1;
    } while (bVar6 < 6);
  }
  return;
}

// SM2MAIN:6e39
// Signature: [] -> []
void InitializeArea(void) {
  byte bVar1;

  InitializeMemory(0x4b);
  bVar1 = 0x21;
  do {
    (&SelectTimer)[force_byte(bVar1)] = 0;
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  ScreenEdgeOrLeft_PageLoc[0] = HalfwayPage;
  if (AltEntranceControl != 0) {
    ScreenEdgeOrLeft_PageLoc[0] = EntrancePage;
  }
  CurrentPageLoc = ScreenEdgeOrLeft_PageLoc[0];
  BackloadingFlag = ScreenEdgeOrLeft_PageLoc[0];
  bVar1 = GetScreenPosition();
  CurrentNTAddr_High = 0x20;
  if ((bVar1 & 1) != 0) {
    CurrentNTAddr_High = 0x24;
  }
  CurrentNTAddr_Low = 0x80;
  BlockBufferColumnPos = (bVar1 & 1) << 4;
  AreaObjectLength[0] -= 1;
  AreaObjectLength[1] -= 1;
  AreaObjectLength[2] -= 1;
  ColumnSets = 0xb;
  FUN_3000();
  if ((HardWorldFlag != 0) || ((2 < WorldNumber && ((WorldNumber != 3 || (2 < LevelNumber)))))) {
    SecondaryHardMode += 1;
  }
  if (HalfwayPage != 0) {
    PlayerEntranceCtrl = 2;
  }
  AreaMusicQueue = 0x80;
  DisableScreenFlag = 1;
  LoadPhysicsData();
  OperMode_Task = OperMode_Task + 1;
  return;
}

// SM2MAIN:6eb9
// Signature: [] -> []
void SecondaryGameSetup(void) {
  byte bVar1;

  DisableScreenFlag = 0;
  WindFlag = 0;
  FlagpoleMusicFlag = 0;
  bVar1 = 0;
  do {
    (&VRAM_Buffer1_Offset)[force_byte(bVar1)] = 0;
    bVar1 += 1;
  } while (bVar1 != 0);
  GameTimerExpiredFlag = 0;
  DisableIntermediate = 0;
  BackloadingFlag = 0;
  BalPlatformAlignment = 0xff;
  NameTableSelect = ScreenEdgeOrLeft_PageLoc[0] & 1;
  GetAreaMusic();
  SprShuffleAmt[2] = 0x38;
  SprShuffleAmt[1] = 0x48;
  SprShuffleAmt[0] = 0x58;
  bVar1 = 0xe;
  do {
    PlayerOrSprDataOffset[bVar1] = DefaultSprOffsets[bVar1];
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  DoNothing();
  IRQUpdateFlag = IRQUpdateFlag + 1;
  OperMode_Task = OperMode_Task + 1;
  return;
}

// SM2MAIN:6f2d
// Signature: [] -> []
void GetAreaMusic(void) {
  byte bVar1;

  if (OperMode != 0) {
    if (((AltEntranceControl == 2) || ((bVar1 = 5, PlayerEntranceCtrl != 6 && (PlayerEntranceCtrl != 7))))
        && (bVar1 = AreaType, CloudTypeOverride != 0)) {
      bVar1 = 4;
    }
    AreaMusicQueue = MusicSelectData[bVar1];
    return;
  }
  return;
}

// SM2MAIN:6f71
// Signature: [r07] -> []
void Entrance_GameTimerSetup(byte param_1) {
  byte bVar1;

  SprObject_PageLoc[0] = ScreenEdgeOrLeft_PageLoc[0];
  VerticalForceDown = 0x28;
  PlayerFacingDir = 1;
  SprObject_Y_HighPos[0] = 1;
  Player_State = 0;
  Player_CollisionBits -= 1;
  HalfwayPage = 0;
  SwimmingFlag = AreaType == 0;
  bVar1 = PlayerEntranceCtrl;
  if ((AltEntranceControl != 0) && (AltEntranceControl != 1)) {
    bVar1 = PlayerStarting_X_Pos[AltEntranceControl + 2];
  }
  SprObject_X_Position[0] = PlayerStarting_X_Pos[AltEntranceControl];
  SprObject_Y_Position[0] = PlayerStarting_Y_Pos[bVar1];
  Player_SprAttrib = PlayerBGPriorityData[bVar1];
  bVar1 = GetPlayerColors();
  if ((GameTimerSetting != 0) && (FetchNewGameTimerFlag != 0)) {
    GameTimerDisplaySMB2J[0] = GameTimerData[GameTimerSetting];
    GameTimerDisplaySMB2J[2] = 1;
    GameTimerDisplaySMB2J[1] = 0;
    FetchNewGameTimerFlag = 0;
    StarInvincibleTimer = 0;
  }
  if (JoypadOverride != 0) {
    Player_State = 3;
    InitBlock_XY_Pos(0);
    Block_Y_Position[0] = 0xf0;
    bVar1 = 5;
    Setup_Vine(5, 0);
  }
  if (AreaType == 0) {
    SetupBubble(bVar1, param_1);
  }
  GameEngineSubroutine = 7;
  return;
}

// SM2MAIN:700f
// Signature: [] -> []
void PlayerLoseLife(void) {
  byte bVar1;

  DisableScreenFlag += 1;
  IRQUpdateFlag = 0;
  EventMusicQueue = 0x80;
  NumberofLives -= 1;
  if (0x7f < NumberofLives) {
    OperMode_Task = 0;
    OperMode = 3;
    return;
  }
  bVar1 = WorldNumber * 2;
  if ((LevelNumber & 2) != 0) {
    bVar1 += 1;
  }
  bVar1 = HalfwayPageNybbles[bVar1];
  if (!(bool)(LevelNumber & 1)) {
    bVar1 >>= 4;
  }
  HalfwayPage = bVar1 & 0xf;
  if ((HalfwayPage != ScreenEdgeOrLeft_PageLoc[0]) && (ScreenEdgeOrLeft_PageLoc[0] <= HalfwayPage)) {
    HalfwayPage = 0;
  }
  ContinueGame();
  return;
}

// SM2MAIN:7057
// Signature: [] -> []
void GameOverSubs(void) {
  FUN_30bf(OperMode_Task);
  return;
}

// SM2MAIN:7063
// Signature: [] -> []
void SetupGameOver(void) {
  ScreenRoutineTask = 0;
  IRQUpdateFlag = 0;
  ContinueMenuSelect = 0;
  EventMusicQueue = 2;
  DisableScreenFlag = DisableScreenFlag + 1;
  OperMode_Task = OperMode_Task + 1;
  return;
}

// SM2MAIN:7079
// Signature: [] -> []
void RunGameOver(void) {
  DisableScreenFlag = 0;
  if (WorldNumber != 8) {
    GameOverMenu();
    return;
  }
  if (ScreenTimer == 0) {
    TerminateGame();
    return;
  }
  return;
}

// SM2MAIN:708d
// Signature: [] -> []
void TerminateGame(void) {
  EventMusicQueue = 0x80;
  OperMode_Task = 0;
  ScreenTimer = 0;
  OperMode = 0;
  return;
}

// SM2MAIN:709d
// Signature: [] -> []
void ContinueGame(void) {
  LoadAreaPointer();
  PlayerSize = 1;
  FetchNewGameTimerFlag = FetchNewGameTimerFlag + 1;
  TimerControl = 0;
  PlayerStatus = 0;
  GameEngineSubroutine = 0;
  OperMode_Task = 0;
  OperMode = 1;
  return;
}

// SM2MAIN:70bb
// Signature: [] -> []
void DoNothing(void) {
  Misc_Collision_Flag[11] = 0xff;
  return;
}

// SM2MAIN:70c1
// Signature: [] -> []
void AreaParserTaskHandler(void) {
  if (AreaParserTaskNum == 0) {
    AreaParserTaskNum = 8;
  }
  AreaParserTasks(AreaParserTaskNum - 1);
  AreaParserTaskNum -= 1;
  if (AreaParserTaskNum == 0) {
    RenderAttributeTables();
  }
  return;
}

// SM2MAIN:70d9
// Signature: [A] -> []
void AreaParserTasks(byte param_1) {
  FUN_30cf(param_1);
  return;
}

// SM2MAIN:70ec
// Signature: [] -> []
void IncrementColumnPos(void) {
  CurrentColumnPos += 1;
  if ((CurrentColumnPos & 0xf) == 0) {
    CurrentPageLoc += 1;
    CurrentColumnPos = 0;
  }
  BlockBufferColumnPos = BlockBufferColumnPos + 1 & 0x1f;
  return;
}

// SM2MAIN:720d
// Signature: [] -> []
void AreaParserCore(void) {
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  bool bVar7;
  struct_r06r07i sVar8;

  if (BackloadingFlag != 0) {
    ProcessAreaData();
  }
  bVar4 = 0xc;
  do {
    MetatileBuffer[bVar4] = 0;
    bVar4 -= 1;
  } while (bVar4 < 0x80);
  bVar4 = CurrentPageLoc;
  if (BackgroundScenery != 0) {
    do {
      if (0x7f < (byte)(bVar4 - 3))
        break;
      bVar4 -= 3;
    } while (bVar4 < 0x80);
    bVar7 = (bool)-((char)(bVar4 << 3) >> 7);
    cVar1 = bVar4 * 0x10 + BSceneDataOffsets[BackgroundScenery - 1] + bVar7;
    bVar4 = BackSceneryData[(
        byte)(cVar1 + CurrentColumnPos
              + (CARRY1(bVar4 * 0x10, BSceneDataOffsets[BackgroundScenery - 1]) || bVar7 && cVar1 == 0))];
    if (bVar4 != 0) {
      cVar1 = (bVar4 & 0xf) - 1;
      bVar2 = cVar1 * 3 - (cVar1 >> 7);
      bVar4 >>= 4;
      cVar1 = 3;
      do {
        MetatileBuffer[bVar4] = BackSceneryMetatiles[bVar2];
        bVar2 += 1;
        bVar4 += 1;
        if (bVar4 == 0xb)
          break;
        cVar1 += -1;
      } while (cVar1 != 0);
    }
  }
  if (ForegroundScenery != 0) {
    bVar4 = BackSceneryMetatiles[ForegroundScenery + 0x23];
    bVar2 = 0;
    do {
      if (ForeSceneryData[bVar4] != 0) {
        MetatileBuffer[bVar2] = ForeSceneryData[bVar4];
      }
      bVar4 += 1;
      bVar2 += 1;
    } while (bVar2 != 0xd);
  }
  if ((AreaType == 0) && (WorldNumber == 7)) {
    bVar4 = 99;
  } else {
    bVar4 = TerrainMetatiles[AreaType];
    if (CloudTypeOverride != 0) {
      bVar4 = 0x88;
    }
  }
  bVar5 = 0;
  bVar2 = TerrainControl << 1;
  do {
    bVar3 = TerrainRenderBits[bVar2];
    bVar2 += 1;
    if ((CloudTypeOverride != 0) && (bVar5 != 0)) {
      bVar3 &= 8;
    }
    bVar6 = 0;
    do {
      if ((Bitmasks[bVar6] & bVar3) != 0) {
        MetatileBuffer[bVar5] = bVar4;
      }
      bVar5 += 1;
      if (bVar5 == 0xd) {
        goto RendBBuf;
      }
      if ((AreaType == 2) && (bVar5 == 0xb)) {
        bVar4 = 0x6b;
      }
      bVar6 += 1;
    } while (bVar6 != 8);
  } while (bVar2 != 0);
RendBBuf:
  ProcessAreaData();
  sVar8 = GetBlockBufferAddr(BlockBufferColumnPos);
  bVar2 = 0;
  bVar4 = 0;
  do {
    bVar5 = MetatileBuffer[bVar2];
    if (bVar5 < BlockBuffLowBounds[(byte)((MetatileBuffer[bVar2] >> 7) << 1
                                          | (byte)((MetatileBuffer[bVar2] & 0xc0) << 1) >> 7)]) {
      bVar5 = 0;
    }
    RAM(SUBPIECE(sVar8, 0, 2) + (ushort)bVar4) = bVar5;
    bVar4 += 0x10;
    bVar2 += 1;
  } while (bVar2 < 0xd);
  return;
}

// SM2MAIN:7319
// Signature: [] -> []
void ProcessAreaData(void) {
  byte bVar1;
  byte bVar2;

  do {
    bVar1 = 2;
    do {
      BehindAreaParserFlag = 0;
      ObjectOffset = bVar1;
      if ((AreaData[AreaDataOffset] == 0xfd) || (AreaObjectLength[bVar1] < 0x80)) {
RdyDecode:
        DecodeAreaData(bVar1, AreaDataOffset);
      } else {
        bVar2 = AreaDataOffset + 1;
        if (((char)AreaData[bVar2] < 0) && (AreaObjectPageSel == 0)) {
          AreaObjectPageSel = 1;
          AreaObjectPageLoc += 1;
        }
        if ((AreaData[AreaDataOffset] & 0xf) != 0xd) {
          if (((AreaData[AreaDataOffset] & 0xf) != 0xe) || (BackloadingFlag == 0)) {
            goto CheckRear;
          }
          goto RdyDecode;
        }
        if (((AreaData[bVar2] & 0x40) == 0) && (AreaObjectPageSel == 0)) {
          AreaObjectPageLoc = AreaData[bVar2] & 0x1f;
          AreaObjectPageSel = 1;
        } else {
CheckRear:
          if (CurrentPageLoc <= AreaObjectPageLoc) {
            goto RdyDecode;
          }
          BehindAreaParserFlag = 1;
        }
        IncAreaObjOffset();
      }
      bVar1 = ObjectOffset;
      if (AreaObjectLength[ObjectOffset] < 0x80) {
        AreaObjectLength[ObjectOffset] = AreaObjectLength[ObjectOffset] - 1;
      }
      bVar1 -= 1;
    } while (bVar1 < 0x80);
    if ((BehindAreaParserFlag == 0) && (BackloadingFlag == 0)) {
      return;
    }
  } while (true);
}

// SM2MAIN:739a
// Signature: [] -> []
void IncAreaObjOffset(void) {
  AreaDataOffset = AreaDataOffset + 2;
  AreaObjectPageSel = 0;
  return;
}

// SM2MAIN:73a6
// Signature: [X, Y] -> []
void DecodeAreaData(byte param_1, byte param_2) {
  byte bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;

  bVar3 = ObjectOffset;
  if (AreaObjectLength[param_1] < 0x80) {
    param_2 = AreaObjOffsetBuffer[param_1];
  }
  cVar2 = 0x10;
  if (AreaData[param_2] == 0xfd) {
    return;
  }
  bVar1 = AreaData[param_2] & 0xf;
  if ((bVar1 != 0xf) && (cVar2 = 8, bVar1 != 0xc)) {
    cVar2 = 0;
  }
  if (bVar1 == 0xe) {
    cVar2 = 0;
    bVar1 = 0x36;
  } else if (bVar1 == 0xd) {
    cVar2 = 0x28;
    if ((AreaData[(byte)(param_2 + 1)] & 0x40) == 0) {
      return;
    }
    if ((AreaData[(byte)(param_2 + 1)] & 0x7f) == 0x4b) {
      LoopCommand += 1;
    }
    bVar1 = AreaData[(byte)(param_2 + 1)] & 0x3f;
  } else {
    if (bVar1 < 0xc) {
      bVar4 = param_2 + 1;
      bVar1 = AreaData[bVar4] & 0x70;
      if (bVar1 == 0) {
        cVar2 = 0x18;
        bVar1 = AreaData[bVar4] & 0xf;
        goto NormObj;
      }
      if ((bVar1 == 0x70) && ((AreaData[bVar4] & 8) != 0)) {
        bVar1 = 0;
      }
    } else {
      bVar1 = AreaData[(byte)(param_2 + 1)] & 0x70;
    }
    bVar1 >>= 4;
  }
NormObj:
  if (0x7f < AreaObjectLength[ObjectOffset]) {
    if (AreaObjectPageLoc == CurrentPageLoc) {
      if (BackloadingFlag != 0) {
        BackloadingFlag = 0;
        BehindAreaParserFlag = 0;
        ObjectOffset = 0;
        return;
      }
      if (AreaData[AreaDataOffset] >> 4 != CurrentColumnPos) {
        return;
      }
    } else if (((AreaData[AreaDataOffset] & 0xf) != 0xe) || (BackloadingFlag == 0)) {
      return;
    }
    AreaObjOffsetBuffer[ObjectOffset] = AreaDataOffset;
    IncAreaObjOffset();
  }
  FUN_30f3(bVar1 + cVar2, bVar3, bVar1);
  return;
}

// SM2MAIN:7456
// Signature: [] -> []
void LoopCmdE(void) { return; }

// SM2MAIN:74e6
// Signature: [X] -> []
void AlterAreaAttributes(byte param_1) {
  byte bVar1;

  bVar1 = AreaData[(byte)(AreaObjOffsetBuffer[param_1] + 1)];
  if ((bVar1 & 0x40) == 0) {
    TerrainControl = bVar1 & 0xf;
    BackgroundScenery = (bVar1 & 0x30) >> 4;
    return;
  }
  bVar1 &= 7;
  ForegroundScenery = bVar1;
  if (3 < bVar1) {
    ForegroundScenery = 0;
    BackgroundColorCtrl = bVar1;
  }
  return;
}

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

// SM2MAIN:7564
// Signature: [] -> []
void ScrollLockObject(void) {
  ScrollLock = ScrollLock ^ 1;
  return;
}

// SM2MAIN:756d
// Signature: [A] -> []
void KillEnemies(byte param_1) {
  byte bVar1;

  bVar1 = 4;
  do {
    if (Enemy_ID[bVar1] == param_1) {
      Enemy_Flag[bVar1] = 0;
    }
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  return;
}

// SM2MAIN:7582
// Signature: [r00] -> []
void AreaFrenzy(byte param_1) {
  byte bVar1;

  bVar1 = 5;
  do {
    bVar1 -= 1;
    if (0x7f < bVar1) {
      EnemyFrenzyQueue = FrenzyIDData[param_1 - 8];
      return;
    }
  } while (FrenzyIDData[param_1 - 8] != Enemy_ID[bVar1]);
  EnemyFrenzyQueue = 0;
  return;
}

// SM2MAIN:7597
// Signature: [X] -> []
void AreaStyleObject(byte param_1) {
  FUN_31d3(AreaStyle, param_1);
  return;
}

// SM2MAIN:75a3
// Signature: [X] -> []
void TreeLedge(byte param_1) {
  byte bVar1;
  struct_yr07i sVar2;

  sVar2 = GetLrgObjAttrib(param_1);
  bVar1 = sVar2.r07;
  if (AreaObjectLength[param_1] == 0) {
    NoUnder(0x18, bVar1);
    return;
  }
  if ((0x7f < AreaObjectLength[param_1])
      && (AreaObjectLength[param_1] = sVar2.y, (CurrentPageLoc | CurrentColumnPos) != 0)) {
    NoUnder(0x16, bVar1);
    return;
  }
  MetatileBuffer[bVar1] = 0x17;
  AllUnder(0x4c, bVar1);
  return;
}

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

// SM2MAIN:75f6
// Signature: [A, X] -> []
void AllUnder(byte param_1, byte param_2) {
  RenderUnderPart(param_1, param_2 + 1, 0xf);
  return;
}

// SM2MAIN:75fc
// Signature: [A, r07] -> []
void NoUnder(byte param_1, byte param_2) {
  RenderUnderPart(param_1, param_2, 0);
  return;
}

// SM2MAIN:7606
// Signature: [X] -> []
void PulleyRopeObject(byte param_1) {
  byte bVar1;
  struct_ycr07 sVar2;

  sVar2 = ChkLrgObjLength(param_1);
  bVar1 = 0;
  if ((!sVar2.c) && (bVar1 = 1, AreaObjectLength[param_1] == 0)) {
    bVar1 = 2;
  }
  MetatileBuffer[0] = PulleyRopeMetatiles[bVar1];
  return;
}

// SM2MAIN:7652
// Signature: [X] -> []
void CastleObject(byte param_1) {
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  struct_yr07i sVar5;
  struct_xci sVar6;
  byte bStack0000;

  sVar5 = GetLrgObjAttrib(param_1);
  bVar3 = sVar5.y;
  ChkLrgObjFixedLength(param_1, 4);
  bVar4 = AreaObjectLength[param_1];
  cVar1 = 0x0B;
  bVar2 = bVar3;
  do {
    MetatileBuffer[bVar2] = CastleMetatiles[bVar4];
    bVar2 += 1;
    if (cVar1 != 0) {
      bVar4 += 5;
      cVar1 += -1;
    }
  } while (bVar2 != 0xb);
  if (CurrentPageLoc != 0) {
    bVar4 = AreaObjectLength[param_1];
    if ((bVar4 == 1) || ((bVar3 == 0 && (bVar4 == 3)))) {
      MetatileBuffer[10] = 0x50;
    } else if (bVar4 == 2) {
      bStack0000 = param_1;
      bStack0000 = GetAreaObjXPosition();
      sVar6 = FindEmptyEnemySlot();
      bVar4 = sVar6.x;
      Enemy_X_Position[bVar4] = bStack0000;
      Enemy_PageLoc[bVar4] = CurrentPageLoc;
      Enemy_Y_HighPos[bVar4] = 1;
      Enemy_Flag[bVar4] = 1;
      Enemy_Y_Position[bVar4] = 0x90;
      Enemy_ID[bVar4] = 0x31;
      return;
    }
  }
  return;
}

// SM2MAIN:76bb
// Signature: [X] -> []
void WaterPipe(byte param_1) {
  struct_yr07i sVar1;

  sVar1 = GetLrgObjAttrib(param_1);
  MetatileBuffer[sVar1.r07] = 0x6d;
  MetatileBuffer[sVar1.r07 + 1] = 0x6e;
  return;
}

// SM2MAIN:76ce
// Signature: [X] -> []
void IntroPipe(byte param_1) {
  byte bVar1;
  struct_yci sVar2;

  ChkLrgObjFixedLength(param_1, 3);
  sVar2 = RenderSidewaysPipe(param_1, 10);
  if (!sVar2.c) {
    bVar1 = 6;
    do {
      MetatileBuffer[bVar1] = 0;
      bVar1 -= 1;
    } while (bVar1 < 0x80);
    MetatileBuffer[7] = VerticalPipeData[sVar2.y];
  }
  return;
}

// SM2MAIN:76f7
// Signature: [X] -> []
void ExitPipe(byte param_1) {
  struct_yr07i sVar1;

  ChkLrgObjFixedLength(param_1, 3);
  sVar1 = GetLrgObjAttrib(param_1);
  RenderSidewaysPipe(param_1, sVar1.y);
  return;
}

// SM2MAIN:76ff
// Signature: [X, Y] -> [Y, C]
struct_yci RenderSidewaysPipe(byte param_1, byte param_2) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  struct_yci sVar4;

  bVar3 = param_2 - 1;
  bVar2 = AreaObjectLength[param_1];
  bVar1 = SidePipeShaftData[bVar2];
  if (bVar1 != 0) {
    bVar3 = RenderUnderPart(bVar1, 0, param_2 - 2);
  }
  MetatileBuffer[bVar3] = SidePipeTopPart[bVar2];
  MetatileBuffer[bVar3 + 1] = SidePipeBottomPart[bVar2];
  sVar4.c = bVar1 == 0;
  sVar4.y = bVar2;
  sVar4.i = (bool)0;
  return sVar4;
}

// SM2MAIN:7731
// Signature: [X, r00] -> []
void VerticalPipe(byte param_1, byte param_2) {
  byte bVar1;
  byte bVar2;
  struct_yr06r07 sVar3;
  struct_xci sVar4;
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

// SM2MAIN:7761
// Signature: [X] -> [Y, r06, r07]
struct_yr06r07 GetPipeHeight(byte param_1) {
  struct_yr07i sVar1;

  ChkLrgObjFixedLength(param_1, 1);
  sVar1 = GetLrgObjAttrib(param_1);
  return CAST_INT_TO_struct_yr06r07(CONCAT12(sVar1.r07, CONCAT11(sVar1.y, AreaObjectLength[param_1])) & 0xff07ff);
}

// SM2MAIN:7772
// Signature: [A, X, r07] -> []
void SetupPiranhaPlant(byte param_1, byte param_2, byte param_3) {
  byte bVar1;

  Enemy_ID[param_2] = param_1;
  bVar1 = GetAreaObjXPosition();
  Enemy_X_Position[param_2] = bVar1 + 8;
  Enemy_PageLoc[param_2] = CurrentPageLoc + (0xf7 < bVar1);
  Enemy_Y_HighPos[param_2] = 1;
  Enemy_Flag[param_2] = 1;
  bVar1 = GetAreaObjYPosition(param_3);
  Enemy_Y_Position[param_2] = bVar1;
  InitPiranhaPlant(param_2);
  return;
}

// SM2MAIN:7791
// Signature: [] -> [X, C]
struct_xci FindEmptyEnemySlot(void) {
  byte bVar1;

  bool bVar2;
  struct_xci sVar3;

  bVar1 = 0;
  do {
    bVar2 = false;
    if (Enemy_Flag[bVar1] == 0)
      break;
    bVar1 += 1;
    bVar2 = 4 < bVar1;
  } while (bVar1 != 5);
  sVar3.c = bVar2;
  sVar3.x = bVar1;
  sVar3.i = (bool)0;
  return sVar3;
}

// SM2MAIN:779e
// Signature: [X] -> []
void Hole_Water(byte param_1) {
  ChkLrgObjLength(param_1);
  MetatileBuffer[10] = 0x86;
  RenderUnderPart(0x87, 0xb, 1);
  return;
}

// SM2MAIN:77af
// Signature: [X] -> []
void QuestionBlockRow_High(byte param_1) {
  byte bStack0000;

  bStack0000 = 3;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xc0;
  return;
}

// SM2MAIN:77b2
// Signature: [X] -> []
void QuestionBlockRow_Low(byte param_1) {
  byte bStack0000;

  bStack0000 = 7;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xc0;
  return;
}

// SM2MAIN:77c0
// Signature: [X] -> []
void Bridge_High(byte param_1) {
  byte bStack0000;

  bStack0000 = 6;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xb;
  RenderUnderPart(100, bStack0000 + 1, 0);
  return;
}

// SM2MAIN:77c3
// Signature: [X] -> []
void Bridge_Middle(byte param_1) {
  byte bStack0000;

  bStack0000 = 7;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xb;
  RenderUnderPart(100, bStack0000 + 1, 0);
  return;
}

// SM2MAIN:77c6
// Signature: [X] -> []
void Bridge_Low(byte param_1) {
  byte bStack0000;

  bStack0000 = 9;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xb;
  RenderUnderPart(100, bStack0000 + 1, 0);
  return;
}

// SM2MAIN:77db
// Signature: [X] -> []
void FlagBalls_Residual(byte param_1) {
  struct_yr07i sVar1;

  sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(0x6f, 2, sVar1.y);
  return;
}

// SM2MAIN:77e5
// Signature: [] -> []
void FlagpoleObject(void) {
  byte bVar1;

  MetatileBuffer[0] = 0x21;
  RenderUnderPart(0x22, 1, 8);
  MetatileBuffer[10] = 0x62;
  bVar1 = GetAreaObjXPosition();
  Enemy_X_Position[5] = bVar1 - 8;
  Enemy_PageLoc[5] = CurrentPageLoc - (bVar1 < 8);
  Enemy_Y_Position[5] = 0x30;
  FlagpoleFNum_Y_Pos = 0xb0;
  Enemy_ID[5] = 0x30;
  Enemy_Flag[5] = Enemy_Flag[5] + 1;
  return;
}

// SM2MAIN:7817
// Signature: [] -> []
void EndlessRope(void) {
  RenderUnderPart(0x40, 0, 0xf);
  return;
}

// SM2MAIN:781e
// Signature: [X] -> []
void BalancePlatRope(byte param_1) {
  struct_yr07i sVar1;
  byte bStack0000;

  bStack0000 = param_1;
  RenderUnderPart(0x44, 1, 0xf);
  sVar1 = GetLrgObjAttrib(bStack0000);
  RenderUnderPart(0x40, 1, sVar1.y);
  return;
}

// SM2MAIN:7839
// Signature: [X] -> []
void RowOfCoins(byte param_1) {
  struct_ycr07 sVar1;
  byte bStack0000;

  bStack0000 = CoinMetatileData[AreaType];
  sVar1 = ChkLrgObjLength(param_1);
  RenderUnderPart(bStack0000, sVar1.r07, 0);
  return;
}

// SM2MAIN:7848
// Signature: [X, r00] -> []
void CastleBridgeObj(byte param_1, byte param_2) {
  ChkLrgObjFixedLength(param_1, 0xc);
  ChainObj(param_2);
  return;
}

// SM2MAIN:7850
// Signature: [r00] -> []
void AxeObj(byte param_1) {
  VRAM_Buffer_AddrCtrl = 8;
  ChainObj(param_1);
  return;
}

// SM2MAIN:7855
// Signature: [r00] -> []
void ChainObj(byte param_1) {
  RenderUnderPart(C_ObjectRow[param_1 + 1], C_ObjectRow[param_1 - 2], 0);
  return;
}

// SM2MAIN:7860
// Signature: [X] -> []
void EmptyBlock(byte param_1) {
  struct_yr07i sVar1;

  sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(0xc5, sVar1.r07, 0);
  return;
}

// SM2MAIN:7875
// Signature: [X] -> []
void RowOfBricks(byte param_1) {
  byte bVar1;
  struct_ycr07 sVar2;
  byte bStack0000;

  bVar1 = AreaType;
  if (CloudTypeOverride != 0) {
    bVar1 = 4;
  }
  bStack0000 = BrickMetatiles[bVar1];
  sVar2 = ChkLrgObjLength(param_1);
  RenderUnderPart(bStack0000, sVar2.r07, 0);
  return;
}

// SM2MAIN:7885
// Signature: [X] -> []
void RowOfSolidBlocks(byte param_1) {
  struct_ycr07 sVar1;
  byte bStack0000;

  bStack0000 = SolidBlockMetatiles[AreaType];
  sVar1 = ChkLrgObjLength(param_1);
  RenderUnderPart(bStack0000, sVar1.r07, 0);
  return;
}

// SM2MAIN:7897
// Signature: [X] -> []
void ColumnOfBricks(byte param_1) {
  struct_yr07i sVar1;
  byte bStack0000;

  bStack0000 = BrickMetatiles[AreaType];
  sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(bStack0000, sVar1.r07, sVar1.y);
  return;
}

// SM2MAIN:78a0
// Signature: [X] -> []
void ColumnOfSolidBlocks(byte param_1) {
  struct_yr07i sVar1;
  byte bStack0000;

  bStack0000 = SolidBlockMetatiles[AreaType];
  sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(bStack0000, sVar1.r07, sVar1.y);
  return;
}

// SM2MAIN:78b0
// Signature: [X] -> []
void BulletBillCannon(byte param_1) {
  byte bVar1;
  byte bVar2;
  struct_yr07i sVar3;

  sVar3 = GetLrgObjAttrib(param_1);
  bVar1 = sVar3.r07;
  MetatileBuffer[bVar1] = 0x65;
  if ((byte)(sVar3.y - 1) < 0x80) {
    MetatileBuffer[(byte)(bVar1 + 1)] = 0x66;
    bVar2 = sVar3.y - 2;
    if (bVar2 < 0x80) {
      RenderUnderPart(0x67, bVar1 + 2, bVar2);
    }
  }
  bVar2 = Cannon_Or_Whirlpool_Offset;
  bVar1 = GetAreaObjYPosition(bVar1);
  Cannon_Y_Position_Or_Whirlpool_Length[bVar2] = bVar1;
  Cannon_Or_Whirlpool_PageLoc[bVar2] = CurrentPageLoc;
  bVar1 = GetAreaObjXPosition();
  Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar2] = bVar1;
  Cannon_Or_Whirlpool_Offset = bVar2 + 1;
  if (5 < Cannon_Or_Whirlpool_Offset) {
    Cannon_Or_Whirlpool_Offset = 0;
  }
  return;
}

// SM2MAIN:78fe
// Signature: [X] -> []
void StaircaseObject(byte param_1) {
  struct_ycr07 sVar1;

  sVar1 = ChkLrgObjLength(param_1);
  if (sVar1.c != false) {
    StaircaseControl = 9;
  }
  StaircaseControl -= 1;
  RenderUnderPart(0x62, StaircaseRowData[StaircaseControl], StaircaseHeightData[StaircaseControl]);
  return;
}

// SM2MAIN:791a
// Signature: [X] -> []
void Jumpspring(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  struct_yr07i sVar4;
  struct_xci sVar5;

  sVar4 = GetLrgObjAttrib(param_1);
  bVar1 = sVar4.r07;
  sVar5 = FindEmptyEnemySlot();
  bVar3 = sVar5.x;
  if (!sVar5.c) {
    bVar2 = GetAreaObjXPosition();
    Enemy_X_Position[bVar3] = bVar2;
    Enemy_PageLoc[bVar3] = CurrentPageLoc;
    bVar2 = GetAreaObjYPosition(bVar1);
    Enemy_Y_Position[bVar3] = bVar2;
    SpriteVarData1[bVar3] = bVar2;
    Enemy_ID[bVar3] = 0x32;
    Enemy_Y_HighPos[bVar3] = 1;
    Enemy_Flag[bVar3] = Enemy_Flag[bVar3] + 1;
    MetatileBuffer[bVar1] = 0x68;
    MetatileBuffer[bVar1 + 1] = 0x69;
  }
  return;
}

// SM2MAIN:794a
// Signature: [X, r00] -> []
void Hidden1UpBlock(byte param_1, byte param_2) {
  if (Hidden1UpFlag != 0) {
    Hidden1UpFlag = 0;
    BrickWithItem(param_1, param_2);
    return;
  }
  return;
}

// SM2MAIN:7957
// Signature: [X, r00] -> []
void QuestionBlock(byte param_1, byte param_2) {
  byte bVar1;
  struct_yr07i sVar2;
  byte bStack0000;

  bVar1 = GetAreaObjectID(param_2);
  bStack0000 = BrickQBlockMetatiles[bVar1];
  sVar2 = GetLrgObjAttrib(param_1);
  RenderUnderPart(bStack0000, sVar2.r07, 0);
  return;
}

// SM2MAIN:795d
// Signature: [X, r00] -> []
void BrickWithCoins(byte param_1, byte param_2) {
  BrickCoinTimerFlag = 0;
  BrickWithItem(param_1, param_2);
  return;
}

// SM2MAIN:7962
// Signature: [X, r00] -> []
void BrickWithItem(byte param_1, byte param_2) {
  char cVar1;
  byte bVar2;
  struct_yr07i sVar3;
  byte bStack0000;

  bVar2 = GetAreaObjectID(param_2);
  cVar1 = 0;
  if (AreaType != 1) {
    cVar1 = 6;
  }
  bStack0000 = BrickQBlockMetatiles[(byte)(cVar1 + bVar2)];
  sVar3 = GetLrgObjAttrib(param_1);
  RenderUnderPart(bStack0000, sVar3.r07, 0);
  return;
}

// SM2MAIN:797f
// Signature: [r00] -> [Y]
byte GetAreaObjectID(byte param_1) { return param_1; }

// SM2MAIN:798a
// Signature: [X] -> []
void Hole_Empty(byte param_1) {
  byte bVar1;
  byte bVar2;
  struct_ycr07 sVar3;

  sVar3 = ChkLrgObjLength(param_1);
  bVar2 = sVar3.y;
  if ((sVar3.c != false) && (AreaType == 0)) {
    bVar1 = GetAreaObjXPosition();
    Cannon_X_Position_Or_Whirlpool_LeftExtent[Cannon_Or_Whirlpool_Offset] = bVar1 - 0x10;
    Cannon_Or_Whirlpool_PageLoc[Cannon_Or_Whirlpool_Offset] = CurrentPageLoc - (bVar1 < 0x10);
    Cannon_Y_Position_Or_Whirlpool_Length[Cannon_Or_Whirlpool_Offset] = (bVar2 + 2) * 0x10;
    Cannon_Or_Whirlpool_Offset += 1;
    if (4 < Cannon_Or_Whirlpool_Offset) {
      Cannon_Or_Whirlpool_Offset = 0;
    }
  }
  RenderUnderPart(HoleMetatiles[AreaType], 8, 0xf);
  return;
}

// SM2MAIN:79c6
// Signature: [A, X, Y] -> [X]
byte RenderUnderPart(byte param_1, byte param_2, byte param_3) {
  byte bVar1;

  do {
    bVar1 = MetatileBuffer[param_2];
    AreaObjectHeight = param_3;
    if ((bVar1 == 0) || (((bVar1 != 0x17 && (bVar1 != 0x8b)) && ((bVar1 == 0xc0 || (bVar1 < 0xc0)))))) {
      MetatileBuffer[param_2] = param_1;
    }
    param_2 += 1;
  } while ((param_2 < 0xd) && (param_3 = AreaObjectHeight - 1, param_3 < 0x80));
  return param_2;
}

// SM2MAIN:79ed
// Signature: [X] -> [Y, C, r07]
struct_ycr07 ChkLrgObjLength(byte param_1) {
  byte bVar1;
  byte bVar2;
  struct_ycr07 sVar3;
  struct_yr07i sVar4;

  sVar4 = GetLrgObjAttrib(param_1);
  bVar1 = sVar4.r07;
  bVar2 = sVar4.y;
  sVar3.c = ChkLrgObjFixedLength(param_1, bVar2);
  sVar3.y = bVar2;
  sVar3.r07 = bVar1;
  return sVar3;
}

// SM2MAIN:79f0
// Signature: [X, Y] -> [C]
bool ChkLrgObjFixedLength(byte param_1, byte param_2) {
  byte bVar1;

  bVar1 = AreaObjectLength[param_1];
  if (0x7f < bVar1) {
    AreaObjectLength[param_1] = param_2;
  }
  return 0x7f < bVar1;
}

// SM2MAIN:79fc
// Signature: [X] -> [Y, r07]
struct_yr07i GetLrgObjAttrib(byte param_1) {

  return CAST_INT_TO_struct_yr07i(
      CONCAT12(0, CONCAT11(AreaData[AreaObjOffsetBuffer[param_1]], AreaData[(byte)(AreaObjOffsetBuffer[param_1] + 1)]))
      & 0xff0f0f);
}

// SM2MAIN:7a0c
// Signature: [] -> [A]
byte GetAreaObjXPosition(void) { return CurrentColumnPos << 4; }

// SM2MAIN:7a14
// Signature: [r07] -> [A]
byte GetAreaObjYPosition(byte param_1) { return param_1 * 0x10 + 0x20; }

// SM2MAIN:7a22
// Signature: [A] -> [r06, r07]
struct_r06r07i GetBlockBufferAddr(byte param_1) {

  struct_r06r07i sVar1;

  sVar1.r07 = BlockBufferAddr[(param_1 >> 4) + 2];
  sVar1.r06 = (param_1 & 0xf) + BlockBufferAddr[param_1 >> 4];
  sVar1.i = (bool)0;
  return sVar1;
}

// SM2MAIN:7a37
// Signature: [] -> []
void GameModeSubs(void) {
  FUN_31e3(OperMode_Task);
  return;
}

// SM2MAIN:7a47
// Signature: [] -> []
void GameCoreRoutine(void) {
  byte bVar1;

  GameRoutines();
  if (OperMode_Task < 4) {
    return;
  }
  ProcFireball_Bubble();
  bVar1 = 0;
  do {
    ObjectOffset = bVar1;
    bVar1 = EnemiesAndLoopsCore(bVar1);
    bVar1 = FloateyNumbersRoutine(bVar1);
    bVar1 += 1;
  } while (bVar1 != 6);
  GetPlayerOffscreenBits();
  RelativePlayerPosition();
  PlayerGfxHandler();
  BlockObjMT_Updater();
  ObjectOffset = 1;
  bVar1 = BlockObjectsCore(1);
  ObjectOffset = bVar1 - 1;
  BlockObjectsCore(ObjectOffset);
  MiscObjectsCore();
  ProcessCannons();
  ProcessWhirlpools();
  FlagpoleRoutine();
  RunGameTimer();
  ColorRotation();
  if (FileListNumber != 0) {
    SimulateWind();
  }
  if (0x7f < (byte)(SprObject_Y_HighPos[0] - 2)) {
    if (StarInvincibleTimer == 0) {
      ResetPalStar();
      goto LAB_3587;
    }
    if ((StarInvincibleTimer == 4) && (IntervalTimerControl == 0)) {
      GetAreaMusic();
    }
  }
  bVar1 = FrameCounter;
  if (StarInvincibleTimer < 8) {
    bVar1 = FrameCounter >> 2;
  }
  CyclePlayerPalette(bVar1 >> 1);
LAB_3587:
  PreviousA_B_Buttons = A_B_Buttons;
  Left_Right_Buttons = 0;
  UpdScrollVar();
  return;
}

// SM2MAIN:7acb
// Signature: [] -> []
void UpdScrollVar(void) {
  if (VRAM_Buffer_AddrCtrl != 6) {
    if (AreaParserTaskNum == 0) {
      if (0x7f < (byte)(ScrollThirtyTwo - 0x20)) {
        return;
      }
      ScrollThirtyTwo = (ScrollThirtyTwo - 0x20) - (ScrollThirtyTwo < 0x20);
      VRAM_Buffer2_Offset = 0;
    }
    AreaParserTaskHandler();
  }
  return;
}

// SM2MAIN:7aef
// Signature: [] -> []
void ScrollHandler(void) {
  byte bVar1;

  Player_X_Scroll += Platform_X_Scroll;
  if ((((ScrollLock != 0) || (Player_Pos_ForScroll < 0x50)) || (SideCollisionTimer != 0))
      || (0x7f < (byte)(Player_X_Scroll - 1))) {
    ScrollAmount = 0;
    ChkPOffscr();
    return;
  }
  bVar1 = Player_X_Scroll;
  if (1 < Player_X_Scroll) {
    bVar1 = Player_X_Scroll - 1;
  }
  if (Player_Pos_ForScroll < 0x70) {
    ScrollScreen(bVar1);
    return;
  }
  ScrollScreen(Player_X_Scroll);
  return;
}

// SM2MAIN:7b58
// Signature: [] -> []
void ChkPOffscr(void) {
  byte bVar1;
  byte bVar2;

  bVar1 = GetXOffscreenBits(0);
  bVar2 = 0;
  if (((bool)(bVar1 >> 7)) || (bVar2 = 1, (bVar1 & 0x20) != 0)) {
    SprObject_X_Position[0] = ScreenEdgeOrLeft_X_Pos[bVar2] - X_SubtracterData[bVar2];
    SprObject_PageLoc[0]
        = ScreenEdgeOrLeft_PageLoc[bVar2] - (ScreenEdgeOrLeft_X_Pos[bVar2] < X_SubtracterData[bVar2]);
    if (Left_Right_Buttons != OffscrJoypadBitsData[bVar2]) {
      PlayerSpriteVarData1[0] = 0;
    }
  }
  Platform_X_Scroll = 0;
  return;
}

// SM2MAIN:7b90
// Signature: [] -> [A]
byte GetScreenPosition(void) {
  ScreenRight_X_Pos = ScreenEdgeOrLeft_X_Pos[0] - 1;
  ScreenRight_PageLoc = ScreenEdgeOrLeft_PageLoc[0] + (ScreenEdgeOrLeft_X_Pos[0] != 0);
  return ScreenRight_PageLoc;
}

// SM2MAIN:7ba2
// Signature: [] -> []
void GameRoutines(void) {
  FUN_31fb(GameEngineSubroutine);
  return;
}

// SM2MAIN:7bc1
// Signature: [] -> []
void PlayerEntrance(void) {
  byte bVar1;

  if (AltEntranceControl == 2) {
    if (JoypadOverride == 0) {
      MovePlayerYAxis(0xff);
      if (0x90 < SprObject_Y_Position[0]) {
        return;
      }
    } else {
      if (VineHeight != 0x60) {
        return;
      }
      DisableCollisionDet = 0x98 < SprObject_Y_Position[0];
      bVar1 = 1;
      if ((bool)DisableCollisionDet) {
        Player_State = 3;
        bVar1 = 8;
        Block_Buffer_1[180] = 8;
      }
      AutoControlPlayer(bVar1);
      if (SprObject_X_Position[0] < 0x48) {
        return;
      }
    }
  } else {
    if (SprObject_Y_Position[0] < 0x30) {
      AutoControlPlayer(0);
      return;
    }
    if ((PlayerEntranceCtrl == 6) || (PlayerEntranceCtrl == 7)) {
      if (Player_SprAttrib == 0) {
        AutoControlPlayer(1);
        return;
      }
      EnterSidePipe();
      ChangeAreaTimer -= 1;
      if (ChangeAreaTimer != 0) {
        return;
      }
      DisableIntermediate += 1;
      NextArea();
      return;
    }
  }
  JoypadOverride = 0;
  AltEntranceControl = 0;
  DisableCollisionDet = 0;
  PlayerFacingDir = 1;
  GameEngineSubroutine = 8;
  return;
}

// SM2MAIN:7c3e
// Signature: [A] -> []
void AutoControlPlayer(byte param_1) {
  SavedJoypadBits[0] = param_1;
  PlayerCtrlRoutine();
  return;
}

// SM2MAIN:7c41
// Signature: [] -> []
void PlayerCtrlRoutine(void) {
  char cVar1;
  char cVar2;
  byte bVar3;

  if (GameEngineSubroutine != 0xb) {
    if ((AreaType == 0) && ((SprObject_Y_HighPos[0] != 1 || (0xcf < SprObject_Y_Position[0])))) {
      SavedJoypadBits[0] = 0;
    }
    A_B_Buttons = SavedJoypadBits[0] & 0xc0;
    Left_Right_Buttons = SavedJoypadBits[0] & 3;
    Up_Down_Buttons = SavedJoypadBits[0] & 0xc;
    if ((((SavedJoypadBits[0] & 4) != 0) && (Player_State == 0)) && (Left_Right_Buttons != 0)) {
      Left_Right_Buttons = 0;
      Up_Down_Buttons = 0;
    }
  }
  PlayerMovementSubs();
  PlayerOrSprObj_BoundBoxCtrl[0] = 1;
  if ((PlayerSize == 0) && (PlayerOrSprObj_BoundBoxCtrl[0] = 0, CrouchingFlag != 0)) {
    PlayerOrSprObj_BoundBoxCtrl[0] = 2;
  }
  if ((PlayerSpriteVarData1[0] != 0) && (Player_MovingDir = 1, 0x7f < PlayerSpriteVarData1[0])) {
    Player_MovingDir = 2;
  }
  ScrollHandler();
  GetPlayerOffscreenBits();
  bVar3 = RelativePlayerPosition();
  BoundingBoxCore(0, bVar3);
  PlayerBGCollision();
  if ((((0x3f < SprObject_Y_Position[0]) && (GameEngineSubroutine != 5)) && (GameEngineSubroutine != 7))
      && (3 < GameEngineSubroutine)) {
    Player_SprAttrib &= 0xdf;
  }
  if ((byte)(SprObject_Y_HighPos[0] - 2) < 0x80) {
    ScrollLock = 1;
    cVar1 = 4;
    cVar2 = 0;
    if (((GameTimerExpiredFlag != 0) || (CloudTypeOverride == 0)) && (cVar2 = 1, GameEngineSubroutine != 0xb)) {
      if (DeathMusicLoaded == 0) {
        EventMusicQueue = 1;
        DeathMusicLoaded = 1;
      }
      cVar1 = 6;
    }
    if ((byte)(SprObject_Y_HighPos[0] - cVar1) < 0x80) {
      if (0x7f < (byte)(cVar2 - 1U)) {
        JoypadOverride = 0;
        SetEntr();
        AltEntranceControl = AltEntranceControl + 1;
        return;
      }
      if (EventMusicBuffer == 0) {
        GameEngineSubroutine = 6;
      }
    }
  }
  return;
}

// SM2MAIN:7d1f
// Signature: [] -> []
void Vine_AutoClimb(void) {
  if ((SprObject_Y_HighPos[0] == 0) && (SprObject_Y_Position[0] < 0xe4)) {
    SetEntr();
    return;
  }
  JoypadOverride = 8;
  Player_State = 3;
  AutoControlPlayer(8);
  return;
}

// SM2MAIN:7d35
// Signature: [] -> []
void SetEntr(void) {
  AltEntranceControl = 2;
  ChgAreaMode();
  return;
}

// SM2MAIN:7d3d
// Signature: [] -> []
void VerticalPipeEntry(void) {
  byte bVar1;

  MovePlayerYAxis(1);
  ScrollHandler();
  bVar1 = 0;
  if ((WarpZoneControl == 0) && (bVar1 = 1, AreaType == 3)) {
    bVar1 = 2;
  }
  ChangeAreaTimer -= 1;
  if (ChangeAreaTimer == 0) {
    AltEntranceControl = bVar1;
    ChgAreaMode();
    return;
  }
  return;
}

// SM2MAIN:7d58
// Signature: [A] -> []
void MovePlayerYAxis(byte param_1) {
  SprObject_Y_Position[0] = param_1 + SprObject_Y_Position[0];
  return;
}

// SM2MAIN:7d5e
// Signature: [] -> []
void SideExitPipeEntry(void) {
  EnterSidePipe();
  ChangeAreaTimer -= 1;
  if (ChangeAreaTimer == 0) {
    AltEntranceControl = 2;
    ChgAreaMode();
    return;
  }
  return;
}

// SM2MAIN:7d6b
// Signature: [] -> [A]
byte ChgAreaMode(void) {
  DisableScreenFlag = DisableScreenFlag + 1;
  OperMode_Task = 0;
  IRQUpdateFlag = 0;
  return 0;
}

// SM2MAIN:7d77
// Signature: [] -> []
void EnterSidePipe(void) {
  bool bVar1;

  PlayerSpriteVarData1[0] = 8;
  bVar1 = (SprObject_X_Position[0] & 0xf) == 0;
  if (bVar1) {
    PlayerSpriteVarData1[0] = 0;
  }
  AutoControlPlayer(!bVar1);
  return;
}

// SM2MAIN:7d8b
// Signature: [] -> []
void PlayerChangeSize(void) {
  if (TimerControl == 0xf8) {
    InitChangeSize();
    return;
  }
  if (TimerControl == 0xc4) {
    DonePlayerTask();
  }
  return;
}

// SM2MAIN:7d9d
// Signature: [] -> []
void PlayerInjuryBlink(void) {
  if (0xef < TimerControl) {
    if (TimerControl == 0xf0) {
      InitChangeSize();
      return;
    }
    return;
  }
  if (TimerControl == 200) {
    DonePlayerTask();
    return;
  }
  PlayerCtrlRoutine();
  return;
}

// SM2MAIN:7dad
// Signature: [] -> []
void InitChangeSize(void) {
  if (PlayerChangeSizeFlag == 0) {
    PlayerAnimCtrl = PlayerChangeSizeFlag;
    PlayerChangeSizeFlag = 1;
    PlayerSize ^= 1;
  }
  return;
}

// SM2MAIN:7dc1
// Signature: [] -> []
void PlayerDeath(void) {
  if (TimerControl < 0xf0) {
    PlayerCtrlRoutine();
    return;
  }
  return;
}

// SM2MAIN:7dcb
// Signature: [] -> []
void DonePlayerTask(void) {
  TimerControl = 0;
  GameEngineSubroutine = 8;
  return;
}

// SM2MAIN:7dd5
// Signature: [] -> []
void PlayerFireFlower(void) {
  if (TimerControl != 0xc0) {
    CyclePlayerPalette(FrameCounter >> 2);
    return;
  }
  DonePlayerTask();
  ResetPalStar();
  return;
}

// SM2MAIN:7de0
// Signature: [A] -> []
void CyclePlayerPalette(byte param_1) {
  Player_SprAttrib = Player_SprAttrib & 0xfc | param_1 & 3;
  return;
}

// SM2MAIN:7df2
// Signature: [] -> []
void ResetPalStar(void) {
  Player_SprAttrib = Player_SprAttrib & 0xfc;
  return;
}

// SM2MAIN:7dfb
// Signature: [] -> []
void FlagpoleSlide(void) {
  byte bVar1;

  if (Enemy_ID[5] == 0x30) {
    Square1SoundQueue = FlagpoleSoundQueue;
    bVar1 = 0;
    FlagpoleSoundQueue = 0;
    if (SprObject_Y_Position[0] < 0x9e) {
      bVar1 = 4;
    }
    AutoControlPlayer(bVar1);
    return;
  }
  GameEngineSubroutine = GameEngineSubroutine + 1;
  return;
}

// SM2MAIN:7e19
// Signature: [] -> []
void PlayerEndLevel(void) {
  AutoControlPlayer(1);
  if ((0xad < SprObject_Y_Position[0]) && (ScrollLock = 0, FlagpoleMusicFlag == 0)) {
    EventMusicQueue = 0x20;
    FlagpoleMusicFlag = 1;
  }
  if (!(bool)(Player_CollisionBits & 1)) {
    if (StarFlagTaskControl == 0) {
      StarFlagTaskControl = 1;
    }
    Player_SprAttrib = 0x20;
  }
  if (StarFlagTaskControl != 5) {
    return;
  }
  LevelNumber += 1;
  if (LevelNumber != 3) {
    NextArea();
    return;
  }
  if (CoinTallyFor1Ups < 10) {
    NextArea();
    return;
  }
  Hidden1UpFlag += 1;
  NextArea();
  return;
}

// SM2MAIN:7e66
// Signature: [] -> []
void NextArea(void) {
  AreaNumber += 1;
  if ((WorldNumber == 8) && (LevelNumber == 4)) {
    LevelNumber = 0;
    AreaNumber = 0;
  }
  LoadAreaPointer();
  FetchNewGameTimerFlag += 1;
  HalfwayPage = ChgAreaMode();
  EventMusicQueue = 0x80;
  return;
}

// SM2MAIN:7e90
// Signature: [] -> []
void PlayerMovementSubs(void) {
  byte bVar1;

  bVar1 = 0;
  if ((PlayerSize == 0) && (bVar1 = CrouchingFlag, Player_State == 0)) {
    bVar1 = Up_Down_Buttons & 4;
  }
  CrouchingFlag = bVar1;
  PlayerPhysicsSub();
  if (PlayerChangeSizeFlag != 0) {
    return;
  }
  if (Player_State != 3) {
    ClimbSideTimer = 0x18;
  }
  FUN_3233(Player_State);
  return;
}

// SM2MAIN:7ec1
// Signature: [] -> []
void OnGroundStateSub(void) {
  GetPlayerAnimSpeed();
  if (Left_Right_Buttons != 0) {
    PlayerFacingDir = Left_Right_Buttons;
  }
  ImposeFriction(Left_Right_Buttons);
  JmpMove();
  return;
}

// SM2MAIN:7ecd
// Signature: [] -> []
void JmpMove(void) {
  Player_X_Scroll = MovePlayerHorizontally();
  if (FileListNumber != 0) {
    BlowPlayerAround();
  }
  return;
}

// SM2MAIN:7edc
// Signature: [] -> []
void FallingSub(void) {
  VerticalForce = VerticalForceDown;
  LRAir();
  return;
}

// SM2MAIN:7ee5
// Signature: [] -> []
void JumpSwimSub(void) {
  if ((PlayerSpriteVarData2[0] < 0x80)
      || (((A_B_Buttons & 0x80 & PreviousA_B_Buttons) == 0
           && (DiffToHaltJump <= (byte)(JumpOrigin_Y_Position - SprObject_Y_Position[0]))))) {
    VerticalForce = VerticalForceDown;
  }
  if (SwimmingFlag == 0) {
    LRAir();
    return;
  }
  GetPlayerAnimSpeed();
  if (SprObject_Y_Position[0] < 0x14) {
    VerticalForce = 0x18;
  }
  if (Left_Right_Buttons == 0) {
    LRAir();
    return;
  }
  PlayerFacingDir = Left_Right_Buttons;
  LRAir();
  return;
}

// SM2MAIN:7f1b
// Signature: [] -> []
void LRAir(void) {
  if (Left_Right_Buttons != 0) {
    ImposeFriction(Left_Right_Buttons);
  }
  JmpMove();
  if (GameEngineSubroutine == 0xb) {
    VerticalForce = 0x28;
  }
  MovePlayerVertically();
  return;
}

// SM2MAIN:7f3b
// Signature: [] -> []
void ClimbingSub(void) {
  bool bVar1;
  bool bVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;

  bVar1 = CARRY1(SprObject_YMF_Dummy[0], SprObject_Y_MoveForce[0]);
  SprObject_YMF_Dummy[0] = SprObject_YMF_Dummy[0] + SprObject_Y_MoveForce[0];
  cVar5 = 0;
  if (0x7f < PlayerSpriteVarData2[0]) {
    cVar5 = -1;
  }
  bVar3 = PlayerSpriteVarData2[0] + SprObject_Y_Position[0] + bVar1;
  bVar2 = CARRY1(PlayerSpriteVarData2[0], SprObject_Y_Position[0]);
  SprObject_Y_Position[0] = bVar3;
  SprObject_Y_HighPos[0] = SprObject_Y_HighPos[0] + cVar5 + (bVar2 || bVar1 && bVar3 == 0);
  bVar3 = Left_Right_Buttons & Player_CollisionBits;
  if (bVar3 != 0) {
    if (ClimbSideTimer == 0) {
      ClimbSideTimer = 0x18;
      bVar4 = 0;
      if (!(bool)(bVar3 & 1)) {
        bVar4 = 2;
      }
      if (PlayerFacingDir != 1) {
        bVar4 += 1;
      }
      SprObject_PageLoc[0] = SprObject_PageLoc[0] + ClimbAdderHigh[bVar4]
                                     + CARRY1(SprObject_X_Position[0], ClimbAdderLow[bVar4]);
      PlayerFacingDir = Left_Right_Buttons ^ 3;
      SprObject_X_Position[0] = SprObject_X_Position[0] + ClimbAdderLow[bVar4];
    }
    return;
  }
  ClimbSideTimer = bVar3;
  return;
}

// SM2MAIN:7fbc
// Signature: [] -> []
void PlayerPhysicsSub(void) {
  byte bVar1;
  byte bVar2;

  if (Player_State == 3) {
    bVar1 = 0;
    if (((Up_Down_Buttons & Player_CollisionBits) != 0)
        && (bVar1 = 1, (Up_Down_Buttons & Player_CollisionBits & 8) == 0)) {
      bVar1 = 2;
    }
    SprObject_Y_MoveForce[0] = Climb_Y_MForceData[bVar1];
    PlayerAnimTimerSet = 8;
    PlayerSpriteVarData2[0] = Climb_Y_SpeedData[bVar1];
    if (Climb_Y_SpeedData[bVar1] < 0x80) {
      PlayerAnimTimerSet = 4;
    }
    return;
  }
  if ((((JumpspringAnimCtrl == 0) && ((A_B_Buttons & 0x80) != 0)) && ((A_B_Buttons & 0x80 & PreviousA_B_Buttons) == 0))
      && ((Player_State == 0 || ((SwimmingFlag != 0 && ((JumpSwimTimer != 0 || (PlayerSpriteVarData2[0] < 0x80)))))))) {
    JumpSwimTimer = 0x20;
    bVar1 = 0;
    SprObject_YMF_Dummy[0] = 0;
    JumpOrigin_Y_HighPos = SprObject_Y_HighPos[0];
    JumpOrigin_Y_Position = SprObject_Y_Position[0];
    Player_State = 1;
    if ((8 < Player_XSpeedAbsolute)
        && (((bVar1 = 1, 0xf < Player_XSpeedAbsolute && (bVar1 = 2, 0x18 < Player_XSpeedAbsolute))
             && (bVar1 = 3, 0x1b < Player_XSpeedAbsolute)))) {
      bVar1 = 4;
    }
    DiffToHaltJump = 1;
    if ((SwimmingFlag != 0) && (bVar1 = 5, Cannon_Timer_Or_Whirlpool_Flag[0] != 0)) {
      bVar1 = 6;
    }
    VerticalForce = JumpMForceData[bVar1];
    VerticalForceDown = FallMForceData[bVar1];
    SprObject_Y_MoveForce[0] = InitMForceData[bVar1];
    PlayerSpriteVarData2[0] = PlayerYSpdData[bVar1];
    if (SwimmingFlag == 0) {
      Square1SoundQueue = 1;
      if (PlayerSize != 0) {
        Square1SoundQueue = 0x80;
      }
    } else {
      Square1SoundQueue = 4;
      if (SprObject_Y_Position[0] < 0x14) {
        PlayerSpriteVarData2[0] = 0;
      }
    }
  }
  bVar2 = 0;
  bVar1 = 0;
  if (Player_State == 0) {
ProcPRun:
    bVar2 = 1;
    if ((AreaType != 0) && (bVar2 = 0, Left_Right_Buttons == Player_MovingDir)) {
      if ((A_B_Buttons & 0x40) != 0) {
        RunningTimer = 10;
        goto GetXPhy;
      }
      if (RunningTimer != 0) {
        goto GetXPhy;
      }
    }
  } else {
    if (0x18 < Player_XSpeedAbsolute) {
      goto GetXPhy;
    }
    if (0x18 < Player_XSpeedAbsolute) {
      goto ProcPRun;
    }
  }
  bVar2 += 1;
  bVar1 = 1;
  if ((RunningSpeed != 0) || (0x20 < Player_XSpeedAbsolute)) {
    bVar1 = 2;
  }
GetXPhy:
  MaximumLeftSpeed = MaxLeftXSpdData[bVar2];
  if (GameEngineSubroutine == 7) {
    bVar2 = 3;
  }
  MaximumRightSpeed = MaxRightXSpdData[bVar2];
  FrictionAdderLow = FrictionData[bVar1];
  FrictionAdderHigh = 0;
  if (PlayerFacingDir != Player_MovingDir) {
    if (RAM(0xb585) == 0x60) {
      return;
    }
    FrictionAdderHigh = FrictionAdderLow >> 7;
    FrictionAdderLow <<= 1;
  }
  return;
}

// SM2MAIN:80fb
// Signature: [] -> []
void GetPlayerAnimSpeed(void) {
  byte bVar1;
  byte bVar2;

  bVar2 = 0;
  bVar1 = Player_XSpeedAbsolute;
  if (Player_XSpeedAbsolute < 0x1c) {
    bVar2 = 1;
    if (Player_XSpeedAbsolute < 0xe) {
      bVar2 = 2;
    }
    bVar1 = RunningSpeed;
    if ((SavedJoypadBits[0] & 0x7f) != 0) {
      if ((SavedJoypadBits[0] & 3) == Player_MovingDir) {
        bVar1 = 0;
      } else if (Player_XSpeedAbsolute < 0xb) {
        Player_MovingDir = PlayerFacingDir;
        PlayerSpriteVarData1[0] = 0;
        Player_X_MoveForce = 0;
      }
    }
  }
  RunningSpeed = bVar1;
  PlayerAnimTimerSet = PlayerAnimTmrData[bVar2];
  return;
}

// SM2MAIN:8138
// Signature: [A] -> []
void ImposeFriction(byte param_1) {
  byte bVar1;

  bVar1 = param_1 & Player_CollisionBits;
  if ((param_1 & Player_CollisionBits) == 0) {
    if (PlayerSpriteVarData1[0] == 0) {
      Player_XSpeedAbsolute = PlayerSpriteVarData1[0];
      return;
    }
    if (PlayerSpriteVarData1[0] < 0x80) {
      goto RghtFrict;
    }
    bVar1 = PlayerSpriteVarData1[0];
    if (PlayerSpriteVarData1[0] < 0x80) {
      goto JoypFrict;
    }
  } else {
JoypFrict:
    if ((bVar1 & 1) == 0) {
RghtFrict:
      bVar1 = Player_X_MoveForce - FrictionAdderLow;
      PlayerSpriteVarData1[0] = (PlayerSpriteVarData1[0] - FrictionAdderHigh) - (Player_X_MoveForce < FrictionAdderLow);
      Player_X_MoveForce = bVar1;
      if (0x7f < (byte)(PlayerSpriteVarData1[0] - MaximumLeftSpeed)) {
        PlayerSpriteVarData1[0] = MaximumLeftSpeed;
      }
      goto XSpdSign;
    }
  }
  bVar1 = Player_X_MoveForce + FrictionAdderLow;
  PlayerSpriteVarData1[0] = PlayerSpriteVarData1[0] + FrictionAdderHigh + CARRY1(Player_X_MoveForce, FrictionAdderLow);
  Player_X_MoveForce = bVar1;
  if ((byte)(PlayerSpriteVarData1[0] - MaximumRightSpeed) < 0x80) {
    PlayerSpriteVarData1[0] = MaximumRightSpeed;
    Player_XSpeedAbsolute = MaximumRightSpeed;
    return;
  }
XSpdSign:
  Player_XSpeedAbsolute = PlayerSpriteVarData1[0];
  if (0x7f < PlayerSpriteVarData1[0]) {
    Player_XSpeedAbsolute = (PlayerSpriteVarData1[0] ^ 0xff) + 1;
  }
  return;
}

// SM2MAIN:8190
// Signature: [] -> []
void ProcFireball_Bubble(void) {
  byte bVar1;

  if (1 < PlayerStatus) {
    if (((((A_B_Buttons & 0x40) != 0) && ((A_B_Buttons & 0x40 & PreviousA_B_Buttons) == 0))
         && (Fireball_State[FireballCounter & 1] == 0))
        && (((SprObject_Y_HighPos[0] == 1 && (CrouchingFlag == 0)) && (Player_State != 3)))) {
      Square1SoundQueue = 0x20;
      Fireball_State[FireballCounter & 1] = 2;
      FireballThrowingTimer = PlayerAnimTimerSet;
      PlayerAnimTimer = PlayerAnimTimerSet - 1;
      FireballCounter += 1;
    }
    FireballObjCore(0);
    FireballObjCore(1);
  }
  if (AreaType == 0) {
    bVar1 = 2;
    do {
      ObjectOffset = bVar1;
      BubbleCheck(bVar1);
      bVar1 = RelativeBubblePosition(bVar1);
      bVar1 = GetBubbleOffscreenBits(bVar1);
      DrawBubble(bVar1);
      bVar1 -= 1;
    } while (bVar1 < 0x80);
  }
  return;
}

// SM2MAIN:81f5
// Signature: [X] -> []
void FireballObjCore(byte param_1) {
  bool bVar1;
  byte in_r01 = 0;
  byte bVar2;
  bool bVar3;

  bVar3 = (bool)-((char)Fireball_State[param_1] >> 7);
  ObjectOffset = param_1;
  if (bVar3) {
    bVar2 = RelativeFireballPosition(param_1);
    DrawExplosion_Fireball(bVar2);
    return;
  }
  if (Fireball_State[param_1] != 0) {
    if (Fireball_State[param_1] != 1) {
      bVar2 = SprObject_X_Position[0] + 4 + bVar3;
      bVar1 = 0xfb < SprObject_X_Position[0];
      Fireball_X_Position[param_1] = bVar2;
      Fireball_PageLoc[param_1] = SprObject_PageLoc[0] + (bVar1 || bVar3 && bVar2 == 0);
      Fireball_Y_Position[param_1] = SprObject_Y_Position[0];
      Fireball_Y_HighPos[param_1] = 1;
      Fireball_X_Speed[param_1] = FireballXSpdData[(byte)(PlayerFacingDir - 1)];
      Fireball_Y_Speed[param_1] = 4;
      Fireball_BoundBoxCtrl[param_1] = 7;
      Fireball_State[param_1] = Fireball_State[param_1] - 1;
    }
    bVar2 = param_1 + 7;
    ImposeGravity(0, bVar2, 0x50, in_r01, 3);
    MoveObjectHorizontally(bVar2);
    bVar2 = RelativeFireballPosition(ObjectOffset);
    bVar2 = GetFireballOffscreenBits(bVar2);
    bVar2 = GetFireballBoundBox(bVar2);
    bVar2 = FireballBGCollision(bVar2);
    if ((FBall_OffscreenBits & 0xcc) == 0) {
      bVar2 = FireballEnemyCollision(bVar2);
      DrawFireball(bVar2);
      return;
    }
    Fireball_State[bVar2] = 0;
  }
  return;
}

// SM2MAIN:8265
// Signature: [X] -> []
void BubbleCheck(byte param_1) {
  if (Bubble_Y_Position[param_1] != 0xf8) {
    MoveBubl(param_1, PseudoRandomBitReg[param_1 + 1] & 1);
    return;
  }
  if (AirBubbleTimer == 0) {
    SetupBubble(param_1, PseudoRandomBitReg[param_1 + 1] & 1);
    return;
  }
  return;
}

// SM2MAIN:8277
// Signature: [X, r07] -> []
void SetupBubble(byte param_1, byte param_2) {
  bool bVar1;
  byte bVar2;
  byte bVar3;
  bool bVar4;

  bVar3 = 0;
  bVar4 = (bool)(PlayerFacingDir & 1);
  if (bVar4 != false) {
    bVar3 = 8;
  }
  bVar2 = bVar3 + SprObject_X_Position[0] + bVar4;
  bVar1 = CARRY1(bVar3, SprObject_X_Position[0]);
  Bubble_X_Position[param_1] = bVar2;
  Bubble_PageLoc[param_1] = SprObject_PageLoc[0] + (bVar1 || bVar4 && bVar2 == 0);
  Bubble_Y_Position[param_1] = SprObject_Y_Position[0] + 8;
  Bubble_Y_HighPos[param_1] = 1;
  AirBubbleTimer = BubbleTimerData[param_2];
  MoveBubl(param_1, param_2);
  return;
}

// SM2MAIN:829e
// Signature: [X, r07] -> []
void MoveBubl(byte param_1, byte param_2) {
  byte bVar1;
  byte bVar2;

  bVar2 = Bubble_YMF_Dummy[param_1];
  bVar1 = Bubble_MForceData[param_2];
  Bubble_YMF_Dummy[param_1] = bVar2 - bVar1;
  bVar2 = Bubble_Y_Position[param_1] - (bVar2 < bVar1);
  if (bVar2 < 0x20) {
    bVar2 = 0xf8;
  }
  Bubble_Y_Position[param_1] = bVar2;
  return;
}

// SM2MAIN:82bb
// Signature: [] -> []
void RunGameTimer(void) {
  byte bVar1;

  if ((((OperMode != 0) && (7 < GameEngineSubroutine)) && (GameEngineSubroutine != 0xb))
      && ((0x7f < (byte)(SprObject_Y_HighPos[0] - 2) && (GameTimerCtrlTimer == 0)))) {
    bVar1 = GameTimerDisplaySMB2J[0] | GameTimerDisplaySMB2J[1] | GameTimerDisplaySMB2J[2];
    if (bVar1 != 0) {
      if ((GameTimerDisplaySMB2J[0] == 1) && ((GameTimerDisplaySMB2J[1] | GameTimerDisplaySMB2J[2]) == 0)) {
        EventMusicQueue = 0x40;
      }
      GameTimerCtrlTimer = 0x18;
      DigitModifier[5] = 0xff;
      DigitsMathRoutine(0x17);
      PrintStatusBarNumbers(0xa2);
      return;
    }
    PlayerStatus = bVar1;
    ForceInjury(0);
    GameTimerExpiredFlag += 1;
  }
  return;
}

// SM2MAIN:8310
// Signature: [X] -> []
void WarpZoneObject(byte param_1) {
  if ((ScrollLock != 0) && ((SprObject_Y_Position[0] & SprObject_Y_HighPos[0]) == 0)) {
    ScrollLock = SprObject_Y_Position[0] & SprObject_Y_HighPos[0];
    EraseEnemyObject(param_1);
    return;
  }
  return;
}

// SM2MAIN:8321
// Signature: [] -> []
void ProcessWhirlpools(void) {
  byte bVar1;
  char cVar2;
  byte bVar3;

  if ((AreaType == 0) && (Cannon_Timer_Or_Whirlpool_Flag[0] = AreaType, TimerControl == 0)) {
    bVar3 = 4;
    do {
      if (((Cannon_Or_Whirlpool_PageLoc[bVar3] != 0)
           && ((byte)((SprObject_PageLoc[0] - Cannon_Or_Whirlpool_PageLoc[bVar3])
                      - (SprObject_X_Position[0] < Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar3]))
               < 0x80))
          && ((byte)(((Cannon_Or_Whirlpool_PageLoc[bVar3]
                       + CARRY1(Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar3],
                                Cannon_Y_Position_Or_Whirlpool_Length[bVar3]))
                      - SprObject_PageLoc[0])
                     - ((byte)(Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar3]
                               + Cannon_Y_Position_Or_Whirlpool_Length[bVar3])
                        < SprObject_X_Position[0]))
              < 0x80)) {
        bVar1 = Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar3] + (Cannon_Y_Position_Or_Whirlpool_Length[bVar3] >> 1);
        if ((FrameCounter & 1) != 0) {
          if ((byte)(((Cannon_Or_Whirlpool_PageLoc[bVar3]
                       + CARRY1(Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar3],
                                Cannon_Y_Position_Or_Whirlpool_Length[bVar3] >> 1))
                      - SprObject_PageLoc[0])
                     - (bVar1 < SprObject_X_Position[0]))
              < 0x80) {
            if ((Player_CollisionBits & 1) == 0) {
              goto WhPull;
            }
            cVar2 = 0xfe < SprObject_X_Position[0];
            SprObject_X_Position[0] = SprObject_X_Position[0] + 1;
          } else {
            cVar2 = -(SprObject_X_Position[0] == 0);
            SprObject_X_Position[0] = SprObject_X_Position[0] - 1;
          }
          SprObject_PageLoc[0] += cVar2;
        }
WhPull:
        Cannon_Timer_Or_Whirlpool_Flag[0] = 1;
        ImposeGravity(0, 0, 0x10, bVar1, 1);
        return;
      }
      bVar3 -= 1;
    } while (bVar3 < 0x80);
  }
  return;
}

// SM2MAIN:83be
// Signature: [] -> []
void FlagpoleRoutine(void) {
  byte bVar1;
  byte bVar2;
  bool bVar3;
  struct_xyi sVar4;
  struct_axr00 sVar5;

  bVar2 = 5;
  ObjectOffset = 5;
  if (Enemy_ID[5] == 0x30) {
    if ((GameEngineSubroutine == 4) && (Player_State == 3)) {
      if ((0xa9 < Enemy_Y_Position[5]) || (bVar3 = 0xa1 < SprObject_Y_Position[0], bVar3)) {
        if (FlagpoleScore == 5) {
          NumberofLives += 1;
          Square2SoundQueue = 0x40;
        } else {
          DigitModifier[FlagpoleScoreDigits[FlagpoleScore]] = FlagpoleScoreMods[FlagpoleScore];
          bVar2 = AddToScore();
        }
        GameEngineSubroutine = 5;
      } else {
        bVar1 = (BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[5] - 1) + bVar3;
        Enemy_Y_Position[5]
            = Enemy_Y_Position[5] + 1
              + (BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[5] != 0 || bVar3 && bVar1 == 0);
        FlagpoleFNum_Y_Pos = (FlagpoleFNum_Y_Pos - 1) - (FlagpoleFNum_YMFDummy != 0xff);
        FlagpoleFNum_YMFDummy = FlagpoleFNum_YMFDummy + 1;
        BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[5] = bVar1;
      }
    }
    sVar4 = GetEnemyOffscreenBits(bVar2);
    sVar5 = RelativeEnemyPosition(sVar4.x);
    FlagpoleGfxHandler(sVar5.x);
  }
  return;
}

// SM2MAIN:8431
// Signature: [X] -> [X]
byte JumpspringHandler(byte param_1) {
  byte bVar1;
  byte bVar2;
  struct_xyi sVar3;
  struct_axr00 sVar4;

  sVar3 = GetEnemyOffscreenBits(param_1);
  bVar1 = sVar3.x;
  if ((TimerControl == 0) && (JumpspringAnimCtrl != 0)) {
    bVar2 = JumpspringAnimCtrl - 1;
    if ((bVar2 & 2) == 0) {
      SprObject_Y_Position[0] += 2;
    } else {
      SprObject_Y_Position[0] -= 2;
    }
    Enemy_Y_Position[bVar1] = SpriteVarData1[bVar1] + Jumpspring_Y_PosData[bVar2];
    if ((((bVar2 != 0) && ((A_B_Buttons & 0x80) != 0)) && ((A_B_Buttons & 0x80 & PreviousA_B_Buttons) == 0))
        && (((JumpspringForce = 0xf4, WorldNumber == 1 || (WorldNumber == 2)) || (WorldNumber == 6)))) {
      JumpspringForce = 0xe0;
    }
    if (bVar2 == 3) {
      PlayerSpriteVarData2[0] = JumpspringForce;
      JumpspringAnimCtrl = 0;
    }
  }
  sVar4 = RelativeEnemyPosition(bVar1);
  bVar1 = EnemyGfxHandler(sVar4.x);
  OffscreenBoundsCheck(bVar1);
  if ((JumpspringAnimCtrl != 0) && (JumpspringTimer == 0)) {
    JumpspringTimer = 4;
    JumpspringAnimCtrl += 1;
  }
  return bVar1;
}

// SM2MAIN:84aa
// Signature: [X, Y] -> []
void Setup_Vine(byte param_1, byte param_2) {
  byte bVar1;

  Enemy_ID[param_1] = 0x2f;
  Enemy_Flag[param_1] = 1;
  Enemy_PageLoc[param_1] = Block_PageLoc[param_2];
  Enemy_X_Position[param_1] = Block_X_Position[param_2];
  bVar1 = Block_Y_Position[param_2];
  Enemy_Y_Position[param_1] = bVar1;
  if (VineFlagOffset == 0) {
    VineStart_Y_Position = bVar1;
  }
  VineObjOffset[VineFlagOffset] = param_1;
  VineFlagOffset = VineFlagOffset + 1;
  Square2SoundQueue = 4;
  return;
}

// SM2MAIN:84d7
// Signature: [X] -> [X]
byte VineObjectHandler(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  bool bVar4;
  struct_axr00 sVar5;
  struct_azr02r04r06r07 sVar6;

  if (param_1 == 5) {
    if ((VineHeight != VineHeightData[(byte)(VineFlagOffset - 1)])
        && (bVar4 = (bool)(FrameCounter >> 1 & 1), bVar4 != false)) {
      Enemy_Y_Position[5] = (Enemy_Y_Position[5] - 1) - !bVar4;
      VineHeight += 1;
    }
    if (7 < VineHeight) {
      sVar5 = RelativeEnemyPosition(5);
      GetEnemyOffscreenBits(sVar5.x);
      bVar1 = 0;
      do {
        bVar3 = bVar1;
        DrawVine(bVar3);
        bVar1 = bVar3 + 1;
      } while ((byte)(bVar3 + 1) != VineFlagOffset);
      bVar1 = VineFlagOffset;
      bVar2 = VineHeight;
      if ((Enemy_OffscreenBits & 0xc) != 0) {
        do {
          bVar1 = EraseEnemyObject(VineObjOffset[bVar3]);
          bVar3 -= 1;
          bVar2 = bVar1;
        } while (bVar3 < 0x80);
      }
      VineHeight = bVar2;
      VineFlagOffset = bVar1;
      if (0x1f < VineHeight) {
        sVar6 = BlockBufferCollision(1, 6, 0x1b);
        bVar1 = sVar6.r02;
        if ((bVar1 < 0xd0) && (RAM(SUBPIECE(sVar6, 4, 2) + (ushort)bVar1) == 0)) {
          RAM(SUBPIECE(sVar6, 4, 2) + (ushort)bVar1) = 0x23;
        }
      }
    }
    if ((0x7f
         < (byte)((Enemy_PageLoc[5] - ScreenEdgeOrLeft_PageLoc[0]) - (Enemy_X_Position[5] < ScreenEdgeOrLeft_X_Pos[0])))
        || ((byte)(Enemy_X_Position[5] - ScreenEdgeOrLeft_X_Pos[0]) < 9)) {
      Enemy_Flag[5] = 0;
      bVar1 = BlockBufferAddr[Enemy_PageLoc[5] & 1];
      bVar3 = BlockBufferAddr[(Enemy_PageLoc[5] & 1) + 2];
      bVar2 = Enemy_X_Position[5] >> 4;
      do {
        if (RAM(CONCAT11(bVar3, bVar1) + (ushort)bVar2) == 0x23) {
          RAM(CONCAT11(bVar3, bVar1) + (ushort)bVar2) = 0;
        }
        bVar2 += 0x10;
      } while (bVar2 < 0xd0);
    }
    return ObjectOffset;
  }
  return param_1;
}

// SM2MAIN:8587
// Signature: [] -> []
void ProcessCannons(void) {
  byte bVar1;
  byte bVar2;
  struct_xyi sVar3;

  if (AreaType != 0) {
    bVar2 = 2;
    do {
      ObjectOffset = bVar2;
      if (Enemy_Flag[bVar2] == 0) {
        bVar1 = PseudoRandomBitReg[bVar2 + 1] & CannonBitmasks[SecondaryHardMode];
        if ((5 < bVar1) || (Cannon_Or_Whirlpool_PageLoc[bVar1] == 0)) {
          goto Chk_BB;
        }
        if (Cannon_Timer_Or_Whirlpool_Flag[bVar1] != 0) {
          Cannon_Timer_Or_Whirlpool_Flag[bVar1] = Cannon_Timer_Or_Whirlpool_Flag[bVar1] - (5 >= bVar1);
          goto Chk_BB;
        }
        if (TimerControl != 0) {
          goto Chk_BB;
        }
        Cannon_Timer_Or_Whirlpool_Flag[bVar1] = 0xe;
        Enemy_PageLoc[bVar2] = Cannon_Or_Whirlpool_PageLoc[bVar1];
        Enemy_X_Position[bVar2] = Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar1];
        Enemy_Y_Position[bVar2] = Cannon_Y_Position_Or_Whirlpool_Length[bVar1] - 8;
        Enemy_Y_HighPos[bVar2] = 1;
        Enemy_Flag[bVar2] = 1;
        Enemy_State[bVar2] = 0;
        Enemy_BoundBoxCtrl[bVar2] = 9;
        Enemy_ID[bVar2] = 0x33;
      } else {
Chk_BB:
        if (Enemy_ID[bVar2] == 0x33) {
          OffscreenBoundsCheck(bVar2);
          if (Enemy_Flag[bVar2] != 0) {
            sVar3 = GetEnemyOffscreenBits(bVar2);
            bVar2 = BulletBillHandler(sVar3.x);
          }
        }
      }
      bVar2 -= 1;
    } while (bVar2 < 0x80);
  }
  return;
}

// SM2MAIN:85fe
// Signature: [X] -> [X]
byte BulletBillHandler(byte param_1) {
  byte bVar1;
  struct_ncr00 sVar2;
  struct_axi sVar3;
  struct_xyi sVar4;
  struct_axr00 sVar5;

  if (TimerControl == 0) {
    if (Enemy_State[param_1] == 0) {
      if ((Enemy_OffscreenBits & 0xc) == 0xc) {
KillBB:
        EraseEnemyObject(param_1);
        return param_1;
      }
      bVar1 = 1;
      sVar2 = PlayerEnemyDiff(param_1);
      if (!sVar2.n) {
        bVar1 += 1;
      }
      Enemy_MovingDir[param_1] = bVar1;
      SpriteVarData1[param_1] = BulletBillXSpdData[(byte)(bVar1 - 1)];
      if ((byte)(sVar2.r00 + 0x28 + sVar2.c) < 0x50) {
        goto KillBB;
      }
      Enemy_State[param_1] = 1;
      EnemyFrameTimer[param_1] = 10;
      Square2SoundQueue = 8;
    }
    if ((Enemy_State[param_1] & 0x20) != 0) {
      param_1 = MoveD_EnemyVertically(param_1);
    }
    sVar3 = MoveEnemyHorizontally(param_1);
    param_1 = sVar3.x;
  }
  sVar4 = GetEnemyOffscreenBits(param_1);
  sVar5 = RelativeEnemyPosition(sVar4.x);
  bVar1 = GetEnemyBoundBox(sVar5.x);
  bVar1 = PlayerEnemyCollision(bVar1);
  bVar1 = EnemyGfxHandler(bVar1);
  return bVar1;
}

// SM2MAIN:865f
// Signature: [] -> [X, C]
struct_xci SpawnHammerObj(void) {
  byte bVar1;
  byte bVar2;

  struct_xci sVar3;
  struct_xci sVar4;

  bVar1 = ObjectOffset;
  bVar2 = PseudoRandomBitReg[1] & 7;
  if (bVar2 == 0) {
    bVar2 = PseudoRandomBitReg[1] & 8;
  }
  if ((Misc_State[bVar2] == 0) && (Enemy_Flag[HammerEnemyOfsData[bVar2]] == 0)) {
    HammerEnemyOffset[bVar2] = ObjectOffset;
    Misc_State[bVar2] = 0x90;
    Misc_BoundBoxCtrl[bVar2] = 7;
    sVar3.c = true;
    sVar3.x = bVar1;
    sVar3.i = (bool)0;
    return sVar3;
  }
  sVar4.c = false;
  sVar4.x = ObjectOffset;
  sVar4.i = (bool)0;
  return sVar4;
}

// SM2MAIN:868e
// Signature: [X] -> [X]
byte ProcHammerObj(byte param_1) {
  byte bVar1;
  byte bVar2;

  if (TimerControl == 0) {
    bVar2 = HammerEnemyOffset[param_1];
    if ((Misc_State[param_1] & 0x7f) == 2) {
      Misc_Y_Speed[param_1] = 0xfe;
      Enemy_State[bVar2] = Enemy_State[bVar2] & 0xf7;
      param_1 = ObjectOffset;
      Misc_X_Speed[ObjectOffset] = HammerXSpdData[(byte)(Enemy_MovingDir[bVar2] - 1)];
    } else if ((Misc_State[param_1] & 0x7f) < 2) {
      bVar2 = param_1 + 0xd;
      ImposeGravity(0, bVar2, 0x10, 0xf, 4);
      MoveObjectHorizontally(bVar2);
      param_1 = PlayerHammerCollision(ObjectOffset);
      goto RunHSubs;
    }
    Misc_State[param_1] = Misc_State[param_1] - 1;
    bVar1 = Enemy_X_Position[bVar2];
    Misc_X_Position[param_1] = bVar1 + 2;
    Misc_PageLoc[param_1] = Enemy_PageLoc[bVar2] + (0xfd < bVar1);
    Misc_Y_Position[param_1] = Enemy_Y_Position[bVar2] - 10;
    Misc_Y_HighPos[param_1] = 1;
  }
RunHSubs:
  bVar2 = GetMiscOffscreenBits(param_1);
  bVar2 = RelativeMiscPosition(bVar2);
  bVar2 = GetMiscBoundBox(bVar2);
  bVar2 = DrawHammer(bVar2);
  return bVar2;
}

// SM2MAIN:8703
// Signature: [X, C] -> []
void CoinBlock(byte param_1, bool param_2) {
  byte bVar1;
  struct_yci sVar2;

  sVar2 = FindEmptyMiscSlot(param_2);
  bVar1 = sVar2.y;
  Misc_PageLoc[bVar1] = Block_PageLoc[param_1];
  Misc_X_Position[bVar1] = Block_X_Position[param_1] | 5;
  Misc_Y_Position[bVar1] = (Block_Y_Position[param_1] - 0x10) - !sVar2.c;
  JCoinC(param_1, bVar1);
  return;
}

// SM2MAIN:871c
// Signature: [X, r02, r06] -> [X]
byte SetupJumpCoin(byte param_1, byte param_2, byte param_3) {
  byte bVar1;
  bool in_C = false;
  struct_yci sVar2;

  sVar2 = FindEmptyMiscSlot(in_C);
  bVar1 = sVar2.y;
  Misc_PageLoc[bVar1] = Block_PageLoc2[param_1];
  Misc_X_Position[bVar1] = param_3 << 4 | 5;
  Misc_Y_Position[bVar1] = (param_2 + 0x20) - ((char)(param_3 << 3) >> 7);
  bVar1 = JCoinC(param_1, bVar1);
  return bVar1;
}

// SM2MAIN:8737
// Signature: [X, Y] -> [X]
byte JCoinC(byte param_1, byte param_2) {
  byte bVar1;

  Misc_Y_Speed[param_2] = 0xfb;
  Misc_Y_HighPos[param_2] = 1;
  Misc_State[param_2] = 1;
  Square2SoundQueue = 1;
  ObjectOffset = param_1;
  bVar1 = GiveOneCoin();
  CoinTallyFor1Ups = CoinTallyFor1Ups + 1;
  return bVar1;
}

// SM2MAIN:874f
// Signature: [C] -> [Y, C]
struct_yci FindEmptyMiscSlot(bool param_1) {

  struct_yci sVar1;

  JumpCoinMiscOffset = 8;
  do {
    if (Misc_State[JumpCoinMiscOffset] == 0) {
      goto UseMiscS;
    }
    JumpCoinMiscOffset -= 1;
    param_1 = 4 < JumpCoinMiscOffset;
  } while (JumpCoinMiscOffset != 5);
  JumpCoinMiscOffset = 8;
UseMiscS:
  sVar1.c = param_1;
  sVar1.y = JumpCoinMiscOffset;
  sVar1.i = (bool)0;
  return sVar1;
}

// SM2MAIN:8761
// Signature: [] -> []
void MiscObjectsCore(void) {
  bool bVar1;
  byte bVar2;

  bVar2 = 8;
  do {
    ObjectOffset = bVar2;
    if (Misc_State[bVar2] != 0) {
      if ((char)Misc_State[bVar2] < 0) {
        bVar2 = ProcHammerObj(bVar2);
      } else {
        if (Misc_State[bVar2] == 1) {
          ImposeGravity(0, bVar2 + 0xd, 0x50, 3, 6);
          bVar2 = ObjectOffset;
          if (Misc_Y_Speed[ObjectOffset] == 5) {
            Misc_State[ObjectOffset] = Misc_State[ObjectOffset] + 1;
          }
        } else {
          Misc_State[bVar2] = Misc_State[bVar2] + 1;
          bVar1 = CARRY1(Misc_X_Position[bVar2], ScrollAmount);
          Misc_X_Position[bVar2] = Misc_X_Position[bVar2] + ScrollAmount;
          Misc_PageLoc[bVar2] = Misc_PageLoc[bVar2] + bVar1;
          if (Misc_State[bVar2] == 0x30) {
            Misc_State[bVar2] = 0;
            goto MiscLoopBack;
          }
        }
        bVar2 = RelativeMiscPosition(bVar2);
        bVar2 = GetMiscOffscreenBits(bVar2);
        bVar2 = GetMiscBoundBox(bVar2);
        bVar2 = JCoinGfxHandler(bVar2);
      }
    }
MiscLoopBack:
    bVar2 -= 1;
    if (0x7f < bVar2) {
      return;
    }
  } while (true);
}

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

// SM2MAIN:87ef
// Signature: [A] -> [X]
byte WriteDigits(byte param_1) {
  PrintStatusBarNumbers(param_1);
  if (VRAM_Buffer1[VRAM_Buffer1_Offset - 6] == 0) {
    VRAM_Buffer1[VRAM_Buffer1_Offset - 6] = 0x24;
  }
  return ObjectOffset;
}

// SM2MAIN:8802
// Signature: [X] -> []
void SetupPowerUp(byte param_1) {
  Enemy_ID[5] = 0x2e;
  Enemy_PageLoc[5] = Block_PageLoc[param_1];
  Enemy_X_Position[5] = Block_X_Position[param_1];
  Enemy_Y_HighPos[5] = 1;
  Enemy_Y_Position[5] = Block_Y_Position[param_1] - 8;
  PwrUpJmp();
  return;
}

// SM2MAIN:8819
// Signature: [] -> []
void PwrUpJmp(void) {
  Enemy_State[5] = 1;
  Enemy_Flag[5] = 1;
  Enemy_BoundBoxCtrl[5] = 3;
  if ((PowerUpType < 2) && (PowerUpType = PlayerStatus, 1 < PlayerStatus)) {
    PowerUpType = PlayerStatus >> 1;
  }
  Enemy_SprAttrib[5] = 0x20;
  Square2SoundQueue = 2;
  return;
}

// SM2MAIN:883e
// Signature: [] -> [X]
byte PowerUpObjHandler(void) {
  byte bVar1;
  bool bVar2;
  struct_axr00 sVar3;
  struct_xyi sVar4;

  bVar1 = 5;
  ObjectOffset = 5;
  if (Enemy_State[5] != 0) {
    if ((char)Enemy_State[5] < 0) {
      if (TimerControl == 0) {
        if ((PowerUpType == 0) || (PowerUpType == 3) || (PowerUpType == 4) || (PowerUpType == 5)) {
          bVar1 = MoveNormalEnemy(5);
          bVar1 = EnemyToBGCollisionDet(bVar1);
        } else if (PowerUpType == 2) {
          bVar1 = MoveJumpingEnemy(5);
          bVar1 = EnemyJump(bVar1);
        }
      }
    } else {
      if ((FrameCounter & 3) == 0) {
        Enemy_Y_Position[5] -= 1;
        bVar2 = 0x10 < Enemy_State[5];
        Enemy_State[5] = Enemy_State[5] + 1;
        if (bVar2) {
          SpriteVarData1[5] = 0x10;
          Enemy_State[5] = 0x80;
          Enemy_SprAttrib[5] = 0;
          Enemy_MovingDir[5] = 1;
        }
      }
      if (Enemy_State[5] < 6) {
        ObjectOffset = 5;
        return 5;
      }
    }
    sVar3 = RelativeEnemyPosition(bVar1);
    sVar4 = GetEnemyOffscreenBits(sVar3.x);
    GetEnemyBoundBox(sVar4.x);
    bVar1 = DrawPowerUp();
    bVar1 = PlayerEnemyCollision(bVar1);
    OffscreenBoundsCheck(bVar1);
  }
  return bVar1;
}

// SM2MAIN:88ae
// Signature: [A, r02, r06, r07] -> []
void PlayerHeadCollision(byte param_1, byte param_2, byte param_3, byte param_4) {
  short sVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  struct_yci sVar5;
  byte bStack0000;

  bVar4 = SprDataOffset_Ctrl;
  sVar1 = CONCAT11(param_4, param_3);
  bVar2 = 0x11;
  if (PlayerSize == 0) {
    bVar2 = 0x12;
  }
  Block_State[SprDataOffset_Ctrl] = bVar2;
  bStack0000 = param_1;
  DestroyBlockMetatile(bVar4, param_2, param_3);
  bVar3 = SprDataOffset_Ctrl;
  Block_Orig_YPos[SprDataOffset_Ctrl] = param_2;
  Block_BBuf_Low[bVar3] = (byte)sVar1;
  bVar4 = RAM(sVar1 + (ushort)param_2);
  sVar5 = BlockBumpedChk(bVar4);
  bVar2 = bVar4;
  if (PlayerSize == 0) {
    bVar2 = 0;
  }
  if (sVar5.c != false) {
    Block_State[bVar3] = 0x11;
    if ((bVar4 == 0x56) || (bVar2 = 0xc5, bVar4 == 0x5c)) {
      if (BrickCoinTimerFlag == 0) {
        BrickCoinTimer = 0xb;
        BrickCoinTimerFlag = 1;
      }
      bVar2 = bVar4;
      if (BrickCoinTimer == 0) {
        bVar2 = 0xc5;
      }
    }
  }
  Block_Metatile[bVar3] = bVar2;
  InitBlock_XY_Pos(bVar3);
  RAM(sVar1 + (ushort)param_2) = 0x20;
  BlockBounceTimer = 0x10;
  bVar4 = 0;
  if ((CrouchingFlag != 0) || (PlayerSize != 0)) {
    bVar4 = 1;
  }
  Block_Y_Position[bVar3] = SprObject_Y_Position[0] + BlockYPosAdderData[bVar4] & 0xf0;
  bVar4 = (byte)((ushort)sVar1 >> 8);
  if (Block_State[bVar3] == 0x11) {
    BumpBlock(param_2, bStack0000, (byte)sVar1, bVar4);
  } else {
    BrickShatter(param_2, (byte)sVar1, bVar4);
  }
  SprDataOffset_Ctrl = SprDataOffset_Ctrl ^ 1;
  return;
}

// SM2MAIN:8945
// Signature: [X] -> []
void InitBlock_XY_Pos(byte param_1) {
  bool bVar1;
  byte bVar2;

  bVar1 = 0xf7 < SprObject_X_Position[0];
  Block_X_Position[param_1] = SprObject_X_Position[0] + 8 & 0xf0;
  bVar2 = SprObject_PageLoc[0] + bVar1;
  Block_PageLoc[param_1] = bVar2;
  Block_PageLoc2[param_1] = bVar2;
  Block_Y_HighPos[param_1] = SprObject_Y_HighPos[0];
  return;
}

// SM2MAIN:895c
// Signature: [r02, r05, r06, r07] -> []
void BumpBlock(byte param_1, byte param_2, byte param_3, byte param_4) {
  byte bVar1;
  byte bVar2;
  struct_xr05i sVar3;
  struct_yci sVar4;

  sVar3 = CheckTopOfBlock(param_1, param_2, param_3, param_4);
  bVar2 = sVar3.x;
  Square1SoundQueue = 2;
  Block_X_Speed[bVar2] = 0;
  Block_Y_MoveForce[bVar2] = 0;
  PlayerSpriteVarData2[0] = 0;
  Block_Y_Speed[bVar2] = 0xfe;
  sVar4 = BlockBumpedChk(sVar3.r05);
  bVar1 = sVar4.y;
  if (sVar4.c != false) {
    if (bVar1 >= 0xd) {
      bVar1 = (bVar1 - 6) - (bVar1 < 0xd);
    }
    FUN_3247(bVar1, bVar2);
    return;
  }
  return;
}

// SM2MAIN:899b
// Signature: [X] -> []
void MushFlowerBlock(byte param_1) {
  PowerUpType = 0;
  SetupPowerUp(param_1);
  return;
}

// SM2MAIN:899e
// Signature: [X] -> []
void StarBlock(byte param_1) {
  PowerUpType = 2;
  SetupPowerUp(param_1);
  return;
}

// SM2MAIN:89a1
// Signature: [X] -> []
void PoisonMushBlock(byte param_1) {
  PowerUpType = 4;
  SetupPowerUp(param_1);
  return;
}

// SM2MAIN:89a4
// Signature: [X] -> []
void ExtraLifeMushBlock(byte param_1) {
  PowerUpType = 3;
  SetupPowerUp(param_1);
  return;
}

// SM2MAIN:89ab
// Signature: [] -> []
void VineBlock(void) {
  Setup_Vine(5, SprDataOffset_Ctrl);
  return;
}

// SM2MAIN:89c7
// Signature: [A] -> [Y, C]
struct_yci BlockBumpedChk(byte param_1) {
  byte bVar1;

  bool bVar2;
  struct_yci sVar3;

  bVar1 = 0x12;
  do {
    bVar2 = BrickQBlockMetatiles[bVar1] <= param_1;
    if (param_1 == BrickQBlockMetatiles[bVar1]) {
      goto MatchBump;
    }
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  bVar2 = false;
MatchBump:
  sVar3.c = bVar2;
  sVar3.y = bVar1;
  sVar3.i = (bool)0;
  return sVar3;
}

// SM2MAIN:89d3
// Signature: [r02, r06, r07] -> []
void BrickShatter(byte param_1, byte param_2, byte param_3) {
  byte in_r05 = 0;
  struct_xr05i sVar1;

  sVar1 = CheckTopOfBlock(param_1, in_r05, param_2, param_3);
  Block_RepFlag[sVar1.x] = 1;
  NoiseSoundQueue = 1;
  SpawnBrickChunks(sVar1.x);
  PlayerSpriteVarData2[0] = 0xfe;
  DigitModifier[5] = 5;
  AddToScore();
  return;
}

// SM2MAIN:89f0
// Signature: [r02, r05, r06, r07] -> [X, r05]
struct_xr05i CheckTopOfBlock(byte param_1, byte param_2, byte param_3, byte param_4) {
  byte bVar1;
  short sVar2;
  byte bVar3;

  struct_xr05i sVar4;

  sVar2 = CONCAT11(param_4, param_3);
  bVar3 = SprDataOffset_Ctrl;
  if ((param_1 != 0) && (bVar1 = param_1 - 0x10, RAM(sVar2 + (ushort)bVar1) == 0xc3)) {
    RAM(sVar2 + (ushort)bVar1) = 0;
    param_2 = RemoveCoin_Axe(bVar1, param_3);
    bVar3 = SetupJumpCoin(SprDataOffset_Ctrl, bVar1, (byte)sVar2);
  }
  sVar4.r05 = param_2;
  sVar4.x = bVar3;
  sVar4.i = (bool)0;
  return sVar4;
}

// SM2MAIN:8a12
// Signature: [X] -> []
void SpawnBrickChunks(byte param_1) {
  Block_Orig_XPos[param_1] = Block_X_Position[param_1];
  Block_X_Speed[param_1] = 0xf0;
  Block_X_Speed[param_1 + 2] = 0xf0;
  Block_Y_Speed[param_1] = 0xfa;
  Block_Y_Speed[param_1 + 2] = 0xfc;
  Block_Y_MoveForce[param_1] = 0;
  Block_Y_MoveForce[param_1 + 2] = 0;
  Block_PageLoc[param_1 + 2] = Block_PageLoc[param_1];
  Block_X_Position[param_1 + 2] = Block_X_Position[param_1];
  Block_Y_Position[param_1 + 2] = Block_Y_Position[param_1] + 8;
  Block_Y_Speed[param_1] = 0xfa;
  return;
}

// SM2MAIN:8a41
// Signature: [X] -> [X]
byte BlockObjectsCore(byte param_1) {
  byte bVar1;
  byte bStack0000;

  bStack0000 = Block_State[param_1];
  if (bStack0000 == 0) {
    goto UpdSte;
  }
  bStack0000 &= 0xf;
  bVar1 = param_1 + 9;
  if (bStack0000 == 1) {
    ImposeGravityBlock(bVar1);
    bVar1 = RelativeBlockPosition(ObjectOffset);
    bVar1 = GetBlockOffscreenBits(bVar1);
    param_1 = DrawBlock(bVar1);
    if (4 < (Block_Y_Position[param_1] & 0xf)) {
      goto UpdSte;
    }
    Block_RepFlag[param_1] = 1;
  } else {
    ImposeGravityBlock(bVar1);
    MoveObjectHorizontally(bVar1);
    bVar1 += 2;
    ImposeGravityBlock(bVar1);
    MoveObjectHorizontally(bVar1);
    bVar1 = RelativeBlockPosition(ObjectOffset);
    param_1 = GetBlockOffscreenBits(bVar1);
    DrawBrickChunks(param_1);
    if (Block_Y_HighPos[param_1] == 0) {
      goto UpdSte;
    }
    if (0xf0 < Block_Y_Position[param_1 + 2]) {
      Block_Y_Position[param_1 + 2] = 0xf0;
    }
    if (Block_Y_Position[param_1] < 0xf0) {
      goto UpdSte;
    }
  }
  bStack0000 = 0;
UpdSte:
  Block_State[param_1] = bStack0000;
  return param_1;
}

// SM2MAIN:8aa5
// Signature: [] -> []
void BlockObjMT_Updater(void) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;

  bVar4 = 1;
  do {
    ObjectOffset = bVar4;
    if ((VRAM_Buffer1[0] == 0) && (Block_RepFlag[bVar4] != 0)) {
      bVar1 = Block_BBuf_Low[bVar4];
      bVar2 = Block_Orig_YPos[bVar4];
      bVar3 = Block_Metatile[bVar4];
      RAM(CONCAT11(5, bVar1) + (ushort)bVar2) = bVar3;
      ReplaceBlockMetatile(bVar3, bVar4, bVar2, bVar1);
      Block_RepFlag[bVar4] = 0;
    }
    bVar4 -= 1;
  } while (bVar4 < 0x80);
  return;
}

// SM2MAIN:8ad3
// Signature: [X] -> [A, X]
struct_axi MoveEnemyHorizontally(byte param_1) {

  struct_axi sVar1;

  sVar1.a = MoveObjectHorizontally(param_1 + 1);
  sVar1.x = ObjectOffset;
  sVar1.i = (bool)0;
  return sVar1;
}

// SM2MAIN:8ada
// Signature: [] -> [A]
byte MovePlayerHorizontally(void) {
  byte bVar1;

  if (JumpspringAnimCtrl == 0) {
    bVar1 = MoveObjectHorizontally(0);
    return bVar1;
  }
  return JumpspringAnimCtrl;
}

// SM2MAIN:8ae0
// Signature: [X] -> [A]
byte MoveObjectHorizontally(byte param_1) {
  byte bVar1;
  bool bVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;

  bVar3 = PlayerSpriteVarData1[param_1] >> 4;
  if (7 < bVar3) {
    bVar3 |= 0xf0;
  }
  cVar5 = 0;
  if (0x7f < bVar3) {
    cVar5 = -1;
  }
  bVar2 = CARRY1(SprObject_X_MoveForce[param_1], PlayerSpriteVarData1[param_1] * 0x10);
  SprObject_X_MoveForce[param_1] = SprObject_X_MoveForce[param_1] + PlayerSpriteVarData1[param_1] * 0x10;
  bVar1 = SprObject_X_Position[param_1];
  bVar4 = bVar1 + bVar3 + bVar2;
  SprObject_X_Position[param_1] = bVar4;
  SprObject_PageLoc[param_1]
      = SprObject_PageLoc[param_1] + cVar5 + (CARRY1(bVar1, bVar3) || bVar2 && bVar4 == 0);
  return bVar2 + bVar3;
}

// SM2MAIN:8b1e
// Signature: [] -> []
void MovePlayerVertically(void) {
  if ((TimerControl == 0) && (JumpspringAnimCtrl != 0)) {
    return;
  }
  ImposeGravitySprObj(4, 0, VerticalForce);
  return;
}

// SM2MAIN:8b34
// Signature: [X] -> [X]
byte MoveD_EnemyVertically(byte param_1) {
  byte bVar1;

  if (Enemy_State[param_1] == 5) {
    bVar1 = MoveFallingPlatform(param_1);
    return bVar1;
  }
  bVar1 = SetXMoveAmt(3, param_1, 0x3d);
  return bVar1;
}

// SM2MAIN:8b3c
// Signature: [X] -> [X]
byte MoveFallingPlatform(byte param_1) {
  byte bVar1;

  bVar1 = SetXMoveAmt(3, param_1, 0x20);
  return bVar1;
}

// SM2MAIN:8b41
// Signature: [X] -> [X]
byte MoveRedPTroopaDown(byte param_1) {
  byte bVar1;

  bVar1 = RedPTroopaGrav(0, param_1 + 1, 3, 6, 2);
  return bVar1;
}

// SM2MAIN:8b46
// Signature: [X] -> [X]
byte MoveRedPTroopaUp(byte param_1) {
  byte bVar1;

  bVar1 = RedPTroopaGrav(1, param_1 + 1, 3, 6, 2);
  return bVar1;
}

// SM2MAIN:8b59
// Signature: [X] -> [X]
byte MoveDropPlatform(byte param_1) {
  byte bVar1;

  bVar1 = SetXMoveAmt(2, param_1, 0x7f);
  return bVar1;
}

// SM2MAIN:8b5d
// Signature: [X] -> [X]
byte MoveEnemySlowVert(byte param_1) {
  byte bVar1;

  bVar1 = SetXMoveAmt(2, param_1, 0xf);
  return bVar1;
}

// SM2MAIN:8b63
// Signature: [X] -> [X]
byte MoveJ_EnemyVertically(byte param_1) {
  byte bVar1;

  bVar1 = SetXMoveAmt(3, param_1, 0x1c);
  return bVar1;
}

// SM2MAIN:8b67
// Signature: [A, X, Y] -> [X]
byte SetXMoveAmt(byte param_1, byte param_2, byte param_3) {
  ImposeGravitySprObj(param_1, param_2 + 1, param_3);
  return ObjectOffset;
}

// SM2MAIN:8b75
// Signature: [X] -> []
void ImposeGravityBlock(byte param_1) {
  byte in_r01 = 0;

  ImposeGravity(0, param_1, 0x50, in_r01, MaxSpdBlockData[1]);
  return;
}

// SM2MAIN:8b7e
// Signature: [A, X, r00] -> []
void ImposeGravitySprObj(byte param_1, byte param_2, byte param_3) {
  byte in_r01 = 0;

  ImposeGravity(0, param_2, param_3, in_r01, param_1);
  return;
}

// SM2MAIN:8b85
// Signature: [X] -> [X]
byte MovePlatformDown(byte param_1) {
  byte bVar1;
  undefined uStack0000;

  uStack0000 = 0;
  bVar1 = 5;
  if (Enemy_ID[param_1] == 0x29) {
    bVar1 = 9;
  }
  bVar1 = RedPTroopaGrav(0, param_1 + 1, bVar1, 10, 3);
  return bVar1;
}

// SM2MAIN:8b88
// Signature: [X] -> [X]
byte MovePlatformUp(byte param_1) {
  byte bVar1;
  undefined uStack0000;

  uStack0000 = 1;
  bVar1 = 5;
  if (Enemy_ID[param_1] == 0x29) {
    bVar1 = 9;
  }
  bVar1 = RedPTroopaGrav(1, param_1 + 1, bVar1, 10, 3);
  return bVar1;
}

// SM2MAIN:8ba2
// Signature: [A, X, r00, r01, r02] -> [X]
byte RedPTroopaGrav(byte param_1, byte param_2, byte param_3, byte param_4, byte param_5) {
  ImposeGravity(param_1, param_2, param_3, param_4, param_5);
  return ObjectOffset;
}

// SM2MAIN:8ba8
// Signature: [A, X, r00, r01, r02] -> []
void ImposeGravity(byte param_1, byte param_2, byte param_3, byte param_4, byte param_5) {
  bool bVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  byte bVar5;

  bVar1 = CARRY1(SprObject_YMF_Dummy[param_2], SprObject_Y_MoveForce[param_2]);
  SprObject_YMF_Dummy[param_2] = SprObject_YMF_Dummy[param_2] + SprObject_Y_MoveForce[param_2];
  cVar4 = 0;
  bVar3 = PlayerSpriteVarData2[param_2];
  if (0x7f < bVar3) {
    cVar4 = -1;
  }
  bVar5 = SprObject_Y_Position[param_2];
  bVar2 = bVar3 + bVar5 + bVar1;
  SprObject_Y_Position[param_2] = bVar2;
  SprObject_Y_HighPos[param_2]
      = SprObject_Y_HighPos[param_2] + cVar4 + (CARRY1(bVar3, bVar5) || bVar1 && bVar2 == 0);
  bVar3 = SprObject_Y_MoveForce[param_2];
  SprObject_Y_MoveForce[param_2] = bVar3 + param_3;
  bVar3 = PlayerSpriteVarData2[param_2] + CARRY1(bVar3, param_3);
  PlayerSpriteVarData2[param_2] = bVar3;
  if (((byte)(bVar3 - param_5) < 0x80) && (0x7f < SprObject_Y_MoveForce[param_2])) {
    PlayerSpriteVarData2[param_2] = param_5;
    SprObject_Y_MoveForce[param_2] = 0;
  }
  if (param_1 != 0) {
    bVar5 = (param_5 ^ 0xff) + 1;
    bVar3 = SprObject_Y_MoveForce[param_2];
    SprObject_Y_MoveForce[param_2] = bVar3 - param_4;
    bVar3 = PlayerSpriteVarData2[param_2] - (bVar3 < param_4);
    PlayerSpriteVarData2[param_2] = bVar3;
    if ((0x7f < (byte)(bVar3 - bVar5)) && (SprObject_Y_MoveForce[param_2] < 0x80)) {
      PlayerSpriteVarData2[param_2] = bVar5;
      SprObject_Y_MoveForce[param_2] = 0xff;
    }
  }
  return;
}

// SM2MAIN:8c23
// Signature: [X] -> [X]
byte EnemiesAndLoopsCore(byte param_1) {
  byte bVar1;
  byte bStack0000;

  bStack0000 = Enemy_Flag[param_1];
  if ((bool)(bStack0000 >> 7)) {
    if (Enemy_Flag[bStack0000 & 0xf] == 0) {
      Enemy_Flag[param_1] = 0;
    }
  } else {
    if (bStack0000 != 0) {
      bVar1 = RunEnemyObjectsCore();
      return bVar1;
    }
    if ((AreaParserTaskNum & 7) != 7) {
      bVar1 = ProcLoopCommand(param_1);
      return bVar1;
    }
  }
  return param_1;
}

// SM2MAIN:8c77
// Signature: [Y] -> []
void ExecGameLoopback(byte param_1) {
  SprObject_PageLoc[0] = SprObject_PageLoc[0] - 4;
  CurrentPageLoc = CurrentPageLoc - 4;
  ScreenEdgeOrLeft_PageLoc[0] = ScreenEdgeOrLeft_PageLoc[0] - 4;
  ScreenRight_PageLoc = ScreenRight_PageLoc - 4;
  AreaObjectPageLoc = AreaObjectPageLoc - 4;
  EnemyObjectPageSel = 0;
  AreaObjectPageSel = 0;
  EnemyDataOffset = 0;
  EnemyObjectPageLoc = 0;
  AreaDataOffset = AreaDataOfsLoopback[param_1];
  return;
}

// SM2MAIN:8cb7
// Signature: [X] -> [X]
byte ProcLoopCommand(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  bool bVar6;

  do {
    if ((LoopCommand != 0) && (CurrentColumnPos == 0)) {
      bVar4 = 0xc;
      do {
        bVar4 -= 1;
        if (0x7f < bVar4) {
          goto ChkEnemyFrenzy;
        }
      } while ((WorldNumber != LoopCmdWorldNumber[bVar4]) || (CurrentPageLoc != LoopCmdPageNumber[bVar4]));
      if ((SprObject_Y_Position[0] == LoopCmdYPosition[bVar4]) && (Player_State == 0)) {
        MultiLoopCorrectCntr += 1;
      }
      MultiLoopPassCntr += 1;
      if (MultiLoopPassCntr == MultiLoopCount[bVar4]) {
        if (MultiLoopCorrectCntr != MultiLoopCount[bVar4]) {
          ExecGameLoopback(bVar4);
          param_1 = KillAllEnemies();
        }
        MultiLoopPassCntr = 0;
        MultiLoopCorrectCntr = 0;
      }
      LoopCommand = 0;
    }
ChkEnemyFrenzy:
    bVar4 = EnemyDataOffset;
    if (EnemyFrenzyQueue != 0) {
      Enemy_ID[param_1] = EnemyFrenzyQueue;
      Enemy_Flag[param_1] = 1;
      Enemy_State[param_1] = 0;
      EnemyFrenzyQueue = 0;
      InitEnemyObject(param_1);
      return param_1;
    }
    if (EnemyData[EnemyDataOffset] == 0xff) {
      goto CheckFrenzyBuffer;
    }
    if ((((EnemyData[EnemyDataOffset] & 0xf) != 0xe) && (4 < param_1))
        && ((EnemyData[(byte)(EnemyDataOffset + 1)] & 0x3f) != 0x2e)) {
      return param_1;
    }
    bVar1 = ScreenRight_X_Pos + 0x30;
    bVar2 = ScreenRight_PageLoc + (0xcf < ScreenRight_X_Pos);
    bVar5 = EnemyDataOffset + 1;
    if (((char)EnemyData[bVar5] < 0) && (EnemyObjectPageSel == 0)) {
      EnemyObjectPageSel = 1;
      EnemyObjectPageLoc += 1;
    }
    if (((EnemyData[EnemyDataOffset] & 0xf) != 0xf) || (EnemyObjectPageSel != 0)) {
      Enemy_PageLoc[param_1] = EnemyObjectPageLoc;
      bVar3 = EnemyData[bVar4] & 0xf0;
      Enemy_X_Position[param_1] = bVar3;
      if (ScreenRight_X_Pos <= bVar3 && ScreenRight_PageLoc <= Enemy_PageLoc[param_1]
          || ScreenRight_X_Pos > bVar3 && ScreenRight_PageLoc < Enemy_PageLoc[param_1]) {
        bVar6 = (bVar1 & 0xf0) < Enemy_X_Position[param_1];
        if ((bVar6 || bVar2 < Enemy_PageLoc[param_1]) && (!bVar6 || bVar2 <= Enemy_PageLoc[param_1])) {
CheckFrenzyBuffer:
          bVar4 = EnemyFrenzyBuffer;
          if (EnemyFrenzyBuffer == 0) {
            if (VineFlagOffset != 1) {
              return param_1;
            }
            bVar4 = 0x2f;
          }
          Enemy_ID[param_1] = bVar4;
          InitEnemyObject(param_1);
          return param_1;
        }
        Enemy_Y_HighPos[param_1] = 1;
        bVar1 = EnemyData[bVar4];
        Enemy_Y_Position[param_1] = bVar1 * 0x10;
        if ((byte)(bVar1 * 0x10) != 0xe0) {
          if (((EnemyData[bVar5] & 0x40) != 0) && (SecondaryHardMode == 0)) {
            bVar4 = Inc2B();
            return bVar4;
          }
          bVar4 = EnemyData[bVar5] & 0x3f;
          if ((0x36 < bVar4) && (bVar4 < 0x3f)) {
            bVar4 = HandleGroupEnemies(bVar4);
            return bVar4;
          }
          if ((bVar4 == 6) && (PrimaryHardMode != 0)) {
            bVar4 = 2;
          }
          Enemy_ID[param_1] = bVar4;
          Enemy_Flag[param_1] = 1;
          InitEnemyObject(param_1);
          if (Enemy_Flag[param_1] == 0) {
            return param_1;
          }
          bVar4 = Inc2B();
          return bVar4;
        }
      } else if ((EnemyData[bVar4] & 0xf) != 0xe) {
        bVar4 = CheckThreeBytes();
        return bVar4;
      }
      if ((WorldNumber == 8) || (EnemyData[(byte)(bVar4 + 2)] >> 5 == WorldNumber)) {
        AreaPointer = EnemyData[(byte)(bVar4 + 1)];
        EntrancePage = EnemyData[(byte)(bVar4 + 2)] & 0x1f;
      }
      EnemyDataOffset += 1;
      bVar4 = Inc2B();
      return bVar4;
    }
    EnemyObjectPageLoc = EnemyData[bVar5] & 0x3f;
    EnemyDataOffset += 2;
    EnemyObjectPageSel = 1;
  } while (true);
}

// SM2MAIN:8e03
// Signature: [X] -> []
void InitEnemyObject(byte param_1) {
  Enemy_State[param_1] = 0;
  CheckpointEnemyID(param_1);
  return;
}

// SM2MAIN:8e34
// Signature: [] -> [X]
byte CheckThreeBytes(void) {
  byte bVar1;

  if ((EnemyData[EnemyDataOffset] & 0xf) != 0xe) {
    bVar1 = Inc2B();
    return bVar1;
  }
  EnemyDataOffset += 1;
  bVar1 = Inc2B();
  return bVar1;
}

// SM2MAIN:8e42
// Signature: [] -> [X]
byte Inc2B(void) {
  EnemyDataOffset = EnemyDataOffset + 2;
  EnemyObjectPageSel = 0;
  return ObjectOffset;
}

// SM2MAIN:8e50
// Signature: [X] -> []
void CheckpointEnemyID(byte param_1) {
  byte bVar1;

  bVar1 = Enemy_ID[param_1];
  if (0x14 >= bVar1) {
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 8 + (0x14 < bVar1);
    EnemyOffscrBitsMasked[param_1] = 1;
  }
  FUN_327f(bVar1, param_1);
  return;
}

// SM2MAIN:8ed4
// Signature: [] -> []
void NoInitCode(void) { return; }

// SM2MAIN:8ed5
// Signature: [X] -> []
void InitGoomba(byte param_1) {
  InitNormalEnemy(param_1);
  SmallBBox(param_1);
  return;
}

// SM2MAIN:8edb
// Signature: [X] -> []
void InitPodoboo(byte param_1) {
  Enemy_Y_HighPos[param_1] = 2;
  Enemy_Y_Position[param_1] = 2;
  EnemyIntervalTimer[param_1] = 1;
  Enemy_State[param_1] = 0;
  SmallBBox(param_1);
  return;
}

// SM2MAIN:8eeb
// Signature: [X] -> []
void InitRetainerObj(byte param_1) {
  Enemy_Y_Position[param_1] = 0xb8;
  return;
}

// SM2MAIN:8ef2
// Signature: [X] -> []
void InitNormalEnemy(byte param_1) {
  SpriteVarData1[param_1] = NormalXSpdData[PrimaryHardMode != 0];
  Enemy_BoundBoxCtrl[param_1] = 3;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
  return;
}

// SM2MAIN:8f02
// Signature: [X] -> []
void InitRedKoopa(byte param_1) {
  InitNormalEnemy(param_1);
  Enemy_State[param_1] = 1;
  return;
}

// SM2MAIN:8f0c
// Signature: [X] -> []
void InitHammerBro(byte param_1) {
  HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = 0;
  SpriteVarData1[param_1] = 0;
  if (WorldNumber < 6) {
    EnemyIntervalTimer[param_1] = HBroWalkingTimerData[SecondaryHardMode];
  }
  Enemy_BoundBoxCtrl[param_1] = 0xb;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
  return;
}

// SM2MAIN:8f28
// Signature: [X] -> []
void InitHorizFlySwimEnemy(byte param_1) {
  SpriteVarData1[param_1] = 0;
  Enemy_BoundBoxCtrl[param_1] = 3;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
  return;
}

// SM2MAIN:8f2d
// Signature: [X] -> []
void InitBloober(byte param_1) {
  SpriteVarData1[param_1] = 0;
  SmallBBox(param_1);
  return;
}

// SM2MAIN:8f31
// Signature: [X] -> [A]
byte SmallBBox(byte param_1) {
  byte bVar1;

  Enemy_BoundBoxCtrl[param_1] = 9;
  Enemy_MovingDir[param_1] = 2;
  bVar1 = InitVStf(param_1);
  return bVar1;
}

// SM2MAIN:8f35
// Signature: [X, C] -> []
void InitRedPTroopa(byte param_1, bool param_2) {
  char cVar1;

  cVar1 = 0x30;
  Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] = Enemy_Y_Position[param_1];
  if (0x7f < Enemy_Y_Position[param_1]) {
    cVar1 = -0x20;
  }
  SpriteVarData1[param_1] = cVar1 + Enemy_Y_Position[param_1] + param_2;
  Enemy_BoundBoxCtrl[param_1] = 3;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
  return;
}

// SM2MAIN:8f4e
// Signature: [X] -> [A]
byte InitVStf(byte param_1) {
  SpriteVarData2[param_1] = 0;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = 0;
  return 0;
}

// SM2MAIN:8f56
// Signature: [X] -> []
void InitBulletBill(byte param_1) {
  Enemy_MovingDir[param_1] = 2;
  Enemy_BoundBoxCtrl[param_1] = 9;
  return;
}

// SM2MAIN:8f60
// Signature: [X] -> []
void InitCheepCheep(byte param_1) {
  SmallBBox(param_1);
  SpriteVarData1[param_1] = PseudoRandomBitReg[param_1] & 0x10;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = Enemy_Y_Position[param_1];
  return;
}

// SM2MAIN:8f70
// Signature: [X] -> []
void InitLakitu(byte param_1) {
  if (EnemyFrenzyBuffer == 0) {
    SetupLakitu(param_1);
    return;
  }
  EraseEnemyObject(param_1);
  return;
}

// SM2MAIN:8f75
// Signature: [X] -> []
void SetupLakitu(byte param_1) {
  LakituReappearTimer = 0;
  InitHorizFlySwimEnemy(param_1);
  Enemy_BoundBoxCtrl[param_1] = 3;
  return;
}

// SM2MAIN:8f8f
// Signature: [X] -> []
void LakituAndSpinyHandler(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  if ((FrenzyEnemyTimer == 0) && (param_1 < 5)) {
    FrenzyEnemyTimer = 0x80;
    bVar2 = 4;
    do {
      if (Enemy_ID[bVar2] == 0x11) {
        if (SprObject_Y_Position[0] < 0x2c) {
          FrenzyEnemyTimer = 0x80;
          return;
        }
        if (Enemy_State[bVar2] != 0) {
          FrenzyEnemyTimer = 0x80;
          return;
        }
        Enemy_PageLoc[param_1] = Enemy_PageLoc[bVar2];
        Enemy_X_Position[param_1] = Enemy_X_Position[bVar2];
        Enemy_Y_HighPos[param_1] = 1;
        Enemy_Y_Position[param_1] = Enemy_Y_Position[bVar2] - 8;
        bVar1 = PseudoRandomBitReg[param_1] & 3;
        bVar2 = ObjectOffset;
        PlayerLakituDiff(ObjectOffset, PRDiffAdjustData[bVar1], PRDiffAdjustData[bVar1 + 4],
                         PRDiffAdjustData[bVar1 + 8]);
        bVar1 = SmallBBox(bVar2);
        bVar3 = 2;
        SpriteVarData1[bVar2] = bVar1;
        if (bVar1 < 0x80) {
          bVar3 = 1;
        }
        Enemy_MovingDir[bVar2] = bVar3;
        SpriteVarData2[bVar2] = 0xfd;
        Enemy_Flag[bVar2] = 1;
        Enemy_State[bVar2] = 5;
        return;
      }
      bVar2 -= 1;
    } while (bVar2 < 0x80);
    LakituReappearTimer += 1;
    if (2 < LakituReappearTimer) {
      bVar2 = 4;
      do {
        if (Enemy_Flag[bVar2] == 0) {
          goto CreateL;
        }
        bVar2 -= 1;
      } while (bVar2 < 0x80);
      if (bVar2 < 0x80) {
CreateL:
        Enemy_State[bVar2] = 0;
        Enemy_ID[bVar2] = 0x11;
        SetupLakitu(bVar2);
        bVar1 = 0x20;
        if ((HardWorldFlag != 0) || (5 < WorldNumber)) {
          bVar1 = 0x60;
        }
        PutAtRightExtent(bVar1, bVar2);
      }
    }
  }
  return;
}

// SM2MAIN:9052
// Signature: [X] -> []
void InitLongFirebar(byte param_1) {
  DuplicateEnemyObj(param_1);
  InitShortFirebar(param_1);
  return;
}

// SM2MAIN:9055
// Signature: [X] -> []
void InitShortFirebar(byte param_1) {
  byte bVar1;

  SpriteVarData1[param_1] = 0;
  FirebarSpinSpeed[param_1] = FirebarSpinSpdData[(byte)(Enemy_ID[param_1] - 0x1b)];
  FirebarSpinDirection[param_1] = FirebarSpinDirData[(byte)(Enemy_ID[param_1] - 0x1b)];
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 4;
  bVar1 = Enemy_X_Position[param_1];
  Enemy_X_Position[param_1] = bVar1 + 4;
  Enemy_PageLoc[param_1] = Enemy_PageLoc[param_1] + (0xfb < bVar1);
  Enemy_BoundBoxCtrl[param_1] = 3;
  return;
}

// SM2MAIN:90a1
// Signature: [X] -> []
void InitFlyingCheepCheep(byte param_1) {
  bool bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;

  if (FrenzyEnemyTimer == 0) {
    SmallBBox(param_1);
    FrenzyEnemyTimer = FlyCCTimerData[PseudoRandomBitReg[param_1 + 1] & 3];
    bVar4 = 3;
    if (SecondaryHardMode != 0) {
      bVar4 = 4;
    }
    if (param_1 < bVar4) {
      bVar4 = PseudoRandomBitReg[param_1];
      SpriteVarData2[param_1] = 0xfb;
      cVar2 = 0;
      if ((PlayerSpriteVarData1[0] != 0) && (cVar2 = 4, 0x18 < PlayerSpriteVarData1[0])) {
        cVar2 = 8;
      }
      bVar3 = cVar2 + (bVar4 & 3);
      if ((PseudoRandomBitReg[param_1 + 1] & 3) != 0) {
        bVar3 = PseudoRandomBitReg[param_1 + 2] & 0xf;
      }
      bVar4 = cVar2 + (bVar4 & 3);
      SpriteVarData1[param_1] = FlyCCXSpeedData[bVar4];
      Enemy_MovingDir[param_1] = 1;
      if ((PlayerSpriteVarData1[0] == 0) && (bVar4 = bVar3, (bVar3 & 2) != 0)) {
        SpriteVarData1[param_1] = (SpriteVarData1[param_1] ^ 0xff) + 1;
        Enemy_MovingDir[param_1] = Enemy_MovingDir[param_1] + 1;
      }
      if ((bVar4 & 2) == 0) {
        bVar1 = SprObject_X_Position[0] < FlyCCXPositionData[bVar4];
        Enemy_X_Position[param_1] = SprObject_X_Position[0] - FlyCCXPositionData[bVar4];
        bVar4 = SprObject_PageLoc[0] - bVar1;
      } else {
        bVar1 = CARRY1(SprObject_X_Position[0], FlyCCXPositionData[bVar4]);
        Enemy_X_Position[param_1] = SprObject_X_Position[0] + FlyCCXPositionData[bVar4];
        bVar4 = SprObject_PageLoc[0] + bVar1;
      }
      Enemy_PageLoc[param_1] = bVar4;
      Enemy_Flag[param_1] = 1;
      Enemy_Y_HighPos[param_1] = 1;
      Enemy_Y_Position[param_1] = 0xf8;
      return;
    }
  }
  return;
}

// SM2MAIN:9142
// Signature: [X] -> []
void InitBowser(byte param_1) {
  byte bVar1;

  bVar1 = 4;
  do {
    if ((bVar1 != ObjectOffset) && (Enemy_ID[bVar1] == 0x2d)) {
      Enemy_ID[bVar1] = 0;
      Enemy_Flag[bVar1] = 0;
    }
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  DuplicateEnemyObj(param_1);
  BowserBodyControls = 0;
  BridgeCollapseOffset = 0;
  BowserOrigXPos = Enemy_X_Position[param_1];
  BowserFireBreathTimer = 0xdf;
  BowserFront_Offset = param_1;
  Enemy_MovingDir[param_1] = 0xdf;
  BowserFeetCounter = 0x20;
  EnemyFrameTimer[param_1] = 0x20;
  BowserHitPoints = 5;
  BowserMovementSpeed = 2;
  return;
}

// SM2MAIN:9186
// Signature: [X] -> []
void DuplicateEnemyObj(byte param_1) {
  byte bVar1;

  bVar1 = 0xff;
  do {
    bVar1 += 1;
  } while (Enemy_Flag[bVar1] != 0);
  DuplicateObj_Offset = bVar1;
  Enemy_Flag[bVar1] = param_1 | 0x80;
  Enemy_PageLoc[bVar1] = Enemy_PageLoc[param_1];
  Enemy_X_Position[bVar1] = Enemy_X_Position[param_1];
  Enemy_Flag[param_1] = 1;
  Enemy_Y_HighPos[bVar1] = 1;
  Enemy_Y_Position[bVar1] = Enemy_Y_Position[param_1];
  return;
}

// SM2MAIN:91b4
// Signature: [X] -> []
void InitBowserFlame(byte param_1) {
  byte bVar1;

  if (FrenzyEnemyTimer != 0) {
    return;
  }
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = 0;
  bVar1 = BowserFront_Offset;
  NoiseSoundQueue |= 2;
  if (Enemy_ID[BowserFront_Offset] != 0x2d) {
    bVar1 = SetFlameTimer();
    FrenzyEnemyTimer = bVar1 + 0x20;
    if (SecondaryHardMode != 0) {
      FrenzyEnemyTimer = bVar1 + 0x10;
    }
    BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = PseudoRandomBitReg[param_1] & 3;
    PutAtRightExtent(FlameYPosData[PseudoRandomBitReg[param_1] & 3], param_1);
    return;
  }
  Enemy_X_Position[param_1] = Enemy_X_Position[BowserFront_Offset] - 0xe;
  Enemy_PageLoc[param_1] = Enemy_PageLoc[bVar1];
  Enemy_Y_Position[param_1] = Enemy_Y_Position[bVar1] + 8;
  BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = PseudoRandomBitReg[param_1] & 3;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1]
      = FlameYMFAdderData[Enemy_Y_Position[param_1] <= FlameYPosData[PseudoRandomBitReg[param_1] & 3]];
  EnemyFrenzyBuffer = 0;
  Enemy_BoundBoxCtrl[param_1] = 8;
  Enemy_Y_HighPos[param_1] = 1;
  Enemy_Flag[param_1] = 1;
  Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] = 0;
  Enemy_State[param_1] = 0;
  return;
}

// SM2MAIN:91e9
// Signature: [A, X] -> [A]
byte PutAtRightExtent(byte param_1, byte param_2) {
  bool bVar1;

  Enemy_Y_Position[param_2] = param_1;
  bVar1 = 0xdf < ScreenRight_X_Pos;
  Enemy_X_Position[param_2] = ScreenRight_X_Pos + 0x20;
  Enemy_PageLoc[param_2] = ScreenRight_PageLoc + bVar1;
  Enemy_BoundBoxCtrl[param_2] = 8;
  Enemy_Y_HighPos[param_2] = 1;
  Enemy_Flag[param_2] = 1;
  Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_2] = 0;
  Enemy_State[param_2] = 0;
  return 0;
}

// SM2MAIN:924e
// Signature: [X] -> []
void InitFireworks(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;

  if (FrenzyEnemyTimer == 0) {
    FrenzyEnemyTimer = 0x20;
    FireworksCounter -= 1;
    bVar5 = 6;
    do {
      bVar5 -= 1;
    } while (Enemy_ID[bVar5] != 0x31);
    bVar1 = Enemy_X_Position[bVar5];
    bVar4 = bVar1 - 0x30;
    bVar2 = Enemy_PageLoc[bVar5];
    bVar3 = FireworksCounter + Enemy_State[bVar5];
    bVar5 = FireworksXPosData[bVar3];
    Enemy_X_Position[param_1] = bVar4 + bVar5;
    Enemy_PageLoc[param_1] = (bVar2 - (bVar1 < 0x30)) + CARRY1(bVar4, bVar5);
    Enemy_Y_Position[param_1] = FireworksYPosData[bVar3];
    Enemy_Y_HighPos[param_1] = 1;
    Enemy_Flag[param_1] = 1;
    SpriteVarData1[param_1] = 0;
    SpriteVarData2[param_1] = 8;
  }
  return;
}

// SM2MAIN:92ad
// Signature: [X] -> []
void BulletBillCheepCheep(byte param_1) {
  byte bVar1;

  if (FrenzyEnemyTimer == 0) {
    if (AreaType == 0) {
      if (param_1 < 3) {
        bVar1 = 0xa9 < PseudoRandomBitReg[param_1];
        if (WorldNumber != 1) {
          bVar1 += 1;
        }
        bVar1 = SwimCC_IDData[bVar1 & 1];
Set17ID:
        Enemy_ID[param_1] = bVar1;
        if (BitMFilter == 0xff) {
          BitMFilter = 0;
        }
        bVar1 = PseudoRandomBitReg[param_1];
        while (true) {
          bVar1 &= 7;
          if ((Bitmasks[bVar1] & BitMFilter) == 0)
            break;
          bVar1 += 1;
        }
        BitMFilter = Bitmasks[bVar1] | BitMFilter;
        bVar1 = PutAtRightExtent(Enemy17YPosData[bVar1], param_1);
        BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = bVar1;
        FrenzyEnemyTimer = 0x20;
        CheckpointEnemyID(param_1);
        return;
      }
    } else {
      bVar1 = 0xff;
      do {
        bVar1 += 1;
        if (4 < bVar1) {
          Square2SoundQueue |= 8;
          bVar1 = 8;
          goto Set17ID;
        }
      } while ((Enemy_Flag[bVar1] == 0) || (Enemy_ID[bVar1] != 8));
    }
  }
  return;
}

// SM2MAIN:932c
// Signature: [A] -> [X]
byte HandleGroupEnemies(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bStack0000;

  bVar5 = 0;
  bStack0000 = param_1 - 0x37;
  if ((bStack0000 < 4) && (bVar5 = 6, PrimaryHardMode != 0)) {
    bVar5 = 2;
  }
  bVar6 = 0xb0;
  if ((bStack0000 & 2) != 0) {
    bVar6 = 0x70;
  }
  NumberofGroupEnemies = 2;
  bVar3 = ScreenRight_PageLoc;
  bVar1 = ScreenRight_X_Pos;
  if ((bStack0000 & 1) != 0) {
    NumberofGroupEnemies = 3;
  }
  do {
    bVar4 = 0xff;
    do {
      bVar4 += 1;
      if (4 < bVar4) {
        goto NextED;
      }
    } while (Enemy_Flag[bVar4] != 0);
    Enemy_ID[bVar4] = bVar5;
    Enemy_PageLoc[bVar4] = bVar3;
    Enemy_X_Position[bVar4] = bVar1;
    bVar2 = bVar1 + 0x18;
    bVar3 += 0xe7 < bVar1;
    Enemy_Y_Position[bVar4] = bVar6;
    Enemy_Y_HighPos[bVar4] = 1;
    Enemy_Flag[bVar4] = 1;
    CheckpointEnemyID(bVar4);
    NumberofGroupEnemies -= 1;
    bVar1 = bVar2;
  } while (NumberofGroupEnemies != 0);
NextED:
  bVar5 = Inc2B();
  return bVar5;
}

// SM2MAIN:9398
// Signature: [X] -> []
void InitPiranhaPlant(byte param_1) {
  EnemyAttributeData[13] = 0x22;
  RAM(0x9ffe) = 0x13;
  if ((HardWorldFlag == 0) && (WorldNumber < 3)) {
    EnemyAttributeData[13] = 0x21;
    RAM(0x9ffe) = 0x21;
  }
  // WARNING: Read-only address (RAM,0x9ffe) is written
  SpriteVarData1[param_1] = 1;
  Enemy_State[param_1] = 0;
  SpriteVarData2[param_1] = 0;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = Enemy_Y_Position[param_1];
  BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = Enemy_Y_Position[param_1] - 0x18;
  Enemy_BoundBoxCtrl[param_1] = 9;
  return;
}

// SM2MAIN:93d5
// Signature: [X] -> []
void InitEnemyFrenzy(byte param_1) {
  EnemyFrenzyBuffer = Enemy_ID[param_1];
  FUN_335f(EnemyFrenzyBuffer - 0x12, param_1);
  return;
}

// SM2MAIN:93ec
// Signature: [] -> []
void NoFrenzyCode(void) { return; }

// SM2MAIN:93ed
// Signature: [X] -> []
void EndFrenzy(byte param_1) {
  byte bVar1;

  bVar1 = 5;
  do {
    if (Enemy_ID[bVar1] == 0x11) {
      Enemy_State[bVar1] = 1;
    }
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  EnemyFrenzyBuffer = 0;
  Enemy_Flag[param_1] = 0;
  return;
}

// SM2MAIN:9406
// Signature: [X] -> []
void InitJumpGPTroopa(byte param_1) {
  Enemy_MovingDir[param_1] = 2;
  SpriteVarData1[param_1] = 0xf4;
  Enemy_BoundBoxCtrl[param_1] = 3;
  return;
}

// SM2MAIN:9414
// Signature: [X] -> []
void InitBalPlatform(byte param_1) {
  bool bVar1;

  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
  if (SecondaryHardMode == 0) {
    PosPlatform(param_1, 2);
  }
  bVar1 = 0x7f < BalPlatformAlignment;
  Enemy_State[param_1] = BalPlatformAlignment;
  BalPlatformAlignment = 0xff;
  if (bVar1) {
    BalPlatformAlignment = param_1;
  }
  Enemy_MovingDir[param_1] = 0;
  PosPlatform(param_1, 0);
  InitDropPlatform(param_1);
  return;
}

// SM2MAIN:9438
// Signature: [X] -> []
void InitDropPlatform(byte param_1) {
  HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = 0xff;
  InitVStf(param_1);
  SPBBox(param_1);
  return;
}

// SM2MAIN:9440
// Signature: [X] -> []
void InitHoriPlatform(byte param_1) {
  SpriteVarData1[param_1] = 0;
  InitVStf(param_1);
  SPBBox(param_1);
  return;
}

// SM2MAIN:9447
// Signature: [X] -> []
void InitVertPlatform(byte param_1) {
  byte bVar1;
  char cVar2;

  cVar2 = 0x40;
  bVar1 = Enemy_Y_Position[param_1];
  if (0x7f < bVar1) {
    bVar1 = (bVar1 ^ 0xff) + 1;
    cVar2 = -0x40;
  }
  Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] = bVar1;
  SpriteVarData1[param_1] = cVar2 + Enemy_Y_Position[param_1];
  InitVStf(param_1);
  SPBBox(param_1);
  return;
}

// SM2MAIN:9460
// Signature: [X] -> []
void SPBBox(byte param_1) {
  byte bVar1;

  bVar1 = 5;
  if ((AreaType != 3) && (SecondaryHardMode == 0)) {
    bVar1 = 6;
  }
  Enemy_BoundBoxCtrl[param_1] = bVar1;
  return;
}

// SM2MAIN:9474
// Signature: [X] -> []
void LargeLiftUp(byte param_1) {
  PlatLiftUp(param_1);
  SPBBox(param_1);
  return;
}

// SM2MAIN:947a
// Signature: [X] -> []
void LargeLiftDown(byte param_1) {
  PlatLiftDown(param_1);
  SPBBox(param_1);
  return;
}

// SM2MAIN:9480
// Signature: [X] -> []
void PlatLiftUp(byte param_1) {
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = 0x10;
  SpriteVarData2[param_1] = 0xff;
  PosPlatform(param_1, 1);
  Enemy_BoundBoxCtrl[param_1] = 4;
  return;
}

// SM2MAIN:948c
// Signature: [X] -> []
void PlatLiftDown(byte param_1) {
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = 0xf0;
  SpriteVarData2[param_1] = 0;
  PosPlatform(param_1, 1);
  Enemy_BoundBoxCtrl[param_1] = 4;
  return;
}

// SM2MAIN:94a6
// Signature: [X, Y] -> []
void PosPlatform(byte param_1, byte param_2) {
  byte bVar1;
  byte bVar2;

  bVar1 = Enemy_X_Position[param_1];
  bVar2 = PlatPosDataLow[param_2];
  Enemy_X_Position[param_1] = bVar1 + bVar2;
  Enemy_PageLoc[param_1] = Enemy_PageLoc[param_1] + PlatPosDataHigh[param_2] + CARRY1(bVar1, bVar2);
  return;
}

// SM2MAIN:94b6
// Signature: [] -> []
void EndOfEnemyInitCode(void) { return; }

// SM2MAIN:94b7
// Signature: [] -> [X]
byte RunEnemyObjectsCore(void) {
  byte bVar1;
  byte bVar2;

  bVar1 = 0;
  bVar2 = Enemy_ID[ObjectOffset];
  if (bVar2 >= 0x15) {
    bVar1 = (bVar2 - 0x14) - (bVar2 < 0x15);
  }
  bVar2 = FUN_337b(bVar1, ObjectOffset);
  return bVar2;
}

// SM2MAIN:950b
// Signature: [] -> []
void NoRunCode(void) { return; }

// SM2MAIN:950c
// Signature: [X] -> [X]
byte RunRetainerObj(byte param_1) {
  byte bVar1;
  struct_xyi sVar2;
  struct_axr00 sVar3;

  sVar2 = GetEnemyOffscreenBits(param_1);
  sVar3 = RelativeEnemyPosition(sVar2.x);
  bVar1 = EnemyGfxHandler(sVar3.x);
  return bVar1;
}

// SM2MAIN:9515
// Signature: [X] -> [X]
byte RunNormalEnemies(byte param_1) {
  byte bVar1;
  struct_xyi sVar2;
  struct_axr00 sVar3;

  Enemy_SprAttrib[param_1] = 0;
  sVar2 = GetEnemyOffscreenBits(param_1);
  sVar3 = RelativeEnemyPosition(sVar2.x);
  bVar1 = EnemyGfxHandler(sVar3.x);
  bVar1 = GetEnemyBoundBox(bVar1);
  bVar1 = EnemyToBGCollisionDet(bVar1);
  bVar1 = EnemiesCollision(bVar1);
  bVar1 = PlayerEnemyCollision(bVar1);
  if (TimerControl == 0) {
    bVar1 = EnemyMovementSubs(bVar1);
  }
  OffscreenBoundsCheck(bVar1);
  return bVar1;
}

// SM2MAIN:953a
// Signature: [X] -> [X]
byte EnemyMovementSubs(byte param_1) {
  byte bVar1;

  bVar1 = FUN_3407(Enemy_ID[param_1], param_1);
  return bVar1;
}

// SM2MAIN:9569
// Signature: [] -> []
void NoMoveCode(void) { return; }

// SM2MAIN:956a
// Signature: [X] -> [X]
byte RunBowserFlame(byte param_1) {
  byte bVar1;
  struct_xyi sVar2;
  struct_axr00 sVar3;

  bVar1 = ProcBowserFlame(param_1);
  sVar2 = GetEnemyOffscreenBits(bVar1);
  sVar3 = RelativeEnemyPosition(sVar2.x);
  bVar1 = GetEnemyBoundBox(sVar3.x);
  bVar1 = PlayerEnemyCollision(bVar1);
  OffscreenBoundsCheck(bVar1);
  return bVar1;
}

// SM2MAIN:957c
// Signature: [X] -> [X]
byte RunFirebarObj(byte param_1) {
  byte bVar1;

  bVar1 = ProcFirebar(param_1);
  OffscreenBoundsCheck(bVar1);
  return bVar1;
}

// SM2MAIN:9582
// Signature: [X] -> [X]
byte RunSmallPlatform(byte param_1) {
  byte bVar1;
  struct_xyi sVar2;
  struct_axr00 sVar3;

  sVar2 = GetEnemyOffscreenBits(param_1);
  sVar3 = RelativeEnemyPosition(sVar2.x);
  bVar1 = SmallPlatformBoundBox(sVar3.x);
  bVar1 = SmallPlatformCollision(bVar1);
  sVar3 = RelativeEnemyPosition(bVar1);
  bVar1 = DrawSmallPlatform(sVar3.x);
  MoveSmallPlatform(bVar1);
  OffscreenBoundsCheck(bVar1);
  return bVar1;
}

// SM2MAIN:959a
// Signature: [X] -> [X]
byte RunLargePlatform(byte param_1) {
  byte bVar1;
  struct_xyi sVar2;
  struct_axr00 sVar3;

  sVar2 = GetEnemyOffscreenBits(param_1);
  sVar3 = RelativeEnemyPosition(sVar2.x);
  bVar1 = LargePlatformBoundBox(sVar3.x);
  bVar1 = LargePlatformCollision(bVar1);
  if (TimerControl == 0) {
    bVar1 = LargePlatformSubroutines(bVar1);
  }
  sVar3 = RelativeEnemyPosition(bVar1);
  bVar1 = DrawLargePlatform(sVar3.x);
  OffscreenBoundsCheck(bVar1);
  return bVar1;
}

// SM2MAIN:95b7
// Signature: [X] -> [X]
byte LargePlatformSubroutines(byte param_1) {
  byte bVar1;

  bVar1 = FUN_345f(Enemy_ID[param_1] - 0x24, param_1);
  return bVar1;
}

// SM2MAIN:95cd
// Signature: [X] -> [A]
byte EraseEnemyObject(byte param_1) {
  Enemy_Flag[param_1] = 0;
  Enemy_ID[param_1] = 0;
  Enemy_State[param_1] = 0;
  FloateyNum_Control[param_1] = 0;
  EnemyIntervalTimer[param_1] = 0;
  ShellChainCounter[param_1] = 0;
  Enemy_SprAttrib[param_1] = 0;
  EnemyFrameTimer[param_1] = 0;
  return 0;
}

// SM2MAIN:95e5
// Signature: [X] -> [X]
byte MovePodoboo(byte param_1) {
  byte bVar1;

  if (EnemyIntervalTimer[param_1] == 0) {
    InitPodoboo(param_1);
    bVar1 = PseudoRandomBitReg[param_1 + 1];
    CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = bVar1 | 0x80;
    EnemyIntervalTimer[param_1] = bVar1 & 0xf | 6;
    SpriteVarData2[param_1] = 0xf9;
  }
  bVar1 = MoveJ_EnemyVertically(param_1);
  return bVar1;
}

// SM2MAIN:960d
// Signature: [X] -> [X]
byte ProcHammerBro(byte param_1) {
  byte bVar1;
  struct_xci sVar2;

  if ((Enemy_State[param_1] & 0x20) != 0) {
    bVar1 = MoveDefeatedEnemy(param_1);
    return bVar1;
  }
  if (HammerBroJumpTimer[param_1] != 0) {
    HammerBroJumpTimer[param_1] = HammerBroJumpTimer[param_1] - 1;
    if ((Enemy_OffscreenBits & 0xc) != 0) {
      bVar1 = MoveHammerBroXDir(param_1);
      return bVar1;
    }
    if (HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] == 0) {
      HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = HammerThrowTmrData[SecondaryHardMode];
      sVar2 = SpawnHammerObj();
      param_1 = sVar2.x;
      if (sVar2.c != false) {
        Enemy_State[param_1] = Enemy_State[param_1] | 8;
        bVar1 = MoveHammerBroXDir(param_1);
        return bVar1;
      }
    }
    HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] - 1;
    bVar1 = MoveHammerBroXDir(param_1);
    return bVar1;
  }
  if ((Enemy_State[param_1] & 7) == 1) {
    bVar1 = MoveHammerBroXDir(param_1);
    return bVar1;
  }
  if (0x7f < Enemy_Y_Position[param_1]) {
    bVar1 = SetHJ(param_1, 0xfa, 0);
    return bVar1;
  }
  if (Enemy_Y_Position[param_1] < 0x70) {
    bVar1 = SetHJ(param_1, 0xfd, 1);
    return bVar1;
  }
  if ((PseudoRandomBitReg[param_1 + 1] & 1) != 0) {
    bVar1 = SetHJ(param_1, 0xfd, 0);
    return bVar1;
  }
  bVar1 = SetHJ(param_1, 0xfa, 0);
  return bVar1;
}

// SM2MAIN:966c
// Signature: [X, Y, r00] -> [X]
byte SetHJ(byte param_1, byte param_2, byte param_3) {
  byte bVar1;

  SpriteVarData2[param_1] = param_2;
  Enemy_State[param_1] = Enemy_State[param_1] | 1;
  bVar1 = param_3 & PseudoRandomBitReg[param_1 + 2];
  if (SecondaryHardMode == 0) {
    bVar1 = 0;
  }
  EnemyFrameTimer[param_1] = HammerBroJumpLData[bVar1];
  HammerBroJumpTimer[param_1] = PseudoRandomBitReg[param_1 + 1] | 0xc0;
  bVar1 = MoveHammerBroXDir(param_1);
  return bVar1;
}

// SM2MAIN:968d
// Signature: [X] -> [X]
byte MoveHammerBroXDir(byte param_1) {
  byte bVar1;
  struct_ncr00 sVar2;

  bVar1 = 0xfc;
  if ((FrameCounter & 0x40) == 0) {
    bVar1 = 4;
  }
  SpriteVarData1[param_1] = bVar1;
  bVar1 = 1;
  sVar2 = PlayerEnemyDiff(param_1);
  if ((!sVar2.n) && (bVar1 += 1, EnemyIntervalTimer[param_1] == 0)) {
    SpriteVarData1[param_1] = 0xf8;
  }
  Enemy_MovingDir[param_1] = bVar1;
  bVar1 = MoveNormalEnemy(param_1);
  return bVar1;
}

// SM2MAIN:96ac
// Signature: [X] -> [X]
byte MoveNormalEnemy(byte param_1) {
  byte bVar1;
  byte bVar2;
  struct_axi sVar3;
  byte bStack0000;

  bVar2 = 0;
  if ((Enemy_State[param_1] & 0x40) == 0) {
    if ((bool)(Enemy_State[param_1] >> 7)) {
      goto SteadM;
    }
    if ((Enemy_State[param_1] & 0x20) != 0) {
      bVar2 = MoveDefeatedEnemy(param_1);
      return bVar2;
    }
    bVar1 = Enemy_State[param_1] & 7;
    if (bVar1 == 0) {
      goto SteadM;
    }
    if ((bVar1 != 5) && (2 < bVar1)) {
      if (EnemyIntervalTimer[param_1] == 0) {
        Enemy_State[param_1] = 0;
        bVar2 = FrameCounter & 1;
        Enemy_MovingDir[param_1] = bVar2 + 1;
        if (PrimaryHardMode != 0) {
          bVar2 += 2;
        }
        SpriteVarData1[param_1] = RevivedXSpeed[bVar2];
        return param_1;
      }
      if ((EnemyIntervalTimer[param_1] == 0xe) && (Enemy_ID[param_1] == 6)) {
        EraseEnemyObject(param_1);
      }
      return param_1;
    }
  }
  param_1 = MoveD_EnemyVertically(param_1);
  bVar2 = 0;
  if (Enemy_State[param_1] != 2) {
    if (((Enemy_State[param_1] & 0x40) != 0) && (Enemy_ID[param_1] != 0x2e)) {
      if (Enemy_ID[param_1] == 0x2e) {
        goto MEHor;
      }
      bVar2 = 1;
    }
SteadM:
    bStack0000 = SpriteVarData1[param_1];
    if (0x7f < bStack0000) {
      bVar2 += 2;
    }
    SpriteVarData1[param_1] = bStack0000 + XSpeedAdderData[bVar2];
    sVar3 = MoveEnemyHorizontally(param_1);
    SpriteVarData1[sVar3.x] = bStack0000;
    return sVar3.x;
  }
MEHor:
  sVar3 = MoveEnemyHorizontally(param_1);
  return sVar3.x;
}

// SM2MAIN:971a
// Signature: [X] -> [X]
byte MoveDefeatedEnemy(byte param_1) {
  byte bVar1;
  struct_axi sVar2;

  bVar1 = MoveD_EnemyVertically(param_1);
  sVar2 = MoveEnemyHorizontally(bVar1);
  return sVar2.x;
}

// SM2MAIN:972e
// Signature: [X] -> [X]
byte MoveJumpingEnemy(byte param_1) {
  byte bVar1;
  struct_axi sVar2;

  bVar1 = MoveJ_EnemyVertically(param_1);
  sVar2 = MoveEnemyHorizontally(bVar1);
  return sVar2.x;
}

// SM2MAIN:9734
// Signature: [X] -> [X]
byte ProcMoveRedPTroopa(byte param_1) {
  byte bVar1;

  if (((SpriteVarData2[param_1] | CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1])
       == 0)
      && (BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = 0,
          Enemy_Y_Position[param_1] < Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1])) {
    if ((FrameCounter & 7) == 0) {
      Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 1;
    }
    return param_1;
  }
  if (SpriteVarData1[param_1] <= Enemy_Y_Position[param_1]) {
    bVar1 = MoveRedPTroopaUp(param_1);
    return bVar1;
  }
  bVar1 = MoveRedPTroopaDown(param_1);
  return bVar1;
}

// SM2MAIN:975a
// Signature: [X] -> [X]
byte MoveFlyGreenPTroopa(byte param_1) {
  byte bVar1;
  char cVar2;
  struct_xr00i sVar3;

  XMoveCntr_GreenPTroopa(param_1);
  sVar3 = MoveWithXMCntrs(param_1);
  bVar1 = sVar3.x;
  cVar2 = 1;
  if ((FrameCounter & 3) == 0) {
    if ((FrameCounter & 0x40) == 0) {
      cVar2 = -1;
    }
    Enemy_Y_Position[bVar1] = Enemy_Y_Position[bVar1] + cVar2;
  }
  return bVar1;
}

// SM2MAIN:977a
// Signature: [X] -> []
void XMoveCntr_GreenPTroopa(byte param_1) {
  XMoveCntr_Platform(0x13, param_1);
  return;
}

// SM2MAIN:977c
// Signature: [A, X] -> []
void XMoveCntr_Platform(byte param_1, byte param_2) {
  if ((FrameCounter & 3) != 0) {
    return;
  }
  if ((bool)(SpriteVarData2[param_2] & 1)) {
    if (SpriteVarData1[param_2] != 0) {
      SpriteVarData1[param_2] = SpriteVarData1[param_2] - 1;
      return;
    }
  } else if (SpriteVarData1[param_2] != param_1) {
    SpriteVarData1[param_2] = SpriteVarData1[param_2] + 1;
    return;
  }
  SpriteVarData2[param_2] = SpriteVarData2[param_2] + 1;
  return;
}

// SM2MAIN:979b
// Signature: [X] -> [X, r00]
struct_xr00i MoveWithXMCntrs(byte param_1) {
  byte bVar1;
  struct_axi sVar2;
  struct_xr00i sVar3;
  byte bStack0000;

  bStack0000 = SpriteVarData1[param_1];
  bVar1 = 1;
  if ((SpriteVarData2[param_1] & 2) == 0) {
    SpriteVarData1[param_1] = (SpriteVarData1[param_1] ^ 0xff) + 1;
    bVar1 = 2;
  }
  Enemy_MovingDir[param_1] = bVar1;
  sVar2 = MoveEnemyHorizontally(param_1);
  sVar3.i = sVar2.i;
  sVar3.x = sVar2.x;
  SpriteVarData1[sVar3.x] = bStack0000;
  sVar3.r00 = sVar2.a;
  return sVar3;
}

// SM2MAIN:97be
// Signature: [X, C] -> [X]
byte MoveBloober(byte param_1, bool param_2) {
  byte bVar1;
  byte bVar2;
  struct_ncr00 sVar3;

  if ((Enemy_State[param_1] & 0x20) != 0) {
    bVar2 = MoveEnemySlowVert(param_1);
    return bVar2;
  }
  if ((PseudoRandomBitReg[param_1 + 1] & BlooberBitmasks[SecondaryHardMode]) == 0) {
    param_2 = (bool)(param_1 & 1);
    if ((param_2 == false) || (bVar2 = Player_MovingDir, !param_2)) {
      bVar2 = 2;
      sVar3 = PlayerEnemyDiff(param_1);
      param_2 = sVar3.c;
      if (sVar3.n != false) {
        bVar2 -= 1;
      }
    }
    Enemy_MovingDir[param_1] = bVar2;
  }
  ProcSwimmingB(param_1, param_2);
  if (0x1f
      < (byte)(Enemy_Y_Position[param_1] - CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1])) {
    Enemy_Y_Position[param_1]
        = Enemy_Y_Position[param_1] - CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];
  }
  if (Enemy_MovingDir[param_1] == 1) {
    bVar2 = Enemy_X_Position[param_1];
    bVar1 = SpriteVarData1[param_1];
    Enemy_X_Position[param_1] = bVar2 + bVar1;
    Enemy_PageLoc[param_1] = Enemy_PageLoc[param_1] + CARRY1(bVar2, bVar1);
    return param_1;
  }
  bVar2 = Enemy_X_Position[param_1];
  bVar1 = SpriteVarData1[param_1];
  Enemy_X_Position[param_1] = bVar2 - bVar1;
  Enemy_PageLoc[param_1] = Enemy_PageLoc[param_1] - (bVar2 < bVar1);
  return param_1;
}

// SM2MAIN:9814
// Signature: [X, C] -> []
void ProcSwimmingB(byte param_1, bool param_2) {
  byte bVar1;

  if ((SpriteVarData2[param_1] & 2) == 0) {
    if (!(bool)(SpriteVarData2[param_1] & 1)) {
      if ((FrameCounter & 7) == 0) {
        bVar1 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] + 1;
        CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = bVar1;
        SpriteVarData1[param_1] = bVar1;
        if (bVar1 == 2) {
          SpriteVarData2[param_1] = SpriteVarData2[param_1] + 1;
        }
      }
      return;
    }
    if ((FrameCounter & 7) == 0) {
      bVar1 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] - 1;
      CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = bVar1;
      SpriteVarData1[param_1] = bVar1;
      if (bVar1 == 0) {
        SpriteVarData2[param_1] = SpriteVarData2[param_1] + 1;
        EnemyIntervalTimer[param_1] = 2;
      }
    }
    return;
  }
  if ((EnemyIntervalTimer[param_1] == 0)
      && (SprObject_Y_Position[0] <= (byte)(Enemy_Y_Position[param_1] + 0x10 + param_2))) {
    SpriteVarData2[param_1] = 0;
    return;
  }
  if (!(bool)(FrameCounter & 1)) {
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 1;
  }
  return;
}

// SM2MAIN:986b
// Signature: [X] -> [X]
byte MoveBulletBill(byte param_1) {
  byte bVar1;
  struct_axi sVar2;

  if ((Enemy_State[param_1] & 0x20) != 0) {
    bVar1 = MoveJ_EnemyVertically(param_1);
    return bVar1;
  }
  SpriteVarData1[param_1] = 0xe8;
  sVar2 = MoveEnemyHorizontally(param_1);
  return sVar2.x;
}

// SM2MAIN:987f
// Signature: [X] -> [X]
byte MoveSwimmingCheepCheep(byte param_1) {
  bool bVar1;
  byte bVar2;
  byte bVar3;

  if ((Enemy_State[param_1] & 0x20) != 0) {
    bVar3 = MoveEnemySlowVert(param_1);
    return bVar3;
  }
  bVar1 = Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1]
          < SwimCCXMoveData[(byte)(Enemy_ID[param_1] - 10)];
  Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1]
      = Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1]
        - SwimCCXMoveData[(byte)(Enemy_ID[param_1] - 10)];
  bVar3 = Enemy_X_Position[param_1];
  Enemy_X_Position[param_1] = bVar3 - bVar1;
  Enemy_PageLoc[param_1] = Enemy_PageLoc[param_1] - (bVar1 && (!bVar1 || bVar3 == 0));
  if (1 < param_1) {
    if (SpriteVarData1[param_1] < 0x10) {
      bVar1 = BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] < 0x40;
      BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1]
          = BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] - 0x40;
      bVar3 = Enemy_Y_Position[param_1];
      Enemy_Y_Position[param_1] = bVar3 - bVar1;
      bVar3 = Enemy_Y_HighPos[param_1] - (bVar1 && (!bVar1 || bVar3 == 0));
    } else {
      bVar3 = BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1];
      BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = bVar3 + 0x40;
      bVar2 = Enemy_Y_Position[param_1] + (0xbf < bVar3);
      Enemy_Y_Position[param_1] = bVar2;
      bVar3 = Enemy_Y_HighPos[param_1] + (0xbf < bVar3 && bVar2 == 0);
    }
    Enemy_Y_HighPos[param_1] = bVar3;
    bVar2 = 0;
    bVar3 = Enemy_Y_Position[param_1] - CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];
    if (0x7f < bVar3) {
      bVar2 = 0x10;
      bVar3 = (bVar3 ^ 0xff) + 1;
    }
    if (0xe < bVar3) {
      SpriteVarData1[param_1] = bVar2;
    }
  }
  return param_1;
}

// SM2MAIN:9971
// Signature: [X] -> [X]
byte ProcFirebar(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  struct_xyi sVar4;
  struct_axr00 sVar5;
  struct_r01r02r03 sVar6;
  struct_xr00r06 sVar7;

  sVar4 = GetEnemyOffscreenBits(param_1);
  bVar3 = sVar4.x;
  if ((Enemy_OffscreenBits & 8) == 0) {
    if (TimerControl == 0) {
      bVar2 = FirebarSpin(FirebarSpinSpeed[bVar3], bVar3);
      SpriteVarData2[bVar3] = bVar2 & 0x1f;
    }
    MysterySpriteThing4 = SpriteVarData2[bVar3];
    if ((0x1e < Enemy_ID[bVar3]) && ((MysterySpriteThing4 == 8 || (MysterySpriteThing4 == 0x18)))) {
      MysterySpriteThing4 += 1;
      SpriteVarData2[bVar3] = MysterySpriteThing4;
    }
    sVar5 = RelativeEnemyPosition(bVar3);
    bVar3 = sVar5.x;
    GetFirebarPosition(sVar5.a, sVar5.r00);
    bVar1 = Enemy_Rel_YPos;
    bVar3 = Enemy_SprDataOffset[bVar3];
    Sprite_Data[bVar3] = Enemy_Rel_YPos;
    bVar2 = Enemy_Rel_XPos;
    Sprite_Data[bVar3 + 3] = Enemy_Rel_XPos;
    sVar7 = FirebarCollision(bVar3, 1, bVar2, bVar1);
    bVar2 = sVar7.r06;
    MysterySpriteThing3 = 5;
    if (0x1e < Enemy_ID[sVar7.x]) {
      MysterySpriteThing3 = 0xb;
    }
    bVar1 = 0;
    do {
      sVar6 = GetFirebarPosition(MysterySpriteThing4, bVar1);
      sVar7 = DrawFirebar_Collision(bVar1, sVar6.r01, sVar6.r02, sVar6.r03, bVar2);
      bVar2 = sVar7.r06;
      bVar3 = sVar7.x;
      if (sVar7.r00 == 4) {
        bVar2 = Enemy_SprDataOffset[DuplicateObj_Offset];
      }
      bVar1 = sVar7.r00 + 1;
    } while (bVar1 < MysterySpriteThing3);
  }
  return bVar3;
}

// SM2MAIN:99f0
// Signature: [r00, r01, r02, r03, r06] -> [X, r00, r06]
struct_xr00r06 DrawFirebar_Collision(byte param_1, byte param_2, byte param_3, byte param_4, byte param_5) {
  byte bVar1;
  byte bVar2;
  bool bVar3;
  struct_xr00r06 sVar4;

  if (!(bool)(param_4 & 1)) {
    param_2 = (param_2 ^ 0xff) + 1 + (param_4 & 1);
  }
  bVar1 = param_2 + Enemy_Rel_XPos;
  Sprite_Data[param_5 + 3] = bVar1;
  if (bVar1 < Enemy_Rel_XPos) {
    bVar2 = Enemy_Rel_XPos - bVar1;
  } else {
    bVar2 = bVar1 - Enemy_Rel_XPos;
  }
  if (bVar2 < 0x59) {
    bVar2 = Enemy_Rel_YPos;
    if (Enemy_Rel_YPos != 0xf8) {
      bVar3 = (bool)(param_4 >> 1 & 1);
      if (!bVar3) {
        param_3 = (param_3 ^ 0xff) + 1 + bVar3;
      }
      bVar2 = param_3 + Enemy_Rel_YPos;
    }
  } else {
    bVar2 = 0xf8;
  }
  Sprite_Data[param_5] = bVar2;
  sVar4 = FirebarCollision(param_5, param_1, bVar1, bVar2);
  return sVar4;
}

// SM2MAIN:9a3d
// Signature: [Y, r00, r06, r07] -> [X, r00, r06]
struct_xr00r06 FirebarCollision(byte param_1, byte param_2, byte param_3, byte param_4) {
  ushort uVar1;
  byte bVar2;
  byte abVar3;
  byte bVar4;
  struct_xr00r06 sVar5;
  byte bStack0000;

  DrawFirebar(param_1);
  bStack0000 = param_1;
  if (((StarInvincibleTimer | TimerControl) != 0) || (SprObject_Y_HighPos[0] != 1)) {
NoColFB:
    sVar5.r00 = param_2;
    sVar5.x = ObjectOffset;
    sVar5.r06 = bStack0000 + 4;
    return sVar5;
  }
  if ((PlayerSize != 0) || (bVar2 = 0, abVar3 = SprObject_Y_Position[0], CrouchingFlag != 0)) {
    bVar2 = 2;
    abVar3 = SprObject_Y_Position[0] + 0x18;
  }
  do {
    bVar4 = abVar3 - param_4;
    if (0x7f < bVar4) {
      bVar4 = (bVar4 ^ 0xff) + 1;
    }
    if ((bVar4 < 8) && (param_3 < 0xf0)) {
      bVar4 = (Sprite_Data[7] + 4) - param_3;
      if (0x7f < bVar4) {
        bVar4 = (bVar4 ^ 0xff) + 1;
      }
      if (bVar4 < 8) {
        Enemy_MovingDir[0] = 1;
        if ((byte)(Sprite_Data[7] + 4) < param_3) {
          Enemy_MovingDir[0] = 2;
        }
        InjurePlayer();
        goto NoColFB;
      }
    }
    if (bVar2 == 2) {
      goto NoColFB;
    }
    uVar1 = (ushort)bVar2;
    bVar2 += 1;
    abVar3 = SprObject_Y_Position[0] + FirebarYPos[uVar1];
  } while (true);
}

// SM2MAIN:9ac3
// Signature: [A, r00] -> [r01, r02, r03]
struct_r01r02r03 GetFirebarPosition(byte param_1, byte param_2) {
  byte bVar1;
  byte bVar2;
  struct_r01r02r03 sVar3;

  bVar1 = param_1 & 0xf;
  if (8 < bVar1) {
    bVar1 = (bVar1 ^ 0xf) + 1;
  }
  bVar2 = param_1 + 8 & 0xf;
  if (8 < bVar2) {
    bVar2 = (bVar2 ^ 0xf) + 1;
  }
  sVar3.r02 = FirebarPosLookupTbl[(byte)(FirebarTblOffsets[param_2] + bVar2)];
  sVar3.r01 = FirebarPosLookupTbl[(byte)(FirebarTblOffsets[param_2] + bVar1)];
  sVar3.r03 = FirebarMirrorData[param_1 >> 3];
  return sVar3;
}

// SM2MAIN:9b14
// Signature: [X] -> [X]
byte MoveFlyingCheepCheep(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  struct_axi sVar4;

  if ((Enemy_State[param_1] & 0x20) != 0) {
    Enemy_SprAttrib[param_1] = 0;
    bVar1 = MoveJ_EnemyVertically(param_1);
    return bVar1;
  }
  sVar4 = MoveEnemyHorizontally(param_1);
  bVar2 = SetXMoveAmt(5, sVar4.x, 0xd);
  bVar3 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[bVar2] >> 4;
  bVar1 = Enemy_Y_Position[bVar2] - PRandomSubtracter[bVar3];
  if (0x7f < bVar1) {
    bVar1 = (bVar1 ^ 0xff) + 1;
  }
  if (bVar1 < 8) {
    bVar1 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[bVar2];
    CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[bVar2] = bVar1 + 0x10;
    bVar3 = (byte)(bVar1 + 0x10) >> 4;
  }
  Enemy_SprAttrib[bVar2] = FlyCCBPriority[bVar3];
  return bVar2;
}

// SM2MAIN:9b5d
// Signature: [X] -> [X]
byte MoveLakitu(byte param_1) {
  byte bVar1;
  struct_axi sVar2;

  if ((Enemy_State[param_1] & 0x20) == 0) {
    if (Enemy_State[param_1] == 0) {
      EnemyFrenzyBuffer = 0x12;
      bVar1 = PlayerLakituDiff(param_1, LakituDiffAdj[0], LakituDiffAdj[1], LakituDiffAdj[2]);
    } else {
      SpriteVarData2[param_1] = 0;
      EnemyFrenzyBuffer = 0;
      bVar1 = 0x10;
    }
    SpriteVarData1[param_1] = bVar1;
    bVar1 = 1;
    if ((SpriteVarData2[param_1] & 1) == 0) {
      SpriteVarData1[param_1] = (SpriteVarData1[param_1] ^ 0xff) + 1;
      bVar1 = 2;
    }
    Enemy_MovingDir[param_1] = bVar1;
    sVar2 = MoveEnemyHorizontally(param_1);
    return sVar2.x;
  }
  bVar1 = MoveD_EnemyVertically(param_1);
  return bVar1;
}

// SM2MAIN:9ba1
// Signature: [X, r01, r02, r03] -> [A]
byte PlayerLakituDiff(byte param_1, byte param_2, byte param_3, byte param_4) {
  byte bVar1;
  byte bVar2;
  char cVar3;
  struct_ncr00 sVar4;

  bVar2 = 0;
  sVar4 = PlayerEnemyDiff(param_1);
  bVar1 = sVar4.r00;
  if (sVar4.n != false) {
    bVar2 += 1;
    bVar1 = (bVar1 ^ 0xff) + 1;
  }
  if (((0x3b < bVar1) && (bVar1 = 0x3c, Enemy_ID[param_1] == 0x11)) && (bVar2 != SpriteVarData2[param_1])) {
    if (SpriteVarData2[param_1] != 0) {
      SpriteVarData1[param_1] = SpriteVarData1[param_1] - 1;
      if (SpriteVarData1[param_1] != 0) {
        return SpriteVarData1[param_1];
      }
    }
    SpriteVarData2[param_1] = bVar2;
  }
  bVar1 = (bVar1 & 0x3c) >> 2;
  cVar3 = 0;
  if ((PlayerSpriteVarData1[0] != 0) && (ScrollAmount != 0)) {
    cVar3 = 1;
    if ((0x18 < PlayerSpriteVarData1[0]) && (1 < ScrollAmount)) {
      cVar3 = 2;
    }
    if (((Enemy_ID[param_1] != 0x12) || (PlayerSpriteVarData1[0] == 0)) && (SpriteVarData2[param_1] == 0)) {
      cVar3 = 0;
    }
  }
  if ((cVar3 != 0) && (param_2 = param_3, cVar3 != 1)) {
    param_2 = param_4;
  }
  do {
    param_2 -= 1;
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  return param_2;
}

// SM2MAIN:9c21
// Signature: [r00] -> []
void BridgeCollapse(byte param_1) {
  byte bVar1;
  byte bVar2;

  if (Enemy_ID[BowserFront_Offset] == 0x2d) {
    ObjectOffset = BowserFront_Offset;
    if (Enemy_State[BowserFront_Offset] == 0) {
      BowserFeetCounter -= 1;
      bVar1 = BowserFront_Offset;
      if (BowserFeetCounter == 0) {
        BowserFeetCounter = 4;
        BowserBodyControls ^= 1;
        bVar2 = VRAM_Buffer1_Offset + 1;
        RemBridge(0xc, bVar2, param_1, BridgeCollapseData[BridgeCollapseOffset], 0x22);
        bVar1 = ObjectOffset;
        MoveVOffset(bVar2);
        Square2SoundQueue = 8;
        NoiseSoundQueue = 1;
        BridgeCollapseOffset += 1;
        if (BridgeCollapseOffset == 0xf) {
          InitVStf(bVar1);
          Enemy_State[bVar1] = 0x40;
          Square2SoundQueue = 0x80;
        }
      }
      BowserGfxHandler(bVar1);
      return;
    }
    if (((Enemy_State[BowserFront_Offset] & 0x40) != 0) && (Enemy_Y_Position[BowserFront_Offset] < 0xe0)) {
      MoveD_Bowser(BowserFront_Offset);
      return;
    }
  }
  EventMusicQueue = 0x80;
  OperMode_Task += 1;
  KillAllEnemies();
  return;
}

// SM2MAIN:9c44
// Signature: [X] -> [X]
byte MoveD_Bowser(byte param_1) {
  byte bVar1;

  bVar1 = MoveEnemySlowVert(param_1);
  bVar1 = BowserGfxHandler(bVar1);
  return bVar1;
}

// SM2MAIN:9c9a
// Signature: [X] -> [X]
byte RunBowser(byte param_1) {
  byte bVar1;
  byte bVar2;
  struct_xci sVar3;
  struct_ncr00 sVar4;

  if ((Enemy_State[param_1] & 0x20) != 0) {
    if (0xdf < Enemy_Y_Position[param_1]) {
      bVar1 = KillAllEnemies();
      return bVar1;
    }
    bVar1 = MoveD_Bowser(param_1);
    return bVar1;
  }
  EnemyFrenzyBuffer = 0;
  if (TimerControl != 0) {
    goto ChkFireB;
  }
  if (BowserBodyControls < 0x80) {
    BowserFeetCounter -= 1;
    if (BowserFeetCounter == 0) {
      BowserFeetCounter = 0x20;
      BowserBodyControls ^= 1;
    }
    if ((FrameCounter & 0xf) == 0) {
      Enemy_MovingDir[param_1] = 2;
    }
    if ((EnemyFrameTimer[param_1] != 0) && (sVar4 = PlayerEnemyDiff(param_1), sVar4.n != false)) {
      Enemy_MovingDir[param_1] = 1;
      BowserMovementSpeed = 2;
      EnemyFrameTimer[param_1] = 0x20;
      BowserFireBreathTimer = 0x20;
      if (199 < Enemy_X_Position[param_1]) {
        goto HammerChk;
      }
    }
    if ((FrameCounter & 3) == 0) {
      if (Enemy_X_Position[param_1] == BowserOrigXPos) {
        MaxRangeFromOrigin = PRandomRange[PseudoRandomBitReg[param_1] & 3];
      }
      bVar1 = Enemy_X_Position[param_1] + BowserMovementSpeed;
      Enemy_X_Position[param_1] = bVar1;
      if (Enemy_MovingDir[param_1] != 1) {
        bVar2 = 0xff;
        bVar1 -= BowserOrigXPos;
        if (0x7f < bVar1) {
          bVar1 = (bVar1 ^ 0xff) + 1;
          bVar2 = 1;
        }
        if (MaxRangeFromOrigin <= bVar1) {
          BowserMovementSpeed = bVar2;
        }
      }
    }
  }
HammerChk:
  if (EnemyFrameTimer[param_1] == 0) {
    param_1 = MoveEnemySlowVert(param_1);
    if ((4 < WorldNumber) && ((FrameCounter & 3) == 0)) {
      sVar3 = SpawnHammerObj();
      param_1 = sVar3.x;
    }
    if (0x7f < Enemy_Y_Position[param_1]) {
      EnemyFrameTimer[param_1] = PRandomRange[PseudoRandomBitReg[param_1] & 3];
    }
  } else if (EnemyFrameTimer[param_1] == 1) {
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
    InitVStf(param_1);
    SpriteVarData2[param_1] = 0xfe;
  }
ChkFireB:
  do {
    if ((WorldNumber != 7) && (4 < WorldNumber)) {
      bVar1 = BowserGfxHandler(param_1);
      return bVar1;
    }
    if (BowserFireBreathTimer != 0) {
      bVar1 = BowserGfxHandler(param_1);
      return bVar1;
    }
    BowserFireBreathTimer = 0x20;
    BowserBodyControls ^= 0x80;
  } while (0x7f < BowserBodyControls);
  BowserFireBreathTimer = SetFlameTimer();
  if (SecondaryHardMode != 0) {
    BowserFireBreathTimer -= 0x10;
  }
  EnemyFrenzyBuffer = 0x15;
  bVar1 = BowserGfxHandler(param_1);
  return bVar1;
}

// SM2MAIN:9ca6
// Signature: [] -> [X]
byte KillAllEnemies(void) {
  byte bVar1;
  byte bVar2;

  bVar2 = 4;
  do {
    bVar1 = EraseEnemyObject(bVar2);
    bVar2 -= 1;
  } while (bVar2 < 0x80);
  EnemyFrenzyBuffer = bVar1;
  return ObjectOffset;
}

// SM2MAIN:9db0
// Signature: [X] -> [X]
byte BowserGfxHandler(byte param_1) {
  byte bVar1;
  byte bVar2;
  char cVar3;
  byte bStack0000;

  bVar2 = ProcessBowserHalf(param_1);
  bVar1 = DuplicateObj_Offset;
  cVar3 = 0x10;
  if ((Enemy_MovingDir[bVar2] & 1) != 0) {
    cVar3 = -0x10;
  }
  Enemy_X_Position[DuplicateObj_Offset] = cVar3 + Enemy_X_Position[bVar2];
  Enemy_Y_Position[bVar1] = Enemy_Y_Position[bVar2] + 8;
  Enemy_State[bVar1] = Enemy_State[bVar2];
  Enemy_MovingDir[bVar1] = Enemy_MovingDir[bVar2];
  bVar1 = DuplicateObj_Offset;
  bStack0000 = ObjectOffset;
  ObjectOffset = DuplicateObj_Offset;
  Enemy_ID[DuplicateObj_Offset] = 0x2d;
  ProcessBowserHalf(bVar1);
  ObjectOffset = bStack0000;
  BowserGfxFlag = 0;
  return bStack0000;
}

// SM2MAIN:9df1
// Signature: [X] -> [X]
byte ProcessBowserHalf(byte param_1) {
  byte bVar1;

  BowserGfxFlag += 1;
  bVar1 = RunRetainerObj(param_1);
  if (Enemy_State[bVar1] == 0) {
    Enemy_BoundBoxCtrl[bVar1] = 10;
    bVar1 = GetEnemyBoundBox(bVar1);
    bVar1 = PlayerEnemyCollision(bVar1);
    return bVar1;
  }
  return bVar1;
}

// SM2MAIN:9e0e
// Signature: [] -> [A]
byte SetFlameTimer(void) {
  byte bVar1;

  bVar1 = BowserFlameTimerCtrl;
  BowserFlameTimerCtrl = BowserFlameTimerCtrl + 1 & 7;
  return FlameTimerData[bVar1];
}

// SM2MAIN:9e20
// Signature: [X] -> [X]
byte ProcBowserFlame(byte param_1) {
  bool bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  struct_xyi sVar6;
  struct_axr00 sVar7;

  if (TimerControl == 0) {
    bVar3 = 0x40;
    if (SecondaryHardMode != 0) {
      bVar3 = 0x60;
    }
    bVar1 = Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] < bVar3;
    Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1]
        = Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] - bVar3;
    bVar3 = Enemy_X_Position[param_1];
    Enemy_X_Position[param_1] = (bVar3 - 1) - bVar1;
    Enemy_PageLoc[param_1] = Enemy_PageLoc[param_1] - ((bVar1 || bVar3 == 0) && (!bVar1 || bVar3 < 2));
    if (Enemy_Y_Position[param_1]
        != FlameYPosData[BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1]]) {
      Enemy_Y_Position[param_1]
          = Enemy_Y_Position[param_1] + CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];
    }
  }
  sVar7 = RelativeEnemyPosition(param_1);
  bVar3 = sVar7.x;
  if (Enemy_State[bVar3] == 0) {
    bVar2 = 0x51;
    bVar5 = 2;
    if ((FrameCounter & 2) != 0) {
      bVar5 = 0x82;
    }
    bVar3 = Enemy_SprDataOffset[bVar3];
    bVar4 = 0;
    do {
      Sprite_Data[bVar3] = Enemy_Rel_YPos;
      Sprite_Data[bVar3 + 1] = bVar2;
      bVar2 += 1;
      Sprite_Data[bVar3 + 2] = bVar5;
      Sprite_Data[bVar3 + 3] = Enemy_Rel_XPos;
      Enemy_Rel_XPos += 8;
      bVar3 += 4;
      bVar4 += 1;
    } while (bVar4 < 3);
    sVar6 = GetEnemyOffscreenBits(ObjectOffset);
    bVar5 = Enemy_OffscreenBits;
    bVar3 = Enemy_SprDataOffset[sVar6.x];
    bVar2 = Enemy_OffscreenBits >> 1;
    if ((Enemy_OffscreenBits & 1) != 0) {
      Sprite_Data[bVar3 + 0xc] = 0xf8;
    }
    if ((bVar2 & 1) != 0) {
      Sprite_Data[bVar3 + 8] = 0xf8;
    }
    if ((bVar5 >> 2 & 1) != 0) {
      Sprite_Data[bVar3 + 4] = 0xf8;
    }
    if ((bVar5 >> 3 & 1) != 0) {
      Sprite_Data[bVar3] = 0xf8;
    }
    return sVar6.x;
  }
  return bVar3;
}

// SM2MAIN:9eca
// Signature: [X] -> [X]
byte RunFireworks(byte param_1) {
  byte bVar1;
  struct_axr00 sVar2;

  bVar1 = SpriteVarData2[param_1] - 1;
  SpriteVarData2[param_1] = bVar1;
  if (bVar1 == 0) {
    SpriteVarData2[param_1] = 8;
    SpriteVarData1[param_1] = SpriteVarData1[param_1] + 1;
    if (2 < SpriteVarData1[param_1]) {
      Enemy_Flag[param_1] = 0;
      Square2SoundQueue = 8;
      DigitModifier[4] = 5;
      bVar1 = EndAreaPoints();
      return bVar1;
    }
  }
  sVar2 = RelativeEnemyPosition(param_1);
  Fireball_Rel_YPos = Enemy_Rel_YPos;
  Fireball_Rel_XPos = Enemy_Rel_XPos;
  bVar1 = DrawExplosion_Fireworks(SpriteVarData1[sVar2.x], Enemy_SprDataOffset[sVar2.x]);
  return bVar1;
}

// SM2MAIN:9f0e
// Signature: [X] -> [X]
byte RunStarFlagObj(byte param_1) {
  byte bVar1;

  EnemyFrenzyBuffer = 0;
  if (StarFlagTaskControl < 5) {
    bVar1 = FUN_347f(StarFlagTaskControl, param_1);
    return bVar1;
  }
  return param_1;
}

// SM2MAIN:9f27
// Signature: [X] -> []
void GameTimerFireworks(byte param_1) {
  byte bVar1;

  if (GameTimerDisplaySMB2J[2] == CoinDisplay[1]) {
    if ((GameTimerDisplaySMB2J[2] & 1) == 0) {
      bVar1 = 0;
      FireworksCounter = 6;
    } else {
      bVar1 = 3;
      FireworksCounter = 3;
    }
  } else {
    bVar1 = 0;
    FireworksCounter = 0xff;
  }
  Enemy_State[param_1] = bVar1;
  StarFlagTaskControl = StarFlagTaskControl + 1;
  return;
}

// SM2MAIN:9f4b
// Signature: [] -> []
void StarFlagExit(void) { return; }

// SM2MAIN:9f4c
// Signature: [X] -> [X]
byte AwardGameTimerPoints(byte param_1) {
  byte bVar1;

  if ((byte)(GameTimerDisplaySMB2J[0] | GameTimerDisplaySMB2J[1] | GameTimerDisplaySMB2J[2]) != 0) {
    bVar1 = AwardTimerCastle();
    return bVar1;
  }
  StarFlagTaskControl = StarFlagTaskControl + 1;
  return param_1;
}

// SM2MAIN:9f57
// Signature: [] -> [X]
byte AwardTimerCastle(void) {
  byte bVar1;

  if ((FrameCounter & 4) != 0) {
    Square2SoundQueue = 0x10;
  }
  DigitModifier[5] = 0xff;
  DigitsMathRoutine(0x17);
  DigitModifier[5] = 5;
  bVar1 = EndAreaPoints();
  return bVar1;
}

// SM2MAIN:9f70
// Signature: [] -> [X]
byte EndAreaPoints(void) {
  byte bVar1;

  DigitsMathRoutine(0xb);
  bVar1 = WriteDigits(2);
  return bVar1;
}

// SM2MAIN:9f7a
// Signature: [X] -> [X]
byte RaiseFlagSetoffFWorks(byte param_1) {
  byte bVar1;

  if (0x71 < Enemy_Y_Position[param_1]) {
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
    bVar1 = DrawStarFlag(param_1);
    return bVar1;
  }
  if ((FireworksCounter != 0) && (FireworksCounter < 0x80)) {
    EnemyFrenzyBuffer = 0x16;
    bVar1 = DrawStarFlag(param_1);
    return bVar1;
  }
  bVar1 = DrawStarFlag(param_1);
  EnemyIntervalTimer[bVar1] = 6;
  StarFlagTaskControl = StarFlagTaskControl + 1;
  return bVar1;
}

// SM2MAIN:9f91
// Signature: [X] -> [X]
byte DrawStarFlag(byte param_1) {
  byte bVar1;
  byte bVar2;
  struct_axr00 sVar3;

  sVar3 = RelativeEnemyPosition(param_1);
  bVar2 = Enemy_SprDataOffset[sVar3.x];
  bVar1 = 3;
  do {
    Sprite_Data[bVar2] = Enemy_Rel_YPos + StarFlagYPosAdder[bVar1];
    Sprite_Data[bVar2 + 1] = StarFlagTileData[bVar1];
    Sprite_Data[bVar2 + 2] = 0x22;
    Sprite_Data[bVar2 + 3] = Enemy_Rel_XPos + StarFlagXPosAdder[bVar1];
    bVar2 += 4;
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  return ObjectOffset;
}

// SM2MAIN:9fce
// Signature: [X] -> [X]
byte DelayToAreaEnd(byte param_1) {
  byte bVar1;

  bVar1 = DrawStarFlag(param_1);
  if ((EnemyIntervalTimer[bVar1] == 0) && (EventMusicBuffer == 0)) {
    StarFlagTaskControl = StarFlagTaskControl + 1;
    return bVar1;
  }
  return bVar1;
}

// SM2MAIN:9fdc
// Signature: [X] -> []
void MovePiranhaPlant(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  struct_ncr00 sVar4;

  if ((Enemy_State[param_1] == 0) && (EnemyFrameTimer[param_1] == 0)) {
    if (SpriteVarData2[param_1] == 0) {
      if (SpriteVarData1[param_1] < 0x80) {
        sVar4 = PlayerEnemyDiff(param_1);
        bVar3 = sVar4.r00;
        if (sVar4.n != false) {
          bVar3 = (bVar3 ^ 0xff) + 1;
        }
        if (bVar3 < RAM(0x9ffe)) {
          goto PutinPipe;
        }
      }
      SpriteVarData1[param_1] = (SpriteVarData1[param_1] ^ 0xff) + 1;
      SpriteVarData2[param_1] = SpriteVarData2[param_1] + 1;
    }
    bVar3 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];
    if (0x7f < SpriteVarData1[param_1]) {
      bVar3 = BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1];
    }
    if ((((EnemyAttributeData[13] == 0x22) || ((FrameCounter & 1) != 0)) && (TimerControl == 0))
        && (bVar1 = Enemy_Y_Position[param_1], bVar2 = SpriteVarData1[param_1],
            Enemy_Y_Position[param_1] = bVar1 + bVar2, (byte)(bVar1 + bVar2) == bVar3)) {
      SpriteVarData2[param_1] = 0;
      EnemyFrameTimer[param_1] = 0x40;
    }
  }
PutinPipe:
  Enemy_SprAttrib[param_1] = 0x20;
  return;
}

// SM2MAIN:a043
// Signature: [A, X] -> [A]
byte FirebarSpin(byte param_1, byte param_2) {
  byte bVar1;

  if (FirebarSpinDirection[param_2] == 0) {
    bVar1 = SpriteVarData1[param_2];
    SpriteVarData1[param_2] = bVar1 + param_1;
    return SpriteVarData2[param_2] + CARRY1(bVar1, param_1);
  }
  bVar1 = SpriteVarData1[param_2];
  SpriteVarData1[param_2] = bVar1 - param_1;
  return SpriteVarData2[param_2] - (bVar1 < param_1);
}

// SM2MAIN:a065
// Signature: [X] -> [X]
byte BalancePlatform(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  struct_xr00r01 sVar4;
  byte bStack0000;

  if (Enemy_Y_HighPos[param_1] == 3) {
    EraseEnemyObject(param_1);
    return param_1;
  }
  bVar3 = Enemy_State[param_1];
  if ((0x7f < bVar3) || (Enemy_ID[bVar3] != 0x24)) {
    return param_1;
  }
  if (Enemy_MovingDir[param_1] != 0) {
    bVar3 = PlatformFall(param_1, bVar3);
    return bVar3;
  }
  if (Enemy_Y_Position[param_1] < 0x2e) {
    if (bVar3 != HammerThrowingTimer_Or_PlatformCollisionFlag[param_1]) {
      Enemy_Y_Position[param_1] = 0x2f;
      StopPlatforms(param_1, bVar3);
      return param_1;
    }
MakePlatformFall:
    bVar3 = InitPlatformFall(bVar3);
    return bVar3;
  }
  if (Enemy_Y_Position[bVar3] < 0x2e) {
    if (param_1 != HammerThrowingTimer_Or_PlatformCollisionFlag[param_1]) {
      Enemy_Y_Position[bVar3] = 0x2f;
      StopPlatforms(param_1, bVar3);
      return param_1;
    }
    goto MakePlatformFall;
  }
  bStack0000 = Enemy_Y_Position[param_1];
  bVar2 = HammerThrowingTimer_Or_PlatformCollisionFlag[param_1];
  if (bVar2 < 0x80) {
ColFlg:
    if (bVar2 == ObjectOffset) {
PlatDn:
      param_1 = MovePlatformDown(param_1);
      goto DoOtherPlatform;
    }
  } else {
    bVar2 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] + 5;
    bVar1 = SpriteVarData2[param_1]
            + (0xfa < CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1]);
    if (0x7f < bVar1) {
      goto PlatDn;
    }
    if (bVar1 == 0) {
      if (bVar2 < 0xb) {
        StopPlatforms(param_1, bVar3);
        goto DoOtherPlatform;
      }
      if (bVar2 < 0xb) {
        goto ColFlg;
      }
    }
  }
  param_1 = MovePlatformUp(param_1);
DoOtherPlatform:
  Enemy_Y_Position[Enemy_State[param_1]]
      = (bStack0000 - Enemy_Y_Position[param_1]) + Enemy_Y_Position[Enemy_State[param_1]];
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] < 0x80) {
    PositionPlayerOnVPlat(HammerThrowingTimer_Or_PlatformCollisionFlag[param_1]);
  }
  if (((SpriteVarData2[ObjectOffset]
        | CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[ObjectOffset])
       != 0)
      && (VRAM_Buffer1_Offset < 0x20)) {
    bVar3 = SpriteVarData2[ObjectOffset];
    bVar2 = ObjectOffset;
    bStack0000 = bVar3;
    sVar4 = SetupPlatformRope(bVar3, ObjectOffset);
    bVar1 = sVar4.x;
    VRAM_Buffer1[bVar1] = sVar4.r01;
    VRAM_Buffer1[bVar1 + 1] = sVar4.r00;
    VRAM_Buffer1[bVar1 + 2] = 2;
    if (SpriteVarData2[bVar2] < 0x80) {
      VRAM_Buffer1[bVar1 + 3] = 0xa2;
      VRAM_Buffer1[bVar1 + 4] = 0xa3;
    } else {
      VRAM_Buffer1[bVar1 + 3] = 0x24;
      VRAM_Buffer1[bVar1 + 4] = 0x24;
    }
    sVar4 = SetupPlatformRope(bVar3 ^ 0xff, Enemy_State[bVar2]);
    bVar3 = sVar4.x;
    VRAM_Buffer1[bVar3 + 5] = sVar4.r01;
    VRAM_Buffer1[bVar3 + 6] = sVar4.r00;
    VRAM_Buffer1[bVar3 + 7] = 2;
    if (bStack0000 < 0x80) {
      VRAM_Buffer1[bVar3 + 8] = 0x24;
      VRAM_Buffer1[bVar3 + 9] = 0x24;
    } else {
      VRAM_Buffer1[bVar3 + 8] = 0xa2;
      VRAM_Buffer1[bVar3 + 9] = 0xa3;
    }
    VRAM_Buffer1[bVar3 + 10] = 0;
    VRAM_Buffer1_Offset += 10;
  }
  return ObjectOffset;
}

// SM2MAIN:a17b
// Signature: [A, Y] -> [X, r00, r01]
struct_xr00r01 SetupPlatformRope(byte param_1, byte param_2) {
  bool bVar1;
  byte bVar2;
  byte bVar3;
  struct_xr00r01 sVar4;

  bVar3 = Enemy_X_Position[param_2];
  bVar1 = 0xf7 < bVar3;
  bVar2 = bVar3 + 8;
  if (SecondaryHardMode == 0) {
    bVar2 = bVar3 + 0x18;
    bVar1 = 0xef < (byte)(bVar3 + 8);
  }
  bVar3 = Enemy_Y_Position[param_2];
  if (0x7f < param_1) {
    bVar3 += 8;
  }
  bVar2 = (bVar3 & 0x38) * 4 + ((bVar2 & 0xf0) >> 3);
  if (0xe7 < Enemy_Y_Position[param_2]) {
    bVar2 &= 0xbf;
  }
  sVar4.r00 = bVar2;
  sVar4.x = VRAM_Buffer1_Offset;
  sVar4.r01 = (Enemy_PageLoc[param_2] + bVar1 & 1) << 2 | (bVar3 >> 7) << 1 | (byte)(bVar3 << 1) >> 7 | 0x20;
  return sVar4;
}

// SM2MAIN:a1d2
// Signature: [Y] -> [X]
byte InitPlatformFall(byte param_1) {
  byte bVar1;
  byte bVar2;
  struct_xyi sVar3;

  sVar3 = GetEnemyOffscreenBits(param_1);
  bVar2 = sVar3.y;
  bVar1 = sVar3.x;
  SetupFloateyNumber(6, bVar1);
  FloateyNum_X_Pos[bVar1] = SprObject_Rel_XPos[0];
  FloateyNum_Y_Pos[bVar1] = SprObject_Y_Position[0];
  Enemy_MovingDir[bVar1] = 1;
  StopPlatforms(bVar1, bVar2);
  return bVar1;
}

// SM2MAIN:a1eb
// Signature: [X, Y] -> []
void StopPlatforms(byte param_1, byte param_2) {
  byte bVar1;

  bVar1 = InitVStf(param_1);
  SpriteVarData2[param_2] = bVar1;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_2] = bVar1;
  return;
}

// SM2MAIN:a1f5
// Signature: [X, Y] -> [X]
byte PlatformFall(byte param_1, byte param_2) {
  byte bStack0000;

  bStack0000 = param_2;
  MoveFallingPlatform(param_1);
  MoveFallingPlatform(bStack0000);
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[ObjectOffset] < 0x80) {
    PositionPlayerOnVPlat(HammerThrowingTimer_Or_PlatformCollisionFlag[ObjectOffset]);
  }
  return ObjectOffset;
}

// SM2MAIN:a20d
// Signature: [X] -> [X]
byte YMovingPlatform(byte param_1) {
  byte bVar1;

  if (((SpriteVarData2[param_1] | CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1])
       == 0)
      && (BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = 0,
          Enemy_Y_Position[param_1] < Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1])) {
    if ((FrameCounter & 7) == 0) {
      Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 1;
    }
    ChkYPCollision(param_1);
    return param_1;
  }
  if (SpriteVarData1[param_1] <= Enemy_Y_Position[param_1]) {
    bVar1 = MovePlatformUp(param_1);
    ChkYPCollision(bVar1);
    return bVar1;
  }
  bVar1 = MovePlatformDown(param_1);
  ChkYPCollision(bVar1);
  return bVar1;
}

// SM2MAIN:a238
// Signature: [X] -> []
void ChkYPCollision(byte param_1) {
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] < 0x80) {
    PositionPlayerOnVPlat(param_1);
  }
  return;
}

// SM2MAIN:a241
// Signature: [X] -> [X]
byte XMovingPlatform(byte param_1) {
  byte bVar1;
  struct_xr00i sVar2;

  XMoveCntr_Platform(0xe, param_1);
  sVar2 = MoveWithXMCntrs(param_1);
  bVar1 = sVar2.x;
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[bVar1] < 0x80) {
    PositionPlayerOnHPlat(bVar1, sVar2.r00);
    return bVar1;
  }
  return bVar1;
}

// SM2MAIN:a24e
// Signature: [X, r00] -> []
void PositionPlayerOnHPlat(byte param_1, byte param_2) {
  char cVar1;

  cVar1 = CARRY1(SprObject_X_Position[0], param_2);
  if (0x7f < param_2) {
    cVar1 = -!(bool)cVar1;
  }
  SprObject_PageLoc[0] += cVar1;
  SprObject_X_Position[0] = SprObject_X_Position[0] + param_2;
  Platform_X_Scroll = param_2;
  PositionPlayerOnVPlat(param_1);
  return;
}

// SM2MAIN:a26b
// Signature: [X] -> [X]
byte DropPlatform(byte param_1) {
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] < 0x80) {
    param_1 = MoveDropPlatform(param_1);
    PositionPlayerOnVPlat(param_1);
  }
  return param_1;
}

// SM2MAIN:a277
// Signature: [X] -> [X]
byte RightPlatform(byte param_1) {
  byte bVar1;
  struct_axi sVar2;

  sVar2 = MoveEnemyHorizontally(param_1);
  bVar1 = sVar2.x;
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[bVar1] < 0x80) {
    SpriteVarData1[bVar1] = 0x10;
    PositionPlayerOnHPlat(bVar1, sVar2.a);
  }
  return bVar1;
}

// SM2MAIN:a289
// Signature: [X] -> []
void MoveLargeLiftPlat(byte param_1) {
  MoveLiftPlatforms(param_1);
  ChkYPCollision(param_1);
  return;
}

// SM2MAIN:a28f
// Signature: [X] -> []
void MoveSmallPlatform(byte param_1) {
  MoveLiftPlatforms(param_1);
  ChkSmallPlatCollision(param_1);
  return;
}

// SM2MAIN:a295
// Signature: [X] -> []
void MoveLiftPlatforms(byte param_1) {
  byte bVar1;

  if (TimerControl == 0) {
    bVar1 = BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1];
    BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1]
        = bVar1 + CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];
    Enemy_Y_Position[param_1]
        = Enemy_Y_Position[param_1] + SpriteVarData2[param_1]
          + CARRY1(bVar1, CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1]);
    return;
  }
  return;
}

// SM2MAIN:a2ab
// Signature: [X] -> []
void ChkSmallPlatCollision(byte param_1) {
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] != 0) {
    PositionPlayerOnS_Plat(HammerThrowingTimer_Or_PlatformCollisionFlag[param_1], param_1);
  }
  return;
}

// SM2MAIN:a2b4
// Signature: [X] -> []
void OffscreenBoundsCheck(byte param_1) {
  byte bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  byte abVar5;
  byte bVar6;
  bool bVar7;
  bool bVar8;

  if (Enemy_ID[param_1] != 0x14) {
    bVar1 = Enemy_ID[param_1];
    bVar7 = 4 < bVar1;
    if (((bVar1 == 5) || (bVar7 = 3 < bVar1, bVar1 == 4))
        || (bVar7 = 0xc < bVar1, abVar5 = ScreenEdgeOrLeft_X_Pos[0], bVar1 == 0xd)) {
      abVar5 = ScreenEdgeOrLeft_X_Pos[0] + 0x38 + bVar7;
      bVar7 = 199 < ScreenEdgeOrLeft_X_Pos[0] || bVar7 && abVar5 == 0;
    }
    bVar2 = 0x47 < abVar5;
    bVar3 = !bVar7;
    bVar4 = 0x48 < abVar5;
    bVar8 = (bVar7 && bVar2 || bVar3 && bVar4)
            || ((!bVar7 || !bVar2) && (!bVar3 || !bVar4)) && ScreenEdgeOrLeft_PageLoc[0] != 0;
    bVar6 = ScreenRight_X_Pos + 0x48 + bVar8;
    if ((0x7f
         < (byte)((Enemy_PageLoc[param_1] - (ScreenEdgeOrLeft_PageLoc[0] - ((!bVar7 || !bVar2) && (!bVar3 || !bVar4))))
                  - (Enemy_X_Position[param_1] < (byte)((abVar5 + 0xb8) - !bVar7))))
        || ((((((byte)((Enemy_PageLoc[param_1]
                        - (ScreenRight_PageLoc + (0xb7 < ScreenRight_X_Pos || bVar8 && bVar6 == 0)))
                       - (Enemy_X_Position[param_1] < bVar6))
                    < 0x80
                && (Enemy_State[param_1] != 5))
               && ((bVar1 != 0xd && ((bVar1 != 4 && (bVar1 != 0x30))))))
              && (bVar1 != 0x31))
             && (bVar1 != 0x32)))) {
      EraseEnemyObject(param_1);
    }
  }
  return;
}

// SM2MAIN:a319
// Signature: [X] -> [X]
byte FireballEnemyCollision(byte param_1) {
  byte bVar1;
  byte bVar2;
  bool bVar3;
  byte bStack0000;

  if (((Fireball_State[param_1] != 0) && (!(bool)(Fireball_State[param_1] >> 7))) && (!(bool)(FrameCounter & 1))) {
    bStack0000 = param_1 * 4 + 0x1c;
    bVar2 = 4;
    do {
      if ((((((Enemy_State[bVar2] & 0x20) == 0) && (Enemy_Flag[bVar2] != 0))
            && ((bVar1 = Enemy_ID[bVar2], bVar1 < 0x24 || (0x2a < bVar1))))
           && ((bVar1 != 6 || (Enemy_State[bVar2] < 2))))
          && (EnemyOffscrBitsMasked[bVar2] == 0)) {
        bVar3 = SprObjectCollisionCore(bVar2 * 4 + 4, bStack0000);
        if (bVar3) {
          Fireball_State[ObjectOffset] = 0x80;
          HandleEnemyFBallCol(bVar2, bVar2);
        }
      }
      bVar2 -= 1;
    } while (bVar2 < 0x80);
  }
  return ObjectOffset;
}

// SM2MAIN:a37f
// Signature: [X, r01] -> []
void HandleEnemyFBallCol(byte param_1, byte param_2) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  RelativeEnemyPosition(param_1);
  if ((Enemy_Flag[param_2] < 0x80) || (bVar2 = Enemy_Flag[param_2] & 0xf, Enemy_ID[bVar2] != 0x2d)) {
    bVar1 = Enemy_ID[param_2];
    if (bVar1 == 2) {
      return;
    }
    bVar2 = param_2;
    if (bVar1 != 0x2d) {
      if (bVar1 == 8) {
        return;
      }
      if (bVar1 == 0xc) {
        return;
      }
      if (0x14 < bVar1) {
        return;
      }
      ShellOrBlockDefeat(param_2);
      return;
    }
  }
  BowserHitPoints -= 1;
  if (BowserHitPoints != 0) {
    return;
  }
  EnemyFrenzyBuffer = InitVStf(bVar2);
  SpriteVarData1[bVar2] = EnemyFrenzyBuffer;
  SpriteVarData2[bVar2] = 0xfe;
  bVar1 = WorldNumber;
  Enemy_ID[bVar2] = BowserIdentities[WorldNumber];
  bVar3 = 0x20;
  if (bVar1 < 3) {
    bVar3 = 0x23;
  }
  Enemy_State[bVar2] = bVar3;
  Square2SoundQueue = 0x80;
  EnemySmackScore(9, param_2);
  return;
}

// SM2MAIN:a3d6
// Signature: [X] -> []
void ShellOrBlockDefeat(byte param_1) {
  byte bVar1;
  byte bVar2;
  bool bVar3;

  bVar2 = Enemy_ID[param_1];
  bVar3 = 3 < bVar2;
  if ((bVar2 == 4) || (bVar3 = 0xc < bVar2, bVar2 == 0xd)) {
    bVar1 = Enemy_Y_Position[param_1] + 0x18 + bVar3;
    if (bVar2 == 4) {
      bVar1 = (bVar1 - 0x31) - (bVar2 < 4);
    }
    Enemy_Y_Position[param_1] = bVar1;
  }
  ChkToStunEnemies(param_1);
  Enemy_State[param_1] = Enemy_State[param_1] & 0x1f | 0x20;
  bVar2 = 2;
  if (Enemy_ID[param_1] == 5) {
    bVar2 = 6;
  }
  if (Enemy_ID[param_1] != 6) {
    EnemySmackScore(bVar2, param_1);
    return;
  }
  EnemySmackScore(1, param_1);
  return;
}

// SM2MAIN:a408
// Signature: [A, X] -> []
void EnemySmackScore(byte param_1, byte param_2) {
  SetupFloateyNumber(param_1, param_2);
  Square1SoundQueue = 8;
  return;
}

// SM2MAIN:a410
// Signature: [X] -> [X]
byte PlayerHammerCollision(byte param_1) {
  byte bVar1;
  bool bVar2;

  if (((FrameCounter & 1) != 0) && ((byte)(SprObject_OffscrBits[0] | TimerControl | Misc_OffscreenBits) == 0)) {
    bVar2 = PlayerCollisionCore(param_1 * 4 + 0x24);
    param_1 = ObjectOffset;
    if (bVar2) {
      if (Misc_Collision_Flag[ObjectOffset] == 0) {
        Misc_Collision_Flag[ObjectOffset] = 1;
        Misc_X_Speed[param_1] = (Misc_X_Speed[param_1] ^ 0xff) + 1;
        if (StarInvincibleTimer == 0) {
          bVar1 = InjurePlayer();
          return bVar1;
        }
      }
    } else {
      Misc_Collision_Flag[ObjectOffset] = 0;
    }
  }
  return param_1;
}

// SM2MAIN:a44f
// Signature: [X] -> [X]
byte HandlePowerUpCollision(byte param_1) {
  byte bVar1;

  EraseEnemyObject(param_1);
  if (PowerUpType == 4) {
    bVar1 = InjurePlayer();
    return bVar1;
  }
  SetupFloateyNumber(6, param_1);
  Square2SoundQueue = 0x20;
  if (PowerUpType < 2) {
    if (PlayerStatus == 0) {
      PlayerStatus = 1;
      bVar1 = 9;
    } else {
      if (PlayerStatus != 1) {
        Square2SoundQueue = 0x20;
        return param_1;
      }
      PlayerStatus = 2;
      GetPlayerColors();
      bVar1 = 0xc;
    }
    bVar1 = SetPRout(bVar1, 0);
    return bVar1;
  }
  if (PowerUpType == 3) {
    FloateyNum_Control[param_1] = 0xb;
    return param_1;
  }
  StarInvincibleTimer = 0x23;
  AreaMusicQueue = 0x40;
  return param_1;
}

// SM2MAIN:a4ab
// Signature: [X] -> [X]
byte PlayerEnemyCollision(byte param_1) {
  byte bVar1;
  byte bVar2;
  bool bVar3;
  struct_ayi sVar4;
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
      if ((bVar1 != 0x12) && (bVar1 != 0x33)) {
        if (bVar1 == 0xd) {
          bVar1 = InjurePlayer();
          return bVar1;
        }
        if (bVar1 == 4) {
          bVar1 = InjurePlayer();
          return bVar1;
        }
        if (bVar1 == 0xc) {
          bVar1 = InjurePlayer();
          return bVar1;
        }
        if (0x14 < bVar1) {
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
      if (((byte)(PlayerSpriteVarData2[0] - 1) < 0x80)
          || (((6 < Enemy_ID[param_1] && ((byte)(SprObject_Y_Position[0] + 0xc) < Enemy_Y_Position[param_1]))
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

// SM2MAIN:a587
// Signature: [] -> [X]
byte InjurePlayer(void) {
  byte bVar1;

  if ((InjuryTimer | StarInvincibleTimer) == 0) {
    bVar1 = ForceInjury(0);
    return bVar1;
  }
  return ObjectOffset;
}

// SM2MAIN:a58f
// Signature: [A] -> [X]
byte ForceInjury(byte param_1) {
  byte bVar1;

  if (PlayerStatus == 0) {
    EventMusicQueue = 1;
    PlayerSpriteVarData2[0] = 0xfc;
    bVar1 = 0xb;
    PlayerSpriteVarData1[0] = PlayerStatus;
  } else {
    InjuryTimer = 8;
    Square1SoundQueue = 0x10;
    PlayerStatus = param_1;
    GetPlayerColors();
    bVar1 = 10;
  }
  bVar1 = SetPRout(bVar1, 1);
  return bVar1;
}

// SM2MAIN:a5a6
// Signature: [A, Y] -> [X]
byte SetPRout(byte param_1, byte param_2) {
  GameEngineSubroutine = param_1;
  Player_State = param_2;
  TimerControl = 0xff;
  ScrollAmount = 0;
  return ObjectOffset;
}

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

// SM2MAIN:a65f
// Signature: [X] -> [X]
byte ChkEnemyFaceRight(byte param_1) {
  byte bVar1;

  if (Enemy_MovingDir[param_1] != 1) {
    bVar1 = LInj(param_1);
    return bVar1;
  }
  bVar1 = InjurePlayer();
  return bVar1;
}

// SM2MAIN:a668
// Signature: [X] -> [X]
byte LInj(byte param_1) {
  byte bVar1;

  EnemyTurnAround(param_1);
  bVar1 = InjurePlayer();
  return bVar1;
}

// SM2MAIN:a66e
// Signature: [X] -> [Y]
byte EnemyFacePlayer(byte param_1) {
  byte bVar1;
  struct_ncr00 sVar2;

  bVar1 = 1;
  sVar2 = PlayerEnemyDiff(param_1);
  if (sVar2.n != false) {
    bVar1 += 1;
  }
  Enemy_MovingDir[param_1] = bVar1;
  return bVar1 - 1;
}

// SM2MAIN:a67a
// Signature: [A, X] -> []
void SetupFloateyNumber(byte param_1, byte param_2) {
  FloateyNum_Control[param_2] = param_1;
  FloateyNum_Timer[param_2] = 0x30;
  FloateyNum_Y_Pos[param_2] = Enemy_Y_Position[param_2];
  FloateyNum_X_Pos[param_2] = Enemy_Rel_XPos;
  return;
}

// SM2MAIN:a69c
// Signature: [X] -> [X]
byte EnemiesCollision(byte param_1) {
  byte bVar1;
  bool bVar2;
  struct_ayi sVar3;
  byte bStack0000;

  if (((FrameCounter & 1) == 0) || (AreaType == 0)) {
    return param_1;
  }
  bVar1 = Enemy_ID[param_1];
  if ((((bVar1 < 0x15) && (bVar1 != 0x11)) && (bVar1 != 0xd))
      && ((bVar1 != 4 && (EnemyOffscrBitsMasked[param_1] == 0)))) {
    sVar3 = GetEnemyBoundBoxOfs();
    bStack0000 = sVar3.y;
joined_r0xa6c1:
    param_1 -= 1;
    if (param_1 < 0x80) {
      if (((Enemy_Flag[param_1] != 0) && (bVar1 = Enemy_ID[param_1], bVar1 < 0x15))
          && ((bVar1 != 0x11 && (((bVar1 != 0xd && (bVar1 != 4)) && (EnemyOffscrBitsMasked[param_1] == 0)))))) {
        bVar2 = SprObjectCollisionCore(param_1 * 4 + 4, bStack0000);
        bVar1 = ObjectOffset;
        if (bVar2) {
          if (((Enemy_State[ObjectOffset] | Enemy_State[param_1]) & 0x80) == 0) {
            if ((Enemy_CollisionBits[param_1] & SetBitsMask[ObjectOffset]) != 0) {
              goto joined_r0xa6c1;
            }
            Enemy_CollisionBits[param_1] = Enemy_CollisionBits[param_1] | SetBitsMask[ObjectOffset];
          }
          ProcEnemyCollisions(bVar1, param_1, param_1);
          goto joined_r0xa6c1;
        }
        Enemy_CollisionBits[param_1] = Enemy_CollisionBits[param_1] & ClearBitsMask[ObjectOffset];
      }
      goto joined_r0xa6c1;
    }
  }
  return ObjectOffset;
}

// SM2MAIN:a725
// Signature: [X, Y, r01] -> []
void ProcEnemyCollisions(byte param_1, byte param_2, byte param_3) {
  if (((Enemy_State[param_2] | Enemy_State[param_1]) & 0x20) == 0) {
    if (Enemy_State[param_1] < 6) {
      if (Enemy_State[param_2] < 6) {
        EnemyTurnAround(param_2);
        EnemyTurnAround(ObjectOffset);
        return;
      }
      if (Enemy_ID[param_2] != 5) {
        ShellOrBlockDefeat(param_1);
        SetupFloateyNumber(ShellChainCounter[param_3] + 4, ObjectOffset);
        ShellChainCounter[param_3] = ShellChainCounter[param_3] + 1;
        return;
      }
    } else if (Enemy_ID[param_1] != 5) {
      if ((char)Enemy_State[param_2] < 0) {
        SetupFloateyNumber(6, param_1);
        ShellOrBlockDefeat(param_1);
        param_2 = param_3;
      }
      ShellOrBlockDefeat(param_2);
      SetupFloateyNumber(ShellChainCounter[ObjectOffset] + 4, param_3);
      ShellChainCounter[ObjectOffset] = ShellChainCounter[ObjectOffset] + 1;
    }
  }
  return;
}

// SM2MAIN:a78d
// Signature: [X] -> []
void EnemyTurnAround(byte param_1) {
  byte bVar1;

  bVar1 = Enemy_ID[param_1];
  if ((((bVar1 != 0xd) && (bVar1 != 4)) && (bVar1 != 0x11)) && (bVar1 != 5)) {
    if (bVar1 == 0x12) {
      RXSpd(param_1);
      return;
    }
    if (bVar1 == 0xe) {
      RXSpd(param_1);
      return;
    }
    if (bVar1 < 7) {
      RXSpd(param_1);
      return;
    }
  }
  return;
}

// SM2MAIN:a7ab
// Signature: [X] -> []
void RXSpd(byte param_1) {
  SpriteVarData1[param_1] = (SpriteVarData1[param_1] ^ 0xff) + 1;
  Enemy_MovingDir[param_1] = Enemy_MovingDir[param_1] ^ 3;
  return;
}

// SM2MAIN:a7ba
// Signature: [X] -> [X]
byte LargePlatformCollision(byte param_1) {
  byte bVar1;

  HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = 0xff;
  if ((TimerControl == 0) && (Enemy_State[param_1] < 0x80)) {
    if (Enemy_ID[param_1] != 0x24) {
      bVar1 = ChkForPlayerC_LargeP(param_1);
      return bVar1;
    }
    bVar1 = ChkForPlayerC_LargeP(Enemy_State[param_1]);
    bVar1 = ChkForPlayerC_LargeP(bVar1);
    return bVar1;
  }
  return ObjectOffset;
}

// SM2MAIN:a7d4
// Signature: [X] -> [X]
byte ChkForPlayerC_LargeP(byte param_1) {
  byte bVar1;
  byte bVar2;
  bool bVar3;
  struct_ayi sVar4;
  byte bStack0000;

  bVar3 = CheckPlayerVertical();
  if (!bVar3) {
    sVar4 = GetEnemyBoundBoxOfsArg(param_1);
    bVar2 = sVar4.y;
    bVar1 = Enemy_Y_Position[param_1];
    bStack0000 = param_1;
    bVar3 = PlayerCollisionCore(bVar2);
    if (bVar3) {
      ProcLPlatCollisions(bStack0000, bVar2, bVar1);
    }
  }
  return ObjectOffset;
}

// SM2MAIN:a7f0
// Signature: [X] -> [X]
byte SmallPlatformCollision(byte param_1) {
  byte bVar1;
  byte bVar2;
  bool bVar3;
  struct_ayi sVar4;

  if (TimerControl == 0) {
    HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = 0;
    bVar3 = CheckPlayerVertical();
    if (!bVar3) {
      bVar1 = 2;
      do {
        sVar4 = GetEnemyBoundBoxOfs();
        bVar2 = sVar4.y;
        if ((CAST_TO_INT(sVar4) & 2) != 0) {
          return ObjectOffset;
        }
        if ((0x1f < BoundingBox_UL_YPos[bVar2]) && (bVar3 = PlayerCollisionCore(bVar2), bVar3)) {
          bVar1 = ProcLPlatCollisions(ObjectOffset, bVar2, bVar1);
          return bVar1;
        }
        BoundingBox_UL_YPos[bVar2] = BoundingBox_UL_YPos[bVar2] + 0x80;
        BoundingBox_DR_YPos[bVar2] = BoundingBox_DR_YPos[bVar2] + 0x80;
        bVar1 -= 1;
      } while (bVar1 != 0);
    }
  }
  return ObjectOffset;
}

// SM2MAIN:a831
// Signature: [X, Y, r00] -> [X]
byte ProcLPlatCollisions(byte param_1, byte param_2, byte param_3) {
  byte bVar1;

  if (((byte)(BoundingBox_DR_YPos[param_2] - BoundingBox_UL_YPos[0]) < 4) && (0x7f < PlayerSpriteVarData2[0])) {
    PlayerSpriteVarData2[0] = 1;
  }
  if (((byte)(BoundingBox_DR_YPos[0] - BoundingBox_UL_YPos[param_2]) < 6) && (PlayerSpriteVarData2[0] < 0x80)) {
    if ((Enemy_ID[param_1] != 0x2b) && (Enemy_ID[param_1] != 0x2c)) {
      param_3 = param_1;
    }
    bVar1 = ObjectOffset;
    HammerThrowingTimer_Or_PlatformCollisionFlag[ObjectOffset] = param_3;
    Player_State = 0;
    return bVar1;
  }
  bVar1 = 1;
  if (((byte)(BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[0] - BoundingBox_UL_Corner_Or_XPos[param_2]) < 8)
      || (bVar1 = 2,
          (byte)((BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2] - BoundingBox_UL_Corner_Or_XPos[0]) - 1) < 9)) {
    ImpedePlayerMove(bVar1);
  }
  return ObjectOffset;
}

// SM2MAIN:a88e
// Signature: [A, X] -> []
void PositionPlayerOnS_Plat(byte param_1, byte param_2) {
  byte bVar1;

  bVar1 = Enemy_Y_Position[param_2] + PlayerPosSPlatData[param_1 - 1];
  if ((GameEngineSubroutine != 0xb) && (Enemy_Y_HighPos[param_2] == 1)) {
    SprObject_Y_Position[0] = bVar1 - 0x20;
    SprObject_Y_HighPos[0] = 1 - (bVar1 < 0x20);
    PlayerSpriteVarData2[0] = 0;
    SprObject_Y_MoveForce[0] = 0;
  }
  return;
}

// SM2MAIN:a896
// Signature: [X] -> []
void PositionPlayerOnVPlat(byte param_1) {
  if ((GameEngineSubroutine != 0xb) && (Enemy_Y_HighPos[param_1] == 1)) {
    SprObject_Y_Position[0] = Enemy_Y_Position[param_1] - 0x20;
    SprObject_Y_HighPos[0] = 1 - (Enemy_Y_Position[param_1] < 0x20);
    PlayerSpriteVarData2[0] = 0;
    SprObject_Y_MoveForce[0] = 0;
  }
  return;
}

// SM2MAIN:a8b6
// Signature: [] -> [C]
bool CheckPlayerVertical(void) { return (SprObject_OffscrBits[0] & 0xf0) != 0; }

// SM2MAIN:a8c0
// Signature: [] -> [A, Y]
struct_ayi GetEnemyBoundBoxOfs(void) {
  struct_ayi sVar1;

  sVar1 = GetEnemyBoundBoxOfsArg(ObjectOffset);
  return sVar1;
}

// SM2MAIN:a8c2
// Signature: [A] -> [A, Y]
struct_ayi GetEnemyBoundBoxOfsArg(byte param_1) {

  return CAST_INT_TO_struct_ayi(CONCAT12(0, CONCAT11(param_1 * 4 + 4, Enemy_OffscreenBits)) & 0xffff0f);
}

// SM2MAIN:a8d2
// Signature: [] -> []
void PlayerBGCollision(void) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  bool bVar8;
  struct_azr02r04r06r07 sVar9;
  struct_aci sVar10;
  struct_ayr02r04r06r07 sVar11;

  if (((DisableCollisionDet != 0) || (GameEngineSubroutine == 0xb)) || (GameEngineSubroutine < 4)) {
    return;
  }
  bVar6 = 1;
  if ((SwimmingFlag == 0) && ((Player_State == 0 || (bVar6 = Player_State, Player_State == 3)))) {
    bVar6 = 2;
  }
  Player_State = bVar6;
  if (SprObject_Y_HighPos[0] != 1) {
    return;
  }
  Player_CollisionBits = 0xff;
  if (0xce < SprObject_Y_Position[0]) {
    Player_CollisionBits = 0xff;
    return;
  }
  bVar6 = 2;
  if (((CrouchingFlag == 0) && (PlayerSize == 0)) && (bVar6 = 1, SwimmingFlag == 0)) {
    bVar6 = 0;
  }
  MysterySpriteThing1 = BlockBufferAdderData[bVar6];
  bVar6 = PlayerSize;
  if (CrouchingFlag != 0) {
    bVar6 = PlayerSize + 1;
  }
  if (PlayerBGUpperExtent[bVar6] <= SprObject_Y_Position[0]) {
    sVar9 = BlockBufferColli_Head(MysterySpriteThing1);
    bVar4 = sVar9.r07;
    bVar6 = sVar9.r02;
    bVar3 = sVar9.r06;
    bVar1 = sVar9.r04;
    if (!sVar9.z) {
      sVar10 = CheckForCoinMTiles(sVar9.a);
      bVar7 = sVar10.a;
      if (sVar10.c) {
        goto HandleCoinMetatile;
      }
      if ((0x7f < PlayerSpriteVarData2[0]) && (3 < bVar1)) {
        bVar8 = CheckForSolidMTiles(bVar7);
        if (bVar8) {
          if (bVar7 != 0x23) {
            Square1SoundQueue = 2;
          }
        } else if ((AreaType != 0) && (BlockBounceTimer == 0)) {
          PlayerHeadCollision(bVar7, bVar6, bVar3, bVar4);
          goto DoFootCheck;
        }
        PlayerSpriteVarData2[0] = 1;
      }
    }
  }
DoFootCheck:
  if (SprObject_Y_Position[0] < 0xcf) {
    sVar11 = BlockBufferColli_Feet(MysterySpriteThing1);
    bVar4 = sVar11.r07;
    bVar6 = sVar11.r02;
    bVar3 = sVar11.r06;
    bVar7 = sVar11.y;
    sVar10 = CheckForCoinMTiles(sVar11.a);
    bVar1 = sVar10.a;
    if (sVar10.c) {
      goto HandleCoinMetatile;
    }
    sVar11 = BlockBufferColli_Feet(bVar7);
    bVar4 = sVar11.r07;
    bVar6 = sVar11.r02;
    bVar3 = sVar11.r06;
    bVar5 = sVar11.r04;
    bVar2 = sVar11.a;
    bVar7 = bVar1;
    if (bVar1 == 0) {
      if (bVar2 == 0) {
        goto DoPlayerSideCheck;
      }
      sVar10 = CheckForCoinMTiles(bVar2);
      bVar7 = sVar10.a;
      if (sVar10.c != false) {
        goto HandleCoinMetatile;
      }
    }
    bVar8 = CheckForClimbMTiles(bVar7);
    if ((!bVar8) && (PlayerSpriteVarData2[0] < 0x80)) {
      if (bVar7 == 0xc6) {
        OperMode_Task = 0;
        OperMode = 2;
        LoadMarioPhysics();
        PlayerSpriteVarData1[0] = 0x18;
        ErACM(bVar6, bVar3, bVar4);
        return;
      }
      bVar8 = ChkInvisibleMTiles(bVar7);
      if (!bVar8) {
        if (JumpspringAnimCtrl == 0) {
          if (4 < bVar5) {
            ImpedePlayerMove(Player_MovingDir);
            return;
          }
          ChkForLandJumpSpring(bVar7);
          SprObject_Y_Position[0] &= 0xf0;
          HandlePipeEntry(bVar2, bVar1);
          PlayerSpriteVarData2[0] = 0;
          SprObject_Y_MoveForce[0] = 0;
          StompChainCounter = 0;
        }
        Player_State = 0;
      }
    }
  }
DoPlayerSideCheck:
  bVar7 = MysterySpriteThing1 + 2;
  bVar1 = 2;
  while (MysterySpriteThing1 = bVar7 + 1, SprObject_Y_Position[0] < 0x20) {
BHalf:
    bVar7 = MysterySpriteThing1 + 1;
    if (SprObject_Y_Position[0] < 8) {
      return;
    }
    if (0xcf < SprObject_Y_Position[0]) {
      return;
    }
    sVar9 = BlockBufferColli_Side(bVar7);
    bVar4 = sVar9.r07;
    bVar6 = sVar9.r02;
    bVar3 = sVar9.r06;
    bVar2 = sVar9.r04;
    bVar5 = sVar9.a;
    if (sVar9.z == false) {
      goto CheckSideMTiles;
    }
    bVar1 -= 1;
    if (bVar1 == 0) {
      return;
    }
  }
  if (0xe3 < SprObject_Y_Position[0]) {
    return;
  }
  sVar9 = BlockBufferColli_Side(MysterySpriteThing1);
  bVar4 = sVar9.r07;
  bVar6 = sVar9.r02;
  bVar3 = sVar9.r06;
  bVar2 = sVar9.r04;
  bVar5 = sVar9.a;
  if ((((sVar9.z) || (bVar5 == 0x19)) || (bVar5 == 0x6d)) || (bVar8 = CheckForClimbMTiles(bVar5), bVar8)) {
    goto BHalf;
  }
CheckSideMTiles:
  bVar8 = ChkInvisibleMTiles(bVar5);
  if (!bVar8) {
    bVar8 = CheckForClimbMTiles(bVar5);
    if (bVar8) {
      HandleClimbing(bVar5, bVar2, bVar3);
      return;
    }
    sVar10 = CheckForCoinMTiles(bVar5);
    bVar7 = sVar10.a;
    if (sVar10.c) {
HandleCoinMetatile:
      ErACM(bVar6, bVar3, bVar4);
      CoinTallyFor1Ups += 1;
      GiveOneCoin();
      return;
    }
    bVar8 = ChkJumpspringMetatiles(bVar7);
    if (bVar8) {
      if (JumpspringAnimCtrl != 0) {
        return;
      }
    } else if (((Player_State == 0) && (PlayerFacingDir == 1)) && ((bVar7 == 0x6e || (bVar7 == 0x1c)))) {
      if (Player_SprAttrib == 0) {
        Square1SoundQueue = 0x10;
      }
      Player_SprAttrib |= 0x20;
      if ((SprObject_X_Position[0] & 0xf) != 0) {
        ChangeAreaTimer = AreaChangeTimerData[ScreenEdgeOrLeft_PageLoc[0] != 0];
      }
      if (GameEngineSubroutine == 7) {
        return;
      }
      if (GameEngineSubroutine != 8) {
        return;
      }
      GameEngineSubroutine = 2;
      return;
    }
    ImpedePlayerMove(bVar1);
  }
  return;
}

// SM2MAIN:aa8d
// Signature: [r02, r06, r07] -> []
void ErACM(byte param_1, byte param_2, byte param_3) {
  RAM(CONCAT11(param_3, param_2) + (ushort)param_1) = 0;
  RemoveCoin_Axe(param_1, param_2);
  return;
}

// SM2MAIN:aa9f
// Signature: [A, r04, r06] -> []
void HandleClimbing(byte param_1, byte param_2, byte param_3) {
  if ((param_2 < 6) || (9 < param_2)) {
    return;
  }
  if ((param_1 == 0x21) || (param_1 == 0x22)) {
    if (GameEngineSubroutine != 5) {
      PlayerFacingDir = 1;
      ScrollLock += 1;
      if (GameEngineSubroutine != 4) {
        KillEnemies(0x33);
        EventMusicQueue = 0x80;
        FlagpoleSoundQueue = 0x40;
        FlagpoleScore = 4;
        FlagpoleCollisionYPos = SprObject_Y_Position[0];
        do {
          if (FlagpoleYPosData[FlagpoleScore] <= SprObject_Y_Position[0])
            break;
          FlagpoleScore -= 1;
        } while (FlagpoleScore != 0);
        if ((CoinDisplay[0] == CoinDisplay[1]) && (CoinDisplay[0] == GameTimerDisplaySMB2J[2])) {
          FlagpoleScore = 5;
        }
      }
      GameEngineSubroutine = 4;
    }
  } else if ((param_1 == 0x23) && (SprObject_Y_Position[0] < 0x20)) {
    GameEngineSubroutine = 1;
  }
  Player_State = 3;
  PlayerSpriteVarData1[0] = 0;
  Player_X_MoveForce = 0;
  if ((byte)(SprObject_X_Position[0] - ScreenEdgeOrLeft_X_Pos[0]) < 0x10) {
    PlayerFacingDir = 2;
  }
  SprObject_X_Position[0] = param_3 * 0x10 + ClimbXPosAdder[PlayerFacingDir - 1];
  if (param_3 == 0) {
    SprObject_PageLoc[0] = ScreenRight_PageLoc + ClimbXPosAdder[PlayerFacingDir + 1];
  }
  return;
}

// SM2MAIN:ab40
// Signature: [A] -> [Z]
bool ChkInvisibleMTiles(byte param_1) {
  bool bVar1;

  bVar1 = param_1 == 0x5e;
  if (((!bVar1) && (bVar1 = param_1 == 0x5f, !bVar1)) && (bVar1 = param_1 == 0x60, !bVar1)) {
    bVar1 = param_1 == 0x61;
  }
  return bVar1;
}

// SM2MAIN:ab4f
// Signature: [A] -> []
void ChkForLandJumpSpring(byte param_1) {
  bool bVar1;

  bVar1 = ChkJumpspringMetatiles(param_1);
  if (bVar1) {
    VerticalForce = 0x70;
    VerticalForceDown = 0x70;
    JumpspringForce = 0xf9;
    JumpspringTimer = 3;
    JumpspringAnimCtrl = 1;
  }
  return;
}

// SM2MAIN:ab6b
// Signature: [A] -> [C]
bool ChkJumpspringMetatiles(byte param_1) {
  bool bVar1;

  if ((param_1 == 0x68) || (bVar1 = false, param_1 == 0x69)) {
    bVar1 = true;
  }
  return bVar1;
}

// SM2MAIN:ab76
// Signature: [r00, r01] -> []
void HandlePipeEntry(byte param_1, byte param_2) {
  byte bVar1;

  if ((((Up_Down_Buttons & 4) != 0) && (param_1 == 0x11)) && (param_2 == 0x10)) {
    ChangeAreaTimer = 0x30;
    GameEngineSubroutine = 3;
    Square1SoundQueue = 0x10;
    Player_SprAttrib = 0x20;
    if (WarpZoneControl != 0) {
      bVar1 = WarpZoneNumbers[WarpZoneControl & 0xf];
      if (HardWorldFlag != 0) {
        bVar1 -= 9;
      }
      WorldNumber = bVar1 - 1;
      AreaPointer = AreaAddrOffsets[WorldAddrOffsets[WorldNumber]];
      EventMusicQueue = 0x80;
      EntrancePage = 0;
      AreaNumber = 0;
      LevelNumber = 0;
      AltEntranceControl = 0;
      Hidden1UpFlag += 1;
      FetchNewGameTimerFlag += 1;
    }
  }
  return;
}

// SM2MAIN:abd4
// Signature: [r00] -> []
void ImpedePlayerMove(byte param_1) {
  byte bVar1;
  byte bVar2;
  char cVar3;

  if (param_1 == 1) {
    bVar2 = 1;
    if (0x7f < PlayerSpriteVarData1[0]) {
      goto ExIPM;
    }
    bVar1 = 0xff;
  } else {
    bVar2 = 2;
    if ((byte)(PlayerSpriteVarData1[0] - 1) < 0x80) {
      goto ExIPM;
    }
    bVar1 = 1;
  }
  SideCollisionTimer = 0x10;
  cVar3 = 0;
  PlayerSpriteVarData1[0] = 0;
  if (0x7f < bVar1) {
    cVar3 = -1;
  }
  SprObject_PageLoc[0] = SprObject_PageLoc[0] + cVar3 + CARRY1(bVar1, SprObject_X_Position[0]);
  SprObject_X_Position[0] = bVar1 + SprObject_X_Position[0];
ExIPM:
  Player_CollisionBits = (bVar2 ^ 0xff) & Player_CollisionBits;
  return;
}

// SM2MAIN:ac18
// Signature: [A] -> [C]
bool CheckForSolidMTiles(byte param_1) {
  byte bVar1;

  bVar1 = GetMTileAttrib(param_1);
  return SolidMTileUpperExt[bVar1] <= param_1;
}

// SM2MAIN:ac23
// Signature: [A] -> [C]
bool CheckForClimbMTiles(byte param_1) {
  byte bVar1;

  bVar1 = GetMTileAttrib(param_1);
  return ClimbMTileUpperExt[bVar1] <= param_1;
}

// SM2MAIN:ac2a
// Signature: [A] -> [A, C]
struct_aci CheckForCoinMTiles(byte param_1) {

  bool bVar1;
  struct_aci sVar2;
  struct_aci sVar3;

  bVar1 = 0xc2 < param_1;
  if ((param_1 != 0xc3) && (bVar1 = 0xc3 < param_1, param_1 != 0xc4)) {
    sVar2.c = false;
    sVar2.a = param_1;
    sVar2.i = (bool)0;
    return sVar2;
  }
  Square2SoundQueue = 1;
  sVar3.c = bVar1;
  sVar3.a = 1;
  sVar3.i = (bool)0;
  return sVar3;
}

// SM2MAIN:ac39
// Signature: [A] -> [X]
byte GetMTileAttrib(byte param_1) { return (param_1 >> 7) << 1 | (byte)((param_1 & 0xc0) << 1) >> 7; }

// SM2MAIN:ac4a
// Signature: [X] -> [X]
byte EnemyToBGCollisionDet(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  bool bVar4;
  struct_ncr00 sVar5;
  struct_axzr04 sVar6;

  if ((((Enemy_State[param_1] & 0x20) != 0) || (bVar4 = SubtEnemyYPos(param_1), !bVar4))
      || ((bVar2 = Enemy_ID[param_1], bVar2 == 0x12 && (Enemy_Y_Position[param_1] < 0x25)))) {
    return param_1;
  }
  if (bVar2 == 0xe) {
    bVar2 = EnemyJump(param_1);
    return bVar2;
  }
  if (bVar2 == 5) {
    bVar2 = HammerBroBGColl(param_1);
    return bVar2;
  }
  if (((bVar2 != 0x12) && (bVar2 != 0x2e)) && ((bVar2 == 4 || (6 < bVar2)))) {
    return param_1;
  }
  sVar6 = ChkUnderEnemy(param_1);
  bVar2 = sVar6.r04;
  bVar3 = sVar6.x;
  bVar1 = sVar6.a;
  if ((sVar6.z != false) || (bVar4 = ChkForNonSolids(bVar1), bVar4)) {
    bVar2 = ChkForRedKoopa(bVar3);
    return bVar2;
  }
  if (bVar1 == 0x20) {
    if (Enemy_ID[bVar3] < 0x15) {
      if (Enemy_ID[bVar3] == 6) {
        KillEnemyAboveBlock(bVar3);
      }
      SetupFloateyNumber(1, bVar3);
      ChkToStunEnemies(bVar3);
      return bVar3;
    }
    ChkToStunEnemies(bVar3);
    return bVar3;
  }
  if (4 < (byte)(bVar2 - 8)) {
    bVar2 = ChkForRedKoopa(bVar3);
    return bVar2;
  }
  if ((Enemy_State[bVar3] & 0x40) == 0) {
    if (((char)Enemy_State[bVar3] < 0) || (bVar2 = Enemy_State[bVar3], bVar2 == 0)) {
      bVar2 = DoEnemySideCheck(bVar3);
      return bVar2;
    }
    if (bVar2 != 5) {
      if (2 < bVar2) {
        return bVar3;
      }
      if (Enemy_State[bVar3] == 2) {
        bVar2 = 0x10;
        if (Enemy_ID[bVar3] == 0x12) {
          bVar2 = 0;
        }
        EnemyIntervalTimer[bVar3] = bVar2;
        Enemy_State[bVar3] = 3;
        EnemyLanding(bVar3);
        return bVar3;
      }
    }
    if (Enemy_ID[bVar3] != 6) {
      if (Enemy_ID[bVar3] == 0x12) {
        Enemy_MovingDir[bVar3] = 1;
        SpriteVarData1[bVar3] = 8;
        if ((FrameCounter & 7) == 0) {
          goto LandEnemyInitState;
        }
      }
      bVar2 = 1;
      sVar5 = PlayerEnemyDiff(bVar3);
      if (sVar5.n != false) {
        bVar2 += 1;
      }
      if (bVar2 == Enemy_MovingDir[bVar3]) {
        bVar3 = ChkForBump_HammerBroJ(bVar3);
      }
    }
  }
LandEnemyInitState:
  EnemyLanding(bVar3);
  if ((Enemy_State[bVar3] & 0x80) != 0) {
    Enemy_State[bVar3] = Enemy_State[bVar3] & 0xbf;
    return bVar3;
  }
  Enemy_State[bVar3] = 0;
  return bVar3;
}

// SM2MAIN:aca3
// Signature: [X] -> []
void ChkToStunEnemies(byte param_1) {
  byte bVar1;

  bVar1 = Enemy_ID[param_1];
  if (bVar1 < 9) {
    NoDemote(bVar1, param_1);
    return;
  }
  if (0x10 < bVar1) {
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
  if ((9 < bVar1) && (bVar1 < 0xd)) {
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
  byte bVar1;
  struct_ncr00 sVar2;

  if ((param_1 != 0x2e) && (param_1 != 6)) {
    Enemy_State[param_2] = 2;
  }
  Enemy_Y_Position[param_2] = Enemy_Y_Position[param_2] - 1;
  Enemy_Y_Position[param_2] = Enemy_Y_Position[param_2] - 1;
  if ((Enemy_ID[param_2] == 7) || (bVar1 = 0xfd, AreaType == 0)) {
    bVar1 = 0xff;
  }
  SpriteVarData2[param_2] = bVar1;
  bVar1 = 1;
  sVar2 = PlayerEnemyDiff(param_2);
  if (sVar2.n != false) {
    bVar1 += 1;
  }
  if ((Enemy_ID[param_2] != 0x33) && (Enemy_ID[param_2] != 8)) {
    Enemy_MovingDir[param_2] = bVar1;
  }
  SpriteVarData1[param_2] = EnemyBGCXSpdData[(byte)(bVar1 - 1)];
  return;
}

// SM2MAIN:ad78
// Signature: [X] -> [X]
byte ChkForRedKoopa(byte param_1) {
  byte bVar1;

  if ((Enemy_ID[param_1] == 3) && (Enemy_State[param_1] == 0)) {
    bVar1 = ChkForBump_HammerBroJ(param_1);
    return bVar1;
  }
  if ((char)Enemy_State[param_1] < 0) {
    bVar1 = Enemy_State[param_1] | 0x40;
  } else {
    bVar1 = EnemyBGCStateData[Enemy_State[param_1]];
  }
  Enemy_State[param_1] = bVar1;
  bVar1 = DoEnemySideCheck(param_1);
  return bVar1;
}

// SM2MAIN:ad94
// Signature: [X] -> [X]
byte DoEnemySideCheck(byte param_1) {
  byte bVar1;
  bool bVar2;
  struct_axzr04 sVar3;

  if (0x1f < Enemy_Y_Position[param_1]) {
    bVar1 = 0x16;
    MysterySpriteThing1 = 2;
    do {
      if (MysterySpriteThing1 == Enemy_MovingDir[param_1]) {
        sVar3 = BlockBufferChk_Enemy(1, param_1, bVar1);
        param_1 = sVar3.x;
        if (!sVar3.z) {
          bVar2 = ChkForNonSolids(sVar3.a);
          if (!bVar2) {
            bVar1 = ChkForBump_HammerBroJ(param_1);
            return bVar1;
          }
        }
      }
      MysterySpriteThing1 -= 1;
      bVar1 += 1;
    } while (bVar1 < 0x18);
  }
  return param_1;
}

// SM2MAIN:adba
// Signature: [X] -> [X]
byte ChkForBump_HammerBroJ(byte param_1) {
  byte bVar1;

  if ((param_1 != 5) && ((char)Enemy_State[param_1] < 0)) {
    Square1SoundQueue = 2;
  }
  if (Enemy_ID[param_1] == 5) {
    bVar1 = SetHJ(param_1, 0xfa, 0);
    return bVar1;
  }
  RXSpd(param_1);
  return param_1;
}

// SM2MAIN:add9
// Signature: [X] -> [N, C, r00]
struct_ncr00 PlayerEnemyDiff(byte param_1) {
  byte bVar1;
  bool bVar2;
  struct_ncr00 sVar3;

  bVar2 = SprObject_X_Position[0] <= Enemy_X_Position[param_1];
  bVar1 = Enemy_PageLoc[param_1];
  sVar3.n = 0x7f < (byte)((bVar1 - SprObject_PageLoc[0]) - !bVar2);
  sVar3.c = bVar2 && SprObject_PageLoc[0] <= bVar1 || !bVar2 && SprObject_PageLoc[0] < bVar1;
  sVar3.r00 = Enemy_X_Position[param_1] - SprObject_X_Position[0];
  return sVar3;
}

// SM2MAIN:ade5
// Signature: [X] -> []
void EnemyLanding(byte param_1) {
  InitVStf(param_1);
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] & 0xf0 | 8;
  return;
}

// SM2MAIN:adf1
// Signature: [X] -> [C]
bool SubtEnemyYPos(byte param_1) { return 0x43 < (byte)(Enemy_Y_Position[param_1] + 0x3e); }

// SM2MAIN:adf9
// Signature: [X] -> [X]
byte EnemyJump(byte param_1) {
  byte bVar1;
  bool bVar2;
  struct_axzr04 sVar3;

  bVar2 = SubtEnemyYPos(param_1);
  if ((bVar2) && (2 < (byte)(SpriteVarData2[param_1] + 2))) {
    sVar3 = ChkUnderEnemy(param_1);
    param_1 = sVar3.x;
    if (!sVar3.z) {
      bVar2 = ChkForNonSolids(sVar3.a);
      if (!bVar2) {
        EnemyLanding(param_1);
        SpriteVarData2[param_1] = 0xfd;
      }
    }
  }
  bVar1 = DoEnemySideCheck(param_1);
  return bVar1;
}

// SM2MAIN:ae1b
// Signature: [X] -> [X]
byte HammerBroBGColl(byte param_1) {
  byte bVar1;
  struct_axzr04 sVar2;

  sVar2 = ChkUnderEnemy(param_1);
  bVar1 = sVar2.x;
  if (!sVar2.z) {
    if (sVar2.a == 0x20) {
      KillEnemyAboveBlock(bVar1);
      return bVar1;
    }
    if (EnemyFrameTimer[bVar1] == 0) {
      Enemy_State[bVar1] = Enemy_State[bVar1] & 0x88;
      EnemyLanding(bVar1);
      bVar1 = DoEnemySideCheck(bVar1);
      return bVar1;
    }
  }
  Enemy_State[bVar1] = Enemy_State[bVar1] | 1;
  return bVar1;
}

// SM2MAIN:ae24
// Signature: [X] -> []
void KillEnemyAboveBlock(byte param_1) {
  ShellOrBlockDefeat(param_1);
  SpriteVarData2[param_1] = 0xfc;
  return;
}

// SM2MAIN:ae44
// Signature: [X] -> [A, X, Z, r04]
struct_axzr04 ChkUnderEnemy(byte param_1) {
  struct_axzr04 sVar1;

  sVar1 = BlockBufferChk_Enemy(0, param_1, 0x15);
  return sVar1;
}

// SM2MAIN:ae4b
// Signature: [A] -> [Z]
bool ChkForNonSolids(byte param_1) {
  bool bVar1;

  bVar1 = param_1 == 0x23;
  if ((((!bVar1) && (bVar1 = param_1 == 0xc3, !bVar1)) && (bVar1 = param_1 == 0xc4, !bVar1))
      && (((bVar1 = param_1 == 0x5e, !bVar1 && (bVar1 = param_1 == 0x5f, !bVar1))
           && (bVar1 = param_1 == 0x60, !bVar1)))) {
    bVar1 = param_1 == 0x61;
  }
  return bVar1;
}

// SM2MAIN:ae66
// Signature: [X] -> [X]
byte FireballBGCollision(byte param_1) {
  bool bVar1;
  struct_axz sVar2;

  if (0x17 < Fireball_Y_Position[param_1]) {
    sVar2 = BlockBufferChk_FBall(param_1);
    param_1 = sVar2.x;
    if (!sVar2.z) {
      bVar1 = ChkForNonSolids(sVar2.a);
      if (!bVar1) {
        if ((Fireball_Y_Speed[param_1] < 0x80) && (FireballBouncingFlag[param_1] == 0)) {
          Fireball_Y_Speed[param_1] = 0xfd;
          FireballBouncingFlag[param_1] = 1;
          Fireball_Y_Position[param_1] = Fireball_Y_Position[param_1] & 0xf8;
          return param_1;
        }
        Fireball_State[param_1] = 0x80;
        Square1SoundQueue = 2;
        return param_1;
      }
    }
  }
  FireballBouncingFlag[param_1] = 0;
  return param_1;
}

// SM2MAIN:aecb
// Signature: [X] -> [X]
byte GetFireballBoundBox(byte param_1) {
  byte bVar1;
  byte bVar2;

  bVar1 = param_1 + 7;
  bVar2 = BoundingBoxCore(bVar1, 2);
  bVar1 = CheckRightScreenBBox(bVar1, bVar2);
  return bVar1;
}

// SM2MAIN:aed4
// Signature: [X] -> [X]
byte GetMiscBoundBox(byte param_1) {
  byte bVar1;
  byte bVar2;

  bVar1 = param_1 + 9;
  bVar2 = BoundingBoxCore(bVar1, 6);
  bVar1 = CheckRightScreenBBox(bVar1, bVar2);
  return bVar1;
}

// SM2MAIN:aee1
// Signature: [X] -> [X]
byte GetEnemyBoundBox(byte param_1) {
  byte bVar1;

  bVar1 = GetMaskedOffScrBits(param_1, 0x44, 0x48);
  return bVar1;
}

// SM2MAIN:aeea
// Signature: [X] -> [X]
byte SmallPlatformBoundBox(byte param_1) {
  byte bVar1;

  bVar1 = GetMaskedOffScrBits(param_1, 4, 8);
  return bVar1;
}

// SM2MAIN:aef0
// Signature: [X, Y, r00] -> [X]
byte GetMaskedOffScrBits(byte param_1, byte param_2, byte param_3) {
  byte bVar1;

  bVar1 = (Enemy_PageLoc[param_1] - ScreenEdgeOrLeft_PageLoc[0])
          - (Enemy_X_Position[param_1] < ScreenEdgeOrLeft_X_Pos[0]);
  if ((bVar1 < 0x80) && ((byte)(bVar1 | Enemy_X_Position[param_1] - ScreenEdgeOrLeft_X_Pos[0]) != 0)) {
    param_2 = param_3;
  }
  bVar1 = param_2 & Enemy_OffscreenBits;
  EnemyOffscrBitsMasked[param_1] = bVar1;
  if (bVar1 != 0) {
    MoveBoundBoxOffscreen(param_1);
    return param_1;
  }
  bVar1 = SetupEOffsetFBBox(param_1);
  return bVar1;
}

// SM2MAIN:af11
// Signature: [X] -> [X]
byte LargePlatformBoundBox(byte param_1) {
  byte bVar1;
  byte bVar2;

  bVar2 = param_1 + 1;
  bVar1 = GetXOffscreenBits(bVar2);
  bVar2 -= 1;
  if (0xfd < bVar1) {
    MoveBoundBoxOffscreen(bVar2);
    return bVar2;
  }
  bVar1 = SetupEOffsetFBBox(bVar2);
  return bVar1;
}

// SM2MAIN:af1a
// Signature: [X] -> [X]
byte SetupEOffsetFBBox(byte param_1) {
  byte bVar1;
  byte bVar2;

  bVar1 = param_1 + 1;
  bVar2 = BoundingBoxCore(bVar1, 1);
  bVar1 = CheckRightScreenBBox(bVar1, bVar2);
  return bVar1;
}

// SM2MAIN:af27
// Signature: [X] -> []
void MoveBoundBoxOffscreen(byte param_1) {
  byte bVar1;

  bVar1 = param_1 << 2;
  EnemyBoundingBoxCoord[bVar1] = 0xff;
  EnemyBoundingBoxCoord[bVar1 + 1] = 0xff;
  EnemyBoundingBoxCoord[bVar1 + 2] = 0xff;
  EnemyBoundingBoxCoord[bVar1 + 3] = 0xff;
  return;
}

// SM2MAIN:af3a
// Signature: [X, Y] -> [Y]
byte BoundingBoxCore(byte param_1, byte param_2) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;

  bVar1 = SprObject_Rel_YPos[param_2];
  bVar2 = SprObject_Rel_XPos[param_2];
  bVar3 = param_1 * 4;
  bVar4 = PlayerOrSprObj_BoundBoxCtrl[param_1] * 4;
  BoundingBox_UL_Corner_Or_XPos[bVar3] = bVar2 + BoundBoxCtrlData[bVar4];
  BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[bVar3] = bVar2 + BoundBoxCtrlData[bVar4 + 2];
  BoundingBox_UL_Corner_Or_XPos[(byte)(bVar3 + 1)] = bVar1 + BoundBoxCtrlData[(byte)(bVar4 + 1)];
  BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[(byte)(bVar3 + 1)] = bVar1 + BoundBoxCtrlData[(byte)(bVar4 + 1) + 2];
  return bVar3;
}

// SM2MAIN:af7c
// Signature: [X, Y] -> [X]
byte CheckRightScreenBBox(byte param_1, byte param_2) {
  byte bVar1;
  bool bVar2;

  bVar1 = ScreenEdgeOrLeft_PageLoc[0] + (0x7f < ScreenEdgeOrLeft_X_Pos[0]);
  bVar2 = (byte)(ScreenEdgeOrLeft_X_Pos[0] + 0x80) <= SprObject_X_Position[param_1];
  if (bVar2 && bVar1 <= SprObject_PageLoc[param_1] || !bVar2 && bVar1 < SprObject_PageLoc[param_1]) {
    if (BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2] < 0x80) {
      if (BoundingBox_UL_Corner_Or_XPos[param_2] < 0x80) {
        BoundingBox_UL_Corner_Or_XPos[param_2] = 0xff;
      }
      BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2] = 0xff;
    }
    return ObjectOffset;
  }
  if ((0x7f < BoundingBox_UL_Corner_Or_XPos[param_2]) && (0x9f < BoundingBox_UL_Corner_Or_XPos[param_2])) {
    if (0x7f < BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2]) {
      BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2] = 0;
    }
    BoundingBox_UL_Corner_Or_XPos[param_2] = 0;
  }
  return ObjectOffset;
}

// SM2MAIN:afc3
// Signature: [Y] -> [C]
bool PlayerCollisionCore(byte param_1) {
  bool bVar1;

  bVar1 = SprObjectCollisionCore(0, param_1);
  return bVar1;
}

// SM2MAIN:afc5
// Signature: [X, Y] -> [C]
bool SprObjectCollisionCore(byte param_1, byte param_2) {
  byte bVar1;
  byte bVar2;

  bVar2 = 1;
  do {
    bVar1 = BoundingBox_UL_Corner_Or_XPos[param_2];
    if (bVar1 < BoundingBox_UL_Corner_Or_XPos[param_1]) {
      if (bVar1 < BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_1]) {
        if ((BoundingBox_UL_Corner_Or_XPos[param_1] <= BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_1])
            && (BoundingBox_UL_Corner_Or_XPos[param_1] > BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2])) {
          return BoundingBox_UL_Corner_Or_XPos[param_1] <= BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2];
        }
      } else if (((bVar1 != BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_1])
                  && (bVar1 = BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2],
                      BoundingBox_UL_Corner_Or_XPos[param_2] <= bVar1))
                 && (BoundingBox_UL_Corner_Or_XPos[param_1] > bVar1)) {
        return BoundingBox_UL_Corner_Or_XPos[param_1] <= bVar1;
      }
    } else if ((((bVar1 != BoundingBox_UL_Corner_Or_XPos[param_1])
                 && (BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_1] <= bVar1))
                && (bVar1 != BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_1]))
               && (((bVar1 < BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2]
                     || (bVar1 == BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2]))
                    || (BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2]
                        < BoundingBox_UL_Corner_Or_XPos[param_1])))) {
      return false;
    }
    param_1 += 1;
    param_2 += 1;
    bVar2 -= 1;
    if (0x7f < bVar2) {
      return true;
    }
  } while (true);
}

// SM2MAIN:b026
// Signature: [A, X, Y] -> [A, X, Z, r04]
struct_axzr04 BlockBufferChk_Enemy(byte param_1, byte param_2, byte param_3) {
  struct_axzr04 sVar1;
  struct_azr02r04r06r07 sVar2;
  byte bStack0000;

  bStack0000 = param_1;
  sVar2 = BlockBufferCollision(param_1, param_2 + 1, param_3);
  sVar1.r04 = sVar2.r04;
  sVar1.a = sVar2.a;
  sVar1.z = sVar1.a == 0;
  sVar1.x = ObjectOffset;
  return sVar1;
}

// SM2MAIN:b03a
// Signature: [X] -> [A, X, Z]
struct_axz BlockBufferChk_FBall(byte param_1) {
  struct_axz sVar1;
  struct_azr02r04r06r07 sVar2;

  sVar2 = BlockBufferCollision(0, param_1 + 7, 0x1a);
  sVar1.a = sVar2.a;
  sVar1.z = sVar1.a == 0;
  sVar1.x = ObjectOffset;
  return sVar1;
}

// SM2MAIN:b086
// Signature: [Y] -> [A, Y, r02, r04, r06, r07]
struct_ayr02r04r06r07 BlockBufferColli_Feet(byte param_1) {
  undefined3 uVar1;
  byte bVar2;
  struct_azr02r04r06r07 sVar3;
  struct_ayr02r04r06r07 sVar4;
  undefined2 uVar5;

  bVar2 = param_1 + 1;
  sVar3 = BlockBufferCollision(0, 0, bVar2);
  sVar4.r02 = sVar3.r02;
  sVar4.a = sVar3.a;
  sVar4.y = bVar2;
  uVar1 = SUBPIECE(sVar3, 3, 3);
  sVar4.r04 = (char)uVar1;
  sVar4.r06 = (char)((uint3)uVar1 >> 8);
  sVar4.r07 = (char)((uint3)uVar1 >> 0x10);
  return sVar4;
}

// SM2MAIN:b087
// Signature: [Y] -> [A, Z, r02, r04, r06, r07]
struct_azr02r04r06r07 BlockBufferColli_Head(byte param_1) {
  struct_azr02r04r06r07 sVar1;

  sVar1 = BlockBufferCollision(0, 0, param_1);
  return sVar1;
}

// SM2MAIN:b08a
// Signature: [Y] -> [A, Z, r02, r04, r06, r07]
struct_azr02r04r06r07 BlockBufferColli_Side(byte param_1) {
  struct_azr02r04r06r07 sVar1;

  sVar1 = BlockBufferCollision(1, 0, param_1);
  return sVar1;
}

// SM2MAIN:b08e
// Signature: [A, X, Y] -> [A, Z, r02, r04, r06, r07]
struct_azr02r04r06r07 BlockBufferCollision(byte param_1, byte param_2, byte param_3) {
  char cVar1;
  byte bVar2;
  byte bVar3;
  struct_r06r07i sVar4;
  byte bStack0000;

  bStack0000 = param_1;
  sVar4 = GetBlockBufferAddr((byte)((byte)(BlockBuffer_X_Adder[param_3] + SprObject_X_Position[param_2]) >> 1
                                    | (SprObject_PageLoc[param_2]
                                       + CARRY1(BlockBuffer_X_Adder[param_3], SprObject_X_Position[param_2]))
                                          * -0x80)
                             >> 3);
  bVar2 = (SprObject_Y_Position[param_2] + BlockBuffer_Y_Adder[param_3] & 0xf0) - 0x20;
  cVar1 = RAM(SUBPIECE(sVar4, 0, 2) + (ushort)bVar2);
  if (bStack0000 == 0) {
    bVar3 = SprObject_Y_Position[param_2];
  } else {
    bVar3 = SprObject_X_Position[param_2];
  }
  return CAST_INT_TO_struct_azr02r04r06r07(
      CONCAT33(CONCAT12(sVar4.r07, CONCAT11(sVar4.r06, bVar3)), CONCAT12(bVar2, CONCAT11(cVar1 == 0, cVar1)))
      & 0xffff0fffffff);
}

// SM2MAIN:b0d9
// Signature: [Y] -> []
void DrawVine(byte param_1) {
  byte bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;

  bVar4 = Enemy_SprDataOffset[VineObjOffset[param_1]];
  bVar3 = SixSpriteStacker(Enemy_Rel_YPos + VineYPosAdder[param_1], bVar4, bVar4);
  bVar1 = Enemy_Rel_XPos;
  Sprite_Data[bVar3 + 3] = Enemy_Rel_XPos;
  Sprite_Data[bVar3 + 0xb] = bVar1;
  Sprite_Data[bVar3 + 0x13] = bVar1;
  bVar1 += 6;
  Sprite_Data[bVar3 + 7] = bVar1;
  Sprite_Data[bVar3 + 0xf] = bVar1;
  Sprite_Data[bVar3 + 0x17] = bVar1;
  Sprite_Data[bVar3 + 2] = 0x21;
  Sprite_Data[bVar3 + 10] = 0x21;
  Sprite_Data[bVar3 + 0x12] = 0x21;
  Sprite_Data[bVar3 + 6] = 0x61;
  Sprite_Data[bVar3 + 0xe] = 0x61;
  Sprite_Data[bVar3 + 0x16] = 0x61;
  bVar1 = 5;
  do {
    Sprite_Data[bVar3 + 1] = 0xe1;
    bVar3 += 4;
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  if (param_1 == 0) {
    Sprite_Data[bVar4 + 1] = 0xe0;
  }
  cVar2 = 0;
  do {
    if (99 < (byte)(VineStart_Y_Position - Sprite_Data[bVar4])) {
      Sprite_Data[bVar4] = 0xf8;
    }
    bVar4 += 4;
    cVar2 += 1;
  } while (cVar2 != 6);
  return;
}

// SM2MAIN:b152
// Signature: [A, Y, r02] -> [Y]
byte SixSpriteStacker(byte param_1, byte param_2, byte param_3) {
  char cVar1;

  cVar1 = 6;
  do {
    Sprite_Data[param_2] = param_1;
    param_1 += 8;
    param_2 += 4;
    cVar1 += -1;
  } while (cVar1 != 0);
  return param_3;
}

// SM2MAIN:b180
// Signature: [X] -> [X]
byte DrawHammer(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  bVar1 = Misc_SprDataOffset[param_1];
  if ((TimerControl == 0) && ((Misc_State[param_1] & 0x7f) == 1)) {
    bVar3 = FrameCounter >> 2 & 3;
  } else {
    bVar3 = 0;
  }
  bVar2 = Misc_Rel_YPos + FirstSprYPos[bVar3];
  Sprite_Data[bVar1] = bVar2;
  Sprite_Data[bVar1 + 4] = bVar2 + SecondSprYPos[bVar3];
  bVar2 = Misc_Rel_XPos + FirstSprXPos[bVar3];
  Sprite_Data[bVar1 + 3] = bVar2;
  Sprite_Data[bVar1 + 7] = bVar2 + SecondSprXPos[bVar3];
  Sprite_Data[bVar1 + 1] = FirstSprTilenum[bVar3];
  Sprite_Data[bVar1 + 5] = SecondSprTilenum[bVar3];
  bVar3 = HammerSprAttrib[bVar3];
  Sprite_Data[bVar1 + 2] = bVar3;
  Sprite_Data[bVar1 + 6] = bVar3;
  bVar3 = ObjectOffset;
  if ((Misc_OffscreenBits & 0xfc) != 0) {
    Misc_State[ObjectOffset] = 0;
    DumpTwoSpr(0xf8, bVar1);
  }
  return bVar3;
}

// SM2MAIN:b1f1
// Signature: [X] -> []
void FlagpoleGfxHandler(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;

  bVar2 = Enemy_Rel_XPos;
  bVar4 = Enemy_SprDataOffset[param_1];
  Sprite_Data[bVar4 + 3] = Enemy_Rel_XPos;
  bVar3 = bVar2 + 8;
  Sprite_Data[bVar4 + 7] = bVar3;
  Sprite_Data[bVar4 + 0xb] = bVar3;
  bVar2 += 0x14;
  cVar5 = 0xf3 < bVar3;
  bVar3 = Enemy_Y_Position[param_1];
  DumpTwoSpr(bVar3, bVar4);
  Sprite_Data[bVar4 + 8] = bVar3 + 8 + cVar5;
  bVar3 = FlagpoleFNum_Y_Pos;
  Sprite_Data[bVar4 + 2] = 1;
  Sprite_Data[bVar4 + 6] = 1;
  Sprite_Data[bVar4 + 10] = 1;
  Sprite_Data[bVar4 + 1] = 0x7e;
  Sprite_Data[bVar4 + 9] = 0x7e;
  Sprite_Data[bVar4 + 5] = 0x7f;
  if (FlagpoleCollisionYPos != 0) {
    bVar1 = FlagpoleScore << 1;
    DrawOneSpriteRow(FlagpoleScoreNumTiles[bVar1 + 1], bVar1, bVar4 + 0xc, FlagpoleScoreNumTiles[bVar1], bVar3, 1, 1,
                     bVar2);
  }
  if ((Enemy_OffscreenBits & 0xe) != 0) {
    MoveSixSpritesOffscreen(Enemy_SprDataOffset[ObjectOffset]);
    return;
  }
  return;
}

// SM2MAIN:b259
// Signature: [Y] -> []
void MoveSixSpritesOffscreen(byte param_1) {
  DumpSixSpr(0xf8, param_1);
  return;
}

// SM2MAIN:b25b
// Signature: [A, Y] -> []
void DumpSixSpr(byte param_1, byte param_2) {
  Sprite_Data[param_2 + 0x14] = param_1;
  Sprite_Data[param_2 + 0x10] = param_1;
  Sprite_Data[param_2 + 0xc] = param_1;
  Sprite_Data[param_2 + 8] = param_1;
  Sprite_Data[param_2 + 4] = param_1;
  Sprite_Data[param_2] = param_1;
  return;
}

// SM2MAIN:b261
// Signature: [A, Y] -> []
void DumpFourSpr(byte param_1, byte param_2) {
  Sprite_Data[param_2 + 0xc] = param_1;
  Sprite_Data[param_2 + 8] = param_1;
  Sprite_Data[param_2 + 4] = param_1;
  Sprite_Data[param_2] = param_1;
  return;
}

// SM2MAIN:b264
// Signature: [A, Y] -> []
void DumpThreeSpr(byte param_1, byte param_2) {
  Sprite_Data[param_2 + 8] = param_1;
  Sprite_Data[param_2 + 4] = param_1;
  Sprite_Data[param_2] = param_1;
  return;
}

// SM2MAIN:b267
// Signature: [A, Y] -> []
void DumpTwoSpr(byte param_1, byte param_2) {
  Sprite_Data[param_2 + 4] = param_1;
  Sprite_Data[param_2] = param_1;
  return;
}

// SM2MAIN:b26e
// Signature: [X] -> [X]
byte DrawLargePlatform(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  char cStack0000;

  bVar2 = SixSpriteStacker(Enemy_Rel_XPos, Enemy_SprDataOffset[param_1] + 3, Enemy_SprDataOffset[param_1]);
  bVar1 = Enemy_Y_Position[ObjectOffset];
  bVar3 = ObjectOffset;
  DumpFourSpr(bVar1, bVar2);
  if ((AreaType == 3) || (SecondaryHardMode != 0)) {
    bVar1 = 0xf8;
  }
  bVar3 = Enemy_SprDataOffset[bVar3];
  Sprite_Data[bVar3 + 0x10] = bVar1;
  Sprite_Data[bVar3 + 0x14] = bVar1;
  bVar1 = 0x5b;
  if (CloudTypeOverride != 0) {
    bVar1 = 0x75;
  }
  bVar3 += 1;
  bVar2 = ObjectOffset;
  DumpSixSpr(bVar1, bVar3);
  DumpSixSpr(2, bVar3 + 1);
  bVar2 += 1;
  bVar3 = GetXOffscreenBits(bVar2);
  bVar2 -= 1;
  bVar1 = Enemy_SprDataOffset[bVar2];
  if ((char)bVar3 < 0) {
    Sprite_Data[bVar1] = 0xf8;
  }
  if ((char)(bVar3 << 1) < 0) {
    Sprite_Data[bVar1 + 4] = 0xf8;
  }
  if ((char)(bVar3 << 2) < 0) {
    Sprite_Data[bVar1 + 8] = 0xf8;
  }
  if ((char)(bVar3 << 3) < 0) {
    Sprite_Data[bVar1 + 0xc] = 0xf8;
  }
  cStack0000 = bVar3 << 5;
  if ((char)(bVar3 << 4) < 0) {
    Sprite_Data[bVar1 + 0x10] = 0xf8;
  }
  if (cStack0000 < 0) {
    Sprite_Data[bVar1 + 0x14] = 0xf8;
  }
  if ((char)Enemy_OffscreenBits < 0) {
    MoveSixSpritesOffscreen(bVar1);
  }
  return bVar2;
}

// SM2MAIN:b32c
// Signature: [X] -> [X]
byte JCoinGfxHandler(byte param_1) {
  byte bVar1;
  byte bVar2;

  bVar2 = Misc_SprDataOffset[param_1];
  if (Misc_State[param_1] < 2) {
    bVar1 = Misc_Y_Position[param_1];
    Sprite_Data[bVar2] = bVar1;
    Sprite_Data[bVar2 + 4] = bVar1 + 8;
    bVar1 = Misc_Rel_XPos;
    Sprite_Data[bVar2 + 3] = Misc_Rel_XPos;
    Sprite_Data[bVar2 + 7] = bVar1;
    bVar2 += 1;
    DumpTwoSpr(JumpingCoinTiles[FrameCounter >> 1 & 3], bVar2);
    Sprite_Data[(byte)(bVar2 - 1) + 2] = 2;
    Sprite_Data[(byte)(bVar2 - 1) + 6] = 0x82;
    param_1 = ObjectOffset;
  } else {
    if (!(bool)(FrameCounter & 1)) {
      Misc_Y_Position[param_1] = Misc_Y_Position[param_1] - 1;
    }
    DumpTwoSpr(Misc_Y_Position[param_1], bVar2);
    bVar1 = Misc_Rel_XPos;
    Sprite_Data[bVar2 + 3] = Misc_Rel_XPos;
    Sprite_Data[bVar2 + 7] = bVar1 + 8;
    Sprite_Data[bVar2 + 2] = 2;
    Sprite_Data[bVar2 + 6] = 2;
    Sprite_Data[bVar2 + 1] = 0xf7;
    Sprite_Data[bVar2 + 5] = 0xfb;
  }
  return param_1;
}

// SM2MAIN:b37d
// Signature: [] -> [X]
byte DrawPowerUp(void) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  struct_xyr02 sVar9;
  byte bStack0000;

  bVar6 = Enemy_Rel_YPos + 8;
  bVar5 = PowerUpAttributes[PowerUpType] | Enemy_SprAttrib[5];
  bStack0000 = PowerUpType;
  bVar7 = PowerUpType << 2;
  bVar4 = 1;
  bVar2 = 1;
  bVar3 = Enemy_Rel_XPos;
  bVar8 = Enemy_SprDataOffset[5];
  do {
    sVar9 = DrawOneSpriteRow(PowerUpGfxTable[bVar7 + 1], bVar7, bVar8, PowerUpGfxTable[bVar7], bVar6, bVar2, bVar5,
                             bVar3);
    bVar1 = Enemy_SprDataOffset[5];
    bVar6 = sVar9.r02;
    bVar8 = sVar9.y;
    bVar7 = sVar9.x;
    bVar4 -= 1;
  } while (bVar4 < 0x80);
  if (((bStack0000 != 0) && (bStack0000 != 3)) && (bStack0000 != 4)) {
    bVar6 = FrameCounter >> 1 & 3 | Enemy_SprAttrib[5];
    Sprite_Data[Enemy_SprDataOffset[5] + 2] = bVar6;
    Sprite_Data[bVar1 + 6] = bVar6;
    if (bStack0000 != 1) {
      Sprite_Data[bVar1 + 10] = bVar6;
      Sprite_Data[bVar1 + 0xe] = bVar6;
    }
    Sprite_Data[bVar1 + 6] = Sprite_Data[bVar1 + 6] | 0x40;
    Sprite_Data[bVar1 + 0xe] = Sprite_Data[bVar1 + 0xe] | 0x40;
  }
  bVar6 = SprObjectOffscrChk();
  return bVar6;
}

// SM2MAIN:b52c
// Signature: [X] -> [X]
byte EnemyGfxHandler(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;

  EnemyAttributeData[24] = 2;
  if (((WorldNumber == 1) || (WorldNumber == 2)) || (WorldNumber == 6)) {
    EnemyAttributeData[24] = 1;
  }
  EnemyAttributeData[25] = EnemyAttributeData[24];
  EnemyAttributeData[26] = EnemyAttributeData[24];
  bVar5 = Enemy_Y_Position[param_1];
  MysterySpriteThing1 = Enemy_SprDataOffset[param_1];
  VerticalFlipFlag = 0;
  bVar2 = Enemy_MovingDir[param_1];
  bVar3 = Enemy_SprAttrib[param_1];
  if (((Enemy_ID[param_1] == 0xd) && (SpriteVarData1[param_1] < 0x80)) && (EnemyFrameTimer[param_1] != 0)) {
    return param_1;
  }
  MysterySpriteThing3 = Enemy_State[param_1];
  MysterySpriteThing2 = MysterySpriteThing3 & 0x1f;
  MysterySpriteThing4 = Enemy_ID[param_1];
  if (MysterySpriteThing4 == 0x35) {
    MysterySpriteThing2 = 0;
    bVar2 = 1;
    MysterySpriteThing4 = 0x15;
  }
  if (MysterySpriteThing4 == 0x33) {
    bVar5 -= 1;
    bVar3 = 3;
    if (EnemyFrameTimer[param_1] != 0) {
      bVar3 = 0x23;
    }
    MysterySpriteThing2 = 0;
    MysterySpriteThing3 = 0;
    MysterySpriteThing4 = 8;
  }
  if (MysterySpriteThing4 == 0x32) {
    MysterySpriteThing2 = 3;
    MysterySpriteThing4 = JumpspringFrameOffsets[JumpspringAnimCtrl];
  }
  if ((MysterySpriteThing4 == 0xc) && (SpriteVarData2[ObjectOffset] < 0x80)) {
    VerticalFlipFlag = 1;
  }
  if ((BowserGfxFlag != 0) && (MysterySpriteThing4 = 0x16, BowserGfxFlag != 1)) {
    MysterySpriteThing4 = 0x17;
  }
  if (MysterySpriteThing4 == 6) {
    if (1 < Enemy_State[ObjectOffset]) {
      MysterySpriteThing2 = 4;
    }
    if (((Enemy_State[ObjectOffset] & 0x20 | TimerControl) == 0) && ((FrameCounter & 8) == 0)) {
      bVar2 ^= 3;
    }
  }
  bVar3 = EnemyAttributeData[MysterySpriteThing4] | bVar3;
  bVar4 = EnemyGfxTableOffsets[MysterySpriteThing4];
  if (BowserGfxFlag != 0) {
    if (BowserGfxFlag == 1) {
      if (0x7f < BowserBodyControls) {
        bVar4 = 0xde;
      }
      if ((MysterySpriteThing3 & 0x20) == 0) {
        goto DrawBowser;
      }
    } else {
      if ((BowserBodyControls & 1) != 0) {
        bVar4 = 0xe4;
      }
      if ((MysterySpriteThing3 & 0x20) == 0) {
        goto DrawBowser;
      }
      bVar5 -= 0x10;
    }
    VerticalFlipFlag = bVar4;
DrawBowser:
    bVar5 = DrawEnemyObject(bVar4, bVar5, bVar2, bVar3, Enemy_Rel_XPos);
    return bVar5;
  }
  if (bVar4 == 0x24) {
    if (MysterySpriteThing2 == 5) {
      bVar4 = 0x30;
      bVar2 = 2;
      MysterySpriteThing2 = 5;
    }
  } else {
    if (bVar4 == 0x90) {
      if (((MysterySpriteThing3 & 0x20) == 0) && (FrenzyEnemyTimer < 0x10)) {
        bVar4 = 0x96;
      }
      goto CheckDefeatedState;
    }
    if (((MysterySpriteThing4 < 4) && (1 < MysterySpriteThing2)) && (bVar4 = 0x5a, MysterySpriteThing4 == 2)) {
      bVar4 = 0x7e;
      bVar5 += 1;
    }
    if (MysterySpriteThing2 == 4) {
      bVar4 = 0x72;
      bVar1 = bVar5 + 1;
      if (MysterySpriteThing4 != 2) {
        bVar4 = 0x66;
        bVar1 = bVar5 + 2;
      }
      bVar5 = bVar1;
      if ((MysterySpriteThing4 == 6) && (bVar4 = 0x54, (MysterySpriteThing3 & 0x20) == 0)) {
        bVar4 = 0x8a;
        bVar5 -= 1;
      }
    }
  }
  if (MysterySpriteThing4 == 5) {
    if (MysterySpriteThing3 != 0) {
      if ((MysterySpriteThing3 & 8) == 0) {
        goto CheckDefeatedState;
      }
      bVar4 = 0xb4;
    }
CheckToAnimateEnemy:
    if (((MysterySpriteThing4 == 6) || (MysterySpriteThing4 == 8))
        || ((MysterySpriteThing4 == 0xc || (0x17 < MysterySpriteThing4)))) {
      goto CheckDefeatedState;
    }
    if (MysterySpriteThing4 == 0x15) {
      MysterySpriteThing2 = 3;
      if (WorldNumber < 7) {
        bVar4 = 0xa2;
      }
      goto CheckDefeatedState;
    }
    if ((FrameCounter & EnemyAnimTimingBMask[0]) != 0) {
      goto CheckDefeatedState;
    }
  } else {
    if (bVar4 == 0x48) {
      goto CheckToAnimateEnemy;
    }
    if (4 < EnemyIntervalTimer[ObjectOffset]) {
      goto CheckDefeatedState;
    }
    if (bVar4 != 0x3c) {
      goto CheckToAnimateEnemy;
    }
    if (EnemyIntervalTimer[ObjectOffset] == 1) {
      goto CheckDefeatedState;
    }
    bVar5 += 3;
  }
  if ((MysterySpriteThing3 & 0xa0 | TimerControl) == 0) {
    bVar4 += 6;
  }
CheckDefeatedState:
  if (MysterySpriteThing4 != 4) {
    if ((MysterySpriteThing3 & 0x20) == 0) {
      bVar5 = DrawEnemyObject(bVar4, bVar5, bVar2, bVar3, Enemy_Rel_XPos);
      return bVar5;
    }
    if (MysterySpriteThing4 < 4) {
      bVar5 = DrawEnemyObject(bVar4, bVar5, bVar2, bVar3, Enemy_Rel_XPos);
      return bVar5;
    }
  }
  VerticalFlipFlag = 1;
  MysterySpriteThing2 = 0;
  bVar5 = DrawEnemyObject(bVar4, bVar5, bVar2, bVar3, Enemy_Rel_XPos);
  return bVar5;
}

// SM2MAIN:b71b
// Signature: [X, r02, r03, r04, r05] -> [X]
byte DrawEnemyObject(byte param_1, byte param_2, byte param_3, byte param_4, byte param_5) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  struct_xyr02 sVar6;

  sVar6 = DrawEnemyObjRow(param_1, MysterySpriteThing1, param_2, param_3, param_4, param_5);
  sVar6 = DrawEnemyObjRow(sVar6.x, sVar6.y, sVar6.r02, param_3, param_4, param_5);
  DrawEnemyObjRow(sVar6.x, sVar6.y, sVar6.r02, param_3, param_4, param_5);
  bVar3 = Enemy_SprDataOffset[ObjectOffset];
  if (MysterySpriteThing4 == 8) {
SkipToOffScrChk:
    bVar3 = SprObjectOffscrChk();
    return bVar3;
  }
  if (VerticalFlipFlag != 0) {
    bVar4 = bVar3 + 2;
    DumpSixSpr(Sprite_Data[bVar3 + 2] | 0x80, bVar4);
    bVar3 = bVar4 - 2;
    bVar2 = bVar3;
    if ((((MysterySpriteThing4 != 5) && (MysterySpriteThing4 != 4)) && (MysterySpriteThing4 != 0x11))
        && (MysterySpriteThing4 < 0x15)) {
      bVar2 = bVar4 + 6;
    }
    bVar4 = Sprite_Data[bVar2 + 1];
    bVar1 = Sprite_Data[bVar2 + 5];
    Sprite_Data[bVar2 + 1] = Sprite_Data[bVar3 + 0x11];
    Sprite_Data[bVar2 + 5] = Sprite_Data[bVar3 + 0x15];
    Sprite_Data[bVar3 + 0x15] = bVar1;
    Sprite_Data[bVar3 + 0x11] = bVar4;
  }
  bVar2 = MysterySpriteThing2;
  if (BowserGfxFlag != 0) {
    goto SkipToOffScrChk;
  }
  if (MysterySpriteThing4 == 5) {
    bVar3 = SprObjectOffscrChk();
    return bVar3;
  }
  if (((MysterySpriteThing4 != 7) && (MysterySpriteThing4 != 0xd))
      && ((MysterySpriteThing4 != 4 && (MysterySpriteThing4 != 0xc)))) {
    if ((MysterySpriteThing4 == 0x12) && (MysterySpriteThing2 != 5)) {
      goto CheckToMirrorLakitu;
    }
    if (MysterySpriteThing4 == 0x15) {
      Sprite_Data[bVar3 + 0x16] = 0x42;
    }
    if (bVar2 < 2) {
      goto CheckToMirrorLakitu;
    }
  }
  if (BowserGfxFlag == 0) {
    bVar4 = Sprite_Data[bVar3 + 2] & 0xa3;
    Sprite_Data[bVar3 + 2] = bVar4;
    Sprite_Data[bVar3 + 10] = bVar4;
    Sprite_Data[bVar3 + 0x12] = bVar4;
    bVar1 = bVar4 | 0x40;
    if (bVar2 == 5) {
      bVar1 = bVar4 | 0xc0;
    }
    Sprite_Data[bVar3 + 6] = bVar1;
    Sprite_Data[bVar3 + 0xe] = bVar1;
    Sprite_Data[bVar3 + 0x16] = bVar1;
    if (bVar2 == 4) {
      bVar2 = Sprite_Data[bVar3 + 10];
      bVar4 = bVar2 | 0x80;
      Sprite_Data[bVar3 + 10] = bVar4;
      Sprite_Data[bVar3 + 0x12] = bVar4;
      bVar2 |= 0xc0;
      Sprite_Data[bVar3 + 0xe] = bVar2;
      Sprite_Data[bVar3 + 0x16] = bVar2;
    }
  }
CheckToMirrorLakitu:
  if (MysterySpriteThing4 == 0x11) {
    if (VerticalFlipFlag == 0) {
      Sprite_Data[bVar3 + 0x12] = Sprite_Data[bVar3 + 0x12] & 0x81;
      bVar2 = Sprite_Data[bVar3 + 0x16] | 0x41;
      Sprite_Data[bVar3 + 0x16] = bVar2;
      bVar5 = 0xf < FrenzyEnemyTimer;
      if (bVar5) {
        bVar3 = SprObjectOffscrChk();
        return bVar3;
      }
      Sprite_Data[bVar3 + 0xe] = bVar2;
      Sprite_Data[bVar3 + 10] = bVar2 & 0x81;
      if (!bVar5) {
        bVar3 = SprObjectOffscrChk();
        return bVar3;
      }
    }
    Sprite_Data[bVar3 + 2] = Sprite_Data[bVar3 + 2] & 0x81;
    Sprite_Data[bVar3 + 6] = Sprite_Data[bVar3 + 6] | 0x41;
  }
  bVar2 = EnemyAttributeData[24];
  if (MysterySpriteThing4 < 0x18) {
    bVar3 = SprObjectOffscrChk();
    return bVar3;
  }
  bVar4 = EnemyAttributeData[24] | 0x80;
  Sprite_Data[bVar3 + 10] = bVar4;
  Sprite_Data[bVar3 + 0x12] = bVar4;
  Sprite_Data[bVar3 + 0xe] = bVar2 | 0xc0;
  Sprite_Data[bVar3 + 0x16] = bVar2 | 0xc0;
  bVar3 = SprObjectOffscrChk();
  return bVar3;
}

// SM2MAIN:b83f
// Signature: [] -> [X]
byte SprObjectOffscrChk(void) {
  byte bVar1;
  byte bVar2;
  byte bStack0000;

  bStack0000 = Enemy_OffscreenBits >> 3;
  bVar1 = ObjectOffset;
  if ((Enemy_OffscreenBits >> 2 & 1) != 0) {
    MoveESprColOffscreen(4, ObjectOffset);
  }
  bVar2 = bStack0000 & 1;
  bStack0000 >>= 1;
  if (bVar2 != 0) {
    MoveESprColOffscreen(0, bVar1);
  }
  bVar2 = bStack0000 >> 1;
  bStack0000 >>= 2;
  if ((bVar2 & 1) != 0) {
    MoveESprRowOffscreen(0x10, bVar1);
  }
  bVar2 = bStack0000 & 1;
  bStack0000 >>= 1;
  if (bVar2 != 0) {
    MoveESprRowOffscreen(8, bVar1);
  }
  if ((bStack0000 & 1) != 0) {
    MoveESprRowOffscreen(bStack0000 >> 1, bVar1);
    if ((Enemy_ID[bVar1] != 0xc) && (Enemy_Y_HighPos[bVar1] == 2)) {
      EraseEnemyObject(bVar1);
    }
  }
  return bVar1;
}

// SM2MAIN:b885
// Signature: [X, Y, r02, r03, r04, r05] -> [X, Y, r02]
struct_xyr02 DrawEnemyObjRow(byte param_1, byte param_2, byte param_3, byte param_4, byte param_5, byte param_6) {
  struct_xyr02 sVar1;

  sVar1 = DrawOneSpriteRow(EnemyGraphicsTable[param_1 + 1], param_1, param_2, EnemyGraphicsTable[param_1], param_3,
                           param_4, param_5, param_6);
  return sVar1;
}

// SM2MAIN:b88d
// Signature: [A, X, Y, r00, r02, r03, r04, r05] -> [X, Y, r02]
struct_xyr02 DrawOneSpriteRow(byte param_1, byte param_2, byte param_3, byte param_4, byte param_5, byte param_6,
                              byte param_7, byte param_8) {
  struct_xyr02 sVar1;

  sVar1 = DrawSpriteObject(param_2, param_3, param_4, param_1, param_5, param_6, param_7, param_8);
  return sVar1;
}

// SM2MAIN:b892
// Signature: [A, X] -> []
void MoveESprRowOffscreen(byte param_1, byte param_2) {
  DumpTwoSpr(0xf8, param_1 + Enemy_SprDataOffset[param_2]);
  return;
}

// SM2MAIN:b89c
// Signature: [A, X] -> []
void MoveESprColOffscreen(byte param_1, byte param_2) {
  byte bVar1;
  byte bVar2;

  bVar2 = param_1 + Enemy_SprDataOffset[param_2];
  bVar1 = MoveColOffscreen(bVar2);
  Sprite_Data[bVar2 + 0x10] = bVar1;
  return;
}

// SM2MAIN:b8ac
// Signature: [X] -> [X]
byte DrawBlock(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  struct_xyr02 sVar8;
  byte bStack0000;

  bVar2 = 3;
  bVar4 = 1;
  bVar7 = AltOrBlock_SprDataOffset[param_1];
  bVar6 = 0;
  bVar1 = Block_Rel_YPos;
  bVar3 = Block_Rel_XPos;
  do {
    sVar8 = DrawOneSpriteRow(DefaultBlockObjTiles[bVar6 + 1], bVar6, bVar7, DefaultBlockObjTiles[bVar6], bVar1, bVar4,
                             bVar2, bVar3);
    bVar5 = ObjectOffset;
    bVar1 = sVar8.r02;
    bVar7 = sVar8.y;
    bVar6 = sVar8.x;
  } while (bVar6 != 4);
  bVar7 = AltOrBlock_SprDataOffset[ObjectOffset];
  if (AreaType != 1) {
    Sprite_Data[bVar7 + 1] = 0x86;
    Sprite_Data[bVar7 + 5] = 0x86;
  }
  if (Block_Metatile[bVar5] == 0xc5) {
    bVar7 += 1;
    DumpFourSpr(0x87, bVar7);
    bVar5 = ObjectOffset;
    bVar7 -= 1;
    bVar4 = 3;
    if (AreaType != 1) {
      bVar4 = 1;
    }
    Sprite_Data[bVar7 + 2] = bVar4;
    Sprite_Data[bVar7 + 6] = bVar4 | 0x40;
    Sprite_Data[bVar7 + 0xe] = bVar4 | 0xc0;
    Sprite_Data[bVar7 + 10] = bVar4 | 0x80;
  }
  bVar4 = Block_OffscreenBits;
  bStack0000 = Block_OffscreenBits;
  if ((Block_OffscreenBits & 4) != 0) {
    Sprite_Data[bVar7 + 4] = 0xf8;
    Sprite_Data[bVar7 + 0xc] = 0xf8;
  }
  ChkLeftCo(bVar4, bVar7);
  return bVar5;
}

// SM2MAIN:b921
// Signature: [A, Y] -> []
void ChkLeftCo(byte param_1, byte param_2) {
  if ((param_1 & 8) != 0) {
    MoveColOffscreen(param_2);
    return;
  }
  return;
}

// SM2MAIN:b925
// Signature: [Y] -> [A]
byte MoveColOffscreen(byte param_1) {
  Sprite_Data[param_1] = 0xf8;
  Sprite_Data[param_1 + 8] = 0xf8;
  return 0xf8;
}

// SM2MAIN:b92e
// Signature: [X] -> []
void DrawBrickChunks(byte param_1) {
  byte bVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;

  bVar1 = 2;
  bVar2 = 0x75;
  if (GameEngineSubroutine != 5) {
    bVar1 = 3;
    bVar2 = 0x84;
  }
  bVar4 = AltOrBlock_SprDataOffset[param_1] + 1;
  DumpFourSpr(bVar2, bVar4);
  bVar4 += 1;
  DumpFourSpr((FrameCounter & 0xc) << 4 | bVar1, bVar4);
  bVar4 -= 2;
  DumpTwoSpr(Block_Rel_YPos, bVar4);
  Sprite_Data[bVar4 + 3] = Block_Rel_XPos;
  bVar1 = Block_Orig_XPos[param_1] - ScreenEdgeOrLeft_X_Pos[0];
  cVar3 = (bVar1 - Block_Rel_XPos) + bVar1 + (Block_Rel_XPos <= bVar1);
  Sprite_Data[bVar4 + 7] = cVar3 + 6 + (CARRY1(bVar1 - Block_Rel_XPos, bVar1) || Block_Rel_XPos <= bVar1 && cVar3 == 0);
  bVar2 = Block_Rel_YPos_2;
  Sprite_Data[bVar4 + 8] = Block_Rel_YPos_2;
  Sprite_Data[bVar4 + 0xc] = bVar2;
  Sprite_Data[bVar4 + 0xb] = Block_Rel_XPos_2;
  cVar3 = (bVar1 - Block_Rel_XPos_2) + bVar1 + (Block_Rel_XPos_2 <= bVar1);
  Sprite_Data[bVar4 + 0xf]
      = cVar3 + 6 + (CARRY1(bVar1 - Block_Rel_XPos_2, bVar1) || Block_Rel_XPos_2 <= bVar1 && cVar3 == 0);
  ChkLeftCo(Block_OffscreenBits, bVar4);
  if ((char)Block_OffscreenBits < 0) {
    DumpTwoSpr(0xf8, bVar4);
  }
  if ((0x7f < bVar1) && (Sprite_Data[bVar4 + 7] <= Sprite_Data[bVar4 + 3])) {
    Sprite_Data[bVar4 + 4] = 0xf8;
    Sprite_Data[bVar4 + 0xc] = 0xf8;
  }
  return;
}

// SM2MAIN:b9b9
// Signature: [X] -> []
void DrawFireball(byte param_1) {
  byte bVar1;

  bVar1 = FBall_SprDataOffset[param_1];
  Sprite_Data[bVar1] = Fireball_Rel_YPos;
  Sprite_Data[bVar1 + 3] = Fireball_Rel_XPos;
  DrawFirebar(bVar1);
  return;
}

// SM2MAIN:b9c8
// Signature: [Y] -> []
void DrawFirebar(byte param_1) {
  byte bVar1;
  byte bVar2;

  bVar1 = FrameCounter;
  Sprite_Data[param_1 + 1] = FrameCounter >> 2 & 1 ^ 100;
  bVar2 = 2;
  if ((bVar1 >> 3 & 1) != 0) {
    bVar2 = 0xc2;
  }
  Sprite_Data[param_1 + 2] = bVar2;
  return;
}

// SM2MAIN:b9e4
// Signature: [X] -> []
void DrawExplosion_Fireball(byte param_1) {
  byte bVar1;

  bVar1 = Fireball_State[param_1];
  Fireball_State[param_1] = Fireball_State[param_1] + 1;
  bVar1 = bVar1 >> 1 & 7;
  if (bVar1 < 3) {
    DrawExplosion_Fireworks(bVar1, AltOrBlock_SprDataOffset[param_1]);
    return;
  }
  Fireball_State[param_1] = 0;
  return;
}

// SM2MAIN:b9f2
// Signature: [A, Y] -> [X]
byte DrawExplosion_Fireworks(byte param_1, byte param_2) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;

  bVar4 = param_2 + 1;
  DumpFourSpr(ExplosionTiles[param_1], bVar4);
  bVar2 = Fireball_Rel_YPos;
  bVar4 -= 1;
  bVar3 = ObjectOffset;
  bVar1 = Fireball_Rel_YPos - 4;
  Sprite_Data[bVar4] = bVar1;
  Sprite_Data[bVar4 + 8] = bVar1;
  Sprite_Data[bVar4 + 4] = bVar2 + 4;
  Sprite_Data[bVar4 + 0xc] = bVar2 + 4;
  bVar2 = Fireball_Rel_XPos;
  bVar1 = Fireball_Rel_XPos - 4;
  Sprite_Data[bVar4 + 3] = bVar1;
  Sprite_Data[bVar4 + 7] = bVar1;
  Sprite_Data[bVar4 + 0xb] = bVar2 + 4;
  Sprite_Data[bVar4 + 0xf] = bVar2 + 4;
  Sprite_Data[bVar4 + 2] = 2;
  Sprite_Data[bVar4 + 6] = 0x82;
  Sprite_Data[bVar4 + 10] = 0x42;
  Sprite_Data[bVar4 + 0xe] = 0xc2;
  return bVar3;
}

// SM2MAIN:ba41
// Signature: [X] -> [X]
byte DrawSmallPlatform(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bStack0000;

  bVar2 = Enemy_SprDataOffset[param_1] + 1;
  DumpSixSpr(0x5b, bVar2);
  bVar2 += 1;
  DumpSixSpr(2, bVar2);
  bVar1 = Enemy_Rel_XPos;
  bVar2 -= 2;
  Sprite_Data[bVar2 + 3] = Enemy_Rel_XPos;
  Sprite_Data[bVar2 + 0xf] = bVar1;
  Sprite_Data[bVar2 + 7] = bVar1 + 8;
  Sprite_Data[bVar2 + 0x13] = bVar1 + 8;
  Sprite_Data[bVar2 + 0xb] = bVar1 + 0x10;
  Sprite_Data[bVar2 + 0x17] = bVar1 + 0x10;
  bStack0000 = Enemy_Y_Position[param_1];
  bVar1 = bStack0000;
  if (bStack0000 < 0x20) {
    bVar1 = 0xf8;
  }
  DumpThreeSpr(bVar1, bVar2);
  bStack0000 += 0x80;
  if (bStack0000 < 0x20) {
    bStack0000 = 0xf8;
  }
  Sprite_Data[bVar2 + 0xc] = bStack0000;
  Sprite_Data[bVar2 + 0x10] = bStack0000;
  Sprite_Data[bVar2 + 0x14] = bStack0000;
  bVar1 = Enemy_OffscreenBits;
  if ((Enemy_OffscreenBits & 8) != 0) {
    Sprite_Data[bVar2] = 0xf8;
    Sprite_Data[bVar2 + 0xc] = 0xf8;
  }
  if ((bVar1 & 4) != 0) {
    Sprite_Data[bVar2 + 4] = 0xf8;
    Sprite_Data[bVar2 + 0x10] = 0xf8;
  }
  if ((bVar1 & 2) != 0) {
    Sprite_Data[bVar2 + 8] = 0xf8;
    Sprite_Data[bVar2 + 0x14] = 0xf8;
  }
  return ObjectOffset;
}

// SM2MAIN:babc
// Signature: [X] -> []
void DrawBubble(byte param_1) {
  byte bVar1;

  if ((SprObject_Y_HighPos[0] == 1) && ((Bubble_OffscreenBits & 8) == 0)) {
    bVar1 = Bubble_SprDataOffset[param_1];
    Sprite_Data[bVar1 + 3] = Bubble_Rel_XPos;
    Sprite_Data[bVar1] = Bubble_Rel_YPos;
    Sprite_Data[bVar1 + 1] = 0x74;
    Sprite_Data[bVar1 + 2] = 2;
  }
  return;
}

// SM2MAIN:bbc4
// Signature: [] -> []
void PlayerGfxHandler(void) {
  byte bVar1;
  byte abVar2;

  if ((InjuryTimer == 0) || (!(bool)(FrameCounter & 1))) {
    if (GameEngineSubroutine == 0xb) {
      PlayerGfxProcessing(PlayerGfxTblOffsets[14]);
      return;
    }
    if (PlayerChangeSizeFlag != 0) {
      bVar1 = HandleChangeSize();
      PlayerGfxProcessing(bVar1);
      return;
    }
    if (SwimmingFlag == 0) {
      FindPlayerAction();
      return;
    }
    if (Player_State == 0) {
      FindPlayerAction();
      return;
    }
    FindPlayerAction();
    if ((FrameCounter & 4) == 0) {
      abVar2 = PlayerOrSprDataOffset[0];
      if (!(bool)(PlayerFacingDir & 1)) {
        abVar2 = PlayerOrSprDataOffset[0] + 4;
      }
      bVar1 = 0;
      if (PlayerSize != 0) {
        if (Sprite_Data[abVar2 + 0x19] == PlayerGraphicsTable[158]) {
          return;
        }
        bVar1 = 1;
      }
      Sprite_Data[abVar2 + 0x19] = SwimKickTileNum[bVar1];
    }
  }
  return;
}

// SM2MAIN:bc0f
// Signature: [] -> []
void FindPlayerAction(void) {
  byte bVar1;

  bVar1 = ProcessPlayerAction();
  PlayerGfxProcessing(bVar1);
  return;
}

// SM2MAIN:bc20
// Signature: [A] -> []
void PlayerGfxProcessing(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;
  bool bVar4;
  byte bVar5;

  PlayerGfxOffset = param_1;
  RenderPlayerSub(4);
  ChkForPlayerAttrib();
  if (FireballThrowingTimer != 0) {
    bVar4 = PlayerAnimTimer < FireballThrowingTimer;
    FireballThrowingTimer = 0;
    if (bVar4) {
      FireballThrowingTimer = PlayerAnimTimer;
      PlayerGfxOffset = PlayerGfxTblOffsets[7];
      bVar3 = 4;
      if ((PlayerSpriteVarData1[0] | Left_Right_Buttons) != 0) {
        bVar3 = 3;
      }
      RenderPlayerSub(bVar3);
    }
  }
  bVar1 = SprObject_OffscrBits[0] >> 4;
  bVar2 = 3;
  bVar3 = PlayerOrSprDataOffset[0] + 0x18;
  do {
    bVar5 = bVar1 & 1;
    bVar1 >>= 1;
    if (bVar5 != 0) {
      DumpTwoSpr(0xf8, bVar3);
    }
    bVar3 -= 8;
    bVar2 -= 1;
  } while (bVar2 < 0x80);
  return;
}

// SM2MAIN:bc7f
// Signature: [] -> []
void DrawPlayer_Intermediate(void) {
  DrawPlayerLoop(0xb8, 4, IntermediatePlayerData[0], IntermediatePlayerData[1], IntermediatePlayerData[2],
                 IntermediatePlayerData[3], IntermediatePlayerData[5]);
  Sprite_Data[34] = Sprite_Data[38] | 0x40;
  return;
}

// SM2MAIN:bc99
// Signature: [A] -> []
void RenderPlayerSub(byte param_1) {
  Player_Pos_ForScroll = SprObject_Rel_XPos[0];
  DrawPlayerLoop(PlayerGfxOffset, PlayerOrSprDataOffset[0], SprObject_Rel_YPos[0], PlayerFacingDir,
                 Player_SprAttrib, SprObject_Rel_XPos[0], param_1);
  return;
}

// SM2MAIN:bcb7
// Signature: [X, Y, r02, r03, r04, r05, r07] -> []
void DrawPlayerLoop(byte param_1, byte param_2, byte param_3, byte param_4, byte param_5, byte param_6, byte param_7) {
  struct_xyr02 sVar1;

  do {
    sVar1 = DrawOneSpriteRow(PlayerGraphicsTable[param_1 + 1], param_1, param_2, PlayerGraphicsTable[param_1], param_3,
                             param_4, param_5, param_6);
    param_3 = sVar1.r02;
    param_2 = sVar1.y;
    param_1 = sVar1.x;
    param_7 -= 1;
  } while (param_7 != 0);
  return;
}

// SM2MAIN:bcc7
// Signature: [] -> [A]
byte ProcessPlayerAction(void) {
  byte bVar1;

  if (Player_State == 3) {
    bVar1 = 5;
    if (PlayerSpriteVarData2[0] != 0) {
      bVar1 = GetGfxOffsetAdder(5);
      bVar1 = ThreeFrameExtent(bVar1);
      return bVar1;
    }
  } else {
    if (Player_State == 2) {
      bVar1 = GetGfxOffsetAdder(4);
      bVar1 = GetCurrentAnimOffset(bVar1);
      return bVar1;
    }
    if (Player_State == 1) {
      if (SwimmingFlag != 0) {
        bVar1 = GetGfxOffsetAdder(1);
        if ((JumpSwimTimer | PlayerAnimCtrl) != 0) {
          bVar1 = FourFrameExtent(bVar1);
          return bVar1;
        }
        if ((bool)(A_B_Buttons >> 7)) {
          bVar1 = FourFrameExtent(bVar1);
          return bVar1;
        }
        bVar1 = GetCurrentAnimOffset(bVar1);
        return bVar1;
      }
      bVar1 = 6;
      if (CrouchingFlag == 0) {
        bVar1 = 0;
      }
    } else {
      bVar1 = 6;
      if ((CrouchingFlag == 0) && (bVar1 = 2, (PlayerSpriteVarData1[0] | Left_Right_Buttons) != 0)) {
        if ((Player_XSpeedAbsolute < 9) || ((Player_MovingDir & PlayerFacingDir) != 0)) {
          bVar1 = GetGfxOffsetAdder(4);
          bVar1 = FourFrameExtent(bVar1);
          return bVar1;
        }
        if (GameEngineSubroutine < 9) {
          NoiseSoundQueue = 0x80;
        }
        bVar1 = 3;
      }
    }
  }
  bVar1 = GetGfxOffsetAdder(bVar1);
  PlayerAnimCtrl = 0;
  return PlayerGfxTblOffsets[bVar1];
}

// SM2MAIN:bd47
// Signature: [Y] -> [A]
byte GetCurrentAnimOffset(byte param_1) {
  byte bVar1;

  bVar1 = GetOffsetFromAnimCtrl(PlayerAnimCtrl, param_1);
  return bVar1;
}

// SM2MAIN:bd4d
// Signature: [Y] -> [A]
byte FourFrameExtent(byte param_1) {
  byte bVar1;

  bVar1 = AnimationControl(3, param_1);
  return bVar1;
}

// SM2MAIN:bd52
// Signature: [Y] -> [A]
byte ThreeFrameExtent(byte param_1) {
  byte bVar1;

  bVar1 = AnimationControl(2, param_1);
  return bVar1;
}

// SM2MAIN:bd54
// Signature: [A, Y] -> [A]
byte AnimationControl(byte param_1, byte param_2) {
  byte bVar1;

  bVar1 = GetCurrentAnimOffset(param_2);
  if (PlayerAnimTimer == 0) {
    PlayerAnimTimer = PlayerAnimTimerSet;
    PlayerAnimCtrl += 1;
    if (param_1 <= PlayerAnimCtrl) {
      PlayerAnimCtrl = 0;
    }
  }
  return bVar1;
}

// SM2MAIN:bd76
// Signature: [Y] -> [Y]
byte GetGfxOffsetAdder(byte param_1) {
  if (PlayerSize != 0) {
    param_1 += 8;
  }
  return param_1;
}

// SM2MAIN:bd95
// Signature: [] -> [A]
byte HandleChangeSize(void) {
  byte bVar1;

  if (((FrameCounter & 3) == 0) && (PlayerAnimCtrl += 1, 9 < PlayerAnimCtrl)) {
    PlayerAnimCtrl = 0;
    PlayerChangeSizeFlag = 0;
  }
  if (PlayerSize != 0) {
    bVar1 = 9;
    if (ChangeSizeOffsetAdder[(byte)(PlayerAnimCtrl + 10)] == 0) {
      bVar1 = 1;
    }
    return PlayerGfxTblOffsets[bVar1];
  }
  bVar1 = GetOffsetFromAnimCtrl(ChangeSizeOffsetAdder[PlayerAnimCtrl], 0xf);
  return bVar1;
}

// SM2MAIN:bdb5
// Signature: [A, Y] -> [A]
byte GetOffsetFromAnimCtrl(byte param_1, byte param_2) {
  return (param_1 * 8 + PlayerGfxTblOffsets[param_2]) - ((char)(param_1 << 2) >> 7);
}

// SM2MAIN:bdce
// Signature: [] -> []
void ChkForPlayerAttrib(void) {
  byte abVar1;

  abVar1 = PlayerOrSprDataOffset[0];
  if (GameEngineSubroutine != 0xb) {
    if (((PlayerGfxOffset == 0x50) || (PlayerGfxOffset == 0xb8)) || (PlayerGfxOffset == 0xc0)) {
      goto C_S_IGAtt;
    }
    if (PlayerGfxOffset != 200) {
      return;
    }
  }
  Sprite_Data[PlayerOrSprDataOffset[0] + 0x12] = Sprite_Data[PlayerOrSprDataOffset[0] + 0x12] & 0x3f;
  Sprite_Data[abVar1 + 0x16] = Sprite_Data[abVar1 + 0x16] & 0x3f | 0x40;
C_S_IGAtt:
  Sprite_Data[abVar1 + 0x1a] = Sprite_Data[abVar1 + 0x1a] & 0x3f;
  Sprite_Data[abVar1 + 0x1e] = Sprite_Data[abVar1 + 0x1e] & 0x3f | 0x40;
  return;
}

// SM2MAIN:be0f
// Signature: [] -> [Y]
byte RelativePlayerPosition(void) {
  byte bVar1;

  bVar1 = 0;
  GetObjRelativePosition(0, 0);
  return bVar1;
}

// SM2MAIN:be16
// Signature: [X] -> [X]
byte RelativeBubblePosition(byte param_1) {
  byte bVar1;

  bVar1 = GetProperObjOffset(param_1, 1);
  GetObjRelativePosition(bVar1, 3);
  return ObjectOffset;
}

// SM2MAIN:be20
// Signature: [X] -> [X]
byte RelativeFireballPosition(byte param_1) {
  byte bVar1;

  bVar1 = GetProperObjOffset(param_1, 0);
  GetObjRelativePosition(bVar1, 2);
  return ObjectOffset;
}

// SM2MAIN:be2d
// Signature: [X] -> [X]
byte RelativeMiscPosition(byte param_1) {
  byte bVar1;

  bVar1 = GetProperObjOffset(param_1, 2);
  GetObjRelativePosition(bVar1, 6);
  return ObjectOffset;
}

// SM2MAIN:be37
// Signature: [X] -> [A, X, r00]
struct_axr00 RelativeEnemyPosition(byte param_1) {
  struct_axr00 sVar1;

  sVar1 = VariableObjOfsRelPos(1, param_1, 1);
  return sVar1;
}

// SM2MAIN:be3e
// Signature: [X] -> [X]
byte RelativeBlockPosition(byte param_1) {
  char cVar1;
  struct_axr00 sVar2;

  cVar1 = 4;
  sVar2 = VariableObjOfsRelPos(9, param_1, 4);
  sVar2 = VariableObjOfsRelPos(9, sVar2.x + 2, cVar1 + 1);
  return sVar2.x;
}

// SM2MAIN:be4a
// Signature: [A, X, Y] -> [A, X, r00]
struct_axr00 VariableObjOfsRelPos(byte param_1, byte param_2, byte param_3) {
  struct_axr00 sVar1;

  sVar1.a = GetObjRelativePosition(param_1 + param_2, param_3);
  sVar1.x = ObjectOffset;
  sVar1.r00 = param_2;
  return sVar1;
}

// SM2MAIN:be56
// Signature: [X, Y] -> [A]
byte GetObjRelativePosition(byte param_1, byte param_2) {
  byte bVar1;

  SprObject_Rel_YPos[param_2] = SprObject_Y_Position[param_1];
  bVar1 = SprObject_X_Position[param_1] - ScreenEdgeOrLeft_X_Pos[0];
  SprObject_Rel_XPos[param_2] = bVar1;
  return bVar1;
}

// SM2MAIN:be65
// Signature: [] -> []
void GetPlayerOffscreenBits(void) {
  GetOffScreenBitsSet(0, 0);
  return;
}

// SM2MAIN:be6c
// Signature: [X] -> [X]
byte GetFireballOffscreenBits(byte param_1) {
  byte bVar1;
  struct_xyi sVar2;

  bVar1 = GetProperObjOffset(param_1, 0);
  sVar2 = GetOffScreenBitsSet(bVar1, 2);
  return sVar2.x;
}

// SM2MAIN:be76
// Signature: [X] -> [X]
byte GetBubbleOffscreenBits(byte param_1) {
  byte bVar1;
  struct_xyi sVar2;

  bVar1 = GetProperObjOffset(param_1, 1);
  sVar2 = GetOffScreenBitsSet(bVar1, 3);
  return sVar2.x;
}

// SM2MAIN:be80
// Signature: [X] -> [X]
byte GetMiscOffscreenBits(byte param_1) {
  byte bVar1;
  struct_xyi sVar2;

  bVar1 = GetProperObjOffset(param_1, 2);
  sVar2 = GetOffScreenBitsSet(bVar1, 6);
  return sVar2.x;
}

// SM2MAIN:be8d
// Signature: [X, Y] -> [X]
byte GetProperObjOffset(byte param_1, byte param_2) { return param_1 + ObjOffsetData[param_2]; }

// SM2MAIN:be94
// Signature: [X] -> [X, Y]
struct_xyi GetEnemyOffscreenBits(byte param_1) {
  struct_xyi sVar1;

  sVar1 = GetOffScreenBitsSet(param_1 + 1, 1);
  return sVar1;
}

// SM2MAIN:be9b
// Signature: [X] -> [X]
byte GetBlockOffscreenBits(byte param_1) {
  struct_xyi sVar1;

  sVar1 = GetOffScreenBitsSet(param_1 + 9, 4);
  return sVar1.x;
}

// SM2MAIN:bea5
// Signature: [X, Y] -> [X, Y]
struct_xyi GetOffScreenBitsSet(byte param_1, byte param_2) {
  struct_xyi sVar1;
  struct_ar00i sVar2;
  byte bStack0000;

  bStack0000 = param_2;
  sVar2 = RunOffscrBitsSubs(param_1);
  sVar1.i = sVar2.i;
  SprObject_OffscrBits[bStack0000] = sVar2.a << 4 | sVar2.r00;
  sVar1.y = bStack0000;
  sVar1.x = ObjectOffset;
  return sVar1;
}

// SM2MAIN:bebc
// Signature: [X] -> [A, r00]
struct_ar00i RunOffscrBitsSubs(byte param_1) {
  byte bVar1;

  struct_ar00i sVar2;

  bVar1 = GetXOffscreenBits(param_1);
  bVar1 >>= 4;
  sVar2.a = GetYOffscreenBits(param_1);
  sVar2.r00 = bVar1;
  sVar2.i = (bool)0;
  return sVar2;
}

// SM2MAIN:bedb
// Signature: [X] -> [A]
byte GetXOffscreenBits(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  bVar3 = 1;
  do {
    bVar1 = (ScreenEdgeOrLeft_PageLoc[bVar3] - SprObject_PageLoc[param_1])
            - (ScreenEdgeOrLeft_X_Pos[bVar3] < SprObject_X_Position[param_1]);
    bVar2 = DefaultXOnscreenOfs[bVar3];
    if ((bVar1 < 0x80) && (bVar2 = DefaultXOnscreenOfs[bVar3 + 1], 0x7f < (byte)(bVar1 - 1))) {
      bVar2 = DividePDiff(8, bVar2, bVar3, 0x38, ScreenEdgeOrLeft_X_Pos[bVar3] - SprObject_X_Position[param_1]);
    }
  } while ((XOffscreenBitsData[bVar2] == 0) && (bVar3 -= 1, bVar3 < 0x80));
  return XOffscreenBitsData[bVar2];
}

// SM2MAIN:bf1e
// Signature: [X] -> [A]
byte GetYOffscreenBits(byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  bVar3 = 1;
  do {
    bVar1
        = (1 - SprObject_Y_HighPos[param_1]) - (HighPosUnitData[bVar3] < SprObject_Y_Position[param_1]);
    bVar2 = DefaultYOnscreenOfs[bVar3];
    if ((bVar1 < 0x80) && (bVar2 = DefaultYOnscreenOfs[bVar3 + 1], 0x7f < (byte)(bVar1 - 1))) {
      bVar2 = DividePDiff(4, bVar2, bVar3, 0x20, HighPosUnitData[bVar3] - SprObject_Y_Position[param_1]);
    }
  } while ((YOffscreenBitsData[bVar2] == 0) && (bVar3 -= 1, bVar3 < 0x80));
  return YOffscreenBitsData[bVar2];
}

// SM2MAIN:bf52
// Signature: [A, X, Y, r06, r07] -> [X]
byte DividePDiff(byte param_1, byte param_2, byte param_3, byte param_4, byte param_5) {
  if (param_5 < param_4) {
    param_2 = param_5 >> 3 & 7;
    if (param_3 == 0) {
      param_2 = param_2 + param_1 + (param_3 != 0);
    }
  }
  return param_2;
}

// SM2MAIN:bf67
// Signature: [X, Y, r00, r01, r02, r03, r04, r05] -> [X, Y, r02]
struct_xyr02 DrawSpriteObject(byte param_1, byte param_2, byte param_3, byte param_4, byte param_5, byte param_6,
                              byte param_7, byte param_8) {
  byte bVar1;
  struct_xyr02 sVar2;

  if ((param_6 >> 1 & 1) == 0) {
    Sprite_Data[param_2 + 1] = param_3;
    Sprite_Data[param_2 + 5] = param_4;
    bVar1 = 0;
  } else {
    Sprite_Data[param_2 + 5] = param_3;
    Sprite_Data[param_2 + 1] = param_4;
    bVar1 = 0x40;
  }
  Sprite_Data[param_2 + 2] = bVar1 | param_7;
  Sprite_Data[param_2 + 6] = bVar1 | param_7;
  Sprite_Data[param_2] = param_5;
  Sprite_Data[param_2 + 4] = param_5;
  Sprite_Data[param_2 + 3] = param_8;
  Sprite_Data[param_2 + 7] = param_8 + 8;
  sVar2.x = param_1 + 2;
  sVar2.y = param_2 + 8;
  sVar2.r02 = param_5 + 8;
  return sVar2;
}

// SM2MAIN:bfb0
// Signature: [] -> []
void AttractModeSubs(void) {
  FUN_3497(OperMode_Task);
  return;
}

// SM2MAIN:bfc2
// Signature: [] -> []
void HardWorldsCheckpoint(void) {
  FUN_34b3(DiskIOTask);
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
  FUN_34cb(DiskIOTask);
  return;
}

// SM2MAIN:c016
// Signature: [] -> []
void LoadWorlds1Thru4(void) {
  byte bVar1;
  bool bVar2;
  struct_ayz sVar3;

  if ((NotColdFlag != 0) && ((HardWorldFlag != 0 || (3 < WorldNumber)))) {
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
  FUN_34e3(DiskIOTask);
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
  FUN_34fb(DiskIOTask);
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
      GamesBeatenCount[0] = 0;
    }
    GamesBeatenCount[0] += 1;
    if (0x18 < GamesBeatenCount[0]) {
      GamesBeatenCount[0] = 0x18;
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
    bVar2 -= 1;
  } while (bVar2 < 0x80);
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

  if ((SavedJoypadBits[0] & 0x10) == 0) {
    if (((SavedJoypadBits[0] & 0x20) != 0) && (SelectTimer == 0)) {
      SelectTimer = (SavedJoypadBits[0] & 0x20) >> 1;
      ContinueMenuSelect ^= 1;
    }
    bVar1 = 2;
    do {
      Sprite_Data[bVar1 + 1] = GameOverCursorData[bVar1];
      bVar1 -= 1;
    } while (bVar1 < 0x80);
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
  bVar1 = 0xb;
  do {
    PlayerScoreDisplay_Or_ScoreAndCoinDisplay[bVar1] = 0;
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  Hidden1UpFlag += 1;
  ContinueGame();
  return;
}

// SM2MAIN:c241
// Signature: [] -> []
void LoadPhysicsData(void) {
  if (CurrentPlayer != 0) {
    ModifyPhysics(0x60, 0x21);
    return;
  }
  LoadMarioPhysics();
  return;
}

// SM2MAIN:c24a
// Signature: [] -> []
void LoadMarioPhysics(void) {
  ModifyPhysics(0xe, 0x10);
  return;
}

// SM2MAIN:c24e
// Signature: [X, Y] -> []
void ModifyPhysics(byte param_1, byte param_2) {
  byte bVar1;

  bVar1 = 0x10;
  RAM(0xb585) = param_1;
  do {
    JumpMForceData[bVar1] = JumpFrictionData[param_2];
    param_2 -= 1;
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  return;
}

// SM2MAIN:c2a4
// Signature: [] -> []
void LoadAreaPointer(void) {
  AreaPointer = FindAreaPointer();
  GetAreaType(AreaPointer);
  return;
}

// SM2MAIN:c2aa
// Signature: [A] -> [A]
byte GetAreaType(byte param_1) {
  AreaType = ((byte)((param_1 & 0x60) << 1) >> 7) << 1 | (byte)((param_1 & 0x60) << 2) >> 7;
  return AreaType;
}

// SM2MAIN:c2b4
// Signature: [] -> [A]
byte FindAreaPointer(void) { return AreaAddrOffsets[(byte)(WorldAddrOffsets[WorldNumber] + AreaNumber)]; }

void FUN_e149(void) { return; }

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
  if (3 < bVar4) {
    ForegroundScenery = 0;
    BackgroundColorCtrl = bVar4;
  }
  PlayerEntranceCtrl = (bVar3 & 0x38) >> 3;
  GameTimerSetting = (bVar3 >> 7) << 1 | (byte)((bVar3 & 0xc0) << 1) >> 7;
  bVar3 = AreaData[1];
  TerrainControl = bVar3 & 0xf;
  BackgroundScenery = (bVar3 & 0x30) >> 4;
  AreaStyle = (bVar3 >> 7) << 1 | (byte)((bVar3 & 0xc0) << 1) >> 7;
  if (AreaStyle == 3) {
    AreaStyle = 0;
    CloudTypeOverride = 3;
  }
  AreaData = CONCAT11(AltHard_AreaDataAddrs[bVar2 + 1] + (0xfd < bVar1), bVar1 + 2);
  return;
}

// SM2DATA4:c3d6
// Signature: [] -> []
void ChangeHalfwayPages(void) {
  byte bVar1;

  bVar1 = 7;
  do {
    HalfwayPageNybbles[bVar1] = AtoDHalfwayPages[bVar1];
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  return;
}

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
  if (3 < bVar4) {
    ForegroundScenery = 0;
    BackgroundColorCtrl = bVar4;
  }
  PlayerEntranceCtrl = (bVar3 & 0x38) >> 3;
  GameTimerSetting = (bVar3 >> 7) << 1 | (byte)((bVar3 & 0xc0) << 1) >> 7;
  bVar3 = AreaData[1];
  TerrainControl = bVar3 & 0xf;
  BackgroundScenery = (bVar3 & 0x30) >> 4;
  AreaStyle = (bVar3 >> 7) << 1 | (byte)((bVar3 & 0xc0) << 1) >> 7;
  if (AreaStyle == 3) {
    AreaStyle = 0;
    CloudTypeOverride = 3;
  }
  AreaData = CONCAT11(AreaDataAddrs[bVar2 + 1] + (0xfd < bVar1), bVar1 + 2);
  return;
}

// SM2MAIN:c46e
// Signature: [] -> []
void GameMenuRoutine(void) {
  byte bVar1;
  bool bVar2;

  if ((SavedJoypadBits[0] & 0x10) != 0) {
    CompletedWorlds = 0;
    DiskIOTask = 0;
    HardWorldFlag = 0;
    if ((7 < GamesBeatenCount[0]) && ((SavedJoypadBits[0] & 0x80) != 0)) {
      HardWorldFlag = 1;
    }
    if (DemoTimer != 0) {
      OperMode_Task += 1;
      PatchPlayerNamePal();
      WorldNumber = 0;
      LevelNumber = 0;
      AreaNumber = 0;
      bVar1 = 0xb;
      do {
        PlayerScoreDisplay_Or_ScoreAndCoinDisplay[bVar1] = 0;
        bVar1 -= 1;
      } while (bVar1 < 0x80);
      return;
    }
    goto ResetTitle;
  }
  if (SavedJoypadBits[0] == 0x20) {
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
    bVar1 = 0;
    do {
      (&VRAM_Buffer1_Offset)[force_byte(bVar1)] = 0;
      SprObject_X_MoveForce[bVar1] = 0;
      bVar1 -= 1;
    } while (bVar1 != 0);
    DrawMenuCursor();
    ScreenRoutineTask = ScreenRoutineTask + 1;
    return;
  }
  OperMode_Task = OperMode_Task + 1;
  return;
}

// SM2MAIN:c58a
// Signature: [] -> []
void WriteTopScore(void) {
  WriteDigits(0xfa);
  OperMode_Task = OperMode_Task + 1;
  return;
}

// SM2MAIN:c592
// Signature: [] -> []
void InitializeGame(void) {
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;

  CompletedWorlds = 0;
  HardWorldFlag = 0;
  CurrentPlayer = 0;
  PatchPlayerNamePal();
  SetupMenuCursor();
  bVar4 = 0x33;
  cVar1 = 0x0C;
  bVar3 = 0;
  do {
    bVar2 = 0x26;
    if (bVar3 < GamesBeatenCount[0]) {
      bVar2 = 0xf1;
    }
    TitleScreenGfxData[bVar4] = bVar2;
    bVar4 += 1;
    cVar1 += -1;
    if (cVar1 == 0) {
      bVar4 = 0x4d;
    }
    bVar3 += 1;
  } while (bVar3 != 0x18);
  bVar3 = InitializeMemory(0x6f);
  bVar4 = 0x1f;
  do {
    (&MusicOffset_Noise)[force_byte(bVar4)] = bVar3;
    bVar4 -= 1;
  } while (bVar4 < 0x80);
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
  byte bVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;

  bVar5 = PlayerNameOffsets[CurrentPlayer];
  cVar3 = CurrentPlayer + 1;
  bVar2 = 4;
  bVar4 = bVar5;
  do {
    bVar1 = PlayerNameData[bVar4];
    TopStatusBarLine[bVar2 + 3] = bVar1;
    ThankYouMessage[bVar2 + 0xd] = bVar1;
    bVar4 -= 1;
    bVar2 -= 1;
  } while (bVar2 < 0x80);
  bVar5 -= cVar3;
  bVar4 = 3;
  do {
    PlayerColors[bVar4] = PlayerPaletteData[bVar5];
    bVar5 -= 1;
    bVar4 -= 1;
  } while (bVar4 < 0x80);
  return;
}

// SM2DATA2+SM2DATA4:c470
// Signature: [X] -> []
void UpsideDownPipe_High(byte param_1) {
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  struct_xci sVar6;
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
  struct_xci sVar7;
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
      SpriteVarData1[param_1] = (SpriteVarData1[param_1] ^ 0xff) + 1;
      SpriteVarData2[param_1] = SpriteVarData2[param_1] + 1;
    }
    bVar3 = BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1];
    if (0x7f < SpriteVarData1[param_1]) {
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
      SprObject_PageLoc[0] += 0xfe < SprObject_X_Position[0];
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
  byte bVar1;

  bVar1 = 0xb;
  do {
    LeavesXPos[bVar1] = LeavesXPos[bVar1] + LeavesPosAdder[bVar1] + LeavesPosAdder[bVar1]
                        + CARRY1(LeavesXPos[bVar1], LeavesPosAdder[bVar1]);
    LeavesYPos[bVar1] = LeavesYPos[bVar1] + LeavesPosAdder[bVar1];
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  return;
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
    if (9 < PrimaryMsgCounter) {
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
  bVar1 = 0xfb < SecondaryMsgCounter;
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
    if (0x7f < NumberofLives) {
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
    bVar2 -= 1;
  } while (bVar2 < 0x80);
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
    bVar1 -= 1;
  } while (bVar1 < 0x80);
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
        if (7 < WorldNumber) {
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
    if (((EndControlCntr & 0x1f) == 0) && (BlueDelayFlag += 1, 10 < BlueDelayFlag)) {
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
    BlueColorOfs -= 1;
  } while (BlueColorOfs != 0);
  BlueColorOfs = bVar1;
  WorldNumber = bStack0000;
  Enemy_SprDataOffset[0] = 0x30;
  Enemy_Y_Position[0] = 0xb8;
  return;
}

// SM2DATA3:c858
// Signature: [] -> []
void WriteNameToVictoryMsg(void) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  ScreenRoutineTask = 0;
  bVar2 = 4;
  if (CurrentPlayer != 0) {
    bVar2 = 9;
  }
  bVar3 = 4;
  do {
    bVar1 = EndPlayerNameData[bVar2];
    ThankYouMessageFinal[bVar3 + 0xd] = bVar1;
    HurrahMsg[bVar3 + 0xe] = bVar1;
    bVar2 -= 1;
    bVar3 -= 1;
  } while (bVar3 < 0x80);
  return;
}
