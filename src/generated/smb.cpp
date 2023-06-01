#include "../smb_functions.h"
#include "smb.h"



// SMB:3000
// Signature: [A, r00] -> []

void FUN_3000(byte param_1,byte param_2)

{
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



// SMB:3014
// Signature: [A] -> []

void FUN_3014(byte param_1)

{
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



// SMB:3028
// Signature: [A, r00] -> []

void FUN_3028(byte param_1,byte param_2)

{
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



// SMB:3040
// Signature: [A] -> []

void FUN_3040(byte param_1)

{
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



// SMB:3080
// Signature: [A] -> []

void FUN_3080(byte param_1)

{
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



// SMB:3090
// Signature: [A] -> []

void FUN_3090(byte param_1)

{
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



// SMB:30b4
// Signature: [A, X, r00] -> []

void FUN_30b4(byte param_1,byte param_2,byte param_3)

{
  if (param_1 == 0) {
    VerticalPipe(param_2,param_3);
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
    VerticalPipe(param_2,param_3);
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
    QuestionBlock(param_2,param_3);
    return;
  }
  if (param_1 == 0x17) {
    QuestionBlock(param_2,param_3);
    return;
  }
  if (param_1 == 0x18) {
    QuestionBlock(param_2,param_3);
    return;
  }
  if (param_1 == 0x19) {
    Hidden1UpBlock(param_2,param_3);
    return;
  }
  if (param_1 == 0x1a) {
    BrickWithItem(param_2,param_3);
    return;
  }
  if (param_1 == 0x1b) {
    BrickWithItem(param_2,param_3);
    return;
  }
  if (param_1 == 0x1c) {
    BrickWithItem(param_2,param_3);
    return;
  }
  if (param_1 == 0x1d) {
    BrickWithCoins(param_2,param_3);
    return;
  }
  if (param_1 == 0x1e) {
    BrickWithItem(param_2,param_3);
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
    CastleBridgeObj(param_2,param_3);
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



// SMB:3174
// Signature: [A, X] -> []

void FUN_3174(byte param_1,byte param_2)

{
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



// SMB:3184
// Signature: [A] -> []

void FUN_3184(byte param_1)

{
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



// SMB:3198
// Signature: [A] -> []

void FUN_3198(byte param_1)

{
  if (param_1 == 0) {
    Entrance_GameTimerSetup(0x91);
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



// SMB:31d0
// Signature: [A] -> []

void FUN_31d0(byte param_1)

{
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



// SMB:31e4
// Signature: [A, X] -> []

void FUN_31e4(byte param_1,byte param_2)

{
  if (param_1 == 0) {
    MushFlowerBlock(param_2);
    return;
  }
  if (param_1 == 1) {
    CoinBlock(param_2,false);
    return;
  }
  if (param_1 == 2) {
    CoinBlock(param_2,false);
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
    CoinBlock(param_2,false);
    return;
  }
  if (param_1 == 8) {
    ExtraLifeMushBlock(param_2);
    return;
  }
  jmpengine_overflow(param_1);
  return;
}



// SMB:320c
// Signature: [A, X] -> []

void FUN_320c(byte param_1,byte param_2)

{
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
    NoInitCode();
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
    InitRedPTroopa(param_2,false);
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
    Setup_Vine(param_2,0x60);
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



// SMB:32ec
// Signature: [A, X] -> []

void FUN_32ec(byte param_1,byte param_2)

{
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



// SMB:3308
// Signature: [A, X] -> [X]

byte FUN_3308(byte param_1,byte param_2)

{
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



// SMB:3394
// Signature: [A, X] -> [X]

byte FUN_3394(byte param_1,byte param_2)

{
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
    bVar1 = MoveNormalEnemy(param_2);
    return bVar1;
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
    bVar1 = MoveBloober(param_2,false);
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



// SMB:33ec
// Signature: [A, X] -> [X]

byte FUN_33ec(byte param_1,byte param_2)

{
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



// SMB:340c
// Signature: [A, X] -> [X]

byte FUN_340c(byte param_1,byte param_2)

{
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



// SMB:8182
// Signature: [] -> []

void PauseRoutine(void)

{
  if ((OperMode == 2) || ((OperMode == 1 && (OperMode_Task == 3)))) {
    if (GamePauseTimer != 0) {
      GamePauseTimer = GamePauseTimer - 1;
      return;
    }
    if ((SavedJoypadBits[0] & 0x10) == 0) {
      GamePauseStatus &= 0x7f;
    }
    else if ((GamePauseStatus & 0x80) == 0) {
      GamePauseTimer = 0x2b;
      PauseSoundQueue = GamePauseStatus + 1;
      GamePauseStatus = GamePauseStatus ^ 1 | 0x80;
    }
  }
  return;
}



// SMB:81c6
// Signature: [] -> []

void SpriteShuffler(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  bVar2 = 0xe;
  do {
    bVar3 = PlayerOrSprDataOffset[bVar2];
    if (0x27 < bVar3) {
      bVar1 = bVar3 + SprShuffleAmt[SprShuffleAmtOffset];
      if (CARRY1(bVar3,SprShuffleAmt[SprShuffleAmtOffset])) {
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



// SMB:8212
// Signature: [r00] -> []

void OperModeExecutionTree(byte param_1)

{
  FUN_3000(OperMode,param_1);
  return;
}



// SMB:8220
// Signature: [] -> []

void MoveAllSpritesOffscreen(void)

{
  byte bVar1;
  
  bVar1 = 0;
  do {
    Sprite_Data[bVar1] = 0xf8;
    bVar1 += 4;
  } while (bVar1 != 0);
  return;
}



// SMB:8223
// Signature: [] -> []

void MoveSpritesOffscreen(void)

{
  byte bVar1;
  
  bVar1 = 4;
  do {
    Sprite_Data[bVar1] = 0xf8;
    bVar1 += 4;
  } while (bVar1 != 0);
  return;
}



// SMB:8231
// Signature: [] -> []

void TitleScreenMode(void)

{
  FUN_3014(OperMode_Task);
  return;
}



// SMB:8245
// Signature: [] -> []

void GameMenuRoutine(void)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  
  bVar3 = false;
  bVar2 = SavedJoypadBits[0] | SavedJoypadBits[1];
  if ((bVar2 == 0x10) || (bVar2 == 0x90)) {
    if (DemoTimer != 0) {
      if ((char)bVar2 < 0) {
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
      bVar2 = 0x17;
      do {
        PlayerScoreDisplay_Or_ScoreAndCoinDisplay[bVar2] = 0;
        bVar2 -= 1;
      } while (bVar2 < 0x80);
      return;
    }
    goto ResetTitle;
  }
  if (bVar2 == 0x20) {
SelectBLogic:
    if (DemoTimer == 0) goto ResetTitle;
    DemoTimer = 0x18;
    if (SelectTimer == 0) {
      SelectTimer = 0x10;
      if (bVar3) {
        WorldSelectNumber = WorldSelectNumber + 1 & 7;
        bVar2 = GoContinue(WorldSelectNumber);
        do {
          (&VRAM_Buffer1_Offset)[force_byte(bVar2)] = WSelectBufferTemplate[bVar2];
          bVar1 = bVar2 - 5;
          bVar2 = bVar2 + 1;
        } while (0x7f < bVar1);
        VRAM_Buffer1[3] = WorldNumber + 1;
      }
      else {
        NumberOfPlayers ^= 1;
        DrawMushroomIcon();
      }
    }
NullJoypad:
    SavedJoypadBits[0] = 0;
  }
  else {
    if (DemoTimer != 0) {
      if ((WorldSelectEnableFlag != 0) && (bVar2 == 0x40)) {
        bVar3 = true;
        goto SelectBLogic;
      }
      goto NullJoypad;
    }
    SelectTimer = bVar2;
    bVar3 = DemoEngine();
    if (bVar3) goto ResetTitle;
  }
  GameCoreRoutine();
  if (GameEngineSubroutine != 6) {
    return;
  }
ResetTitle:
  OperMode = 0;
  OperMode_Task = 0;
  Sprite0HitDetectFlag = 0;
  DisableScreenFlag = DisableScreenFlag + 1;
  return;
}



// SMB:830e
// Signature: [A] -> [X]

byte GoContinue(byte param_1)

{
  WorldNumber = param_1;
  OffScr_WorldNumber = param_1;
  AreaNumber = 0;
  OffScr_AreaNumber = 0;
  return 0;
}



// SMB:8325
// Signature: [] -> []

void DrawMushroomIcon(void)

{
  byte bVar1;
  
  bVar1 = 7;
  do {
    (&VRAM_Buffer1_Offset)[force_byte(bVar1)] = MushroomIconData[bVar1];
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  if (NumberOfPlayers != 0) {
    VRAM_Buffer1[3] = 0x24;
    VRAM_Buffer1[5] = 0xce;
  }
  return;
}



// SMB:836b
// Signature: [] -> [C]

bool DemoEngine(void)

{
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



// SMB:838b
// Signature: [r00] -> []

void VictoryMode(byte param_1)

{
  VictoryModeSubroutines(param_1);
  if (OperMode_Task != 0) {
    ObjectOffset = 0;
    EnemiesAndLoopsCore(0);
  }
  RelativePlayerPosition();
  PlayerGfxHandler();
  return;
}



// SMB:83a0
// Signature: [r00] -> []

void VictoryModeSubroutines(byte param_1)

{
  FUN_3028(OperMode_Task,param_1);
  return;
}



// SMB:83b0
// Signature: [] -> []

void SetupVictoryMode(void)

{
  FireballSpinDirectionOrVictoryDestPageLoc[0] = ScreenRight_PageLoc + 1;
  EventMusicQueue = 8;
  OperMode_Task = OperMode_Task + 1;
  return;
}



// SMB:83bd
// Signature: [] -> []

void PlayerVictoryWalk(void)

{
  bool bVar1;
  byte bVar2;
  
  bVar2 = 0;
  VictoryWalkControl = 0;
  if ((PlayerOrSprObject_PageLoc[0] != FireballSpinDirectionOrVictoryDestPageLoc[0]) ||
     (PlayerOrSprObject_X_Position[0] < 0x60)) {
    VictoryWalkControl = 1;
    bVar2 = 1;
  }
  AutoControlPlayer(bVar2);
  if (ScreenEdgeOrLeft_PageLoc[0] != FireballSpinDirectionOrVictoryDestPageLoc[0]) {
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



// SMB:83f6
// Signature: [] -> []

void PrintVictoryMessages(void)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  
  if (SecondaryMsgCounter == 0) {
    bVar1 = PrimaryMsgCounter;
    if (PrimaryMsgCounter == 0) goto ThankPlayer;
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
          }
          else {
            bVar2 = bVar1 + 1;
            if (WorldNumber != 7) {
              bVar3 = 3 < bVar1;
              if (bVar3) goto SetEndTimer;
              bVar2 = bVar1;
              if (2 < bVar1) goto IncMsgCounter;
            }
          }
          if (bVar2 == 3) {
            EventMusicQueue = 4;
          }
          VRAM_Buffer_AddrCtrl = bVar2 + 0xc;
        }
      }
      else if (1 < PrimaryMsgCounter) goto ThankPlayer;
    }
  }
IncMsgCounter:
  PrimaryMsgCounter += 0xfb < SecondaryMsgCounter;
  bVar3 = 6 < PrimaryMsgCounter;
  SecondaryMsgCounter = SecondaryMsgCounter + 4;
SetEndTimer:
  if (bVar3) {
    WorldEndTimer = 6;
    OperMode_Task += 1;
  }
  return;
}



// SMB:8461
// Signature: [] -> []

void PlayerEndWorld(void)

{
  if (WorldEndTimer == 0) {
    if (6 < WorldNumber) {
      if (((SavedJoypadBits[0] | SavedJoypadBits[1]) & 0x40) != 0) {
        WorldSelectEnableFlag = 1;
        NumberofLives = 0xff;
        TerminateGame();
      }
      return;
    }
    AreaNumber = 0;
    LevelNumber = 0;
    OperMode_Task = 0;
    WorldNumber += 1;
    LoadAreaPointer();
    FetchNewGameTimerFlag += 1;
    OperMode = 1;
  }
  return;
}



// SMB:84c3
// Signature: [X] -> [X]

byte FloateyNumbersRoutine(byte param_1)

{
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
  if (((bVar2 != 0x12) && (bVar2 != 0xd)) &&
     ((bVar2 == 5 ||
      (((bVar2 != 10 && (bVar2 != 0xb)) && ((8 < bVar2 || (Enemy_State[param_1] < 2)))))))) {
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
  DumpTwoSpr((FloateyNum_Y_Pos[param_1] - 8) - !bVar4,bVar3);
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



// SMB:8567
// Signature: [] -> []

void ScreenRoutines(void)

{
  FUN_3040(ScreenRoutineTask);
  return;
}



// SMB:858b
// Signature: [] -> []

void InitScreen(void)

{
  MoveAllSpritesOffscreen();
  InitializeNameTables();
  if (OperMode != 0) {
    VRAM_Buffer_AddrCtrl = 3;
  }
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}



// SMB:859b
// Signature: [] -> []

void SetupIntermediate(void)

{
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



// SMB:85bf
// Signature: [] -> []

void GetAreaPalette(void)

{
  VRAM_Buffer_AddrCtrl = AreaPalette[AreaType];
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}



// SMB:85e3
// Signature: [] -> []

void GetBackgroundColor(void)

{
  if (BackgroundColorCtrl != 0) {
    VRAM_Buffer_AddrCtrl = BGColorCtrl_Addr[BackgroundColorCtrl - 4];
  }
  ScreenRoutineTask += 1;
  GetPlayerColors();
  return;
}



// SMB:85f1
// Signature: [] -> [X]

byte GetPlayerColors(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  bVar3 = 0;
  if (CurrentPlayer != 0) {
    bVar3 = 4;
  }
  if (PlayerStatus == 2) {
    bVar3 = 8;
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



// SMB:8643
// Signature: [] -> []

void GetAlternatePalette1(void)

{
  if (AreaStyle == 1) {
    VRAM_Buffer_AddrCtrl = 0xb;
  }
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}



// SMB:8652
// Signature: [] -> []

void WriteTopStatusLine(void)

{
  WriteGameText(0);
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}



// SMB:865a
// Signature: [] -> []

void WriteBottomStatusLine(void)

{
  GetSBNybbles();
  VRAM_Buffer1[VRAM_Buffer1_Offset] = 0x20;
  VRAM_Buffer1[VRAM_Buffer1_Offset + 1] = 0x73;
  VRAM_Buffer1[VRAM_Buffer1_Offset + 2] = 3;
  VRAM_Buffer1[VRAM_Buffer1_Offset + 3] = WorldNumber + 1;
  VRAM_Buffer1[VRAM_Buffer1_Offset + 4] = 0x28;
  VRAM_Buffer1[VRAM_Buffer1_Offset + 5] = LevelNumber + 1;
  VRAM_Buffer1[VRAM_Buffer1_Offset + 6] = 0;
  VRAM_Buffer1_Offset = VRAM_Buffer1_Offset + 6;
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}



// SMB:8693
// Signature: [] -> []

void DisplayTimeUp(void)

{
  if (GameTimerExpiredFlag != 0) {
    GameTimerExpiredFlag = 0;
    WriteGameText(2);
    ResetScreenTimer();
    DisableScreenFlag = 0;
    return;
  }
  ScreenRoutineTask = ScreenRoutineTask + 2;
  return;
}



// SMB:86a8
// Signature: [] -> []

void DisplayIntermediate(void)

{
  if (OperMode != 0) {
    if (OperMode == 3) {
      ScreenTimer = 0x12;
      WriteGameText(3);
      OperMode_Task = OperMode_Task + 1;
      return;
    }
    if ((AltEntranceControl == 0) && ((AreaType == 3 || (DisableIntermediate == 0)))) {
      DrawPlayer_Intermediate();
      WriteGameText(1);
      ResetScreenTimer();
      DisableScreenFlag = 0;
      return;
    }
  }
  ScreenRoutineTask = 8;
  return;
}



// SMB:86e6
// Signature: [] -> []

void AreaParserTaskControl(void)

{
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



// SMB:8732
// Signature: [] -> []

void ClearBuffersDrawIcon(void)

{
  byte bVar1;
  
  if (OperMode == 0) {
    bVar1 = 0;
    do {
      (&VRAM_Buffer1_Offset)[force_byte(bVar1)] = 0;
      SprObject_X_MoveForce[bVar1] = 0;
      bVar1 -= 1;
    } while (bVar1 != 0);
    DrawMushroomIcon();
    ScreenRoutineTask = ScreenRoutineTask + 1;
    return;
  }
  OperMode_Task = OperMode_Task + 1;
  return;
}



// SMB:8749
// Signature: [] -> []

void WriteTopScore(void)

{
  UpdateNumber(0xfa);
  OperMode_Task = OperMode_Task + 1;
  return;
}



// SMB:8808
// Signature: [A] -> []

void WriteGameText(byte param_1)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = param_1 << 1;
  if (3 < bVar1) {
    if (7 < bVar1) {
      bVar1 = 8;
    }
    if (NumberOfPlayers == 0) {
      bVar1 += 1;
    }
  }
  bVar1 = GameTextOffsets[bVar1];
  bVar2 = 0;
  do {
    if (GameText[bVar1] == 0xff) break;
    VRAM_Buffer1[bVar2] = GameText[bVar1];
    bVar1 += 1;
    bVar2 += 1;
  } while (bVar2 != 0);
  VRAM_Buffer1[bVar2] = 0;
  if (3 < param_1) {
    bVar1 = ((param_1 - 4) - (3 >= param_1)) * 4;
    bVar2 = 0;
    do {
      VRAM_Buffer1[bVar2 + 0x1b] = WarpZoneNumbers[bVar1];
      bVar1 += 1;
      bVar2 += 4;
    } while (bVar2 < 0xc);
    VRAM_Buffer1_Offset = 0x2c;
    return;
  }
  if (param_1 == 1) {
    VRAM_Buffer1[8] = NumberofLives + 1;
    if (VRAM_Buffer1[8] >= 10) {
      VRAM_Buffer1[8] = (NumberofLives - 9) - (VRAM_Buffer1[8] < 10);
      VRAM_Buffer1[7] = 0x9f;
    }
    VRAM_Buffer1[19] = WorldNumber + 1;
    VRAM_Buffer1[21] = LevelNumber + 1;
    return;
  }
  if (NumberOfPlayers != 0) {
    bVar1 = CurrentPlayer;
    if ((param_1 == 2) && (OperMode != 3)) {
      bVar1 = CurrentPlayer ^ 1;
    }
    if ((bVar1 & 1) != 0) {
      bVar1 = 4;
      do {
        VRAM_Buffer1[bVar1 + 3] = LuigiName[bVar1];
        bVar1 -= 1;
      } while (bVar1 < 0x80);
    }
  }
  return;
}



// SMB:889d
// Signature: [] -> []

void ResetSpritesAndScreenTimer(void)

{
  if (ScreenTimer == 0) {
    MoveAllSpritesOffscreen();
    ResetScreenTimer();
    return;
  }
  return;
}



// SMB:88a5
// Signature: [] -> []

void ResetScreenTimer(void)

{
  ScreenTimer = 7;
  ScreenRoutineTask = ScreenRoutineTask + 1;
  return;
}



// SMB:88ae
// Signature: [] -> []

void RenderAreaGraphics(void)

{
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
    VRAM_Buffer2[bVar4 + 3] = RAM(CONCAT11(bVar3,bVar6) + (ushort)bVar2);
    VRAM_Buffer2[bVar4 + 4] = RAM(CONCAT11(bVar3,bVar6) + (ushort)(byte)(bVar2 + 1));
    bVar6 = bVar5;
    if (bVar7 == 0) {
      if ((bool)(bVar9 & 1)) {
        bVar8 >>= 2;
NextMTRow:
        bVar6 = bVar5 + 1;
      }
      else {
        bVar8 = ((bVar9 & 1) << 1 | bVar1 >> 7) << 1 | (byte)(bVar8 << 1) >> 7;
      }
    }
    else {
      if ((bool)(bVar9 & 1)) goto NextMTRow;
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
  } while( true );
}



// SMB:896a
// Signature: [] -> []

void RenderAttributeTables(void)

{
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



// SMB:89e1
// Signature: [] -> []

void ColorRotation(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  bVar2 = FrameCounter & 7;
  if ((bVar2 == 0) && (bVar1 = VRAM_Buffer1_Offset, VRAM_Buffer1_Offset < 0x31)) {
    do {
      VRAM_Buffer1[bVar1] = BlankPalette[bVar2];
      bVar2 += 1;
      bVar1 = bVar1 + 1;
    } while (bVar2 < 8);
    bVar1 = 3;
    bVar2 = AreaType << 2;
    bVar3 = VRAM_Buffer1_Offset;
    do {
      VRAM_Buffer1[bVar3 + 3] = Palette3Data[bVar2];
      bVar2 += 1;
      bVar3 += 1;
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



// SMB:8a4d
// Signature: [r02, r06] -> [r05]

byte RemoveCoin_Axe(byte param_1,byte param_2)

{
  byte bVar1;
  
  bVar1 = 3;
  if (AreaType == 0) {
    bVar1 = 4;
  }
  bVar1 = PutBlockMetatile(bVar1,AreaType,0x41,param_1,param_2);
  VRAM_Buffer_AddrCtrl = 6;
  return bVar1;
}



// SMB:8a61
// Signature: [A, X, r02, r06] -> []

void ReplaceBlockMetatile(byte param_1,byte param_2,byte param_3,byte param_4)

{
  WriteBlockMetatile(param_1,param_2,param_3,param_4);
  Block_ResidualCounter += 1;
  Block_RepFlag[param_2] = Block_RepFlag[param_2] - 1;
  return;
}



// SMB:8a6b
// Signature: [X, r02, r06] -> []

void DestroyBlockMetatile(byte param_1,byte param_2,byte param_3)

{
  WriteBlockMetatile(0,param_1,param_2,param_3);
  return;
}



// SMB:8a6d
// Signature: [A, X, r02, r06] -> []

void WriteBlockMetatile(byte param_1,byte param_2,byte param_3,byte param_4)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = 3;
  if ((((param_1 != 0) && (bVar1 = 0, param_1 != 0x58)) && (param_1 != 0x51)) &&
     ((bVar1 = 1, param_1 != 0x5d && (param_1 != 0x52)))) {
    bVar1 = 2;
  }
  bVar2 = VRAM_Buffer1_Offset + 1;
  PutBlockMetatile(bVar1,param_2,bVar2,param_3,param_4);
  MoveVOffset(bVar2);
  return;
}



// SMB:8a8f
// Signature: [Y] -> []

void MoveVOffset(byte param_1)

{
  VRAM_Buffer1_Offset = param_1 + 9;
  return;
}



// SMB:8a97
// Signature: [A, X, Y, r02, r06] -> [r05]

byte PutBlockMetatile(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5)

{
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
  bVar3 = ((bVar1 >> 7) << 1 | (byte)(bVar1 * 2) >> 7) + CARRY1(bVar1 * 4,bVar2) + cVar4;
  RemBridge(param_1 << 2,param_3,param_2,bVar1 * 4 + bVar2,bVar3);
  return bVar3;
}



// SMB:8acd
// Signature: [X, Y, r00, r04, r05] -> []

void RemBridge(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5)

{
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



// SMB:8e19
// Signature: [] -> []

void InitializeNameTables(void)

{
  byte bVar1;
  
  bVar1 = ppustatus();
  WritePPUReg1(Mirror_PPU_CTRL_REG1 & 0xf0 | 0x10);
  WriteNTAddr(0x24);
  WriteNTAddr(0x20);
  return;
}



// SMB:8eed
// Signature: [A] -> []

void WritePPUReg1(byte param_1)

{
  ppuctrl(param_1);
  Mirror_PPU_CTRL_REG1 = param_1;
  return;
}



// SMB:8f06
// Signature: [A] -> []

void PrintStatusBarNumbers(byte param_1)

{
  OutputNumbers(param_1);
  OutputNumbers(param_1 >> 4);
  return;
}



// SMB:8f11
// Signature: [A] -> []

void OutputNumbers(byte param_1)

{
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



// SMB:8f5f
// Signature: [Y] -> []

void DigitsMathRoutine(byte param_1)

{
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
      }
      else {
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



// SMB:8f97
// Signature: [] -> []

void UpdateTopScore(void)

{
  TopScoreCheck(5);
  TopScoreCheck(0xb);
  return;
}



// SMB:8f9e
// Signature: [X] -> []

void TopScoreCheck(byte param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  bool bVar4;
  byte bVar5;
  bool bVar6;
  
  bVar3 = 5;
  bVar4 = true;
  do {
    bVar6 = bVar4;
    bVar5 = bVar3;
    bVar1 = PlayerScoreDisplay_Or_ScoreAndCoinDisplay[param_1];
    bVar2 = DisplayDigits_Or_TopScoreDisplay[bVar5];
    param_1 -= 1;
    bVar3 = bVar5 - 1;
    bVar4 = bVar6 && bVar2 <= bVar1 || !bVar6 && bVar2 < bVar1;
  } while ((byte)(bVar5 - 1) < 0x80);
  if (bVar6 && bVar2 <= bVar1 || !bVar6 && bVar2 < bVar1) {
    do {
      param_1 += 1;
      DisplayDigits_Or_TopScoreDisplay[bVar5] = PlayerScoreDisplay_Or_ScoreAndCoinDisplay[param_1];
      bVar5 += 1;
    } while (bVar5 < 6);
  }
  return;
}



// SMB:8fcf
// Signature: [] -> []

void InitializeGame(void)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = InitializeMemory(0x6f);
  bVar2 = 0x1f;
  do {
    (&MusicOffset_Noise)[force_byte(bVar2)] = bVar1;
    bVar2 -= 1;
  } while (bVar2 < 0x80);
  DemoTimer = 0x18;
  LoadAreaPointer();
  InitializeArea();
  return;
}



// SMB:8fe4
// Signature: [] -> []

void InitializeArea(void)

{
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
  GetAreaDataAddrs();
  if ((PrimaryHardMode != 0) || ((3 < WorldNumber && ((WorldNumber != 4 || (1 < LevelNumber)))))) {
    SecondaryHardMode += 1;
  }
  if (HalfwayPage != 0) {
    PlayerEntranceCtrl = 2;
  }
  AreaMusicQueue = 0x80;
  DisableScreenFlag = 1;
  OperMode_Task = OperMode_Task + 1;
  return;
}



// SMB:9061
// Signature: [] -> []

void PrimaryGameSetup(void)

{
  FetchNewGameTimerFlag = 1;
  PlayerSize = 1;
  NumberofLives = 2;
  OffScr_NumberofLives = 2;
  SecondaryGameSetup();
  return;
}



// SMB:9071
// Signature: [] -> []

void SecondaryGameSetup(void)

{
  byte bVar1;
  
  DisableScreenFlag = 0;
  bVar1 = 0;
  do {
    (&VRAM_Buffer1_Offset)[force_byte(bVar1)] = 0;
    bVar1 += 1;
  } while (bVar1 != 0);
  GameTimerExpiredFlag = 0;
  DisableIntermediate = 0;
  BackloadingFlag = 0;
  BalPlatformAlignment = 0xff;
  Mirror_PPU_CTRL_REG1 = Mirror_PPU_CTRL_REG1 & 0xfe | ScreenEdgeOrLeft_PageLoc[0] & 1;
  GetAreaMusic();
  SprShuffleAmt[2] = 0x38;
  SprShuffleAmt[1] = 0x48;
  SprShuffleAmt[0] = 0x58;
  bVar1 = 0xe;
  do {
    PlayerOrSprDataOffset[bVar1] = DefaultSprOffsets[bVar1];
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  bVar1 = 3;
  do {
    Sprite_Data[bVar1] = Sprite0Data[bVar1];
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  DoNothing2();
  DoNothing1();
  Sprite0HitDetectFlag = Sprite0HitDetectFlag + 1;
  OperMode_Task = OperMode_Task + 1;
  return;
}



// SMB:90ed
// Signature: [] -> []

void GetAreaMusic(void)

{
  byte bVar1;
  
  if (OperMode != 0) {
    if (((AltEntranceControl == 2) ||
        ((bVar1 = 5, PlayerEntranceCtrl != 6 && (PlayerEntranceCtrl != 7)))) &&
       (bVar1 = AreaType, CloudTypeOverride != 0)) {
      bVar1 = 4;
    }
    AreaMusicQueue = MusicSelectData[bVar1];
    return;
  }
  return;
}



// SMB:9131
// Signature: [r07] -> []

void Entrance_GameTimerSetup(byte param_1)

{
  byte bVar1;
  
  PlayerOrSprObject_PageLoc[0] = ScreenEdgeOrLeft_PageLoc[0];
  VerticalForceDown = 0x28;
  PlayerFacingDir = 1;
  PlayerOrSprObject_Y_HighPos[0] = 1;
  Player_State = 0;
  Player_CollisionBits -= 1;
  HalfwayPage = 0;
  SwimmingFlag = AreaType == 0;
  bVar1 = PlayerEntranceCtrl;
  if ((AltEntranceControl != 0) && (AltEntranceControl != 1)) {
    bVar1 = PlayerStarting_X_Pos[AltEntranceControl + 2];
  }
  PlayerOrSprObject_X_Position[0] = PlayerStarting_X_Pos[AltEntranceControl];
  PlayerOrSprObject_Y_Position[0] = PlayerStarting_Y_Pos[bVar1];
  Player_SprAttrib = PlayerBGPriorityData[bVar1];
  bVar1 = GetPlayerColors();
  if ((GameTimerSetting != 0) && (FetchNewGameTimerFlag != 0)) {
    GameTimerDisplay[0] = GameTimerData[GameTimerSetting];
    GameTimerDisplay[2] = 1;
    GameTimerDisplay[1] = 0;
    FetchNewGameTimerFlag = 0;
    StarInvincibleTimer = 0;
  }
  if (JoypadOverride != 0) {
    Player_State = 3;
    InitBlock_XY_Pos(0);
    Block_Y_Position[0] = 0xf0;
    bVar1 = 5;
    Setup_Vine(5,0);
  }
  if (AreaType == 0) {
    SetupBubble(bVar1,param_1);
  }
  GameEngineSubroutine = 7;
  return;
}



// SMB:91cd
// Signature: [] -> []

void PlayerLoseLife(void)

{
  byte bVar1;
  
  DisableScreenFlag += 1;
  Sprite0HitDetectFlag = 0;
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
  if ((HalfwayPage != ScreenEdgeOrLeft_PageLoc[0]) && (ScreenEdgeOrLeft_PageLoc[0] <= HalfwayPage))
  {
    HalfwayPage = 0;
  }
  TransposePlayers();
  ContinueGame();
  return;
}



// SMB:9218
// Signature: [] -> []

void GameOverMode(void)

{
  FUN_3080(OperMode_Task);
  return;
}



// SMB:9224
// Signature: [] -> []

void SetupGameOver(void)

{
  ScreenRoutineTask = 0;
  Sprite0HitDetectFlag = 0;
  EventMusicQueue = 2;
  DisableScreenFlag = DisableScreenFlag + 1;
  OperMode_Task = OperMode_Task + 1;
  return;
}



// SMB:9237
// Signature: [] -> []

void RunGameOver(void)

{
  DisableScreenFlag = 0;
  if ((SavedJoypadBits[0] & 0x10) != 0) {
    TerminateGame();
    return;
  }
  if (ScreenTimer == 0) {
    TerminateGame();
    return;
  }
  return;
}



// SMB:9248
// Signature: [] -> []

void TerminateGame(void)

{
  bool bVar1;
  
  EventMusicQueue = 0x80;
  bVar1 = TransposePlayers();
  if (!bVar1) {
    ContinueGame();
    return;
  }
  ContinueWorld = WorldNumber;
  OperMode_Task = 0;
  ScreenTimer = 0;
  OperMode = 0;
  return;
}



// SMB:9264
// Signature: [] -> []

void ContinueGame(void)

{
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



// SMB:92aa
// Signature: [] -> []

void DoNothing1(void)

{
  Misc_Collision_Flag[11] = 0xff;
  return;
}



// SMB:92af
// Signature: [] -> []

void DoNothing2(void)

{
  return;
}



// SMB:92b0
// Signature: [] -> []

void AreaParserTaskHandler(void)

{
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



// SMB:92c8
// Signature: [A] -> []

void AreaParserTasks(byte param_1)

{
  FUN_3090(param_1);
  return;
}



// SMB:92db
// Signature: [] -> []

void IncrementColumnPos(void)

{
  byte bVar1;
  
  bVar1 = CurrentColumnPos + 1 & 0xf;
  CurrentColumnPos = CurrentColumnPos + 1;
  if (bVar1 == 0) {
    CurrentPageLoc += 1;
    CurrentColumnPos = bVar1;
  }
  BlockBufferColumnPos = BlockBufferColumnPos + 1 & 0x1f;
  return;
}



// SMB:93fc
// Signature: [] -> []

void AreaParserCore(void)

{
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
      if (0x7f < (byte)(bVar4 - 3)) break;
      bVar4 -= 3;
    } while (bVar4 < 0x80);
    bVar7 = (bool)-((char)(bVar4 << 3) >> 7);
    cVar1 = bVar4 * 0x10 + BSceneDataOffsets[BackgroundScenery - 1] + bVar7;
    bVar4 = BackSceneryData
            [(byte)(cVar1 + CurrentColumnPos +
                   (CARRY1(bVar4 * 0x10,BSceneDataOffsets[BackgroundScenery - 1]) ||
                   bVar7 && cVar1 == 0))];
    if (bVar4 != 0) {
      cVar1 = (bVar4 & 0xf) - 1;
      bVar2 = cVar1 * 3 - (cVar1 >> 7);
      bVar4 >>= 4;
      cVar1 = 3;
      do {
        MetatileBuffer[bVar4] = BackSceneryMetatiles[bVar2];
        bVar2 += 1;
        bVar4 += 1;
        if (bVar4 == 0xb) break;
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
    bVar4 = 0x62;
  }
  else {
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
      if (bVar5 == 0xd) goto RendBBuf;
      if ((AreaType == 2) && (bVar5 == 0xb)) {
        bVar4 = 0x54;
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
    if (bVar5 < BlockBuffLowBounds
                [(byte)((MetatileBuffer[bVar2] >> 7) << 1 |
                       (byte)((MetatileBuffer[bVar2] & 0xc0) << 1) >> 7)]) {
      bVar5 = 0;
    }
    RAM(SUB32(sVar8,0) + (ushort)bVar4) = bVar5;
    bVar4 += 0x10;
    bVar2 += 1;
  } while (bVar2 < 0xd);
  return;
}



// SMB:9508
// Signature: [] -> []

void ProcessAreaData(void)

{
  byte bVar1;
  byte bVar2;
  
  do {
    bVar1 = 2;
    do {
      BehindAreaParserFlag = 0;
      ObjectOffset = bVar1;
      if ((AreaData[AreaDataOffset] == 0xfd) || (AreaObjectLength[bVar1] < 0x80)) {
RdyDecode:
        DecodeAreaData(bVar1,AreaDataOffset);
      }
      else {
        bVar2 = AreaDataOffset + 1;
        if (((char)AreaData[bVar2] < 0) && (AreaObjectPageSel == 0)) {
          AreaObjectPageSel = 1;
          AreaObjectPageLoc += 1;
        }
        if ((AreaData[AreaDataOffset] & 0xf) != 0xd) {
          if (((AreaData[AreaDataOffset] & 0xf) != 0xe) || (BackloadingFlag == 0)) goto CheckRear;
          goto RdyDecode;
        }
        if (((AreaData[bVar2] & 0x40) == 0) && (AreaObjectPageSel == 0)) {
          AreaObjectPageLoc = AreaData[bVar2] & 0x1f;
          AreaObjectPageSel = 1;
        }
        else {
CheckRear:
          if (CurrentPageLoc <= AreaObjectPageLoc) goto RdyDecode;
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
  } while( true );
}



// SMB:9589
// Signature: [] -> []

void IncAreaObjOffset(void)

{
  AreaDataOffset = AreaDataOffset + 2;
  AreaObjectPageSel = 0;
  return;
}



// SMB:9595
// Signature: [X, Y] -> []

void DecodeAreaData(byte param_1,byte param_2)

{
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
    bVar1 = 0x2e;
  }
  else if (bVar1 == 0xd) {
    cVar2 = 0x22;
    if ((AreaData[(byte)(param_2 + 1)] & 0x40) == 0) {
      return;
    }
    if ((AreaData[(byte)(param_2 + 1)] & 0x7f) == 0x4b) {
      LoopCommand += 1;
    }
    bVar1 = AreaData[(byte)(param_2 + 1)] & 0x3f;
  }
  else {
    if (bVar1 < 0xc) {
      bVar4 = param_2 + 1;
      bVar1 = AreaData[bVar4] & 0x70;
      if (bVar1 == 0) {
        cVar2 = 0x16;
        bVar1 = AreaData[bVar4] & 0xf;
        goto NormObj;
      }
      if ((bVar1 == 0x70) && ((AreaData[bVar4] & 8) != 0)) {
        bVar1 = 0;
      }
    }
    else {
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
    }
    else if (((AreaData[AreaDataOffset] & 0xf) != 0xe) || (BackloadingFlag == 0)) {
      return;
    }
    AreaObjOffsetBuffer[ObjectOffset] = AreaDataOffset;
    IncAreaObjOffset();
  }
  FUN_30b4(bVar1 + cVar2,bVar3,bVar1);
  return;
}



// SMB:9645
// Signature: [] -> []

void LoopCmdE(void)

{
  return;
}



// SMB:96c5
// Signature: [X] -> []

void AlterAreaAttributes(byte param_1)

{
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



// SMB:96f2
// Signature: [] -> []

void ScrollLockObject_Warp(void)

{
  WarpZoneControl = 4;
  if ((WorldNumber != 0) && (WarpZoneControl = 5, AreaType == 1)) {
    WarpZoneControl = 6;
  }
  WriteGameText(WarpZoneControl);
  KillEnemies(0xd);
  ScrollLockObject();
  return;
}



// SMB:970d
// Signature: [] -> []

void ScrollLockObject(void)

{
  ScrollLock = ScrollLock ^ 1;
  return;
}



// SMB:9716
// Signature: [A] -> []

void KillEnemies(byte param_1)

{
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



// SMB:972b
// Signature: [r00] -> []

void AreaFrenzy(byte param_1)

{
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



// SMB:9740
// Signature: [X] -> []

void AreaStyleObject(byte param_1)

{
  FUN_3174(AreaStyle,param_1);
  return;
}



// SMB:974c
// Signature: [X] -> []

void TreeLedge(byte param_1)

{
  byte bVar1;
  struct_yr07i sVar2;
  
  sVar2 = GetLrgObjAttrib(param_1);
  bVar1 = sVar2.r07;
  if (AreaObjectLength[param_1] == 0) {
    NoUnder(0x18,bVar1);
    return;
  }
  if ((0x7f < AreaObjectLength[param_1]) &&
     (AreaObjectLength[param_1] = sVar2.y, (CurrentPageLoc | CurrentColumnPos) != 0)) {
    NoUnder(0x16,bVar1);
    return;
  }
  MetatileBuffer[bVar1] = 0x17;
  RenderUnderPart(0x4c,bVar1 + 1,0xf);
  return;
}



// SMB:9778
// Signature: [X] -> []

void MushroomLedge(byte param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  struct_ycr07 sVar4;
  
  sVar4 = ChkLrgObjLength(param_1);
  bVar3 = sVar4.r07;
  if (sVar4.c != false) {
    MushroomLedgeHalfLen[param_1] = AreaObjectLength[param_1] >> 1;
    NoUnder(0x19,bVar3);
    return;
  }
  bVar2 = AreaObjectLength[param_1];
  if (bVar2 == 0) {
    NoUnder(0x1b,bVar3);
    return;
  }
  bVar1 = MushroomLedgeHalfLen[param_1];
  MetatileBuffer[bVar3] = 0x1a;
  if (bVar2 == bVar1) {
    MetatileBuffer[(byte)(bVar3 + 1)] = 0x4f;
    RenderUnderPart(0x50,bVar3 + 2,0xf);
    return;
  }
  return;
}



// SMB:97b0
// Signature: [A, r07] -> []

void NoUnder(byte param_1,byte param_2)

{
  RenderUnderPart(param_1,param_2,0);
  return;
}



// SMB:97ba
// Signature: [X] -> []

void PulleyRopeObject(byte param_1)

{
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



// SMB:9806
// Signature: [X] -> []

void CastleObject(byte param_1)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  struct_yr07i sVar5;
  struct_xci sVar6;
  byte bStack0000;
  
  sVar5 = GetLrgObjAttrib(param_1);
  bVar3 = sVar5.y;
  ChkLrgObjFixedLength(param_1,4);
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
      MetatileBuffer[10] = 0x52;
    }
    else if (bVar4 == 2) {
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



// SMB:986f
// Signature: [X] -> []

void WaterPipe(byte param_1)

{
  struct_yr07i sVar1;
  
  sVar1 = GetLrgObjAttrib(param_1);
  MetatileBuffer[sVar1.r07] = 0x6b;
  MetatileBuffer[sVar1.r07 + 1] = 0x6c;
  return;
}



// SMB:9882
// Signature: [X] -> []

void IntroPipe(byte param_1)

{
  byte bVar1;
  struct_yci sVar2;
  
  ChkLrgObjFixedLength(param_1,3);
  sVar2 = RenderSidewaysPipe(param_1,10);
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



// SMB:98ab
// Signature: [X] -> []

void ExitPipe(byte param_1)

{
  struct_yr07i sVar1;
  
  ChkLrgObjFixedLength(param_1,3);
  sVar1 = GetLrgObjAttrib(param_1);
  RenderSidewaysPipe(param_1,sVar1.y);
  return;
}



// SMB:98b3
// Signature: [X, Y] -> [Y, C]

struct_yci RenderSidewaysPipe(byte param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  
  bVar3 = param_2 - 1;
  bVar2 = AreaObjectLength[param_1];
  bVar1 = SidePipeShaftData[bVar2];
  if (bVar1 != 0) {
    bVar3 = RenderUnderPart(bVar1,0,param_2 - 2);
  }
  MetatileBuffer[bVar3] = SidePipeTopPart[bVar2];
  MetatileBuffer[bVar3 + 1] = SidePipeBottomPart[bVar2];
  return (struct_yci)CONCAT12(0,CONCAT11(bVar1 == 0,bVar2));
}



// SMB:98e5
// Signature: [X, r00] -> []

void VerticalPipe(byte param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  struct_yr06r07 sVar5;
  struct_xci sVar6;
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
      Enemy_PageLoc[bVar4] = CurrentPageLoc + (0xf7 < bVar3);
      Enemy_Y_HighPos[bVar4] = 1;
      Enemy_Flag[bVar4] = 1;
      bVar3 = GetAreaObjYPosition(bVar2);
      Enemy_Y_Position[bVar4] = bVar3;
      Enemy_ID[bVar4] = 0xd;
      InitPiranhaPlant(bVar4);
    }
  }
  MetatileBuffer[bVar2] = VerticalPipeData[bStack0000];
  RenderUnderPart(VerticalPipeData[bStack0000 + 2],bVar2 + 1,bVar1 - 1);
  return;
}



// SMB:9939
// Signature: [X] -> [Y, r06, r07]

struct_yr06r07 GetPipeHeight(byte param_1)

{
  struct_yr07i sVar1;
  
  ChkLrgObjFixedLength(param_1,1);
  sVar1 = GetLrgObjAttrib(param_1);
  return (struct_yr06r07)
         (CONCAT12(sVar1.r07,CONCAT11(sVar1.y,AreaObjectLength[param_1])) & 0xff07ff);
}



// SMB:994a
// Signature: [] -> [X, C]

struct_xci FindEmptyEnemySlot(void)

{
  byte bVar1;
  
  bool bVar2;
  
  bVar1 = 0;
  do {
    bVar2 = false;
    if (Enemy_Flag[bVar1] == 0) break;
    bVar1 += 1;
    bVar2 = 4 < bVar1;
  } while (bVar1 != 5);
  return (struct_xci)CONCAT12(0,CONCAT11(bVar2,bVar1));
}



// SMB:9957
// Signature: [X] -> []

void Hole_Water(byte param_1)

{
  ChkLrgObjLength(param_1);
  MetatileBuffer[10] = 0x86;
  RenderUnderPart(0x87,0xb,1);
  return;
}



// SMB:9968
// Signature: [X] -> []

void QuestionBlockRow_High(byte param_1)

{
  byte bStack0000;
  
  bStack0000 = 3;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xc0;
  return;
}



// SMB:996b
// Signature: [X] -> []

void QuestionBlockRow_Low(byte param_1)

{
  byte bStack0000;
  
  bStack0000 = 7;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xc0;
  return;
}



// SMB:9979
// Signature: [X] -> []

void Bridge_High(byte param_1)

{
  byte bStack0000;
  
  bStack0000 = 6;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xb;
  RenderUnderPart(99,bStack0000 + 1,0);
  return;
}



// SMB:997c
// Signature: [X] -> []

void Bridge_Middle(byte param_1)

{
  byte bStack0000;
  
  bStack0000 = 7;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xb;
  RenderUnderPart(99,bStack0000 + 1,0);
  return;
}



// SMB:997f
// Signature: [X] -> []

void Bridge_Low(byte param_1)

{
  byte bStack0000;
  
  bStack0000 = 9;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xb;
  RenderUnderPart(99,bStack0000 + 1,0);
  return;
}



// SMB:9994
// Signature: [X] -> []

void FlagBalls_Residual(byte param_1)

{
  struct_yr07i sVar1;
  
  sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(0x6d,2,sVar1.y);
  return;
}



// SMB:999e
// Signature: [] -> []

void FlagpoleObject(void)

{
  byte bVar1;
  
  MetatileBuffer[0] = 0x24;
  RenderUnderPart(0x25,1,8);
  MetatileBuffer[10] = 0x61;
  bVar1 = GetAreaObjXPosition();
  Enemy_X_Position[5] = bVar1 - 8;
  Enemy_PageLoc[5] = CurrentPageLoc - (bVar1 < 8);
  Enemy_Y_Position[5] = 0x30;
  FlagpoleFNum_Y_Pos = 0xb0;
  Enemy_ID[5] = 0x30;
  Enemy_Flag[5] = Enemy_Flag[5] + 1;
  return;
}



// SMB:99d0
// Signature: [] -> []

void EndlessRope(void)

{
  RenderUnderPart(0x40,0,0xf);
  return;
}



// SMB:99d7
// Signature: [X] -> []

void BalancePlatRope(byte param_1)

{
  struct_yr07i sVar1;
  byte bStack0000;
  
  bStack0000 = param_1;
  RenderUnderPart(0x44,1,0xf);
  sVar1 = GetLrgObjAttrib(bStack0000);
  RenderUnderPart(0x40,1,sVar1.y);
  return;
}



// SMB:99f2
// Signature: [X] -> []

void RowOfCoins(byte param_1)

{
  struct_ycr07 sVar1;
  byte bStack0000;
  
  bStack0000 = CoinMetatileData[AreaType];
  sVar1 = ChkLrgObjLength(param_1);
  RenderUnderPart(bStack0000,sVar1.r07,0);
  return;
}



// SMB:9a01
// Signature: [X, r00] -> []

void CastleBridgeObj(byte param_1,byte param_2)

{
  ChkLrgObjFixedLength(param_1,0xc);
  ChainObj(param_2);
  return;
}



// SMB:9a09
// Signature: [r00] -> []

void AxeObj(byte param_1)

{
  VRAM_Buffer_AddrCtrl = 8;
  ChainObj(param_1);
  return;
}



// SMB:9a0e
// Signature: [r00] -> []

void ChainObj(byte param_1)

{
  RenderUnderPart(C_ObjectRow[param_1 + 1],C_ObjectRow[param_1 - 2],0);
  return;
}



// SMB:9a19
// Signature: [X] -> []

void EmptyBlock(byte param_1)

{
  struct_yr07i sVar1;
  
  sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(0xc4,sVar1.r07,0);
  return;
}



// SMB:9a2e
// Signature: [X] -> []

void RowOfBricks(byte param_1)

{
  byte bVar1;
  struct_ycr07 sVar2;
  byte bStack0000;
  
  bVar1 = AreaType;
  if (CloudTypeOverride != 0) {
    bVar1 = 4;
  }
  bStack0000 = BrickMetatiles[bVar1];
  sVar2 = ChkLrgObjLength(param_1);
  RenderUnderPart(bStack0000,sVar2.r07,0);
  return;
}



// SMB:9a3e
// Signature: [X] -> []

void RowOfSolidBlocks(byte param_1)

{
  struct_ycr07 sVar1;
  byte bStack0000;
  
  bStack0000 = SolidBlockMetatiles[AreaType];
  sVar1 = ChkLrgObjLength(param_1);
  RenderUnderPart(bStack0000,sVar1.r07,0);
  return;
}



// SMB:9a50
// Signature: [X] -> []

void ColumnOfBricks(byte param_1)

{
  struct_yr07i sVar1;
  byte bStack0000;
  
  bStack0000 = BrickMetatiles[AreaType];
  sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(bStack0000,sVar1.r07,sVar1.y);
  return;
}



// SMB:9a59
// Signature: [X] -> []

void ColumnOfSolidBlocks(byte param_1)

{
  struct_yr07i sVar1;
  byte bStack0000;
  
  bStack0000 = SolidBlockMetatiles[AreaType];
  sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(bStack0000,sVar1.r07,sVar1.y);
  return;
}



// SMB:9a69
// Signature: [X] -> []

void BulletBillCannon(byte param_1)

{
  byte bVar1;
  byte bVar2;
  struct_yr07i sVar3;
  
  sVar3 = GetLrgObjAttrib(param_1);
  bVar1 = sVar3.r07;
  MetatileBuffer[bVar1] = 100;
  if ((byte)(sVar3.y - 1) < 0x80) {
    MetatileBuffer[(byte)(bVar1 + 1)] = 0x65;
    bVar2 = sVar3.y - 2;
    if (bVar2 < 0x80) {
      RenderUnderPart(0x66,bVar1 + 2,bVar2);
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



// SMB:9ab7
// Signature: [X] -> []

void StaircaseObject(byte param_1)

{
  struct_ycr07 sVar1;
  
  sVar1 = ChkLrgObjLength(param_1);
  if (sVar1.c != false) {
    StaircaseControl = 9;
  }
  StaircaseControl -= 1;
  RenderUnderPart(0x61,StaircaseRowData[StaircaseControl],StaircaseHeightData[StaircaseControl]);
  return;
}



// SMB:9ad3
// Signature: [X] -> []

void Jumpspring(byte param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  struct_yr07i sVar4;
  struct_xci sVar5;
  
  sVar4 = GetLrgObjAttrib(param_1);
  bVar1 = sVar4.r07;
  sVar5 = FindEmptyEnemySlot();
  bVar3 = sVar5.x;
  bVar2 = GetAreaObjXPosition();
  Enemy_X_Position[bVar3] = bVar2;
  Enemy_PageLoc[bVar3] = CurrentPageLoc;
  bVar2 = GetAreaObjYPosition(bVar1);
  Enemy_Y_Position[bVar3] = bVar2;
  PlayerSpriteVarData1[bVar3 + 1] = bVar2;
  Enemy_ID[bVar3] = 0x32;
  Enemy_Y_HighPos[bVar3] = 1;
  Enemy_Flag[bVar3] = Enemy_Flag[bVar3] + 1;
  MetatileBuffer[bVar1] = 0x67;
  MetatileBuffer[bVar1 + 1] = 0x68;
  return;
}



// SMB:9b01
// Signature: [X, r00] -> []

void Hidden1UpBlock(byte param_1,byte param_2)

{
  if (Hidden1UpFlag != 0) {
    Hidden1UpFlag = 0;
    BrickWithItem(param_1,param_2);
    return;
  }
  return;
}



// SMB:9b0e
// Signature: [X, r00] -> []

void QuestionBlock(byte param_1,byte param_2)

{
  byte bVar1;
  struct_yr07i sVar2;
  byte bStack0000;
  
  bVar1 = GetAreaObjectID(param_2);
  bStack0000 = BrickQBlockMetatiles[bVar1];
  sVar2 = GetLrgObjAttrib(param_1);
  RenderUnderPart(bStack0000,sVar2.r07,0);
  return;
}



// SMB:9b14
// Signature: [X, r00] -> []

void BrickWithCoins(byte param_1,byte param_2)

{
  BrickCoinTimerFlag = 0;
  BrickWithItem(param_1,param_2);
  return;
}



// SMB:9b19
// Signature: [X, r00] -> []

void BrickWithItem(byte param_1,byte param_2)

{
  char cVar1;
  byte bVar2;
  struct_yr07i sVar3;
  byte bStack0000;
  
  bVar2 = GetAreaObjectID(param_2);
  cVar1 = 0;
  if (AreaType != 1) {
    cVar1 = 5;
  }
  bStack0000 = BrickQBlockMetatiles[(byte)(cVar1 + bVar2)];
  sVar3 = GetLrgObjAttrib(param_1);
  RenderUnderPart(bStack0000,sVar3.r07,0);
  return;
}



// SMB:9b36
// Signature: [r00] -> [Y]

byte GetAreaObjectID(byte param_1)

{
  return param_1;
}



// SMB:9b41
// Signature: [X] -> []

void Hole_Empty(byte param_1)

{
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
  RenderUnderPart(HoleMetatiles[AreaType],8,0xf);
  return;
}



// SMB:9b7d
// Signature: [A, X, Y] -> [X]

byte RenderUnderPart(byte param_1,byte param_2,byte param_3)

{
  byte bVar1;
  
  do {
    bVar1 = MetatileBuffer[param_2];
    AreaObjectHeight = param_3;
    if ((bVar1 == 0) ||
       (((bVar1 != 0x17 && (bVar1 != 0x1a)) &&
        ((bVar1 == 0xc0 || ((bVar1 < 0xc0 && ((bVar1 != 0x54 || (param_1 != 0x50)))))))))) {
      MetatileBuffer[param_2] = param_1;
    }
    param_2 += 1;
  } while ((param_2 < 0xd) && (param_3 = AreaObjectHeight - 1, param_3 < 0x80));
  return param_2;
}



// SMB:9bac
// Signature: [X] -> [Y, C, r07]

struct_ycr07 ChkLrgObjLength(byte param_1)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  struct_yr07i sVar4;
  
  sVar4 = GetLrgObjAttrib(param_1);
  bVar1 = sVar4.r07;
  bVar2 = sVar4.y;
  bVar3 = ChkLrgObjFixedLength(param_1,bVar2);
  return (struct_ycr07)CONCAT12(bVar1,CONCAT11(bVar3,bVar2));
}



// SMB:9baf
// Signature: [X, Y] -> [C]

bool ChkLrgObjFixedLength(byte param_1,byte param_2)

{
  byte bVar1;
  
  bVar1 = AreaObjectLength[param_1];
  if (0x7f < bVar1) {
    AreaObjectLength[param_1] = param_2;
  }
  return 0x7f < bVar1;
}



// SMB:9bbb
// Signature: [X] -> [Y, r07]

struct_yr07i GetLrgObjAttrib(byte param_1)

{
  
  
  return (struct_yr07i)
         (CONCAT12(0,CONCAT11(AreaData[AreaObjOffsetBuffer[param_1]],
                                 AreaData[(byte)(AreaObjOffsetBuffer[param_1] + 1)])) & 0xff0f0f);
}



// SMB:9bcb
// Signature: [] -> [A]

byte GetAreaObjXPosition(void)

{
  return CurrentColumnPos << 4;
}



// SMB:9bd3
// Signature: [r07] -> [A]

byte GetAreaObjYPosition(byte param_1)

{
  return param_1 * 0x10 + 0x20;
}



// SMB:9be1
// Signature: [A] -> [r06, r07]

struct_r06r07i GetBlockBufferAddr(byte param_1)

{
  
  
  return (struct_r06r07i)
         CONCAT12(0,CONCAT11(BlockBufferAddr[(param_1 >> 4) + 2],
                                (param_1 & 0xf) + BlockBufferAddr[param_1 >> 4]));
}



// SMB:9c03
// Signature: [] -> []

void LoadAreaPointer(void)

{
  AreaPointer = FindAreaPointer();
  GetAreaType(AreaPointer);
  return;
}



// SMB:9c09
// Signature: [A] -> [A]

byte GetAreaType(byte param_1)

{
  AreaType = ((byte)((param_1 & 0x60) << 1) >> 7) << 1 | (byte)((param_1 & 0x60) << 2) >> 7;
  return AreaType;
}



// SMB:9c13
// Signature: [] -> [A]

byte FindAreaPointer(void)

{
  return AreaAddrOffsets[(byte)(WorldAddrOffsets[WorldNumber] + AreaNumber)];
}



// SMB:9c22
// Signature: [] -> []

void GetAreaDataAddrs(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  bVar2 = GetAreaType(AreaPointer);
  AreaAddrsLOffset = AreaPointer & 0x1f;
  EnemyData._0_1_ = EnemyDataAddrLow[(byte)(EnemyAddrHOffsets[bVar2] + AreaAddrsLOffset)];
  EnemyData._1_1_ = EnemyDataAddrHigh[(byte)(EnemyAddrHOffsets[bVar2] + AreaAddrsLOffset)];
  bVar1 = AreaDataAddrLow[(byte)(AreaDataHOffsets[AreaType] + AreaAddrsLOffset)];
  AreaData = CONCAT11(AreaDataAddrHigh
                              [(byte)(AreaDataHOffsets[AreaType] + AreaAddrsLOffset)],bVar1);
  bVar2 = *AreaData;
  bVar3 = bVar2 & 7;
  ForegroundScenery = bVar3;
  if (3 < bVar3) {
    ForegroundScenery = 0;
    BackgroundColorCtrl = bVar3;
  }
  PlayerEntranceCtrl = (bVar2 & 0x38) >> 3;
  GameTimerSetting = (bVar2 >> 7) << 1 | (byte)((bVar2 & 0xc0) << 1) >> 7;
  bVar2 = AreaData[1];
  TerrainControl = bVar2 & 0xf;
  BackgroundScenery = (bVar2 & 0x30) >> 4;
  bVar2 = (bVar2 >> 7) << 1 | (byte)((bVar2 & 0xc0) << 1) >> 7;
  AreaStyle = bVar2;
  if (bVar2 == 3) {
    AreaStyle = 0;
    CloudTypeOverride = bVar2;
  }
  AreaData = CONCAT11(AreaDataAddrHigh
                              [(byte)(AreaDataHOffsets[AreaType] + AreaAddrsLOffset)] +
                              (0xfd < bVar1),bVar1 + 2);
  return;
}



// SMB:aedc
// Signature: [] -> []

void GameMode(void)

{
  FUN_3184(OperMode_Task);
  return;
}



// SMB:aeea
// Signature: [] -> []

void GameCoreRoutine(void)

{
  byte bVar1;
  
  SavedJoypadBits[0] = SavedJoypadBits[CurrentPlayer];
  GameRoutines();
  if (OperMode_Task < 3) {
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
  if (0x7f < (byte)(PlayerOrSprObject_Y_HighPos[0] - 2)) {
    if (StarInvincibleTimer == 0) {
      ResetPalStar();
      goto LAB_3469;
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
LAB_3469:
  PreviousA_B_Buttons = A_B_Buttons;
  Left_Right_Buttons = 0;
  UpdScrollVar();
  return;
}



// SMB:af6f
// Signature: [] -> []

void UpdScrollVar(void)

{
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



// SMB:af93
// Signature: [] -> []

void ScrollHandler(void)

{
  byte bVar1;
  
  Player_X_Scroll += Platform_X_Scroll;
  if ((((ScrollLock != 0) || (Player_Pos_ForScroll < 0x50)) || (SideCollisionTimer != 0)) ||
     (0x7f < (byte)(Player_X_Scroll - 1))) {
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



// SMB:afc4
// Signature: [Y] -> []

void ScrollScreen(byte param_1)

{
  ScrollThirtyTwo = param_1 + ScrollThirtyTwo;
  HorizontalScroll = param_1 + ScreenEdgeOrLeft_X_Pos[0];
  ScreenEdgeOrLeft_PageLoc[0] += CARRY1(param_1,ScreenEdgeOrLeft_X_Pos[0]);
  Mirror_PPU_CTRL_REG1 = Mirror_PPU_CTRL_REG1 & 0xfe | ScreenEdgeOrLeft_PageLoc[0] & 1;
  ScreenEdgeOrLeft_X_Pos[0] = HorizontalScroll;
  ScrollAmount = param_1;
  GetScreenPosition();
  ScrollIntervalTimer = 8;
  ChkPOffscr();
  return;
}



// SMB:b000
// Signature: [] -> []

void ChkPOffscr(void)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = GetXOffscreenBits(0);
  bVar2 = 0;
  if (((bool)(bVar1 >> 7)) || (bVar2 = 1, (bVar1 & 0x20) != 0)) {
    PlayerOrSprObject_X_Position[0] = ScreenEdgeOrLeft_X_Pos[bVar2] - X_SubtracterData[bVar2];
    PlayerOrSprObject_PageLoc[0] =
         ScreenEdgeOrLeft_PageLoc[bVar2] - (ScreenEdgeOrLeft_X_Pos[bVar2] < X_SubtracterData[bVar2])
    ;
    if (Left_Right_Buttons != OffscrJoypadBitsData[bVar2]) {
      PlayerSpriteVarData1[0] = 0;
    }
  }
  Platform_X_Scroll = 0;
  return;
}



// SMB:b038
// Signature: [] -> [A]

byte GetScreenPosition(void)

{
  ScreenRight_X_Pos = ScreenEdgeOrLeft_X_Pos[0] - 1;
  ScreenRight_PageLoc = ScreenEdgeOrLeft_PageLoc[0] + (ScreenEdgeOrLeft_X_Pos[0] != 0);
  return ScreenRight_PageLoc;
}



// SMB:b04a
// Signature: [] -> []

void GameRoutines(void)

{
  FUN_3198(GameEngineSubroutine);
  return;
}



// SMB:b069
// Signature: [] -> []

void PlayerEntrance(void)

{
  byte bVar1;
  
  if (AltEntranceControl == 2) {
    if (JoypadOverride == 0) {
      MovePlayerYAxis(0xff);
      if (0x90 < PlayerOrSprObject_Y_Position[0]) {
        return;
      }
    }
    else {
      if (VineHeight != 0x60) {
        return;
      }
      DisableCollisionDet = 0x98 < PlayerOrSprObject_Y_Position[0];
      bVar1 = 1;
      if ((bool)DisableCollisionDet) {
        Player_State = 3;
        bVar1 = 8;
        Block_Buffer_1[180] = 8;
      }
      AutoControlPlayer(bVar1);
      if (PlayerOrSprObject_X_Position[0] < 0x48) {
        return;
      }
    }
  }
  else {
    if (PlayerOrSprObject_Y_Position[0] < 0x30) {
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



// SMB:b0e6
// Signature: [A] -> []

void AutoControlPlayer(byte param_1)

{
  SavedJoypadBits[0] = param_1;
  PlayerCtrlRoutine();
  return;
}



// SMB:b0e9
// Signature: [] -> []

void PlayerCtrlRoutine(void)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  
  if (GameEngineSubroutine != 0xb) {
    if ((AreaType == 0) &&
       ((PlayerOrSprObject_Y_HighPos[0] != 1 || (0xcf < PlayerOrSprObject_Y_Position[0])))) {
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
  BoundingBoxCore(0,bVar3);
  PlayerBGCollision();
  if ((((0x3f < PlayerOrSprObject_Y_Position[0]) && (GameEngineSubroutine != 5)) &&
      (GameEngineSubroutine != 7)) && (3 < GameEngineSubroutine)) {
    Player_SprAttrib &= 0xdf;
  }
  if ((byte)(PlayerOrSprObject_Y_HighPos[0] - 2) < 0x80) {
    ScrollLock = 1;
    cVar1 = 4;
    cVar2 = 0;
    if (((GameTimerExpiredFlag != 0) || (CloudTypeOverride == 0)) &&
       (cVar2 = 1, GameEngineSubroutine != 0xb)) {
      if (DeathMusicLoaded == 0) {
        EventMusicQueue = 1;
        DeathMusicLoaded = 1;
      }
      cVar1 = 6;
    }
    if ((byte)(PlayerOrSprObject_Y_HighPos[0] - cVar1) < 0x80) {
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



// SMB:b1c7
// Signature: [] -> []

void Vine_AutoClimb(void)

{
  if ((PlayerOrSprObject_Y_HighPos[0] == 0) && (PlayerOrSprObject_Y_Position[0] < 0xe4)) {
    SetEntr();
    return;
  }
  JoypadOverride = 8;
  Player_State = 3;
  AutoControlPlayer(8);
  return;
}



// SMB:b1dd
// Signature: [] -> []

void SetEntr(void)

{
  AltEntranceControl = 2;
  ChgAreaMode();
  return;
}



// SMB:b1e5
// Signature: [] -> []

void VerticalPipeEntry(void)

{
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



// SMB:b200
// Signature: [A] -> []

void MovePlayerYAxis(byte param_1)

{
  PlayerOrSprObject_Y_Position[0] = param_1 + PlayerOrSprObject_Y_Position[0];
  return;
}



// SMB:b206
// Signature: [] -> []

void SideExitPipeEntry(void)

{
  EnterSidePipe();
  ChangeAreaTimer -= 1;
  if (ChangeAreaTimer == 0) {
    AltEntranceControl = 2;
    ChgAreaMode();
    return;
  }
  return;
}



// SMB:b213
// Signature: [] -> [A]

byte ChgAreaMode(void)

{
  DisableScreenFlag = DisableScreenFlag + 1;
  OperMode_Task = 0;
  Sprite0HitDetectFlag = 0;
  return 0;
}



// SMB:b21f
// Signature: [] -> []

void EnterSidePipe(void)

{
  byte bVar1;
  byte bVar2;
  
  PlayerSpriteVarData1[0] = 8;
  bVar1 = PlayerOrSprObject_X_Position[0] & 0xf;
  bVar2 = 1;
  if (bVar1 == 0) {
    bVar2 = bVar1;
    PlayerSpriteVarData1[0] = bVar1;
  }
  AutoControlPlayer(bVar2);
  return;
}



// SMB:b233
// Signature: [] -> []

void PlayerChangeSize(void)

{
  if (TimerControl == 0xf8) {
    InitChangeSize();
    return;
  }
  if (TimerControl == 0xc4) {
    DonePlayerTask();
  }
  return;
}



// SMB:b245
// Signature: [] -> []

void PlayerInjuryBlink(void)

{
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



// SMB:b255
// Signature: [] -> []

void InitChangeSize(void)

{
  if (PlayerChangeSizeFlag == 0) {
    PlayerAnimCtrl = PlayerChangeSizeFlag;
    PlayerChangeSizeFlag = 1;
    PlayerSize ^= 1;
  }
  return;
}



// SMB:b269
// Signature: [] -> []

void PlayerDeath(void)

{
  if (TimerControl < 0xf0) {
    PlayerCtrlRoutine();
    return;
  }
  return;
}



// SMB:b273
// Signature: [] -> []

void DonePlayerTask(void)

{
  TimerControl = 0;
  GameEngineSubroutine = 8;
  return;
}



// SMB:b27d
// Signature: [] -> []

void PlayerFireFlower(void)

{
  if (TimerControl != 0xc0) {
    CyclePlayerPalette(FrameCounter >> 2);
    return;
  }
  DonePlayerTask();
  ResetPalStar();
  return;
}



// SMB:b288
// Signature: [A] -> []

void CyclePlayerPalette(byte param_1)

{
  Player_SprAttrib = Player_SprAttrib & 0xfc | param_1 & 3;
  return;
}



// SMB:b29a
// Signature: [] -> []

void ResetPalStar(void)

{
  Player_SprAttrib = Player_SprAttrib & 0xfc;
  return;
}



// SMB:b2a4
// Signature: [] -> []

void FlagpoleSlide(void)

{
  byte bVar1;
  
  if (Enemy_ID[5] == 0x30) {
    Square1SoundQueue = FlagpoleSoundQueue;
    bVar1 = 0;
    FlagpoleSoundQueue = 0;
    if (PlayerOrSprObject_Y_Position[0] < 0x9e) {
      bVar1 = 4;
    }
    AutoControlPlayer(bVar1);
    return;
  }
  GameEngineSubroutine = GameEngineSubroutine + 1;
  return;
}



// SMB:b2ca
// Signature: [] -> []

void PlayerEndLevel(void)

{
  AutoControlPlayer(1);
  if ((0xad < PlayerOrSprObject_Y_Position[0]) && (ScrollLock != 0)) {
    EventMusicQueue = 0x20;
    ScrollLock = 0;
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
  if (CoinTallyFor1Ups < Hidden1UpCoinAmts[WorldNumber]) {
    NextArea();
    return;
  }
  Hidden1UpFlag += 1;
  NextArea();
  return;
}



// SMB:b315
// Signature: [] -> []

void NextArea(void)

{
  AreaNumber += 1;
  LoadAreaPointer();
  FetchNewGameTimerFlag += 1;
  HalfwayPage = ChgAreaMode();
  EventMusicQueue = 0x80;
  return;
}



// SMB:b329
// Signature: [] -> []

void PlayerMovementSubs(void)

{
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
  FUN_31d0(Player_State);
  return;
}



// SMB:b35a
// Signature: [] -> []

void OnGroundStateSub(void)

{
  GetPlayerAnimSpeed();
  if (Left_Right_Buttons != 0) {
    PlayerFacingDir = Left_Right_Buttons;
  }
  ImposeFriction(Left_Right_Buttons);
  Player_X_Scroll = MovePlayerHorizontally();
  return;
}



// SMB:b36d
// Signature: [] -> []

void FallingSub(void)

{
  VerticalForce = VerticalForceDown;
  LRAir();
  return;
}



// SMB:b376
// Signature: [] -> []

void JumpSwimSub(void)

{
  if ((PlayerSpriteVarData2[0] < 0x80) ||
     (((A_B_Buttons & 0x80 & PreviousA_B_Buttons) == 0 &&
      (DiffToHaltJump <= (byte)(JumpOrigin_Y_Position - PlayerOrSprObject_Y_Position[0]))))) {
    VerticalForce = VerticalForceDown;
  }
  if (SwimmingFlag == 0) {
    LRAir();
    return;
  }
  GetPlayerAnimSpeed();
  if (PlayerOrSprObject_Y_Position[0] < 0x14) {
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



// SMB:b3ac
// Signature: [] -> []

void LRAir(void)

{
  if (Left_Right_Buttons != 0) {
    ImposeFriction(Left_Right_Buttons);
  }
  Player_X_Scroll = MovePlayerHorizontally();
  if (GameEngineSubroutine == 0xb) {
    VerticalForce = 0x28;
  }
  MovePlayerVertically();
  return;
}



// SMB:b3cf
// Signature: [] -> []

void ClimbingSub(void)

{
  bool bVar1;
  bool bVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  
  bVar1 = CARRY1(PlayerOrSprObject_YMF_Dummy[0],PlayerOrSprObject_Y_MoveForce[0]);
  PlayerOrSprObject_YMF_Dummy[0] = PlayerOrSprObject_YMF_Dummy[0] + PlayerOrSprObject_Y_MoveForce[0]
  ;
  cVar5 = 0;
  if (0x7f < PlayerSpriteVarData2[0]) {
    cVar5 = -1;
  }
  bVar3 = PlayerSpriteVarData2[0] + PlayerOrSprObject_Y_Position[0] + bVar1;
  bVar2 = CARRY1(PlayerSpriteVarData2[0],PlayerOrSprObject_Y_Position[0]);
  PlayerOrSprObject_Y_Position[0] = bVar3;
  PlayerOrSprObject_Y_HighPos[0] =
       PlayerOrSprObject_Y_HighPos[0] + cVar5 + (bVar2 || bVar1 && bVar3 == 0);
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
      PlayerOrSprObject_PageLoc[0] =
           PlayerOrSprObject_PageLoc[0] + ClimbAdderHigh[bVar4] +
           CARRY1(PlayerOrSprObject_X_Position[0],ClimbAdderLow[bVar4]);
      PlayerFacingDir = Left_Right_Buttons ^ 3;
      PlayerOrSprObject_X_Position[0] = PlayerOrSprObject_X_Position[0] + ClimbAdderLow[bVar4];
    }
    return;
  }
  ClimbSideTimer = bVar3;
  return;
}



// SMB:b450
// Signature: [] -> []

void PlayerPhysicsSub(void)

{
  byte bVar1;
  byte bVar2;
  
  if (Player_State == 3) {
    bVar1 = 0;
    if (((Up_Down_Buttons & Player_CollisionBits) != 0) &&
       (bVar1 = 1, (Up_Down_Buttons & Player_CollisionBits & 8) == 0)) {
      bVar1 = 2;
    }
    PlayerOrSprObject_Y_MoveForce[0] = Climb_Y_MForceData[bVar1];
    PlayerAnimTimerSet = 8;
    PlayerSpriteVarData2[0] = Climb_Y_SpeedData[bVar1];
    if (Climb_Y_SpeedData[bVar1] < 0x80) {
      PlayerAnimTimerSet = 4;
    }
    return;
  }
  if ((((JumpspringAnimCtrl == 0) && ((A_B_Buttons & 0x80) != 0)) &&
      ((A_B_Buttons & 0x80 & PreviousA_B_Buttons) == 0)) &&
     ((Player_State == 0 ||
      ((SwimmingFlag != 0 && ((JumpSwimTimer != 0 || (PlayerSpriteVarData2[0] < 0x80)))))))) {
    JumpSwimTimer = 0x20;
    bVar1 = 0;
    PlayerOrSprObject_YMF_Dummy[0] = 0;
    JumpOrigin_Y_HighPos = PlayerOrSprObject_Y_HighPos[0];
    JumpOrigin_Y_Position = PlayerOrSprObject_Y_Position[0];
    Player_State = 1;
    if ((8 < Player_XSpeedAbsolute) &&
       (((bVar1 = 1, 0xf < Player_XSpeedAbsolute && (bVar1 = 2, 0x18 < Player_XSpeedAbsolute)) &&
        (bVar1 = 3, 0x1b < Player_XSpeedAbsolute)))) {
      bVar1 = 4;
    }
    DiffToHaltJump = 1;
    if ((SwimmingFlag != 0) && (bVar1 = 5, Cannon_Timer_Or_Whirlpool_Flag[0] != 0)) {
      bVar1 = 6;
    }
    VerticalForce = JumpMForceData[bVar1];
    VerticalForceDown = FallMForceData[bVar1];
    PlayerOrSprObject_Y_MoveForce[0] = InitMForceData[bVar1];
    PlayerSpriteVarData2[0] = PlayerYSpdData[bVar1];
    if (SwimmingFlag == 0) {
      Square1SoundQueue = 1;
      if (PlayerSize != 0) {
        Square1SoundQueue = 0x80;
      }
    }
    else {
      Square1SoundQueue = 4;
      if (PlayerOrSprObject_Y_Position[0] < 0x14) {
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
      if (RunningTimer != 0) goto GetXPhy;
    }
  }
  else {
    if (0x18 < Player_XSpeedAbsolute) goto GetXPhy;
    if (0x18 < Player_XSpeedAbsolute) goto ProcPRun;
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
    FrictionAdderHigh = FrictionAdderLow >> 7;
    FrictionAdderLow <<= 1;
  }
  return;
}



// SMB:b58f
// Signature: [] -> []

void GetPlayerAnimSpeed(void)

{
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
      }
      else if (Player_XSpeedAbsolute < 0xb) {
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



// SMB:b5cc
// Signature: [A] -> []

void ImposeFriction(byte param_1)

{
  byte bVar1;
  
  bVar1 = param_1 & Player_CollisionBits;
  if ((param_1 & Player_CollisionBits) == 0) {
    if (PlayerSpriteVarData1[0] == 0) {
      Player_XSpeedAbsolute = PlayerSpriteVarData1[0];
      return;
    }
    if (PlayerSpriteVarData1[0] < 0x80) goto RghtFrict;
    bVar1 = PlayerSpriteVarData1[0];
    if (PlayerSpriteVarData1[0] < 0x80) goto JoypFrict;
  }
  else {
JoypFrict:
    if ((bVar1 & 1) == 0) {
RghtFrict:
      bVar1 = Player_X_MoveForce - FrictionAdderLow;
      PlayerSpriteVarData1[0] =
           (PlayerSpriteVarData1[0] - FrictionAdderHigh) - (Player_X_MoveForce < FrictionAdderLow);
      Player_X_MoveForce = bVar1;
      if (0x7f < (byte)(PlayerSpriteVarData1[0] - MaximumLeftSpeed)) {
        PlayerSpriteVarData1[0] = MaximumLeftSpeed;
      }
      goto XSpdSign;
    }
  }
  bVar1 = Player_X_MoveForce + FrictionAdderLow;
  PlayerSpriteVarData1[0] =
       PlayerSpriteVarData1[0] + FrictionAdderHigh + CARRY1(Player_X_MoveForce,FrictionAdderLow);
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



// SMB:b624
// Signature: [] -> []

void ProcFireball_Bubble(void)

{
  byte bVar1;
  
  if (1 < PlayerStatus) {
    if (((((A_B_Buttons & 0x40) != 0) && ((A_B_Buttons & 0x40 & PreviousA_B_Buttons) == 0)) &&
        (Fireball_State[FireballCounter & 1] == 0)) &&
       (((PlayerOrSprObject_Y_HighPos[0] == 1 && (CrouchingFlag == 0)) && (Player_State != 3)))) {
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



// SMB:b689
// Signature: [X] -> []

void FireballObjCore(byte param_1)

{
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
      bVar2 = PlayerOrSprObject_X_Position[0] + 4 + bVar3;
      bVar1 = 0xfb < PlayerOrSprObject_X_Position[0];
      Fireball_X_Position[param_1] = bVar2;
      Fireball_PageLoc[param_1] = PlayerOrSprObject_PageLoc[0] + (bVar1 || bVar3 && bVar2 == 0);
      Fireball_Y_Position[param_1] = PlayerOrSprObject_Y_Position[0];
      Fireball_Y_HighPos[param_1] = 1;
      Fireball_X_Speed[param_1] = FireballXSpdData[(byte)(PlayerFacingDir - 1)];
      Fireball_Y_Speed[param_1] = 4;
      Fireball_BoundBoxCtrl[param_1] = 7;
      Fireball_State[param_1] = Fireball_State[param_1] - 1;
    }
    bVar2 = param_1 + 7;
    ImposeGravity(0,bVar2,0x50,in_r01,3);
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



// SMB:b6f9
// Signature: [X] -> []

void BubbleCheck(byte param_1)

{
  if (Bubble_Y_Position[param_1] != 0xf8) {
    MoveBubl(param_1,PseudoRandomBitReg[param_1 + 1] & 1);
    return;
  }
  if (AirBubbleTimer == 0) {
    SetupBubble(param_1,PseudoRandomBitReg[param_1 + 1] & 1);
    return;
  }
  return;
}



// SMB:b70b
// Signature: [X, r07] -> []

void SetupBubble(byte param_1,byte param_2)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  bool bVar4;
  
  bVar3 = 0;
  bVar4 = (bool)(PlayerFacingDir & 1);
  if (bVar4 != false) {
    bVar3 = 8;
  }
  bVar2 = bVar3 + PlayerOrSprObject_X_Position[0] + bVar4;
  bVar1 = CARRY1(bVar3,PlayerOrSprObject_X_Position[0]);
  Bubble_X_Position[param_1] = bVar2;
  Bubble_PageLoc[param_1] = PlayerOrSprObject_PageLoc[0] + (bVar1 || bVar4 && bVar2 == 0);
  Bubble_Y_Position[param_1] = PlayerOrSprObject_Y_Position[0] + 8;
  Bubble_Y_HighPos[param_1] = 1;
  AirBubbleTimer = BubbleTimerData[param_2];
  MoveBubl(param_1,param_2);
  return;
}



// SMB:b732
// Signature: [X, r07] -> []

void MoveBubl(byte param_1,byte param_2)

{
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



// SMB:b74f
// Signature: [] -> []

void RunGameTimer(void)

{
  byte bVar1;
  
  if ((((OperMode != 0) && (7 < GameEngineSubroutine)) && (GameEngineSubroutine != 0xb)) &&
     ((PlayerOrSprObject_Y_HighPos[0] < 2 && (GameTimerCtrlTimer == 0)))) {
    bVar1 = GameTimerDisplay[0] | GameTimerDisplay[1] | GameTimerDisplay[2];
    if (bVar1 != 0) {
      if ((GameTimerDisplay[0] == 1) && ((GameTimerDisplay[1] | GameTimerDisplay[2]) == 0)) {
        EventMusicQueue = 0x40;
      }
      GameTimerCtrlTimer = 0x18;
      DigitModifier[5] = 0xff;
      DigitsMathRoutine(0x23);
      PrintStatusBarNumbers(0xa4);
      return;
    }
    PlayerStatus = bVar1;
    ForceInjury(0);
    GameTimerExpiredFlag += 1;
  }
  return;
}



// SMB:b7a4
// Signature: [X] -> []

void WarpZoneObject(byte param_1)

{
  if ((ScrollLock != 0) && ((PlayerOrSprObject_Y_Position[0] & PlayerOrSprObject_Y_HighPos[0]) == 0)
     ) {
    WarpZoneControl += 1;
    ScrollLock = PlayerOrSprObject_Y_Position[0] & PlayerOrSprObject_Y_HighPos[0];
    EraseEnemyObject(param_1);
    return;
  }
  return;
}



// SMB:b7b8
// Signature: [] -> []

void ProcessWhirlpools(void)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  
  if ((AreaType == 0) && (Cannon_Timer_Or_Whirlpool_Flag[0] = AreaType, TimerControl == 0)) {
    bVar3 = 4;
    do {
      if (((Cannon_Or_Whirlpool_PageLoc[bVar3] != 0) &&
          ((byte)((PlayerOrSprObject_PageLoc[0] - Cannon_Or_Whirlpool_PageLoc[bVar3]) -
                 (PlayerOrSprObject_X_Position[0] < Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar3]
                 )) < 0x80)) &&
         ((byte)(((Cannon_Or_Whirlpool_PageLoc[bVar3] +
                  CARRY1(Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar3],
                         Cannon_Y_Position_Or_Whirlpool_Length[bVar3])) -
                 PlayerOrSprObject_PageLoc[0]) -
                ((byte)(Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar3] +
                       Cannon_Y_Position_Or_Whirlpool_Length[bVar3]) <
                PlayerOrSprObject_X_Position[0])) < 0x80)) {
        bVar1 = Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar3] +
                (Cannon_Y_Position_Or_Whirlpool_Length[bVar3] >> 1);
        if ((FrameCounter & 1) != 0) {
          if ((byte)(((Cannon_Or_Whirlpool_PageLoc[bVar3] +
                      CARRY1(Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar3],
                             Cannon_Y_Position_Or_Whirlpool_Length[bVar3] >> 1)) -
                     PlayerOrSprObject_PageLoc[0]) - (bVar1 < PlayerOrSprObject_X_Position[0])) <
              0x80) {
            if ((Player_CollisionBits & 1) == 0) goto WhPull;
            cVar2 = 0xfe < PlayerOrSprObject_X_Position[0];
            PlayerOrSprObject_X_Position[0] = PlayerOrSprObject_X_Position[0] + 1;
          }
          else {
            cVar2 = -(PlayerOrSprObject_X_Position[0] == 0);
            PlayerOrSprObject_X_Position[0] = PlayerOrSprObject_X_Position[0] - 1;
          }
          PlayerOrSprObject_PageLoc[0] += cVar2;
        }
WhPull:
        Cannon_Timer_Or_Whirlpool_Flag[0] = 1;
        ImposeGravity(0,0,0x10,bVar1,1);
        return;
      }
      bVar3 -= 1;
    } while (bVar3 < 0x80);
  }
  return;
}



// SMB:b855
// Signature: [] -> []

void FlagpoleRoutine(void)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  struct_xyi sVar4;
  struct_axr00 sVar5;
  
  bVar2 = 5;
  ObjectOffset = 5;
  if (Enemy_ID[5] == 0x30) {
    if ((GameEngineSubroutine == 4) && (Player_State == 3)) {
      if ((0xa9 < Enemy_Y_Position[5]) || (bVar3 = 0xa1 < PlayerOrSprObject_Y_Position[0], bVar3)) {
        DigitModifier[FlagpoleScoreDigits[FlagpoleScore]] = FlagpoleScoreMods[FlagpoleScore];
        bVar2 = AddToScore();
        GameEngineSubroutine = 5;
      }
      else {
        bVar1 = (BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[5] - 1) + bVar3;
        Enemy_Y_Position[5] =
             Enemy_Y_Position[5] + 1 +
             (BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[5] != 0 ||
             bVar3 && bVar1 == 0);
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



// SMB:b8ba
// Signature: [X] -> [X]

byte JumpspringHandler(byte param_1)

{
  byte bVar1;
  byte bVar2;
  struct_xyi sVar3;
  struct_axr00 sVar4;
  
  sVar3 = GetEnemyOffscreenBits(param_1);
  bVar1 = sVar3.x;
  if ((TimerControl == 0) && (JumpspringAnimCtrl != 0)) {
    bVar2 = JumpspringAnimCtrl - 1;
    if ((bVar2 & 2) == 0) {
      PlayerOrSprObject_Y_Position[0] += 2;
    }
    else {
      PlayerOrSprObject_Y_Position[0] -= 2;
    }
    Enemy_Y_Position[bVar1] = PlayerSpriteVarData1[bVar1 + 1] + Jumpspring_Y_PosData[bVar2];
    if (((bVar2 != 0) && ((A_B_Buttons & 0x80) != 0)) &&
       ((A_B_Buttons & 0x80 & PreviousA_B_Buttons) == 0)) {
      JumpspringForce = 0xf4;
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



// SMB:b91e
// Signature: [X, Y] -> []

void Setup_Vine(byte param_1,byte param_2)

{
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



// SMB:b94b
// Signature: [X] -> [X]

byte VineObjectHandler(byte param_1)

{
  byte bVar1;
  short sVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  struct_axr00 sVar6;
  struct_azr02r04r06r07 sVar7;
  
  if (param_1 == 5) {
    if ((VineHeight != VineHeightData[(byte)(VineFlagOffset - 1)]) &&
       (bVar5 = (bool)(FrameCounter >> 1 & 1), bVar5 != false)) {
      Enemy_Y_Position[5] = (Enemy_Y_Position[5] - 1) - !bVar5;
      VineHeight += 1;
    }
    if (7 < VineHeight) {
      sVar6 = RelativeEnemyPosition(5);
      GetEnemyOffscreenBits(sVar6.x);
      bVar3 = 0;
      do {
        bVar4 = bVar3;
        DrawVine(bVar4);
        bVar3 = bVar4 + 1;
      } while ((byte)(bVar4 + 1) != VineFlagOffset);
      bVar3 = VineFlagOffset;
      bVar1 = VineHeight;
      if ((Enemy_OffscreenBits & 0xc) != 0) {
        do {
          bVar3 = EraseEnemyObject(VineObjOffset[bVar4]);
          bVar4 -= 1;
          bVar1 = bVar3;
        } while (bVar4 < 0x80);
      }
      VineHeight = bVar1;
      VineFlagOffset = bVar3;
      if (0x1f < VineHeight) {
        sVar7 = BlockBufferCollision(1,6,0x1b);
        bVar3 = sVar7.r02;
        sVar2 = (short)((uint6)sVar7 >> 0x20);
        if ((bVar3 < 0xd0) && (RAM(sVar2 + (ushort)bVar3) == 0)) {
          RAM(sVar2 + (ushort)bVar3) = 0x26;
        }
      }
    }
  }
  return ObjectOffset;
}



// SMB:b9bc
// Signature: [] -> []

void ProcessCannons(void)

{
  byte bVar1;
  byte bVar2;
  struct_xyi sVar3;
  
  if (AreaType != 0) {
    bVar2 = 2;
    do {
      ObjectOffset = bVar2;
      if (Enemy_Flag[bVar2] == 0) {
        bVar1 = PseudoRandomBitReg[bVar2 + 1] & CannonBitmasks[SecondaryHardMode];
        if ((5 < bVar1) || (Cannon_Or_Whirlpool_PageLoc[bVar1] == 0)) goto Chk_BB;
        if (Cannon_Timer_Or_Whirlpool_Flag[bVar1] != 0) {
          Cannon_Timer_Or_Whirlpool_Flag[bVar1] =
               Cannon_Timer_Or_Whirlpool_Flag[bVar1] - (5 >= bVar1);
          goto Chk_BB;
        }
        if (TimerControl != 0) goto Chk_BB;
        Cannon_Timer_Or_Whirlpool_Flag[bVar1] = 0xe;
        Enemy_PageLoc[bVar2] = Cannon_Or_Whirlpool_PageLoc[bVar1];
        Enemy_X_Position[bVar2] = Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar1];
        Enemy_Y_Position[bVar2] = Cannon_Y_Position_Or_Whirlpool_Length[bVar1] - 8;
        Enemy_Y_HighPos[bVar2] = 1;
        Enemy_Flag[bVar2] = 1;
        Enemy_State[bVar2] = 0;
        Enemy_BoundBoxCtrl[bVar2] = 9;
        Enemy_ID[bVar2] = 0x33;
      }
      else {
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



// SMB:ba33
// Signature: [X] -> [X]

byte BulletBillHandler(byte param_1)

{
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
      PlayerSpriteVarData1[param_1 + 1] = BulletBillXSpdData[(byte)(bVar1 - 1)];
      if ((byte)(sVar2.r00 + 0x28 + sVar2.c) < 0x50) goto KillBB;
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



// SMB:ba94
// Signature: [] -> [X, C]

struct_xci SpawnHammerObj(void)

{
  byte bVar1;
  byte bVar2;
  
  
  bVar1 = ObjectOffset;
  bVar2 = PseudoRandomBitReg[1] & 7;
  if (bVar2 == 0) {
    bVar2 = PseudoRandomBitReg[1] & 8;
  }
  if ((Misc_State[bVar2] == 0) && (Enemy_Flag[HammerEnemyOfsData[bVar2]] == 0)) {
    HammerEnemyOffset[bVar2] = ObjectOffset;
    Misc_State[bVar2] = 0x90;
    Misc_BoundBoxCtrl[bVar2] = 7;
    return (struct_xci)CONCAT12(0,CONCAT11(1,bVar1));
  }
  return (struct_xci)CONCAT12(0,(ushort)ObjectOffset);
}



// SMB:bac3
// Signature: [X] -> [X]

byte ProcHammerObj(byte param_1)

{
  byte bVar1;
  byte bVar2;
  
  if (TimerControl == 0) {
    bVar2 = HammerEnemyOffset[param_1];
    if ((Misc_State[param_1] & 0x7f) == 2) {
      Misc_Y_Speed[param_1] = 0xfe;
      Enemy_State[bVar2] = Enemy_State[bVar2] & 0xf7;
      param_1 = ObjectOffset;
      Misc_X_Speed[ObjectOffset] = HammerXSpdData[(byte)(Enemy_MovingDir[bVar2] - 1)];
    }
    else if ((Misc_State[param_1] & 0x7f) < 2) {
      bVar2 = param_1 + 0xd;
      ImposeGravity(0,bVar2,0x10,0xf,4);
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



// SMB:bb38
// Signature: [X, C] -> []

void CoinBlock(byte param_1,bool param_2)

{
  byte bVar1;
  struct_yci sVar2;
  
  sVar2 = FindEmptyMiscSlot(param_2);
  bVar1 = sVar2.y;
  Misc_PageLoc[bVar1] = Block_PageLoc[param_1];
  Misc_X_Position[bVar1] = Block_X_Position[param_1] | 5;
  Misc_Y_Position[bVar1] = (Block_Y_Position[param_1] - 0x10) - !sVar2.c;
  JCoinC(param_1,bVar1);
  return;
}



// SMB:bb51
// Signature: [X, r02, r06] -> [X]

byte SetupJumpCoin(byte param_1,byte param_2,byte param_3)

{
  byte bVar1;
  bool in_C = false;
  struct_yci sVar2;
  
  sVar2 = FindEmptyMiscSlot(in_C);
  bVar1 = sVar2.y;
  Misc_PageLoc[bVar1] = Block_PageLoc2[param_1];
  Misc_X_Position[bVar1] = param_3 << 4 | 5;
  Misc_Y_Position[bVar1] = (param_2 + 0x20) - ((char)(param_3 << 3) >> 7);
  bVar1 = JCoinC(param_1,bVar1);
  return bVar1;
}



// SMB:bb6c
// Signature: [X, Y] -> [X]

byte JCoinC(byte param_1,byte param_2)

{
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



// SMB:bb84
// Signature: [C] -> [Y, C]

struct_yci FindEmptyMiscSlot(bool param_1)

{
  
  
  JumpCoinMiscOffset = 8;
  do {
    if (Misc_State[JumpCoinMiscOffset] == 0) goto UseMiscS;
    JumpCoinMiscOffset -= 1;
    param_1 = 4 < JumpCoinMiscOffset;
  } while (JumpCoinMiscOffset != 5);
  JumpCoinMiscOffset = 8;
UseMiscS:
  return (struct_yci)CONCAT12(0,CONCAT11(param_1,JumpCoinMiscOffset));
}



// SMB:bb96
// Signature: [] -> []

void MiscObjectsCore(void)

{
  bool bVar1;
  byte bVar2;
  
  bVar2 = 8;
  do {
    ObjectOffset = bVar2;
    if (Misc_State[bVar2] != 0) {
      if ((char)Misc_State[bVar2] < 0) {
        bVar2 = ProcHammerObj(bVar2);
      }
      else {
        if (Misc_State[bVar2] == 1) {
          ImposeGravity(0,bVar2 + 0xd,0x50,3,6);
          bVar2 = ObjectOffset;
          if (Misc_Y_Speed[ObjectOffset] == 5) {
            Misc_State[ObjectOffset] = Misc_State[ObjectOffset] + 1;
          }
        }
        else {
          Misc_State[bVar2] = Misc_State[bVar2] + 1;
          bVar1 = CARRY1(Misc_X_Position[bVar2],ScrollAmount);
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
  } while( true );
}



// SMB:bbfe
// Signature: [] -> [X]

byte GiveOneCoin(void)

{
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

byte AddToScore(void)

{
  byte bVar1;
  
  DigitsMathRoutine(ScoreOffsets[CurrentPlayer]);
  bVar1 = GetSBNybbles();
  return bVar1;
}



// SMB:bc30
// Signature: [] -> [X]

byte GetSBNybbles(void)

{
  byte bVar1;
  
  bVar1 = UpdateNumber(StatusBarNybbles[CurrentPlayer]);
  return bVar1;
}



// SMB:bc36
// Signature: [A] -> [X]

byte UpdateNumber(byte param_1)

{
  PrintStatusBarNumbers(param_1);
  if (Sprite_Data[VRAM_Buffer1_Offset + 0xfb] == 0) {
    Sprite_Data[VRAM_Buffer1_Offset + 0xfb] = 0x24;
  }
  return ObjectOffset;
}



// SMB:bc49
// Signature: [X] -> []

void SetupPowerUp(byte param_1)

{
  Enemy_ID[5] = 0x2e;
  Enemy_PageLoc[5] = Block_PageLoc[param_1];
  Enemy_X_Position[5] = Block_X_Position[param_1];
  Enemy_Y_HighPos[5] = 1;
  Enemy_Y_Position[5] = Block_Y_Position[param_1] - 8;
  PwrUpJmp();
  return;
}



// SMB:bc60
// Signature: [] -> []

void PwrUpJmp(void)

{
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



// SMB:bc85
// Signature: [] -> [X]

byte PowerUpObjHandler(void)

{
  byte bVar1;
  bool bVar2;
  struct_axr00 sVar3;
  struct_xyi sVar4;
  
  bVar1 = 5;
  ObjectOffset = 5;
  if (Enemy_State[5] != 0) {
    if ((char)Enemy_State[5] < 0) {
      if (TimerControl == 0) {
        if ((PowerUpType == 0) || (PowerUpType == 3)) {
          bVar1 = MoveNormalEnemy(5);
          bVar1 = EnemyToBGCollisionDet(bVar1);
        }
        else if (PowerUpType == 2) {
          bVar1 = MoveJumpingEnemy(5);
          bVar1 = EnemyJump(bVar1);
        }
      }
    }
    else {
      if ((FrameCounter & 3) == 0) {
        Enemy_Y_Position[5] -= 1;
        bVar2 = 0x10 < Enemy_State[5];
        Enemy_State[5] = Enemy_State[5] + 1;
        if (bVar2) {
          PlayerSpriteVarData1[6] = 0x10;
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



// SMB:bced
// Signature: [A, r02, r06, r07] -> []

void PlayerHeadCollision(byte param_1,byte param_2,byte param_3,byte param_4)

{
  short sVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  struct_yci sVar5;
  byte bStack0000;
  
  bVar4 = SprDataOffset_Ctrl;
  sVar1 = CONCAT11(param_4,param_3);
  bVar2 = 0x11;
  if (PlayerSize == 0) {
    bVar2 = 0x12;
  }
  Block_State[SprDataOffset_Ctrl] = bVar2;
  bStack0000 = param_1;
  DestroyBlockMetatile(bVar4,param_2,param_3);
  bVar2 = SprDataOffset_Ctrl;
  Block_Orig_YPos[SprDataOffset_Ctrl] = param_2;
  Block_BBuf_Low[bVar2] = (byte)sVar1;
  bVar4 = RAM(sVar1 + (ushort)param_2);
  sVar5 = BlockBumpedChk(bVar4);
  bVar3 = bVar4;
  if (PlayerSize == 0) {
    bVar3 = PlayerSize;
  }
  if (sVar5.c != false) {
    Block_State[bVar2] = 0x11;
    if ((bVar4 == 0x58) || (bVar3 = 0xc4, bVar4 == 0x5d)) {
      if (BrickCoinTimerFlag == 0) {
        BrickCoinTimer = 0xb;
        BrickCoinTimerFlag = 1;
      }
      bVar3 = bVar4;
      if (BrickCoinTimer == 0) {
        bVar3 = 0xc4;
      }
    }
  }
  Block_Metatile[bVar2] = bVar3;
  InitBlock_XY_Pos(bVar2);
  RAM(sVar1 + (ushort)param_2) = 0x23;
  BlockBounceTimer = 0x10;
  bVar4 = 0;
  if ((CrouchingFlag != 0) || (PlayerSize != 0)) {
    bVar4 = 1;
  }
  Block_Y_Position[bVar2] = PlayerOrSprObject_Y_Position[0] + BlockYPosAdderData[bVar4] & 0xf0;
  bVar4 = (byte)((ushort)sVar1 >> 8);
  if (Block_State[bVar2] == 0x11) {
    BumpBlock(param_2,bStack0000,(byte)sVar1,bVar4);
  }
  else {
    BrickShatter(param_2,(byte)sVar1,bVar4);
  }
  SprDataOffset_Ctrl = SprDataOffset_Ctrl ^ 1;
  return;
}



// SMB:bd84
// Signature: [X] -> []

void InitBlock_XY_Pos(byte param_1)

{
  bool bVar1;
  byte bVar2;
  
  bVar1 = 0xf7 < PlayerOrSprObject_X_Position[0];
  Block_X_Position[param_1] = PlayerOrSprObject_X_Position[0] + 8 & 0xf0;
  bVar2 = PlayerOrSprObject_PageLoc[0] + bVar1;
  Block_PageLoc[param_1] = bVar2;
  Block_PageLoc2[param_1] = bVar2;
  Block_Y_HighPos[param_1] = PlayerOrSprObject_Y_HighPos[0];
  return;
}



// SMB:bd9b
// Signature: [r02, r05, r06, r07] -> []

void BumpBlock(byte param_1,byte param_2,byte param_3,byte param_4)

{
  byte bVar1;
  byte bVar2;
  struct_yci sVar3;
  struct_xr05i sVar4;
  
  sVar4 = CheckTopOfBlock(param_1,param_2,param_3,param_4);
  bVar2 = sVar4.x;
  Square1SoundQueue = 2;
  Block_X_Speed[bVar2] = 0;
  Block_Y_MoveForce[bVar2] = 0;
  PlayerSpriteVarData2[0] = 0;
  Block_Y_Speed[bVar2] = 0xfe;
  sVar3 = BlockBumpedChk(sVar4.r05);
  bVar1 = sVar3.y;
  if (sVar3.c != false) {
    if (bVar1 >= 9) {
      bVar1 = (bVar1 - 5) - (bVar1 < 9);
    }
    FUN_31e4(bVar1,bVar2);
    return;
  }
  return;
}



// SMB:bdd2
// Signature: [X] -> []

void MushFlowerBlock(byte param_1)

{
  PowerUpType = 0;
  SetupPowerUp(param_1);
  return;
}



// SMB:bdd5
// Signature: [X] -> []

void StarBlock(byte param_1)

{
  PowerUpType = 2;
  SetupPowerUp(param_1);
  return;
}



// SMB:bdd8
// Signature: [X] -> []

void ExtraLifeMushBlock(byte param_1)

{
  PowerUpType = 3;
  SetupPowerUp(param_1);
  return;
}



// SMB:bddf
// Signature: [] -> []

void VineBlock(void)

{
  Setup_Vine(5,SprDataOffset_Ctrl);
  return;
}



// SMB:bdf6
// Signature: [A] -> [Y, C]

struct_yci BlockBumpedChk(byte param_1)

{
  byte bVar1;
  
  bool bVar2;
  
  bVar1 = 0xd;
  do {
    bVar2 = BrickQBlockMetatiles[bVar1] <= param_1;
    if (param_1 == BrickQBlockMetatiles[bVar1]) goto MatchBump;
    bVar1 -= 1;
  } while (bVar1 < 0x80);
  bVar2 = false;
MatchBump:
  return (struct_yci)CONCAT12(0,CONCAT11(bVar2,bVar1));
}



// SMB:be02
// Signature: [r02, r06, r07] -> []

void BrickShatter(byte param_1,byte param_2,byte param_3)

{
  byte in_r05 = 0;
  struct_xr05i sVar1;
  
  sVar1 = CheckTopOfBlock(param_1,in_r05,param_2,param_3);
  Block_RepFlag[sVar1.x] = 1;
  NoiseSoundQueue = 1;
  SpawnBrickChunks(sVar1.x);
  PlayerSpriteVarData2[0] = 0xfe;
  DigitModifier[5] = 5;
  AddToScore();
  return;
}



// SMB:be1f
// Signature: [r02, r05, r06, r07] -> [X, r05]

struct_xr05i CheckTopOfBlock(byte param_1,byte param_2,byte param_3,byte param_4)

{
  byte bVar1;
  short sVar2;
  byte bVar3;
  
  
  sVar2 = CONCAT11(param_4,param_3);
  bVar3 = SprDataOffset_Ctrl;
  if ((param_1 != 0) && (bVar1 = param_1 - 0x10, RAM(sVar2 + (ushort)bVar1) == 0xc2)) {
    RAM(sVar2 + (ushort)bVar1) = 0;
    param_2 = RemoveCoin_Axe(bVar1,param_3);
    bVar3 = SetupJumpCoin(SprDataOffset_Ctrl,bVar1,(byte)sVar2);
  }
  return (struct_xr05i)CONCAT12(0,CONCAT11(param_2,bVar3));
}



// SMB:be41
// Signature: [X] -> []

void SpawnBrickChunks(byte param_1)

{
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



// SMB:be70
// Signature: [X] -> [X]

byte BlockObjectsCore(byte param_1)

{
  byte bVar1;
  byte bStack0000;
  
  bStack0000 = Block_State[param_1];
  if (bStack0000 == 0) goto UpdSte;
  bStack0000 &= 0xf;
  bVar1 = param_1 + 9;
  if (bStack0000 == 1) {
    ImposeGravityBlock(bVar1);
    bVar1 = RelativeBlockPosition(ObjectOffset);
    bVar1 = GetBlockOffscreenBits(bVar1);
    param_1 = DrawBlock(bVar1);
    if (4 < (Block_Y_Position[param_1] & 0xf)) goto UpdSte;
    Block_RepFlag[param_1] = 1;
  }
  else {
    ImposeGravityBlock(bVar1);
    MoveObjectHorizontally(bVar1);
    bVar1 += 2;
    ImposeGravityBlock(bVar1);
    MoveObjectHorizontally(bVar1);
    bVar1 = RelativeBlockPosition(ObjectOffset);
    param_1 = GetBlockOffscreenBits(bVar1);
    DrawBrickChunks(param_1);
    if (Block_Y_HighPos[param_1] == 0) goto UpdSte;
    if (0xf0 < Block_Y_Position[param_1 + 2]) {
      Block_Y_Position[param_1 + 2] = 0xf0;
    }
    if (Block_Y_Position[param_1] < 0xf0) goto UpdSte;
  }
  bStack0000 = 0;
UpdSte:
  Block_State[param_1] = bStack0000;
  return param_1;
}



// SMB:bed4
// Signature: [] -> []

void BlockObjMT_Updater(void)

{
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
      RAM(CONCAT11(5,bVar1) + (ushort)bVar2) = bVar3;
      ReplaceBlockMetatile(bVar3,bVar4,bVar2,bVar1);
      Block_RepFlag[bVar4] = 0;
    }
    bVar4 -= 1;
  } while (bVar4 < 0x80);
  return;
}



// SMB:bf02
// Signature: [X] -> [A, X]

struct_axi MoveEnemyHorizontally(byte param_1)

{
  byte bVar1;
  
  
  bVar1 = MoveObjectHorizontally(param_1 + 1);
  return (struct_axi)CONCAT12(0,CONCAT11(ObjectOffset,bVar1));
}



// SMB:bf09
// Signature: [] -> [A]

byte MovePlayerHorizontally(void)

{
  byte bVar1;
  
  if (JumpspringAnimCtrl == 0) {
    bVar1 = MoveObjectHorizontally(0);
    return bVar1;
  }
  return JumpspringAnimCtrl;
}



// SMB:bf0f
// Signature: [X] -> [A]

byte MoveObjectHorizontally(byte param_1)

{
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
  bVar2 = CARRY1(SprObject_X_MoveForce[param_1],PlayerSpriteVarData1[param_1] * 0x10);
  SprObject_X_MoveForce[param_1] =
       SprObject_X_MoveForce[param_1] + PlayerSpriteVarData1[param_1] * 0x10;
  bVar1 = PlayerOrSprObject_X_Position[param_1];
  bVar4 = bVar1 + bVar3 + bVar2;
  PlayerOrSprObject_X_Position[param_1] = bVar4;
  PlayerOrSprObject_PageLoc[param_1] =
       PlayerOrSprObject_PageLoc[param_1] + cVar5 + (CARRY1(bVar1,bVar3) || bVar2 && bVar4 == 0);
  return bVar2 + bVar3;
}



// SMB:bf4d
// Signature: [] -> []

void MovePlayerVertically(void)

{
  if ((TimerControl == 0) && (JumpspringAnimCtrl != 0)) {
    return;
  }
  ImposeGravitySprObj(4,0,VerticalForce);
  return;
}



// SMB:bf63
// Signature: [X] -> [X]

byte MoveD_EnemyVertically(byte param_1)

{
  byte bVar1;
  
  if (Enemy_State[param_1] == 5) {
    bVar1 = MoveFallingPlatform(param_1);
    return bVar1;
  }
  bVar1 = SetXMoveAmt(3,param_1,0x3d);
  return bVar1;
}



// SMB:bf6b
// Signature: [X] -> [X]

byte MoveFallingPlatform(byte param_1)

{
  byte bVar1;
  
  bVar1 = SetXMoveAmt(3,param_1,0x20);
  return bVar1;
}



// SMB:bf70
// Signature: [X] -> [X]

byte MoveRedPTroopaDown(byte param_1)

{
  ImposeGravity(0,param_1 + 1,3,6,2);
  return ObjectOffset;
}



// SMB:bf75
// Signature: [X] -> [X]

byte MoveRedPTroopaUp(byte param_1)

{
  ImposeGravity(1,param_1 + 1,3,6,2);
  return ObjectOffset;
}



// SMB:bf88
// Signature: [X] -> [X]

byte MoveDropPlatform(byte param_1)

{
  byte bVar1;
  
  bVar1 = SetXMoveAmt(2,param_1,0x7f);
  return bVar1;
}



// SMB:bf8c
// Signature: [X] -> [X]

byte MoveEnemySlowVert(byte param_1)

{
  byte bVar1;
  
  bVar1 = SetXMoveAmt(2,param_1,0xf);
  return bVar1;
}



// SMB:bf92
// Signature: [X] -> [X]

byte MoveJ_EnemyVertically(byte param_1)

{
  byte bVar1;
  
  bVar1 = SetXMoveAmt(3,param_1,0x1c);
  return bVar1;
}



// SMB:bf96
// Signature: [A, X, Y] -> [X]

byte SetXMoveAmt(byte param_1,byte param_2,byte param_3)

{
  ImposeGravitySprObj(param_1,param_2 + 1,param_3);
  return ObjectOffset;
}



// SMB:bfa4
// Signature: [X] -> []

void ImposeGravityBlock(byte param_1)

{
  byte in_r01 = 0;
  
  ImposeGravity(0,param_1,0x50,in_r01,MaxSpdBlockData[1]);
  return;
}



// SMB:bfad
// Signature: [A, X, r00] -> []

void ImposeGravitySprObj(byte param_1,byte param_2,byte param_3)

{
  byte in_r01 = 0;
  
  ImposeGravity(0,param_2,param_3,in_r01,param_1);
  return;
}



// SMB:bfb4
// Signature: [X] -> [X]

byte MovePlatformDown(byte param_1)

{
  byte bVar1;
  undefined uStack0000;
  
  uStack0000 = 0;
  bVar1 = 5;
  if (Enemy_ID[param_1] == 0x29) {
    bVar1 = 9;
  }
  ImposeGravity(0,param_1 + 1,bVar1,10,3);
  return ObjectOffset;
}



// SMB:bfb7
// Signature: [X] -> [X]

byte MovePlatformUp(byte param_1)

{
  byte bVar1;
  undefined uStack0000;
  
  uStack0000 = 1;
  bVar1 = 5;
  if (Enemy_ID[param_1] == 0x29) {
    bVar1 = 9;
  }
  ImposeGravity(1,param_1 + 1,bVar1,10,3);
  return ObjectOffset;
}



// SMB:bfd7
// Signature: [A, X, r00, r01, r02] -> []

void ImposeGravity(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  byte bVar5;
  
  bVar1 = CARRY1(PlayerOrSprObject_YMF_Dummy[param_2],PlayerOrSprObject_Y_MoveForce[param_2]);
  PlayerOrSprObject_YMF_Dummy[param_2] =
       PlayerOrSprObject_YMF_Dummy[param_2] + PlayerOrSprObject_Y_MoveForce[param_2];
  cVar4 = 0;
  bVar3 = PlayerSpriteVarData2[param_2];
  if (0x7f < bVar3) {
    cVar4 = -1;
  }
  bVar5 = PlayerOrSprObject_Y_Position[param_2];
  bVar2 = bVar3 + bVar5 + bVar1;
  PlayerOrSprObject_Y_Position[param_2] = bVar2;
  PlayerOrSprObject_Y_HighPos[param_2] =
       PlayerOrSprObject_Y_HighPos[param_2] + cVar4 + (CARRY1(bVar3,bVar5) || bVar1 && bVar2 == 0);
  bVar3 = PlayerOrSprObject_Y_MoveForce[param_2];
  PlayerOrSprObject_Y_MoveForce[param_2] = bVar3 + param_3;
  bVar3 = PlayerSpriteVarData2[param_2] + CARRY1(bVar3,param_3);
  PlayerSpriteVarData2[param_2] = bVar3;
  if (((byte)(bVar3 - param_5) < 0x80) && (0x7f < PlayerOrSprObject_Y_MoveForce[param_2])) {
    PlayerSpriteVarData2[param_2] = param_5;
    PlayerOrSprObject_Y_MoveForce[param_2] = 0;
  }
  if (param_1 != 0) {
    bVar5 = (param_5 ^ 0xff) + 1;
    bVar3 = PlayerOrSprObject_Y_MoveForce[param_2];
    PlayerOrSprObject_Y_MoveForce[param_2] = bVar3 - param_4;
    bVar3 = PlayerSpriteVarData2[param_2] - (bVar3 < param_4);
    PlayerSpriteVarData2[param_2] = bVar3;
    if ((0x7f < (byte)(bVar3 - bVar5)) && (PlayerOrSprObject_Y_MoveForce[param_2] < 0x80)) {
      PlayerSpriteVarData2[param_2] = bVar5;
      PlayerOrSprObject_Y_MoveForce[param_2] = 0xff;
    }
  }
  return;
}



// SMB:c047
// Signature: [X] -> [X]

byte EnemiesAndLoopsCore(byte param_1)

{
  byte bVar1;
  byte bStack0000;
  
  bStack0000 = Enemy_Flag[param_1];
  if ((bool)(bStack0000 >> 7)) {
    if (Enemy_Flag[bStack0000 & 0xf] == 0) {
      Enemy_Flag[param_1] = 0;
    }
  }
  else {
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



// SMB:c08c
// Signature: [Y] -> []

void ExecGameLoopback(byte param_1)

{
  PlayerOrSprObject_PageLoc[0] = PlayerOrSprObject_PageLoc[0] - 4;
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



// SMB:c0cc
// Signature: [X] -> [X]

byte ProcLoopCommand(byte param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  bool bVar6;
  
  do {
    if ((LoopCommand != 0) && (CurrentColumnPos == 0)) {
      bVar4 = 0xb;
      do {
        bVar4 -= 1;
        if (0x7f < bVar4) goto ChkEnemyFrenzy;
      } while ((WorldNumber != LoopCmdWorldNumber[bVar4]) ||
              (CurrentPageLoc != LoopCmdPageNumber[bVar4]));
      if (PlayerOrSprObject_Y_Position[0] != LoopCmdYPosition[bVar4]) goto WrongChk;
      if (Player_State != 0) goto WrongChk;
      if (WorldNumber == 6) {
        MultiLoopCorrectCntr += 1;
        do {
          MultiLoopPassCntr += 1;
          if (MultiLoopPassCntr != 3) goto InitLCmd;
          if (MultiLoopCorrectCntr == 3) goto InitMLp;
          if (MultiLoopCorrectCntr != 3) break;
WrongChk: 0;
        } while (WorldNumber == 6);
        ExecGameLoopback(bVar4);
        param_1 = KillAllEnemies();
      }
InitMLp:
      MultiLoopPassCntr = 0;
      MultiLoopCorrectCntr = 0;
InitLCmd:
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
    if (EnemyData[EnemyDataOffset] == 0xff) goto CheckFrenzyBuffer;
    if ((((EnemyData[EnemyDataOffset] & 0xf) != 0xe) && (4 < param_1)) &&
       ((EnemyData[(byte)(EnemyDataOffset + 1)] & 0x3f) != 0x2e)) {
      return param_1;
    }
    bVar1 = ScreenRight_X_Pos + 0x30;
    bVar2 = ScreenRight_PageLoc + (0xcf < ScreenRight_X_Pos);
    bVar5 = EnemyDataOffset + 1;
    if (((char)EnemyData[bVar5] < 0) && (EnemyObjectPageSel == 0)) {
      EnemyObjectPageSel = 1;
      EnemyObjectPageLoc += 1;
    }
    if (((EnemyData[EnemyDataOffset] & 0xf) != 0xf) || (EnemyObjectPageSel != 0)) break;
    EnemyObjectPageLoc = EnemyData[bVar5] & 0x3f;
    EnemyDataOffset += 2;
    EnemyObjectPageSel = 1;
  } while( true );
  Enemy_PageLoc[param_1] = EnemyObjectPageLoc;
  bVar3 = EnemyData[bVar4] & 0xf0;
  Enemy_X_Position[param_1] = bVar3;
  if (ScreenRight_X_Pos <= bVar3 && ScreenRight_PageLoc <= Enemy_PageLoc[param_1] ||
      ScreenRight_X_Pos > bVar3 && ScreenRight_PageLoc < Enemy_PageLoc[param_1]) {
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
      if (((EnemyData[bVar5] & 0x40) == 0) || (SecondaryHardMode != 0)) {
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
      }
      goto Inc2B;
    }
  }
  else if ((EnemyData[bVar4] & 0xf) != 0xe) {
    bVar4 = CheckThreeBytes();
    return bVar4;
  }
  if (EnemyData[(byte)(bVar4 + 2)] >> 5 == WorldNumber) {
    AreaPointer = EnemyData[(byte)(bVar4 + 1)];
    EntrancePage = EnemyData[(byte)(bVar4 + 2)] & 0x1f;
  }
  EnemyDataOffset += 1;
Inc2B:
  EnemyDataOffset = EnemyDataOffset + 2;
  EnemyObjectPageSel = 0;
  return ObjectOffset;
}



// SMB:c226
// Signature: [X] -> []

void InitEnemyObject(byte param_1)

{
  Enemy_State[param_1] = 0;
  CheckpointEnemyID(param_1);
  return;
}



// SMB:c250
// Signature: [] -> [X]

byte CheckThreeBytes(void)

{
  if ((EnemyData[EnemyDataOffset] & 0xf) == 0xe) {
    EnemyDataOffset += 1;
  }
  EnemyDataOffset = EnemyDataOffset + 2;
  EnemyObjectPageSel = 0;
  return ObjectOffset;
}



// SMB:c26c
// Signature: [X] -> []

void CheckpointEnemyID(byte param_1)

{
  byte bVar1;
  
  bVar1 = Enemy_ID[param_1];
  if (0x14 >= bVar1) {
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 8 + (0x14 < bVar1);
    EnemyOffscrBitsMasked[param_1] = 1;
  }
  FUN_320c(bVar1,param_1);
  return;
}



// SMB:c2f0
// Signature: [] -> []

void NoInitCode(void)

{
  return;
}



// SMB:c2f1
// Signature: [X] -> []

void InitGoomba(byte param_1)

{
  InitNormalEnemy(param_1);
  SmallBBox(param_1);
  return;
}



// SMB:c2f7
// Signature: [X] -> []

void InitPodoboo(byte param_1)

{
  Enemy_Y_HighPos[param_1] = 2;
  Enemy_Y_Position[param_1] = 2;
  EnemyIntervalTimer[param_1] = 1;
  Enemy_State[param_1] = 0;
  SmallBBox(param_1);
  return;
}



// SMB:c307
// Signature: [X] -> []

void InitRetainerObj(byte param_1)

{
  Enemy_Y_Position[param_1] = 0xb8;
  return;
}



// SMB:c30e
// Signature: [X] -> []

void InitNormalEnemy(byte param_1)

{
  PlayerSpriteVarData1[param_1 + 1] = NormalXSpdData[PrimaryHardMode != 0];
  Enemy_BoundBoxCtrl[param_1] = 3;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
  return;
}



// SMB:c31e
// Signature: [X] -> []

void InitRedKoopa(byte param_1)

{
  InitNormalEnemy(param_1);
  Enemy_State[param_1] = 1;
  return;
}



// SMB:c328
// Signature: [X] -> []

void InitHammerBro(byte param_1)

{
  HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = 0;
  PlayerSpriteVarData1[param_1 + 1] = 0;
  EnemyIntervalTimer[param_1] = HBroWalkingTimerData[SecondaryHardMode];
  Enemy_BoundBoxCtrl[param_1] = 0xb;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
  return;
}



// SMB:c33d
// Signature: [X] -> []

void InitHorizFlySwimEnemy(byte param_1)

{
  PlayerSpriteVarData1[param_1 + 1] = 0;
  Enemy_BoundBoxCtrl[param_1] = 3;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
  return;
}



// SMB:c342
// Signature: [X] -> []

void InitBloober(byte param_1)

{
  PlayerSpriteVarData1[param_1 + 1] = 0;
  SmallBBox(param_1);
  return;
}



// SMB:c346
// Signature: [X] -> [A]

byte SmallBBox(byte param_1)

{
  byte bVar1;
  
  Enemy_BoundBoxCtrl[param_1] = 9;
  Enemy_MovingDir[param_1] = 2;
  bVar1 = InitVStf(param_1);
  return bVar1;
}



// SMB:c34a
// Signature: [X, C] -> []

void InitRedPTroopa(byte param_1,bool param_2)

{
  char cVar1;
  
  cVar1 = 0x30;
  Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] = Enemy_Y_Position[param_1];
  if (0x7f < Enemy_Y_Position[param_1]) {
    cVar1 = -0x20;
  }
  PlayerSpriteVarData1[param_1 + 1] = cVar1 + Enemy_Y_Position[param_1] + param_2;
  Enemy_BoundBoxCtrl[param_1] = 3;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
  return;
}



// SMB:c363
// Signature: [X] -> [A]

byte InitVStf(byte param_1)

{
  PlayerSpriteVarData2[param_1 + 1] = 0;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = 0;
  return 0;
}



// SMB:c36b
// Signature: [X] -> []

void InitBulletBill(byte param_1)

{
  Enemy_MovingDir[param_1] = 2;
  Enemy_BoundBoxCtrl[param_1] = 9;
  return;
}



// SMB:c375
// Signature: [X] -> []

void InitCheepCheep(byte param_1)

{
  SmallBBox(param_1);
  PlayerSpriteVarData1[param_1 + 1] = PseudoRandomBitReg[param_1] & 0x10;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] =
       Enemy_Y_Position[param_1];
  return;
}



// SMB:c385
// Signature: [X] -> []

void InitLakitu(byte param_1)

{
  if (EnemyFrenzyBuffer == 0) {
    SetupLakitu(param_1);
    return;
  }
  EraseEnemyObject(param_1);
  return;
}



// SMB:c38a
// Signature: [X] -> []

void SetupLakitu(byte param_1)

{
  LakituReappearTimer = 0;
  InitHorizFlySwimEnemy(param_1);
  Enemy_BoundBoxCtrl[param_1] = 3;
  return;
}



// SMB:c3a4
// Signature: [X] -> []

void LakituAndSpinyHandler(byte param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  if ((FrenzyEnemyTimer == 0) && (param_1 < 5)) {
    FrenzyEnemyTimer = 0x80;
    bVar2 = 4;
    do {
      if (Enemy_ID[bVar2] == 0x11) {
        if (PlayerOrSprObject_Y_Position[0] < 0x2c) {
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
        PlayerLakituDiff(ObjectOffset,PRDiffAdjustData[bVar1],PRDiffAdjustData[bVar1 + 4],
                         PRDiffAdjustData[bVar1 + 8]);
        bVar1 = SmallBBox(bVar2);
        bVar3 = 2;
        PlayerSpriteVarData1[bVar2 + 1] = bVar1;
        if (bVar1 < 0x80) {
          bVar3 = 1;
        }
        Enemy_MovingDir[bVar2] = bVar3;
        PlayerSpriteVarData2[bVar2 + 1] = 0xfd;
        Enemy_Flag[bVar2] = 1;
        Enemy_State[bVar2] = 5;
        return;
      }
      bVar2 -= 1;
    } while (bVar2 < 0x80);
    LakituReappearTimer += 1;
    if (6 < LakituReappearTimer) {
      bVar2 = 4;
      do {
        if (Enemy_Flag[bVar2] == 0) goto CreateL;
        bVar2 -= 1;
      } while (bVar2 < 0x80);
      if (bVar2 < 0x80) {
CreateL:
        Enemy_State[bVar2] = 0;
        Enemy_ID[bVar2] = 0x11;
        SetupLakitu(bVar2);
        PutAtRightExtent(0x20,bVar2);
      }
    }
  }
  return;
}



// SMB:c459
// Signature: [X] -> []

void InitLongFirebar(byte param_1)

{
  DuplicateEnemyObj(param_1);
  InitShortFirebar(param_1);
  return;
}



// SMB:c45c
// Signature: [X] -> []

void InitShortFirebar(byte param_1)

{
  byte bVar1;
  
  PlayerSpriteVarData1[param_1 + 1] = 0;
  FirebarSpinSpeed[param_1] = FirebarSpinSpdData[(byte)(Enemy_ID[param_1] - 0x1b)];
  FireballSpinDirectionOrVictoryDestPageLoc[param_1] =
       FirebarSpinDirData[(byte)(Enemy_ID[param_1] - 0x1b)];
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 4;
  bVar1 = Enemy_X_Position[param_1];
  Enemy_X_Position[param_1] = bVar1 + 4;
  Enemy_PageLoc[param_1] = Enemy_PageLoc[param_1] + (0xfb < bVar1);
  Enemy_BoundBoxCtrl[param_1] = 3;
  return;
}



// SMB:c4a8
// Signature: [X] -> []

void InitFlyingCheepCheep(byte param_1)

{
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
      PlayerSpriteVarData2[param_1 + 1] = 0xfb;
      cVar2 = 0;
      if ((PlayerSpriteVarData1[0] != 0) && (cVar2 = 4, 0x18 < PlayerSpriteVarData1[0])) {
        cVar2 = 8;
      }
      bVar3 = cVar2 + (bVar4 & 3);
      if ((PseudoRandomBitReg[param_1 + 1] & 3) != 0) {
        bVar3 = PseudoRandomBitReg[param_1 + 2] & 0xf;
      }
      bVar4 = cVar2 + (bVar4 & 3);
      PlayerSpriteVarData1[param_1 + 1] = FlyCCXSpeedData[bVar4];
      Enemy_MovingDir[param_1] = 1;
      if ((PlayerSpriteVarData1[0] == 0) && (bVar4 = bVar3, (bVar3 & 2) != 0)) {
        PlayerSpriteVarData1[param_1 + 1] = (PlayerSpriteVarData1[param_1 + 1] ^ 0xff) + 1;
        Enemy_MovingDir[param_1] = Enemy_MovingDir[param_1] + 1;
      }
      if ((bVar4 & 2) == 0) {
        bVar1 = PlayerOrSprObject_X_Position[0] < FlyCCXPositionData[bVar4];
        Enemy_X_Position[param_1] = PlayerOrSprObject_X_Position[0] - FlyCCXPositionData[bVar4];
        bVar4 = PlayerOrSprObject_PageLoc[0] - bVar1;
      }
      else {
        bVar1 = CARRY1(PlayerOrSprObject_X_Position[0],FlyCCXPositionData[bVar4]);
        Enemy_X_Position[param_1] = PlayerOrSprObject_X_Position[0] + FlyCCXPositionData[bVar4];
        bVar4 = PlayerOrSprObject_PageLoc[0] + bVar1;
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



// SMB:c549
// Signature: [X] -> []

void InitBowser(byte param_1)

{
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



// SMB:c575
// Signature: [X] -> []

void DuplicateEnemyObj(byte param_1)

{
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



// SMB:c5a3
// Signature: [X] -> []

void InitBowserFlame(byte param_1)

{
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
    BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] =
         PseudoRandomBitReg[param_1] & 3;
    PutAtRightExtent(FlameYPosData[PseudoRandomBitReg[param_1] & 3],param_1);
    return;
  }
  Enemy_X_Position[param_1] = Enemy_X_Position[BowserFront_Offset] - 0xe;
  Enemy_PageLoc[param_1] = Enemy_PageLoc[bVar1];
  Enemy_Y_Position[param_1] = Enemy_Y_Position[bVar1] + 8;
  BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] =
       PseudoRandomBitReg[param_1] & 3;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] =
       FlameYMFAdderData
       [Enemy_Y_Position[param_1] <= FlameYPosData[PseudoRandomBitReg[param_1] & 3]];
  EnemyFrenzyBuffer = 0;
  Enemy_BoundBoxCtrl[param_1] = 8;
  Enemy_Y_HighPos[param_1] = 1;
  Enemy_Flag[param_1] = 1;
  Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] = 0;
  Enemy_State[param_1] = 0;
  return;
}



// SMB:c5d8
// Signature: [A, X] -> [A]

byte PutAtRightExtent(byte param_1,byte param_2)

{
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



// SMB:c63d
// Signature: [X] -> []

void InitFireworks(byte param_1)

{
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
    Enemy_PageLoc[param_1] = (bVar2 - (bVar1 < 0x30)) + CARRY1(bVar4,bVar5);
    Enemy_Y_Position[param_1] = FireworksYPosData[bVar3];
    Enemy_Y_HighPos[param_1] = 1;
    Enemy_Flag[param_1] = 1;
    PlayerSpriteVarData1[param_1 + 1] = 0;
    PlayerSpriteVarData2[param_1 + 1] = 8;
  }
  return;
}



// SMB:c69c
// Signature: [X] -> []

void BulletBillCheepCheep(byte param_1)

{
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
        while( true ) {
          bVar1 &= 7;
          if ((Bitmasks[bVar1] & BitMFilter) == 0) break;
          bVar1 += 1;
        }
        BitMFilter = Bitmasks[bVar1] | BitMFilter;
        bVar1 = PutAtRightExtent(Enemy17YPosData[bVar1],param_1);
        BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = bVar1;
        FrenzyEnemyTimer = 0x20;
        CheckpointEnemyID(param_1);
        return;
      }
    }
    else {
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



// SMB:c71b
// Signature: [A] -> [X]

byte HandleGroupEnemies(byte param_1)

{
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
      if (4 < bVar4) goto Inc2B;
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
Inc2B:
  EnemyDataOffset = EnemyDataOffset + 2;
  EnemyObjectPageSel = 0;
  return ObjectOffset;
}



// SMB:c787
// Signature: [X] -> []

void InitPiranhaPlant(byte param_1)

{
  PlayerSpriteVarData1[param_1 + 1] = 1;
  Enemy_State[param_1] = 0;
  PlayerSpriteVarData2[param_1 + 1] = 0;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] =
       Enemy_Y_Position[param_1];
  BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] =
       Enemy_Y_Position[param_1] - 0x18;
  Enemy_BoundBoxCtrl[param_1] = 9;
  return;
}



// SMB:c7a0
// Signature: [X] -> []

void InitEnemyFrenzy(byte param_1)

{
  EnemyFrenzyBuffer = Enemy_ID[param_1];
  FUN_32ec(EnemyFrenzyBuffer - 0x12,param_1);
  return;
}



// SMB:c7b7
// Signature: [] -> []

void NoFrenzyCode(void)

{
  return;
}



// SMB:c7b8
// Signature: [X] -> []

void EndFrenzy(byte param_1)

{
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



// SMB:c7d1
// Signature: [X] -> []

void InitJumpGPTroopa(byte param_1)

{
  Enemy_MovingDir[param_1] = 2;
  PlayerSpriteVarData1[param_1 + 1] = 0xf8;
  Enemy_BoundBoxCtrl[param_1] = 3;
  return;
}



// SMB:c7df
// Signature: [X] -> []

void InitBalPlatform(byte param_1)

{
  bool bVar1;
  
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
  if (SecondaryHardMode == 0) {
    PosPlatform(param_1,2);
  }
  bVar1 = 0x7f < BalPlatformAlignment;
  Enemy_State[param_1] = BalPlatformAlignment;
  BalPlatformAlignment = 0xff;
  if (bVar1) {
    BalPlatformAlignment = param_1;
  }
  Enemy_MovingDir[param_1] = 0;
  PosPlatform(param_1,0);
  InitDropPlatform(param_1);
  return;
}



// SMB:c803
// Signature: [X] -> []

void InitDropPlatform(byte param_1)

{
  HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = 0xff;
  InitVStf(param_1);
  SPBBox(param_1);
  return;
}



// SMB:c80b
// Signature: [X] -> []

void InitHoriPlatform(byte param_1)

{
  PlayerSpriteVarData1[param_1 + 1] = 0;
  InitVStf(param_1);
  SPBBox(param_1);
  return;
}



// SMB:c812
// Signature: [X] -> []

void InitVertPlatform(byte param_1)

{
  byte bVar1;
  char cVar2;
  
  cVar2 = 0x40;
  bVar1 = Enemy_Y_Position[param_1];
  if (0x7f < bVar1) {
    bVar1 = (bVar1 ^ 0xff) + 1;
    cVar2 = -0x40;
  }
  Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] = bVar1;
  PlayerSpriteVarData1[param_1 + 1] = cVar2 + Enemy_Y_Position[param_1];
  InitVStf(param_1);
  SPBBox(param_1);
  return;
}



// SMB:c82b
// Signature: [X] -> []

void SPBBox(byte param_1)

{
  byte bVar1;
  
  bVar1 = 5;
  if ((AreaType != 3) && (SecondaryHardMode == 0)) {
    bVar1 = 6;
  }
  Enemy_BoundBoxCtrl[param_1] = bVar1;
  return;
}



// SMB:c83f
// Signature: [X] -> []

void LargeLiftUp(byte param_1)

{
  PlatLiftUp(param_1);
  SPBBox(param_1);
  return;
}



// SMB:c845
// Signature: [X] -> []

void LargeLiftDown(byte param_1)

{
  PlatLiftDown(param_1);
  SPBBox(param_1);
  return;
}



// SMB:c84b
// Signature: [X] -> []

void PlatLiftUp(byte param_1)

{
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = 0x10;
  PlayerSpriteVarData2[param_1 + 1] = 0xff;
  PosPlatform(param_1,1);
  Enemy_BoundBoxCtrl[param_1] = 4;
  return;
}



// SMB:c857
// Signature: [X] -> []

void PlatLiftDown(byte param_1)

{
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = 0xf0;
  PlayerSpriteVarData2[param_1 + 1] = 0;
  PosPlatform(param_1,1);
  Enemy_BoundBoxCtrl[param_1] = 4;
  return;
}



// SMB:c871
// Signature: [X, Y] -> []

void PosPlatform(byte param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = Enemy_X_Position[param_1];
  bVar2 = PlatPosDataLow[param_2];
  Enemy_X_Position[param_1] = bVar1 + bVar2;
  Enemy_PageLoc[param_1] = Enemy_PageLoc[param_1] + PlatPosDataHigh[param_2] + CARRY1(bVar1,bVar2);
  return;
}



// SMB:c881
// Signature: [] -> []

void EndOfEnemyInitCode(void)

{
  return;
}



// SMB:c882
// Signature: [] -> [X]

byte RunEnemyObjectsCore(void)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = 0;
  bVar2 = Enemy_ID[ObjectOffset];
  if (bVar2 >= 0x15) {
    bVar1 = (bVar2 - 0x14) - (bVar2 < 0x15);
  }
  bVar2 = FUN_3308(bVar1,ObjectOffset);
  return bVar2;
}



// SMB:c8d6
// Signature: [] -> []

void NoRunCode(void)

{
  return;
}



// SMB:c8d7
// Signature: [X] -> [X]

byte RunRetainerObj(byte param_1)

{
  byte bVar1;
  struct_xyi sVar2;
  struct_axr00 sVar3;
  
  sVar2 = GetEnemyOffscreenBits(param_1);
  sVar3 = RelativeEnemyPosition(sVar2.x);
  bVar1 = EnemyGfxHandler(sVar3.x);
  return bVar1;
}



// SMB:c8e0
// Signature: [X] -> [X]

byte RunNormalEnemies(byte param_1)

{
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



// SMB:c905
// Signature: [X] -> [X]

byte EnemyMovementSubs(byte param_1)

{
  byte bVar1;
  
  bVar1 = FUN_3394(Enemy_ID[param_1],param_1);
  return bVar1;
}



// SMB:c934
// Signature: [] -> []

void NoMoveCode(void)

{
  return;
}



// SMB:c935
// Signature: [X] -> [X]

byte RunBowserFlame(byte param_1)

{
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



// SMB:c947
// Signature: [X] -> [X]

byte RunFirebarObj(byte param_1)

{
  byte bVar1;
  
  bVar1 = ProcFirebar(param_1);
  OffscreenBoundsCheck(bVar1);
  return bVar1;
}



// SMB:c94d
// Signature: [X] -> [X]

byte RunSmallPlatform(byte param_1)

{
  byte bVar1;
  struct_axr00 sVar2;
  struct_xyi sVar3;
  
  sVar3 = GetEnemyOffscreenBits(param_1);
  sVar2 = RelativeEnemyPosition(sVar3.x);
  bVar1 = SmallPlatformBoundBox(sVar2.x);
  bVar1 = SmallPlatformCollision(bVar1);
  sVar2 = RelativeEnemyPosition(bVar1);
  bVar1 = DrawSmallPlatform(sVar2.x);
  MoveSmallPlatform(bVar1);
  OffscreenBoundsCheck(bVar1);
  return bVar1;
}



// SMB:c965
// Signature: [X] -> [X]

byte RunLargePlatform(byte param_1)

{
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



// SMB:c982
// Signature: [X] -> [X]

byte LargePlatformSubroutines(byte param_1)

{
  byte bVar1;
  
  bVar1 = FUN_33ec(Enemy_ID[param_1] - 0x24,param_1);
  return bVar1;
}



// SMB:c998
// Signature: [X] -> [A]

byte EraseEnemyObject(byte param_1)

{
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



// SMB:c9b0
// Signature: [X] -> [X]

byte MovePodoboo(byte param_1)

{
  byte bVar1;
  
  if (EnemyIntervalTimer[param_1] == 0) {
    InitPodoboo(param_1);
    bVar1 = PseudoRandomBitReg[param_1 + 1];
    CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = bVar1 | 0x80;
    EnemyIntervalTimer[param_1] = bVar1 & 0xf | 6;
    PlayerSpriteVarData2[param_1 + 1] = 0xf9;
  }
  bVar1 = MoveJ_EnemyVertically(param_1);
  return bVar1;
}



// SMB:c9d8
// Signature: [X] -> [X]

byte ProcHammerBro(byte param_1)

{
  byte bVar1;
  byte bVar2;
  struct_xci sVar3;
  
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
      sVar3 = SpawnHammerObj();
      param_1 = sVar3.x;
      if (sVar3.c != false) {
        Enemy_State[param_1] = Enemy_State[param_1] | 8;
        bVar1 = MoveHammerBroXDir(param_1);
        return bVar1;
      }
    }
    HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] =
         HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] - 1;
    bVar1 = MoveHammerBroXDir(param_1);
    return bVar1;
  }
  if ((Enemy_State[param_1] & 7) == 1) {
    bVar1 = MoveHammerBroXDir(param_1);
    return bVar1;
  }
  bVar1 = 0;
  bVar2 = 0xfa;
  if (Enemy_Y_Position[param_1] < 0x80) {
    bVar2 = 0xfd;
    bVar1 = 1;
    if ((0x6f < Enemy_Y_Position[param_1]) &&
       (bVar1 = 0, (PseudoRandomBitReg[param_1 + 1] & 1) == 0)) {
      bVar2 = 0xfa;
    }
  }
  PlayerSpriteVarData2[param_1 + 1] = bVar2;
  Enemy_State[param_1] = Enemy_State[param_1] | 1;
  bVar1 = bVar1 & PseudoRandomBitReg[param_1 + 2];
  if (SecondaryHardMode == 0) {
    bVar1 = SecondaryHardMode;
  }
  EnemyFrameTimer[param_1] = HammerBroJumpLData[bVar1];
  HammerBroJumpTimer[param_1] = PseudoRandomBitReg[param_1 + 1] | 0xc0;
  bVar1 = MoveHammerBroXDir(param_1);
  return bVar1;
}



// SMB:ca58
// Signature: [X] -> [X]

byte MoveHammerBroXDir(byte param_1)

{
  byte bVar1;
  struct_ncr00 sVar2;
  
  bVar1 = 0xfc;
  if ((FrameCounter & 0x40) == 0) {
    bVar1 = 4;
  }
  PlayerSpriteVarData1[param_1 + 1] = bVar1;
  bVar1 = 1;
  sVar2 = PlayerEnemyDiff(param_1);
  if ((!sVar2.n) && (bVar1 += 1, EnemyIntervalTimer[param_1] == 0)) {
    PlayerSpriteVarData1[param_1 + 1] = 0xf8;
  }
  Enemy_MovingDir[param_1] = bVar1;
  bVar1 = MoveNormalEnemy(param_1);
  return bVar1;
}



// SMB:ca77
// Signature: [X] -> [X]

byte MoveNormalEnemy(byte param_1)

{
  byte bVar1;
  byte bVar2;
  struct_axi sVar3;
  byte bStack0000;
  
  bVar2 = 0;
  if ((Enemy_State[param_1] & 0x40) == 0) {
    if ((bool)(Enemy_State[param_1] >> 7)) goto SteadM;
    if ((Enemy_State[param_1] & 0x20) != 0) {
      bVar2 = MoveDefeatedEnemy(param_1);
      return bVar2;
    }
    bVar1 = Enemy_State[param_1] & 7;
    if (bVar1 == 0) goto SteadM;
    if ((bVar1 != 5) && (2 < bVar1)) {
      if (EnemyIntervalTimer[param_1] == 0) {
        Enemy_State[param_1] = 0;
        bVar2 = FrameCounter & 1;
        Enemy_MovingDir[param_1] = bVar2 + 1;
        if (PrimaryHardMode != 0) {
          bVar2 += 2;
        }
        PlayerSpriteVarData1[param_1 + 1] = RevivedXSpeed[bVar2];
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
      if (Enemy_ID[param_1] == 0x2e) goto MEHor;
      bVar2 = 1;
    }
SteadM:
    bStack0000 = PlayerSpriteVarData1[param_1 + 1];
    if (0x7f < bStack0000) {
      bVar2 += 2;
    }
    PlayerSpriteVarData1[param_1 + 1] = bStack0000 + XSpeedAdderData[bVar2];
    sVar3 = MoveEnemyHorizontally(param_1);
    PlayerSpriteVarData1[sVar3.x + 1] = bStack0000;
    return sVar3.x;
  }
MEHor:
  sVar3 = MoveEnemyHorizontally(param_1);
  return sVar3.x;
}



// SMB:cae5
// Signature: [X] -> [X]

byte MoveDefeatedEnemy(byte param_1)

{
  byte bVar1;
  struct_axi sVar2;
  
  bVar1 = MoveD_EnemyVertically(param_1);
  sVar2 = MoveEnemyHorizontally(bVar1);
  return sVar2.x;
}



// SMB:caf9
// Signature: [X] -> [X]

byte MoveJumpingEnemy(byte param_1)

{
  byte bVar1;
  struct_axi sVar2;
  
  bVar1 = MoveJ_EnemyVertically(param_1);
  sVar2 = MoveEnemyHorizontally(bVar1);
  return sVar2.x;
}



// SMB:caff
// Signature: [X] -> [X]

byte ProcMoveRedPTroopa(byte param_1)

{
  byte bVar1;
  
  if (((PlayerSpriteVarData2[param_1 + 1] |
       CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1]) == 0) &&
     (BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = 0,
     Enemy_Y_Position[param_1] <
     Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1])) {
    if ((FrameCounter & 7) == 0) {
      Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 1;
    }
    return param_1;
  }
  if (PlayerSpriteVarData1[param_1 + 1] <= Enemy_Y_Position[param_1]) {
    bVar1 = MoveRedPTroopaUp(param_1);
    return bVar1;
  }
  bVar1 = MoveRedPTroopaDown(param_1);
  return bVar1;
}



// SMB:cb25
// Signature: [X] -> [X]

byte MoveFlyGreenPTroopa(byte param_1)

{
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



// SMB:cb45
// Signature: [X] -> []

void XMoveCntr_GreenPTroopa(byte param_1)

{
  XMoveCntr_Platform(0x13,param_1);
  return;
}



// SMB:cb47
// Signature: [A, X] -> []

void XMoveCntr_Platform(byte param_1,byte param_2)

{
  if ((FrameCounter & 3) != 0) {
    return;
  }
  if ((bool)(PlayerSpriteVarData2[param_2 + 1] & 1)) {
    if (PlayerSpriteVarData1[param_2 + 1] != 0) {
      PlayerSpriteVarData1[param_2 + 1] = PlayerSpriteVarData1[param_2 + 1] - 1;
      return;
    }
  }
  else if (PlayerSpriteVarData1[param_2 + 1] != param_1) {
    PlayerSpriteVarData1[param_2 + 1] = PlayerSpriteVarData1[param_2 + 1] + 1;
    return;
  }
  PlayerSpriteVarData2[param_2 + 1] = PlayerSpriteVarData2[param_2 + 1] + 1;
  return;
}



// SMB:cb66
// Signature: [X] -> [X, r00]

struct_xr00i MoveWithXMCntrs(byte param_1)

{
  byte bVar1;
  struct_axi sVar2;
  byte bStack0000;
  
  bStack0000 = PlayerSpriteVarData1[param_1 + 1];
  bVar1 = 1;
  if ((PlayerSpriteVarData2[param_1 + 1] & 2) == 0) {
    PlayerSpriteVarData1[param_1 + 1] = (PlayerSpriteVarData1[param_1 + 1] ^ 0xff) + 1;
    bVar1 = 2;
  }
  Enemy_MovingDir[param_1] = bVar1;
  sVar2 = MoveEnemyHorizontally(param_1);
  PlayerSpriteVarData1[sVar2.x + 1] = bStack0000;
  return (struct_xr00i)((uint3)sVar2 & 0xff0000 | (uint3)CONCAT11(sVar2.a,sVar2.x));
}



// SMB:cb89
// Signature: [X, C] -> [X]

byte MoveBloober(byte param_1,bool param_2)

{
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
  ProcSwimmingB(param_1,param_2);
  if (0x1f < (byte)(Enemy_Y_Position[param_1] -
                   CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1])) {
    Enemy_Y_Position[param_1] =
         Enemy_Y_Position[param_1] -
         CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];
  }
  if (Enemy_MovingDir[param_1] == 1) {
    bVar2 = Enemy_X_Position[param_1];
    bVar1 = PlayerSpriteVarData1[param_1 + 1];
    Enemy_X_Position[param_1] = bVar2 + bVar1;
    Enemy_PageLoc[param_1] = Enemy_PageLoc[param_1] + CARRY1(bVar2,bVar1);
    return param_1;
  }
  bVar2 = Enemy_X_Position[param_1];
  bVar1 = PlayerSpriteVarData1[param_1 + 1];
  Enemy_X_Position[param_1] = bVar2 - bVar1;
  Enemy_PageLoc[param_1] = Enemy_PageLoc[param_1] - (bVar2 < bVar1);
  return param_1;
}



// SMB:cbdf
// Signature: [X, C] -> []

void ProcSwimmingB(byte param_1,bool param_2)

{
  byte bVar1;
  
  if ((PlayerSpriteVarData2[param_1 + 1] & 2) == 0) {
    if (!(bool)(PlayerSpriteVarData2[param_1 + 1] & 1)) {
      if ((FrameCounter & 7) == 0) {
        bVar1 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] + 1;
        CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = bVar1;
        PlayerSpriteVarData1[param_1 + 1] = bVar1;
        if (bVar1 == 2) {
          PlayerSpriteVarData2[param_1 + 1] = PlayerSpriteVarData2[param_1 + 1] + 1;
        }
      }
      return;
    }
    if ((FrameCounter & 7) == 0) {
      bVar1 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] - 1;
      CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = bVar1;
      PlayerSpriteVarData1[param_1 + 1] = bVar1;
      if (bVar1 == 0) {
        PlayerSpriteVarData2[param_1 + 1] = PlayerSpriteVarData2[param_1 + 1] + 1;
        EnemyIntervalTimer[param_1] = 2;
      }
    }
    return;
  }
  if ((EnemyIntervalTimer[param_1] == 0) &&
     (PlayerOrSprObject_Y_Position[0] <= (byte)(Enemy_Y_Position[param_1] + 0x10 + param_2))) {
    PlayerSpriteVarData2[param_1 + 1] = 0;
    return;
  }
  if (!(bool)(FrameCounter & 1)) {
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 1;
  }
  return;
}



// SMB:cc36
// Signature: [X] -> [X]

byte MoveBulletBill(byte param_1)

{
  byte bVar1;
  struct_axi sVar2;
  
  if ((Enemy_State[param_1] & 0x20) != 0) {
    bVar1 = MoveJ_EnemyVertically(param_1);
    return bVar1;
  }
  PlayerSpriteVarData1[param_1 + 1] = 0xe8;
  sVar2 = MoveEnemyHorizontally(param_1);
  return sVar2.x;
}



// SMB:cc4a
// Signature: [X] -> [X]

byte MoveSwimmingCheepCheep(byte param_1)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  
  if ((Enemy_State[param_1] & 0x20) != 0) {
    bVar3 = MoveEnemySlowVert(param_1);
    return bVar3;
  }
  bVar1 = Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] <
          SwimCCXMoveData[(byte)(Enemy_ID[param_1] - 10)];
  Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] =
       Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] -
       SwimCCXMoveData[(byte)(Enemy_ID[param_1] - 10)];
  bVar3 = Enemy_X_Position[param_1];
  Enemy_X_Position[param_1] = bVar3 - bVar1;
  Enemy_PageLoc[param_1] = Enemy_PageLoc[param_1] - (bVar1 && (!bVar1 || bVar3 == 0));
  if (1 < param_1) {
    if (PlayerSpriteVarData1[param_1 + 1] < 0x10) {
      bVar1 = BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] < 0x20;
      BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] =
           BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] - 0x20;
      bVar3 = Enemy_Y_Position[param_1];
      Enemy_Y_Position[param_1] = bVar3 - bVar1;
      bVar3 = Enemy_Y_HighPos[param_1] - (bVar1 && (!bVar1 || bVar3 == 0));
    }
    else {
      bVar3 = BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1];
      BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = bVar3 + 0x20;
      bVar2 = Enemy_Y_Position[param_1] + (0xdf < bVar3);
      Enemy_Y_Position[param_1] = bVar2;
      bVar3 = Enemy_Y_HighPos[param_1] + (0xdf < bVar3 && bVar2 == 0);
    }
    Enemy_Y_HighPos[param_1] = bVar3;
    bVar2 = 0;
    bVar3 = Enemy_Y_Position[param_1] -
            CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];
    if (0x7f < bVar3) {
      bVar2 = 0x10;
      bVar3 = (bVar3 ^ 0xff) + 1;
    }
    if (0xe < bVar3) {
      PlayerSpriteVarData1[param_1 + 1] = bVar2;
    }
  }
  return param_1;
}



// SMB:cd3c
// Signature: [X] -> [X]

byte ProcFirebar(byte param_1)

{
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
      bVar2 = FirebarSpin(FirebarSpinSpeed[bVar3],bVar3);
      PlayerSpriteVarData2[bVar3 + 1] = bVar2 & 0x1f;
    }
    MysterySpriteThing4 = PlayerSpriteVarData2[bVar3 + 1];
    if ((0x1e < Enemy_ID[bVar3]) && ((MysterySpriteThing4 == 8 || (MysterySpriteThing4 == 0x18)))) {
      MysterySpriteThing4 += 1;
      PlayerSpriteVarData2[bVar3 + 1] = MysterySpriteThing4;
    }
    sVar5 = RelativeEnemyPosition(bVar3);
    bVar3 = sVar5.x;
    GetFirebarPosition(sVar5.a,sVar5.r00);
    bVar1 = Enemy_Rel_YPos;
    bVar3 = Enemy_SprDataOffset[bVar3];
    Sprite_Data[bVar3] = Enemy_Rel_YPos;
    bVar2 = Enemy_Rel_XPos;
    Sprite_Data[bVar3 + 3] = Enemy_Rel_XPos;
    sVar7 = FirebarCollision(bVar3,1,bVar2,bVar1);
    bVar2 = sVar7.r06;
    MysterySpriteThing3 = 5;
    if (0x1e < Enemy_ID[sVar7.x]) {
      MysterySpriteThing3 = 0xb;
    }
    bVar1 = 0;
    do {
      sVar6 = GetFirebarPosition(MysterySpriteThing4,bVar1);
      sVar7 = DrawFirebar_Collision(bVar1,sVar6.r01,sVar6.r02,sVar6.r03,bVar2);
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



// SMB:cdbb
// Signature: [r00, r01, r02, r03, r06] -> [X, r00, r06]

struct_xr00r06
DrawFirebar_Collision(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5)

{
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
  }
  else {
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
  }
  else {
    bVar2 = 0xf8;
  }
  Sprite_Data[param_5] = bVar2;
  sVar4 = FirebarCollision(param_5,param_1,bVar1,bVar2);
  return sVar4;
}



// SMB:ce08
// Signature: [Y, r00, r06, r07] -> [X, r00, r06]

struct_xr00r06 FirebarCollision(byte param_1,byte param_2,byte param_3,byte param_4)

{
  ushort uVar1;
  byte bVar2;
  byte abVar3 [1];
  byte bVar4;
  byte bStack0000;
  
  DrawFirebar(param_1);
  bVar2 = StarInvincibleTimer | TimerControl;
  bStack0000 = param_1;
  if ((bVar2 != 0) || (PlayerOrSprObject_Y_HighPos[0] != 1)) {
NoColFB:
    return (struct_xr00r06)CONCAT12(bStack0000 + 4,CONCAT11(param_2,ObjectOffset));
  }
  if ((PlayerSize != 0) || (abVar3[0] = PlayerOrSprObject_Y_Position[0], CrouchingFlag != 0)) {
    bVar2 = 2;
    abVar3[0] = PlayerOrSprObject_Y_Position[0] + 0x18;
  }
  do {
    bVar4 = abVar3[0] - param_4;
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
    if (bVar2 == 2) goto NoColFB;
    uVar1 = (ushort)bVar2;
    bVar2 += 1;
    abVar3[0] = PlayerOrSprObject_Y_Position[0] + FirebarYPos[uVar1];
  } while( true );
}



// SMB:ce8e
// Signature: [A, r00] -> [r01, r02, r03]

struct_r01r02r03 GetFirebarPosition(byte param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = param_1 & 0xf;
  if (8 < bVar1) {
    bVar1 = (bVar1 ^ 0xf) + 1;
  }
  bVar2 = param_1 + 8 & 0xf;
  if (8 < bVar2) {
    bVar2 = (bVar2 ^ 0xf) + 1;
  }
  return (struct_r01r02r03)
         CONCAT12(FirebarMirrorData[param_1 >> 3],
                  CONCAT11(FirebarPosLookupTbl[(byte)(FirebarTblOffsets[param_2] + bVar2)],
                           FirebarPosLookupTbl[(byte)(FirebarTblOffsets[param_2] + bVar1)]));
}



// SMB:cedf
// Signature: [X] -> [X]

byte MoveFlyingCheepCheep(byte param_1)

{
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
  bVar2 = SetXMoveAmt(5,sVar4.x,0xd);
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



// SMB:cf28
// Signature: [X] -> [X]

byte MoveLakitu(byte param_1)

{
  byte bVar1;
  struct_axi sVar2;
  
  if ((Enemy_State[param_1] & 0x20) == 0) {
    if (Enemy_State[param_1] == 0) {
      EnemyFrenzyBuffer = 0x12;
      bVar1 = PlayerLakituDiff(param_1,LakituDiffAdj[0],LakituDiffAdj[1],LakituDiffAdj[2]);
    }
    else {
      PlayerSpriteVarData2[param_1 + 1] = 0;
      EnemyFrenzyBuffer = 0;
      bVar1 = 0x10;
    }
    PlayerSpriteVarData1[param_1 + 1] = bVar1;
    bVar1 = 1;
    if ((PlayerSpriteVarData2[param_1 + 1] & 1) == 0) {
      PlayerSpriteVarData1[param_1 + 1] = (PlayerSpriteVarData1[param_1 + 1] ^ 0xff) + 1;
      bVar1 = 2;
    }
    Enemy_MovingDir[param_1] = bVar1;
    sVar2 = MoveEnemyHorizontally(param_1);
    return sVar2.x;
  }
  bVar1 = MoveD_EnemyVertically(param_1);
  return bVar1;
}



// SMB:cf6c
// Signature: [X, r01, r02, r03] -> [A]

byte PlayerLakituDiff(byte param_1,byte param_2,byte param_3,byte param_4)

{
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
  if (((0x3b < bVar1) && (bVar1 = 0x3c, Enemy_ID[param_1] == 0x11)) &&
     (bVar2 != PlayerSpriteVarData2[param_1 + 1])) {
    if (PlayerSpriteVarData2[param_1 + 1] != 0) {
      PlayerSpriteVarData1[param_1 + 1] = PlayerSpriteVarData1[param_1 + 1] - 1;
      if (PlayerSpriteVarData1[param_1 + 1] != 0) {
        return PlayerSpriteVarData1[param_1 + 1];
      }
    }
    PlayerSpriteVarData2[param_1 + 1] = bVar2;
  }
  bVar1 = (bVar1 & 0x3c) >> 2;
  cVar3 = 0;
  if ((PlayerSpriteVarData1[0] != 0) && (ScrollAmount != 0)) {
    cVar3 = 1;
    if ((0x18 < PlayerSpriteVarData1[0]) && (1 < ScrollAmount)) {
      cVar3 = 2;
    }
    if (((Enemy_ID[param_1] != 0x12) || (PlayerSpriteVarData1[0] == 0)) &&
       (PlayerSpriteVarData2[param_1 + 1] == 0)) {
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



// SMB:cfec
// Signature: [r00] -> []

void BridgeCollapse(byte param_1)

{
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
        RemBridge(0xc,bVar2,param_1,BridgeCollapseData[BridgeCollapseOffset],0x22);
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
    if (((Enemy_State[BowserFront_Offset] & 0x40) != 0) &&
       (Enemy_Y_Position[BowserFront_Offset] < 0xe0)) {
      MoveD_Bowser(BowserFront_Offset);
      return;
    }
  }
  EventMusicQueue = 0x80;
  OperMode_Task += 1;
  KillAllEnemies();
  return;
}



// SMB:d00f
// Signature: [X] -> [X]

byte MoveD_Bowser(byte param_1)

{
  byte bVar1;
  
  bVar1 = MoveEnemySlowVert(param_1);
  bVar1 = BowserGfxHandler(bVar1);
  return bVar1;
}



// SMB:d065
// Signature: [X] -> [X]

byte RunBowser(byte param_1)

{
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
  if (TimerControl != 0) goto ChkFireB;
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
      if (199 < Enemy_X_Position[param_1]) goto HammerChk;
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
  }
  else if (EnemyFrameTimer[param_1] == 1) {
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
    InitVStf(param_1);
    PlayerSpriteVarData2[param_1 + 1] = 0xfe;
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



// SMB:d071
// Signature: [] -> [X]

byte KillAllEnemies(void)

{
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



// SMB:d17b
// Signature: [X] -> [X]

byte BowserGfxHandler(byte param_1)

{
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



// SMB:d1bc
// Signature: [X] -> [X]

byte ProcessBowserHalf(byte param_1)

{
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



// SMB:d1d9
// Signature: [] -> [A]

byte SetFlameTimer(void)

{
  byte bVar1;
  
  bVar1 = BowserFlameTimerCtrl;
  BowserFlameTimerCtrl = BowserFlameTimerCtrl + 1 & 7;
  return FlameTimerData[bVar1];
}



// SMB:d1eb
// Signature: [X] -> [X]

byte ProcBowserFlame(byte param_1)

{
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
    Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] =
         Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] - bVar3;
    bVar3 = Enemy_X_Position[param_1];
    Enemy_X_Position[param_1] = (bVar3 - 1) - bVar1;
    Enemy_PageLoc[param_1] =
         Enemy_PageLoc[param_1] - ((bVar1 || bVar3 == 0) && (!bVar1 || bVar3 < 2));
    if (Enemy_Y_Position[param_1] !=
        FlameYPosData[BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1]]) {
      Enemy_Y_Position[param_1] =
           Enemy_Y_Position[param_1] +
           CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];
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



// SMB:d295
// Signature: [X] -> [X]

byte RunFireworks(byte param_1)

{
  byte bVar1;
  struct_axr00 sVar2;
  
  bVar1 = PlayerSpriteVarData2[param_1 + 1] - 1;
  PlayerSpriteVarData2[param_1 + 1] = bVar1;
  if (bVar1 == 0) {
    PlayerSpriteVarData2[param_1 + 1] = 8;
    PlayerSpriteVarData1[param_1 + 1] = PlayerSpriteVarData1[param_1 + 1] + 1;
    if (2 < PlayerSpriteVarData1[param_1 + 1]) {
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
  bVar1 = DrawExplosion_Fireworks(PlayerSpriteVarData1[sVar2.x + 1],Enemy_SprDataOffset[sVar2.x]);
  return bVar1;
}



// SMB:d2d9
// Signature: [X] -> [X]

byte RunStarFlagObj(byte param_1)

{
  byte bVar1;
  
  EnemyFrenzyBuffer = 0;
  if (StarFlagTaskControl < 5) {
    bVar1 = FUN_340c(StarFlagTaskControl,param_1);
    return bVar1;
  }
  return param_1;
}



// SMB:d2f2
// Signature: [X] -> []

void GameTimerFireworks(byte param_1)

{
  byte bVar1;
  
  bVar1 = 5;
  FireworksCounter = GameTimerDisplay[2];
  if (((GameTimerDisplay[2] != 1) && (bVar1 = 3, GameTimerDisplay[2] != 3)) &&
     (bVar1 = 0, GameTimerDisplay[2] != 6)) {
    FireworksCounter = 0xff;
  }
  Enemy_State[param_1] = bVar1;
  StarFlagTaskControl = StarFlagTaskControl + 1;
  return;
}



// SMB:d311
// Signature: [] -> []

void StarFlagExit(void)

{
  return;
}



// SMB:d312
// Signature: [X] -> [X]

byte AwardGameTimerPoints(byte param_1)

{
  byte bVar1;
  
  if ((byte)(GameTimerDisplay[0] | GameTimerDisplay[1] | GameTimerDisplay[2]) != 0) {
    if ((FrameCounter & 4) != 0) {
      Square2SoundQueue = 0x10;
    }
    DigitModifier[5] = 0xff;
    DigitsMathRoutine(0x23);
    DigitModifier[5] = 5;
    bVar1 = EndAreaPoints();
    return bVar1;
  }
  StarFlagTaskControl = StarFlagTaskControl + 1;
  return param_1;
}



// SMB:d336
// Signature: [] -> [X]

byte EndAreaPoints(void)

{
  byte bVar1;
  
  bVar1 = 0xb;
  if (CurrentPlayer != 0) {
    bVar1 = 0x11;
  }
  DigitsMathRoutine(bVar1);
  bVar1 = UpdateNumber(CurrentPlayer << 4 | 4);
  return bVar1;
}



// SMB:d34e
// Signature: [X] -> [X]

byte RaiseFlagSetoffFWorks(byte param_1)

{
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



// SMB:d365
// Signature: [X] -> [X]

byte DrawStarFlag(byte param_1)

{
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



// SMB:d3a2
// Signature: [X] -> [X]

byte DelayToAreaEnd(byte param_1)

{
  byte bVar1;
  
  bVar1 = DrawStarFlag(param_1);
  if ((EnemyIntervalTimer[bVar1] == 0) && (EventMusicBuffer == 0)) {
    StarFlagTaskControl = StarFlagTaskControl + 1;
    return bVar1;
  }
  return bVar1;
}



// SMB:d3b0
// Signature: [X] -> []

void MovePiranhaPlant(byte param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  struct_ncr00 sVar4;
  
  if ((Enemy_State[param_1] == 0) && (EnemyFrameTimer[param_1] == 0)) {
    if (PlayerSpriteVarData2[param_1 + 1] == 0) {
      if (PlayerSpriteVarData1[param_1 + 1] < 0x80) {
        sVar4 = PlayerEnemyDiff(param_1);
        bVar3 = sVar4.r00;
        if (sVar4.n != false) {
          bVar3 = (bVar3 ^ 0xff) + 1;
        }
        if (bVar3 < 0x21) goto PutinPipe;
      }
      PlayerSpriteVarData1[param_1 + 1] = (PlayerSpriteVarData1[param_1 + 1] ^ 0xff) + 1;
      PlayerSpriteVarData2[param_1 + 1] = PlayerSpriteVarData2[param_1 + 1] + 1;
    }
    bVar3 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];
    if (0x7f < PlayerSpriteVarData1[param_1 + 1]) {
      bVar3 = BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1];
    }
    if ((((FrameCounter & 1) != 0) && (TimerControl == 0)) &&
       (bVar1 = Enemy_Y_Position[param_1], bVar2 = PlayerSpriteVarData1[param_1 + 1],
       Enemy_Y_Position[param_1] = bVar1 + bVar2, (byte)(bVar1 + bVar2) == bVar3)) {
      PlayerSpriteVarData2[param_1 + 1] = 0;
      EnemyFrameTimer[param_1] = 0x40;
    }
  }
PutinPipe:
  Enemy_SprAttrib[param_1] = 0x20;
  return;
}



// SMB:d410
// Signature: [A, X] -> [A]

byte FirebarSpin(byte param_1,byte param_2)

{
  byte bVar1;
  
  if (FireballSpinDirectionOrVictoryDestPageLoc[param_2] == 0) {
    bVar1 = PlayerSpriteVarData1[param_2 + 1];
    PlayerSpriteVarData1[param_2 + 1] = bVar1 + param_1;
    return PlayerSpriteVarData2[param_2 + 1] + CARRY1(bVar1,param_1);
  }
  bVar1 = PlayerSpriteVarData1[param_2 + 1];
  PlayerSpriteVarData1[param_2 + 1] = bVar1 - param_1;
  return PlayerSpriteVarData2[param_2 + 1] - (bVar1 < param_1);
}



// SMB:d432
// Signature: [X] -> [X]

byte BalancePlatform(byte param_1)

{
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
  if (0x7f < bVar3) {
    return param_1;
  }
  if (Enemy_MovingDir[param_1] != 0) {
    bVar3 = PlatformFall(param_1,bVar3);
    return bVar3;
  }
  if (Enemy_Y_Position[param_1] < 0x2e) {
    if (bVar3 != HammerThrowingTimer_Or_PlatformCollisionFlag[param_1]) {
      Enemy_Y_Position[param_1] = 0x2f;
      StopPlatforms(param_1,bVar3);
      return param_1;
    }
MakePlatformFall:
    bVar3 = InitPlatformFall(bVar3);
    return bVar3;
  }
  if (Enemy_Y_Position[bVar3] < 0x2e) {
    if (param_1 != HammerThrowingTimer_Or_PlatformCollisionFlag[param_1]) {
      Enemy_Y_Position[bVar3] = 0x2f;
      StopPlatforms(param_1,bVar3);
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
  }
  else {
    bVar2 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] + 5;
    bVar1 = PlayerSpriteVarData2[param_1 + 1] +
            (0xfa < CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1]);
    if (0x7f < bVar1) goto PlatDn;
    if (bVar1 == 0) {
      if (bVar2 < 0xb) {
        StopPlatforms(param_1,bVar3);
        goto DoOtherPlatform;
      }
      if (bVar2 < 0xb) goto ColFlg;
    }
  }
  param_1 = MovePlatformUp(param_1);
DoOtherPlatform:
  Enemy_Y_Position[Enemy_State[param_1]] =
       (bStack0000 - Enemy_Y_Position[param_1]) + Enemy_Y_Position[Enemy_State[param_1]];
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] < 0x80) {
    PositionPlayerOnVPlat(HammerThrowingTimer_Or_PlatformCollisionFlag[param_1]);
  }
  if (((PlayerSpriteVarData2[ObjectOffset + 1] |
       CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[ObjectOffset]) != 0) &&
     (VRAM_Buffer1_Offset < 0x20)) {
    bVar3 = PlayerSpriteVarData2[ObjectOffset + 1];
    bVar2 = ObjectOffset;
    bStack0000 = bVar3;
    sVar4 = SetupPlatformRope(bVar3,ObjectOffset);
    bVar1 = sVar4.x;
    VRAM_Buffer1[bVar1] = sVar4.r01;
    VRAM_Buffer1[bVar1 + 1] = sVar4.r00;
    VRAM_Buffer1[bVar1 + 2] = 2;
    if (PlayerSpriteVarData2[bVar2 + 1] < 0x80) {
      VRAM_Buffer1[bVar1 + 3] = 0xa2;
      VRAM_Buffer1[bVar1 + 4] = 0xa3;
    }
    else {
      VRAM_Buffer1[bVar1 + 3] = 0x24;
      VRAM_Buffer1[bVar1 + 4] = 0x24;
    }
    sVar4 = SetupPlatformRope(bVar3 ^ 0xff,Enemy_State[bVar2]);
    bVar3 = sVar4.x;
    VRAM_Buffer1[bVar3 + 5] = sVar4.r01;
    VRAM_Buffer1[bVar3 + 6] = sVar4.r00;
    VRAM_Buffer1[bVar3 + 7] = 2;
    if (bStack0000 < 0x80) {
      VRAM_Buffer1[bVar3 + 8] = 0x24;
      VRAM_Buffer1[bVar3 + 9] = 0x24;
    }
    else {
      VRAM_Buffer1[bVar3 + 8] = 0xa2;
      VRAM_Buffer1[bVar3 + 9] = 0xa3;
    }
    VRAM_Buffer1[bVar3 + 10] = 0;
    VRAM_Buffer1_Offset += 10;
  }
  return ObjectOffset;
}



// SMB:d541
// Signature: [A, Y] -> [X, r00, r01]

struct_xr00r01 SetupPlatformRope(byte param_1,byte param_2)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  
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
  return (struct_xr00r01)
         CONCAT12((Enemy_PageLoc[param_2] + bVar1 & 1) << 2 |
                  (bVar3 >> 7) << 1 | (byte)(bVar3 << 1) >> 7 | 0x20,
                  CONCAT11(bVar2,VRAM_Buffer1_Offset));
}



// SMB:d598
// Signature: [Y] -> [X]

byte InitPlatformFall(byte param_1)

{
  byte bVar1;
  byte bVar2;
  struct_xyi sVar3;
  
  sVar3 = GetEnemyOffscreenBits(param_1);
  bVar2 = sVar3.y;
  bVar1 = sVar3.x;
  SetupFloateyNumber(6,bVar1);
  FloateyNum_X_Pos[bVar1] = PlayerOrSprObject_Rel_XPos[0];
  FloateyNum_Y_Pos[bVar1] = PlayerOrSprObject_Y_Position[0];
  Enemy_MovingDir[bVar1] = 1;
  StopPlatforms(bVar1,bVar2);
  return bVar1;
}



// SMB:d5b1
// Signature: [X, Y] -> []

void StopPlatforms(byte param_1,byte param_2)

{
  byte bVar1;
  
  bVar1 = InitVStf(param_1);
  PlayerSpriteVarData2[param_2 + 1] = bVar1;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_2] = bVar1;
  return;
}



// SMB:d5bb
// Signature: [X, Y] -> [X]

byte PlatformFall(byte param_1,byte param_2)

{
  byte bStack0000;
  
  bStack0000 = param_2;
  MoveFallingPlatform(param_1);
  MoveFallingPlatform(bStack0000);
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[ObjectOffset] < 0x80) {
    PositionPlayerOnVPlat(HammerThrowingTimer_Or_PlatformCollisionFlag[ObjectOffset]);
  }
  return ObjectOffset;
}



// SMB:d5d3
// Signature: [X] -> [X]

byte YMovingPlatform(byte param_1)

{
  byte bVar1;
  
  if (((PlayerSpriteVarData2[param_1 + 1] |
       CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1]) == 0) &&
     (BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = 0,
     Enemy_Y_Position[param_1] <
     Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1])) {
    if ((FrameCounter & 7) == 0) {
      Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 1;
    }
    ChkYPCollision(param_1);
    return param_1;
  }
  if (PlayerSpriteVarData1[param_1 + 1] <= Enemy_Y_Position[param_1]) {
    bVar1 = MovePlatformUp(param_1);
    ChkYPCollision(bVar1);
    return bVar1;
  }
  bVar1 = MovePlatformDown(param_1);
  ChkYPCollision(bVar1);
  return bVar1;
}



// SMB:d5fe
// Signature: [X] -> []

void ChkYPCollision(byte param_1)

{
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] < 0x80) {
    PositionPlayerOnVPlat(param_1);
  }
  return;
}



// SMB:d607
// Signature: [X] -> [X]

byte XMovingPlatform(byte param_1)

{
  byte bVar1;
  struct_xr00i sVar2;
  
  XMoveCntr_Platform(0xe,param_1);
  sVar2 = MoveWithXMCntrs(param_1);
  bVar1 = sVar2.x;
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[bVar1] < 0x80) {
    PositionPlayerOnHPlat(bVar1,sVar2.r00);
    return bVar1;
  }
  return bVar1;
}



// SMB:d614
// Signature: [X, r00] -> []

void PositionPlayerOnHPlat(byte param_1,byte param_2)

{
  char cVar1;
  
  cVar1 = CARRY1(PlayerOrSprObject_X_Position[0],param_2);
  if (0x7f < param_2) {
    cVar1 = -!(bool)cVar1;
  }
  PlayerOrSprObject_PageLoc[0] += cVar1;
  PlayerOrSprObject_X_Position[0] = PlayerOrSprObject_X_Position[0] + param_2;
  Platform_X_Scroll = param_2;
  PositionPlayerOnVPlat(param_1);
  return;
}



// SMB:d631
// Signature: [X] -> [X]

byte DropPlatform(byte param_1)

{
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] < 0x80) {
    param_1 = MoveDropPlatform(param_1);
    PositionPlayerOnVPlat(param_1);
  }
  return param_1;
}



// SMB:d63d
// Signature: [X] -> [X]

byte RightPlatform(byte param_1)

{
  byte bVar1;
  struct_axi sVar2;
  
  sVar2 = MoveEnemyHorizontally(param_1);
  bVar1 = sVar2.x;
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[bVar1] < 0x80) {
    PlayerSpriteVarData1[bVar1 + 1] = 0x10;
    PositionPlayerOnHPlat(bVar1,sVar2.a);
  }
  return bVar1;
}



// SMB:d64f
// Signature: [X] -> []

void MoveLargeLiftPlat(byte param_1)

{
  MoveLiftPlatforms(param_1);
  ChkYPCollision(param_1);
  return;
}



// SMB:d655
// Signature: [X] -> []

void MoveSmallPlatform(byte param_1)

{
  MoveLiftPlatforms(param_1);
  ChkSmallPlatCollision(param_1);
  return;
}



// SMB:d65b
// Signature: [X] -> []

void MoveLiftPlatforms(byte param_1)

{
  byte bVar1;
  
  if (TimerControl == 0) {
    bVar1 = BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1];
    BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] =
         bVar1 + CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];
    Enemy_Y_Position[param_1] =
         Enemy_Y_Position[param_1] + PlayerSpriteVarData2[param_1 + 1] +
         CARRY1(bVar1,CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1]);
    return;
  }
  return;
}



// SMB:d671
// Signature: [X] -> []

void ChkSmallPlatCollision(byte param_1)

{
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] != 0) {
    PositionPlayerOnS_Plat(HammerThrowingTimer_Or_PlatformCollisionFlag[param_1],param_1);
  }
  return;
}



// SMB:d67a
// Signature: [X] -> []

void OffscreenBoundsCheck(byte param_1)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  byte abVar5 [1];
  byte bVar6;
  bool bVar7;
  bool bVar8;
  
  if (Enemy_ID[param_1] != 0x14) {
    bVar1 = Enemy_ID[param_1];
    bVar7 = 4 < bVar1;
    if ((bVar1 == 5) || (bVar7 = 0xc < bVar1, abVar5[0] = ScreenEdgeOrLeft_X_Pos[0], bVar1 == 0xd))
    {
      abVar5[0] = ScreenEdgeOrLeft_X_Pos[0] + 0x38 + bVar7;
      bVar7 = 199 < ScreenEdgeOrLeft_X_Pos[0] || bVar7 && abVar5[0] == 0;
    }
    bVar2 = 0x47 < abVar5[0];
    bVar3 = !bVar7;
    bVar4 = 0x48 < abVar5[0];
    bVar8 = (bVar7 && bVar2 || bVar3 && bVar4) ||
            ((!bVar7 || !bVar2) && (!bVar3 || !bVar4)) && ScreenEdgeOrLeft_PageLoc[0] != 0;
    bVar6 = ScreenRight_X_Pos + 0x48 + bVar8;
    if ((0x7f < (byte)((Enemy_PageLoc[param_1] -
                       (ScreenEdgeOrLeft_PageLoc[0] - ((!bVar7 || !bVar2) && (!bVar3 || !bVar4)))) -
                      (Enemy_X_Position[param_1] < (byte)((abVar5[0] + 0xb8) - !bVar7)))) ||
       (((((byte)((Enemy_PageLoc[param_1] -
                  (ScreenRight_PageLoc + (0xb7 < ScreenRight_X_Pos || bVar8 && bVar6 == 0))) -
                 (Enemy_X_Position[param_1] < bVar6)) < 0x80 && (Enemy_State[param_1] != 5)) &&
         (bVar1 != 0xd)) && (((bVar1 != 0x30 && (bVar1 != 0x31)) && (bVar1 != 0x32)))))) {
      EraseEnemyObject(param_1);
    }
  }
  return;
}



// SMB:d6d9
// Signature: [X] -> [X]

byte FireballEnemyCollision(byte param_1)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  byte bStack0000;
  
  if (((Fireball_State[param_1] != 0) && (!(bool)(Fireball_State[param_1] >> 7))) &&
     (!(bool)(FrameCounter & 1))) {
    bStack0000 = param_1 * 4 + 0x1c;
    bVar2 = 4;
    do {
      if ((((((Enemy_State[bVar2] & 0x20) == 0) && (Enemy_Flag[bVar2] != 0)) &&
           ((bVar1 = Enemy_ID[bVar2], bVar1 < 0x24 || (0x2a < bVar1)))) &&
          ((bVar1 != 6 || (Enemy_State[bVar2] < 2)))) && (EnemyOffscrBitsMasked[bVar2] == 0)) {
        bVar3 = SprObjectCollisionCore(bVar2 * 4 + 4,bStack0000);
        if (bVar3) {
          Fireball_State[ObjectOffset] = 0x80;
          HandleEnemyFBallCol(bVar2,bVar2);
        }
      }
      bVar2 -= 1;
    } while (bVar2 < 0x80);
  }
  return ObjectOffset;
}



// SMB:d73e
// Signature: [X, r01] -> []

void HandleEnemyFBallCol(byte param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  RelativeEnemyPosition(param_1);
  if ((Enemy_Flag[param_2] < 0x80) || (bVar2 = Enemy_Flag[param_2] & 0xf, Enemy_ID[bVar2] != 0x2d))
  {
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
  PlayerSpriteVarData1[bVar2 + 1] = EnemyFrenzyBuffer;
  PlayerSpriteVarData2[bVar2 + 1] = 0xfe;
  bVar1 = WorldNumber;
  Enemy_ID[bVar2] = BowserIdentities[WorldNumber];
  bVar3 = 0x20;
  if (bVar1 < 3) {
    bVar3 = 0x23;
  }
  Enemy_State[bVar2] = bVar3;
  Square2SoundQueue = 0x80;
  EnemySmackScore(9,param_2);
  return;
}



// SMB:d795
// Signature: [X] -> []

void ShellOrBlockDefeat(byte param_1)

{
  byte bVar1;
  
  bVar1 = Enemy_ID[param_1];
  if (bVar1 == 0xd) {
    bVar1 = Enemy_Y_Position[param_1] + 0x18 + (0xc < bVar1);
    Enemy_Y_Position[param_1] = bVar1;
  }
  ChkToStunEnemies(bVar1,param_1);
  Enemy_State[param_1] = Enemy_State[param_1] & 0x1f | 0x20;
  bVar1 = 2;
  if (Enemy_ID[param_1] == 5) {
    bVar1 = 6;
  }
  if (Enemy_ID[param_1] != 6) {
    EnemySmackScore(bVar1,param_1);
    return;
  }
  EnemySmackScore(1,param_1);
  return;
}



// SMB:d7bc
// Signature: [A, X] -> []

void EnemySmackScore(byte param_1,byte param_2)

{
  SetupFloateyNumber(param_1,param_2);
  Square1SoundQueue = 8;
  return;
}



// SMB:d7c4
// Signature: [X] -> [X]

byte PlayerHammerCollision(byte param_1)

{
  byte bVar1;
  bool bVar2;
  
  if (((FrameCounter & 1) != 0) && ((TimerControl | Misc_OffscreenBits) == 0)) {
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
    }
    else {
      Misc_Collision_Flag[ObjectOffset] = 0;
    }
  }
  return param_1;
}



// SMB:d800
// Signature: [X] -> [X]

byte HandlePowerUpCollision(byte param_1)

{
  byte bVar1;
  
  EraseEnemyObject(param_1);
  SetupFloateyNumber(6,param_1);
  Square2SoundQueue = 0x20;
  if (1 < PowerUpType) {
    if (PowerUpType == 3) {
      FloateyNum_Control[param_1] = 0xb;
      return param_1;
    }
    StarInvincibleTimer = 0x23;
    AreaMusicQueue = 0x40;
    return param_1;
  }
  if (PlayerStatus == 0) {
    PlayerStatus = 1;
    bVar1 = 9;
  }
  else {
    if (PlayerStatus != 1) {
      Square2SoundQueue = 0x20;
      return param_1;
    }
    PlayerStatus = 2;
    GetPlayerColors();
    bVar1 = 0xc;
  }
  bVar1 = SetPRout(bVar1,0);
  return bVar1;
}



// SMB:d853
// Signature: [X] -> [X]

byte PlayerEnemyCollision(byte param_1)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  struct_ayi sVar4;
  byte bStack0000;
  
  if ((bool)(FrameCounter & 1)) {
    return param_1;
  }
  bVar3 = CheckPlayerVertical();
  if ((((!bVar3) && (EnemyOffscrBitsMasked[param_1] == 0)) && (GameEngineSubroutine == 8)) &&
     ((Enemy_State[param_1] & 0x20) == 0)) {
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
      if (bVar1 != 0x12) {
        if (bVar1 == 0xd) {
          bVar1 = InjurePlayer();
          return bVar1;
        }
        if (bVar1 == 0xc) {
          bVar1 = InjurePlayer();
          return bVar1;
        }
        if (bVar1 != 0x33) {
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
            PlayerSpriteVarData1[param_1 + 1] = KickedShellXSpdData[bVar1];
            bVar1 = StompChainCounter + 3;
            if (EnemyIntervalTimer[param_1] < 3) {
              bVar1 = KickedShellPtsData[EnemyIntervalTimer[param_1]];
            }
            SetupFloateyNumber(bVar1,param_1);
            return param_1;
          }
        }
      }
      if ((((0x7f < PlayerSpriteVarData2[0]) || (PlayerSpriteVarData2[0] == 0)) &&
          ((Enemy_ID[param_1] < 7 ||
           (Enemy_Y_Position[param_1] <= (byte)(PlayerOrSprObject_Y_Position[0] + 0xc))))) &&
         (StompTimer == 0)) {
        if (InjuryTimer != 0) {
          return ObjectOffset;
        }
        if (PlayerOrSprObject_Rel_XPos[0] < Enemy_Rel_XPos) {
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
      if (((((bVar1 != 0x14) && (bVar1 != 8)) && (bVar1 != 0x33)) &&
          ((bVar1 != 0xc && (bVar2 = 1, bVar1 != 5)))) &&
         ((bVar2 = 2, bVar1 != 0x11 && (bVar2 = 3, bVar1 != 7)))) {
        if (bVar1 < 9) {
          Enemy_State[param_1] = 4;
          StompChainCounter += 1;
          SetupFloateyNumber(StompChainCounter + StompTimer,param_1);
          StompTimer += 1;
          EnemyIntervalTimer[param_1] = RevivalRateData[PrimaryHardMode];
        }
        else {
          Enemy_ID[param_1] = bVar1 & 1;
          Enemy_State[param_1] = 0;
          SetupFloateyNumber(3,param_1);
          InitVStf(param_1);
          bVar1 = EnemyFacePlayer(param_1);
          PlayerSpriteVarData1[param_1 + 1] = DemotedKoopaXSpdData[bVar1];
        }
        PlayerSpriteVarData2[0] = 0xfc;
        return param_1;
      }
      SetupFloateyNumber(StompedEnemyPtsData[bVar2],param_1);
      bStack0000 = Enemy_MovingDir[param_1];
      SetStun(param_1);
      Enemy_MovingDir[param_1] = bStack0000;
      Enemy_State[param_1] = 0x20;
      bVar1 = InitVStf(param_1);
      PlayerSpriteVarData1[param_1 + 1] = bVar1;
      PlayerSpriteVarData2[0] = 0xfd;
      return param_1;
    }
    Enemy_CollisionBits[ObjectOffset] = Enemy_CollisionBits[ObjectOffset] & 0xfe;
  }
  return param_1;
}



// SMB:d92c
// Signature: [] -> [X]

byte InjurePlayer(void)

{
  byte bVar1;
  
  if (InjuryTimer == 0) {
    bVar1 = ForceInjury(0);
    return bVar1;
  }
  return ObjectOffset;
}



// SMB:d931
// Signature: [A] -> [X]

byte ForceInjury(byte param_1)

{
  byte bVar1;
  
  if (PlayerStatus == 0) {
    EventMusicQueue = 1;
    PlayerSpriteVarData2[0] = 0xfc;
    bVar1 = 0xb;
    PlayerSpriteVarData1[0] = PlayerStatus;
  }
  else {
    InjuryTimer = 8;
    Square1SoundQueue = 0x10;
    PlayerStatus = param_1;
    GetPlayerColors();
    bVar1 = 10;
  }
  bVar1 = SetPRout(bVar1,1);
  return bVar1;
}



// SMB:d948
// Signature: [A, Y] -> [X]

byte SetPRout(byte param_1,byte param_2)

{
  GameEngineSubroutine = param_1;
  Player_State = param_2;
  TimerControl = 0xff;
  ScrollAmount = 0;
  return ObjectOffset;
}



// SMB:d9f6
// Signature: [X] -> [X]

byte ChkEnemyFaceRight(byte param_1)

{
  byte bVar1;
  
  if (Enemy_MovingDir[param_1] != 1) {
    bVar1 = LInj(param_1);
    return bVar1;
  }
  bVar1 = InjurePlayer();
  return bVar1;
}



// SMB:d9ff
// Signature: [X] -> [X]

byte LInj(byte param_1)

{
  byte bVar1;
  
  EnemyTurnAround(param_1);
  bVar1 = InjurePlayer();
  return bVar1;
}



// SMB:da05
// Signature: [X] -> [Y]

byte EnemyFacePlayer(byte param_1)

{
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



// SMB:da11
// Signature: [A, X] -> [A]

byte SetupFloateyNumber(byte param_1,byte param_2)

{
  byte bVar1;
  
  FloateyNum_Control[param_2] = param_1;
  FloateyNum_Timer[param_2] = 0x30;
  FloateyNum_Y_Pos[param_2] = Enemy_Y_Position[param_2];
  bVar1 = Enemy_Rel_XPos;
  FloateyNum_X_Pos[param_2] = Enemy_Rel_XPos;
  return bVar1;
}



// SMB:da33
// Signature: [X] -> [X]

byte EnemiesCollision(byte param_1)

{
  byte bVar1;
  bool bVar2;
  struct_ayi sVar3;
  byte bStack0000;
  
  if (((FrameCounter & 1) == 0) || (AreaType == 0)) {
    return param_1;
  }
  bVar1 = Enemy_ID[param_1];
  if ((((bVar1 < 0x15) && (bVar1 != 0x11)) && (bVar1 != 0xd)) &&
     (EnemyOffscrBitsMasked[param_1] == 0)) {
    sVar3 = GetEnemyBoundBoxOfs();
    bStack0000 = sVar3.y;
joined_r0xda54:
    param_1 -= 1;
    if (param_1 < 0x80) {
      if (((Enemy_Flag[param_1] != 0) && (bVar1 = Enemy_ID[param_1], bVar1 < 0x15)) &&
         ((bVar1 != 0x11 && ((bVar1 != 0xd && (EnemyOffscrBitsMasked[param_1] == 0)))))) {
        bVar2 = SprObjectCollisionCore(param_1 * 4 + 4,bStack0000);
        bVar1 = ObjectOffset;
        if (bVar2) {
          if (((Enemy_State[ObjectOffset] | Enemy_State[param_1]) & 0x80) == 0) {
            if ((Enemy_CollisionBits[param_1] & SetBitsMask[ObjectOffset]) != 0)
            goto joined_r0xda54;
            Enemy_CollisionBits[param_1] = Enemy_CollisionBits[param_1] | SetBitsMask[ObjectOffset];
          }
          ProcEnemyCollisions(bVar1,param_1,param_1);
          goto joined_r0xda54;
        }
        Enemy_CollisionBits[param_1] = Enemy_CollisionBits[param_1] & ClearBitsMask[ObjectOffset];
      }
      goto joined_r0xda54;
    }
  }
  return ObjectOffset;
}



// SMB:dab4
// Signature: [X, Y, r01] -> []

void ProcEnemyCollisions(byte param_1,byte param_2,byte param_3)

{
  if (((Enemy_State[param_2] | Enemy_State[param_1]) & 0x20) == 0) {
    if (Enemy_State[param_1] < 6) {
      if (Enemy_State[param_2] < 6) {
        EnemyTurnAround(param_2);
        EnemyTurnAround(ObjectOffset);
        return;
      }
      if (Enemy_ID[param_2] != 5) {
        ShellOrBlockDefeat(param_1);
        SetupFloateyNumber(ShellChainCounter[param_3] + 4,ObjectOffset);
        ShellChainCounter[param_3] = ShellChainCounter[param_3] + 1;
        return;
      }
    }
    else if (Enemy_ID[param_1] != 5) {
      if ((char)Enemy_State[param_2] < 0) {
        SetupFloateyNumber(6,param_1);
        ShellOrBlockDefeat(param_1);
        param_2 = param_3;
      }
      ShellOrBlockDefeat(param_2);
      SetupFloateyNumber(ShellChainCounter[ObjectOffset] + 4,param_3);
      ShellChainCounter[ObjectOffset] = ShellChainCounter[ObjectOffset] + 1;
    }
  }
  return;
}



// SMB:db1c
// Signature: [X] -> []

void EnemyTurnAround(byte param_1)

{
  byte bVar1;
  
  bVar1 = Enemy_ID[param_1];
  if (((bVar1 != 0xd) && (bVar1 != 0x11)) && (bVar1 != 5)) {
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



// SMB:db36
// Signature: [X] -> []

void RXSpd(byte param_1)

{
  PlayerSpriteVarData1[param_1 + 1] = (PlayerSpriteVarData1[param_1 + 1] ^ 0xff) + 1;
  Enemy_MovingDir[param_1] = Enemy_MovingDir[param_1] ^ 3;
  return;
}



// SMB:db45
// Signature: [X] -> [X]

byte LargePlatformCollision(byte param_1)

{
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



// SMB:db5f
// Signature: [X] -> [X]

byte ChkForPlayerC_LargeP(byte param_1)

{
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
      ProcLPlatCollisions(bStack0000,bVar2,bVar1);
    }
  }
  return ObjectOffset;
}



// SMB:db7b
// Signature: [X] -> [X]

byte SmallPlatformCollision(byte param_1)

{
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
        if (((uint3)sVar4 & 2) != 0) {
          return ObjectOffset;
        }
        if ((0x1f < BoundingBox_UL_YPos[bVar2]) && (bVar3 = PlayerCollisionCore(bVar2), bVar3)) {
          bVar1 = ProcLPlatCollisions(ObjectOffset,bVar2,bVar1);
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



// SMB:dbbc
// Signature: [X, Y, r00] -> [X]

byte ProcLPlatCollisions(byte param_1,byte param_2,byte param_3)

{
  byte bVar1;
  
  if (((byte)(BoundingBox_DR_YPos[param_2] - BoundingBox_UL_YPos[0]) < 4) &&
     (0x7f < PlayerSpriteVarData2[0])) {
    PlayerSpriteVarData2[0] = 1;
  }
  if (((byte)(BoundingBox_DR_YPos[0] - BoundingBox_UL_YPos[param_2]) < 6) &&
     (PlayerSpriteVarData2[0] < 0x80)) {
    if ((Enemy_ID[param_1] != 0x2b) && (Enemy_ID[param_1] != 0x2c)) {
      param_3 = param_1;
    }
    bVar1 = ObjectOffset;
    HammerThrowingTimer_Or_PlatformCollisionFlag[ObjectOffset] = param_3;
    Player_State = 0;
    return bVar1;
  }
  bVar1 = 1;
  if (((byte)(BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[0] -
             BoundingBox_UL_Corner_Or_XPos[param_2]) < 8) ||
     (bVar1 = 2,
     (byte)((BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2] -
            BoundingBox_UL_Corner_Or_XPos[0]) - 1) < 9)) {
    ImpedePlayerMove(bVar1);
  }
  return ObjectOffset;
}



// SMB:dc19
// Signature: [A, X] -> []

void PositionPlayerOnS_Plat(byte param_1,byte param_2)

{
  byte bVar1;
  
  bVar1 = Enemy_Y_Position[param_2] + PlayerPosSPlatData[param_1 - 1];
  if ((GameEngineSubroutine != 0xb) && (Enemy_Y_HighPos[param_2] == 1)) {
    PlayerOrSprObject_Y_Position[0] = bVar1 - 0x20;
    PlayerOrSprObject_Y_HighPos[0] = 1 - (bVar1 < 0x20);
    PlayerSpriteVarData2[0] = 0;
    PlayerOrSprObject_Y_MoveForce[0] = 0;
  }
  return;
}



// SMB:dc21
// Signature: [X] -> []

void PositionPlayerOnVPlat(byte param_1)

{
  if ((GameEngineSubroutine != 0xb) && (Enemy_Y_HighPos[param_1] == 1)) {
    PlayerOrSprObject_Y_Position[0] = Enemy_Y_Position[param_1] - 0x20;
    PlayerOrSprObject_Y_HighPos[0] = 1 - (Enemy_Y_Position[param_1] < 0x20);
    PlayerSpriteVarData2[0] = 0;
    PlayerOrSprObject_Y_MoveForce[0] = 0;
  }
  return;
}



// SMB:dc41
// Signature: [] -> [C]

bool CheckPlayerVertical(void)

{
  bool bVar1;
  
  bVar1 = 0xef < PlayerOrSprObject_OffscrBits[0];
  if ((!bVar1) && (PlayerOrSprObject_Y_HighPos[0] == 1)) {
    bVar1 = 0xcf < PlayerOrSprObject_Y_Position[0];
  }
  return bVar1;
}



// SMB:dc52
// Signature: [] -> [A, Y]

struct_ayi GetEnemyBoundBoxOfs(void)

{
  struct_ayi sVar1;
  
  sVar1 = GetEnemyBoundBoxOfsArg(ObjectOffset);
  return sVar1;
}



// SMB:dc54
// Signature: [A] -> [A, Y]

struct_ayi GetEnemyBoundBoxOfsArg(byte param_1)

{
  
  
  return (struct_ayi)
         (CONCAT12(0,CONCAT11(param_1 * 4 + 4,Enemy_OffscreenBits)) & 0xffff0f);
}



// SMB:dc64
// Signature: [] -> []

void PlayerBGCollision(void)

{
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
  if (PlayerOrSprObject_Y_HighPos[0] != 1) {
    return;
  }
  Player_CollisionBits = 0xff;
  if (0xce < PlayerOrSprObject_Y_Position[0]) {
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
  if (PlayerBGUpperExtent[bVar6] <= PlayerOrSprObject_Y_Position[0]) {
    sVar9 = BlockBufferColli_Head(MysterySpriteThing1);
    bVar4 = sVar9.r07;
    bVar6 = sVar9.r02;
    bVar3 = sVar9.r06;
    bVar1 = sVar9.r04;
    if (!sVar9.z) {
      sVar10 = CheckForCoinMTiles(sVar9.a);
      bVar7 = sVar10.a;
      if (sVar10.c) goto HandleCoinMetatile;
      if ((0x7f < PlayerSpriteVarData2[0]) && (3 < bVar1)) {
        bVar8 = CheckForSolidMTiles(bVar7);
        if (bVar8) {
          if (bVar7 != 0x26) {
            Square1SoundQueue = 2;
          }
        }
        else if ((AreaType != 0) && (BlockBounceTimer == 0)) {
          PlayerHeadCollision(bVar7,bVar6,bVar3,bVar4);
          goto DoFootCheck;
        }
        PlayerSpriteVarData2[0] = 1;
      }
    }
  }
DoFootCheck:
  if (PlayerOrSprObject_Y_Position[0] < 0xcf) {
    sVar11 = BlockBufferColli_Feet(MysterySpriteThing1);
    bVar4 = sVar11.r07;
    bVar6 = sVar11.r02;
    bVar3 = sVar11.r06;
    bVar7 = sVar11.y;
    sVar10 = CheckForCoinMTiles(sVar11.a);
    bVar1 = sVar10.a;
    if (sVar10.c) goto HandleCoinMetatile;
    sVar11 = BlockBufferColli_Feet(bVar7);
    bVar4 = sVar11.r07;
    bVar6 = sVar11.r02;
    bVar3 = sVar11.r06;
    bVar5 = sVar11.r04;
    bVar2 = sVar11.a;
    bVar7 = bVar1;
    if (bVar1 == 0) {
      if (bVar2 == 0) goto DoPlayerSideCheck;
      sVar10 = CheckForCoinMTiles(bVar2);
      bVar7 = sVar10.a;
      if (sVar10.c != false) goto HandleCoinMetatile;
    }
    bVar8 = CheckForClimbMTiles(bVar7);
    if ((!bVar8) && (PlayerSpriteVarData2[0] < 0x80)) {
      if (bVar7 == 0xc5) {
        OperMode_Task = 0;
        OperMode = 2;
        PlayerSpriteVarData1[0] = 0x18;
        ErACM(bVar6,bVar3,bVar4);
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
          PlayerOrSprObject_Y_Position[0] &= 0xf0;
          HandlePipeEntry(bVar2,bVar1);
          PlayerSpriteVarData2[0] = 0;
          PlayerOrSprObject_Y_MoveForce[0] = 0;
          StompChainCounter = 0;
        }
        Player_State = 0;
      }
    }
  }
DoPlayerSideCheck:
  bVar7 = MysterySpriteThing1 + 2;
  bVar1 = 2;
  while (MysterySpriteThing1 = bVar7 + 1, PlayerOrSprObject_Y_Position[0] < 0x20) {
BHalf:
    bVar7 = MysterySpriteThing1 + 1;
    if (PlayerOrSprObject_Y_Position[0] < 8) {
      return;
    }
    if (0xcf < PlayerOrSprObject_Y_Position[0]) {
      return;
    }
    sVar9 = BlockBufferColli_Side(bVar7);
    bVar4 = sVar9.r07;
    bVar6 = sVar9.r02;
    bVar3 = sVar9.r06;
    bVar2 = sVar9.r04;
    bVar5 = sVar9.a;
    if (sVar9.z == false) goto CheckSideMTiles;
    bVar1 -= 1;
    if (bVar1 == 0) {
      return;
    }
  }
  if (0xe3 < PlayerOrSprObject_Y_Position[0]) {
    return;
  }
  sVar9 = BlockBufferColli_Side(MysterySpriteThing1);
  bVar4 = sVar9.r07;
  bVar6 = sVar9.r02;
  bVar3 = sVar9.r06;
  bVar2 = sVar9.r04;
  bVar5 = sVar9.a;
  if ((((sVar9.z) || (bVar5 == 0x1c)) || (bVar5 == 0x6b)) ||
     (bVar8 = CheckForClimbMTiles(bVar5), bVar8)) goto BHalf;
CheckSideMTiles:
  bVar8 = ChkInvisibleMTiles(bVar5);
  if (!bVar8) {
    bVar8 = CheckForClimbMTiles(bVar5);
    if (bVar8) {
      HandleClimbing(bVar5,bVar2,bVar3);
      return;
    }
    sVar10 = CheckForCoinMTiles(bVar5);
    bVar7 = sVar10.a;
    if (sVar10.c) {
HandleCoinMetatile:
      ErACM(bVar6,bVar3,bVar4);
      CoinTallyFor1Ups += 1;
      GiveOneCoin();
      return;
    }
    bVar8 = ChkJumpspringMetatiles(bVar7);
    if (bVar8) {
      if (JumpspringAnimCtrl != 0) {
        return;
      }
    }
    else if (((Player_State == 0) && (PlayerFacingDir == 1)) && ((bVar7 == 0x6c || (bVar7 == 0x1f)))
            ) {
      if (Player_SprAttrib == 0) {
        Square1SoundQueue = 0x10;
      }
      Player_SprAttrib |= 0x20;
      if ((PlayerOrSprObject_X_Position[0] & 0xf) != 0) {
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



// SMB:de1c
// Signature: [r02, r06, r07] -> []

void ErACM(byte param_1,byte param_2,byte param_3)

{
  RAM(CONCAT11(param_3,param_2) + (ushort)param_1) = 0;
  RemoveCoin_Axe(param_1,param_2);
  return;
}



// SMB:de2e
// Signature: [A, r04, r06] -> []

void HandleClimbing(byte param_1,byte param_2,byte param_3)

{
  if ((param_2 < 6) || (9 < param_2)) {
    return;
  }
  if ((param_1 == 0x24) || (param_1 == 0x25)) {
    if (GameEngineSubroutine != 5) {
      PlayerFacingDir = 1;
      ScrollLock += 1;
      if (GameEngineSubroutine != 4) {
        KillEnemies(0x33);
        EventMusicQueue = 0x80;
        FlagpoleSoundQueue = 0x40;
        FlagpoleScore = 4;
        FlagpoleCollisionYPos = PlayerOrSprObject_Y_Position[0];
        do {
          if (FlagpoleYPosData[FlagpoleScore] <= PlayerOrSprObject_Y_Position[0]) break;
          FlagpoleScore -= 1;
        } while (FlagpoleScore != 0);
      }
      GameEngineSubroutine = 4;
    }
  }
  else if ((param_1 == 0x26) && (PlayerOrSprObject_Y_Position[0] < 0x20)) {
    GameEngineSubroutine = 1;
  }
  Player_State = 3;
  PlayerSpriteVarData1[0] = 0;
  Player_X_MoveForce = 0;
  if ((byte)(PlayerOrSprObject_X_Position[0] - ScreenEdgeOrLeft_X_Pos[0]) < 0x10) {
    PlayerFacingDir = 2;
  }
  PlayerOrSprObject_X_Position[0] = param_3 * 0x10 + ClimbXPosAdder[PlayerFacingDir - 1];
  if (param_3 == 0) {
    PlayerOrSprObject_PageLoc[0] = ScreenRight_PageLoc + ClimbXPosAdder[PlayerFacingDir + 1];
  }
  return;
}



// SMB:debd
// Signature: [A] -> [Z]

bool ChkInvisibleMTiles(byte param_1)

{
  return param_1 == 0x5f || param_1 == 0x60;
}



// SMB:dec4
// Signature: [A] -> []

void ChkForLandJumpSpring(byte param_1)

{
  bool bVar1;
  
  bVar1 = ChkJumpspringMetatiles(param_1);
  if (bVar1) {
    VerticalForce = 0x70;
    JumpspringForce = 0xf9;
    JumpspringTimer = 3;
    JumpspringAnimCtrl = 1;
  }
  return;
}



// SMB:dedd
// Signature: [A] -> [C]

bool ChkJumpspringMetatiles(byte param_1)

{
  bool bVar1;
  
  if ((param_1 == 0x67) || (bVar1 = false, param_1 == 0x68)) {
    bVar1 = true;
  }
  return bVar1;
}



// SMB:dee8
// Signature: [r00, r01] -> []

void HandlePipeEntry(byte param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  
  if ((((Up_Down_Buttons & 4) != 0) && (param_1 == 0x11)) && (param_2 == 0x10)) {
    ChangeAreaTimer = 0x30;
    GameEngineSubroutine = 3;
    Square1SoundQueue = 0x10;
    Player_SprAttrib = 0x20;
    if (WarpZoneControl != 0) {
      bVar1 = (WarpZoneControl & 3) * 4;
      bVar2 = bVar1;
      if ((0x5f < PlayerOrSprObject_X_Position[0]) &&
         (bVar2 = bVar1 + 1, 0x9f < PlayerOrSprObject_X_Position[0])) {
        bVar2 = bVar1 + 2;
      }
      WorldNumber = WarpZoneNumbers[bVar2] - 1;
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



// SMB:df4b
// Signature: [r00] -> []

void ImpedePlayerMove(byte param_1)

{
  byte bVar1;
  char cVar2;
  
  if (param_1 == 1) {
    if (0x7f < PlayerSpriteVarData1[0]) goto ExIPM;
    bVar1 = 0xff;
  }
  else {
    param_1 = 2;
    if ((byte)(PlayerSpriteVarData1[0] - 1) < 0x80) goto ExIPM;
    bVar1 = 1;
  }
  SideCollisionTimer = 0x10;
  cVar2 = 0;
  PlayerSpriteVarData1[0] = 0;
  if (0x7f < bVar1) {
    cVar2 = -1;
  }
  PlayerOrSprObject_PageLoc[0] =
       PlayerOrSprObject_PageLoc[0] + cVar2 + CARRY1(bVar1,PlayerOrSprObject_X_Position[0]);
  PlayerOrSprObject_X_Position[0] = bVar1 + PlayerOrSprObject_X_Position[0];
ExIPM:
  Player_CollisionBits = (param_1 ^ 0xff) & Player_CollisionBits;
  return;
}



// SMB:df8f
// Signature: [A] -> [C]

bool CheckForSolidMTiles(byte param_1)

{
  byte bVar1;
  
  bVar1 = GetMTileAttrib(param_1);
  return SolidMTileUpperExt[bVar1] <= param_1;
}



// SMB:df9a
// Signature: [A] -> [C]

bool CheckForClimbMTiles(byte param_1)

{
  byte bVar1;
  
  bVar1 = GetMTileAttrib(param_1);
  return ClimbMTileUpperExt[bVar1] <= param_1;
}



// SMB:dfa1
// Signature: [A] -> [A, C]

struct_aci CheckForCoinMTiles(byte param_1)

{
  
  bool bVar1;
  
  bVar1 = 0xc1 < param_1;
  if ((param_1 != 0xc2) && (bVar1 = 0xc2 < param_1, param_1 != 0xc3)) {
    return (struct_aci)CONCAT12(0,(ushort)param_1);
  }
  Square2SoundQueue = 1;
  return (struct_aci)CONCAT12(0,CONCAT11(bVar1,1));
}



// SMB:dfb0
// Signature: [A] -> [X]

byte GetMTileAttrib(byte param_1)

{
  return (param_1 >> 7) << 1 | (byte)((param_1 & 0xc0) << 1) >> 7;
}



// SMB:dfc1
// Signature: [X] -> [X]

byte EnemyToBGCollisionDet(byte param_1)

{
  byte bVar1;
  short sVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  bool bVar6;
  struct_ncr00 sVar7;
  struct_axzr02r04r06r07 sVar8;
  
  if ((((Enemy_State[param_1] & 0x20) != 0) || (bVar6 = SubtEnemyYPos(param_1), !bVar6)) ||
     ((bVar4 = Enemy_ID[param_1], bVar4 == 0x12 && (Enemy_Y_Position[param_1] < 0x25)))) {
    return param_1;
  }
  if (bVar4 == 0xe) {
    bVar4 = EnemyJump(param_1);
    return bVar4;
  }
  if (bVar4 == 5) {
    bVar4 = HammerBroBGColl(param_1);
    return bVar4;
  }
  if (((bVar4 != 0x12) && (bVar4 != 0x2e)) && (6 < bVar4)) {
    return param_1;
  }
  sVar8 = ChkUnderEnemy(param_1);
  sVar2 = (short)((uint7)sVar8 >> 0x28);
  bVar1 = sVar8.r04;
  bVar4 = sVar8.r02;
  bVar5 = sVar8.x;
  bVar3 = sVar8.a;
  if ((sVar8.z != false) || (bVar6 = ChkForNonSolids(bVar3), bVar6)) {
    bVar4 = ChkForRedKoopa(bVar5);
    return bVar4;
  }
  if (bVar3 == 0x23) {
    RAM(sVar2 + (ushort)bVar4) = 0;
    bVar4 = Enemy_ID[bVar5];
    if (bVar4 < 0x15) {
      if (bVar4 == 6) {
        KillEnemyAboveBlock(bVar5);
      }
      bVar4 = SetupFloateyNumber(1,bVar5);
      ChkToStunEnemies(bVar4,bVar5);
      return bVar5;
    }
    ChkToStunEnemies(bVar4,bVar5);
    return bVar5;
  }
  if (4 < (byte)(bVar1 - 8)) {
    bVar4 = ChkForRedKoopa(bVar5);
    return bVar4;
  }
  if ((Enemy_State[bVar5] & 0x40) == 0) {
    if (((char)Enemy_State[bVar5] < 0) || (bVar4 = Enemy_State[bVar5], bVar4 == 0)) {
      bVar4 = DoEnemySideCheck(bVar5);
      return bVar4;
    }
    if (bVar4 != 5) {
      if (2 < bVar4) {
        return bVar5;
      }
      if (Enemy_State[bVar5] == 2) {
        bVar4 = 0x10;
        if (Enemy_ID[bVar5] == 0x12) {
          bVar4 = 0;
        }
        EnemyIntervalTimer[bVar5] = bVar4;
        Enemy_State[bVar5] = 3;
        EnemyLanding(bVar5);
        return bVar5;
      }
    }
    if (Enemy_ID[bVar5] != 6) {
      if (Enemy_ID[bVar5] == 0x12) {
        Enemy_MovingDir[bVar5] = 1;
        PlayerSpriteVarData1[bVar5 + 1] = 8;
        if ((FrameCounter & 7) == 0) goto LandEnemyInitState;
      }
      bVar4 = 1;
      sVar7 = PlayerEnemyDiff(bVar5);
      if (sVar7.n != false) {
        bVar4 += 1;
      }
      if (bVar4 == Enemy_MovingDir[bVar5]) {
        bVar5 = ChkForBump_HammerBroJ(bVar5);
      }
    }
  }
LandEnemyInitState:
  EnemyLanding(bVar5);
  if ((Enemy_State[bVar5] & 0x80) != 0) {
    Enemy_State[bVar5] = Enemy_State[bVar5] & 0xbf;
    return bVar5;
  }
  Enemy_State[bVar5] = 0;
  return bVar5;
}



// SMB:e01b
// Signature: [A, X] -> []

void ChkToStunEnemies(byte param_1,byte param_2)

{
  if (param_1 < 9) {
    SetStun(param_2);
    return;
  }
  if (0x10 < param_1) {
    SetStun(param_2);
    return;
  }
  if ((9 < param_1) && (param_1 < 0xd)) {
    SetStun(param_2);
    return;
  }
  Enemy_ID[param_2] = param_1 & 1;
  SetStun(param_2);
  return;
}



// SMB:e02f
// Signature: [X] -> []

void SetStun(byte param_1)

{
  byte bVar1;
  struct_ncr00 sVar2;
  
  Enemy_State[param_1] = Enemy_State[param_1] & 0xf0 | 2;
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
  if ((Enemy_ID[param_1] == 7) || (bVar1 = 0xfd, AreaType == 0)) {
    bVar1 = 0xff;
  }
  PlayerSpriteVarData2[param_1 + 1] = bVar1;
  bVar1 = 1;
  sVar2 = PlayerEnemyDiff(param_1);
  if (sVar2.n != false) {
    bVar1 += 1;
  }
  if ((Enemy_ID[param_1] != 0x33) && (Enemy_ID[param_1] != 8)) {
    Enemy_MovingDir[param_1] = bVar1;
  }
  PlayerSpriteVarData1[param_1 + 1] = EnemyBGCXSpdData[(byte)(bVar1 - 1)];
  return;
}



// SMB:e0e2
// Signature: [X] -> [X]

byte ChkForRedKoopa(byte param_1)

{
  byte bVar1;
  
  if ((Enemy_ID[param_1] == 3) && (Enemy_State[param_1] == 0)) {
    bVar1 = ChkForBump_HammerBroJ(param_1);
    return bVar1;
  }
  if ((char)Enemy_State[param_1] < 0) {
    bVar1 = Enemy_State[param_1] | 0x40;
  }
  else {
    bVar1 = EnemyBGCStateData[Enemy_State[param_1]];
  }
  Enemy_State[param_1] = bVar1;
  bVar1 = DoEnemySideCheck(param_1);
  return bVar1;
}



// SMB:e0fe
// Signature: [X] -> [X]

byte DoEnemySideCheck(byte param_1)

{
  byte bVar1;
  bool bVar2;
  struct_axzr02r04r06r07 sVar3;
  
  if (0x1f < Enemy_Y_Position[param_1]) {
    bVar1 = 0x16;
    MysterySpriteThing1 = 2;
    do {
      if (MysterySpriteThing1 == Enemy_MovingDir[param_1]) {
        sVar3 = BlockBufferChk_Enemy(1,param_1,bVar1);
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



// SMB:e124
// Signature: [X] -> [X]

byte ChkForBump_HammerBroJ(byte param_1)

{
  byte bVar1;
  
  if ((param_1 != 5) && ((char)Enemy_State[param_1] < 0)) {
    Square1SoundQueue = 2;
  }
  if (Enemy_ID[param_1] == 5) {
    PlayerSpriteVarData2[param_1 + 1] = 0xfa;
    Enemy_State[param_1] = Enemy_State[param_1] | 1;
    bVar1 = 0;
    if (SecondaryHardMode == 0) {
      bVar1 = SecondaryHardMode;
    }
    EnemyFrameTimer[param_1] = HammerBroJumpLData[bVar1];
    HammerBroJumpTimer[param_1] = PseudoRandomBitReg[param_1 + 1] | 0xc0;
    bVar1 = MoveHammerBroXDir(param_1);
    return bVar1;
  }
  RXSpd(param_1);
  return param_1;
}



// SMB:e143
// Signature: [X] -> [N, C, r00]

struct_ncr00 PlayerEnemyDiff(byte param_1)

{
  byte bVar1;
  bool bVar2;
  
  bVar2 = PlayerOrSprObject_X_Position[0] <= Enemy_X_Position[param_1];
  bVar1 = Enemy_PageLoc[param_1];
  return (struct_ncr00)
         CONCAT12(Enemy_X_Position[param_1] - PlayerOrSprObject_X_Position[0],
                  CONCAT11(bVar2 && PlayerOrSprObject_PageLoc[0] <= bVar1 ||
                           !bVar2 && PlayerOrSprObject_PageLoc[0] < bVar1,
                           0x7f < (byte)((bVar1 - PlayerOrSprObject_PageLoc[0]) - !bVar2)));
}



// SMB:e14f
// Signature: [X] -> []

void EnemyLanding(byte param_1)

{
  InitVStf(param_1);
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] & 0xf0 | 8;
  return;
}



// SMB:e15b
// Signature: [X] -> [C]

bool SubtEnemyYPos(byte param_1)

{
  return 0x43 < (byte)(Enemy_Y_Position[param_1] + 0x3e);
}



// SMB:e163
// Signature: [X] -> [X]

byte EnemyJump(byte param_1)

{
  byte bVar1;
  bool bVar2;
  struct_axzr02r04r06r07 sVar3;
  
  bVar2 = SubtEnemyYPos(param_1);
  if ((bVar2) && (2 < (byte)(PlayerSpriteVarData2[param_1 + 1] + 2))) {
    sVar3 = ChkUnderEnemy(param_1);
    param_1 = sVar3.x;
    if (!sVar3.z) {
      bVar2 = ChkForNonSolids(sVar3.a);
      if (!bVar2) {
        EnemyLanding(param_1);
        PlayerSpriteVarData2[param_1 + 1] = 0xfd;
      }
    }
  }
  bVar1 = DoEnemySideCheck(param_1);
  return bVar1;
}



// SMB:e185
// Signature: [X] -> [X]

byte HammerBroBGColl(byte param_1)

{
  byte bVar1;
  struct_axzr02r04r06r07 sVar2;
  
  sVar2 = ChkUnderEnemy(param_1);
  bVar1 = sVar2.x;
  if (!sVar2.z) {
    if (sVar2.a == 0x23) {
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



// SMB:e18e
// Signature: [X] -> []

void KillEnemyAboveBlock(byte param_1)

{
  ShellOrBlockDefeat(param_1);
  PlayerSpriteVarData2[param_1 + 1] = 0xfc;
  return;
}



// SMB:e1ae
// Signature: [X] -> [A, X, Z, r02, r04, r06, r07]

struct_axzr02r04r06r07 ChkUnderEnemy(byte param_1)

{
  struct_axzr02r04r06r07 sVar1;
  
  sVar1 = BlockBufferChk_Enemy(0,param_1,0x15);
  return sVar1;
}



// SMB:e1b5
// Signature: [A] -> [Z]

bool ChkForNonSolids(byte param_1)

{
  bool bVar1;
  
  bVar1 = param_1 == 0x26;
  if ((((!bVar1) && (bVar1 = param_1 == 0xc2, !bVar1)) && (bVar1 = param_1 == 0xc3, !bVar1)) &&
     (bVar1 = param_1 == 0x5f, !bVar1)) {
    bVar1 = param_1 == 0x60;
  }
  return bVar1;
}



// SMB:e1c8
// Signature: [X] -> [X]

byte FireballBGCollision(byte param_1)

{
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



// SMB:e22d
// Signature: [X] -> [X]

byte GetFireballBoundBox(byte param_1)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = param_1 + 7;
  bVar2 = BoundingBoxCore(bVar1,2);
  bVar1 = CheckRightScreenBBox(bVar1,bVar2);
  return bVar1;
}



// SMB:e236
// Signature: [X] -> [X]

byte GetMiscBoundBox(byte param_1)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = param_1 + 9;
  bVar2 = BoundingBoxCore(bVar1,6);
  bVar1 = CheckRightScreenBBox(bVar1,bVar2);
  return bVar1;
}



// SMB:e243
// Signature: [X] -> [X]

byte GetEnemyBoundBox(byte param_1)

{
  byte bVar1;
  
  bVar1 = GetMaskedOffScrBits(param_1,0x44,0x48);
  return bVar1;
}



// SMB:e24c
// Signature: [X] -> [X]

byte SmallPlatformBoundBox(byte param_1)

{
  byte bVar1;
  
  bVar1 = GetMaskedOffScrBits(param_1,4,8);
  return bVar1;
}



// SMB:e252
// Signature: [X, Y, r00] -> [X]

byte GetMaskedOffScrBits(byte param_1,byte param_2,byte param_3)

{
  byte bVar1;
  
  bVar1 = (Enemy_PageLoc[param_1] - ScreenEdgeOrLeft_PageLoc[0]) -
          (Enemy_X_Position[param_1] < ScreenEdgeOrLeft_X_Pos[0]);
  if ((bVar1 < 0x80) && ((byte)(bVar1 | Enemy_X_Position[param_1] - ScreenEdgeOrLeft_X_Pos[0]) != 0)
     ) {
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



// SMB:e273
// Signature: [X] -> [X]

byte LargePlatformBoundBox(byte param_1)

{
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



// SMB:e27c
// Signature: [X] -> [X]

byte SetupEOffsetFBBox(byte param_1)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = param_1 + 1;
  bVar2 = BoundingBoxCore(bVar1,1);
  bVar1 = CheckRightScreenBBox(bVar1,bVar2);
  return bVar1;
}



// SMB:e289
// Signature: [X] -> []

void MoveBoundBoxOffscreen(byte param_1)

{
  byte bVar1;
  
  bVar1 = param_1 << 2;
  EnemyBoundingBoxCoord[bVar1] = 0xff;
  EnemyBoundingBoxCoord[bVar1 + 1] = 0xff;
  EnemyBoundingBoxCoord[bVar1 + 2] = 0xff;
  EnemyBoundingBoxCoord[bVar1 + 3] = 0xff;
  return;
}



// SMB:e29c
// Signature: [X, Y] -> [Y]

byte BoundingBoxCore(byte param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  
  bVar1 = PlayerOrSprObject_Rel_YPos[param_2];
  bVar2 = PlayerOrSprObject_Rel_XPos[param_2];
  bVar3 = param_1 * 4;
  bVar4 = PlayerOrSprObj_BoundBoxCtrl[param_1] * 4;
  BoundingBox_UL_Corner_Or_XPos[bVar3] = bVar2 + BoundBoxCtrlData[bVar4];
  BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[bVar3] = bVar2 + BoundBoxCtrlData[bVar4 + 2];
  BoundingBox_UL_Corner_Or_XPos[(byte)(bVar3 + 1)] = bVar1 + BoundBoxCtrlData[(byte)(bVar4 + 1)];
  BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[(byte)(bVar3 + 1)] =
       bVar1 + BoundBoxCtrlData[(byte)(bVar4 + 1) + 2];
  return bVar3;
}



// SMB:e2de
// Signature: [X, Y] -> [X]

byte CheckRightScreenBBox(byte param_1,byte param_2)

{
  byte bVar1;
  bool bVar2;
  
  bVar1 = ScreenEdgeOrLeft_PageLoc[0] + (0x7f < ScreenEdgeOrLeft_X_Pos[0]);
  bVar2 = (byte)(ScreenEdgeOrLeft_X_Pos[0] + 0x80) <= PlayerOrSprObject_X_Position[param_1];
  if (bVar2 && bVar1 <= PlayerOrSprObject_PageLoc[param_1] ||
      !bVar2 && bVar1 < PlayerOrSprObject_PageLoc[param_1]) {
    if (BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2] < 0x80) {
      if (BoundingBox_UL_Corner_Or_XPos[param_2] < 0x80) {
        BoundingBox_UL_Corner_Or_XPos[param_2] = 0xff;
      }
      BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2] = 0xff;
    }
    return ObjectOffset;
  }
  if ((0x7f < BoundingBox_UL_Corner_Or_XPos[param_2]) &&
     (0x9f < BoundingBox_UL_Corner_Or_XPos[param_2])) {
    if (0x7f < BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2]) {
      BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2] = 0;
    }
    BoundingBox_UL_Corner_Or_XPos[param_2] = 0;
  }
  return ObjectOffset;
}



// SMB:e325
// Signature: [Y] -> [C]

bool PlayerCollisionCore(byte param_1)

{
  bool bVar1;
  
  bVar1 = SprObjectCollisionCore(0,param_1);
  return bVar1;
}



// SMB:e327
// Signature: [X, Y] -> [C]

bool SprObjectCollisionCore(byte param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  
  bVar2 = 1;
  do {
    bVar1 = BoundingBox_UL_Corner_Or_XPos[param_2];
    if (bVar1 < BoundingBox_UL_Corner_Or_XPos[param_1]) {
      if (bVar1 < BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_1]) {
        if ((BoundingBox_UL_Corner_Or_XPos[param_1] <=
             BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_1]) &&
           (BoundingBox_UL_Corner_Or_XPos[param_1] >
            BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2])) {
          return BoundingBox_UL_Corner_Or_XPos[param_1] <=
                 BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2];
        }
      }
      else if (((bVar1 != BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_1]) &&
               (bVar1 = BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2],
               BoundingBox_UL_Corner_Or_XPos[param_2] <= bVar1)) &&
              (BoundingBox_UL_Corner_Or_XPos[param_1] > bVar1)) {
        return BoundingBox_UL_Corner_Or_XPos[param_1] <= bVar1;
      }
    }
    else if ((((bVar1 != BoundingBox_UL_Corner_Or_XPos[param_1]) &&
              (BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_1] <= bVar1)) &&
             (bVar1 != BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_1])) &&
            (((bVar1 < BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2] ||
              (bVar1 == BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2])) ||
             (BoundingBox_DR_XPos_Or_BoundingBox_LR_Corner[param_2] <
              BoundingBox_UL_Corner_Or_XPos[param_1])))) {
      return false;
    }
    param_1 += 1;
    param_2 += 1;
    bVar2 -= 1;
    if (0x7f < bVar2) {
      return true;
    }
  } while( true );
}



// SMB:e388
// Signature: [A, X, Y] -> [A, X, Z, r02, r04, r06, r07]

struct_axzr02r04r06r07 BlockBufferChk_Enemy(byte param_1,byte param_2,byte param_3)

{
  struct_azr02r04r06r07 sVar1;
  byte bStack0000;
  
  bStack0000 = param_1;
  sVar1 = BlockBufferCollision(param_1,param_2 + 1,param_3);
  return (struct_axzr02r04r06r07)
         CONCAT34((int3)((uint6)sVar1 >> 0x18),
                  CONCAT22(CONCAT11(sVar1.r02,sVar1.a == 0),CONCAT11(ObjectOffset,sVar1.a)));
}



// SMB:e39c
// Signature: [X] -> [A, X, Z]

struct_axz BlockBufferChk_FBall(byte param_1)

{
  struct_azr02r04r06r07 sVar1;
  
  sVar1 = BlockBufferCollision(0,param_1 + 7,0x1a);
  return (struct_axz)CONCAT12(sVar1.a == 0,CONCAT11(ObjectOffset,sVar1.a));
}



// SMB:e3e8
// Signature: [Y] -> [A, Y, r02, r04, r06, r07]

struct_ayr02r04r06r07 BlockBufferColli_Feet(byte param_1)

{
  byte bVar1;
  struct_azr02r04r06r07 sVar2;
  
  bVar1 = param_1 + 1;
  sVar2 = BlockBufferCollision(0,0,bVar1);
  return (struct_ayr02r04r06r07)
         CONCAT33((uint3)(((uint6)sVar2 & 0xff0000ff0000) >> 0x18) |
                  (uint3)(ushort)((uint6)sVar2 >> 0x18),
                  (uint3)((uint6)sVar2 & 0xff0000ff0000) |
                  (uint3)(SUB62(sVar2,0) & 0xff | (ushort)bVar1 << 8));
}



// SMB:e3e9
// Signature: [Y] -> [A, Z, r02, r04, r06, r07]

struct_azr02r04r06r07 BlockBufferColli_Head(byte param_1)

{
  struct_azr02r04r06r07 sVar1;
  
  sVar1 = BlockBufferCollision(0,0,param_1);
  return sVar1;
}



// SMB:e3ec
// Signature: [Y] -> [A, Z, r02, r04, r06, r07]

struct_azr02r04r06r07 BlockBufferColli_Side(byte param_1)

{
  struct_azr02r04r06r07 sVar1;
  
  sVar1 = BlockBufferCollision(1,0,param_1);
  return sVar1;
}



// SMB:e3f0
// Signature: [A, X, Y] -> [A, Z, r02, r04, r06, r07]

struct_azr02r04r06r07 BlockBufferCollision(byte param_1,byte param_2,byte param_3)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  struct_r06r07i sVar4;
  byte bStack0000;
  
  bStack0000 = param_1;
  sVar4 = GetBlockBufferAddr((byte)((byte)(BlockBuffer_X_Adder[param_3] +
                                          PlayerOrSprObject_X_Position[param_2]) >> 1 |
                                   (PlayerOrSprObject_PageLoc[param_2] +
                                   CARRY1(BlockBuffer_X_Adder[param_3],
                                          PlayerOrSprObject_X_Position[param_2])) * -0x80) >> 3);
  bVar2 = (PlayerOrSprObject_Y_Position[param_2] + BlockBuffer_Y_Adder[param_3] & 0xf0) - 0x20;
  cVar1 = RAM(SUB32(sVar4,0) + (ushort)bVar2);
  if (bStack0000 == 0) {
    bVar3 = PlayerOrSprObject_Y_Position[param_2];
  }
  else {
    bVar3 = PlayerOrSprObject_X_Position[param_2];
  }
  return (struct_azr02r04r06r07)
         (CONCAT33(CONCAT12(sVar4.r07,CONCAT11(sVar4.r06,bVar3)),
                   CONCAT12(bVar2,CONCAT11(cVar1 == 0,cVar1))) & 0xffff0fffffff);
}



// SMB:e435
// Signature: [Y] -> []

void DrawVine(byte param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = Enemy_SprDataOffset[VineObjOffset[param_1]];
  bVar3 = SixSpriteStacker(Enemy_Rel_YPos + VineYPosAdder[param_1],bVar4,bVar4);
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



// SMB:e4ae
// Signature: [A, Y, r02] -> [Y]

byte SixSpriteStacker(byte param_1,byte param_2,byte param_3)

{
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



// SMB:e4dc
// Signature: [X] -> [X]

byte DrawHammer(byte param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  bVar1 = Misc_SprDataOffset[param_1];
  if ((TimerControl == 0) && ((Misc_State[param_1] & 0x7f) == 1)) {
    bVar3 = FrameCounter >> 2 & 3;
  }
  else {
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
    DumpTwoSpr(0xf8,bVar1);
  }
  return bVar3;
}



// SMB:e54b
// Signature: [X] -> []

void FlagpoleGfxHandler(byte param_1)

{
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
  DumpTwoSpr(bVar3,bVar4);
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
    DrawOneSpriteRow(FlagpoleScoreNumTiles[bVar1 + 1],bVar1,bVar4 + 0xc,FlagpoleScoreNumTiles[bVar1]
                     ,bVar3,1,1,bVar2);
  }
  if ((Enemy_OffscreenBits & 0xe) != 0) {
    MoveSixSpritesOffscreen(Enemy_SprDataOffset[ObjectOffset]);
    return;
  }
  return;
}



// SMB:e5b3
// Signature: [Y] -> []

void MoveSixSpritesOffscreen(byte param_1)

{
  DumpSixSpr(0xf8,param_1);
  return;
}



// SMB:e5b5
// Signature: [A, Y] -> []

void DumpSixSpr(byte param_1,byte param_2)

{
  Sprite_Data[param_2 + 0x14] = param_1;
  Sprite_Data[param_2 + 0x10] = param_1;
  Sprite_Data[param_2 + 0xc] = param_1;
  Sprite_Data[param_2 + 8] = param_1;
  Sprite_Data[param_2 + 4] = param_1;
  Sprite_Data[param_2] = param_1;
  return;
}



// SMB:e5bb
// Signature: [A, Y] -> []

void DumpFourSpr(byte param_1,byte param_2)

{
  Sprite_Data[param_2 + 0xc] = param_1;
  Sprite_Data[param_2 + 8] = param_1;
  Sprite_Data[param_2 + 4] = param_1;
  Sprite_Data[param_2] = param_1;
  return;
}



// SMB:e5be
// Signature: [A, Y] -> []

void DumpThreeSpr(byte param_1,byte param_2)

{
  Sprite_Data[param_2 + 8] = param_1;
  Sprite_Data[param_2 + 4] = param_1;
  Sprite_Data[param_2] = param_1;
  return;
}



// SMB:e5c1
// Signature: [A, Y] -> []

void DumpTwoSpr(byte param_1,byte param_2)

{
  Sprite_Data[param_2 + 4] = param_1;
  Sprite_Data[param_2] = param_1;
  return;
}



// SMB:e5c8
// Signature: [X] -> [X]

byte DrawLargePlatform(byte param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  char cStack0000;
  
  bVar2 = SixSpriteStacker(Enemy_Rel_XPos,Enemy_SprDataOffset[param_1] + 3,
                           Enemy_SprDataOffset[param_1]);
  bVar1 = Enemy_Y_Position[ObjectOffset];
  bVar3 = ObjectOffset;
  DumpFourSpr(bVar1,bVar2);
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
  DumpSixSpr(bVar1,bVar3);
  DumpSixSpr(2,bVar3 + 1);
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



// SMB:e686
// Signature: [X] -> [X]

byte JCoinGfxHandler(byte param_1)

{
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
    DumpTwoSpr(JumpingCoinTiles[FrameCounter >> 1 & 3],bVar2);
    Sprite_Data[(byte)(bVar2 - 1) + 2] = 2;
    Sprite_Data[(byte)(bVar2 - 1) + 6] = 0x82;
    param_1 = ObjectOffset;
  }
  else {
    if (!(bool)(FrameCounter & 1)) {
      Misc_Y_Position[param_1] = Misc_Y_Position[param_1] - 1;
    }
    DumpTwoSpr(Misc_Y_Position[param_1],bVar2);
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



// SMB:e6d2
// Signature: [] -> [X]

byte DrawPowerUp(void)

{
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
    sVar9 = DrawOneSpriteRow(PowerUpGfxTable[bVar7 + 1],bVar7,bVar8,PowerUpGfxTable[bVar7],bVar6,
                             bVar2,bVar5,bVar3);
    bVar1 = Enemy_SprDataOffset[5];
    bVar6 = sVar9.r02;
    bVar8 = sVar9.y;
    bVar7 = sVar9.x;
    bVar4 -= 1;
  } while (bVar4 < 0x80);
  if ((bStack0000 != 0) && (bStack0000 != 3)) {
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



// SMB:e87d
// Signature: [X] -> [X]

byte EnemyGfxHandler(byte param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  bool bVar6;
  struct_xyr02 sVar7;
  
  bVar5 = Enemy_Y_Position[param_1];
  MysterySpriteThing1 = Enemy_SprDataOffset[param_1];
  VerticalFlipFlag = 0;
  bVar1 = Enemy_MovingDir[param_1];
  bVar3 = Enemy_SprAttrib[param_1];
  if (((Enemy_ID[param_1] == 0xd) && (PlayerSpriteVarData1[param_1 + 1] < 0x80)) &&
     (EnemyFrameTimer[param_1] != 0)) {
    return param_1;
  }
  MysterySpriteThing3 = Enemy_State[param_1];
  MysterySpriteThing2 = MysterySpriteThing3 & 0x1f;
  MysterySpriteThing4 = Enemy_ID[param_1];
  if (MysterySpriteThing4 == 0x35) {
    MysterySpriteThing2 = 0;
    bVar1 = 1;
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
  if ((MysterySpriteThing4 == 0xc) && (PlayerSpriteVarData2[ObjectOffset + 1] < 0x80)) {
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
      bVar1 ^= 3;
    }
  }
  bVar3 = EnemyAttributeData[MysterySpriteThing4] | bVar3;
  bVar4 = EnemyGfxTableOffsets[MysterySpriteThing4];
  if (BowserGfxFlag == 0) {
    if (bVar4 != 0x24) {
      if (bVar4 != 0x90) {
        if (((MysterySpriteThing4 < 4) && (1 < MysterySpriteThing2)) &&
           (bVar4 = 0x5a, MysterySpriteThing4 == 2)) {
          bVar4 = 0x7e;
          bVar5 += 1;
        }
        if (MysterySpriteThing2 == 4) {
          bVar4 = 0x72;
          bVar2 = bVar5 + 1;
          if (MysterySpriteThing4 != 2) {
            bVar4 = 0x66;
            bVar2 = bVar5 + 2;
          }
          bVar5 = bVar2;
          if ((MysterySpriteThing4 == 6) && (bVar4 = 0x54, (MysterySpriteThing3 & 0x20) == 0)) {
            bVar4 = 0x8a;
            bVar5 -= 1;
          }
        }
        goto CheckForHammerBro;
      }
      if (((MysterySpriteThing3 & 0x20) == 0) && (FrenzyEnemyTimer < 0x10)) {
        bVar4 = 0x96;
      }
      goto CheckDefeatedState;
    }
    if (MysterySpriteThing2 == 5) {
      bVar4 = 0x30;
      bVar1 = 2;
      MysterySpriteThing2 = 5;
    }
CheckForHammerBro:
    if (MysterySpriteThing4 == 5) {
      if (MysterySpriteThing3 != 0) {
        if ((MysterySpriteThing3 & 8) == 0) goto CheckDefeatedState;
        bVar4 = 0xb4;
      }
CheckToAnimateEnemy:
      if ((((MysterySpriteThing4 != 6) && (MysterySpriteThing4 != 8)) &&
          (MysterySpriteThing4 != 0xc)) && (MysterySpriteThing4 < 0x18)) {
        if (MysterySpriteThing4 == 0x15) {
          if (WorldNumber < 7) {
            bVar4 = 0xa2;
            MysterySpriteThing2 = 3;
          }
        }
        else if ((FrameCounter & EnemyAnimTimingBMask[0]) == 0) goto CheckAnimationStop;
      }
    }
    else {
      if (bVar4 == 0x48) goto CheckToAnimateEnemy;
      if (EnemyIntervalTimer[ObjectOffset] < 5) {
        if (bVar4 != 0x3c) goto CheckToAnimateEnemy;
        if (EnemyIntervalTimer[ObjectOffset] == 1) goto CheckDefeatedState;
        bVar5 += 3;
CheckAnimationStop:
        if ((MysterySpriteThing3 & 0xa0 | TimerControl) == 0) {
          bVar4 += 6;
        }
      }
    }
CheckDefeatedState:
    if (((MysterySpriteThing3 & 0x20) != 0) && (3 < MysterySpriteThing4)) {
      VerticalFlipFlag = 1;
      MysterySpriteThing2 = 0;
    }
  }
  else if (BowserGfxFlag == 1) {
    if (0x7f < BowserBodyControls) {
      bVar4 = 0xde;
    }
    if ((MysterySpriteThing3 & 0x20) != 0) {
FlipBowserOver:
      VerticalFlipFlag = bVar4;
    }
  }
  else {
    if ((BowserBodyControls & 1) != 0) {
      bVar4 = 0xe4;
    }
    if ((MysterySpriteThing3 & 0x20) != 0) {
      bVar5 -= 0x10;
      goto FlipBowserOver;
    }
  }
  bVar2 = Enemy_Rel_XPos;
  sVar7 = DrawEnemyObjRow(bVar4,MysterySpriteThing1,bVar5,bVar1,bVar3,Enemy_Rel_XPos);
  sVar7 = DrawEnemyObjRow(sVar7.x,sVar7.y,sVar7.r02,bVar1,bVar3,bVar2);
  DrawEnemyObjRow(sVar7.x,sVar7.y,sVar7.r02,bVar1,bVar3,bVar2);
  bVar5 = Enemy_SprDataOffset[ObjectOffset];
  if (MysterySpriteThing4 == 8) {
SkipToOffScrChk:
    bVar5 = SprObjectOffscrChk();
    return bVar5;
  }
  if (VerticalFlipFlag != 0) {
    bVar3 = bVar5 + 2;
    DumpSixSpr(Sprite_Data[bVar5 + 2] | 0x80,bVar3);
    bVar5 = bVar3 - 2;
    bVar1 = bVar5;
    if (((MysterySpriteThing4 != 5) && (MysterySpriteThing4 != 0x11)) &&
       (MysterySpriteThing4 < 0x15)) {
      bVar1 = bVar3 + 6;
    }
    bVar3 = Sprite_Data[bVar1 + 1];
    bVar4 = Sprite_Data[bVar1 + 5];
    Sprite_Data[bVar1 + 1] = Sprite_Data[bVar5 + 0x11];
    Sprite_Data[bVar1 + 5] = Sprite_Data[bVar5 + 0x15];
    Sprite_Data[bVar5 + 0x15] = bVar4;
    Sprite_Data[bVar5 + 0x11] = bVar3;
  }
  bVar1 = MysterySpriteThing2;
  if (BowserGfxFlag != 0) goto SkipToOffScrChk;
  if (MysterySpriteThing4 == 5) {
    bVar5 = SprObjectOffscrChk();
    return bVar5;
  }
  if (((MysterySpriteThing4 != 7) && (MysterySpriteThing4 != 0xd)) && (MysterySpriteThing4 != 0xc))
  {
    if ((MysterySpriteThing4 == 0x12) && (MysterySpriteThing2 != 5)) goto CheckToMirrorLakitu;
    if (MysterySpriteThing4 == 0x15) {
      Sprite_Data[bVar5 + 0x16] = 0x42;
    }
    if (bVar1 < 2) goto CheckToMirrorLakitu;
  }
  if (BowserGfxFlag == 0) {
    bVar3 = Sprite_Data[bVar5 + 2] & 0xa3;
    Sprite_Data[bVar5 + 2] = bVar3;
    Sprite_Data[bVar5 + 10] = bVar3;
    Sprite_Data[bVar5 + 0x12] = bVar3;
    bVar4 = bVar3 | 0x40;
    if (bVar1 == 5) {
      bVar4 = bVar3 | 0xc0;
    }
    Sprite_Data[bVar5 + 6] = bVar4;
    Sprite_Data[bVar5 + 0xe] = bVar4;
    Sprite_Data[bVar5 + 0x16] = bVar4;
    if (bVar1 == 4) {
      bVar1 = Sprite_Data[bVar5 + 10];
      bVar3 = bVar1 | 0x80;
      Sprite_Data[bVar5 + 10] = bVar3;
      Sprite_Data[bVar5 + 0x12] = bVar3;
      bVar1 |= 0xc0;
      Sprite_Data[bVar5 + 0xe] = bVar1;
      Sprite_Data[bVar5 + 0x16] = bVar1;
    }
  }
CheckToMirrorLakitu:
  if (MysterySpriteThing4 == 0x11) {
    if (VerticalFlipFlag == 0) {
      Sprite_Data[bVar5 + 0x12] = Sprite_Data[bVar5 + 0x12] & 0x81;
      bVar1 = Sprite_Data[bVar5 + 0x16] | 0x41;
      Sprite_Data[bVar5 + 0x16] = bVar1;
      bVar6 = 0xf < FrenzyEnemyTimer;
      if (bVar6) {
        bVar5 = SprObjectOffscrChk();
        return bVar5;
      }
      Sprite_Data[bVar5 + 0xe] = bVar1;
      Sprite_Data[bVar5 + 10] = bVar1 & 0x81;
      if (!bVar6) {
        bVar5 = SprObjectOffscrChk();
        return bVar5;
      }
    }
    Sprite_Data[bVar5 + 2] = Sprite_Data[bVar5 + 2] & 0x81;
    Sprite_Data[bVar5 + 6] = Sprite_Data[bVar5 + 6] | 0x41;
  }
  if (MysterySpriteThing4 < 0x18) {
    bVar5 = SprObjectOffscrChk();
    return bVar5;
  }
  Sprite_Data[bVar5 + 10] = 0x82;
  Sprite_Data[bVar5 + 0x12] = 0x82;
  Sprite_Data[bVar5 + 0xe] = 0xc2;
  Sprite_Data[bVar5 + 0x16] = 0xc2;
  bVar5 = SprObjectOffscrChk();
  return bVar5;
}



// SMB:eb64
// Signature: [] -> [X]

byte SprObjectOffscrChk(void)

{
  byte bVar1;
  byte bVar2;
  byte bStack0000;
  
  bStack0000 = Enemy_OffscreenBits >> 3;
  bVar1 = ObjectOffset;
  if ((Enemy_OffscreenBits >> 2 & 1) != 0) {
    MoveESprColOffscreen(4,ObjectOffset);
  }
  bVar2 = bStack0000 & 1;
  bStack0000 >>= 1;
  if (bVar2 != 0) {
    MoveESprColOffscreen(0,bVar1);
  }
  bVar2 = bStack0000 >> 1;
  bStack0000 >>= 2;
  if ((bVar2 & 1) != 0) {
    MoveESprRowOffscreen(0x10,bVar1);
  }
  bVar2 = bStack0000 & 1;
  bStack0000 >>= 1;
  if (bVar2 != 0) {
    MoveESprRowOffscreen(8,bVar1);
  }
  if ((bStack0000 & 1) != 0) {
    MoveESprRowOffscreen(bStack0000 >> 1,bVar1);
    if ((Enemy_ID[bVar1] != 0xc) && (Enemy_Y_HighPos[bVar1] == 2)) {
      EraseEnemyObject(bVar1);
    }
  }
  return bVar1;
}



// SMB:ebaa
// Signature: [X, Y, r02, r03, r04, r05] -> [X, Y, r02]

struct_xyr02
DrawEnemyObjRow(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6)

{
  struct_xyr02 sVar1;
  
  sVar1 = DrawOneSpriteRow(EnemyGraphicsTable[param_1 + 1],param_1,param_2,
                           EnemyGraphicsTable[param_1],param_3,param_4,param_5,param_6);
  return sVar1;
}



// SMB:ebb2
// Signature: [A, X, Y, r00, r02, r03, r04, r05] -> [X, Y, r02]

struct_xyr02
DrawOneSpriteRow(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,
                byte param_7,byte param_8)

{
  struct_xyr02 sVar1;
  
  sVar1 = DrawSpriteObject(param_2,param_3,param_4,param_1,param_5,param_6,param_7,param_8);
  return sVar1;
}



// SMB:ebb7
// Signature: [A, X] -> []

void MoveESprRowOffscreen(byte param_1,byte param_2)

{
  DumpTwoSpr(0xf8,param_1 + Enemy_SprDataOffset[param_2]);
  return;
}



// SMB:ebc1
// Signature: [A, X] -> []

void MoveESprColOffscreen(byte param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  
  bVar2 = param_1 + Enemy_SprDataOffset[param_2];
  bVar1 = MoveColOffscreen(bVar2);
  Sprite_Data[bVar2 + 0x10] = bVar1;
  return;
}



// SMB:ebd1
// Signature: [X] -> [X]

byte DrawBlock(byte param_1)

{
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
    sVar8 = DrawOneSpriteRow(DefaultBlockObjTiles[bVar6 + 1],bVar6,bVar7,DefaultBlockObjTiles[bVar6]
                             ,bVar1,bVar4,bVar2,bVar3);
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
  if (Block_Metatile[bVar5] == 0xc4) {
    bVar7 += 1;
    DumpFourSpr(0x87,bVar7);
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
  ChkLeftCo(bVar4,bVar7);
  return bVar5;
}



// SMB:ec46
// Signature: [A, Y] -> []

void ChkLeftCo(byte param_1,byte param_2)

{
  if ((param_1 & 8) != 0) {
    MoveColOffscreen(param_2);
    return;
  }
  return;
}



// SMB:ec4a
// Signature: [Y] -> [A]

byte MoveColOffscreen(byte param_1)

{
  Sprite_Data[param_1] = 0xf8;
  Sprite_Data[param_1 + 8] = 0xf8;
  return 0xf8;
}



// SMB:ec53
// Signature: [X] -> []

void DrawBrickChunks(byte param_1)

{
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
  DumpFourSpr(bVar2,bVar4);
  bVar4 += 1;
  DumpFourSpr((FrameCounter & 0xc) << 4 | bVar1,bVar4);
  bVar4 -= 2;
  DumpTwoSpr(Block_Rel_YPos,bVar4);
  Sprite_Data[bVar4 + 3] = Block_Rel_XPos;
  bVar1 = Block_Orig_XPos[param_1] - ScreenEdgeOrLeft_X_Pos[0];
  cVar3 = (bVar1 - Block_Rel_XPos) + bVar1 + (Block_Rel_XPos <= bVar1);
  Sprite_Data[bVar4 + 7] =
       cVar3 + 6 +
       (CARRY1(bVar1 - Block_Rel_XPos,bVar1) || Block_Rel_XPos <= bVar1 && cVar3 == 0);
  bVar2 = Block_Rel_YPos_2;
  Sprite_Data[bVar4 + 8] = Block_Rel_YPos_2;
  Sprite_Data[bVar4 + 0xc] = bVar2;
  Sprite_Data[bVar4 + 0xb] = Block_Rel_XPos_2;
  cVar3 = (bVar1 - Block_Rel_XPos_2) + bVar1 + (Block_Rel_XPos_2 <= bVar1);
  Sprite_Data[bVar4 + 0xf] =
       cVar3 + 6 +
       (CARRY1(bVar1 - Block_Rel_XPos_2,bVar1) || Block_Rel_XPos_2 <= bVar1 && cVar3 == 0);
  ChkLeftCo(Block_OffscreenBits,bVar4);
  if ((char)Block_OffscreenBits < 0) {
    DumpTwoSpr(0xf8,bVar4);
  }
  if ((0x7f < bVar1) && (Sprite_Data[bVar4 + 7] <= Sprite_Data[bVar4 + 3])) {
    Sprite_Data[bVar4 + 4] = 0xf8;
    Sprite_Data[bVar4 + 0xc] = 0xf8;
  }
  return;
}



// SMB:ecde
// Signature: [X] -> []

void DrawFireball(byte param_1)

{
  byte bVar1;
  
  bVar1 = FBall_SprDataOffset[param_1];
  Sprite_Data[bVar1] = Fireball_Rel_YPos;
  Sprite_Data[bVar1 + 3] = Fireball_Rel_XPos;
  DrawFirebar(bVar1);
  return;
}



// SMB:eced
// Signature: [Y] -> []

void DrawFirebar(byte param_1)

{
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



// SMB:ed09
// Signature: [X] -> []

void DrawExplosion_Fireball(byte param_1)

{
  byte bVar1;
  
  bVar1 = Fireball_State[param_1];
  Fireball_State[param_1] = Fireball_State[param_1] + 1;
  bVar1 = bVar1 >> 1 & 7;
  if (bVar1 < 3) {
    DrawExplosion_Fireworks(bVar1,AltOrBlock_SprDataOffset[param_1]);
    return;
  }
  Fireball_State[param_1] = 0;
  return;
}



// SMB:ed17
// Signature: [A, Y] -> [X]

byte DrawExplosion_Fireworks(byte param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = param_2 + 1;
  DumpFourSpr(ExplosionTiles[param_1],bVar4);
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



// SMB:ed66
// Signature: [X] -> [X]

byte DrawSmallPlatform(byte param_1)

{
  byte bVar1;
  byte bVar2;
  byte bStack0000;
  
  bVar2 = Enemy_SprDataOffset[param_1] + 1;
  DumpSixSpr(0x5b,bVar2);
  bVar2 += 1;
  DumpSixSpr(2,bVar2);
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
  DumpThreeSpr(bVar1,bVar2);
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



// SMB:ede1
// Signature: [X] -> []

void DrawBubble(byte param_1)

{
  byte bVar1;
  
  if ((PlayerOrSprObject_Y_HighPos[0] == 1) && ((Bubble_OffscreenBits & 8) == 0)) {
    bVar1 = Bubble_SprDataOffset[param_1];
    Sprite_Data[bVar1 + 3] = Bubble_Rel_XPos;
    Sprite_Data[bVar1] = Bubble_Rel_YPos;
    Sprite_Data[bVar1 + 1] = 0x74;
    Sprite_Data[bVar1 + 2] = 2;
  }
  return;
}



// SMB:eee9
// Signature: [] -> []

void PlayerGfxHandler(void)

{
  byte bVar1;
  byte abVar2 [1];
  
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
    bVar1 = FrameCounter & 4;
    if (bVar1 == 0) {
      abVar2[0] = PlayerOrSprDataOffset[0];
      if (!(bool)(PlayerFacingDir & 1)) {
        abVar2[0] = PlayerOrSprDataOffset[0] + 4;
      }
      if (PlayerSize != 0) {
        if (Sprite_Data[abVar2[0] + 0x19] == PlayerGraphicsTable[158]) {
          return;
        }
        bVar1 = 1;
      }
      Sprite_Data[abVar2[0] + 0x19] = SwimKickTileNum[bVar1];
    }
  }
  return;
}



// SMB:ef34
// Signature: [] -> []

void FindPlayerAction(void)

{
  byte bVar1;
  
  bVar1 = ProcessPlayerAction();
  PlayerGfxProcessing(bVar1);
  return;
}



// SMB:ef45
// Signature: [A] -> []

void PlayerGfxProcessing(byte param_1)

{
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
  bVar1 = PlayerOrSprObject_OffscrBits[0] >> 4;
  bVar2 = 3;
  bVar3 = PlayerOrSprDataOffset[0] + 0x18;
  do {
    bVar5 = bVar1 & 1;
    bVar1 >>= 1;
    if (bVar5 != 0) {
      DumpTwoSpr(0xf8,bVar3);
    }
    bVar3 -= 8;
    bVar2 -= 1;
  } while (bVar2 < 0x80);
  return;
}



// SMB:efa4
// Signature: [] -> []

void DrawPlayer_Intermediate(void)

{
  DrawPlayerLoop(0xb8,4,IntermediatePlayerData[0],IntermediatePlayerData[1],
                 IntermediatePlayerData[2],IntermediatePlayerData[3],IntermediatePlayerData[5]);
  Sprite_Data[34] = Sprite_Data[38] | 0x40;
  return;
}



// SMB:efbe
// Signature: [A] -> []

void RenderPlayerSub(byte param_1)

{
  Player_Pos_ForScroll = PlayerOrSprObject_Rel_XPos[0];
  DrawPlayerLoop(PlayerGfxOffset,PlayerOrSprDataOffset[0],PlayerOrSprObject_Rel_YPos[0],
                 PlayerFacingDir,Player_SprAttrib,PlayerOrSprObject_Rel_XPos[0],param_1);
  return;
}



// SMB:efdc
// Signature: [X, Y, r02, r03, r04, r05, r07] -> []

void DrawPlayerLoop(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,
                   byte param_7)

{
  struct_xyr02 sVar1;
  
  do {
    sVar1 = DrawOneSpriteRow(PlayerGraphicsTable[param_1 + 1],param_1,param_2,
                             PlayerGraphicsTable[param_1],param_3,param_4,param_5,param_6);
    param_3 = sVar1.r02;
    param_2 = sVar1.y;
    param_1 = sVar1.x;
    param_7 -= 1;
  } while (param_7 != 0);
  return;
}



// SMB:efec
// Signature: [] -> [A]

byte ProcessPlayerAction(void)

{
  byte bVar1;
  
  if (Player_State == 3) {
    bVar1 = 5;
    if (PlayerSpriteVarData2[0] != 0) {
      bVar1 = GetGfxOffsetAdder(5);
      bVar1 = ThreeFrameExtent(bVar1);
      return bVar1;
    }
  }
  else {
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
    }
    else {
      bVar1 = 6;
      if ((CrouchingFlag == 0) && (bVar1 = 2, (PlayerSpriteVarData1[0] | Left_Right_Buttons) != 0))
      {
        if ((Player_XSpeedAbsolute < 9) || ((Player_MovingDir & PlayerFacingDir) != 0)) {
          bVar1 = GetGfxOffsetAdder(4);
          bVar1 = FourFrameExtent(bVar1);
          return bVar1;
        }
        bVar1 = 3;
      }
    }
  }
  bVar1 = GetGfxOffsetAdder(bVar1);
  PlayerAnimCtrl = 0;
  return PlayerGfxTblOffsets[bVar1];
}



// SMB:f062
// Signature: [Y] -> [A]

byte GetCurrentAnimOffset(byte param_1)

{
  return (PlayerAnimCtrl * 8 + PlayerGfxTblOffsets[param_1]) - ((char)(PlayerAnimCtrl << 2) >> 7)
  ;
}



// SMB:f068
// Signature: [Y] -> [A]

byte FourFrameExtent(byte param_1)

{
  byte bVar1;
  
  bVar1 = AnimationControl(3,param_1);
  return bVar1;
}



// SMB:f06d
// Signature: [Y] -> [A]

byte ThreeFrameExtent(byte param_1)

{
  byte bVar1;
  
  bVar1 = AnimationControl(2,param_1);
  return bVar1;
}



// SMB:f06f
// Signature: [A, Y] -> [A]

byte AnimationControl(byte param_1,byte param_2)

{
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



// SMB:f091
// Signature: [Y] -> [Y]

byte GetGfxOffsetAdder(byte param_1)

{
  if (PlayerSize != 0) {
    param_1 += 8;
  }
  return param_1;
}



// SMB:f0b0
// Signature: [] -> [A]

byte HandleChangeSize(void)

{
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
  return (ChangeSizeOffsetAdder[PlayerAnimCtrl] * 8 + PlayerGfxTblOffsets[15]) -
         ((char)(ChangeSizeOffsetAdder[PlayerAnimCtrl] << 2) >> 7);
}



// SMB:f0e9
// Signature: [] -> []

void ChkForPlayerAttrib(void)

{
  byte abVar1 [1];
  
  abVar1[0] = PlayerOrSprDataOffset[0];
  if (GameEngineSubroutine != 0xb) {
    if (((PlayerGfxOffset == 0x50) || (PlayerGfxOffset == 0xb8)) || (PlayerGfxOffset == 0xc0))
    goto C_S_IGAtt;
    if (PlayerGfxOffset != 200) {
      return;
    }
  }
  Sprite_Data[PlayerOrSprDataOffset[0] + 0x12] = Sprite_Data[PlayerOrSprDataOffset[0] + 0x12] & 0x3f
  ;
  Sprite_Data[abVar1[0] + 0x16] = Sprite_Data[abVar1[0] + 0x16] & 0x3f | 0x40;
C_S_IGAtt:
  Sprite_Data[abVar1[0] + 0x1a] = Sprite_Data[abVar1[0] + 0x1a] & 0x3f;
  Sprite_Data[abVar1[0] + 0x1e] = Sprite_Data[abVar1[0] + 0x1e] & 0x3f | 0x40;
  return;
}



// SMB:f12a
// Signature: [] -> [Y]

byte RelativePlayerPosition(void)

{
  byte bVar1;
  
  bVar1 = 0;
  GetObjRelativePosition(0,0);
  return bVar1;
}



// SMB:f131
// Signature: [X] -> [X]

byte RelativeBubblePosition(byte param_1)

{
  byte bVar1;
  
  bVar1 = GetProperObjOffset(param_1,1);
  GetObjRelativePosition(bVar1,3);
  return ObjectOffset;
}



// SMB:f13b
// Signature: [X] -> [X]

byte RelativeFireballPosition(byte param_1)

{
  byte bVar1;
  
  bVar1 = GetProperObjOffset(param_1,0);
  GetObjRelativePosition(bVar1,2);
  return ObjectOffset;
}



// SMB:f148
// Signature: [X] -> [X]

byte RelativeMiscPosition(byte param_1)

{
  byte bVar1;
  
  bVar1 = GetProperObjOffset(param_1,2);
  GetObjRelativePosition(bVar1,6);
  return ObjectOffset;
}



// SMB:f152
// Signature: [X] -> [A, X, r00]

struct_axr00 RelativeEnemyPosition(byte param_1)

{
  struct_axr00 sVar1;
  
  sVar1 = VariableObjOfsRelPos(1,param_1,1);
  return sVar1;
}



// SMB:f159
// Signature: [X] -> [X]

byte RelativeBlockPosition(byte param_1)

{
  char cVar1;
  struct_axr00 sVar2;
  
  cVar1 = 4;
  sVar2 = VariableObjOfsRelPos(9,param_1,4);
  sVar2 = VariableObjOfsRelPos(9,sVar2.x + 2,cVar1 + 1);
  return sVar2.x;
}



// SMB:f165
// Signature: [A, X, Y] -> [A, X, r00]

struct_axr00 VariableObjOfsRelPos(byte param_1,byte param_2,byte param_3)

{
  byte bVar1;
  
  bVar1 = GetObjRelativePosition(param_1 + param_2,param_3);
  return (struct_axr00)CONCAT12(param_2,CONCAT11(ObjectOffset,bVar1));
}



// SMB:f171
// Signature: [X, Y] -> [A]

byte GetObjRelativePosition(byte param_1,byte param_2)

{
  byte bVar1;
  
  PlayerOrSprObject_Rel_YPos[param_2] = PlayerOrSprObject_Y_Position[param_1];
  bVar1 = PlayerOrSprObject_X_Position[param_1] - ScreenEdgeOrLeft_X_Pos[0];
  PlayerOrSprObject_Rel_XPos[param_2] = bVar1;
  return bVar1;
}



// SMB:f180
// Signature: [] -> []

void GetPlayerOffscreenBits(void)

{
  GetOffScreenBitsSet(0,0);
  return;
}



// SMB:f187
// Signature: [X] -> [X]

byte GetFireballOffscreenBits(byte param_1)

{
  byte bVar1;
  struct_xyi sVar2;
  
  bVar1 = GetProperObjOffset(param_1,0);
  sVar2 = GetOffScreenBitsSet(bVar1,2);
  return sVar2.x;
}



// SMB:f191
// Signature: [X] -> [X]

byte GetBubbleOffscreenBits(byte param_1)

{
  byte bVar1;
  struct_xyi sVar2;
  
  bVar1 = GetProperObjOffset(param_1,1);
  sVar2 = GetOffScreenBitsSet(bVar1,3);
  return sVar2.x;
}



// SMB:f19b
// Signature: [X] -> [X]

byte GetMiscOffscreenBits(byte param_1)

{
  byte bVar1;
  struct_xyi sVar2;
  
  bVar1 = GetProperObjOffset(param_1,2);
  sVar2 = GetOffScreenBitsSet(bVar1,6);
  return sVar2.x;
}



// SMB:f1a8
// Signature: [X, Y] -> [X]

byte GetProperObjOffset(byte param_1,byte param_2)

{
  return param_1 + ObjOffsetData[param_2];
}



// SMB:f1af
// Signature: [X] -> [X, Y]

struct_xyi GetEnemyOffscreenBits(byte param_1)

{
  struct_xyi sVar1;
  
  sVar1 = GetOffScreenBitsSet(param_1 + 1,1);
  return sVar1;
}



// SMB:f1b6
// Signature: [X] -> [X]

byte GetBlockOffscreenBits(byte param_1)

{
  struct_xyi sVar1;
  
  sVar1 = GetOffScreenBitsSet(param_1 + 9,4);
  return sVar1.x;
}



// SMB:f1c0
// Signature: [X, Y] -> [X, Y]

struct_xyi GetOffScreenBitsSet(byte param_1,byte param_2)

{
  struct_ar00i sVar1;
  byte bStack0000;
  
  bStack0000 = param_2;
  sVar1 = RunOffscrBitsSubs(param_1);
  PlayerOrSprObject_OffscrBits[bStack0000] = sVar1.a << 4 | sVar1.r00;
  return (struct_xyi)((uint3)sVar1 & 0xff0000 | (uint3)CONCAT11(bStack0000,ObjectOffset));
}



// SMB:f1d7
// Signature: [X] -> [A, r00]

struct_ar00i RunOffscrBitsSubs(byte param_1)

{
  byte bVar1;
  byte bVar2;
  
  
  bVar1 = GetXOffscreenBits(param_1);
  bVar1 >>= 4;
  bVar2 = GetYOffscreenBits(param_1);
  return (struct_ar00i)CONCAT12(0,CONCAT11(bVar1,bVar2));
}



// SMB:f1f6
// Signature: [X] -> [A]

byte GetXOffscreenBits(byte param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  bVar3 = 1;
  do {
    bVar1 = (ScreenEdgeOrLeft_PageLoc[bVar3] - PlayerOrSprObject_PageLoc[param_1]) -
            (ScreenEdgeOrLeft_X_Pos[bVar3] < PlayerOrSprObject_X_Position[param_1]);
    bVar2 = DefaultXOnscreenOfs[bVar3];
    if ((bVar1 < 0x80) && (bVar2 = DefaultXOnscreenOfs[bVar3 + 1], 0x7f < (byte)(bVar1 - 1))) {
      bVar2 = DividePDiff(8,bVar2,bVar3,0x38,
                          ScreenEdgeOrLeft_X_Pos[bVar3] - PlayerOrSprObject_X_Position[param_1]);
    }
  } while ((XOffscreenBitsData[bVar2] == 0) && (bVar3 -= 1, bVar3 < 0x80));
  return XOffscreenBitsData[bVar2];
}



// SMB:f239
// Signature: [X] -> [A]

byte GetYOffscreenBits(byte param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  bVar3 = 1;
  do {
    bVar1 = (1 - PlayerOrSprObject_Y_HighPos[param_1]) -
            (HighPosUnitData[bVar3] < PlayerOrSprObject_Y_Position[param_1]);
    bVar2 = DefaultYOnscreenOfs[bVar3];
    if ((bVar1 < 0x80) && (bVar2 = DefaultYOnscreenOfs[bVar3 + 1], 0x7f < (byte)(bVar1 - 1))) {
      bVar2 = DividePDiff(4,bVar2,bVar3,0x20,
                          HighPosUnitData[bVar3] - PlayerOrSprObject_Y_Position[param_1]);
    }
  } while ((YOffscreenBitsData[bVar2] == 0) && (bVar3 -= 1, bVar3 < 0x80));
  return YOffscreenBitsData[bVar2];
}



// SMB:f26d
// Signature: [A, X, Y, r06, r07] -> [X]

byte DividePDiff(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5)

{
  if (param_5 < param_4) {
    param_2 = param_5 >> 3 & 7;
    if (param_3 == 0) {
      param_2 = param_2 + param_1 + (param_3 != 0);
    }
  }
  return param_2;
}



// SMB:f282
// Signature: [X, Y, r00, r01, r02, r03, r04, r05] -> [X, Y, r02]

struct_xyr02
DrawSpriteObject(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,
                byte param_7,byte param_8)

{
  byte bVar1;
  
  if ((param_6 >> 1 & 1) == 0) {
    Sprite_Data[param_2 + 1] = param_3;
    Sprite_Data[param_2 + 5] = param_4;
    bVar1 = 0;
  }
  else {
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
  return (struct_xyr02)CONCAT12(param_5 + 8,CONCAT11(param_2 + 8,param_1 + 2));
}


