#pragma once
#pragma pack(push, 1)


typedef unsigned char    byte;

typedef struct struct_ycr07 struct_ycr07;

struct struct_ycr07 {
  byte y;
  bool c;
  byte r07;
};


typedef struct struct_xr00r01 struct_xr00r01;

struct struct_xr00r01 {
  byte x;
  byte r00;
  byte r01;
};


typedef struct struct_axyz struct_axyz;

struct struct_axyz {
  byte a;
  byte x;
  byte y;
  bool z;
};


typedef struct struct_nr00 struct_nr00;

struct struct_nr00 {
  bool n;
  byte r00;
};


typedef struct struct_ncr00 struct_ncr00;

struct struct_ncr00 {
  bool n;
  bool c;
  byte r00;
};


typedef struct struct_xr06 struct_xr06;

struct struct_xr06 {
  byte x;
  byte r06;
};


typedef struct struct_ayz struct_ayz;

struct struct_ayz {
  byte a;
  byte y;
  bool z;
};


typedef struct struct_r06r07 struct_r06r07;

struct struct_r06r07 {
  byte r06;
  byte r07;
};


typedef struct struct_ayr02r04r06r07 struct_ayr02r04r06r07;

struct struct_ayr02r04r06r07 {
  byte a;
  byte y;
  byte r02;
  byte r04;
  byte r06;
  byte r07;
};


typedef struct struct_ay struct_ay;

struct struct_ay {
  byte a;
  byte y;
};


struct blockbuffer_colli_result {
  byte a;
  bool z;
  byte r04;

  u16 mt_x;
  u16 mt_y;
};


typedef struct struct_axy struct_axy;

struct struct_axy {
  byte a;
  byte x;
  byte y;
};


typedef struct struct_axz struct_axz;

struct struct_axz {
  byte a;
  byte x;
  bool z;
};


typedef struct struct_axzr02r04r06r07 struct_axzr02r04r06r07;

struct struct_axzr02r04r06r07 {
  byte a;
  byte x;
  bool z;
  byte r02;
  byte r04;
  byte r06;
  byte r07;
};


typedef struct struct_yr07 struct_yr07;

struct struct_yr07 {
  byte y;
  byte r07;
};


typedef struct struct_ax struct_ax;

struct struct_ax {
  byte a;
  byte x;
};


typedef struct struct_r01r02r03 struct_r01r02r03;

struct struct_r01r02r03 {
  byte r01;
  byte r02;
  byte r03;
};


typedef struct struct_azr04 struct_azr04;

struct struct_azr04 {
  byte a;
  bool z;
  byte r04;
};


typedef struct struct_axzr04 struct_axzr04;

struct struct_axzr04 {
  byte a;
  byte x;
  bool z;
  byte r04;
};


typedef struct struct_xc struct_xc;

struct struct_xc {
  byte x;
  bool c;
};


typedef struct struct_xyr02 struct_xyr02;

struct struct_xyr02 {
  byte x;
  byte y;
  byte r02;
};


typedef struct struct_yc struct_yc;

struct struct_yc {
  byte y;
  bool c;
};


typedef struct struct_ar00 struct_ar00;

struct struct_ar00 {
  byte a;
  byte r00;
};


typedef struct struct_yr06r07 struct_yr06r07;

struct struct_yr06r07 {
  byte y;
  byte r06;
  byte r07;
};


typedef struct struct_xr00 struct_xr00;

struct struct_xr00 {
  byte x;
  byte r00;
};





void smb1_jumptable_GameOverMode(byte param_1);
#define jumptable_GameOverMode smb1_jumptable_GameOverMode

void smb1_jumptable_AreaParserTasks(byte param_1);
#define jumptable_AreaParserTasks smb1_jumptable_AreaParserTasks

void smb1_jumptable_AreaStyleObject(byte param_1,byte param_2);
#define jumptable_AreaStyleObject smb1_jumptable_AreaStyleObject

void smb1_jumptable_GameRoutines(byte param_1);
#define jumptable_GameRoutines smb1_jumptable_GameRoutines

void smb1_jumptable_PlayerMovementSubs(byte param_1);
#define jumptable_PlayerMovementSubs smb1_jumptable_PlayerMovementSubs

void smb1_jumptable_CheckpointEnemyID(byte param_1,byte param_2);
#define jumptable_CheckpointEnemyID smb1_jumptable_CheckpointEnemyID

void smb1_jumptable_InitEnemyFrenzy(byte param_1,byte param_2);
#define jumptable_InitEnemyFrenzy smb1_jumptable_InitEnemyFrenzy

byte smb1_jumptable_RunEnemyObjectsCore(byte param_1,byte param_2);
#define jumptable_RunEnemyObjectsCore smb1_jumptable_RunEnemyObjectsCore

byte smb1_jumptable_EnemyMovementSubs(byte param_1,byte param_2);
#define jumptable_EnemyMovementSubs smb1_jumptable_EnemyMovementSubs

byte smb1_jumptable_LargePlatformSubroutines(byte param_1,byte param_2);
#define jumptable_LargePlatformSubroutines smb1_jumptable_LargePlatformSubroutines

byte smb1_jumptable_RunStarFlagObj(byte param_1,byte param_2);
#define jumptable_RunStarFlagObj smb1_jumptable_RunStarFlagObj

void smb1_PauseRoutine(void);
#define PauseRoutine smb1_PauseRoutine

void smb1_SpriteShuffler(void);
#define SpriteShuffler smb1_SpriteShuffler

void smb1_OperModeExecutionTree(void);
#define OperModeExecutionTree smb1_OperModeExecutionTree

void smb1_MoveAllSpritesOffscreen(void);
#define MoveAllSpritesOffscreen smb1_MoveAllSpritesOffscreen

void smb1_MoveSpritesOffscreen(void);
#define MoveSpritesOffscreen smb1_MoveSpritesOffscreen

void smb1_TitleScreenMode(void);
#define TitleScreenMode smb1_TitleScreenMode

void smb1_GameMenuRoutine(void);
#define GameMenuRoutine smb1_GameMenuRoutine

void smb1_DrawMushroomIcon(void);
#define DrawMushroomIcon smb1_DrawMushroomIcon

bool smb1_DemoEngine(void);
#define DemoEngine smb1_DemoEngine

void smb1_VictoryMode(void);
#define VictoryMode smb1_VictoryMode

void smb1_VictoryModeSubroutines(void);
#define VictoryModeSubroutines smb1_VictoryModeSubroutines

void smb1_SetupVictoryMode(void);
#define SetupVictoryMode smb1_SetupVictoryMode

void smb1_PlayerVictoryWalk(void);
#define PlayerVictoryWalk smb1_PlayerVictoryWalk

void smb1_PrintVictoryMessages(void);
#define PrintVictoryMessages smb1_PrintVictoryMessages

void smb1_PlayerEndWorld(void);
#define PlayerEndWorld smb1_PlayerEndWorld

void smb1_FloateyNumbersRoutine(byte param_1);
#define FloateyNumbersRoutine smb1_FloateyNumbersRoutine

void smb1_ScreenRoutines(void);
#define ScreenRoutines smb1_ScreenRoutines

void smb1_InitScreen(void);
#define InitScreen smb1_InitScreen

void smb1_SetupIntermediate(void);
#define SetupIntermediate smb1_SetupIntermediate

void smb1_GetAreaPalette(void);
#define GetAreaPalette smb1_GetAreaPalette

void smb1_GetBackgroundColor(void);
#define GetBackgroundColor smb1_GetBackgroundColor

void smb1_GetPlayerColors(void);
#define GetPlayerColors smb1_GetPlayerColors

void smb1_GetAlternatePalette1(void);
#define GetAlternatePalette1 smb1_GetAlternatePalette1

void smb1_WriteTopStatusLine(void);
#define WriteTopStatusLine smb1_WriteTopStatusLine

void smb1_WriteBottomStatusLine(void);
#define WriteBottomStatusLine smb1_WriteBottomStatusLine

void smb1_DisplayTimeUp(void);
#define DisplayTimeUp smb1_DisplayTimeUp

void smb1_DisplayIntermediate(void);
#define DisplayIntermediate smb1_DisplayIntermediate

void smb1_ClearBuffersDrawIcon(void);
#define ClearBuffersDrawIcon smb1_ClearBuffersDrawIcon

void smb1_WriteTopScore(void);
#define WriteTopScore smb1_WriteTopScore

void smb1_WriteGameText(byte param_1);
#define WriteGameText smb1_WriteGameText

void smb1_ResetSpritesAndScreenTimer(void);
#define ResetSpritesAndScreenTimer smb1_ResetSpritesAndScreenTimer

void smb1_ResetScreenTimer(void);
#define ResetScreenTimer smb1_ResetScreenTimer

void smb1_ColorRotation(void);
#define ColorRotation smb1_ColorRotation

void smb1_RemoveCoin_Axe(u16 mt_x, u16 mt_y);
#define RemoveCoin_Axe smb1_RemoveCoin_Axe

void smb1_ReplaceBlockMetatile(byte param_1,byte param_2,u16 mt_x, u16 mt_y);
#define ReplaceBlockMetatile smb1_ReplaceBlockMetatile

void smb1_DestroyBlockMetatile(u16 mt_x, u16 mt_y);
#define DestroyBlockMetatile smb1_DestroyBlockMetatile

void smb1_WriteBlockMetatile(byte param_1,u16 mt_x, u16 mt_y);
#define WriteBlockMetatile smb1_WriteBlockMetatile

void smb1_InitializeNameTables(void);
#define InitializeNameTables smb1_InitializeNameTables

void smb1_WritePPUReg1(byte param_1);
#define WritePPUReg1 smb1_WritePPUReg1

void smb1_PrintStatusBarNumbers(byte param_1);
#define PrintStatusBarNumbers smb1_PrintStatusBarNumbers

void smb1_OutputNumbers(byte param_1);
#define OutputNumbers smb1_OutputNumbers

void smb1_DigitsMathRoutine(byte param_1);
#define DigitsMathRoutine smb1_DigitsMathRoutine

void smb1_UpdateTopScore(void);
#define UpdateTopScore smb1_UpdateTopScore

void smb1_TopScoreCheck(byte param_1);
#define TopScoreCheck smb1_TopScoreCheck

void smb1_InitializeGame(void);
#define InitializeGame smb1_InitializeGame

void smb1_DemoReset(void);
#define DemoReset smb1_DemoReset

void smb1_InitializeArea(void);
#define InitializeArea smb1_InitializeArea

void smb1_PrimaryGameSetup(void);
#define PrimaryGameSetup smb1_PrimaryGameSetup

void smb1_SecondaryGameSetup(void);
#define SecondaryGameSetup smb1_SecondaryGameSetup

void smb1_GetAreaMusic(void);
#define GetAreaMusic smb1_GetAreaMusic

void smb1_Entrance_GameTimerSetup(void);
#define Entrance_GameTimerSetup smb1_Entrance_GameTimerSetup

void smb1_PlayerLoseLife(void);
#define PlayerLoseLife smb1_PlayerLoseLife

void smb1_GameOverMode(void);
#define GameOverMode smb1_GameOverMode

void smb1_SetupGameOver(void);
#define SetupGameOver smb1_SetupGameOver

void smb1_RunGameOver(void);
#define RunGameOver smb1_RunGameOver

void smb1_TerminateGame(void);
#define TerminateGame smb1_TerminateGame

void smb1_ContinueGame(void);
#define ContinueGame smb1_ContinueGame

void smb1_KillEnemies(byte param_1);
#define KillEnemies smb1_KillEnemies

void smb1_GameMode(void);
#define GameMode smb1_GameMode

void smb1_GameCoreRoutine(void);
#define GameCoreRoutine smb1_GameCoreRoutine

void smb1_UpdScrollVar(void);
#define UpdScrollVar smb1_UpdScrollVar

void smb1_ScrollHandler(void);
#define ScrollHandler smb1_ScrollHandler

void smb1_ScrollScreen(byte param_1);
#define ScrollScreen smb1_ScrollScreen

void smb1_ChkPOffscr(void);
#define ChkPOffscr smb1_ChkPOffscr

byte smb1_GetScreenPosition(void);
#define GetScreenPosition smb1_GetScreenPosition

void smb1_GameRoutines(void);
#define GameRoutines smb1_GameRoutines

void smb1_PlayerEntrance(void);
#define PlayerEntrance smb1_PlayerEntrance

void smb1_AutoControlPlayer(byte param_1);
#define AutoControlPlayer smb1_AutoControlPlayer

void smb1_PlayerCtrlRoutine(void);
#define PlayerCtrlRoutine smb1_PlayerCtrlRoutine

void smb1_Vine_AutoClimb(void);
#define Vine_AutoClimb smb1_Vine_AutoClimb

void smb1_SetEntr(void);
#define SetEntr smb1_SetEntr

void smb1_VerticalPipeEntry(void);
#define VerticalPipeEntry smb1_VerticalPipeEntry

void smb1_MovePlayerYAxis(byte param_1);
#define MovePlayerYAxis smb1_MovePlayerYAxis

void smb1_SideExitPipeEntry(void);
#define SideExitPipeEntry smb1_SideExitPipeEntry

byte smb1_ChgAreaMode(void);
#define ChgAreaMode smb1_ChgAreaMode

void smb1_EnterSidePipe(void);
#define EnterSidePipe smb1_EnterSidePipe

void smb1_PlayerChangeSize(void);
#define PlayerChangeSize smb1_PlayerChangeSize

void smb1_PlayerInjuryBlink(void);
#define PlayerInjuryBlink smb1_PlayerInjuryBlink

void smb1_InitChangeSize(void);
#define InitChangeSize smb1_InitChangeSize

void smb1_PlayerDeath(void);
#define PlayerDeath smb1_PlayerDeath

void smb1_DonePlayerTask(void);
#define DonePlayerTask smb1_DonePlayerTask

void smb1_PlayerFireFlower(void);
#define PlayerFireFlower smb1_PlayerFireFlower

void smb1_CyclePlayerPalette(byte param_1);
#define CyclePlayerPalette smb1_CyclePlayerPalette

void smb1_ResetPalStar(void);
#define ResetPalStar smb1_ResetPalStar

void smb1_FlagpoleSlide(void);
#define FlagpoleSlide smb1_FlagpoleSlide

void smb1_PlayerEndLevel(void);
#define PlayerEndLevel smb1_PlayerEndLevel

void smb1_NextArea(void);
#define NextArea smb1_NextArea

void smb1_PlayerMovementSubs(void);
#define PlayerMovementSubs smb1_PlayerMovementSubs

void smb1_OnGroundStateSub(void);
#define OnGroundStateSub smb1_OnGroundStateSub

void smb1_FallingSub(void);
#define FallingSub smb1_FallingSub

void smb1_JumpSwimSub(void);
#define JumpSwimSub smb1_JumpSwimSub

void smb1_LRAir(void);
#define LRAir smb1_LRAir

void smb1_ClimbingSub(void);
#define ClimbingSub smb1_ClimbingSub

void smb1_PlayerPhysicsSub(void);
#define PlayerPhysicsSub smb1_PlayerPhysicsSub

void smb1_GetPlayerAnimSpeed(void);
#define GetPlayerAnimSpeed smb1_GetPlayerAnimSpeed

void smb1_ImposeFriction(byte param_1);
#define ImposeFriction smb1_ImposeFriction

void smb1_ProcFireball_Bubble(void);
#define ProcFireball_Bubble smb1_ProcFireball_Bubble

void smb1_FireballObjCore(byte param_1);
#define FireballObjCore smb1_FireballObjCore

void smb1_BubbleCheck(byte param_1);
#define BubbleCheck smb1_BubbleCheck

void smb1_SetupBubble_buggy(byte param_1,byte param_2);
#define SetupBubble_buggy smb1_SetupBubble_buggy

void smb1_MoveBubl(byte param_1,byte param_2);
#define MoveBubl smb1_MoveBubl

void smb1_RunGameTimer(void);
#define RunGameTimer smb1_RunGameTimer

void smb1_WarpZoneObject(byte param_1);
#define WarpZoneObject smb1_WarpZoneObject

void smb1_ProcessWhirlpools(void);
#define ProcessWhirlpools smb1_ProcessWhirlpools

void smb1_FlagpoleRoutine(void);
#define FlagpoleRoutine smb1_FlagpoleRoutine

void smb1_JumpspringHandler(byte param_1);
#define JumpspringHandler smb1_JumpspringHandler

void smb1_Setup_Vine(byte param_1,byte param_2);
#define Setup_Vine smb1_Setup_Vine

void smb1_VineObjectHandler(byte param_1);
#define VineObjectHandler smb1_VineObjectHandler

void smb1_ProcessCannons(void);
#define ProcessCannons smb1_ProcessCannons

void smb1_BulletBillHandler(byte param_1);
#define BulletBillHandler smb1_BulletBillHandler

bool smb1_SpawnHammerObj(byte objoff);
#define SpawnHammerObj smb1_SpawnHammerObj

void smb1_CoinBlock(byte param_1);
#define CoinBlock smb1_CoinBlock

void smb1_JCoinC(byte param_1,byte param_2);
#define JCoinC smb1_JCoinC

void smb1_MiscObjectsCore(void);
#define MiscObjectsCore smb1_MiscObjectsCore

void smb1_GiveOneCoin(void);
#define GiveOneCoin smb1_GiveOneCoin

void smb1_AddToScore(void);
#define AddToScore smb1_AddToScore

void smb1_WriteScoreAndCoinTally(void);
#define WriteScoreAndCoinTally smb1_WriteScoreAndCoinTally

void smb1_WriteDigits(byte param_1);
#define WriteDigits smb1_WriteDigits

void smb1_SetupPowerUp(byte param_1);
#define SetupPowerUp smb1_SetupPowerUp

void smb1_PwrUpJmp(void);
#define PwrUpJmp smb1_PwrUpJmp

void smb1_PowerUpObjHandler(void);
#define PowerUpObjHandler smb1_PowerUpObjHandler

void smb1_PlayerHeadCollision(byte param_1,u16 mt_x, u16 mt_y);
#define PlayerHeadCollision smb1_PlayerHeadCollision

void smb1_InitBlock_XY_Pos(byte param_1);
#define InitBlock_XY_Pos smb1_InitBlock_XY_Pos

void smb1_BumpBlock(u16 mt_x,u16 mt_y,byte param_2);
#define BumpBlock smb1_BumpBlock

void smb1_MushFlowerBlock(byte param_1);
#define MushFlowerBlock smb1_MushFlowerBlock

void smb1_StarBlock(byte param_1);
#define StarBlock smb1_StarBlock

void smb1_ExtraLifeMushBlock(byte param_1);
#define ExtraLifeMushBlock smb1_ExtraLifeMushBlock

void smb1_VineBlock(void);
#define VineBlock smb1_VineBlock

struct_yc smb1_BlockBumpedChk(byte param_1);
#define BlockBumpedChk smb1_BlockBumpedChk

void smb1_BrickShatter(u16 mt_x, u16 mt_y);
#define BrickShatter smb1_BrickShatter

byte smb1_CheckTopOfBlock(u16 mt_x, u16 mt_y);
#define CheckTopOfBlock smb1_CheckTopOfBlock

void smb1_SpawnBrickChunks(byte param_1);
#define SpawnBrickChunks smb1_SpawnBrickChunks

void smb1_BlockObjectsCore(byte param_1);
#define BlockObjectsCore smb1_BlockObjectsCore

void smb1_BlockObjMT_Updater(void);
#define BlockObjMT_Updater smb1_BlockObjMT_Updater

byte smb1_MoveEnemyHorizontally(byte param_1);
#define MoveEnemyHorizontally smb1_MoveEnemyHorizontally

byte smb1_MovePlayerHorizontally(void);
#define MovePlayerHorizontally smb1_MovePlayerHorizontally

byte smb1_MoveObjectHorizontally(byte param_1);
#define MoveObjectHorizontally smb1_MoveObjectHorizontally

void smb1_MovePlayerVertically(void);
#define MovePlayerVertically smb1_MovePlayerVertically

void smb1_MoveD_EnemyVertically(byte param_1);
#define MoveD_EnemyVertically smb1_MoveD_EnemyVertically

void smb1_MoveFallingPlatform(byte param_1);
#define MoveFallingPlatform smb1_MoveFallingPlatform

void smb1_MoveRedPTroopaDown(byte param_1);
#define MoveRedPTroopaDown smb1_MoveRedPTroopaDown

void smb1_MoveRedPTroopaUp(byte param_1);
#define MoveRedPTroopaUp smb1_MoveRedPTroopaUp

void smb1_MoveDropPlatform(byte param_1);
#define MoveDropPlatform smb1_MoveDropPlatform

void smb1_MoveEnemySlowVert(byte param_1);
#define MoveEnemySlowVert smb1_MoveEnemySlowVert

void smb1_MoveJ_EnemyVertically(byte param_1);
#define MoveJ_EnemyVertically smb1_MoveJ_EnemyVertically

void smb1_SetXMoveAmt(byte param_1,byte param_2,byte param_3);
#define SetXMoveAmt smb1_SetXMoveAmt

void smb1_ImposeGravityBlock(byte param_1);
#define ImposeGravityBlock smb1_ImposeGravityBlock

void smb1_ImposeGravitySprObj(byte param_1,byte param_2,byte param_3);
#define ImposeGravitySprObj smb1_ImposeGravitySprObj

void smb1_MovePlatformDown(byte param_1);
#define MovePlatformDown smb1_MovePlatformDown

void smb1_MovePlatformUp(byte param_1);
#define MovePlatformUp smb1_MovePlatformUp

void smb1_ImposeGravity(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
#define ImposeGravity smb1_ImposeGravity

void smb1_EnemiesAndLoopsCore(byte param_1);
#define EnemiesAndLoopsCore smb1_EnemiesAndLoopsCore

void smb1_ExecGameLoopback(byte param_1);
#define ExecGameLoopback smb1_ExecGameLoopback

void smb1_ProcLoopCommand(byte param_1);
#define ProcLoopCommand smb1_ProcLoopCommand

void smb1_InitEnemyObject(byte param_1);
#define InitEnemyObject smb1_InitEnemyObject

void smb1_CheckThreeBytes(void);
#define CheckThreeBytes smb1_CheckThreeBytes

void smb1_CheckpointEnemyID(byte param_1);
#define CheckpointEnemyID smb1_CheckpointEnemyID

void smb1_InitGoomba(byte param_1);
#define InitGoomba smb1_InitGoomba

void smb1_InitPodoboo(byte param_1);
#define InitPodoboo smb1_InitPodoboo

void smb1_InitRetainerObj(byte param_1);
#define InitRetainerObj smb1_InitRetainerObj

void smb1_InitNormalEnemy(byte param_1);
#define InitNormalEnemy smb1_InitNormalEnemy

void smb1_InitRedKoopa(byte param_1);
#define InitRedKoopa smb1_InitRedKoopa

void smb1_InitHammerBro(byte param_1);
#define InitHammerBro smb1_InitHammerBro

void smb1_InitHorizFlySwimEnemy(byte param_1);
#define InitHorizFlySwimEnemy smb1_InitHorizFlySwimEnemy

void smb1_InitBloober(byte param_1);
#define InitBloober smb1_InitBloober

byte smb1_SmallBBox(byte param_1);
#define SmallBBox smb1_SmallBBox

void smb1_InitRedPTroopa(byte param_1);
#define InitRedPTroopa smb1_InitRedPTroopa

byte smb1_InitVStf(byte param_1);
#define InitVStf smb1_InitVStf

void smb1_InitBulletBill(byte param_1);
#define InitBulletBill smb1_InitBulletBill

void smb1_InitCheepCheep(byte param_1);
#define InitCheepCheep smb1_InitCheepCheep

void smb1_InitLakitu(byte param_1);
#define InitLakitu smb1_InitLakitu

void smb1_SetupLakitu(byte param_1);
#define SetupLakitu smb1_SetupLakitu

void smb1_LakituAndSpinyHandler(byte param_1);
#define LakituAndSpinyHandler smb1_LakituAndSpinyHandler

void smb1_InitLongFirebar(byte param_1);
#define InitLongFirebar smb1_InitLongFirebar

void smb1_InitShortFirebar(byte param_1);
#define InitShortFirebar smb1_InitShortFirebar

void smb1_InitFlyingCheepCheep(byte param_1);
#define InitFlyingCheepCheep smb1_InitFlyingCheepCheep

void smb1_InitBowser(byte param_1);
#define InitBowser smb1_InitBowser

void smb1_DuplicateEnemyObj(byte param_1);
#define DuplicateEnemyObj smb1_DuplicateEnemyObj

void smb1_InitBowserFlame(byte param_1);
#define InitBowserFlame smb1_InitBowserFlame

void smb1_PutAtRightExtent(byte param_1,byte param_2);
#define PutAtRightExtent smb1_PutAtRightExtent

void smb1_InitFireworks(byte param_1);
#define InitFireworks smb1_InitFireworks

void smb1_BulletBillCheepCheep(byte param_1);
#define BulletBillCheepCheep smb1_BulletBillCheepCheep

void smb1_HandleGroupEnemies(byte param_1);
#define HandleGroupEnemies smb1_HandleGroupEnemies

void smb1_InitPiranhaPlant(byte param_1);
#define InitPiranhaPlant smb1_InitPiranhaPlant

void smb1_InitEnemyFrenzy(byte param_1);
#define InitEnemyFrenzy smb1_InitEnemyFrenzy

void smb1_EndFrenzy(byte param_1);
#define EndFrenzy smb1_EndFrenzy

void smb1_InitJumpGPTroopa(byte param_1);
#define InitJumpGPTroopa smb1_InitJumpGPTroopa

void smb1_InitBalPlatform(byte param_1);
#define InitBalPlatform smb1_InitBalPlatform

void smb1_InitDropPlatform(byte param_1);
#define InitDropPlatform smb1_InitDropPlatform

void smb1_InitHoriPlatform(byte param_1);
#define InitHoriPlatform smb1_InitHoriPlatform

void smb1_InitVertPlatform(byte param_1);
#define InitVertPlatform smb1_InitVertPlatform

void smb1_SPBBox(byte param_1);
#define SPBBox smb1_SPBBox

void smb1_LargeLiftUp(byte param_1);
#define LargeLiftUp smb1_LargeLiftUp

void smb1_LargeLiftDown(byte param_1);
#define LargeLiftDown smb1_LargeLiftDown

void smb1_PlatLiftUp(byte param_1);
#define PlatLiftUp smb1_PlatLiftUp

void smb1_PlatLiftDown(byte param_1);
#define PlatLiftDown smb1_PlatLiftDown

void smb1_PosPlatform(byte param_1,byte param_2);
#define PosPlatform smb1_PosPlatform

void smb1_RunEnemyObjectsCore(byte objoff);
#define RunEnemyObjectsCore smb1_RunEnemyObjectsCore

void smb1_RunRetainerObj(byte param_1);
#define RunRetainerObj smb1_RunRetainerObj

void smb1_RunNormalEnemies(byte param_1);
#define RunNormalEnemies smb1_RunNormalEnemies

void smb1_EnemyMovementSubs(byte param_1);
#define EnemyMovementSubs smb1_EnemyMovementSubs

void smb1_RunBowserFlame(byte param_1);
#define RunBowserFlame smb1_RunBowserFlame

void smb1_RunFirebarObj(byte param_1);
#define RunFirebarObj smb1_RunFirebarObj

void smb1_RunSmallPlatform(byte param_1);
#define RunSmallPlatform smb1_RunSmallPlatform

void smb1_RunLargePlatform(byte param_1);
#define RunLargePlatform smb1_RunLargePlatform

void smb1_LargePlatformSubroutines(byte param_1);
#define LargePlatformSubroutines smb1_LargePlatformSubroutines

void smb1_EraseEnemyObject(byte param_1);
#define EraseEnemyObject smb1_EraseEnemyObject

void smb1_MovePodoboo(byte param_1);
#define MovePodoboo smb1_MovePodoboo

void smb1_ProcHammerBro(byte param_1);
#define ProcHammerBro smb1_ProcHammerBro

void smb1_SetHJ(byte param_1,byte param_2,byte param_3);
#define SetHJ smb1_SetHJ

void smb1_MoveHammerBroXDir(byte param_1);
#define MoveHammerBroXDir smb1_MoveHammerBroXDir

void smb1_MoveNormalEnemy(byte param_1);
#define MoveNormalEnemy smb1_MoveNormalEnemy

void smb1_MoveDefeatedEnemy(byte param_1);
#define MoveDefeatedEnemy smb1_MoveDefeatedEnemy

void smb1_MoveJumpingEnemy(byte param_1);
#define MoveJumpingEnemy smb1_MoveJumpingEnemy

void smb1_ProcMoveRedPTroopa(byte param_1);
#define ProcMoveRedPTroopa smb1_ProcMoveRedPTroopa

void smb1_MoveFlyGreenPTroopa(byte param_1);
#define MoveFlyGreenPTroopa smb1_MoveFlyGreenPTroopa

void smb1_XMoveCntr_GreenPTroopa(byte param_1);
#define XMoveCntr_GreenPTroopa smb1_XMoveCntr_GreenPTroopa

void smb1_XMoveCntr_Platform(byte param_1,byte param_2);
#define XMoveCntr_Platform smb1_XMoveCntr_Platform

byte smb1_MoveWithXMCntrs(byte objoff);
#define MoveWithXMCntrs smb1_MoveWithXMCntrs

void smb1_MoveBloober(byte param_1,bool param_2);
#define MoveBloober smb1_MoveBloober

void smb1_ProcSwimmingB(byte param_1,bool param_2);
#define ProcSwimmingB smb1_ProcSwimmingB

void smb1_MoveBulletBill(byte param_1);
#define MoveBulletBill smb1_MoveBulletBill

void smb1_MoveSwimmingCheepCheep(byte param_1);
#define MoveSwimmingCheepCheep smb1_MoveSwimmingCheepCheep

void smb1_ProcFirebar(byte param_1);
#define ProcFirebar smb1_ProcFirebar

byte smb1_DrawFirebar_Collision(byte param_2,byte param_3,byte param_4,byte param_5);
#define DrawFirebar_Collision smb1_DrawFirebar_Collision

byte smb1_FirebarCollision(byte param_1,byte param_3,byte param_4);
#define FirebarCollision smb1_FirebarCollision

struct_r01r02r03 smb1_GetFirebarPosition(byte param_1,byte param_2);
#define GetFirebarPosition smb1_GetFirebarPosition

void smb1_MoveFlyingCheepCheep(byte param_1);
#define MoveFlyingCheepCheep smb1_MoveFlyingCheepCheep

void smb1_MoveLakitu(byte param_1);
#define MoveLakitu smb1_MoveLakitu

byte smb1_PlayerLakituDiff(byte param_1,byte param_2,byte param_3,byte param_4);
#define PlayerLakituDiff smb1_PlayerLakituDiff

void smb1_BridgeCollapse(void);
#define BridgeCollapse smb1_BridgeCollapse

void smb1_MoveD_Bowser(byte param_1);
#define MoveD_Bowser smb1_MoveD_Bowser

void smb1_RunBowser(byte param_1);
#define RunBowser smb1_RunBowser

void smb1_KillAllEnemies(void);
#define KillAllEnemies smb1_KillAllEnemies

void smb1_BowserGfxHandler(byte param_1);
#define BowserGfxHandler smb1_BowserGfxHandler

void smb1_ProcessBowserHalf(byte param_1);
#define ProcessBowserHalf smb1_ProcessBowserHalf

byte smb1_SetFlameTimer(void);
#define SetFlameTimer smb1_SetFlameTimer

void smb1_ProcBowserFlame(byte param_1);
#define ProcBowserFlame smb1_ProcBowserFlame

void smb1_RunFireworks(byte param_1);
#define RunFireworks smb1_RunFireworks

void smb1_RunStarFlagObj(byte param_1);
#define RunStarFlagObj smb1_RunStarFlagObj

void smb1_GameTimerFireworks(byte param_1);
#define GameTimerFireworks smb1_GameTimerFireworks

void smb1_AwardGameTimerPoints(byte param_1);
#define AwardGameTimerPoints smb1_AwardGameTimerPoints

void smb1_AwardTimerCastle(void);
#define AwardTimerCastle smb1_AwardTimerCastle

void smb1_EndAreaPoints(void);
#define EndAreaPoints smb1_EndAreaPoints

void smb1_RaiseFlagSetoffFWorks(byte param_1);
#define RaiseFlagSetoffFWorks smb1_RaiseFlagSetoffFWorks

void smb1_DrawStarFlag(byte param_1);
#define DrawStarFlag smb1_DrawStarFlag

void smb1_DelayToAreaEnd(byte param_1);
#define DelayToAreaEnd smb1_DelayToAreaEnd

void smb1_MovePiranhaPlant(byte param_1);
#define MovePiranhaPlant smb1_MovePiranhaPlant

void smb1_BalancePlatform(byte param_1);
#define BalancePlatform smb1_BalancePlatform

void smb1_InitPlatformFall(byte param_1, byte objoff);
#define InitPlatformFall smb1_InitPlatformFall

void smb1_StopPlatforms(byte param_1,byte param_2);
#define StopPlatforms smb1_StopPlatforms

void smb1_PlatformFall(byte param_1,byte param_2);
#define PlatformFall smb1_PlatformFall

void smb1_YMovingPlatform(byte param_1);
#define YMovingPlatform smb1_YMovingPlatform

void smb1_ChkYPCollision(byte param_1);
#define ChkYPCollision smb1_ChkYPCollision

void smb1_XMovingPlatform(byte objoff);
#define XMovingPlatform smb1_XMovingPlatform

void smb1_PositionPlayerOnHPlat(byte param_1,byte param_2);
#define PositionPlayerOnHPlat smb1_PositionPlayerOnHPlat

void smb1_DropPlatform(byte param_1);
#define DropPlatform smb1_DropPlatform

void smb1_RightPlatform(byte objoff);
#define RightPlatform smb1_RightPlatform

void smb1_MoveLargeLiftPlat(byte param_1);
#define MoveLargeLiftPlat smb1_MoveLargeLiftPlat

void smb1_MoveSmallPlatform(byte param_1);
#define MoveSmallPlatform smb1_MoveSmallPlatform

void smb1_MoveLiftPlatforms(byte param_1);
#define MoveLiftPlatforms smb1_MoveLiftPlatforms

void smb1_ChkSmallPlatCollision(byte param_1);
#define ChkSmallPlatCollision smb1_ChkSmallPlatCollision

void smb1_OffscreenBoundsCheck(byte param_1);
#define OffscreenBoundsCheck smb1_OffscreenBoundsCheck

void smb1_FireballEnemyCollision(byte param_1);
#define FireballEnemyCollision smb1_FireballEnemyCollision

void smb1_HandleEnemyFBallCol(byte param_1);
#define HandleEnemyFBallCol smb1_HandleEnemyFBallCol

void smb1_ShellOrBlockDefeat(byte param_1);
#define ShellOrBlockDefeat smb1_ShellOrBlockDefeat

void smb1_EnemySmackScore(byte param_1,byte param_2);
#define EnemySmackScore smb1_EnemySmackScore

void smb1_PlayerHammerCollision(byte param_1);
#define PlayerHammerCollision smb1_PlayerHammerCollision

void smb1_HandlePowerUpCollision(byte param_1);
#define HandlePowerUpCollision smb1_HandlePowerUpCollision

void smb1_PlayerEnemyCollision(byte param_1);
#define PlayerEnemyCollision smb1_PlayerEnemyCollision

void smb1_InjurePlayer(void);
#define InjurePlayer smb1_InjurePlayer

void smb1_ForceInjury(byte param_1);
#define ForceInjury smb1_ForceInjury

void smb1_SetPRout(byte param_1,byte param_2);
#define SetPRout smb1_SetPRout

void smb1_ChkEnemyFaceRight(byte param_1);
#define ChkEnemyFaceRight smb1_ChkEnemyFaceRight

void smb1_LInj(byte param_1);
#define LInj smb1_LInj

bool smb1_EnemyFacePlayer(byte param_1);
#define EnemyFacePlayer smb1_EnemyFacePlayer

void smb1_SetupFloateyNumber(byte param_1,byte param_2);
#define SetupFloateyNumber smb1_SetupFloateyNumber

void smb1_EnemiesCollision(byte param_1);
#define EnemiesCollision smb1_EnemiesCollision

void smb1_ProcEnemyCollisions(byte param_1,byte param_2);
#define ProcEnemyCollisions smb1_ProcEnemyCollisions

void smb1_EnemyTurnAround(byte param_1);
#define EnemyTurnAround smb1_EnemyTurnAround

void smb1_RXSpd(byte param_1);
#define RXSpd smb1_RXSpd

void smb1_LargePlatformCollision(byte param_1);
#define LargePlatformCollision smb1_LargePlatformCollision

void smb1_SmallPlatformCollision(byte param_1);
#define SmallPlatformCollision smb1_SmallPlatformCollision

void smb1_ProcLPlatCollisions(byte param_1,byte param_2,byte param_3, byte objoff);
#define ProcLPlatCollisions smb1_ProcLPlatCollisions

void smb1_PositionPlayerOnS_Plat(byte param_1,byte param_2);
#define PositionPlayerOnS_Plat smb1_PositionPlayerOnS_Plat

void smb1_PositionPlayerOnVPlat(byte param_1);
#define PositionPlayerOnVPlat smb1_PositionPlayerOnVPlat

bool smb1_CheckPlayerVertical(void);
#define CheckPlayerVertical smb1_CheckPlayerVertical

void smb1_PlayerBGCollision(void);
#define PlayerBGCollision smb1_PlayerBGCollision

void smb1_HandleClimbing(byte param_1,byte param_2,u16 mt_x);
#define HandleClimbing smb1_HandleClimbing

bool smb1_ChkInvisibleMTiles(byte param_1);
#define ChkInvisibleMTiles smb1_ChkInvisibleMTiles

void smb1_ChkForLandJumpSpring(byte param_1);
#define ChkForLandJumpSpring smb1_ChkForLandJumpSpring

bool smb1_ChkJumpspringMetatiles(byte param_1);
#define ChkJumpspringMetatiles smb1_ChkJumpspringMetatiles

void smb1_HandlePipeEntry(byte param_1,byte param_2);
#define HandlePipeEntry smb1_HandlePipeEntry

void smb1_ImpedePlayerMove(byte param_1);
#define ImpedePlayerMove smb1_ImpedePlayerMove

bool smb1_CheckForSolidMTiles(byte param_1);
#define CheckForSolidMTiles smb1_CheckForSolidMTiles

bool smb1_CheckForClimbMTiles(byte param_1);
#define CheckForClimbMTiles smb1_CheckForClimbMTiles

bool smb1_CheckForCoinMTiles(byte param_1);
#define CheckForCoinMTiles smb1_CheckForCoinMTiles

byte smb1_GetMTileAttrib(byte param_1);
#define GetMTileAttrib smb1_GetMTileAttrib

void smb1_EnemyToBGCollisionDet(byte param_1);
#define EnemyToBGCollisionDet smb1_EnemyToBGCollisionDet

void smb1_ChkToStunEnemies(byte param_1,byte param_2);
#define ChkToStunEnemies smb1_ChkToStunEnemies

void smb1_SetStun2(byte param_1);
#define SetStun2 smb1_SetStun2

void smb1_ChkForRedKoopa(byte param_1);
#define ChkForRedKoopa smb1_ChkForRedKoopa

void smb1_DoEnemySideCheck(byte param_1);
#define DoEnemySideCheck smb1_DoEnemySideCheck

void smb1_ChkForBump_HammerBroJ(byte param_1);
#define ChkForBump_HammerBroJ smb1_ChkForBump_HammerBroJ

struct_ncr00 smb1_PlayerEnemyDiff(byte param_1);
#define PlayerEnemyDiff smb1_PlayerEnemyDiff

void smb1_EnemyLanding(byte param_1);
#define EnemyLanding smb1_EnemyLanding

bool smb1_SubtEnemyYPos(byte param_1);
#define SubtEnemyYPos smb1_SubtEnemyYPos

void smb1_EnemyJump(byte param_1);
#define EnemyJump smb1_EnemyJump

void smb1_HammerBroBGColl(byte param_1);
#define HammerBroBGColl smb1_HammerBroBGColl

void smb1_KillEnemyAboveBlock(byte param_1);
#define KillEnemyAboveBlock smb1_KillEnemyAboveBlock

struct_azr04 smb1_ChkUnderEnemy(byte param_1);
#define ChkUnderEnemy smb1_ChkUnderEnemy

bool smb1_ChkForNonSolids(byte param_1);
#define ChkForNonSolids smb1_ChkForNonSolids

void smb1_FireballBGCollision(byte param_1);
#define FireballBGCollision smb1_FireballBGCollision

void smb1_GetFireballBoundBox(byte param_1);
#define GetFireballBoundBox smb1_GetFireballBoundBox

void smb1_GetMiscBoundBox(byte param_1);
#define GetMiscBoundBox smb1_GetMiscBoundBox

void smb1_GetEnemyBoundBox(byte param_1);
#define GetEnemyBoundBox smb1_GetEnemyBoundBox

void smb1_SmallPlatformBoundBox(byte param_1);
#define SmallPlatformBoundBox smb1_SmallPlatformBoundBox

void smb1_GetMaskedOffScrBits(byte param_1,byte param_2,byte param_3);
#define GetMaskedOffScrBits smb1_GetMaskedOffScrBits

void smb1_LargePlatformBoundBox(byte param_1);
#define LargePlatformBoundBox smb1_LargePlatformBoundBox

void smb1_SetupEOffsetFBBox(byte param_1);
#define SetupEOffsetFBBox smb1_SetupEOffsetFBBox

void smb1_MoveBoundBoxOffscreen(byte param_1);
#define MoveBoundBoxOffscreen smb1_MoveBoundBoxOffscreen

void smb1_BoundingBoxCore(byte param_1,byte param_2);
#define BoundingBoxCore smb1_BoundingBoxCore

void smb1_CheckRightScreenBBox(byte param_1);
#define CheckRightScreenBBox smb1_CheckRightScreenBBox

bool smb1_PlayerCollisionCore(byte param_1);
#define PlayerCollisionCore smb1_PlayerCollisionCore

bool smb1_SprObjectCollisionCore(byte param_1,byte param_2);
#define SprObjectCollisionCore smb1_SprObjectCollisionCore

struct blockbuffer_colli_result smb1_BlockBufferColli_Feet(byte param_1);
#define BlockBufferColli_Feet smb1_BlockBufferColli_Feet

struct blockbuffer_colli_result smb1_BlockBufferColli_Head(byte param_1);
#define BlockBufferColli_Head smb1_BlockBufferColli_Head

struct blockbuffer_colli_result smb1_BlockBufferColli_Side(byte param_1);
#define BlockBufferColli_Side smb1_BlockBufferColli_Side

struct blockbuffer_colli_result smb1_BlockBufferCollision(byte param_1,byte param_2,byte param_3);
#define BlockBufferCollision smb1_BlockBufferCollision

void smb1_DrawVine(byte param_1);
#define DrawVine smb1_DrawVine

void smb1_DrawHammer(byte objoff);
#define DrawHammer smb1_DrawHammer

void smb1_FlagpoleGfxHandler(byte param_1);
#define FlagpoleGfxHandler smb1_FlagpoleGfxHandler

void smb1_DrawLargePlatform(byte param_1);
#define DrawLargePlatform smb1_DrawLargePlatform

void smb1_JCoinGfxHandler(byte param_1);
#define JCoinGfxHandler smb1_JCoinGfxHandler

void smb1_DrawPowerUp(byte objoff);
#define DrawPowerUp smb1_DrawPowerUp

void smb1_EnemyGfxHandler(byte param_1);
#define EnemyGfxHandler smb1_EnemyGfxHandler

void smb1_DrawEnemyObject(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,byte param_7,byte param_8,byte param_9);
#define DrawEnemyObject smb1_DrawEnemyObject

void smb1_SprObjectOffscrChk(byte objoff);
#define SprObjectOffscrChk smb1_SprObjectOffscrChk

struct_xyr02 smb1_DrawEnemyObjRow(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6);
#define DrawEnemyObjRow smb1_DrawEnemyObjRow

struct_xyr02 smb1_DrawOneSpriteRow(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,byte param_7,byte param_8);
#define DrawOneSpriteRow smb1_DrawOneSpriteRow

void smb1_DrawBlock(byte param_1);
#define DrawBlock smb1_DrawBlock

void smb1_DrawBrickChunks(byte param_1);
#define DrawBrickChunks smb1_DrawBrickChunks

void smb1_DrawFireball(byte param_1);
#define DrawFireball smb1_DrawFireball

void smb1_DrawFirebar(byte param_1);
#define DrawFirebar smb1_DrawFirebar

void smb1_DrawExplosion_Fireball(byte param_1);
#define DrawExplosion_Fireball smb1_DrawExplosion_Fireball

void smb1_DrawExplosion_Fireworks(byte param_1,byte param_2);
#define DrawExplosion_Fireworks smb1_DrawExplosion_Fireworks

void smb1_DrawSmallPlatform(byte param_1);
#define DrawSmallPlatform smb1_DrawSmallPlatform

void smb1_DrawBubble(byte param_1);
#define DrawBubble smb1_DrawBubble

void smb1_PlayerGfxHandler(void);
#define PlayerGfxHandler smb1_PlayerGfxHandler

void smb1_FindPlayerAction(void);
#define FindPlayerAction smb1_FindPlayerAction

void smb1_PlayerGfxProcessing(byte param_1);
#define PlayerGfxProcessing smb1_PlayerGfxProcessing

void smb1_DrawPlayer_Intermediate(void);
#define DrawPlayer_Intermediate smb1_DrawPlayer_Intermediate

void smb1_RenderPlayerSub(byte param_1);
#define RenderPlayerSub smb1_RenderPlayerSub

void smb1_DrawPlayerLoop(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,byte param_7);
#define DrawPlayerLoop smb1_DrawPlayerLoop

byte smb1_ProcessPlayerAction(void);
#define ProcessPlayerAction smb1_ProcessPlayerAction

byte smb1_GetCurrentAnimOffset(byte param_1);
#define GetCurrentAnimOffset smb1_GetCurrentAnimOffset

byte smb1_FourFrameExtent(byte param_1);
#define FourFrameExtent smb1_FourFrameExtent

byte smb1_ThreeFrameExtent(byte param_1);
#define ThreeFrameExtent smb1_ThreeFrameExtent

byte smb1_AnimationControl(byte param_1,byte param_2);
#define AnimationControl smb1_AnimationControl

byte smb1_GetGfxOffsetAdder(byte param_1);
#define GetGfxOffsetAdder smb1_GetGfxOffsetAdder

byte smb1_HandleChangeSize(void);
#define HandleChangeSize smb1_HandleChangeSize

byte smb1_GetOffsetFromAnimCtrl(byte param_1,byte param_2);
#define GetOffsetFromAnimCtrl smb1_GetOffsetFromAnimCtrl

void smb1_ChkForPlayerAttrib(void);
#define ChkForPlayerAttrib smb1_ChkForPlayerAttrib

byte smb1_RelativePlayerPosition(void);
#define RelativePlayerPosition smb1_RelativePlayerPosition

void smb1_RelativeBubblePosition(byte param_1);
#define RelativeBubblePosition smb1_RelativeBubblePosition

void smb1_RelativeFireballPosition(byte param_1);
#define RelativeFireballPosition smb1_RelativeFireballPosition

void smb1_RelativeMiscPosition(byte param_1);
#define RelativeMiscPosition smb1_RelativeMiscPosition

void smb1_RelativeEnemyPosition(byte param_1);
#define RelativeEnemyPosition smb1_RelativeEnemyPosition

void smb1_RelativeBlockPosition(byte param_1);
#define RelativeBlockPosition smb1_RelativeBlockPosition

void smb1_GetObjRelativePosition(byte param_1,byte param_2);
#define GetObjRelativePosition smb1_GetObjRelativePosition

void smb1_GetPlayerOffscreenBits(void);
#define GetPlayerOffscreenBits smb1_GetPlayerOffscreenBits

void smb1_GetFireballOffscreenBits(byte param_1);
#define GetFireballOffscreenBits smb1_GetFireballOffscreenBits

void smb1_GetBubbleOffscreenBits(byte param_1);
#define GetBubbleOffscreenBits smb1_GetBubbleOffscreenBits

void smb1_GetMiscOffscreenBits(byte param_1);
#define GetMiscOffscreenBits smb1_GetMiscOffscreenBits

byte smb1_GetProperObjOffset(byte param_1,byte param_2);
#define GetProperObjOffset smb1_GetProperObjOffset

void smb1_GetEnemyOffscreenBits(byte param_1);
#define GetEnemyOffscreenBits smb1_GetEnemyOffscreenBits

void smb1_GetBlockOffscreenBits(byte param_1);
#define GetBlockOffscreenBits smb1_GetBlockOffscreenBits

void smb1_GetOffScreenBitsSet(byte param_1,byte param_2);
#define GetOffScreenBitsSet smb1_GetOffScreenBitsSet

byte smb1_GetXOffscreenBits(byte param_1);
#define GetXOffscreenBits smb1_GetXOffscreenBits

byte smb1_GetYOffscreenBits(byte param_1);
#define GetYOffscreenBits smb1_GetYOffscreenBits

byte smb1_DividePDiff(byte param_1,byte param_2,bool param_3,byte param_4,byte param_5);
#define DividePDiff smb1_DividePDiff

struct_xyr02 smb1_DrawSpriteObject(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,byte param_7,byte param_8);
#define DrawSpriteObject smb1_DrawSpriteObject


#pragma pack(pop)
