#ifndef SMBCORE_SMB2JROMARRAYS_H
#define SMBCORE_SMB2JROMARRAYS_H

#define VRAM_AddrTable                   RAMARRAY(0x6060, 62)
#define VRAM_Buffer_Offset               RAMARRAY(0x609E, 2)
#define WorldBits                        RAMARRAY(0x62F7, 8)
#define FloateyNumTileData               RAMARRAY(0x63FD, 24)
#define ScoreUpdateData                  RAMARRAY(0x6415, 12)
#define AreaPalette                      RAMARRAY(0x651B, 4)
#define BGColorCtrl_Addr                 RAMARRAY(0x652B, 4)
#define BackgroundColors                 RAMARRAY(0x652F, 8)
#define PlayerColors                     RAMARRAY(0x6537, 8)
#define TopStatusBarLine                 RAMARRAY(0x6672, 39)
#define WorldLivesDisplay                RAMARRAY(0x6699, 31)
#define TimeUp                           RAMARRAY(0x66B8, 11)
#define GameOver                         RAMARRAY(0x66C3, 36)
#define WarpZone                         RAMARRAY(0x66E7, 37)
#define WarpZoneNumbers                  RAMARRAY(0x670C, 11)
#define GameTextOffsets                  RAMARRAY(0x6717, 4)
#define ColorRotatePalette               RAMARRAY(0x68A0, 6)
#define BlankPalette                     RAMARRAY(0x68A6, 8)
#define Palette3Data                     RAMARRAY(0x68AE, 16)
#define BlockGfxData                     RAMARRAY(0x6916, 20)
#define MetatileGraphics_Low             RAMARRAY(0x69E5, 4)
#define MetatileGraphics_High            RAMARRAY(0x69E9, 4)
#define Palette0_MTiles                  RAMARRAY(0x69ED, 144)
#define Palette1_MTiles                  RAMARRAY(0x6A7D, 192)
#define Palette2_MTiles                  RAMARRAY(0x6B3D, 52)
#define Palette3_MTiles                  RAMARRAY(0x6B71, 28)
#define WaterPaletteData                 RAMARRAY(0x6B8D, 36)
#define GroundPaletteData                RAMARRAY(0x6BB1, 36)
#define UndergroundPaletteData           RAMARRAY(0x6BD5, 36)
#define CastlePaletteData                RAMARRAY(0x6BF9, 36)
#define DaySnowPaletteData               RAMARRAY(0x6C1D, 8)
#define NightSnowPaletteData             RAMARRAY(0x6C25, 8)
#define MushroomPaletteData              RAMARRAY(0x6C2D, 8)
#define BowserPaletteData                RAMARRAY(0x6C35, 8)
#define ThankYouMessage                  RAMARRAY(0x6C3D, 20)
#define MushroomRetainerMsg              RAMARRAY(0x6C51, 44)
#define JumpEngine                       RAMARRAY(0x6C7D, 21)
#define StatusBarData                    RAMARRAY(0x6D6D, 8)
#define StatusBarOffset                  RAMARRAY(0x6D75, 4)
#define DefaultSprOffsets                RAMARRAY(0x6E2A, 15)
#define MusicSelectData                  RAMARRAY(0x6F27, 6)
#define PlayerStarting_X_Pos             RAMARRAY(0x6F56, 4)
#define AltYPosOffset                    RAMARRAY(0x6F5A, 2)
#define PlayerStarting_Y_Pos             RAMARRAY(0x6F5C, 9)
#define PlayerBGPriorityData             RAMARRAY(0x6F65, 8)
#define GameTimerData                    RAMARRAY(0x6F6D, 4)
#define HalfwayPageNybbles               RAMARRAY(0x6FFD, 18)
#define BSceneDataOffsets                RAMARRAY(0x7108, 3)
#define BackSceneryData                  RAMARRAY(0x710B, 144)
#define BackSceneryMetatiles             RAMARRAY(0x719B, 36)
#define FSceneDataOffsets                RAMARRAY(0x71BF, 3)
#define ForeSceneryData                  RAMARRAY(0x71C2, 39)
#define TerrainMetatiles                 RAMARRAY(0x71E9, 4)
#define TerrainRenderBits                RAMARRAY(0x71ED, 32)
#define BlockBuffLowBounds               RAMARRAY(0x7315, 4)
#define FrenzyIDData                     RAMARRAY(0x757F, 3)
#define PulleyRopeMetatiles              RAMARRAY(0x7603, 3)
#define CastleMetatiles                  RAMARRAY(0x761B, 55)
#define SidePipeShaftData                RAMARRAY(0x76EB, 4)
#define SidePipeTopPart                  RAMARRAY(0x76EF, 4)
#define SidePipeBottomPart               RAMARRAY(0x76F3, 4)
#define VerticalPipeData                 RAMARRAY(0x7729, 8)
#define CoinMetatileData                 RAMARRAY(0x7835, 4)
#define C_ObjectRow                      RAMARRAY(0x7842, 3)
#define C_ObjectMetatile                 RAMARRAY(0x7845, 3)
#define SolidBlockMetatiles              RAMARRAY(0x786C, 4)
#define BrickMetatiles                   RAMARRAY(0x7870, 5)
#define StaircaseHeightData              RAMARRAY(0x78EC, 9)
#define StaircaseRowData                 RAMARRAY(0x78F5, 9)
#define HoleMetatiles                    RAMARRAY(0x7986, 4)
#define BlockBufferAddr                  RAMARRAY(0x7A1E, 4)
#define X_SubtracterData                 RAMARRAY(0x7B8C, 2)
#define OffscrJoypadBitsData             RAMARRAY(0x7B8E, 2)
#define ClimbAdderLow                    RAMARRAY(0x7F33, 4)
#define ClimbAdderHigh                   RAMARRAY(0x7F37, 4)
#define JumpMForceData                   RAMARRAY(0x7F90, 7)
#define FallMForceData                   RAMARRAY(0x7F97, 7)
#define FrictionData                     RAMARRAY(0x7F9E, 3)
#define PlayerYSpdData                   RAMARRAY(0x7FA1, 7)
#define InitMForceData                   RAMARRAY(0x7FA8, 7)
#define MaxLeftXSpdData                  RAMARRAY(0x7FAF, 3)
#define MaxRightXSpdData                 RAMARRAY(0x7FB2, 4)
#define Climb_Y_SpeedData                RAMARRAY(0x7FB6, 3)
#define Climb_Y_MForceData               RAMARRAY(0x7FB9, 3)
#define PlayerAnimTmrData                RAMARRAY(0x80F8, 3)
#define FireballXSpdData                 RAMARRAY(0x81F3, 2)
#define Bubble_MForceData                RAMARRAY(0x82B7, 2)
#define BubbleTimerData                  RAMARRAY(0x82B9, 2)
#define FlagpoleScoreMods                RAMARRAY(0x83B4, 5)
#define FlagpoleScoreDigits              RAMARRAY(0x83B9, 5)
#define Jumpspring_Y_PosData             RAMARRAY(0x842D, 4)
#define VineHeightData                   RAMARRAY(0x84D5, 2)
#define CannonBitmasks                   RAMARRAY(0x8585, 2)
#define BulletBillXSpdData               RAMARRAY(0x85FC, 2)
#define HammerEnemyOfsData               RAMARRAY(0x8654, 9)
#define HammerXSpdData                   RAMARRAY(0x865D, 2)
#define BlockYPosAdderData               RAMARRAY(0x88AC, 2)
#define BrickQBlockMetatiles             RAMARRAY(0x89B4, 19)
#define MaxSpdBlockData                  RAMARRAY(0x8B70, 2)
#define ResidualGravityCode              RAMARRAY(0x8B72, 3)
#define LoopCmdWorldNumber               RAMARRAY(0x8C47, 12)
#define LoopCmdPageNumber                RAMARRAY(0x8C53, 12)
#define LoopCmdYPosition                 RAMARRAY(0x8C5F, 12)
#define MultiLoopCount                   RAMARRAY(0x8C6B, 12)
#define NormalXSpdData                   RAMARRAY(0x8EF0, 2)
#define HBroWalkingTimerData             RAMARRAY(0x8F0A, 2)
#define PRDiffAdjustData                 RAMARRAY(0x8F83, 12)
#define FirebarSpinSpdData               RAMARRAY(0x9048, 5)
#define FirebarSpinDirData               RAMARRAY(0x904D, 5)
#define FlyCCXPositionData               RAMARRAY(0x9081, 16)
#define FlyCCXSpeedData                  RAMARRAY(0x9091, 12)
#define FlyCCTimerData                   RAMARRAY(0x909D, 4)
#define FlameYPosData                    RAMARRAY(0x91AE, 4)
#define FlameYMFAdderData                RAMARRAY(0x91B2, 2)
#define FireworksXPosData                RAMARRAY(0x9242, 6)
#define FireworksYPosData                RAMARRAY(0x9248, 6)
#define Bitmasks                         RAMARRAY(0x929B, 8)
#define Enemy17YPosData                  RAMARRAY(0x92A3, 8)
#define SwimCC_IDData                    RAMARRAY(0x92AB, 2)
#define PlatPosDataLow                   RAMARRAY(0x94A0, 3)
#define PlatPosDataHigh                  RAMARRAY(0x94A3, 3)
#define HammerThrowTmrData               RAMARRAY(0x9603, 2)
#define XSpeedAdderData                  RAMARRAY(0x9605, 4)
#define RevivedXSpeed                    RAMARRAY(0x9609, 4)
#define HammerBroJumpLData               RAMARRAY(0x9645, 2)
#define BlooberBitmasks                  RAMARRAY(0x97BC, 2)
#define SwimCCXMoveData                  RAMARRAY(0x987B, 4)
#define FirebarPosLookupTbl              RAMARRAY(0x98FC, 99)
#define FirebarMirrorData                RAMARRAY(0x995F, 4)
#define FirebarTblOffsets                RAMARRAY(0x9963, 12)
#define FirebarYPos                      RAMARRAY(0x996F, 2)
#define PRandomSubtracter                RAMARRAY(0x9B0A, 5)
#define FlyCCBPriority                   RAMARRAY(0x9B0F, 5)
#define LakituDiffAdj                    RAMARRAY(0x9B5A, 3)
#define BridgeCollapseData               RAMARRAY(0x9C12, 15)
#define PRandomRange                     RAMARRAY(0x9C96, 4)
#define FlameTimerData                   RAMARRAY(0x9E06, 8)
#define StarFlagYPosAdder                RAMARRAY(0x9F02, 4)
#define StarFlagXPosAdder                RAMARRAY(0x9F06, 4)
#define StarFlagTileData                 RAMARRAY(0x9F0A, 4)
#define BowserIdentities                 RAMARRAY(0xA376, 9)
#define ResidualXSpdData                 RAMARRAY(0xA4A5, 2)
#define KickedShellXSpdData              RAMARRAY(0xA4A7, 2)
#define DemotedKoopaXSpdData             RAMARRAY(0xA4A9, 2)
#define KickedShellPtsData               RAMARRAY(0xA4EA, 3)
#define StompedEnemyPtsData              RAMARRAY(0xA5C3, 4)
#define RevivalRateData                  RAMARRAY(0xA62F, 2)
#define SetBitsMask                      RAMARRAY(0xA68E, 7)
#define ClearBitsMask                    RAMARRAY(0xA695, 7)
#define PlayerPosSPlatData               RAMARRAY(0xA88C, 2)
#define PlayerBGUpperExtent              RAMARRAY(0xA8D0, 2)
#define AreaChangeTimerData              RAMARRAY(0xAA71, 2)
#define ClimbXPosAdder                   RAMARRAY(0xAA96, 2)
#define ClimbPLocAdder                   RAMARRAY(0xAA98, 2)
#define FlagpoleYPosData                 RAMARRAY(0xAA9A, 5)
#define SolidMTileUpperExt               RAMARRAY(0xAC14, 4)
#define ClimbMTileUpperExt               RAMARRAY(0xAC1F, 4)
#define EnemyBGCStateData                RAMARRAY(0xAC42, 6)
#define EnemyBGCXSpdData                 RAMARRAY(0xAC48, 2)
#define BoundBoxCtrlData                 RAMARRAY(0xAE9B, 48)
#define ResidualMiscObjectCode           RAMARRAY(0xB030, 10)
#define BlockBufferAdderData             RAMARRAY(0xB04B, 3)
#define BlockBuffer_X_Adder              RAMARRAY(0xB04E, 28)
#define BlockBuffer_Y_Adder              RAMARRAY(0xB06A, 28)
#define VineYPosAdder                    RAMARRAY(0xB0D7, 2)
#define FirstSprXPos                     RAMARRAY(0xB164, 4)
#define FirstSprYPos                     RAMARRAY(0xB168, 4)
#define SecondSprXPos                    RAMARRAY(0xB16C, 4)
#define SecondSprYPos                    RAMARRAY(0xB170, 4)
#define FirstSprTilenum                  RAMARRAY(0xB174, 4)
#define SecondSprTilenum                 RAMARRAY(0xB178, 4)
#define HammerSprAttrib                  RAMARRAY(0xB17C, 4)
#define FlagpoleScoreNumTiles            RAMARRAY(0xB1E5, 12)
#define JumpingCoinTiles                 RAMARRAY(0xB328, 4)
#define PowerUpGfxTable                  RAMARRAY(0xB364, 20)
#define PowerUpAttributes                RAMARRAY(0xB378, 5)
#define EnemyGraphicsTable               RAMARRAY(0xB3ED, 258)
#define EnemyGfxTableOffsets             RAMARRAY(0xB4EF, 27)
#define EnemyAttributeData               RAMARRAY(0xB50A, 27)
#define EnemyAnimTimingBMask             RAMARRAY(0xB525, 2)
#define JumpspringFrameOffsets           RAMARRAY(0xB527, 5)
#define DefaultBlockObjTiles             RAMARRAY(0xB8A8, 4)
#define ExplosionTiles                   RAMARRAY(0xB9E1, 3)
#define PlayerGfxTblOffsets              RAMARRAY(0xBAE2, 16)
#define PlayerGraphicsTable              RAMARRAY(0xBAF2, 208)
#define SwimKickTileNum                  RAMARRAY(0xBBC2, 2)
#define IntermediatePlayerData           RAMARRAY(0xBC79, 6)
#define ChangeSizeOffsetAdder            RAMARRAY(0xBD81, 20)
#define ObjOffsetData                    RAMARRAY(0xBE8A, 3)
#define XOffscreenBitsData               RAMARRAY(0xBEC8, 16)
#define DefaultXOnscreenOfs              RAMARRAY(0xBED8, 3)
#define YOffscreenBitsData               RAMARRAY(0xBF10, 9)
#define DefaultYOnscreenOfs              RAMARRAY(0xBF19, 3)
#define HighPosUnitData                  RAMARRAY(0xBF1C, 2)
#define DiskIDString                     RAMARRAY(0xC0D2, 10)
#define FileListAddrLow                  RAMARRAY(0xC0DC, 4)
#define FileListAddrHigh                 RAMARRAY(0xC0E0, 4)
#define World14List                      RAMARRAY(0xC0E4, 4)
#define World58List                      RAMARRAY(0xC0E8, 2)
#define EndingList                       RAMARRAY(0xC0EA, 4)
#define WorldADList                      RAMARRAY(0xC0EE, 2)
#define FileCount                        RAMARRAY(0xC0F0, 4)
#define DiskScreenPalette                RAMARRAY(0xC10B, 8)
#define DiskErrorMainMsg                 RAMARRAY(0xC149, 21)
#define DiskErrorMsgOffsets              RAMARRAY(0xC15E, 4)
#define DiskErrorMsgs                    RAMARRAY(0xC162, 32)
#define GameOverCursorData               RAMARRAY(0xC1BD, 3)
#define GameOverCursorY                  RAMARRAY(0xC1C0, 2)
#define JumpFrictionData                 RAMARRAY(0xC21F, 34)
#define WorldAddrOffsets                 RAMARRAY(0xC357, 9)
#define AreaDataOfsLoopback              RAMARRAY(0xC388, 12)
#define EnemyAddrHOffsets                RAMARRAY(0xC394, 4)
#define EnemyDataAddrs                   RAMARRAY(0xC398, 104)
#define AreaDataHOffsets                 RAMARRAY(0xC400, 4)
#define AreaDataAddrs                    RAMARRAY(0xC404, 106)
#define MenuCursorTemplate               RAMARRAY(0xC511, 7)
#define MenuCursorTiles                  RAMARRAY(0xC518, 3)
#define DemoActionData                   RAMARRAY(0xC530, 17)
#define DemoTimingData                   RAMARRAY(0xC541, 18)
#define PlayerNameData                   RAMARRAY(0xC5EB, 10)
#define PlayerPaletteData                RAMARRAY(0xC5F5, 8)
#define PlayerNameOffsets                RAMARRAY(0xC5FD, 2)
#define TitleScreenGfxData               RAMARRAY(0xC62B, 357)
#define GamesBeatenCount                 RAMARRAY(0xD29F, 1)
#define SwimStompEnvelopeData            RAMARRAY(0xD381, 14)
#define ExtraLifeFreqData                RAMARRAY(0xD4A4, 6)
#define PowerUpGrabFreqData              RAMARRAY(0xD4AA, 30)
#define PUp_VGrow_FreqData               RAMARRAY(0xD4C8, 32)
#define WindFreqEnvData                  RAMARRAY(0xD5FB, 24)
#define BrickShatterFreqData             RAMARRAY(0xD613, 16)
#define SkidSfxFreqData                  RAMARRAY(0xD623, 6)
#define MusicHeaderData                  RAMARRAY(0xD949, 49)
#define TimeRunningOutHdr                RAMARRAY(0xD97A, 5)
#define Star_CloudHdr                    RAMARRAY(0xD97F, 6)
#define EndOfLevelMusHdr                 RAMARRAY(0xD985, 5)
#define ResidualHeaderData               RAMARRAY(0xD98A, 5)
#define UndergroundMusHdr                RAMARRAY(0xD98F, 5)
#define SilenceHdr                       RAMARRAY(0xD994, 4)
#define CastleMusHdr                     RAMARRAY(0xD998, 5)
#define GameOverMusHdr                   RAMARRAY(0xD99D, 5)
#define WaterMusHdr                      RAMARRAY(0xD9A2, 6)
#define WinCastleMusHdr                  RAMARRAY(0xD9A8, 5)
#define GroundLevelPart1Hdr              RAMARRAY(0xD9AD, 6)
#define GroundLevelPart2AHdr             RAMARRAY(0xD9B3, 6)
#define GroundLevelPart2BHdr             RAMARRAY(0xD9B9, 6)
#define GroundLevelPart2CHdr             RAMARRAY(0xD9BF, 6)
#define GroundLevelPart3AHdr             RAMARRAY(0xD9C5, 6)
#define GroundLevelPart3BHdr             RAMARRAY(0xD9CB, 6)
#define GroundLevelLeadInHdr             RAMARRAY(0xD9D1, 6)
#define GroundLevelPart4AHdr             RAMARRAY(0xD9D7, 6)
#define GroundLevelPart4BHdr             RAMARRAY(0xD9DD, 6)
#define GroundLevelPart4CHdr             RAMARRAY(0xD9E3, 6)
#define DeathMusHdr                      RAMARRAY(0xD9E9, 6)
#define Star_CloudMData                  RAMARRAY(0xD9EF, 73)
#define GroundM_P1Data                   RAMARRAY(0xDA38, 27)
#define SilenceData                      RAMARRAY(0xDA53, 45)
#define GroundM_P2AData                  RAMARRAY(0xDA80, 44)
#define GroundM_P2BData                  RAMARRAY(0xDAAC, 40)
#define GroundM_P2CData                  RAMARRAY(0xDAD4, 37)
#define GroundM_P3AData                  RAMARRAY(0xDAF9, 25)
#define GroundM_P3BData                  RAMARRAY(0xDB12, 30)
#define GroundMLdInData                  RAMARRAY(0xDB30, 44)
#define GroundM_P4AData                  RAMARRAY(0xDB5C, 38)
#define GroundM_P4BData                  RAMARRAY(0xDB82, 39)
#define DeathMusData                     RAMARRAY(0xDBA9, 2)
#define GroundM_P4CData                  RAMARRAY(0xDBAB, 48)
#define CastleMusData                    RAMARRAY(0xDBDB, 161)
#define GameOverMusData                  RAMARRAY(0xDC7C, 45)
#define TimeRunOutMusData                RAMARRAY(0xDCA9, 62)
#define WinLevelMusData                  RAMARRAY(0xDCE7, 97)
#define UndergroundMusData               RAMARRAY(0xDD48, 65)
#define WaterMusData                     RAMARRAY(0xDD89, 255)
#define EndOfCastleMusData               RAMARRAY(0xDE88, 120)
#define FreqRegLookupTbl                 RAMARRAY(0xDF00, 102)
#define MusicLengthLookupTbl             RAMARRAY(0xDF66, 48)
#define EndOfCastleMusicEnvData          RAMARRAY(0xDF96, 4)
#define AreaMusicEnvData                 RAMARRAY(0xDF9A, 8)
#define WaterEventMusEnvData             RAMARRAY(0xDFA2, 40)
#define BowserFlameEnvData               RAMARRAY(0xDFCA, 32)
#define BrickShatterEnvData              RAMARRAY(0xDFEA, 16)
#define LeavesYPos                       RAMARRAY(0xC52C, 12)
#define LeavesXPos                       RAMARRAY(0xC538, 12)
#define LeavesTile                       RAMARRAY(0xC544, 12)
#define LeavesPosAdder                   RAMARRAY(0xC589, 24)
#define PrintWorld9Msgs                  RAMARRAY(0xC5D0, 25)
#define NoFW9                            RAMARRAY(0xC5E9, 8)
#define W9GameOver                       RAMARRAY(0xC5F1, 13)
#define BlueTransPalette                 RAMARRAY(0xC6A9, 20)
#define BlueTints                        RAMARRAY(0xC6BD, 4)
#define TwoBlankRows                     RAMARRAY(0xC6C1, 9)
#define SaveFileHeader                   RAMARRAY(0xC748, 17)
#define FlashMRSpriteDataOfs             RAMARRAY(0xC7A1, 6)
#define MRSpriteDataOfs                  RAMARRAY(0xC7A7, 7)
#define MRetainerYPos                    RAMARRAY(0xC7AE, 7)
#define MRetainerXPos                    RAMARRAY(0xC7B5, 8)
#define EndPlayerNameData                RAMARRAY(0xC84E, 10)
#define UnusedAttribData                 RAMARRAY(0xC876, 9)
#define FinalRoomPalette                 RAMARRAY(0xC87F, 20)
#define ThankYouMessageFinal             RAMARRAY(0xC893, 24)
#define PeaceIsPavedMsg                  RAMARRAY(0xC8AB, 22)
#define WithKingdomSavedMsg              RAMARRAY(0xC8C1, 22)
#define HurrahMsg                        RAMARRAY(0xC8D7, 20)
#define OurOnlyHeroMsg                   RAMARRAY(0xC8EB, 17)
#define ThisEndsYourTripMsg              RAMARRAY(0xC8FC, 23)
#define OfALongFriendshipMsg             RAMARRAY(0xC913, 24)
#define PointsAddedMsg                   RAMARRAY(0xC92B, 24)
#define ForEachPlayerLeftMsg             RAMARRAY(0xC943, 25)
#define PrincessPeachsRoom               RAMARRAY(0xC95C, 33)
#define FantasyWorld9Msg                 RAMARRAY(0xC97D, 67)
#define SuperPlayerMsg                   RAMARRAY(0xC9C0, 192)
#define ModTable1                        RAMARRAY(0xCF86, 16)
#define ModTable2                        RAMARRAY(0xCF96, 16)
#define MusicHeaderOffsetData            RAMARRAY(0xCFFA, 11)
#define AltSound_MusicHeaderData         RAMARRAY(0xD005, 8)
#define VictoryPart1BHdr                 RAMARRAY(0xD00D, 8)
#define VictoryPart2AHdr                 RAMARRAY(0xD015, 8)
#define VictoryPart2CHdr                 RAMARRAY(0xD01D, 8)
#define VictoryPart2DHdr                 RAMARRAY(0xD025, 8)
#define VictoryPart2BHdr                 RAMARRAY(0xD02D, 11)
#define VictoryM_P1AData                 RAMARRAY(0xD038, 79)
#define VictoryM_P1BData                 RAMARRAY(0xD087, 104)
#define VictoryM_P2AData                 RAMARRAY(0xD0EF, 23)
#define VictoryM_P2BData                 RAMARRAY(0xD106, 61)
#define VictoryM_P2CData                 RAMARRAY(0xD143, 104)
#define VictoryM_P2DData                 RAMARRAY(0xD1AB, 37)
#define WaveformData2                    RAMARRAY(0xD1D0, 32)
#define VolEnvData2                      RAMARRAY(0xD1F0, 4)
#define VolEnvData1                      RAMARRAY(0xD1F4, 12)
#define FDSFreqLookupTbl                 RAMARRAY(0xD200, 60)
#define VictoryMusEnvData                RAMARRAY(0xD23C, 16)
#define WaveformHeaderOffsets            RAMARRAY(0xD24C, 2)
#define Wave1Hdr                         RAMARRAY(0xD24E, 8)
#define Wave2Hdr                         RAMARRAY(0xD256, 9)
#define WaveformData1                    RAMARRAY(0xD25F, 32)
#define SweepModData1                    RAMARRAY(0xD27F, 10)
#define SweepModData2                    RAMARRAY(0xD289, 6)
#define AltSound_MusicLengthLookupTbl    RAMARRAY(0xD28F, 16)
#define AltHard_WorldAddrOffsets         RAMARRAY(0xC357, 9)
#define AltHard_EnemyAddrHOffsets        RAMARRAY(0xC372, 4)
#define AltHard_EnemyDataAddrs           RAMARRAY(0xC376, 42)
#define AltHard_AreaDataHOffsets         RAMARRAY(0xC3A0, 4)
#define AltHard_AreaDataAddrs            RAMARRAY(0xC3A4, 42)
#define AtoDHalfwayPages                 RAMARRAY(0xC3CE, 8)

#endif
