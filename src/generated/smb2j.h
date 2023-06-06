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
    inline struct_ycr07() {}
    inline struct_ycr07(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte y;
    bool c;
    byte r07;
};

typedef struct struct_xr00r01 struct_xr00r01, *Pstruct_xr00r01;

struct struct_xr00r01 {
    inline struct_xr00r01() {}
    inline struct_xr00r01(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte x;
    byte r00;
    byte r01;
};

typedef struct struct_nr00i struct_nr00i, *Pstruct_nr00i;

struct struct_nr00i {
    inline struct_nr00i() {}
    inline struct_nr00i(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    bool n;
    byte r00;
    bool i;
};

typedef struct struct_ncr00 struct_ncr00, *Pstruct_ncr00;

struct struct_ncr00 {
    inline struct_ncr00() {}
    inline struct_ncr00(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    bool n;
    bool c;
    byte r00;
};

typedef struct struct_xr00r06 struct_xr00r06, *Pstruct_xr00r06;

struct struct_xr00r06 {
    inline struct_xr00r06() {}
    inline struct_xr00r06(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte x;
    byte r00;
    byte r06;
};

typedef struct struct_r06r07i struct_r06r07i, *Pstruct_r06r07i;

struct struct_r06r07i {
    inline struct_r06r07i() {}
    inline struct_r06r07i(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte r06;
    byte r07;
    bool i;
};

typedef struct struct_ayr02r04r06r07 struct_ayr02r04r06r07, *Pstruct_ayr02r04r06r07;

struct struct_ayr02r04r06r07 {
    inline struct_ayr02r04r06r07() {}
    inline struct_ayr02r04r06r07(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte a;
    byte y;
    byte r02;
    byte r04;
    byte r06;
    byte r07;
};

typedef struct struct_azr02r04r06r07 struct_azr02r04r06r07, *Pstruct_azr02r04r06r07;

struct struct_azr02r04r06r07 {
    inline struct_azr02r04r06r07() {}
    inline struct_azr02r04r06r07(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte a;
    bool z;
    byte r02;
    byte r04;
    byte r06;
    byte r07;
};

typedef struct struct_r01r02r03 struct_r01r02r03, *Pstruct_r01r02r03;

struct struct_r01r02r03 {
    inline struct_r01r02r03() {}
    inline struct_r01r02r03(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte r01;
    byte r02;
    byte r03;
};

typedef struct struct_axzr04 struct_axzr04, *Pstruct_axzr04;

struct struct_axzr04 {
    inline struct_axzr04() {}
    inline struct_axzr04(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte a;
    byte x;
    bool z;
    byte r04;
};

typedef struct struct_xyi struct_xyi, *Pstruct_xyi;

struct struct_xyi {
    inline struct_xyi() {}
    inline struct_xyi(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte x;
    byte y;
    bool i;
};

typedef struct struct_axr00 struct_axr00, *Pstruct_axr00;

struct struct_axr00 {
    inline struct_axr00() {}
    inline struct_axr00(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte a;
    byte x;
    byte r00;
};

typedef struct struct_azi struct_azi, *Pstruct_azi;

struct struct_azi {
    inline struct_azi() {}
    inline struct_azi(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte a;
    bool z;
    bool i;
};

typedef struct struct_ayz struct_ayz, *Pstruct_ayz;

struct struct_ayz {
    inline struct_ayz() {}
    inline struct_ayz(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte a;
    byte y;
    bool z;
};

typedef struct struct_ayi struct_ayi, *Pstruct_ayi;

struct struct_ayi {
    inline struct_ayi() {}
    inline struct_ayi(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte a;
    byte y;
    bool i;
};

typedef struct struct_axz struct_axz, *Pstruct_axz;

struct struct_axz {
    inline struct_axz() {}
    inline struct_axz(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte a;
    byte x;
    bool z;
};

typedef struct struct_yr07i struct_yr07i, *Pstruct_yr07i;

struct struct_yr07i {
    inline struct_yr07i() {}
    inline struct_yr07i(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte y;
    byte r07;
    bool i;
};

typedef struct struct_axi struct_axi, *Pstruct_axi;

struct struct_axi {
    inline struct_axi() {}
    inline struct_axi(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte a;
    byte x;
    bool i;
};

typedef struct struct_xr05i struct_xr05i, *Pstruct_xr05i;

struct struct_xr05i {
    inline struct_xr05i() {}
    inline struct_xr05i(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte x;
    byte r05;
    bool i;
};

typedef struct struct_xci struct_xci, *Pstruct_xci;

struct struct_xci {
    inline struct_xci() {}
    inline struct_xci(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte x;
    bool c;
    bool i;
};

typedef struct struct_xyr02 struct_xyr02, *Pstruct_xyr02;

struct struct_xyr02 {
    inline struct_xyr02() {}
    inline struct_xyr02(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte x;
    byte y;
    byte r02;
};

typedef struct struct_yci struct_yci, *Pstruct_yci;

struct struct_yci {
    inline struct_yci() {}
    inline struct_yci(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte y;
    bool c;
    bool i;
};

typedef struct struct_ar00i struct_ar00i, *Pstruct_ar00i;

struct struct_ar00i {
    inline struct_ar00i() {}
    inline struct_ar00i(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte a;
    byte r00;
    bool i;
};

typedef struct struct_yr06r07 struct_yr06r07, *Pstruct_yr06r07;

struct struct_yr06r07 {
    inline struct_yr06r07() {}
    inline struct_yr06r07(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte y;
    byte r06;
    byte r07;
};

typedef struct struct_aci struct_aci, *Pstruct_aci;

struct struct_aci {
    inline struct_aci() {}
    inline struct_aci(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte a;
    bool c;
    bool i;
};

typedef struct struct_xr00i struct_xr00i, *Pstruct_xr00i;

struct struct_xr00i {
    inline struct_xr00i() {}
    inline struct_xr00i(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
    inline uint64_t subpiece(uint64_t a, uint64_t b) {
        uint64_t v = *this;
        return (v>>(a*8)) & BITMASK_HELPER(b);
    }

    byte x;
    byte r00;
    bool i;
};




void FUN_3000(void);
void FUN_300f(byte param_1,byte param_2);
void FUN_3023(byte param_1,byte param_2);
void FUN_303f(byte param_1,byte param_2);
void FUN_307b(byte param_1);
void FUN_30bf(byte param_1);
void FUN_30cf(byte param_1);
void FUN_30f3(byte param_1,byte param_2,byte param_3);
void FUN_31d3(byte param_1,byte param_2);
void FUN_31e3(byte param_1);
void FUN_31fb(byte param_1);
void FUN_3233(byte param_1);
void FUN_3247(byte param_1,byte param_2);
void FUN_327f(byte param_1,byte param_2);
void FUN_335f(byte param_1,byte param_2);
byte FUN_337b(byte param_1,byte param_2);
byte FUN_3407(byte param_1,byte param_2);
byte FUN_345f(byte param_1,byte param_2);
byte FUN_347f(byte param_1,byte param_2);
void FUN_3497(byte param_1);
void FUN_34b3(byte param_1);
void FUN_34cb(byte param_1);
void FUN_34e3(byte param_1);
void FUN_34fb(byte param_1);
void PauseRoutine(void);
void SpriteShuffler(void);
void OperModeExecutionTree(byte param_1);
void MoveAllSpritesOffscreen(void);
void MoveSpritesOffscreen(void);
void VictoryModeMain(byte param_1);
void VictoryModeSubroutines(byte param_1);
void SetupVictoryMode(void);
void DrawTitleScreen(void);
void PlayerVictoryWalk(void);
void PrintVictoryMessages(void);
void EndCastleAward(void);
void EndWorld1Thru7(void);
byte FloateyNumbersRoutine(byte param_1);
void ScreenRoutines(void);
void InitScreen(void);
void InitScreenPalette(void);
void SetupIntermediate(void);
void GetAreaPalette(void);
void GetBackgroundColor(void);
byte GetPlayerColors(void);
void GetAlternatePalette1(void);
void WriteTopStatusLine(void);
void WriteBottomStatusLine(void);
byte GetWorldNumForDisplay(void);
void DisplayTimeUp(void);
void OtherInter(byte param_1);
void DisplayIntermediate(void);
void AreaParserTaskControl(void);
void WriteGameText(byte param_1);
void WriteWarpZoneMessage(byte param_1);
void ResetSpritesAndScreenTimer(void);
void ResetScreenTimer(void);
void RenderAreaGraphics(void);
void RenderAttributeTables(void);
void ColorRotation(void);
byte RemoveCoin_Axe(byte param_1,byte param_2);
void ReplaceBlockMetatile(byte param_1,byte param_2,byte param_3,byte param_4);
void DestroyBlockMetatile(byte param_1,byte param_2,byte param_3);
void WriteBlockMetatile(byte param_1,byte param_2,byte param_3,byte param_4);
void MoveVOffset(byte param_1);
byte PutBlockMetatile(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
void RemBridge(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
void InitializeNameTables(void);
void WritePPUReg1(byte param_1);
void PrintStatusBarNumbers(byte param_1);
void OutputNumbers(byte param_1);
void DigitsMathRoutine(byte param_1);
void UpdateTopScore(void);
void InitializeArea(void);
void SecondaryGameSetup(void);
void GetAreaMusic(void);
void Entrance_GameTimerSetup(byte param_1);
void PlayerLoseLife(void);
void GameOverSubs(void);
void SetupGameOver(void);
void RunGameOver(void);
void TerminateGame(void);
void ContinueGame(void);
void DoNothing(void);
void AreaParserTaskHandler(void);
void AreaParserTasks(byte param_1);
void IncrementColumnPos(void);
void AreaParserCore(void);
void ProcessAreaData(void);
void IncAreaObjOffset(void);
void DecodeAreaData(byte param_1,byte param_2);
void LoopCmdE(void);
void AlterAreaAttributes(byte param_1);
void ScrollLockObject_Warp(void);
void ScrollLockObject(void);
void KillEnemies(byte param_1);
void AreaFrenzy(byte param_1);
void AreaStyleObject(byte param_1);
void TreeLedge(byte param_1);
void CloudLedge(byte param_1);
void AllUnder(byte param_1,byte param_2);
void NoUnder(byte param_1,byte param_2);
void PulleyRopeObject(byte param_1);
void CastleObject(byte param_1);
void WaterPipe(byte param_1);
void IntroPipe(byte param_1);
void ExitPipe(byte param_1);
struct_yci RenderSidewaysPipe(byte param_1,byte param_2);
void VerticalPipe(byte param_1,byte param_2);
struct_yr06r07 GetPipeHeight(byte param_1);
void SetupPiranhaPlant(byte param_1,byte param_2,byte param_3);
struct_xci FindEmptyEnemySlot(void);
void Hole_Water(byte param_1);
void QuestionBlockRow_High(byte param_1);
void QuestionBlockRow_Low(byte param_1);
void Bridge_High(byte param_1);
void Bridge_Middle(byte param_1);
void Bridge_Low(byte param_1);
void FlagBalls_Residual(byte param_1);
void FlagpoleObject(void);
void EndlessRope(void);
void BalancePlatRope(byte param_1);
void RowOfCoins(byte param_1);
void CastleBridgeObj(byte param_1,byte param_2);
void AxeObj(byte param_1);
void ChainObj(byte param_1);
void EmptyBlock(byte param_1);
void RowOfBricks(byte param_1);
void RowOfSolidBlocks(byte param_1);
void ColumnOfBricks(byte param_1);
void ColumnOfSolidBlocks(byte param_1);
void BulletBillCannon(byte param_1);
void StaircaseObject(byte param_1);
void Jumpspring(byte param_1);
void Hidden1UpBlock(byte param_1,byte param_2);
void QuestionBlock(byte param_1,byte param_2);
void BrickWithCoins(byte param_1,byte param_2);
void BrickWithItem(byte param_1,byte param_2);
byte GetAreaObjectID(byte param_1);
void Hole_Empty(byte param_1);
byte RenderUnderPart(byte param_1,byte param_2,byte param_3);
struct_ycr07 ChkLrgObjLength(byte param_1);
bool ChkLrgObjFixedLength(byte param_1,byte param_2);
struct_yr07i GetLrgObjAttrib(byte param_1);
byte GetAreaObjXPosition(void);
byte GetAreaObjYPosition(byte param_1);
struct_r06r07i GetBlockBufferAddr(byte param_1);
void GameModeSubs(void);
void GameCoreRoutine(void);
void UpdScrollVar(void);
void ScrollHandler(void);
void ChkPOffscr(void);
byte GetScreenPosition(void);
void GameRoutines(void);
void PlayerEntrance(void);
void AutoControlPlayer(byte param_1);
void PlayerCtrlRoutine(void);
void Vine_AutoClimb(void);
void SetEntr(void);
void VerticalPipeEntry(void);
void MovePlayerYAxis(byte param_1);
void SideExitPipeEntry(void);
byte ChgAreaMode(void);
void EnterSidePipe(void);
void PlayerChangeSize(void);
void PlayerInjuryBlink(void);
void InitChangeSize(void);
void PlayerDeath(void);
void DonePlayerTask(void);
void PlayerFireFlower(void);
void CyclePlayerPalette(byte param_1);
void ResetPalStar(void);
void FlagpoleSlide(void);
void PlayerEndLevel(void);
void NextArea(void);
void PlayerMovementSubs(void);
void OnGroundStateSub(void);
void JmpMove(void);
void FallingSub(void);
void JumpSwimSub(void);
void LRAir(void);
void ClimbingSub(void);
void PlayerPhysicsSub(void);
void GetPlayerAnimSpeed(void);
void ImposeFriction(byte param_1);
void ProcFireball_Bubble(void);
void FireballObjCore(byte param_1);
void BubbleCheck(byte param_1);
void SetupBubble(byte param_1,byte param_2);
void MoveBubl(byte param_1,byte param_2);
void RunGameTimer(void);
void WarpZoneObject(byte param_1);
void ProcessWhirlpools(void);
void FlagpoleRoutine(void);
byte JumpspringHandler(byte param_1);
void Setup_Vine(byte param_1,byte param_2);
byte VineObjectHandler(byte param_1);
void ProcessCannons(void);
byte BulletBillHandler(byte param_1);
struct_xci SpawnHammerObj(void);
byte ProcHammerObj(byte param_1);
void CoinBlock(byte param_1,bool param_2);
byte SetupJumpCoin(byte param_1,byte param_2,byte param_3);
byte JCoinC(byte param_1,byte param_2);
struct_yci FindEmptyMiscSlot(bool param_1);
void MiscObjectsCore(void);
byte GiveOneCoin(void);
byte AddToScore(void);
byte WriteScoreAndCoinTally(void);
byte WriteDigits(byte param_1);
void SetupPowerUp(byte param_1);
void PwrUpJmp(void);
byte PowerUpObjHandler(void);
void PlayerHeadCollision(byte param_1,byte param_2,byte param_3,byte param_4);
void InitBlock_XY_Pos(byte param_1);
void BumpBlock(byte param_1,byte param_2,byte param_3,byte param_4);
void MushFlowerBlock(byte param_1);
void StarBlock(byte param_1);
void PoisonMushBlock(byte param_1);
void ExtraLifeMushBlock(byte param_1);
void VineBlock(void);
struct_yci BlockBumpedChk(byte param_1);
void BrickShatter(byte param_1,byte param_2,byte param_3);
struct_xr05i CheckTopOfBlock(byte param_1,byte param_2,byte param_3,byte param_4);
void SpawnBrickChunks(byte param_1);
byte BlockObjectsCore(byte param_1);
void BlockObjMT_Updater(void);
struct_axi MoveEnemyHorizontally(byte param_1);
byte MovePlayerHorizontally(void);
byte MoveObjectHorizontally(byte param_1);
void MovePlayerVertically(void);
byte MoveD_EnemyVertically(byte param_1);
byte MoveFallingPlatform(byte param_1);
byte MoveRedPTroopaDown(byte param_1);
byte MoveRedPTroopaUp(byte param_1);
byte MoveDropPlatform(byte param_1);
byte MoveEnemySlowVert(byte param_1);
byte MoveJ_EnemyVertically(byte param_1);
byte SetXMoveAmt(byte param_1,byte param_2,byte param_3);
void ImposeGravityBlock(byte param_1);
void ImposeGravitySprObj(byte param_1,byte param_2,byte param_3);
byte MovePlatformDown(byte param_1);
byte MovePlatformUp(byte param_1);
byte RedPTroopaGrav(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
void ImposeGravity(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
byte EnemiesAndLoopsCore(byte param_1);
void ExecGameLoopback(byte param_1);
byte ProcLoopCommand(byte param_1);
void InitEnemyObject(byte param_1);
byte CheckThreeBytes(void);
byte Inc2B(void);
void CheckpointEnemyID(byte param_1);
void NoInitCode(void);
void InitGoomba(byte param_1);
void InitPodoboo(byte param_1);
void InitRetainerObj(byte param_1);
void InitNormalEnemy(byte param_1);
void InitRedKoopa(byte param_1);
void InitHammerBro(byte param_1);
void InitHorizFlySwimEnemy(byte param_1);
void InitBloober(byte param_1);
byte SmallBBox(byte param_1);
void InitRedPTroopa(byte param_1,bool param_2);
byte InitVStf(byte param_1);
void InitBulletBill(byte param_1);
void InitCheepCheep(byte param_1);
void InitLakitu(byte param_1);
void SetupLakitu(byte param_1);
void LakituAndSpinyHandler(byte param_1);
void InitLongFirebar(byte param_1);
void InitShortFirebar(byte param_1);
void InitFlyingCheepCheep(byte param_1);
void InitBowser(byte param_1);
void DuplicateEnemyObj(byte param_1);
void InitBowserFlame(byte param_1);
byte PutAtRightExtent(byte param_1,byte param_2);
void InitFireworks(byte param_1);
void BulletBillCheepCheep(byte param_1);
byte HandleGroupEnemies(byte param_1);
void InitPiranhaPlant(byte param_1);
void InitEnemyFrenzy(byte param_1);
void NoFrenzyCode(void);
void EndFrenzy(byte param_1);
void InitJumpGPTroopa(byte param_1);
void InitBalPlatform(byte param_1);
void InitDropPlatform(byte param_1);
void InitHoriPlatform(byte param_1);
void InitVertPlatform(byte param_1);
void SPBBox(byte param_1);
void LargeLiftUp(byte param_1);
void LargeLiftDown(byte param_1);
void PlatLiftUp(byte param_1);
void PlatLiftDown(byte param_1);
void PosPlatform(byte param_1,byte param_2);
void EndOfEnemyInitCode(void);
byte RunEnemyObjectsCore(void);
void NoRunCode(void);
byte RunRetainerObj(byte param_1);
byte RunNormalEnemies(byte param_1);
byte EnemyMovementSubs(byte param_1);
void NoMoveCode(void);
byte RunBowserFlame(byte param_1);
byte RunFirebarObj(byte param_1);
byte RunSmallPlatform(byte param_1);
byte RunLargePlatform(byte param_1);
byte LargePlatformSubroutines(byte param_1);
byte EraseEnemyObject(byte param_1);
byte MovePodoboo(byte param_1);
byte ProcHammerBro(byte param_1);
byte SetHJ(byte param_1,byte param_2,byte param_3);
byte MoveHammerBroXDir(byte param_1);
byte MoveNormalEnemy(byte param_1);
byte MoveDefeatedEnemy(byte param_1);
byte MoveJumpingEnemy(byte param_1);
byte ProcMoveRedPTroopa(byte param_1);
byte MoveFlyGreenPTroopa(byte param_1);
void XMoveCntr_GreenPTroopa(byte param_1);
void XMoveCntr_Platform(byte param_1,byte param_2);
struct_xr00i MoveWithXMCntrs(byte param_1);
byte MoveBloober(byte param_1,bool param_2);
void ProcSwimmingB(byte param_1,bool param_2);
byte MoveBulletBill(byte param_1);
byte MoveSwimmingCheepCheep(byte param_1);
byte ProcFirebar(byte param_1);
struct_xr00r06 DrawFirebar_Collision(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
struct_xr00r06 FirebarCollision(byte param_1,byte param_2,byte param_3,byte param_4);
struct_r01r02r03 GetFirebarPosition(byte param_1,byte param_2);
byte MoveFlyingCheepCheep(byte param_1);
byte MoveLakitu(byte param_1);
byte PlayerLakituDiff(byte param_1,byte param_2,byte param_3,byte param_4);
void BridgeCollapse(byte param_1);
byte MoveD_Bowser(byte param_1);
byte RunBowser(byte param_1);
byte KillAllEnemies(void);
byte BowserGfxHandler(byte param_1);
byte ProcessBowserHalf(byte param_1);
byte SetFlameTimer(void);
byte ProcBowserFlame(byte param_1);
byte RunFireworks(byte param_1);
byte RunStarFlagObj(byte param_1);
void GameTimerFireworks(byte param_1);
void StarFlagExit(void);
byte AwardGameTimerPoints(byte param_1);
byte AwardTimerCastle(void);
byte EndAreaPoints(void);
byte RaiseFlagSetoffFWorks(byte param_1);
byte DrawStarFlag(byte param_1);
byte DelayToAreaEnd(byte param_1);
void MovePiranhaPlant(byte param_1);
byte FirebarSpin(byte param_1,byte param_2);
byte BalancePlatform(byte param_1);
struct_xr00r01 SetupPlatformRope(byte param_1,byte param_2);
byte InitPlatformFall(byte param_1);
void StopPlatforms(byte param_1,byte param_2);
byte PlatformFall(byte param_1,byte param_2);
byte YMovingPlatform(byte param_1);
void ChkYPCollision(byte param_1);
byte XMovingPlatform(byte param_1);
void PositionPlayerOnHPlat(byte param_1,byte param_2);
byte DropPlatform(byte param_1);
byte RightPlatform(byte param_1);
void MoveLargeLiftPlat(byte param_1);
void MoveSmallPlatform(byte param_1);
void MoveLiftPlatforms(byte param_1);
void ChkSmallPlatCollision(byte param_1);
void OffscreenBoundsCheck(byte param_1);
byte FireballEnemyCollision(byte param_1);
void HandleEnemyFBallCol(byte param_1,byte param_2);
void ShellOrBlockDefeat(byte param_1);
void EnemySmackScore(byte param_1,byte param_2);
byte PlayerHammerCollision(byte param_1);
byte HandlePowerUpCollision(byte param_1);
byte PlayerEnemyCollision(byte param_1);
byte InjurePlayer(void);
byte ForceInjury(byte param_1);
byte SetPRout(byte param_1,byte param_2);
byte SetBounce(byte param_1);
byte ChkEnemyFaceRight(byte param_1);
byte LInj(byte param_1);
byte EnemyFacePlayer(byte param_1);
void SetupFloateyNumber(byte param_1,byte param_2);
byte EnemiesCollision(byte param_1);
void ProcEnemyCollisions(byte param_1,byte param_2,byte param_3);
void EnemyTurnAround(byte param_1);
void RXSpd(byte param_1);
byte LargePlatformCollision(byte param_1);
byte ChkForPlayerC_LargeP(byte param_1);
byte SmallPlatformCollision(byte param_1);
byte ProcLPlatCollisions(byte param_1,byte param_2,byte param_3);
void PositionPlayerOnS_Plat(byte param_1,byte param_2);
void PositionPlayerOnVPlat(byte param_1);
bool CheckPlayerVertical(void);
struct_ayi GetEnemyBoundBoxOfs(void);
struct_ayi GetEnemyBoundBoxOfsArg(byte param_1);
void PlayerBGCollision(void);
void ErACM(byte param_1,byte param_2,byte param_3);
void HandleClimbing(byte param_1,byte param_2,byte param_3);
bool ChkInvisibleMTiles(byte param_1);
void ChkForLandJumpSpring(byte param_1);
bool ChkJumpspringMetatiles(byte param_1);
void HandlePipeEntry(byte param_1,byte param_2);
void ImpedePlayerMove(byte param_1);
bool CheckForSolidMTiles(byte param_1);
bool CheckForClimbMTiles(byte param_1);
struct_aci CheckForCoinMTiles(byte param_1);
byte GetMTileAttrib(byte param_1);
byte EnemyToBGCollisionDet(byte param_1);
void ChkToStunEnemies(byte param_1);
void NoDemote(byte param_1,byte param_2);
byte ChkForRedKoopa(byte param_1);
byte DoEnemySideCheck(byte param_1);
byte ChkForBump_HammerBroJ(byte param_1);
struct_ncr00 PlayerEnemyDiff(byte param_1);
void EnemyLanding(byte param_1);
bool SubtEnemyYPos(byte param_1);
byte EnemyJump(byte param_1);
byte HammerBroBGColl(byte param_1);
void KillEnemyAboveBlock(byte param_1);
struct_axzr04 ChkUnderEnemy(byte param_1);
bool ChkForNonSolids(byte param_1);
byte FireballBGCollision(byte param_1);
byte GetFireballBoundBox(byte param_1);
byte GetMiscBoundBox(byte param_1);
byte GetEnemyBoundBox(byte param_1);
byte SmallPlatformBoundBox(byte param_1);
byte GetMaskedOffScrBits(byte param_1,byte param_2,byte param_3);
byte LargePlatformBoundBox(byte param_1);
byte SetupEOffsetFBBox(byte param_1);
void MoveBoundBoxOffscreen(byte param_1);
byte BoundingBoxCore(byte param_1,byte param_2);
byte CheckRightScreenBBox(byte param_1,byte param_2);
bool PlayerCollisionCore(byte param_1);
bool SprObjectCollisionCore(byte param_1,byte param_2);
struct_axzr04 BlockBufferChk_Enemy(byte param_1,byte param_2,byte param_3);
struct_axz BlockBufferChk_FBall(byte param_1);
struct_ayr02r04r06r07 BlockBufferColli_Feet(byte param_1);
struct_azr02r04r06r07 BlockBufferColli_Head(byte param_1);
struct_azr02r04r06r07 BlockBufferColli_Side(byte param_1);
struct_azr02r04r06r07 BlockBufferCollision(byte param_1,byte param_2,byte param_3);
void DrawVine(byte param_1);
byte SixSpriteStacker(byte param_1,byte param_2,byte param_3);
byte DrawHammer(byte param_1);
void FlagpoleGfxHandler(byte param_1);
void MoveSixSpritesOffscreen(byte param_1);
void DumpSixSpr(byte param_1,byte param_2);
void DumpFourSpr(byte param_1,byte param_2);
void DumpThreeSpr(byte param_1,byte param_2);
void DumpTwoSpr(byte param_1,byte param_2);
byte DrawLargePlatform(byte param_1);
byte JCoinGfxHandler(byte param_1);
byte DrawPowerUp(void);
byte EnemyGfxHandler(byte param_1);
byte SprObjectOffscrChk(void);
struct_xyr02 DrawEnemyObjRow(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6);
struct_xyr02 DrawOneSpriteRow(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,byte param_7,byte param_8);
void MoveESprRowOffscreen(byte param_1,byte param_2);
void MoveESprColOffscreen(byte param_1,byte param_2);
byte DrawBlock(byte param_1);
void ChkLeftCo(byte param_1,byte param_2);
byte MoveColOffscreen(byte param_1);
void DrawBrickChunks(byte param_1);
void DrawFireball(byte param_1);
void DrawFirebar(byte param_1);
void DrawExplosion_Fireball(byte param_1);
byte DrawExplosion_Fireworks(byte param_1,byte param_2);
byte DrawSmallPlatform(byte param_1);
void DrawBubble(byte param_1);
void PlayerGfxHandler(void);
void FindPlayerAction(void);
void PlayerGfxProcessing(byte param_1);
void DrawPlayer_Intermediate(void);
void RenderPlayerSub(byte param_1);
void DrawPlayerLoop(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,byte param_7);
byte ProcessPlayerAction(void);
byte GetCurrentAnimOffset(byte param_1);
byte FourFrameExtent(byte param_1);
byte ThreeFrameExtent(byte param_1);
byte AnimationControl(byte param_1,byte param_2);
byte GetGfxOffsetAdder(byte param_1);
byte HandleChangeSize(void);
void ChkForPlayerAttrib(void);
byte RelativePlayerPosition(void);
byte RelativeBubblePosition(byte param_1);
byte RelativeFireballPosition(byte param_1);
byte RelativeMiscPosition(byte param_1);
struct_axr00 RelativeEnemyPosition(byte param_1);
byte RelativeBlockPosition(byte param_1);
struct_axr00 VariableObjOfsRelPos(byte param_1,byte param_2,byte param_3);
byte GetObjRelativePosition(byte param_1,byte param_2);
void GetPlayerOffscreenBits(void);
byte GetFireballOffscreenBits(byte param_1);
byte GetBubbleOffscreenBits(byte param_1);
byte GetMiscOffscreenBits(byte param_1);
byte GetProperObjOffset(byte param_1,byte param_2);
struct_xyi GetEnemyOffscreenBits(byte param_1);
byte GetBlockOffscreenBits(byte param_1);
struct_xyi GetOffScreenBitsSet(byte param_1,byte param_2);
struct_ar00i RunOffscrBitsSubs(byte param_1);
byte GetXOffscreenBits(byte param_1);
byte GetYOffscreenBits(byte param_1);
byte DividePDiff(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5);
struct_xyr02 DrawSpriteObject(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,byte param_7,byte param_8);
void AttractModeSubs(void);
void HardWorldsCheckpoint(void);
void LoadHardWorlds(void);
void AttractModeDiskRoutines(void);
void LoadWorlds1Thru4(void);
void GameModeDiskRoutines(void);
void LoadWorlds5Thru8(void);
void ResetDiskIOTask(void);
void VMDelay(void);
void StartVMDelay(void);
void ContinueVMDelay(void);
void VictoryModeDiskRoutines(void);
void LoadEnding(void);
bool CheckFileCount(byte param_1);
void DiskScreen(void);
void WaitForEject(void);
void WaitForReinsert(void);
void ResetDiskVars(void);
void DiskErrorHandler(byte param_1);
void GameOverMenu(void);
void LoadPhysicsData(void);
void LoadMarioPhysics(void);
void ModifyPhysics(byte param_1,byte param_2);
void LoadAreaPointer(void);
byte GetAreaType(byte param_1);
byte FindAreaPointer(void);
undefined FUN_e149();
void AltHard_GetAreaDataAddrs(void);
void ChangeHalfwayPages(void);
void GetAreaDataAddrs(void);
void GameMenuRoutine(void);
void DrawMenuCursor(void);
void SetupMenuCursor(void);
bool DemoEngine(void);
void ClearBuffersDrawIcon(void);
void WriteTopScore(void);
void InitializeGame(void);
void DemoReset(void);
void PrimaryGameSetup(void);
void PatchPlayerNamePal(void);
void UpsideDownPipe_High(byte param_1);
void UpsideDownPipe_Low(byte param_1);
void MoveUpsideDownPiranhaP(byte param_1);
void BlowPlayerAround(void);
void SimulateWind(void);
void ModifyLeavesPos(void);
void WindOn(void);
void WindOff(void);
void ScreenSubsForFinalRoom(void);
void DrawFinalRoom(void);
void RevealPrincess(void);
void PrintVictoryMsgsForWorld8(void);
void EraseEndingCounters(void);
void AwardExtraLives(void);
void FadeToBlue(void);
void EraseLivesLines(void);
void RunMushroomRetainers(void);
void EndingDiskRoutines(void);
void MushroomRetainersForW8(void);
void WriteNameToVictoryMsg(void);

#pragma pack(pop)
#include "../smb_functions.h"
