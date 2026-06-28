#ifndef SMBCORE_SMB2JROMARRAYS_H
#define SMBCORE_SMB2JROMARRAYS_H

#define WindFreqEnvData_IntendedLength 24
#define EndOfCastleMusicEnvData_IntendedLength 4
#define AreaMusicEnvData_IntendedLength 8
#define WaterEventMusicEnvData_IntendedLength 40

// The original game modifies an instruction opcode
#define PhysicsInstructionOpcode         RAM(0x80f1)

// The original game modifies an instruction operand
#define PiranhaPlantCompareOperand       RAM(0x9ffe)

// If in World 4+, or the hard worlds
#define PiranhaPlantHardMode (PiranhaPlantCompareOperand != 0x21)

// If using Mario's physics
#define MarioPhysics (PhysicsInstructionOpcode != 0x60)

// The original game modifies an instruction operand
#define SoundEngineJsrOperandLo       RAM(0x611d)
#define SoundEngineJsrOperandHi       RAM(0x611e)

#define AlternateSoundEngineEnabled (SoundEngineJsrOperandLo == 0x5f)

#define GamesBeatenCount                 RAM(0xD29F)

#define VRAM_AddrTable                   RAMARRAY_CONST(0x6060, 62)

// GameText aliases some other labels, referenced in by GameTextOffsets
// GameTextOffsets contains 4 entries. WarpZone(Numbers) are referenced explicitly.
#define GameText                         RAMARRAY_CONST(0x6672, 39+31+11+36)
// TopStatusBarLine is mutable because the names are patched in PatchPlayerNamePal
#define TopStatusBarLine                 RAMARRAY(0x6672, 39)

#define WarpZone                         RAMARRAY_CONST(0x66E7, 37)
#define WarpZoneNumbers                  RAMARRAY_CONST(0x670C, 11)
#define GameTextOffsets                  RAMARRAY_CONST(0x6717, 4)

#define MetatileGraphics_Low             RAMARRAY_CONST(0x69E5, 4)
#define MetatileGraphics_High            RAMARRAY_CONST(0x69E9, 4)
#define ThankYouMessage                  RAMARRAY(0x6C3D, 20)

#define HalfwayPageNybbles               RAMARRAY(0x6FFD, 18)
#define StaircaseHeightData              RAMARRAY_CONST(0x78EC, 9)
#define StaircaseRowData                 RAMARRAY_CONST(0x78F5, 9)

#define LoopCmdWorldNumber               RAMARRAY_CONST(0x8C47, 12)
#define LoopCmdPageNumber                RAMARRAY_CONST(0x8C53, 12)
#define LoopCmdYPosition                 RAMARRAY_CONST(0x8C5F, 12)
#define MultiLoopCount                   RAMARRAY_CONST(0x8C6B, 12)
#define FlameYPosData                    RAMARRAY_CONST(0x91AE, 4)

#define BowserIdentities                 RAMARRAY_CONST(0xA376, 9)

#define EnemyGraphicsTable               RAMARRAY_CONST(0xB3ED, 258)
#define PlayerGfxTblOffsets              RAMARRAY_CONST(0xBAE2, 16)
#define PlayerGraphicsTable              RAMARRAY_CONST(0xBAF2, 208)
#define FileCount                        RAMARRAY_CONST(0xC0F0, 4)
#define DiskErrorMainMsg                 RAMARRAY(0xC149, 21)
#define DiskErrorMsgOffsets              RAMARRAY_CONST(0xC15E, 4)
#define DiskErrorMsgs                    RAMARRAY_CONST(0xC162, 32)

#define WorldAddrOffsets                 RAMARRAY_CONST(0xC357, 9)
#define AreaDataOfsLoopback              RAMARRAY_CONST(0xC388, 12)
#define EnemyAddrHOffsets                RAMARRAY_CONST(0xC394, 4)
#define EnemyDataAddrs                   RAMARRAY_CONST(0xC398, 104)
#define AreaDataHOffsets                 RAMARRAY_CONST(0xC400, 4)
#define AreaDataAddrs                    RAMARRAY_CONST(0xC404, 106)
#define MenuCursorTemplate               RAMARRAY(0xC511, 7)
#define MenuCursorTiles                  RAMARRAY_CONST(0xC518, 3)
#define DemoActionData                   RAMARRAY_CONST(0xC530, 17)
#define DemoTimingData                   RAMARRAY_CONST(0xC541, 18)
#define PlayerNameMario                  RAMARRAY_CONST(0xC5EB, 5)
#define PlayerNameLuigi                  RAMARRAY_CONST(0xC5F0, 5)
#define TitleScreenGfxData               RAMARRAY(0xC62B, 357)
#define SwimStompEnvelopeData            RAMARRAY_CONST(0xD381, 14)
#define ExtraLifeFreqData                RAMARRAY_CONST(0xD4A4, 6)
#define PowerUpGrabFreqData              RAMARRAY_CONST(0xD4AA, 30)
#define PUp_VGrow_FreqData               RAMARRAY_CONST(0xD4C8, 32)
#define WindFreqEnvData                  RAMARRAY_CONST(0xD5FB, WindFreqEnvData_IntendedLength+1)
#define BrickShatterFreqData             RAMARRAY_CONST(0xD613, 16)
#define SkidSfxFreqData                  RAMARRAY_CONST(0xD623, 6)

#define MusicHeaderData                  RAMARRAY_CONST(0xD949, 0xD9EF - 0xD949)

#define FreqRegLookupTbl                 RAMARRAY_CONST(0xDF00, 102)
#define MusicLengthLookupTbl             RAMARRAY_CONST(0xDF66, 48)

#define EndOfCastleMusicEnvData          RAMARRAY_CONST(0xDF96, EndOfCastleMusicEnvData_IntendedLength+1)
#define AreaMusicEnvData                 RAMARRAY_CONST(0xDF9A, AreaMusicEnvData_IntendedLength+1)
#define WaterEventMusEnvData             RAMARRAY_CONST(0xDFA2, WaterEventMusicEnvData_IntendedLength+1)

#define BowserFlameEnvData_Minus1        RAMARRAY_CONST(0xDFCA-1, 32+1)
#define BrickShatterEnvData              RAMARRAY_CONST(0xDFEA, 16)


#define LeavesYPos                       RAMARRAY(0xC52C, 12)
#define LeavesXPos                       RAMARRAY(0xC538, 12)
#define FlashMRSpriteDataOfs             RAMARRAY_CONST(0xC7A1, 6)
#define MRSpriteDataOfs                  RAMARRAY_CONST(0xC7A7, 7)
#define MRetainerYPos                    RAMARRAY_CONST(0xC7AE, 7)
#define MRetainerXPos                    RAMARRAY_CONST(0xC7B5, 8)
#define EndPlayerName_Mario              RAMARRAY_CONST(0xC84E, 5)
#define EndPlayerName_Luigi              RAMARRAY_CONST(0xC853, 5)
// UNUSED: #define FinalRoomPalette                 RAMARRAY_CONST(0xC87F, 20)
#define ThankYouMessageFinal             RAMARRAY(0xC893, 24)
// UNUSED: #define PeaceIsPavedMsg                  RAMARRAY_CONST(0xC8AB, 22)
// UNUSED: #define WithKingdomSavedMsg              RAMARRAY_CONST(0xC8C1, 22)
#define HurrahMsg                        RAMARRAY(0xC8D7, 20)
// UNUSED: #define OurOnlyHeroMsg                   RAMARRAY_CONST(0xC8EB, 17)
// UNUSED: #define ThisEndsYourTripMsg              RAMARRAY_CONST(0xC8FC, 23)
// UNUSED: #define OfALongFriendshipMsg             RAMARRAY_CONST(0xC913, 24)
// UNUSED: #define PointsAddedMsg                   RAMARRAY_CONST(0xC92B, 24)
// UNUSED: #define ForEachPlayerLeftMsg             RAMARRAY_CONST(0xC943, 25)
// UNUSED: #define PrincessPeachsRoom               RAMARRAY_CONST(0xC95C, 33)
// UNUSED: #define FantasyWorld9Msg                 RAMARRAY_CONST(0xC97D, 67)
// UNUSED: #define SuperPlayerMsg                   RAMARRAY_CONST(0xC9C0, 192)
// UNUSED: #define ModTable1                        RAMARRAY_CONST(0xCF86, 16)
// UNUSED: #define ModTable2                        RAMARRAY_CONST(0xCF96, 16)
// UNUSED: #define MusicHeaderOffsetData            RAMARRAY_CONST(0xCFFA, 11)
// UNUSED: #define AltSound_MusicHeaderData         RAMARRAY_CONST(0xD005, 8)
// UNUSED: #define VictoryPart1BHdr                 RAMARRAY_CONST(0xD00D, 8)
// UNUSED: #define VictoryPart2AHdr                 RAMARRAY_CONST(0xD015, 8)
// UNUSED: #define VictoryPart2CHdr                 RAMARRAY_CONST(0xD01D, 8)
// UNUSED: #define VictoryPart2DHdr                 RAMARRAY_CONST(0xD025, 8)
// UNUSED: #define VictoryPart2BHdr                 RAMARRAY_CONST(0xD02D, 11)
// UNUSED: #define VictoryM_P1AData                 RAMARRAY_CONST(0xD038, 79)
// UNUSED: #define VictoryM_P1BData                 RAMARRAY_CONST(0xD087, 104)
// UNUSED: #define VictoryM_P2AData                 RAMARRAY_CONST(0xD0EF, 23)
// UNUSED: #define VictoryM_P2BData                 RAMARRAY_CONST(0xD106, 61)
// UNUSED: #define VictoryM_P2CData                 RAMARRAY_CONST(0xD143, 104)
// UNUSED: #define VictoryM_P2DData                 RAMARRAY_CONST(0xD1AB, 37)
// UNUSED: #define WaveformData2                    RAMARRAY_CONST(0xD1D0, 32)
// UNUSED: #define VolEnvData2                      RAMARRAY_CONST(0xD1F0, 4)
// UNUSED: #define VolEnvData1                      RAMARRAY_CONST(0xD1F4, 12)
// UNUSED: #define FDSFreqLookupTbl                 RAMARRAY_CONST(0xD200, 60)
// UNUSED: #define VictoryMusEnvData                RAMARRAY_CONST(0xD23C, 16)
// UNUSED: #define WaveformHeaderOffsets            RAMARRAY_CONST(0xD24C, 2)
// UNUSED: #define Wave1Hdr                         RAMARRAY_CONST(0xD24E, 8)
// UNUSED: #define Wave2Hdr                         RAMARRAY_CONST(0xD256, 9)
// UNUSED: #define WaveformData1                    RAMARRAY_CONST(0xD25F, 32)
// UNUSED: #define SweepModData1                    RAMARRAY_CONST(0xD27F, 10)
// UNUSED: #define SweepModData2                    RAMARRAY_CONST(0xD289, 6)
// UNUSED: #define AltSound_MusicLengthLookupTbl    RAMARRAY_CONST(0xD28F, 16)
// UNUSED: #define AltHard_WorldAddrOffsets         RAMARRAY_CONST(0xC357, 9)
#define AltHard_EnemyAddrHOffsets        RAMARRAY_CONST(0xC372, 4)
#define AltHard_EnemyDataAddrs           RAMARRAY_CONST(0xC376, 42)
#define AltHard_AreaDataHOffsets         RAMARRAY_CONST(0xC3A0, 4)
#define AltHard_AreaDataAddrs            RAMARRAY_CONST(0xC3A4, 42)
#define AtoDHalfwayPages                 RAMARRAY_CONST(0xC3CE, 8)


#endif

