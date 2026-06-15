#ifndef SMBCORE_SMB1ROMARRAYS_H
#define SMBCORE_SMB1ROMARRAYS_H

#define EndOfCastleMusicEnvData_IntendedLength 4
#define AreaMusicEnvData_IntendedLength 8
#define WaterEventMusicEnvData_IntendedLength 40

// This is a constant in SMB1, but changes in SMB2J. This definition is here for symmetry with smb2j.
#define PiranhaPlantCompareOperand       0x21

// If using Mario's physics
#define MarioPhysics true

#define VRAM_AddrTable_Low               RAMARRAY_CONST(0x805A, 19)
#define VRAM_AddrTable_High              RAMARRAY_CONST(0x806D, 19)
#define DemoActionData                   RAMARRAY_CONST(0x8340, 21)
#define DemoTimingData                   RAMARRAY_CONST(0x8355, 22)
#define GameText                         RAMARRAY_CONST(0x8752, 0x9B)
#define LuigiName                        RAMARRAY_CONST(0x87ED, 5)
#define WarpZoneNumbers                  RAMARRAY_CONST(0x87F2, 12)
#define GameTextOffsets                  RAMARRAY_CONST(0x87FE, 10)
#define MetatileGraphics_Low             RAMARRAY_CONST(0x8B08, 4)
#define MetatileGraphics_High            RAMARRAY_CONST(0x8B0C, 4)

#define HalfwayPageNybbles               RAMARRAY_CONST(0x91BD, 16)
#define BSceneDataOffsets                RAMARRAY_CONST(0x92F7, 3)
#define BackSceneryData                  RAMARRAY_CONST(0x92FA, 144)
#define BackSceneryMetatiles             RAMARRAY_CONST(0x938A, 36)
#define FSceneDataOffsets                RAMARRAY_CONST(0x93AE, 3)
#define ForeSceneryData                  RAMARRAY_CONST(0x93B1, 39)
#define TerrainMetatiles                 RAMARRAY_CONST(0x93D8, 4)
#define TerrainRenderBits                RAMARRAY_CONST(0x93DC, 32)
#define BlockBuffLowBounds               RAMARRAY_CONST(0x9504, 4)
#define FrenzyIDData                     RAMARRAY_CONST(0x9728, 3)
#define PulleyRopeMetatiles              RAMARRAY_CONST(0x97B7, 3)
#define CastleMetatiles                  RAMARRAY_CONST(0x97CF, 55)
#define SidePipeShaftData                RAMARRAY_CONST(0x989F, 4)
#define SidePipeTopPart                  RAMARRAY_CONST(0x98A3, 4)
#define SidePipeBottomPart               RAMARRAY_CONST(0x98A7, 4)
#define VerticalPipeData                 RAMARRAY_CONST(0x98DD, 8)
#define CoinMetatileData                 RAMARRAY_CONST(0x99EE, 4)
#define C_ObjectRow                      RAMARRAY_CONST(0x99FB, 3)
#define C_ObjectMetatile                 RAMARRAY_CONST(0x99FE, 3)
#define SolidBlockMetatiles              RAMARRAY_CONST(0x9A25, 4)
#define BrickMetatiles                   RAMARRAY_CONST(0x9A29, 5)
#define StaircaseHeightData              RAMARRAY_CONST(0x9AA5, 9)
#define StaircaseRowData                 RAMARRAY_CONST(0x9AAE, 9)
#define HoleMetatiles                    RAMARRAY_CONST(0x9B3D, 4)
#define AreaDataOfsLoopback              RAMARRAY_CONST(0x9BF8, 11)
#define WorldAddrOffsets                 RAMARRAY_CONST(0x9CB4, 8)
#define AreaAddrOffsets                  RAMARRAY_CONST(0x9CBC, 0x24)
#define EnemyAddrHOffsets                RAMARRAY_CONST(0x9CE0, 4)
#define EnemyDataAddrLow                 RAMARRAY_CONST(0x9CE4, 34)
#define EnemyDataAddrHigh                RAMARRAY_CONST(0x9D06, 34)
#define AreaDataHOffsets                 RAMARRAY_CONST(0x9D28, 4)
#define AreaDataAddrLow                  RAMARRAY_CONST(0x9D2C, 34)
#define AreaDataAddrHigh                 RAMARRAY_CONST(0x9D4E, 34)
#define Hidden1UpCoinAmts                RAMARRAY_CONST(0xB2C2, 8)
#define PlayerAnimTmrData                RAMARRAY_CONST(0xB58C, 3)

#define LoopCmdWorldNumber               RAMARRAY_CONST(0xC06B, 11)
#define LoopCmdPageNumber                RAMARRAY_CONST(0xC076, 11)
#define LoopCmdYPosition                 RAMARRAY_CONST(0xC081, 11)
#define FlameYPosData                    RAMARRAY_CONST(0xC59D, 4)

#define BowserIdentities                 RAMARRAY_CONST(0xD736, 8)

#define VineYPosAdder                    RAMARRAY_CONST(0xE433, 2)
#define EnemyGraphicsTable               RAMARRAY_CONST(0xE73E, 258)
#define EnemyGfxTableOffsets             RAMARRAY_CONST(0xE840, 27)
#define EnemyAttributeData               RAMARRAY_CONST(0xE85B, 27)
#define PlayerGfxTblOffsets              RAMARRAY_CONST(0xEE07, 16)
#define PlayerGraphicsTable              RAMARRAY_CONST(0xEE17, 208)
#define DefaultXOnscreenOfs              RAMARRAY_CONST(0xF1F3, 3)
#define DefaultYOnscreenOfs              RAMARRAY_CONST(0xF234, 3)
#define SwimStompEnvelopeData            RAMARRAY_CONST(0xF3B1, 14)
#define ExtraLifeFreqData                RAMARRAY_CONST(0xF4D4, 6)
#define PowerUpGrabFreqData              RAMARRAY_CONST(0xF4DA, 30)
#define PUp_VGrow_FreqData               RAMARRAY_CONST(0xF4F8, 32)
#define BrickShatterFreqData             RAMARRAY_CONST(0xF62B, 16)

#define MusicHeaderData                  RAMARRAY_CONST(0xF90D, 0xF9B8 - 0xF90D)
#define FreqRegLookupTbl                 RAMARRAY_CONST(0xFF00, 102)
#define MusicLengthLookupTbl             RAMARRAY_CONST(0xFF66, 48)

#define EndOfCastleMusicEnvData          RAMARRAY_CONST(0xFF96, EndOfCastleMusicEnvData_IntendedLength+1)
#define AreaMusicEnvData                 RAMARRAY_CONST(0xFF9A, AreaMusicEnvData_IntendedLength+1)
#define WaterEventMusEnvData             RAMARRAY_CONST(0xFFA2, WaterEventMusicEnvData_IntendedLength+1)

#define BowserFlameEnvData_Minus1        RAMARRAY_CONST(0xFFCA-1, 32+1)
#define BrickShatterEnvData              RAMARRAY_CONST(0xFFEA, 16)

#endif

