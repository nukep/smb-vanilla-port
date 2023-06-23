#pragma once
#pragma pack(push, 1)
typedef unsigned char   undefined;


typedef unsigned char    byte;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
#define unkbyte9   unsigned long long
#define unkbyte10   unsigned long long
#define unkbyte11   unsigned long long
#define unkbyte12   unsigned long long
#define unkbyte13   unsigned long long
#define unkbyte14   unsigned long long
#define unkbyte15   unsigned long long
#define unkbyte16   unsigned long long

#define unkuint9   unsigned long long
#define unkuint10   unsigned long long
#define unkuint11   unsigned long long
#define unkuint12   unsigned long long
#define unkuint13   unsigned long long
#define unkuint14   unsigned long long
#define unkuint15   unsigned long long
#define unkuint16   unsigned long long

#define unkint9   long long
#define unkint10   long long
#define unkint11   long long
#define unkint12   long long
#define unkint13   long long
#define unkint14   long long
#define unkint15   long long
#define unkint16   long long

#define unkfloat1   float
#define unkfloat2   float
#define unkfloat3   float
#define unkfloat5   double
#define unkfloat6   double
#define unkfloat7   double
#define unkfloat9   long double
#define unkfloat11   long double
#define unkfloat12   long double
#define unkfloat13   long double
#define unkfloat14   long double
#define unkfloat15   long double
#define unkfloat16   long double

#define BADSPACEBASE   void
#define code   void

typedef struct struct_ycr07 struct_ycr07, *Pstruct_ycr07;

struct struct_ycr07 {
  byte y;
  bool c;
  byte r07;
};
static inline struct_ycr07 CAST_INT_TO_struct_ycr07(uint64_t v) {
  struct_ycr07 a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_xr00r01 struct_xr00r01, *Pstruct_xr00r01;

struct struct_xr00r01 {
  byte x;
  byte r00;
  byte r01;
};
static inline struct_xr00r01 CAST_INT_TO_struct_xr00r01(uint64_t v) {
  struct_xr00r01 a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_nr00i struct_nr00i, *Pstruct_nr00i;

struct struct_nr00i {
  bool n;
  byte r00;
  bool i;
};
static inline struct_nr00i CAST_INT_TO_struct_nr00i(uint64_t v) {
  struct_nr00i a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_ncr00 struct_ncr00, *Pstruct_ncr00;

struct struct_ncr00 {
  bool n;
  bool c;
  byte r00;
};
static inline struct_ncr00 CAST_INT_TO_struct_ncr00(uint64_t v) {
  struct_ncr00 a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_xr00r06 struct_xr00r06, *Pstruct_xr00r06;

struct struct_xr00r06 {
  byte x;
  byte r00;
  byte r06;
};
static inline struct_xr00r06 CAST_INT_TO_struct_xr00r06(uint64_t v) {
  struct_xr00r06 a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_r06r07i struct_r06r07i, *Pstruct_r06r07i;

struct struct_r06r07i {
  byte r06;
  byte r07;
  bool i;
};
static inline struct_r06r07i CAST_INT_TO_struct_r06r07i(uint64_t v) {
  struct_r06r07i a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_ayr02r04r06r07 struct_ayr02r04r06r07, *Pstruct_ayr02r04r06r07;

struct struct_ayr02r04r06r07 {
  byte a;
  byte y;
  byte r02;
  byte r04;
  byte r06;
  byte r07;
};
static inline struct_ayr02r04r06r07 CAST_INT_TO_struct_ayr02r04r06r07(uint64_t v) {
  struct_ayr02r04r06r07 a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_azr02r04r06r07 struct_azr02r04r06r07, *Pstruct_azr02r04r06r07;

struct struct_azr02r04r06r07 {
  byte a;
  bool z;
  byte r02;
  byte r04;
  byte r06;
  byte r07;
};
static inline struct_azr02r04r06r07 CAST_INT_TO_struct_azr02r04r06r07(uint64_t v) {
  struct_azr02r04r06r07 a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_r01r02r03 struct_r01r02r03, *Pstruct_r01r02r03;

struct struct_r01r02r03 {
  byte r01;
  byte r02;
  byte r03;
};
static inline struct_r01r02r03 CAST_INT_TO_struct_r01r02r03(uint64_t v) {
  struct_r01r02r03 a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_axzr04 struct_axzr04, *Pstruct_axzr04;

struct struct_axzr04 {
  byte a;
  byte x;
  bool z;
  byte r04;
};
static inline struct_axzr04 CAST_INT_TO_struct_axzr04(uint64_t v) {
  struct_axzr04 a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_xyi struct_xyi, *Pstruct_xyi;

struct struct_xyi {
  byte x;
  byte y;
  bool i;
};
static inline struct_xyi CAST_INT_TO_struct_xyi(uint64_t v) {
  struct_xyi a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_axyz struct_axyz, *Pstruct_axyz;

struct struct_axyz {
  byte a;
  byte x;
  byte y;
  bool z;
};
static inline struct_axyz CAST_INT_TO_struct_axyz(uint64_t v) {
  struct_axyz a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_axr00 struct_axr00, *Pstruct_axr00;

struct struct_axr00 {
  byte a;
  byte x;
  byte r00;
};
static inline struct_axr00 CAST_INT_TO_struct_axr00(uint64_t v) {
  struct_axr00 a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_azi struct_azi, *Pstruct_azi;

struct struct_azi {
  byte a;
  bool z;
  bool i;
};
static inline struct_azi CAST_INT_TO_struct_azi(uint64_t v) {
  struct_azi a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_ayz struct_ayz, *Pstruct_ayz;

struct struct_ayz {
  byte a;
  byte y;
  bool z;
};
static inline struct_ayz CAST_INT_TO_struct_ayz(uint64_t v) {
  struct_ayz a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_ayi struct_ayi, *Pstruct_ayi;

struct struct_ayi {
  byte a;
  byte y;
  bool i;
};
static inline struct_ayi CAST_INT_TO_struct_ayi(uint64_t v) {
  struct_ayi a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_axy struct_axy, *Pstruct_axy;

struct struct_axy {
  byte a;
  byte x;
  byte y;
};
static inline struct_axy CAST_INT_TO_struct_axy(uint64_t v) {
  struct_axy a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_axz struct_axz, *Pstruct_axz;

struct struct_axz {
  byte a;
  byte x;
  bool z;
};
static inline struct_axz CAST_INT_TO_struct_axz(uint64_t v) {
  struct_axz a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_yr07i struct_yr07i, *Pstruct_yr07i;

struct struct_yr07i {
  byte y;
  byte r07;
  bool i;
};
static inline struct_yr07i CAST_INT_TO_struct_yr07i(uint64_t v) {
  struct_yr07i a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_axi struct_axi, *Pstruct_axi;

struct struct_axi {
  byte a;
  byte x;
  bool i;
};
static inline struct_axi CAST_INT_TO_struct_axi(uint64_t v) {
  struct_axi a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_xr05i struct_xr05i, *Pstruct_xr05i;

struct struct_xr05i {
  byte x;
  byte r05;
  bool i;
};
static inline struct_xr05i CAST_INT_TO_struct_xr05i(uint64_t v) {
  struct_xr05i a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_xci struct_xci, *Pstruct_xci;

struct struct_xci {
  byte x;
  bool c;
  bool i;
};
static inline struct_xci CAST_INT_TO_struct_xci(uint64_t v) {
  struct_xci a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_xyr02 struct_xyr02, *Pstruct_xyr02;

struct struct_xyr02 {
  byte x;
  byte y;
  byte r02;
};
static inline struct_xyr02 CAST_INT_TO_struct_xyr02(uint64_t v) {
  struct_xyr02 a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_yci struct_yci, *Pstruct_yci;

struct struct_yci {
  byte y;
  bool c;
  bool i;
};
static inline struct_yci CAST_INT_TO_struct_yci(uint64_t v) {
  struct_yci a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_ar00i struct_ar00i, *Pstruct_ar00i;

struct struct_ar00i {
  byte a;
  byte r00;
  bool i;
};
static inline struct_ar00i CAST_INT_TO_struct_ar00i(uint64_t v) {
  struct_ar00i a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_yr06r07 struct_yr06r07, *Pstruct_yr06r07;

struct struct_yr06r07 {
  byte y;
  byte r06;
  byte r07;
};
static inline struct_yr06r07 CAST_INT_TO_struct_yr06r07(uint64_t v) {
  struct_yr06r07 a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_aci struct_aci, *Pstruct_aci;

struct struct_aci {
  byte a;
  bool c;
  bool i;
};
static inline struct_aci CAST_INT_TO_struct_aci(uint64_t v) {
  struct_aci a;
  memcpy(&a, &v, sizeof(a));
  return a;
};

typedef struct struct_xr00i struct_xr00i, *Pstruct_xr00i;

struct struct_xr00i {
  byte x;
  byte r00;
  bool i;
};
static inline struct_xr00i CAST_INT_TO_struct_xr00i(uint64_t v) {
  struct_xr00i a;
  memcpy(&a, &v, sizeof(a));
  return a;
};




void smb2j_jumptable_OperModeExecutionTree(byte param_1,byte param_2);
#define jumptable_OperModeExecutionTree smb2j_jumptable_OperModeExecutionTree

void smb2j_jumptable_VictoryModeSubroutines(byte param_1,byte param_2);
#define jumptable_VictoryModeSubroutines smb2j_jumptable_VictoryModeSubroutines

void smb2j_jumptable_VictoryModeSubroutines_forW8(byte param_1,byte param_2);
#define jumptable_VictoryModeSubroutines_forW8 smb2j_jumptable_VictoryModeSubroutines_forW8

void smb2j_jumptable_ScreenRoutines(byte param_1);
#define jumptable_ScreenRoutines smb2j_jumptable_ScreenRoutines

void smb2j_jumptable_GameOverMode(byte param_1);
#define jumptable_GameOverMode smb2j_jumptable_GameOverMode

void smb2j_jumptable_AreaParserTasks(byte param_1);
#define jumptable_AreaParserTasks smb2j_jumptable_AreaParserTasks

void smb2j_jumptable_DecodeAreaData(byte param_1,byte param_2,byte param_3);
#define jumptable_DecodeAreaData smb2j_jumptable_DecodeAreaData

void smb2j_jumptable_AreaStyleObject(byte param_1,byte param_2);
#define jumptable_AreaStyleObject smb2j_jumptable_AreaStyleObject

void smb2j_jumptable_GameMode(byte param_1);
#define jumptable_GameMode smb2j_jumptable_GameMode

void smb2j_jumptable_GameRoutines(byte param_1);
#define jumptable_GameRoutines smb2j_jumptable_GameRoutines

void smb2j_jumptable_PlayerMovementSubs(byte param_1);
#define jumptable_PlayerMovementSubs smb2j_jumptable_PlayerMovementSubs

void smb2j_jumptable_BumpBlock(byte param_1,byte param_2);
#define jumptable_BumpBlock smb2j_jumptable_BumpBlock

void smb2j_jumptable_CheckpointEnemyID(byte param_1,byte param_2);
#define jumptable_CheckpointEnemyID smb2j_jumptable_CheckpointEnemyID

void smb2j_jumptable_InitEnemyFrenzy(byte param_1,byte param_2);
#define jumptable_InitEnemyFrenzy smb2j_jumptable_InitEnemyFrenzy

byte smb2j_jumptable_RunEnemyObjectsCore(byte param_1,byte param_2);
#define jumptable_RunEnemyObjectsCore smb2j_jumptable_RunEnemyObjectsCore

byte smb2j_jumptable_EnemyMovementSubs(byte param_1,byte param_2);
#define jumptable_EnemyMovementSubs smb2j_jumptable_EnemyMovementSubs

byte smb2j_jumptable_LargePlatformSubroutines(byte param_1,byte param_2);
#define jumptable_LargePlatformSubroutines smb2j_jumptable_LargePlatformSubroutines

byte smb2j_jumptable_RunStarFlagObj(byte param_1,byte param_2);
#define jumptable_RunStarFlagObj smb2j_jumptable_RunStarFlagObj

void smb2j_jumptable_AttractModeSubs(byte param_1);
#define jumptable_AttractModeSubs smb2j_jumptable_AttractModeSubs

void smb2j_jumptable_HardWorldsCheckpoint(byte param_1);
#define jumptable_HardWorldsCheckpoint smb2j_jumptable_HardWorldsCheckpoint

void smb2j_jumptable_AttractModeDiskRoutines(byte param_1);
#define jumptable_AttractModeDiskRoutines smb2j_jumptable_AttractModeDiskRoutines

void smb2j_jumptable_GameModeDiskRoutines(byte param_1);
#define jumptable_GameModeDiskRoutines smb2j_jumptable_GameModeDiskRoutines

void smb2j_jumptable_VictoryModeDiskRoutines(byte param_1);
#define jumptable_VictoryModeDiskRoutines smb2j_jumptable_VictoryModeDiskRoutines

void smb2j_PauseRoutine(void);
#define PauseRoutine smb2j_PauseRoutine

void smb2j_SpriteShuffler(void);
#define SpriteShuffler smb2j_SpriteShuffler

void smb2j_OperModeExecutionTree(void);
#define OperModeExecutionTree smb2j_OperModeExecutionTree

void smb2j_MoveAllSpritesOffscreen(void);
#define MoveAllSpritesOffscreen smb2j_MoveAllSpritesOffscreen

void smb2j_MoveSpritesOffscreen(void);
#define MoveSpritesOffscreen smb2j_MoveSpritesOffscreen

void smb2j_VictoryMode(byte param_1);
#define VictoryMode smb2j_VictoryMode

void smb2j_VictoryModeSubroutines(byte param_1);
#define VictoryModeSubroutines smb2j_VictoryModeSubroutines

void smb2j_SetupVictoryMode(void);
#define SetupVictoryMode smb2j_SetupVictoryMode

void smb2j_DrawTitleScreen(void);
#define DrawTitleScreen smb2j_DrawTitleScreen

void smb2j_PlayerVictoryWalk(void);
#define PlayerVictoryWalk smb2j_PlayerVictoryWalk

void smb2j_PrintVictoryMessages(void);
#define PrintVictoryMessages smb2j_PrintVictoryMessages

void smb2j_EndCastleAward(void);
#define EndCastleAward smb2j_EndCastleAward

void smb2j_PlayerEndWorld(void);
#define PlayerEndWorld smb2j_PlayerEndWorld

byte smb2j_FloateyNumbersRoutine(byte param_1);
#define FloateyNumbersRoutine smb2j_FloateyNumbersRoutine

void smb2j_ScreenRoutines(void);
#define ScreenRoutines smb2j_ScreenRoutines

void smb2j_InitScreen(void);
#define InitScreen smb2j_InitScreen

void smb2j_InitScreenPalette(void);
#define InitScreenPalette smb2j_InitScreenPalette

void smb2j_SetupIntermediate(void);
#define SetupIntermediate smb2j_SetupIntermediate

void smb2j_GetAreaPalette(void);
#define GetAreaPalette smb2j_GetAreaPalette

void smb2j_GetBackgroundColor(void);
#define GetBackgroundColor smb2j_GetBackgroundColor

byte smb2j_GetPlayerColors(void);
#define GetPlayerColors smb2j_GetPlayerColors

void smb2j_GetAlternatePalette1(void);
#define GetAlternatePalette1 smb2j_GetAlternatePalette1

void smb2j_WriteTopStatusLine(void);
#define WriteTopStatusLine smb2j_WriteTopStatusLine

void smb2j_WriteBottomStatusLine(void);
#define WriteBottomStatusLine smb2j_WriteBottomStatusLine

byte smb2j_GetWorldNumForDisplay(void);
#define GetWorldNumForDisplay smb2j_GetWorldNumForDisplay

void smb2j_DisplayTimeUp(void);
#define DisplayTimeUp smb2j_DisplayTimeUp

void smb2j_DisplayIntermediate(void);
#define DisplayIntermediate smb2j_DisplayIntermediate

void smb2j_AreaParserTaskControl(void);
#define AreaParserTaskControl smb2j_AreaParserTaskControl

void smb2j_WriteGameText(byte param_1);
#define WriteGameText smb2j_WriteGameText

void smb2j_WriteWarpZoneMessage(byte param_1);
#define WriteWarpZoneMessage smb2j_WriteWarpZoneMessage

void smb2j_ResetSpritesAndScreenTimer(void);
#define ResetSpritesAndScreenTimer smb2j_ResetSpritesAndScreenTimer

void smb2j_ResetScreenTimer(void);
#define ResetScreenTimer smb2j_ResetScreenTimer

void smb2j_RenderAreaGraphics(void);
#define RenderAreaGraphics smb2j_RenderAreaGraphics

void smb2j_RenderAttributeTables(void);
#define RenderAttributeTables smb2j_RenderAttributeTables

void smb2j_ColorRotation(void);
#define ColorRotation smb2j_ColorRotation

byte smb2j_RemoveCoin_Axe(byte param_1,byte param_2);
#define RemoveCoin_Axe smb2j_RemoveCoin_Axe

void smb2j_ReplaceBlockMetatile(byte param_1,byte param_2,byte param_3,byte param_4);
#define ReplaceBlockMetatile smb2j_ReplaceBlockMetatile

void smb2j_DestroyBlockMetatile(byte param_1,byte param_2,byte param_3);
#define DestroyBlockMetatile smb2j_DestroyBlockMetatile

void smb2j_WriteBlockMetatile(byte param_1,byte param_2,byte param_3,byte param_4);
#define WriteBlockMetatile smb2j_WriteBlockMetatile

void smb2j_MoveVOffset(byte param_1);
#define MoveVOffset smb2j_MoveVOffset

byte smb2j_PutBlockMetatile(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
#define PutBlockMetatile smb2j_PutBlockMetatile

void smb2j_RemBridge(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
#define RemBridge smb2j_RemBridge

void smb2j_InitializeNameTables(void);
#define InitializeNameTables smb2j_InitializeNameTables

void smb2j_WritePPUReg1(byte param_1);
#define WritePPUReg1 smb2j_WritePPUReg1

void smb2j_PrintStatusBarNumbers(byte param_1);
#define PrintStatusBarNumbers smb2j_PrintStatusBarNumbers

void smb2j_OutputNumbers(byte param_1);
#define OutputNumbers smb2j_OutputNumbers

void smb2j_DigitsMathRoutine(byte param_1);
#define DigitsMathRoutine smb2j_DigitsMathRoutine

void smb2j_UpdateTopScore(void);
#define UpdateTopScore smb2j_UpdateTopScore

void smb2j_TopScoreCheck(byte param_1);
#define TopScoreCheck smb2j_TopScoreCheck

void smb2j_InitializeArea(void);
#define InitializeArea smb2j_InitializeArea

void smb2j_SecondaryGameSetup(void);
#define SecondaryGameSetup smb2j_SecondaryGameSetup

void smb2j_GetAreaMusic(void);
#define GetAreaMusic smb2j_GetAreaMusic

void smb2j_Entrance_GameTimerSetup(byte param_1);
#define Entrance_GameTimerSetup smb2j_Entrance_GameTimerSetup

void smb2j_PlayerLoseLife(void);
#define PlayerLoseLife smb2j_PlayerLoseLife

void smb2j_GameOverMode(void);
#define GameOverMode smb2j_GameOverMode

void smb2j_SetupGameOver(void);
#define SetupGameOver smb2j_SetupGameOver

void smb2j_RunGameOver(void);
#define RunGameOver smb2j_RunGameOver

void smb2j_TerminateGame(void);
#define TerminateGame smb2j_TerminateGame

void smb2j_ContinueGame(void);
#define ContinueGame smb2j_ContinueGame

void smb2j_DoNothing(void);
#define DoNothing smb2j_DoNothing

void smb2j_AreaParserTaskHandler(void);
#define AreaParserTaskHandler smb2j_AreaParserTaskHandler

void smb2j_AreaParserTasks(byte param_1);
#define AreaParserTasks smb2j_AreaParserTasks

void smb2j_IncrementColumnPos(void);
#define IncrementColumnPos smb2j_IncrementColumnPos

void smb2j_AreaParserCore(void);
#define AreaParserCore smb2j_AreaParserCore

void smb2j_ProcessAreaData(void);
#define ProcessAreaData smb2j_ProcessAreaData

void smb2j_IncAreaObjOffset(void);
#define IncAreaObjOffset smb2j_IncAreaObjOffset

void smb2j_DecodeAreaData(byte param_1,byte param_2);
#define DecodeAreaData smb2j_DecodeAreaData

void smb2j_LoopCmdE(void);
#define LoopCmdE smb2j_LoopCmdE

void smb2j_AlterAreaAttributes(byte param_1);
#define AlterAreaAttributes smb2j_AlterAreaAttributes

void smb2j_ScrollLockObject_Warp(void);
#define ScrollLockObject_Warp smb2j_ScrollLockObject_Warp

void smb2j_ScrollLockObject(void);
#define ScrollLockObject smb2j_ScrollLockObject

void smb2j_KillEnemies(byte param_1);
#define KillEnemies smb2j_KillEnemies

void smb2j_AreaFrenzy(byte param_1);
#define AreaFrenzy smb2j_AreaFrenzy

void smb2j_AreaStyleObject(byte param_1);
#define AreaStyleObject smb2j_AreaStyleObject

void smb2j_TreeLedge(byte param_1);
#define TreeLedge smb2j_TreeLedge

void smb2j_CloudLedge(byte param_1);
#define CloudLedge smb2j_CloudLedge

void smb2j_NoUnder(byte param_1,byte param_2);
#define NoUnder smb2j_NoUnder

void smb2j_PulleyRopeObject(byte param_1);
#define PulleyRopeObject smb2j_PulleyRopeObject

void smb2j_CastleObject(byte param_1);
#define CastleObject smb2j_CastleObject

void smb2j_WaterPipe(byte param_1);
#define WaterPipe smb2j_WaterPipe

void smb2j_IntroPipe(byte param_1);
#define IntroPipe smb2j_IntroPipe

void smb2j_ExitPipe(byte param_1);
#define ExitPipe smb2j_ExitPipe

struct_yci smb2j_RenderSidewaysPipe(byte param_1,byte param_2);
#define RenderSidewaysPipe smb2j_RenderSidewaysPipe

void smb2j_VerticalPipe(byte param_1,byte param_2);
#define VerticalPipe smb2j_VerticalPipe

struct_yr06r07 smb2j_GetPipeHeight(byte param_1);
#define GetPipeHeight smb2j_GetPipeHeight

void smb2j_SetupPiranhaPlant(byte param_1,byte param_2,byte param_3);
#define SetupPiranhaPlant smb2j_SetupPiranhaPlant

struct_xci smb2j_FindEmptyEnemySlot(void);
#define FindEmptyEnemySlot smb2j_FindEmptyEnemySlot

void smb2j_Hole_Water(byte param_1);
#define Hole_Water smb2j_Hole_Water

void smb2j_QuestionBlockRow_High(byte param_1);
#define QuestionBlockRow_High smb2j_QuestionBlockRow_High

void smb2j_QuestionBlockRow_Low(byte param_1);
#define QuestionBlockRow_Low smb2j_QuestionBlockRow_Low

void smb2j_Bridge_High(byte param_1);
#define Bridge_High smb2j_Bridge_High

void smb2j_Bridge_Middle(byte param_1);
#define Bridge_Middle smb2j_Bridge_Middle

void smb2j_Bridge_Low(byte param_1);
#define Bridge_Low smb2j_Bridge_Low

void smb2j_FlagBalls_Residual(byte param_1);
#define FlagBalls_Residual smb2j_FlagBalls_Residual

void smb2j_FlagpoleObject(void);
#define FlagpoleObject smb2j_FlagpoleObject

void smb2j_EndlessRope(void);
#define EndlessRope smb2j_EndlessRope

void smb2j_BalancePlatRope(byte param_1);
#define BalancePlatRope smb2j_BalancePlatRope

void smb2j_RowOfCoins(byte param_1);
#define RowOfCoins smb2j_RowOfCoins

void smb2j_CastleBridgeObj(byte param_1,byte param_2);
#define CastleBridgeObj smb2j_CastleBridgeObj

void smb2j_AxeObj(byte param_1);
#define AxeObj smb2j_AxeObj

void smb2j_ChainObj(byte param_1);
#define ChainObj smb2j_ChainObj

void smb2j_EmptyBlock(byte param_1);
#define EmptyBlock smb2j_EmptyBlock

void smb2j_RowOfBricks(byte param_1);
#define RowOfBricks smb2j_RowOfBricks

void smb2j_RowOfSolidBlocks(byte param_1);
#define RowOfSolidBlocks smb2j_RowOfSolidBlocks

void smb2j_ColumnOfBricks(byte param_1);
#define ColumnOfBricks smb2j_ColumnOfBricks

void smb2j_ColumnOfSolidBlocks(byte param_1);
#define ColumnOfSolidBlocks smb2j_ColumnOfSolidBlocks

void smb2j_BulletBillCannon(byte param_1);
#define BulletBillCannon smb2j_BulletBillCannon

void smb2j_StaircaseObject(byte param_1);
#define StaircaseObject smb2j_StaircaseObject

void smb2j_Jumpspring(byte param_1);
#define Jumpspring smb2j_Jumpspring

void smb2j_Hidden1UpBlock(byte param_1,byte param_2);
#define Hidden1UpBlock smb2j_Hidden1UpBlock

void smb2j_QuestionBlock(byte param_1,byte param_2);
#define QuestionBlock smb2j_QuestionBlock

void smb2j_BrickWithCoins(byte param_1,byte param_2);
#define BrickWithCoins smb2j_BrickWithCoins

void smb2j_BrickWithItem(byte param_1,byte param_2);
#define BrickWithItem smb2j_BrickWithItem

byte smb2j_GetAreaObjectID(byte param_1);
#define GetAreaObjectID smb2j_GetAreaObjectID

void smb2j_Hole_Empty(byte param_1);
#define Hole_Empty smb2j_Hole_Empty

byte smb2j_RenderUnderPart(byte param_1,byte param_2,byte param_3);
#define RenderUnderPart smb2j_RenderUnderPart

struct_ycr07 smb2j_ChkLrgObjLength(byte param_1);
#define ChkLrgObjLength smb2j_ChkLrgObjLength

bool smb2j_ChkLrgObjFixedLength(byte param_1,byte param_2);
#define ChkLrgObjFixedLength smb2j_ChkLrgObjFixedLength

struct_yr07i smb2j_GetLrgObjAttrib(byte param_1);
#define GetLrgObjAttrib smb2j_GetLrgObjAttrib

byte smb2j_GetAreaObjXPosition(void);
#define GetAreaObjXPosition smb2j_GetAreaObjXPosition

byte smb2j_GetAreaObjYPosition(byte param_1);
#define GetAreaObjYPosition smb2j_GetAreaObjYPosition

struct_r06r07i smb2j_GetBlockBufferAddr(byte param_1);
#define GetBlockBufferAddr smb2j_GetBlockBufferAddr

void smb2j_GameMode(void);
#define GameMode smb2j_GameMode

void smb2j_GameCoreRoutine(void);
#define GameCoreRoutine smb2j_GameCoreRoutine

void smb2j_UpdScrollVar(void);
#define UpdScrollVar smb2j_UpdScrollVar

void smb2j_ScrollHandler(void);
#define ScrollHandler smb2j_ScrollHandler

void smb2j_ChkPOffscr(void);
#define ChkPOffscr smb2j_ChkPOffscr

byte smb2j_GetScreenPosition(void);
#define GetScreenPosition smb2j_GetScreenPosition

void smb2j_GameRoutines(void);
#define GameRoutines smb2j_GameRoutines

void smb2j_PlayerEntrance(void);
#define PlayerEntrance smb2j_PlayerEntrance

void smb2j_AutoControlPlayer(byte param_1);
#define AutoControlPlayer smb2j_AutoControlPlayer

void smb2j_PlayerCtrlRoutine(void);
#define PlayerCtrlRoutine smb2j_PlayerCtrlRoutine

void smb2j_Vine_AutoClimb(void);
#define Vine_AutoClimb smb2j_Vine_AutoClimb

void smb2j_SetEntr(void);
#define SetEntr smb2j_SetEntr

void smb2j_VerticalPipeEntry(void);
#define VerticalPipeEntry smb2j_VerticalPipeEntry

void smb2j_MovePlayerYAxis(byte param_1);
#define MovePlayerYAxis smb2j_MovePlayerYAxis

void smb2j_SideExitPipeEntry(void);
#define SideExitPipeEntry smb2j_SideExitPipeEntry

byte smb2j_ChgAreaMode(void);
#define ChgAreaMode smb2j_ChgAreaMode

void smb2j_EnterSidePipe(void);
#define EnterSidePipe smb2j_EnterSidePipe

void smb2j_PlayerChangeSize(void);
#define PlayerChangeSize smb2j_PlayerChangeSize

void smb2j_PlayerInjuryBlink(void);
#define PlayerInjuryBlink smb2j_PlayerInjuryBlink

void smb2j_InitChangeSize(void);
#define InitChangeSize smb2j_InitChangeSize

void smb2j_PlayerDeath(void);
#define PlayerDeath smb2j_PlayerDeath

void smb2j_DonePlayerTask(void);
#define DonePlayerTask smb2j_DonePlayerTask

void smb2j_PlayerFireFlower(void);
#define PlayerFireFlower smb2j_PlayerFireFlower

void smb2j_CyclePlayerPalette(byte param_1);
#define CyclePlayerPalette smb2j_CyclePlayerPalette

void smb2j_ResetPalStar(void);
#define ResetPalStar smb2j_ResetPalStar

void smb2j_FlagpoleSlide(void);
#define FlagpoleSlide smb2j_FlagpoleSlide

void smb2j_PlayerEndLevel(void);
#define PlayerEndLevel smb2j_PlayerEndLevel

void smb2j_NextArea(void);
#define NextArea smb2j_NextArea

void smb2j_PlayerMovementSubs(void);
#define PlayerMovementSubs smb2j_PlayerMovementSubs

void smb2j_OnGroundStateSub(void);
#define OnGroundStateSub smb2j_OnGroundStateSub

void smb2j_FallingSub(void);
#define FallingSub smb2j_FallingSub

void smb2j_JumpSwimSub(void);
#define JumpSwimSub smb2j_JumpSwimSub

void smb2j_LRAir(void);
#define LRAir smb2j_LRAir

void smb2j_ClimbingSub(void);
#define ClimbingSub smb2j_ClimbingSub

void smb2j_PlayerPhysicsSub(void);
#define PlayerPhysicsSub smb2j_PlayerPhysicsSub

void smb2j_GetPlayerAnimSpeed(void);
#define GetPlayerAnimSpeed smb2j_GetPlayerAnimSpeed

void smb2j_ImposeFriction(byte param_1);
#define ImposeFriction smb2j_ImposeFriction

void smb2j_ProcFireball_Bubble(void);
#define ProcFireball_Bubble smb2j_ProcFireball_Bubble

void smb2j_FireballObjCore(byte param_1);
#define FireballObjCore smb2j_FireballObjCore

void smb2j_BubbleCheck(byte param_1);
#define BubbleCheck smb2j_BubbleCheck

void smb2j_SetupBubble(byte param_1,byte param_2);
#define SetupBubble smb2j_SetupBubble

void smb2j_MoveBubl(byte param_1,byte param_2);
#define MoveBubl smb2j_MoveBubl

void smb2j_RunGameTimer(void);
#define RunGameTimer smb2j_RunGameTimer

void smb2j_WarpZoneObject(byte param_1);
#define WarpZoneObject smb2j_WarpZoneObject

void smb2j_ProcessWhirlpools(void);
#define ProcessWhirlpools smb2j_ProcessWhirlpools

void smb2j_FlagpoleRoutine(void);
#define FlagpoleRoutine smb2j_FlagpoleRoutine

byte smb2j_JumpspringHandler(byte param_1);
#define JumpspringHandler smb2j_JumpspringHandler

void smb2j_Setup_Vine(byte param_1,byte param_2);
#define Setup_Vine smb2j_Setup_Vine

byte smb2j_VineObjectHandler(byte param_1);
#define VineObjectHandler smb2j_VineObjectHandler

void smb2j_ProcessCannons(void);
#define ProcessCannons smb2j_ProcessCannons

byte smb2j_BulletBillHandler(byte param_1);
#define BulletBillHandler smb2j_BulletBillHandler

struct_xci smb2j_SpawnHammerObj(void);
#define SpawnHammerObj smb2j_SpawnHammerObj

byte smb2j_ProcHammerObj(byte param_1);
#define ProcHammerObj smb2j_ProcHammerObj

void smb2j_CoinBlock(byte param_1,bool param_2);
#define CoinBlock smb2j_CoinBlock

byte smb2j_SetupJumpCoin(byte param_1,byte param_2,byte param_3);
#define SetupJumpCoin smb2j_SetupJumpCoin

byte smb2j_JCoinC(byte param_1,byte param_2);
#define JCoinC smb2j_JCoinC

struct_yci smb2j_FindEmptyMiscSlot(bool param_1);
#define FindEmptyMiscSlot smb2j_FindEmptyMiscSlot

void smb2j_MiscObjectsCore(void);
#define MiscObjectsCore smb2j_MiscObjectsCore

byte smb2j_GiveOneCoin(void);
#define GiveOneCoin smb2j_GiveOneCoin

byte smb2j_AddToScore(void);
#define AddToScore smb2j_AddToScore

byte smb2j_WriteScoreAndCoinTally(void);
#define WriteScoreAndCoinTally smb2j_WriteScoreAndCoinTally

byte smb2j_WriteDigits(byte param_1);
#define WriteDigits smb2j_WriteDigits

void smb2j_SetupPowerUp(byte param_1);
#define SetupPowerUp smb2j_SetupPowerUp

void smb2j_PwrUpJmp(void);
#define PwrUpJmp smb2j_PwrUpJmp

byte smb2j_PowerUpObjHandler(void);
#define PowerUpObjHandler smb2j_PowerUpObjHandler

void smb2j_PlayerHeadCollision(byte param_1,byte param_2,byte param_3,byte param_4);
#define PlayerHeadCollision smb2j_PlayerHeadCollision

void smb2j_InitBlock_XY_Pos(byte param_1);
#define InitBlock_XY_Pos smb2j_InitBlock_XY_Pos

void smb2j_BumpBlock(byte param_1,byte param_2,byte param_3,byte param_4);
#define BumpBlock smb2j_BumpBlock

void smb2j_MushFlowerBlock(byte param_1);
#define MushFlowerBlock smb2j_MushFlowerBlock

void smb2j_StarBlock(byte param_1);
#define StarBlock smb2j_StarBlock

void smb2j_PoisonMushBlock(byte param_1);
#define PoisonMushBlock smb2j_PoisonMushBlock

void smb2j_ExtraLifeMushBlock(byte param_1);
#define ExtraLifeMushBlock smb2j_ExtraLifeMushBlock

void smb2j_VineBlock(void);
#define VineBlock smb2j_VineBlock

struct_yci smb2j_BlockBumpedChk(byte param_1);
#define BlockBumpedChk smb2j_BlockBumpedChk

void smb2j_BrickShatter(byte param_1,byte param_2,byte param_3);
#define BrickShatter smb2j_BrickShatter

struct_xr05i smb2j_CheckTopOfBlock(byte param_1,byte param_2,byte param_3,byte param_4);
#define CheckTopOfBlock smb2j_CheckTopOfBlock

void smb2j_SpawnBrickChunks(byte param_1);
#define SpawnBrickChunks smb2j_SpawnBrickChunks

byte smb2j_BlockObjectsCore(byte param_1);
#define BlockObjectsCore smb2j_BlockObjectsCore

void smb2j_BlockObjMT_Updater(void);
#define BlockObjMT_Updater smb2j_BlockObjMT_Updater

struct_axi smb2j_MoveEnemyHorizontally(byte param_1);
#define MoveEnemyHorizontally smb2j_MoveEnemyHorizontally

byte smb2j_MovePlayerHorizontally(void);
#define MovePlayerHorizontally smb2j_MovePlayerHorizontally

byte smb2j_MoveObjectHorizontally(byte param_1);
#define MoveObjectHorizontally smb2j_MoveObjectHorizontally

void smb2j_MovePlayerVertically(void);
#define MovePlayerVertically smb2j_MovePlayerVertically

byte smb2j_MoveD_EnemyVertically(byte param_1);
#define MoveD_EnemyVertically smb2j_MoveD_EnemyVertically

byte smb2j_MoveFallingPlatform(byte param_1);
#define MoveFallingPlatform smb2j_MoveFallingPlatform

byte smb2j_MoveRedPTroopaDown(byte param_1);
#define MoveRedPTroopaDown smb2j_MoveRedPTroopaDown

byte smb2j_MoveRedPTroopaUp(byte param_1);
#define MoveRedPTroopaUp smb2j_MoveRedPTroopaUp

byte smb2j_MoveDropPlatform(byte param_1);
#define MoveDropPlatform smb2j_MoveDropPlatform

byte smb2j_MoveEnemySlowVert(byte param_1);
#define MoveEnemySlowVert smb2j_MoveEnemySlowVert

byte smb2j_MoveJ_EnemyVertically(byte param_1);
#define MoveJ_EnemyVertically smb2j_MoveJ_EnemyVertically

byte smb2j_SetXMoveAmt(byte param_1,byte param_2,byte param_3);
#define SetXMoveAmt smb2j_SetXMoveAmt

void smb2j_ImposeGravityBlock(byte param_1);
#define ImposeGravityBlock smb2j_ImposeGravityBlock

void smb2j_ImposeGravitySprObj(byte param_1,byte param_2,byte param_3);
#define ImposeGravitySprObj smb2j_ImposeGravitySprObj

byte smb2j_MovePlatformDown(byte param_1);
#define MovePlatformDown smb2j_MovePlatformDown

byte smb2j_MovePlatformUp(byte param_1);
#define MovePlatformUp smb2j_MovePlatformUp

byte smb2j_RedPTroopaGrav(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
#define RedPTroopaGrav smb2j_RedPTroopaGrav

void smb2j_ImposeGravity(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
#define ImposeGravity smb2j_ImposeGravity

byte smb2j_EnemiesAndLoopsCore(byte param_1);
#define EnemiesAndLoopsCore smb2j_EnemiesAndLoopsCore

void smb2j_ExecGameLoopback(byte param_1);
#define ExecGameLoopback smb2j_ExecGameLoopback

byte smb2j_ProcLoopCommand(byte param_1);
#define ProcLoopCommand smb2j_ProcLoopCommand

void smb2j_InitEnemyObject(byte param_1);
#define InitEnemyObject smb2j_InitEnemyObject

byte smb2j_CheckThreeBytes(void);
#define CheckThreeBytes smb2j_CheckThreeBytes

byte smb2j_Inc2B(void);
#define Inc2B smb2j_Inc2B

void smb2j_CheckpointEnemyID(byte param_1);
#define CheckpointEnemyID smb2j_CheckpointEnemyID

void smb2j_NoInitCode(void);
#define NoInitCode smb2j_NoInitCode

void smb2j_InitGoomba(byte param_1);
#define InitGoomba smb2j_InitGoomba

void smb2j_InitPodoboo(byte param_1);
#define InitPodoboo smb2j_InitPodoboo

void smb2j_InitRetainerObj(byte param_1);
#define InitRetainerObj smb2j_InitRetainerObj

void smb2j_InitNormalEnemy(byte param_1);
#define InitNormalEnemy smb2j_InitNormalEnemy

void smb2j_InitRedKoopa(byte param_1);
#define InitRedKoopa smb2j_InitRedKoopa

void smb2j_InitHammerBro(byte param_1);
#define InitHammerBro smb2j_InitHammerBro

void smb2j_InitHorizFlySwimEnemy(byte param_1);
#define InitHorizFlySwimEnemy smb2j_InitHorizFlySwimEnemy

void smb2j_InitBloober(byte param_1);
#define InitBloober smb2j_InitBloober

byte smb2j_SmallBBox(byte param_1);
#define SmallBBox smb2j_SmallBBox

void smb2j_InitRedPTroopa(byte param_1,bool param_2);
#define InitRedPTroopa smb2j_InitRedPTroopa

byte smb2j_InitVStf(byte param_1);
#define InitVStf smb2j_InitVStf

void smb2j_InitBulletBill(byte param_1);
#define InitBulletBill smb2j_InitBulletBill

void smb2j_InitCheepCheep(byte param_1);
#define InitCheepCheep smb2j_InitCheepCheep

void smb2j_InitLakitu(byte param_1);
#define InitLakitu smb2j_InitLakitu

void smb2j_SetupLakitu(byte param_1);
#define SetupLakitu smb2j_SetupLakitu

void smb2j_LakituAndSpinyHandler(byte param_1);
#define LakituAndSpinyHandler smb2j_LakituAndSpinyHandler

void smb2j_InitLongFirebar(byte param_1);
#define InitLongFirebar smb2j_InitLongFirebar

void smb2j_InitShortFirebar(byte param_1);
#define InitShortFirebar smb2j_InitShortFirebar

void smb2j_InitFlyingCheepCheep(byte param_1);
#define InitFlyingCheepCheep smb2j_InitFlyingCheepCheep

void smb2j_InitBowser(byte param_1);
#define InitBowser smb2j_InitBowser

void smb2j_DuplicateEnemyObj(byte param_1);
#define DuplicateEnemyObj smb2j_DuplicateEnemyObj

void smb2j_InitBowserFlame(byte param_1);
#define InitBowserFlame smb2j_InitBowserFlame

byte smb2j_PutAtRightExtent(byte param_1,byte param_2);
#define PutAtRightExtent smb2j_PutAtRightExtent

void smb2j_InitFireworks(byte param_1);
#define InitFireworks smb2j_InitFireworks

void smb2j_BulletBillCheepCheep(byte param_1);
#define BulletBillCheepCheep smb2j_BulletBillCheepCheep

byte smb2j_HandleGroupEnemies(byte param_1);
#define HandleGroupEnemies smb2j_HandleGroupEnemies

void smb2j_InitPiranhaPlant(byte param_1);
#define InitPiranhaPlant smb2j_InitPiranhaPlant

void smb2j_InitEnemyFrenzy(byte param_1);
#define InitEnemyFrenzy smb2j_InitEnemyFrenzy

void smb2j_NoFrenzyCode(void);
#define NoFrenzyCode smb2j_NoFrenzyCode

void smb2j_EndFrenzy(byte param_1);
#define EndFrenzy smb2j_EndFrenzy

void smb2j_InitJumpGPTroopa(byte param_1);
#define InitJumpGPTroopa smb2j_InitJumpGPTroopa

void smb2j_InitBalPlatform(byte param_1);
#define InitBalPlatform smb2j_InitBalPlatform

void smb2j_InitDropPlatform(byte param_1);
#define InitDropPlatform smb2j_InitDropPlatform

void smb2j_InitHoriPlatform(byte param_1);
#define InitHoriPlatform smb2j_InitHoriPlatform

void smb2j_InitVertPlatform(byte param_1);
#define InitVertPlatform smb2j_InitVertPlatform

void smb2j_SPBBox(byte param_1);
#define SPBBox smb2j_SPBBox

void smb2j_LargeLiftUp(byte param_1);
#define LargeLiftUp smb2j_LargeLiftUp

void smb2j_LargeLiftDown(byte param_1);
#define LargeLiftDown smb2j_LargeLiftDown

void smb2j_PlatLiftUp(byte param_1);
#define PlatLiftUp smb2j_PlatLiftUp

void smb2j_PlatLiftDown(byte param_1);
#define PlatLiftDown smb2j_PlatLiftDown

void smb2j_PosPlatform(byte param_1,byte param_2);
#define PosPlatform smb2j_PosPlatform

void smb2j_EndOfEnemyInitCode(void);
#define EndOfEnemyInitCode smb2j_EndOfEnemyInitCode

byte smb2j_RunEnemyObjectsCore(void);
#define RunEnemyObjectsCore smb2j_RunEnemyObjectsCore

void smb2j_NoRunCode(void);
#define NoRunCode smb2j_NoRunCode

byte smb2j_RunRetainerObj(byte param_1);
#define RunRetainerObj smb2j_RunRetainerObj

byte smb2j_RunNormalEnemies(byte param_1);
#define RunNormalEnemies smb2j_RunNormalEnemies

byte smb2j_EnemyMovementSubs(byte param_1);
#define EnemyMovementSubs smb2j_EnemyMovementSubs

void smb2j_NoMoveCode(void);
#define NoMoveCode smb2j_NoMoveCode

byte smb2j_RunBowserFlame(byte param_1);
#define RunBowserFlame smb2j_RunBowserFlame

byte smb2j_RunFirebarObj(byte param_1);
#define RunFirebarObj smb2j_RunFirebarObj

byte smb2j_RunSmallPlatform(byte param_1);
#define RunSmallPlatform smb2j_RunSmallPlatform

byte smb2j_RunLargePlatform(byte param_1);
#define RunLargePlatform smb2j_RunLargePlatform

byte smb2j_LargePlatformSubroutines(byte param_1);
#define LargePlatformSubroutines smb2j_LargePlatformSubroutines

byte smb2j_EraseEnemyObject(byte param_1);
#define EraseEnemyObject smb2j_EraseEnemyObject

byte smb2j_MovePodoboo(byte param_1);
#define MovePodoboo smb2j_MovePodoboo

byte smb2j_ProcHammerBro(byte param_1);
#define ProcHammerBro smb2j_ProcHammerBro

byte smb2j_SetHJ(byte param_1,byte param_2,byte param_3);
#define SetHJ smb2j_SetHJ

byte smb2j_MoveHammerBroXDir(byte param_1);
#define MoveHammerBroXDir smb2j_MoveHammerBroXDir

byte smb2j_MoveNormalEnemy(byte param_1);
#define MoveNormalEnemy smb2j_MoveNormalEnemy

byte smb2j_MoveDefeatedEnemy(byte param_1);
#define MoveDefeatedEnemy smb2j_MoveDefeatedEnemy

byte smb2j_MoveJumpingEnemy(byte param_1);
#define MoveJumpingEnemy smb2j_MoveJumpingEnemy

byte smb2j_ProcMoveRedPTroopa(byte param_1);
#define ProcMoveRedPTroopa smb2j_ProcMoveRedPTroopa

byte smb2j_MoveFlyGreenPTroopa(byte param_1);
#define MoveFlyGreenPTroopa smb2j_MoveFlyGreenPTroopa

void smb2j_XMoveCntr_GreenPTroopa(byte param_1);
#define XMoveCntr_GreenPTroopa smb2j_XMoveCntr_GreenPTroopa

void smb2j_XMoveCntr_Platform(byte param_1,byte param_2);
#define XMoveCntr_Platform smb2j_XMoveCntr_Platform

struct_xr00i smb2j_MoveWithXMCntrs(byte param_1);
#define MoveWithXMCntrs smb2j_MoveWithXMCntrs

byte smb2j_MoveBloober(byte param_1,bool param_2);
#define MoveBloober smb2j_MoveBloober

void smb2j_ProcSwimmingB(byte param_1,bool param_2);
#define ProcSwimmingB smb2j_ProcSwimmingB

byte smb2j_MoveBulletBill(byte param_1);
#define MoveBulletBill smb2j_MoveBulletBill

byte smb2j_MoveSwimmingCheepCheep(byte param_1);
#define MoveSwimmingCheepCheep smb2j_MoveSwimmingCheepCheep

byte smb2j_ProcFirebar(byte param_1);
#define ProcFirebar smb2j_ProcFirebar

struct_xr00r06 smb2j_DrawFirebar_Collision(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
#define DrawFirebar_Collision smb2j_DrawFirebar_Collision

struct_xr00r06 smb2j_FirebarCollision(byte param_1,byte param_2,byte param_3,byte param_4);
#define FirebarCollision smb2j_FirebarCollision

struct_r01r02r03 smb2j_GetFirebarPosition(byte param_1,byte param_2);
#define GetFirebarPosition smb2j_GetFirebarPosition

byte smb2j_MoveFlyingCheepCheep(byte param_1);
#define MoveFlyingCheepCheep smb2j_MoveFlyingCheepCheep

byte smb2j_MoveLakitu(byte param_1);
#define MoveLakitu smb2j_MoveLakitu

byte smb2j_PlayerLakituDiff(byte param_1,byte param_2,byte param_3,byte param_4);
#define PlayerLakituDiff smb2j_PlayerLakituDiff

void smb2j_BridgeCollapse(byte param_1);
#define BridgeCollapse smb2j_BridgeCollapse

byte smb2j_MoveD_Bowser(byte param_1);
#define MoveD_Bowser smb2j_MoveD_Bowser

byte smb2j_RunBowser(byte param_1);
#define RunBowser smb2j_RunBowser

byte smb2j_KillAllEnemies(void);
#define KillAllEnemies smb2j_KillAllEnemies

byte smb2j_BowserGfxHandler(byte param_1);
#define BowserGfxHandler smb2j_BowserGfxHandler

byte smb2j_ProcessBowserHalf(byte param_1);
#define ProcessBowserHalf smb2j_ProcessBowserHalf

byte smb2j_SetFlameTimer(void);
#define SetFlameTimer smb2j_SetFlameTimer

byte smb2j_ProcBowserFlame(byte param_1);
#define ProcBowserFlame smb2j_ProcBowserFlame

byte smb2j_RunFireworks(byte param_1);
#define RunFireworks smb2j_RunFireworks

byte smb2j_RunStarFlagObj(byte param_1);
#define RunStarFlagObj smb2j_RunStarFlagObj

void smb2j_GameTimerFireworks(byte param_1);
#define GameTimerFireworks smb2j_GameTimerFireworks

void smb2j_StarFlagExit(void);
#define StarFlagExit smb2j_StarFlagExit

byte smb2j_AwardGameTimerPoints(byte param_1);
#define AwardGameTimerPoints smb2j_AwardGameTimerPoints

byte smb2j_AwardTimerCastle(void);
#define AwardTimerCastle smb2j_AwardTimerCastle

byte smb2j_EndAreaPoints(void);
#define EndAreaPoints smb2j_EndAreaPoints

byte smb2j_RaiseFlagSetoffFWorks(byte param_1);
#define RaiseFlagSetoffFWorks smb2j_RaiseFlagSetoffFWorks

byte smb2j_DrawStarFlag(byte param_1);
#define DrawStarFlag smb2j_DrawStarFlag

byte smb2j_DelayToAreaEnd(byte param_1);
#define DelayToAreaEnd smb2j_DelayToAreaEnd

void smb2j_MovePiranhaPlant(byte param_1);
#define MovePiranhaPlant smb2j_MovePiranhaPlant

byte smb2j_FirebarSpin(byte param_1,byte param_2);
#define FirebarSpin smb2j_FirebarSpin

byte smb2j_BalancePlatform(byte param_1);
#define BalancePlatform smb2j_BalancePlatform

struct_xr00r01 smb2j_SetupPlatformRope(byte param_1,byte param_2);
#define SetupPlatformRope smb2j_SetupPlatformRope

byte smb2j_InitPlatformFall(byte param_1);
#define InitPlatformFall smb2j_InitPlatformFall

void smb2j_StopPlatforms(byte param_1,byte param_2);
#define StopPlatforms smb2j_StopPlatforms

byte smb2j_PlatformFall(byte param_1,byte param_2);
#define PlatformFall smb2j_PlatformFall

byte smb2j_YMovingPlatform(byte param_1);
#define YMovingPlatform smb2j_YMovingPlatform

void smb2j_ChkYPCollision(byte param_1);
#define ChkYPCollision smb2j_ChkYPCollision

byte smb2j_XMovingPlatform(byte param_1);
#define XMovingPlatform smb2j_XMovingPlatform

void smb2j_PositionPlayerOnHPlat(byte param_1,byte param_2);
#define PositionPlayerOnHPlat smb2j_PositionPlayerOnHPlat

byte smb2j_DropPlatform(byte param_1);
#define DropPlatform smb2j_DropPlatform

byte smb2j_RightPlatform(byte param_1);
#define RightPlatform smb2j_RightPlatform

void smb2j_MoveLargeLiftPlat(byte param_1);
#define MoveLargeLiftPlat smb2j_MoveLargeLiftPlat

void smb2j_MoveSmallPlatform(byte param_1);
#define MoveSmallPlatform smb2j_MoveSmallPlatform

void smb2j_MoveLiftPlatforms(byte param_1);
#define MoveLiftPlatforms smb2j_MoveLiftPlatforms

void smb2j_ChkSmallPlatCollision(byte param_1);
#define ChkSmallPlatCollision smb2j_ChkSmallPlatCollision

void smb2j_OffscreenBoundsCheck(byte param_1);
#define OffscreenBoundsCheck smb2j_OffscreenBoundsCheck

byte smb2j_FireballEnemyCollision(byte param_1);
#define FireballEnemyCollision smb2j_FireballEnemyCollision

void smb2j_HandleEnemyFBallCol(byte param_1,byte param_2);
#define HandleEnemyFBallCol smb2j_HandleEnemyFBallCol

void smb2j_ShellOrBlockDefeat(byte param_1);
#define ShellOrBlockDefeat smb2j_ShellOrBlockDefeat

void smb2j_EnemySmackScore(byte param_1,byte param_2);
#define EnemySmackScore smb2j_EnemySmackScore

byte smb2j_PlayerHammerCollision(byte param_1);
#define PlayerHammerCollision smb2j_PlayerHammerCollision

byte smb2j_HandlePowerUpCollision(byte param_1);
#define HandlePowerUpCollision smb2j_HandlePowerUpCollision

byte smb2j_PlayerEnemyCollision(byte param_1);
#define PlayerEnemyCollision smb2j_PlayerEnemyCollision

byte smb2j_InjurePlayer(void);
#define InjurePlayer smb2j_InjurePlayer

byte smb2j_ForceInjury(byte param_1);
#define ForceInjury smb2j_ForceInjury

byte smb2j_SetPRout(byte param_1,byte param_2);
#define SetPRout smb2j_SetPRout

byte smb2j_SetBounce(byte param_1);
#define SetBounce smb2j_SetBounce

byte smb2j_ChkEnemyFaceRight(byte param_1);
#define ChkEnemyFaceRight smb2j_ChkEnemyFaceRight

byte smb2j_LInj(byte param_1);
#define LInj smb2j_LInj

byte smb2j_EnemyFacePlayer(byte param_1);
#define EnemyFacePlayer smb2j_EnemyFacePlayer

void smb2j_SetupFloateyNumber(byte param_1,byte param_2);
#define SetupFloateyNumber smb2j_SetupFloateyNumber

byte smb2j_EnemiesCollision(byte param_1);
#define EnemiesCollision smb2j_EnemiesCollision

void smb2j_ProcEnemyCollisions(byte param_1,byte param_2,byte param_3);
#define ProcEnemyCollisions smb2j_ProcEnemyCollisions

void smb2j_EnemyTurnAround(byte param_1);
#define EnemyTurnAround smb2j_EnemyTurnAround

void smb2j_RXSpd(byte param_1);
#define RXSpd smb2j_RXSpd

byte smb2j_LargePlatformCollision(byte param_1);
#define LargePlatformCollision smb2j_LargePlatformCollision

byte smb2j_ChkForPlayerC_LargeP(byte param_1);
#define ChkForPlayerC_LargeP smb2j_ChkForPlayerC_LargeP

byte smb2j_SmallPlatformCollision(byte param_1);
#define SmallPlatformCollision smb2j_SmallPlatformCollision

byte smb2j_ProcLPlatCollisions(byte param_1,byte param_2,byte param_3);
#define ProcLPlatCollisions smb2j_ProcLPlatCollisions

void smb2j_PositionPlayerOnS_Plat(byte param_1,byte param_2);
#define PositionPlayerOnS_Plat smb2j_PositionPlayerOnS_Plat

void smb2j_PositionPlayerOnVPlat(byte param_1);
#define PositionPlayerOnVPlat smb2j_PositionPlayerOnVPlat

bool smb2j_CheckPlayerVertical(void);
#define CheckPlayerVertical smb2j_CheckPlayerVertical

struct_ayi smb2j_GetEnemyBoundBoxOfs(void);
#define GetEnemyBoundBoxOfs smb2j_GetEnemyBoundBoxOfs

struct_ayi smb2j_GetEnemyBoundBoxOfsArg(byte param_1);
#define GetEnemyBoundBoxOfsArg smb2j_GetEnemyBoundBoxOfsArg

void smb2j_PlayerBGCollision(void);
#define PlayerBGCollision smb2j_PlayerBGCollision

void smb2j_ErACM(byte param_1,byte param_2,byte param_3);
#define ErACM smb2j_ErACM

void smb2j_HandleClimbing(byte param_1,byte param_2,byte param_3);
#define HandleClimbing smb2j_HandleClimbing

bool smb2j_ChkInvisibleMTiles(byte param_1);
#define ChkInvisibleMTiles smb2j_ChkInvisibleMTiles

void smb2j_ChkForLandJumpSpring(byte param_1);
#define ChkForLandJumpSpring smb2j_ChkForLandJumpSpring

bool smb2j_ChkJumpspringMetatiles(byte param_1);
#define ChkJumpspringMetatiles smb2j_ChkJumpspringMetatiles

void smb2j_HandlePipeEntry(byte param_1,byte param_2);
#define HandlePipeEntry smb2j_HandlePipeEntry

void smb2j_ImpedePlayerMove(byte param_1);
#define ImpedePlayerMove smb2j_ImpedePlayerMove

bool smb2j_CheckForSolidMTiles(byte param_1);
#define CheckForSolidMTiles smb2j_CheckForSolidMTiles

bool smb2j_CheckForClimbMTiles(byte param_1);
#define CheckForClimbMTiles smb2j_CheckForClimbMTiles

struct_aci smb2j_CheckForCoinMTiles(byte param_1);
#define CheckForCoinMTiles smb2j_CheckForCoinMTiles

byte smb2j_GetMTileAttrib(byte param_1);
#define GetMTileAttrib smb2j_GetMTileAttrib

byte smb2j_EnemyToBGCollisionDet(byte param_1);
#define EnemyToBGCollisionDet smb2j_EnemyToBGCollisionDet

void smb2j_ChkToStunEnemies(byte param_1);
#define ChkToStunEnemies smb2j_ChkToStunEnemies

void smb2j_NoDemote(byte param_1,byte param_2);
#define NoDemote smb2j_NoDemote

void smb2j_SetStun2(byte param_1);
#define SetStun2 smb2j_SetStun2

byte smb2j_ChkForRedKoopa(byte param_1);
#define ChkForRedKoopa smb2j_ChkForRedKoopa

byte smb2j_DoEnemySideCheck(byte param_1);
#define DoEnemySideCheck smb2j_DoEnemySideCheck

byte smb2j_ChkForBump_HammerBroJ(byte param_1);
#define ChkForBump_HammerBroJ smb2j_ChkForBump_HammerBroJ

struct_ncr00 smb2j_PlayerEnemyDiff(byte param_1);
#define PlayerEnemyDiff smb2j_PlayerEnemyDiff

void smb2j_EnemyLanding(byte param_1);
#define EnemyLanding smb2j_EnemyLanding

bool smb2j_SubtEnemyYPos(byte param_1);
#define SubtEnemyYPos smb2j_SubtEnemyYPos

byte smb2j_EnemyJump(byte param_1);
#define EnemyJump smb2j_EnemyJump

byte smb2j_HammerBroBGColl(byte param_1);
#define HammerBroBGColl smb2j_HammerBroBGColl

void smb2j_KillEnemyAboveBlock(byte param_1);
#define KillEnemyAboveBlock smb2j_KillEnemyAboveBlock

struct_axzr04 smb2j_ChkUnderEnemy(byte param_1);
#define ChkUnderEnemy smb2j_ChkUnderEnemy

bool smb2j_ChkForNonSolids(byte param_1);
#define ChkForNonSolids smb2j_ChkForNonSolids

byte smb2j_FireballBGCollision(byte param_1);
#define FireballBGCollision smb2j_FireballBGCollision

byte smb2j_GetFireballBoundBox(byte param_1);
#define GetFireballBoundBox smb2j_GetFireballBoundBox

byte smb2j_GetMiscBoundBox(byte param_1);
#define GetMiscBoundBox smb2j_GetMiscBoundBox

byte smb2j_GetEnemyBoundBox(byte param_1);
#define GetEnemyBoundBox smb2j_GetEnemyBoundBox

byte smb2j_SmallPlatformBoundBox(byte param_1);
#define SmallPlatformBoundBox smb2j_SmallPlatformBoundBox

byte smb2j_GetMaskedOffScrBits(byte param_1,byte param_2,byte param_3);
#define GetMaskedOffScrBits smb2j_GetMaskedOffScrBits

byte smb2j_LargePlatformBoundBox(byte param_1);
#define LargePlatformBoundBox smb2j_LargePlatformBoundBox

byte smb2j_SetupEOffsetFBBox(byte param_1);
#define SetupEOffsetFBBox smb2j_SetupEOffsetFBBox

void smb2j_MoveBoundBoxOffscreen(byte param_1);
#define MoveBoundBoxOffscreen smb2j_MoveBoundBoxOffscreen

byte smb2j_BoundingBoxCore(byte param_1,byte param_2);
#define BoundingBoxCore smb2j_BoundingBoxCore

byte smb2j_CheckRightScreenBBox(byte param_1,byte param_2);
#define CheckRightScreenBBox smb2j_CheckRightScreenBBox

bool smb2j_PlayerCollisionCore(byte param_1);
#define PlayerCollisionCore smb2j_PlayerCollisionCore

bool smb2j_SprObjectCollisionCore(byte param_1,byte param_2);
#define SprObjectCollisionCore smb2j_SprObjectCollisionCore

struct_axzr04 smb2j_BlockBufferChk_Enemy(byte param_1,byte param_2,byte param_3);
#define BlockBufferChk_Enemy smb2j_BlockBufferChk_Enemy

struct_axz smb2j_BlockBufferChk_FBall(byte param_1);
#define BlockBufferChk_FBall smb2j_BlockBufferChk_FBall

struct_ayr02r04r06r07 smb2j_BlockBufferColli_Feet(byte param_1);
#define BlockBufferColli_Feet smb2j_BlockBufferColli_Feet

struct_azr02r04r06r07 smb2j_BlockBufferColli_Head(byte param_1);
#define BlockBufferColli_Head smb2j_BlockBufferColli_Head

struct_azr02r04r06r07 smb2j_BlockBufferColli_Side(byte param_1);
#define BlockBufferColli_Side smb2j_BlockBufferColli_Side

struct_azr02r04r06r07 smb2j_BlockBufferCollision(byte param_1,byte param_2,byte param_3);
#define BlockBufferCollision smb2j_BlockBufferCollision

void smb2j_DrawVine(byte param_1);
#define DrawVine smb2j_DrawVine

byte smb2j_SixSpriteStacker(byte param_1,byte param_2,byte param_3);
#define SixSpriteStacker smb2j_SixSpriteStacker

byte smb2j_DrawHammer(byte param_1);
#define DrawHammer smb2j_DrawHammer

void smb2j_FlagpoleGfxHandler(byte param_1);
#define FlagpoleGfxHandler smb2j_FlagpoleGfxHandler

void smb2j_MoveSixSpritesOffscreen(byte param_1);
#define MoveSixSpritesOffscreen smb2j_MoveSixSpritesOffscreen

void smb2j_DumpSixSpr(byte param_1,byte param_2);
#define DumpSixSpr smb2j_DumpSixSpr

void smb2j_DumpFourSpr(byte param_1,byte param_2);
#define DumpFourSpr smb2j_DumpFourSpr

void smb2j_DumpThreeSpr(byte param_1,byte param_2);
#define DumpThreeSpr smb2j_DumpThreeSpr

void smb2j_DumpTwoSpr(byte param_1,byte param_2);
#define DumpTwoSpr smb2j_DumpTwoSpr

byte smb2j_DrawLargePlatform(byte param_1);
#define DrawLargePlatform smb2j_DrawLargePlatform

byte smb2j_JCoinGfxHandler(byte param_1);
#define JCoinGfxHandler smb2j_JCoinGfxHandler

byte smb2j_DrawPowerUp(void);
#define DrawPowerUp smb2j_DrawPowerUp

byte smb2j_EnemyGfxHandler(byte param_1);
#define EnemyGfxHandler smb2j_EnemyGfxHandler

byte smb2j_DrawEnemyObject(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
#define DrawEnemyObject smb2j_DrawEnemyObject

byte smb2j_SprObjectOffscrChk(void);
#define SprObjectOffscrChk smb2j_SprObjectOffscrChk

struct_xyr02 smb2j_DrawEnemyObjRow(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6);
#define DrawEnemyObjRow smb2j_DrawEnemyObjRow

struct_xyr02 smb2j_DrawOneSpriteRow(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,byte param_7,byte param_8);
#define DrawOneSpriteRow smb2j_DrawOneSpriteRow

void smb2j_MoveESprRowOffscreen(byte param_1,byte param_2);
#define MoveESprRowOffscreen smb2j_MoveESprRowOffscreen

void smb2j_MoveESprColOffscreen(byte param_1,byte param_2);
#define MoveESprColOffscreen smb2j_MoveESprColOffscreen

byte smb2j_DrawBlock(byte param_1);
#define DrawBlock smb2j_DrawBlock

void smb2j_ChkLeftCo(byte param_1,byte param_2);
#define ChkLeftCo smb2j_ChkLeftCo

byte smb2j_MoveColOffscreen(byte param_1);
#define MoveColOffscreen smb2j_MoveColOffscreen

void smb2j_DrawBrickChunks(byte param_1);
#define DrawBrickChunks smb2j_DrawBrickChunks

void smb2j_DrawFireball(byte param_1);
#define DrawFireball smb2j_DrawFireball

void smb2j_DrawFirebar(byte param_1);
#define DrawFirebar smb2j_DrawFirebar

void smb2j_DrawExplosion_Fireball(byte param_1);
#define DrawExplosion_Fireball smb2j_DrawExplosion_Fireball

byte smb2j_DrawExplosion_Fireworks(byte param_1,byte param_2);
#define DrawExplosion_Fireworks smb2j_DrawExplosion_Fireworks

byte smb2j_DrawSmallPlatform(byte param_1);
#define DrawSmallPlatform smb2j_DrawSmallPlatform

void smb2j_DrawBubble(byte param_1);
#define DrawBubble smb2j_DrawBubble

void smb2j_PlayerGfxHandler(void);
#define PlayerGfxHandler smb2j_PlayerGfxHandler

void smb2j_FindPlayerAction(void);
#define FindPlayerAction smb2j_FindPlayerAction

void smb2j_PlayerGfxProcessing(byte param_1);
#define PlayerGfxProcessing smb2j_PlayerGfxProcessing

void smb2j_DrawPlayer_Intermediate(void);
#define DrawPlayer_Intermediate smb2j_DrawPlayer_Intermediate

void smb2j_RenderPlayerSub(byte param_1);
#define RenderPlayerSub smb2j_RenderPlayerSub

void smb2j_DrawPlayerLoop(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,byte param_7);
#define DrawPlayerLoop smb2j_DrawPlayerLoop

byte smb2j_ProcessPlayerAction(void);
#define ProcessPlayerAction smb2j_ProcessPlayerAction

byte smb2j_GetCurrentAnimOffset(byte param_1);
#define GetCurrentAnimOffset smb2j_GetCurrentAnimOffset

byte smb2j_FourFrameExtent(byte param_1);
#define FourFrameExtent smb2j_FourFrameExtent

byte smb2j_ThreeFrameExtent(byte param_1);
#define ThreeFrameExtent smb2j_ThreeFrameExtent

byte smb2j_AnimationControl(byte param_1,byte param_2);
#define AnimationControl smb2j_AnimationControl

byte smb2j_GetGfxOffsetAdder(byte param_1);
#define GetGfxOffsetAdder smb2j_GetGfxOffsetAdder

byte smb2j_HandleChangeSize(void);
#define HandleChangeSize smb2j_HandleChangeSize

byte smb2j_GetOffsetFromAnimCtrl(byte param_1,byte param_2);
#define GetOffsetFromAnimCtrl smb2j_GetOffsetFromAnimCtrl

void smb2j_ChkForPlayerAttrib(void);
#define ChkForPlayerAttrib smb2j_ChkForPlayerAttrib

byte smb2j_RelativePlayerPosition(void);
#define RelativePlayerPosition smb2j_RelativePlayerPosition

byte smb2j_RelativeBubblePosition(byte param_1);
#define RelativeBubblePosition smb2j_RelativeBubblePosition

byte smb2j_RelativeFireballPosition(byte param_1);
#define RelativeFireballPosition smb2j_RelativeFireballPosition

byte smb2j_RelativeMiscPosition(byte param_1);
#define RelativeMiscPosition smb2j_RelativeMiscPosition

struct_axr00 smb2j_RelativeEnemyPosition(byte param_1);
#define RelativeEnemyPosition smb2j_RelativeEnemyPosition

byte smb2j_RelativeBlockPosition(byte param_1);
#define RelativeBlockPosition smb2j_RelativeBlockPosition

struct_axr00 smb2j_VariableObjOfsRelPos(byte param_1,byte param_2,byte param_3);
#define VariableObjOfsRelPos smb2j_VariableObjOfsRelPos

byte smb2j_GetObjRelativePosition(byte param_1,byte param_2);
#define GetObjRelativePosition smb2j_GetObjRelativePosition

void smb2j_GetPlayerOffscreenBits(void);
#define GetPlayerOffscreenBits smb2j_GetPlayerOffscreenBits

byte smb2j_GetFireballOffscreenBits(byte param_1);
#define GetFireballOffscreenBits smb2j_GetFireballOffscreenBits

byte smb2j_GetBubbleOffscreenBits(byte param_1);
#define GetBubbleOffscreenBits smb2j_GetBubbleOffscreenBits

byte smb2j_GetMiscOffscreenBits(byte param_1);
#define GetMiscOffscreenBits smb2j_GetMiscOffscreenBits

byte smb2j_GetProperObjOffset(byte param_1,byte param_2);
#define GetProperObjOffset smb2j_GetProperObjOffset

struct_xyi smb2j_GetEnemyOffscreenBits(byte param_1);
#define GetEnemyOffscreenBits smb2j_GetEnemyOffscreenBits

byte smb2j_GetBlockOffscreenBits(byte param_1);
#define GetBlockOffscreenBits smb2j_GetBlockOffscreenBits

struct_xyi smb2j_GetOffScreenBitsSet(byte param_1,byte param_2);
#define GetOffScreenBitsSet smb2j_GetOffScreenBitsSet

struct_ar00i smb2j_RunOffscrBitsSubs(byte param_1);
#define RunOffscrBitsSubs smb2j_RunOffscrBitsSubs

byte smb2j_GetXOffscreenBits(byte param_1);
#define GetXOffscreenBits smb2j_GetXOffscreenBits

byte smb2j_GetYOffscreenBits(byte param_1);
#define GetYOffscreenBits smb2j_GetYOffscreenBits

byte smb2j_DividePDiff(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
#define DividePDiff smb2j_DividePDiff

struct_xyr02 smb2j_DrawSpriteObject(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,byte param_7,byte param_8);
#define DrawSpriteObject smb2j_DrawSpriteObject

void smb2j_AttractModeSubs(void);
#define AttractModeSubs smb2j_AttractModeSubs

void smb2j_HardWorldsCheckpoint(void);
#define HardWorldsCheckpoint smb2j_HardWorldsCheckpoint

void smb2j_LoadHardWorlds(void);
#define LoadHardWorlds smb2j_LoadHardWorlds

void smb2j_AttractModeDiskRoutines(void);
#define AttractModeDiskRoutines smb2j_AttractModeDiskRoutines

void smb2j_LoadWorlds1Thru4(void);
#define LoadWorlds1Thru4 smb2j_LoadWorlds1Thru4

void smb2j_GameModeDiskRoutines(void);
#define GameModeDiskRoutines smb2j_GameModeDiskRoutines

void smb2j_LoadWorlds5Thru8(void);
#define LoadWorlds5Thru8 smb2j_LoadWorlds5Thru8

void smb2j_ResetDiskIOTask(void);
#define ResetDiskIOTask smb2j_ResetDiskIOTask

void smb2j_VMDelay(void);
#define VMDelay smb2j_VMDelay

void smb2j_StartVMDelay(void);
#define StartVMDelay smb2j_StartVMDelay

void smb2j_ContinueVMDelay(void);
#define ContinueVMDelay smb2j_ContinueVMDelay

void smb2j_VictoryModeDiskRoutines(void);
#define VictoryModeDiskRoutines smb2j_VictoryModeDiskRoutines

void smb2j_LoadEnding(void);
#define LoadEnding smb2j_LoadEnding

bool smb2j_CheckFileCount(byte param_1);
#define CheckFileCount smb2j_CheckFileCount

void smb2j_DiskScreen(void);
#define DiskScreen smb2j_DiskScreen

void smb2j_WaitForEject(void);
#define WaitForEject smb2j_WaitForEject

void smb2j_WaitForReinsert(void);
#define WaitForReinsert smb2j_WaitForReinsert

void smb2j_ResetDiskVars(void);
#define ResetDiskVars smb2j_ResetDiskVars

void smb2j_DiskErrorHandler(byte param_1);
#define DiskErrorHandler smb2j_DiskErrorHandler

void smb2j_GameOverMenu(void);
#define GameOverMenu smb2j_GameOverMenu

void smb2j_LoadPhysicsData(void);
#define LoadPhysicsData smb2j_LoadPhysicsData

void smb2j_LoadMarioPhysics(void);
#define LoadMarioPhysics smb2j_LoadMarioPhysics

void smb2j_ModifyPhysics(byte param_1,byte param_2);
#define ModifyPhysics smb2j_ModifyPhysics

void smb2j_LoadAreaPointer(void);
#define LoadAreaPointer smb2j_LoadAreaPointer

byte smb2j_GetAreaType(byte param_1);
#define GetAreaType smb2j_GetAreaType

byte smb2j_FindAreaPointer(void);
#define FindAreaPointer smb2j_FindAreaPointer

void smb2j_FUN_e149(void);
#define FUN_e149 smb2j_FUN_e149

void smb2j_AltHard_GetAreaDataAddrs(void);
#define AltHard_GetAreaDataAddrs smb2j_AltHard_GetAreaDataAddrs

void smb2j_ChangeHalfwayPages(void);
#define ChangeHalfwayPages smb2j_ChangeHalfwayPages

void smb2j_GetAreaDataAddrs(void);
#define GetAreaDataAddrs smb2j_GetAreaDataAddrs

void smb2j_GameMenuRoutine(void);
#define GameMenuRoutine smb2j_GameMenuRoutine

void smb2j_DrawMenuCursor(void);
#define DrawMenuCursor smb2j_DrawMenuCursor

void smb2j_SetupMenuCursor(void);
#define SetupMenuCursor smb2j_SetupMenuCursor

bool smb2j_DemoEngine(void);
#define DemoEngine smb2j_DemoEngine

void smb2j_ClearBuffersDrawIcon(void);
#define ClearBuffersDrawIcon smb2j_ClearBuffersDrawIcon

void smb2j_WriteTopScore(void);
#define WriteTopScore smb2j_WriteTopScore

void smb2j_InitializeGame(void);
#define InitializeGame smb2j_InitializeGame

void smb2j_DemoReset(void);
#define DemoReset smb2j_DemoReset

void smb2j_PrimaryGameSetup(void);
#define PrimaryGameSetup smb2j_PrimaryGameSetup

void smb2j_PatchPlayerNamePal(void);
#define PatchPlayerNamePal smb2j_PatchPlayerNamePal

void smb2j_UpsideDownPipe_High(byte param_1);
#define UpsideDownPipe_High smb2j_UpsideDownPipe_High

void smb2j_UpsideDownPipe_Low(byte param_1);
#define UpsideDownPipe_Low smb2j_UpsideDownPipe_Low

void smb2j_MoveUpsideDownPiranhaP(byte param_1);
#define MoveUpsideDownPiranhaP smb2j_MoveUpsideDownPiranhaP

void smb2j_BlowPlayerAround(void);
#define BlowPlayerAround smb2j_BlowPlayerAround

void smb2j_SimulateWind(void);
#define SimulateWind smb2j_SimulateWind

void smb2j_ModifyLeavesPos(void);
#define ModifyLeavesPos smb2j_ModifyLeavesPos

void smb2j_WindOn(void);
#define WindOn smb2j_WindOn

void smb2j_WindOff(void);
#define WindOff smb2j_WindOff

void smb2j_ScreenSubsForFinalRoom(void);
#define ScreenSubsForFinalRoom smb2j_ScreenSubsForFinalRoom

void smb2j_DrawFinalRoom(void);
#define DrawFinalRoom smb2j_DrawFinalRoom

void smb2j_RevealPrincess(void);
#define RevealPrincess smb2j_RevealPrincess

void smb2j_PrintVictoryMsgsForWorld8(void);
#define PrintVictoryMsgsForWorld8 smb2j_PrintVictoryMsgsForWorld8

void smb2j_EraseEndingCounters(void);
#define EraseEndingCounters smb2j_EraseEndingCounters

void smb2j_AwardExtraLives(void);
#define AwardExtraLives smb2j_AwardExtraLives

void smb2j_FadeToBlue(void);
#define FadeToBlue smb2j_FadeToBlue

void smb2j_EraseLivesLines(void);
#define EraseLivesLines smb2j_EraseLivesLines

void smb2j_RunMushroomRetainers(void);
#define RunMushroomRetainers smb2j_RunMushroomRetainers

void smb2j_EndingDiskRoutines(void);
#define EndingDiskRoutines smb2j_EndingDiskRoutines

void smb2j_MushroomRetainersForW8(void);
#define MushroomRetainersForW8 smb2j_MushroomRetainersForW8

void smb2j_WriteNameToVictoryMsg(void);
#define WriteNameToVictoryMsg smb2j_WriteNameToVictoryMsg


#pragma pack(pop)
