#ifndef SMBCORE_VARS_H
#define SMBCORE_VARS_H

// Note: None of the RAM or RAMARRAY declarations should overlap each other.
// If aliasing occurs, refer to to an existing declaration.
// TODO: Fix aliasing with the $0300 page. Many of the variables there overlap.


// some noisy names used during ghidra decompilation
// should be removed eventually
#define PlayerSpriteVarData1 SprObject_X_Speed
#define SpriteVarData1 Enemy_X_Speed
#define PlayerSpriteVarData2 SprObject_Y_Speed
#define SpriteVarData2 Enemy_Y_Speed
#define Cannon_Or_Whirlpool_PageLoc      Cannon_PageLoc
#define Cannon_Or_Whirlpool_X_Position   Cannon_X_Position
#define Cannon_X_Position_Or_Whirlpool_LeftExtent Cannon_X_Position
#define Whirlpool_LeftExtent Whirlpool_X_Position
#define Cannon_Y_Position_Or_Whirlpool_Length Cannon_Y_Position
#define Cannon_Timer_Or_Whirlpool_Flag   Cannon_Timer
#define HammerThrowingTimer_Or_PlatformCollisionFlag PlatformCollisionFlag
#define CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos Enemy_Y_MoveForce
#define Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos (SprObject_X_MoveForce + 1)
#define BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos (SprObject_YMF_Dummy + 1)
#define PlayerOrSprObject_YMF_Dummy      SprObject_YMF_Dummy
#define PlayerOrSprObject_Y_MoveForce    SprObject_Y_MoveForce
#define Cannon_Or_Whirlpool_Offset       Cannon_Offset
#define PlayerOrSprObj_BoundBoxCtrl  SprObj_BoundBoxCtrl
#define PlayerOrSprDataOffset        SprDataOffset
#define AltOrBlock_SprDataOffset     (SprDataOffset + 8)
#define ScreenEdgeOrLeft_PageLoc ScreenEdge_PageLoc
#define ScreenEdgeOrLeft_X_Pos ScreenEdge_X_Pos
#define DisplayDigits_Or_TopScoreDisplay DisplayDigits
#define PlayerScoreDisplay_Or_ScoreAndCoinDisplay (DisplayDigits + 6)


// These are used largely to zero-out the memory in these regions

#define VRAM_Page                        RAMARRAY(0x0300, 0x100)
#define Objects_Page                     RAMARRAY(0x0400, 0x100)


// Pointers
// Note: The port accesses data using pointers stored elsewhere instead of the 16-bit values here,
// but we still store the 16-bit 6502 pointers to support save states (for now).
// These are pointers to ROM.

#define AreaData_addr_lo                 RAM(0x00E7)
#define AreaData_addr_hi                 RAM(0x00E8)
#define EnemyData_addr_lo                RAM(0x00E9)
#define EnemyData_addr_hi                RAM(0x00EA)
#define MusicData_addr_lo                RAM(0x00F5)
#define MusicData_addr_hi                RAM(0x00F6)


/* common ----------------------- */
#define ObjectOffset                     RAM(0x0008)
#define FrameCounter                     RAM(0x0009)
#define A_B_Buttons                      RAM(0x000A)
#define Up_Down_Buttons                  RAM(0x000B)
#define Left_Right_Buttons               RAM(0x000C)
#define PreviousA_B_Buttons              RAM(0x000D)
#define GameEngineSubroutine             RAM(0x000E)
#define Enemy_Flag                       RAMARRAY(0x000F, 6+1)  // +1, because SpawnHammerObj regularly accesses Enemy_Flag[6].
#define Enemy_ID                         RAMARRAY(0x0016, 6)
#define Player_State                     RAM(0x001D)
#define Enemy_State                      RAMARRAY(0x001E, 6)
#define Fireball_State                   RAMARRAY(0x0024, 2)
#define Block_State                      RAMARRAY(0x0026, 2)
#define Misc_State                       RAMARRAY(0x002A, 9)
#define PlayerFacingDir                  RAM(0x0033)
#define FirebarSpinDirection             RAMARRAY(0x0034, 5)

// reuses memory
#define VictoryDestPageLoc               FirebarSpinDirection[0]
#define VictoryWalkControl               FirebarSpinDirection[1]

#define PowerUpType                      RAM(0x0039)
#define FireballBouncingFlag             RAMARRAY(0x003A, 2)
#define HammerBroJumpTimer               RAMARRAY(0x003C, 6)	// as many as Enemy_ID
#define Player_MovingDir                 RAM(0x0045)
#define Enemy_MovingDir                  RAMARRAY(0x0046, 6)	// as many as Enemy_ID

#define SprObject_X_Speed                RAMARRAY(0x0057, 22)
#define Player_X_Speed                   SprObject_X_Speed[0]
#define Enemy_X_Speed                    (SprObject_X_Speed + 1)
#define Fireball_X_Speed                 (SprObject_X_Speed + 7)
#define Block_X_Speed                    (SprObject_X_Speed + 9)
#define Misc_X_Speed                     (SprObject_X_Speed + 13)

//# define BlooperMoveSpeed                 RAMARRAY(0x0058, 0)
//# define CheepCheepMoveMFlag              RAMARRAY(0x0058, 0)
//# define ExplosionGfxCounter              RAMARRAY(0x0058, 0)
//# define FirebarSpinState_Low             RAMARRAY(0x0058, 0)
//# define Jumpspring_FixedYPos             RAMARRAY(0x0058, 0)
//# define LakituMoveSpeed                  RAMARRAY(0x0058, 0)
//# define PiranhaPlant_Y_Speed             RAMARRAY(0x0058, 0)
//# define RedPTroopaCenterYPos             RAMARRAY(0x0058, 0)
//# define XMoveSecondaryCounter            RAMARRAY(0x0058, 0)
//# define YPlatformCenterYPos              RAMARRAY(0x0058, 0)

#define SprObject_PageLoc                RAMARRAY(0x006D, 25)	// 3 more, because of bubbles
#define Player_PageLoc                   SprObject_PageLoc[0]
#define Enemy_PageLoc                    (SprObject_PageLoc + 1)
#define Fireball_PageLoc                 (SprObject_PageLoc + 7)
#define Block_PageLoc                    (SprObject_PageLoc + 9)
#define Misc_PageLoc                     (SprObject_PageLoc + 13)
#define Bubble_PageLoc                   (SprObject_PageLoc + 22)

#define SprObject_X_Position             RAMARRAY(0x0086, 25)	// 3 more, because of bubbles
#define Player_X_Position                SprObject_X_Position[0]
#define Enemy_X_Position                 (SprObject_X_Position + 1)
#define Fireball_X_Position              (SprObject_X_Position + 7)
#define Block_X_Position                 (SprObject_X_Position + 9)
#define Misc_X_Position                  (SprObject_X_Position + 13)
#define Bubble_X_Position                (SprObject_X_Position + 22)

#define SprObject_Y_Speed                RAMARRAY(0x009F, 22)
#define Player_Y_Speed                   SprObject_Y_Speed[0]
#define Enemy_Y_Speed                    (SprObject_Y_Speed + 1)
#define Fireball_Y_Speed                 (SprObject_Y_Speed + 7)
#define Block_Y_Speed                    (SprObject_Y_Speed + 9)
#define Misc_Y_Speed                     (SprObject_Y_Speed + 13)

//# define BlooperMoveCounter               RAMARRAY(0x00A0, 0)
//# define ExplosionTimerCounter            RAMARRAY(0x00A0, 0)
//# define FirebarSpinState_High            RAMARRAY(0x00A0, 0)
//# define LakituMoveDirection              RAMARRAY(0x00A0, 0)
//# define PiranhaPlant_MoveFlag            RAMARRAY(0x00A0, 0)
//# define XMovePrimaryCounter              RAMARRAY(0x00A0, 0)

#define SprObject_Y_HighPos              RAMARRAY(0x00B5, 25)	// 3 more, because of bubbles
#define Player_Y_HighPos                 SprObject_Y_HighPos[0]
#define Enemy_Y_HighPos                  (SprObject_Y_HighPos + 1)
#define Fireball_Y_HighPos               (SprObject_Y_HighPos + 7)
#define Block_Y_HighPos                  (SprObject_Y_HighPos + 9)
#define Misc_Y_HighPos                   (SprObject_Y_HighPos + 13)
#define Bubble_Y_HighPos                 (SprObject_Y_HighPos + 22)

#define SprObject_Y_Position             RAMARRAY(0x00CE, 25)	// 3 more, because of bubbles
#define Player_Y_Position                SprObject_Y_Position[0]
#define Enemy_Y_Position                 (SprObject_Y_Position + 1)
#define Fireball_Y_Position              (SprObject_Y_Position + 7)
#define Block_Y_Position                 (SprObject_Y_Position + 9)
#define Misc_Y_Position                  (SprObject_Y_Position + 13)
#define Bubble_Y_Position                (SprObject_Y_Position + 22)

// $EB to $EF are treated as temporary registers.
// $EE is never used, but it's in that range.
// #define rEB                              RAM(0x00EB)
// #define rEC                              RAM(0x00EC)
// #define rED                              RAM(0x00ED)
#define rEF                              RAM(0x00EF)

#define NoteLenLookupTblOfs              RAM(0x00F0)
#define Square1SoundBuffer               RAM(0x00F1)
#define Square2SoundBuffer               RAM(0x00F2)
#define NoiseSoundBuffer                 RAM(0x00F3)
#define AreaMusicBuffer                  RAM(0x00F4)
#define MusicOffset_Square2              RAM(0x00F7)
#define MusicOffset_Square1              RAM(0x00F8)
#define MusicOffset_Triangle             RAM(0x00F9)
#define PauseSoundQueue                  RAM(0x00FA)
#define AreaMusicQueue                   RAM(0x00FB)
#define EventMusicQueue                  RAM(0x00FC)
#define NoiseSoundQueue                  RAM(0x00FD)
#define Square2SoundQueue                RAM(0x00FE)
#define Square1SoundQueue                RAM(0x00FF)
#define VerticalFlipFlag                 RAM(0x0109)
#define FlagpoleFNum_Y_Pos               RAM(0x010D)
#define FlagpoleFNum_YMFDummy            RAM(0x010E)
#define FlagpoleScore                    RAM(0x010F)

#define FloateyNum_Control               RAMARRAY(0x0110, 7)
#define FloateyNum_X_Pos                 RAMARRAY(0x0117, 7)
#define FloateyNum_Y_Pos                 RAMARRAY(0x011E, 7)
#define ShellChainCounter                RAMARRAY(0x0125, 7)
#define FloateyNum_Timer                 RAMARRAY(0x012C, 7)

#define DigitModifier_Minus1             RAMARRAY(0x0133, 7)
#define DigitModifier                    (DigitModifier_Minus1 + 1)

//#define TheStack                         RAMARRAY(0x0160, (0x200 - 0x160))

#define Sprite_Data                      RAMARRAY(0x0200, 0x100)

// There's a lot of ugly aliasing (overlapping) with VRAM here...

#define VRAM_Data1                       RAMARRAY(0x0300, 0x100)
#define VRAM_Data2                       RAMARRAY(0x0340, 0x0C0)

// Note: crosses into $0400 and a bunch of other variables.
// This should be of little consequence, because memory is cleared before starting new areas.
// However, it's not cleared before starting the demo, so it might affect that... maybe.
#define VRAM_SMB1_TitleScreen            RAMARRAY(0x0300, 0x13A)

#define VRAM_Buffer1_Offset              VRAM_Data1[0]
#define VRAM_Buffer1                     (VRAM_Data1 + 1)
#define VRAM_Buffer2_Offset              VRAM_Data2[0]
#define VRAM_Buffer2                     (VRAM_Data2 + 1)

#define BowserBodyControls               RAM(0x0363)
#define BowserFeetCounter                RAM(0x0364)
#define BowserMovementSpeed              RAM(0x0365)
#define BowserOrigXPos                   RAM(0x0366)
#define BowserFlameTimerCtrl             RAM(0x0367)
#define BowserFront_Offset               RAM(0x0368)
#define BridgeCollapseOffset             RAM(0x0369)
#define BowserGfxFlag                    RAM(0x036A)
#define FirebarSpinSpeed                 RAMARRAY(0x0388, 5)
#define VineFlagOffset                   RAM(0x0398)
#define VineHeight                       RAM(0x0399)
#define VineObjOffset                    RAMARRAY(0x039A, 2)
#define VineStart_Y_Position             RAM(0x039D)
#define BalPlatformAlignment             RAM(0x03A0)
#define Platform_X_Scroll                RAM(0x03A1)

#define PlatformCollisionFlag            RAMARRAY(0x03A2, 5)

// reuses memory
#define HammerThrowingTimer PlatformCollisionFlag

#define SprObject_Rel_XPos               RAMARRAY(0x03AD, 7)
#define Player_Rel_XPos                  SprObject_Rel_XPos[0]
#define Enemy_Rel_XPos                   SprObject_Rel_XPos[1]
#define Fireball_Rel_XPos                SprObject_Rel_XPos[2]
#define Bubble_Rel_XPos                  SprObject_Rel_XPos[3]
#define Block_Rel_XPos                   SprObject_Rel_XPos[4]
#define Block_Rel_XPos_2                 SprObject_Rel_XPos[5]
#define Misc_Rel_XPos                    SprObject_Rel_XPos[6]

#define SprObject_Rel_YPos               RAMARRAY(0x03B8, 7)
#define Player_Rel_YPos                  SprObject_Rel_YPos[0]
#define Enemy_Rel_YPos                   SprObject_Rel_YPos[1]
#define Fireball_Rel_YPos                SprObject_Rel_YPos[2]
#define Bubble_Rel_YPos                  SprObject_Rel_YPos[3]
#define Block_Rel_YPos                   SprObject_Rel_YPos[4]
#define Block_Rel_YPos_2                 SprObject_Rel_YPos[5]
#define Misc_Rel_YPos                    SprObject_Rel_YPos[6]

#define SprObject_Attrib                 RAMARRAY(0x03C4, 7)
#define Player_SprAttrib                 SprObject_Attrib[0]
#define Enemy_SprAttrib                  (SprObject_Attrib + 1)

#define SprObject_OffscrBits             RAMARRAY(0x03D0, 7)
#define Player_OffscreenBits             SprObject_OffscrBits[0]
#define Enemy_OffscreenBits              SprObject_OffscrBits[1]
#define FBall_OffscreenBits              SprObject_OffscrBits[2]
#define Bubble_OffscreenBits             SprObject_OffscrBits[3]
#define Block_OffscreenBits              SprObject_OffscrBits[4]
//
#define Misc_OffscreenBits               SprObject_OffscrBits[6]

#define EnemyOffscrBitsMasked            RAMARRAY(0x03D8, 6)
#define Block_Orig_YPos                  RAMARRAY(0x03E4, 2)
#define Block_BBuf_Low                   RAMARRAY(0x03E6, 2)
#define Block_Metatile                   RAMARRAY(0x03E8, 2)
#define Block_PageLoc2                   RAMARRAY(0x03EA, 2)
#define Block_RepFlag                    RAMARRAY(0x03EC, 2)
#define SprDataOffset_Ctrl               RAM(0x03EE)
#define Block_ResidualCounter            RAM(0x03F0)
#define Block_Orig_XPos                  RAMARRAY(0x03F1, 2)
#define AttributeBuffer                  RAMARRAY(0x03F9, 7)

#define SprObject_X_MoveForce            RAMARRAY(0x0400, 22)

#define Enemy_X_MoveForce                (SprObject_X_MoveForce + 1)
#define RedPTroopaOrigXPos               (SprObject_X_MoveForce + 1)
#define YPlatformTopYPos                 (SprObject_X_MoveForce + 1)

#define SprObject_YMF_Dummy              RAMARRAY(0x0416, 22)
#define Player_YMF_Dummy   SprObject_YMF_Dummy[0]
#define Enemy_YMF_Dummy                  (SprObject_YMF_Dummy + 1)

// #define BowserFlamePRandomOfs            (SprObject_YMF_Dummy + 1)
// #define PiranhaPlantUpYPos               (SprObject_YMF_Dummy + 1)

#define Bubble_YMF_Dummy                 RAMARRAY(0x042C, 3)
#define SprObject_Y_MoveForce            RAMARRAY(0x0433, 22)
#define Player_Y_MoveForce               SprObject_Y_MoveForce[0]
#define Enemy_Y_MoveForce                (SprObject_Y_MoveForce + 1)
#define Block_Y_MoveForce                (SprObject_Y_MoveForce + 9)

// #define CheepCheepOrigYPos               (SprObject_Y_MoveForce + 1)
// #define PiranhaPlantDownYPos             (SprObject_Y_MoveForce + 1)

#define MaximumLeftSpeed                 RAM(0x0450)
#define MaximumRightSpeed                RAM(0x0456)

#define Cannon_Offset                    RAM(0x046A)
#define Cannon_PageLoc                   RAMARRAY(0x046B, 6)
#define Cannon_X_Position                RAMARRAY(0x0471, 6)
#define Cannon_Y_Position                RAMARRAY(0x0477, 6)
#define Cannon_Timer                     RAMARRAY(0x047D, 6)

// the whirlpools reuse memory from the cannons (or vice-versa)
#define Whirlpool_Offset                 Cannon_Offset
#define Whirlpool_PageLoc                Cannon_PageLoc
#define Whirlpool_X_Position             Cannon_X_Position
#define Whirlpool_Length                 Cannon_Y_Position
#define Whirlpool_Flag                   Cannon_Timer[0]

#define BowserHitPoints                  RAM(0x0483)
#define StompChainCounter                RAM(0x0484)
#define Player_CollisionBits             RAM(0x0490)

#define Enemy_CollisionBits              RAMARRAY(0x0491, 6)

#define SprObj_BoundBoxCtrl              RAMARRAY(0x0499, 18)
#define Player_BoundBoxCtrl              SprObj_BoundBoxCtrl[0]
#define Enemy_BoundBoxCtrl               (SprObj_BoundBoxCtrl + 1)
#define Fireball_BoundBoxCtrl            (SprObj_BoundBoxCtrl + 7)
#define Misc_BoundBoxCtrl                (SprObj_BoundBoxCtrl + 9)

#define BoundingBoxCoords                RAMARRAY(0x04AC, 21*4)

#define Block_Buffers                    RAMARRAY(0x0500, 0x1A0)
// #define Block_Buffer_1                   RAMARRAY(0x0500, 0xD0)
// #define Block_Buffer_2                   RAMARRAY(0x05D0, 0xD0)

#define BlockBufferColumnPos             RAM(0x06A0)
#define MetatileBuffer                   RAMARRAY(0x06A1, 13)       // note: this overflows rarely. but MetatileBuffer[13] is accessed in World 4-3 in this TAS: https://tasvideos.org/6913S
#define HammerEnemyOffset                RAMARRAY(0x06AE, 9)
#define JumpCoinMiscOffset               RAM(0x06B7)
#define BrickCoinTimerFlag               RAM(0x06BC)
#define Misc_Collision_Flag              RAMARRAY(0x06BE, 12)
#define EnemyFrenzyBuffer                RAM(0x06CB)
#define SecondaryHardMode                RAM(0x06CC)
#define EnemyFrenzyQueue                 RAM(0x06CD)
#define FireballCounter                  RAM(0x06CE)
#define DuplicateObj_Offset              RAM(0x06CF)
#define LakituReappearTimer              RAM(0x06D1)
#define NumberofGroupEnemies             RAM(0x06D3)
#define ColorRotateOffset                RAM(0x06D4)
#define PlayerGfxOffset                  RAM(0x06D5)
#define WarpZoneControl                  RAM(0x06D6)
#define FireworksCounter                 RAM(0x06D7)
#define MultiLoopCorrectCntr             RAM(0x06D9)
#define MultiLoopPassCntr                RAM(0x06DA)
#define JumpspringForce                  RAM(0x06DB)
#define MaxRangeFromOrigin               RAM(0x06DC)
#define BitMFilter                       RAM(0x06DD)
#define ChangeAreaTimer                  RAM(0x06DE)
#define SprShuffleAmtOffset              RAM(0x06E0)

#define SprShuffleAmt                    RAMARRAY(0x06E1, 3)

#define SprDataOffset                    RAMARRAY(0x06E4, 24)
#define Player_SprDataOffset             SprDataOffset[0]
#define Enemy_SprDataOffset              (SprDataOffset + 1)
#define Alt_SprDataOffset                (SprDataOffset + 8)
#define Block_SprDataOffset              (SprDataOffset + 8)
#define Bubble_SprDataOffset             (SprDataOffset + 10)
#define FBall_SprDataOffset              (SprDataOffset + 13)
#define Misc_SprDataOffset               (SprDataOffset + 15)

#define SavedJoypadBits                  RAMARRAY(0x06FC, 2)
#define Player_X_Scroll                  RAM(0x06FF)
#define Player_XSpeedAbsolute            RAM(0x0700)
#define FrictionAdderHigh                RAM(0x0701)
#define FrictionAdderLow                 RAM(0x0702)
#define RunningSpeed                     RAM(0x0703)
#define SwimmingFlag                     RAM(0x0704)
#define Player_X_MoveForce               RAM(0x0705)
#define DiffToHaltJump                   RAM(0x0706)
#define JumpOrigin_Y_HighPos             RAM(0x0707)
#define JumpOrigin_Y_Position            RAM(0x0708)
#define VerticalForce                    RAM(0x0709)
#define VerticalForceDown                RAM(0x070A)
#define PlayerChangeSizeFlag             RAM(0x070B)
#define PlayerAnimTimerSet               RAM(0x070C)
#define PlayerAnimCtrl                   RAM(0x070D)
#define JumpspringAnimCtrl               RAM(0x070E)
#define FlagpoleCollisionYPos            RAM(0x070F)
#define PlayerEntranceCtrl               RAM(0x0710)
#define FireballThrowingTimer            RAM(0x0711)
#define DeathMusicLoaded                 RAM(0x0712)
#define FlagpoleSoundQueue               RAM(0x0713)
#define CrouchingFlag                    RAM(0x0714)
#define GameTimerSetting                 RAM(0x0715)
#define DisableCollisionDet              RAM(0x0716)
#define DemoAction                       RAM(0x0717)
#define DemoActionTimer                  RAM(0x0718)
#define PrimaryMsgCounter                RAM(0x0719)

#define ScreenEdge_PageLoc               RAMARRAY(0x071A, 2)
#define ScreenLeft_PageLoc               ScreenEdge_PageLoc[0]
#define ScreenRight_PageLoc              ScreenEdge_PageLoc[1]

#define ScreenEdge_X_Pos                 RAMARRAY(0x071C, 2)
#define ScreenLeft_X_Pos                 ScreenEdge_X_Pos[0]
#define ScreenRight_X_Pos                ScreenEdge_X_Pos[1]

#define ColumnSets                       RAM(0x071E)
#define AreaParserTaskNum                RAM(0x071F)
#define CurrentNTAddr_High               RAM(0x0720)
#define CurrentNTAddr_Low                RAM(0x0721)
#define ScrollLock                       RAM(0x0723)
#define CurrentPageLoc                   RAM(0x0725)
#define CurrentColumnPos                 RAM(0x0726)
#define TerrainControl                   RAM(0x0727)
#define BackloadingFlag                  RAM(0x0728)
#define BehindAreaParserFlag             RAM(0x0729)
#define AreaObjectPageLoc                RAM(0x072A)
#define AreaObjectPageSel                RAM(0x072B)
#define AreaDataOffset                   RAM(0x072C)
#define AreaObjOffsetBuffer              RAMARRAY(0x072D, 3)
#define AreaObjectLength                 RAMARRAY(0x0730, 3)
#define AreaStyle                        RAM(0x0733)
#define StaircaseControl                 RAM(0x0734)
#define AreaObjectHeight                 RAM(0x0735)
#define MushroomLedgeHalfLen             RAMARRAY(0x0736, 3)
#define EnemyDataOffset                  RAM(0x0739)
#define EnemyObjectPageLoc               RAM(0x073A)
#define EnemyObjectPageSel               RAM(0x073B)
#define ScreenRoutineTask                RAM(0x073C)
#define ScrollThirtyTwo                  RAM(0x073D)
#define HorizontalScroll                 RAM(0x073F)
#define VerticalScroll                   RAM(0x0740)
#define ForegroundScenery                RAM(0x0741)
#define BackgroundScenery                RAM(0x0742)
#define CloudTypeOverride                RAM(0x0743)
#define BackgroundColorCtrl              RAM(0x0744)
#define LoopCommand                      RAM(0x0745)
#define StarFlagTaskControl              RAM(0x0746)
#define TimerControl                     RAM(0x0747)
#define CoinTallyFor1Ups                 RAM(0x0748)
#define SecondaryMsgCounter              RAM(0x0749)
#define JoypadBitMask                    RAMARRAY(0x074A, 2)
#define AreaType                         RAM(0x074E)
#define AreaAddrsLOffset                 RAM(0x074F)
#define AreaPointer                      RAM(0x0750)
#define EntrancePage                     RAM(0x0751)
#define AltEntranceControl               RAM(0x0752)
#define CurrentPlayer                    RAM(0x0753)
#define PlayerSize                       RAM(0x0754)
#define Player_Pos_ForScroll             RAM(0x0755)
#define PlayerStatus                     RAM(0x0756)
#define FetchNewGameTimerFlag            RAM(0x0757)
#define JoypadOverride                   RAM(0x0758)
#define GameTimerExpiredFlag             RAM(0x0759)
#define NumberofLives                    RAM(0x075A)
#define HalfwayPage                      RAM(0x075B)
#define LevelNumber                      RAM(0x075C)
#define Hidden1UpFlag                    RAM(0x075D)
#define CoinTally                        RAM(0x075E)
#define WorldNumber                      RAM(0x075F)
#define AreaNumber                       RAM(0x0760)
#define ScrollFractional                 RAM(0x0768)
#define DisableIntermediate              RAM(0x0769)
#define PrimaryHardMode                  RAM(0x076A)
#define WorldSelectNumber                RAM(0x076B)
#define OperMode                         RAM(0x0770)
#define OperMode_Task                    RAM(0x0772)
#define VRAM_Buffer_AddrCtrl             RAM(0x0773)
#define DisableScreenFlag                RAM(0x0774)
#define ScrollAmount                     RAM(0x0775)
#define GamePauseStatus                  RAM(0x0776)
#define GamePauseTimer                   RAM(0x0777)
#define Mirror_PPU_CTRL_REG1             RAM(0x0778)
#define Mirror_PPU_CTRL_REG2             RAM(0x0779)
#define IntervalTimerControl             RAM(0x077F)

#define Timers                           RAMARRAY(0x0780, 36)
#define SelectTimer                      Timers[0]
#define PlayerAnimTimer                  Timers[1]
#define JumpSwimTimer                    Timers[2]
#define RunningTimer                     Timers[3]
#define BlockBounceTimer                 Timers[4]
#define SideCollisionTimer               Timers[5]
#define JumpspringTimer                  Timers[6]
#define GameTimerCtrlTimer               Timers[7]
#define ClimbSideTimer                   Timers[9]
#define EnemyFrameTimer                  (Timers + 10)      // note: this subarray has a length of 6
#define FrenzyEnemyTimer                 EnemyFrameTimer[5]
#define BowserFireBreathTimer            Timers[16]
#define StompTimer                       Timers[17]
#define AirBubbleTimer                   Timers[18]
#define UnusedTimer1                     Timers[19]
#define UnusedTimer2                     Timers[20]
#define ScrollIntervalTimer              Timers[21]
#define EnemyIntervalTimer               (Timers + 22)      // note: this subarray has a length of 7
#define BrickCoinTimer                   Timers[29]
#define InjuryTimer                      Timers[30]
#define StarInvincibleTimer              Timers[31]
#define ScreenTimer                      Timers[32]
#define WorldEndTimer                    Timers[33]
#define DemoTimer                        Timers[34]
#define UnusedTimer3                     Timers[35]

#define PseudoRandomBitReg               RAMARRAY(0x07A7, 7)

#define SoundMemory                      RAMARRAY(0x07B0, 0x20)
#define MusicOffset_Noise                SoundMemory[0x00]
#define EventMusicBuffer                 SoundMemory[0x01]
#define PauseSoundBuffer                 SoundMemory[0x02]
#define Squ2_NoteLenBuffer               SoundMemory[0x03]
#define Squ2_NoteLenCounter              SoundMemory[0x04]
#define Squ2_EnvelopeDataCtrl            SoundMemory[0x05]
#define Squ1_NoteLenCounter              SoundMemory[0x06]
#define Squ1_EnvelopeDataCtrl            SoundMemory[0x07]
#define Tri_NoteLenBuffer                SoundMemory[0x08]
#define Tri_NoteLenCounter               SoundMemory[0x09]
#define Noise_BeatLenCounter             SoundMemory[0x0A]
#define Squ1_SfxLenCounter               SoundMemory[0x0B]
#define Squ2_SfxLenCounter               SoundMemory[0x0D]
#define Sfx_SecondaryCounter             SoundMemory[0x0E]
#define Noise_SfxLenCounter              SoundMemory[0x0F]
#define DAC_Counter                      SoundMemory[0x10]
#define NoiseDataLoopbackOfs             SoundMemory[0x11]
#define NoteLengthTblAdder               SoundMemory[0x14]
#define AreaMusicBuffer_Alt              SoundMemory[0x15]
#define PauseModeFlag                    SoundMemory[0x16]
#define GroundMusicHeaderOfs             SoundMemory[0x17]
#define AltRegContentFlag                SoundMemory[0x1A]

#define DisplayDigits                    RAMARRAY(0x07D7, 0x24)
#define TopScoreDisplay                  DisplayDigits
#define PlayerScoreDisplay               (DisplayDigits + 6)
#define ScoreAndCoinDisplay              (DisplayDigits + 6)

#define WarmBootValidation               RAM(0x07FF)
/* smb1 ----------------------- */
#define Sprite0HitDetectFlag             RAM(0x0722)
#define OffScr_NumberofLives             RAM(0x0761)
#define OffScr_HalfwayPage               RAM(0x0762)
#define OffScr_LevelNumber               RAM(0x0763)
#define OffScr_Hidden1UpFlag             RAM(0x0764)
#define OffScr_CoinTally                 RAM(0x0765)
#define OffScr_WorldNumber               RAM(0x0766)
#define OffScr_AreaNumber                RAM(0x0767)
#define NumberOfPlayers                  RAM(0x077A)
#define GameTimerDisplaySMB1             (DisplayDigits + 33)
#define WorldSelectEnableFlag            RAM(0x07FC)
#define ContinueWorld                    RAM(0x07FD)
/* smb2j ----------------------- */
#define FDSBIOS_IRQFlag                  RAM(0x0101)
#define IRQUpdateFlag                    RAM(0x0722)
#define MsgFractional                    RAM(0x0749)
#define EndControlCntr                   RAM(0x0761)
#define BlueColorOfs                     RAM(0x0762)
#define BlueDelayFlag                    RAM(0x0763)
#define MushroomRetDelay                 RAM(0x0764)
#define NameTableSelect                  RAM(0x077A)
#define IRQAckFlag                       RAM(0x077B)
#define CoinDisplay                      (DisplayDigits + 16)
#define GameTimerDisplaySMB2J            (DisplayDigits + 21)
#define FantasyW9MsgFlag                 RAM(0x07F5)
#define FlagpoleMusicFlag                RAM(0x07F6)
#define FileListNumber                   RAM(0x07F7)
#define ContinueMenuSelect               RAM(0x07F8)
#define WindFlag                         RAM(0x07F9)
#define CompletedWorlds                  RAM(0x07FA)
#define HardWorldFlag                    RAM(0x07FB)
#define DiskIOTask                       RAM(0x07FC)
#define NotColdFlag                      RAM(0x07FD)

#endif
