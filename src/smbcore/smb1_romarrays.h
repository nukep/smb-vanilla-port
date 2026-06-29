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
#define StaircaseHeightData              RAMARRAY_CONST(0x9AA5, 9)
#define StaircaseRowData                 RAMARRAY_CONST(0x9AAE, 9)
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

#define LoopCmdWorldNumber               RAMARRAY_CONST(0xC06B, 11)
#define LoopCmdPageNumber                RAMARRAY_CONST(0xC076, 11)
#define LoopCmdYPosition                 RAMARRAY_CONST(0xC081, 11)
#define FlameYPosData                    RAMARRAY_CONST(0xC59D, 4)

#define BowserIdentities                 RAMARRAY_CONST(0xD736, 8)

#define EnemyGraphicsTable               RAMARRAY_CONST(0xE73E, 258)
#define EnemyAttributeData               RAMARRAY_CONST(0xE85B, 27)
#define PlayerGfxTblOffsets              RAMARRAY_CONST(0xEE07, 16)
#define PlayerGraphicsTable              RAMARRAY_CONST(0xEE17, 208)
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

