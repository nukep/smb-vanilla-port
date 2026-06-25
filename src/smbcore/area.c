#include "src/base.h"
#include "src/smbcore/tiles.h"
#include "types.h"
#include "vars.h"

#include "area.h"

#define NO_AVAIL_ENEMY_SLOT 5

static void RenderAreaGraphics(void);
static void RenderAttributeTables(void);
static void IncrementColumnPos(void);
static void AreaParserCore(void);
static void ProcessAreaData(void);
static bool DecodeAreaData(byte param_1, byte param_2);
static void AlterAreaAttributes(byte param_1);
static void ScrollLockObject_Warp(void);
static void ScrollLockObject(void);
static void AreaFrenzy(byte param_1);
static void TreeLedge(byte param_1);
static void NoUnder(byte param_1, byte param_2);
static void PulleyRopeObject(byte param_1);
static void CastleObject(byte param_1);
static void WaterPipe(byte param_1);
static void IntroPipe(byte param_1);
static void ExitPipe(byte param_1);
static void SetupPiranhaPlant(byte param_1, byte param_2, byte param_3);
static void VerticalPipe(byte param_1, bool decorative);
static struct_yr06r07 GetPipeHeight(byte param_1);
static byte FindEmptyEnemySlot(void);
static void Hole_Water(byte param_1);
static void QuestionBlockRow_High(byte param_1);
static void QuestionBlockRow_Low(byte param_1);
static void Bridge_High(byte param_1);
static void Bridge_Middle(byte param_1);
static void Bridge_Low(byte param_1);
static void FlagBalls_Residual(byte param_1);
static void FlagpoleObject(void);
static void EndlessRope(void);
static void BalancePlatRope(byte param_1);
static void RowOfCoins(byte param_1);
static void CastleBridgeObj(byte param_1, byte param_2);
static void AxeObj(byte param_1);
static void ChainObj(byte param_1);
static void EmptyBlock(byte param_1);
static void RowOfBricks(byte param_1);
static void RowOfSolidBlocks(byte param_1);
static void ColumnOfBricks(byte param_1);
static void ColumnOfSolidBlocks(byte param_1);
static void BulletBillCannon(byte param_1);
static void StaircaseObject(byte param_1);
static void Jumpspring(byte param_1);
static void Hidden1UpBlock(byte param_1, byte param_2);
static void QuestionBlock(byte param_1, byte param_2);
static void BrickWithCoins(byte param_1, byte param_2);
static void BrickWithItem(byte param_1, byte param_2);
static void Hole_Empty(byte param_1);
static void RenderUnderPart(byte param_1, byte param_2, byte param_3);
static struct_ycr07 ChkLrgObjLength(byte param_1);
static bool ChkLrgObjFixedLength(byte param_1, byte param_2);
static struct_yr07 GetLrgObjAttrib(byte param_1);
static byte GetAreaObjXPosition(void);
static byte GetAreaObjYPosition(byte param_1);

#ifdef SMB1_MODE
static void MushroomLedge(byte param_1);
#endif
#ifdef SMB2J_MODE
static void CloudLedge(byte param_1);
#endif

#ifdef SMB2J_MODE
static void WriteWarpZoneMessage(byte param_1);
static void UpsideDownPipe_High(byte param_1);
static void UpsideDownPipe_Low(byte param_1);
static void WindOn(void);
static void WindOff(void);
#endif

enum AreaParserTasks_jumptable_item {
  AREAPARSERTASKS_INCREMENTCOLUMNPOS_1,
  AREAPARSERTASKS_RENDERAREAGRAPHICS_1,
  AREAPARSERTASKS_RENDERAREAGRAPHICS_2,
  AREAPARSERTASKS_AREAPARSERCORE_1,
  AREAPARSERTASKS_INCREMENTCOLUMNPOS_2,
  AREAPARSERTASKS_RENDERAREAGRAPHICS_3,
  AREAPARSERTASKS_RENDERAREAGRAPHICS_4,
  AREAPARSERTASKS_AREAPARSERCORE_2,
};

enum DecodeAreaData_jumptable_item {
  DECODEAREADATA_VERTICALPIPE_1,
  DECODEAREADATA_AREASTYLEOBJECT,
  DECODEAREADATA_ROWOFBRICKS,
  DECODEAREADATA_ROWOFSOLIDBLOCKS,
  DECODEAREADATA_ROWOFCOINS,
  DECODEAREADATA_COLUMNOFBRICKS,
  DECODEAREADATA_COLUMNOFSOLIDBLOCKS,
  DECODEAREADATA_VERTICALPIPE_2,
  DECODEAREADATA_HOLE_EMPTY,
  DECODEAREADATA_PULLEYROPEOBJECT,
  DECODEAREADATA_BRIDGE_HIGH,
  DECODEAREADATA_BRIDGE_MIDDLE,
  DECODEAREADATA_BRIDGE_LOW,
  DECODEAREADATA_HOLE_WATER,
  DECODEAREADATA_QUESTIONBLOCKROW_HIGH,
  DECODEAREADATA_QUESTIONBLOCKROW_LOW,
  DECODEAREADATA_ENDLESSROPE,
  DECODEAREADATA_BALANCEPLATROPE,
  DECODEAREADATA_CASTLEOBJECT,
  DECODEAREADATA_STAIRCASEOBJECT,
  DECODEAREADATA_EXITPIPE,
  DECODEAREADATA_FLAGBALLS_RESIDUAL,
#ifdef SMB2J_MODE
  DECODEAREADATA_UPSIDEDOWNPIPE_HIGH,
  DECODEAREADATA_UPSIDEDOWNPIPE_LOW,
#endif
  DECODEAREADATA_QUESTIONBLOCK_1,
  DECODEAREADATA_QUESTIONBLOCK_2,
  DECODEAREADATA_QUESTIONBLOCK_3,
#ifdef SMB2J_MODE
  DECODEAREADATA_QUESTIONBLOCK_4,
#endif
  DECODEAREADATA_HIDDEN1UPBLOCK,
#ifdef SMB2J_MODE
  DECODEAREADATA_QUESTIONBLOCK_5,
  DECODEAREADATA_QUESTIONBLOCK_6,
#endif
  DECODEAREADATA_BRICKWITHITEM_1,
  DECODEAREADATA_BRICKWITHITEM_2,
  DECODEAREADATA_BRICKWITHITEM_3,
#ifdef SMB2J_MODE
  DECODEAREADATA_BRICKWITHITEM_5,
#endif
  DECODEAREADATA_BRICKWITHCOINS,
  DECODEAREADATA_BRICKWITHITEM_4,
  DECODEAREADATA_WATERPIPE,
  DECODEAREADATA_EMPTYBLOCK,
  DECODEAREADATA_JUMPSPRING,
  DECODEAREADATA_INTROPIPE,
  DECODEAREADATA_FLAGPOLEOBJECT,
  DECODEAREADATA_AXEOBJ,
  DECODEAREADATA_CHAINOBJ,
  DECODEAREADATA_CASTLEBRIDGEOBJ,
  DECODEAREADATA_SCROLLLOCKOBJECT_WARP,
  DECODEAREADATA_SCROLLLOCKOBJECT_1,
  DECODEAREADATA_SCROLLLOCKOBJECT_2,
  DECODEAREADATA_AREAFRENZY_1,
  DECODEAREADATA_AREAFRENZY_2,
  DECODEAREADATA_AREAFRENZY_3,
  DECODEAREADATA_NOOP,
#ifdef SMB2J_MODE
  DECODEAREADATA_WINDON,
  DECODEAREADATA_WINDOFF,
#endif
  DECODEAREADATA_ALTERAREAATTRIBUTES,
};

enum AreaStyleObject_jumptable_item {
  AREASTYLEOBJECT_TREELEDGE,
  AREASTYLEOBJECT_MUSHROOMLEDGE,
  AREASTYLEOBJECT_BULLETBILLCANNON,
};


// SMB:86e6
// SM2MAIN:6659
// Signature: [] -> []
void AreaParserTaskControl(void) {
  DisableScreenFlag += 1;
  do {
    AreaParserTaskHandler();
  } while (AreaParserTaskNum != 0);
  ColumnSets -= 1;
  if (ColumnSets >= 0x80) {
    ScreenRoutineTask += 1;
  }
  VRAM_Buffer_AddrCtrl = ADDRCTRL_VRAM_BUFFER2;
}


// SMB:88ae
// SM2MAIN:678b
// Signature: [] -> []
void RenderAreaGraphics(void) {
  const bool even_column = (CurrentColumnPos & 1) == 0;

  VRAM_Buffer2[VRAM_Buffer2_Offset + 0] = CurrentNTAddr_High;
  VRAM_Buffer2[VRAM_Buffer2_Offset + 1] = CurrentNTAddr_Low;
  VRAM_Buffer2[VRAM_Buffer2_Offset + 2] = DRAW_FLAG_VERTICAL | (13*2);

  for (int i = 0; i < 13; i++) {
    const byte mt = MetatileBuffer[i];
    const byte lo = MetatileGraphics_Low[mt >> 6];
    const byte hi = MetatileGraphics_High[mt >> 6];

    const u8 *data = rom_ptr((hi << 8) | lo);

    const byte bVar2 = (mt << 2) | ((AreaParserTaskNum & 1) ? 0 : 2);
    VRAM_Buffer2[VRAM_Buffer2_Offset + 3] = data[bVar2];
    VRAM_Buffer2[VRAM_Buffer2_Offset + 4] = data[bVar2 + 1];

    byte bVar8 = mt & 0xc0;
    const byte tmp1 = i/2;

    if ((i & 1) == 0) {
      bVar8 >>= 4;
    }

    if (even_column) {
      bVar8 >>= 2;
    }

    AttributeBuffer[tmp1] |= bVar8;
    VRAM_Buffer2_Offset += 2;
  }

  VRAM_Buffer2_Offset += 3;
  VRAM_Buffer2[VRAM_Buffer2_Offset] = 0;

  CurrentNTAddr_Low += 1;

  if ((CurrentNTAddr_Low & 0x1f) == 0) {
    CurrentNTAddr_Low = 0x80;
    CurrentNTAddr_High ^= 4;
  }

  VRAM_Buffer_AddrCtrl = ADDRCTRL_VRAM_BUFFER2;
}


// SMB:896a
// SM2MAIN:6847
// Signature: [] -> []
void RenderAttributeTables(void) {
  bool even_page = (CurrentNTAddr_High & 0x04) == 0;
  const byte nt_lo = (CurrentNTAddr_Low - 4) & 0x1f;
  if (nt_lo >= 32 - 4) {
    even_page = !even_page;
  }

  // NES note: this bit is unlikely to be set, because CurrentNTAddr_Low seems to always be a multiple of 4.
  // But this is what the original game does.
  const byte carry_bug = CurrentNTAddr_Low & 0x02 ? 1 : 0;

  const u16 attrtable = even_page ? 0x23c0 : 0x27c0;

  const u16 ppuaddr = (attrtable | (nt_lo >> 2)) + carry_bug;

  for (int i = 0; i < 7; i++) {
    VRAM_Buffer2[VRAM_Buffer2_Offset + 0] = ppuaddr >> 8;
    VRAM_Buffer2[VRAM_Buffer2_Offset + 1] = (ppuaddr & 0xff) + (i+1)*8;
    VRAM_Buffer2[VRAM_Buffer2_Offset + 2] = 1;
    VRAM_Buffer2[VRAM_Buffer2_Offset + 3] = AttributeBuffer[i];
    VRAM_Buffer2_Offset += 4;

    AttributeBuffer[i] = 0;
  }

  VRAM_Buffer2[VRAM_Buffer2_Offset] = 0;
  VRAM_Buffer_AddrCtrl = ADDRCTRL_VRAM_BUFFER2;
}


// SMB:92b0
// SM2MAIN:70c1
// Signature: [] -> []
void AreaParserTaskHandler(void) {
  if (AreaParserTaskNum == 0) {
    AreaParserTaskNum = 8;
  }

  switch (AreaParserTaskNum - 1) {
  case AREAPARSERTASKS_INCREMENTCOLUMNPOS_1:
  case AREAPARSERTASKS_INCREMENTCOLUMNPOS_2:
    IncrementColumnPos();
    break;

  case AREAPARSERTASKS_RENDERAREAGRAPHICS_1:
  case AREAPARSERTASKS_RENDERAREAGRAPHICS_2:
  case AREAPARSERTASKS_RENDERAREAGRAPHICS_3:
  case AREAPARSERTASKS_RENDERAREAGRAPHICS_4:
    RenderAreaGraphics();
    break;

  case AREAPARSERTASKS_AREAPARSERCORE_1:
  case AREAPARSERTASKS_AREAPARSERCORE_2:
    AreaParserCore();
    break;

  default:
    jmpengine_overflow(AreaParserTaskNum - 1);
  }

  AreaParserTaskNum -= 1;
  if (AreaParserTaskNum == 0) {
    RenderAttributeTables();
  }
}


// SMB:92db
// SM2MAIN:70ec
// Signature: [] -> []
void IncrementColumnPos(void) {
  CurrentColumnPos += 1;
  if ((CurrentColumnPos & 0xf) == 0) {
    CurrentPageLoc += 1;
    CurrentColumnPos = 0;
  }
  BlockBufferColumnPos = (BlockBufferColumnPos + 1) & 0x1f;
}


// SMB:93fc
// SM2MAIN:720d
// Signature: [] -> []
void AreaParserCore(void) {
  if (BackloadingFlag != 0) {
    ProcessAreaData();
  }

  for (int i = 0; i < 13; i++) {
    MetatileBuffer[i] = MT_0;
  }

  static const u8 backscenery_lookup[3][3][16] = {
    // clouds
    {
      { 0x93, 0x00, 0x00, 0x11, 0x12, 0x12, 0x13, 0x00,
        0x00, 0x51, 0x52, 0x53, 0x00, 0x00, 0x00, 0x00, },
      { 0x00, 0x00, 0x01, 0x02, 0x02, 0x03, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x91, 0x92, 0x93, 0x00, },
      { 0x00, 0x00, 0x00, 0x51, 0x52, 0x53, 0x41, 0x42,
        0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91, 0x92, },
    },

    // mountains and bushes
    {
      { 0x97, 0x87, 0x88, 0x89, 0x99, 0x00, 0x00, 0x00,
        0x11, 0x12, 0x13, 0xa4, 0xa5, 0xa5, 0xa5, 0xa6, },
      { 0x97, 0x98, 0x99, 0x01, 0x02, 0x03, 0x00, 0xa4,
        0xa5, 0xa6, 0x00, 0x11, 0x12, 0x12, 0x12, 0x13, },
      { 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x03,
        0x00, 0xa4, 0xa5, 0xa5, 0xa6, 0x00, 0x00, 0x00, },
    },

    // trees and fences
    {
      { 0x11, 0x12, 0x12, 0x13, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x9c, 0x00, 0x8b, 0xaa, 0xaa, },
      { 0xaa, 0xaa, 0x11, 0x12, 0x13, 0x8b, 0x00, 0x9c,
        0x9c, 0x00, 0x00, 0x01, 0x02, 0x03, 0x11, 0x12, },
      { 0x12, 0x13, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa,
        0x9c, 0xaa, 0x00, 0x8b, 0x00, 0x01, 0x02, 0x03, },
    }
  };

  static const u8 backscenery_metatiles[][3] = {
    // Cloud
    { MT_CLOUD_TL, MT_CLOUD_BL, MT_0 },
    { MT_CLOUD_TM, MT_CLOUD_BM, MT_0 },
    { MT_CLOUD_TR, MT_CLOUD_BR, MT_0 },

    // Bush
    { MT_BUSH_L, MT_0, MT_0 },
    { MT_BUSH_M, MT_0, MT_0 },
    { MT_BUSH_R, MT_0, MT_0 },

    // Mountain
    { MT_0, MT_MOUNTAIN_L, MT_MOUNTAIN_DOTS_1 },
    { MT_MOUNTAIN_TOP, MT_MOUNTAIN_DOTS_1, MT_MOUNTAIN_GREEN },
    { MT_0, MT_MOUNTAIN_R, MT_MOUNTAIN_DOTS_2 },

    // Fence
    { MT_FENCE, MT_0, MT_0 },

    // Tall tree
    { MT_TREE_TALL_1, MT_TREE_TALL_2, MT_TREE_TRUNK },

    // Short tree
    { MT_TREE_SHORT, MT_TREE_TRUNK, MT_TREE_TRUNK },
  };

  assert_eq_assumption(BackgroundScenery <= 3, true);
  assert_eq_assumption(ForegroundScenery <= 3, true);
  assert_eq_assumption(CurrentColumnPos < 16, true);

  if (BackgroundScenery != 0) {
    // NES note: In the original, if the page location is > 0x82, it breaks a loop that calculates modulo 3.
    // This port fixes it. Keeping the old glitchy behavior isn't worth it.
    // This glitch is impractical if not impossible to execute in unmodified ROMs,
    // but is still potentially achievable in modified levels.
    //
    // In practice, CurrentPageLoc only goes up to 24 in unmodified ROMs without jumping over the flagpole.
    // It takes between 4 to 5 time units to travel 1 page location by running.
    // To get from page 24 to 0x82, the player would travel 106 pages.
    // If the player ran nonstop from page 24 to 0x82, it would take between 424 to 530 time units.

    const u8 back_scenery_data = backscenery_lookup[BackgroundScenery - 1][CurrentPageLoc % 3][CurrentColumnPos];

    if (back_scenery_data != 0) {
      const byte type = back_scenery_data & 0xf;
      const byte mt_y = back_scenery_data >> 4;

      assert_eq_assumption(type >= 1, true);
      assert_eq_assumption(type <= 12, true);

      for (int i = 0; i < 3; i++) {
        if (mt_y+i == 11) {
          break;
        }
        MetatileBuffer[mt_y + i] = backscenery_metatiles[type-1][i];
      }
    }
  }

  static const u8 forescenery_metatiles[3][13] = {
    // in water
    { MT_WATER_TOP,
      MT_WATER_BLANK, MT_WATER_BLANK, MT_WATER_BLANK, MT_WATER_BLANK, MT_WATER_BLANK, MT_WATER_BLANK, MT_WATER_BLANK, MT_WATER_BLANK, MT_WATER_BLANK, MT_WATER_BLANK,
      MT_UNDERWATER_GROUND,
      MT_UNDERWATER_GROUND, },

    // wall
    { MT_0, MT_0, MT_0, MT_0, MT_0, MT_CASTLE_TOP, MT_CASTLE_BRICK, MT_CASTLE_BRICK, MT_CASTLE_BRICK, MT_CASTLE_BRICK, MT_CASTLE_BRICK,
      MT_0, MT_0, },

    // over water. also lava.
    { MT_0, MT_0, MT_0, MT_0, MT_0, MT_0, MT_0, MT_0, MT_0, MT_0, MT_0, MT_WATER_TOP, MT_WATER_BLANK, },
  };

  if (ForegroundScenery != 0) {
    for (int i = 0; i < 13; i++) {
      const u8 metatile = forescenery_metatiles[ForegroundScenery - 1][i];
      if (metatile != 0) {
        MetatileBuffer[i] = metatile;
      }
    }
  }

  static const u8 terrain_metatiles[4] = {
    MT_UNDERWATER_GROUND, MT_STONE, MT_BRICK, MT_CASTLE_INSIDE_WALL
  };

  assert_eq_assumption(AreaType < 4, true);

  // RendTerr
  {
    byte mt = terrain_metatiles[AreaType];

    if (CloudTypeOverride != 0) {
      mt = MT_CLOUD_BLOCK;
    }

    // Special exception for water levels in world 8
    if ((AreaType == 0) && (WorldNumber == 7)) {
      mt = MT_CASTLE_INSIDE_WALL;
    }

    assert_eq_assumption(TerrainControl < 16, true);

    static const u16 terrain_renderbits[16] = {
      0b0000000000000000,
      0b0001100000000000,
      0b0001100000000001,
      0b0001100000000111,
      0b0001100000001111,
      0b0001100011111111,
      0b0001111100000001,
      0b0001111100000111,
      0b0001111100001111,
      0b0001111110000001,
      0b0000000000000001,
      0b0001111110001111,
      0b0001111111110001,
      0b0001100011111001,
      0b0001100011110001,
      0b0001111111111111,
    };

    // a 13-bit bitfield
    u16 bits = terrain_renderbits[TerrainControl];

    if (CloudTypeOverride != 0) {
      // Render 0-7, and 11
      bits &= 0x08ff;
    }

    for (int j = 0; j < 13; j++) {
      if ((AreaType == 2) && (j >= 11)) {
        // For underground levels, replace the ground
        mt = MT_STONE;
      }

      if ((bits & (1 << j)) != 0) {
        MetatileBuffer[j] = mt;
      }
    }
  }

  // RendBBuf

  ProcessAreaData();

  // Inlined: GetBlockBufferAddr

  const u16 mt_x = BlockBufferColumnPos;

  for (int i = 0; i < 13; i++) {
    const byte mt = MetatileBuffer[i];

    // Note: simplified lookup of BlockBuffLowBounds

    if (mt < MT_PIPE_VERT_WARP_TL || (mt >= MT_ROPE_VERT && mt < MT_BRICK_2) || (mt >= MT_CLOUD_TL && mt < MT_CLOUD_BLOCK)) {
      set_metatile(mt_x, i, MT_0);
    } else {
      set_metatile(mt_x, i, mt);
    }
  }
}


// SMB:9508
// SM2MAIN:7319
// Signature: [] -> []
void ProcessAreaData(void) {
  while (true) {
    for (int objoff = 2; objoff >= 0; objoff--) {
      BehindAreaParserFlag = 0;

      bool decode = true;

      if (AreaData[AreaDataOffset] == 0xfd) {
        decode = true;
      } else if (AreaObjectLength[objoff] < 0x80) {
        decode = true;
      } else {
        const byte second_byte = AreaData[AreaDataOffset + 1];
        const byte first_nibble = AreaData[AreaDataOffset] & 0xf;

        if (second_byte & 0x80) {
          if (AreaObjectPageSel == 0) {
            AreaObjectPageSel = 1;
            AreaObjectPageLoc += 1;
          }
        }

        if ((first_nibble == 0xd) && ((second_byte & 0x40) == 0) && (AreaObjectPageSel == 0)) {
          AreaObjectPageLoc = second_byte & 0x1f;
          AreaObjectPageSel = 1;
          decode = false;
        } else if ((first_nibble == 0xe) && (BackloadingFlag != 0)) {
          decode = true;
        } else {
          // CheckRear
          if (CurrentPageLoc <= AreaObjectPageLoc) {
            decode = true;
          } else {
            // SetBehind
            BehindAreaParserFlag = 1;
            decode = false;
          }
        }
      }

      if (decode) {
        // RdyDecode
        if (!DecodeAreaData(objoff, AreaDataOffset)) {
          BackloadingFlag = 0;
          BehindAreaParserFlag = 0;

          // ChkLength
          if (AreaObjectLength[0] < 0x80) {
            AreaObjectLength[0] -= 1;
          }

          return;
        }
      } else {
        // NextAObj
        // inlined: IncAreaObjOffset
        AreaDataOffset += 2;
        AreaObjectPageSel = 0;
      }

      // ChkLength
      if (AreaObjectLength[objoff] < 0x80) {
        AreaObjectLength[objoff] -= 1;
      }
    }

    if ((BehindAreaParserFlag == 0) && (BackloadingFlag == 0)) {
      return;
    }
  }
}


// SMB:9595
// SM2MAIN:73a6
bool DecodeAreaData(const byte objoff, const byte param_2) {
  // Note: reworked to return false if r08 is set to 0. Unmodified otherwise.
  // X = r08 on call.
  // Original signature: [X, Y, r08] -> [r08]

  byte tmp1 = param_2;
  if (AreaObjectLength[objoff] < 0x80) {
    tmp1 = AreaObjOffsetBuffer[objoff];
  }

  if (AreaData[tmp1] == 0xfd) {
    return true;
  }

  const byte data = AreaData[(byte)(tmp1 + 1)];

  char cVar2 = 0;
  byte bVar1;

  switch (AreaData[tmp1] & 0xf) {
  case 0xe:
    bVar1 = ssw(0x2e, 0x36);
    break;

  case 0xd:
    cVar2 = ssw(0x22, 0x28);
    if ((data & 0x40) == 0) {
      return true;
    }
    if ((data & 0x7f) == 0x4b) {
      LoopCommand += 1;
    }
    bVar1 = data & 0x3f;
    break;

  case 0xc:
    cVar2 = 8;
    bVar1 = (data & 0x70) >> 4;
    break;

  case 0xf:
    cVar2 = 0x10;
    bVar1 = (data & 0x70) >> 4;
    break;

  default:
    if ((data & 0x70) == 0) {
      cVar2 = ssw(0x16, 0x18);
      bVar1 = data & 0xf;
    } else if ((data & 0x78) == (0x70 | 0x08)) {
      bVar1 = 0;
    } else {
      bVar1 = (data & 0x70) >> 4;
    }
    break;
  }

  if (AreaObjectLength[objoff] >= 0x80) {
    if (AreaObjectPageLoc != CurrentPageLoc) {
      if ((AreaData[AreaDataOffset] & 0xf) != 0xe) {
        return true;
      }
      if (BackloadingFlag == 0) {
        return true;
      }
    } else {
      // InitRear
      if (BackloadingFlag != 0) {
        // Note: moved BackloadingFlag and BehindAreaParserFlag clear to caller instead
        return false;
      }

      // BackColC
      if ((AreaData[AreaDataOffset] >> 4) != CurrentColumnPos) {
        return true;
      }
    }
    // StarAObj
    AreaObjOffsetBuffer[objoff] = AreaDataOffset;

    // inlined: IncAreaObjOffset
    AreaDataOffset += 2;
    AreaObjectPageSel = 0;
  }

  const byte jmptable_idx = bVar1 + cVar2;

  switch (jmptable_idx) {
  case DECODEAREADATA_VERTICALPIPE_1:
    VerticalPipe(objoff, bVar1 != 0);
    return true;

  case DECODEAREADATA_VERTICALPIPE_2:
    VerticalPipe(objoff, bVar1 != 0);
    return true;

  case DECODEAREADATA_AREASTYLEOBJECT:
    switch (AreaStyle) {
    case AREASTYLEOBJECT_TREELEDGE:
      TreeLedge(objoff);
      return true;

    case AREASTYLEOBJECT_MUSHROOMLEDGE:
#ifdef SMB1_MODE
      MushroomLedge(objoff);
#endif
#ifdef SMB2J_MODE
      CloudLedge(objoff);
#endif
      return true;

    case AREASTYLEOBJECT_BULLETBILLCANNON:
      BulletBillCannon(objoff);
      return true;

    default:
      jmpengine_overflow(AreaStyle);
      return true;
    }

  case DECODEAREADATA_ROWOFBRICKS:
    RowOfBricks(objoff);
    return true;

  case DECODEAREADATA_ROWOFSOLIDBLOCKS:
    RowOfSolidBlocks(objoff);
    return true;

  case DECODEAREADATA_ROWOFCOINS:
    RowOfCoins(objoff);
    return true;

  case DECODEAREADATA_COLUMNOFBRICKS:
    ColumnOfBricks(objoff);
    return true;

  case DECODEAREADATA_COLUMNOFSOLIDBLOCKS:
    ColumnOfSolidBlocks(objoff);
    return true;

  case DECODEAREADATA_HOLE_EMPTY:
    Hole_Empty(objoff);
    return true;

  case DECODEAREADATA_PULLEYROPEOBJECT:
    PulleyRopeObject(objoff);
    return true;

  case DECODEAREADATA_BRIDGE_HIGH:
    Bridge_High(objoff);
    return true;

  case DECODEAREADATA_BRIDGE_MIDDLE:
    Bridge_Middle(objoff);
    return true;

  case DECODEAREADATA_BRIDGE_LOW:
    Bridge_Low(objoff);
    return true;

  case DECODEAREADATA_HOLE_WATER:
    Hole_Water(objoff);
    return true;

  case DECODEAREADATA_QUESTIONBLOCKROW_HIGH:
    QuestionBlockRow_High(objoff);
    return true;

  case DECODEAREADATA_QUESTIONBLOCKROW_LOW:
    QuestionBlockRow_Low(objoff);
    return true;

  case DECODEAREADATA_ENDLESSROPE:
    EndlessRope();
    return true;

  case DECODEAREADATA_BALANCEPLATROPE:
    BalancePlatRope(objoff);
    return true;

  case DECODEAREADATA_CASTLEOBJECT:
    CastleObject(objoff);
    return true;

  case DECODEAREADATA_STAIRCASEOBJECT:
    StaircaseObject(objoff);
    return true;

  case DECODEAREADATA_EXITPIPE:
    ExitPipe(objoff);
    return true;

  case DECODEAREADATA_FLAGBALLS_RESIDUAL:
    FlagBalls_Residual(objoff);
    return true;

  case DECODEAREADATA_QUESTIONBLOCK_1:
  case DECODEAREADATA_QUESTIONBLOCK_2:
  case DECODEAREADATA_QUESTIONBLOCK_3:
    QuestionBlock(objoff, bVar1);
    return true;

  case DECODEAREADATA_HIDDEN1UPBLOCK:
    Hidden1UpBlock(objoff, bVar1);
    return true;

  case DECODEAREADATA_BRICKWITHITEM_1:
  case DECODEAREADATA_BRICKWITHITEM_2:
  case DECODEAREADATA_BRICKWITHITEM_3:
  case DECODEAREADATA_BRICKWITHITEM_4:
    BrickWithItem(objoff, bVar1);
    return true;

  case DECODEAREADATA_BRICKWITHCOINS:
    BrickWithCoins(objoff, bVar1);
    return true;

  case DECODEAREADATA_WATERPIPE:
    WaterPipe(objoff);
    return true;

  case DECODEAREADATA_EMPTYBLOCK:
    EmptyBlock(objoff);
    return true;

  case DECODEAREADATA_JUMPSPRING:
    Jumpspring(objoff);
    return true;

  case DECODEAREADATA_INTROPIPE:
    IntroPipe(objoff);
    return true;

  case DECODEAREADATA_FLAGPOLEOBJECT:
    FlagpoleObject();
    return true;

  case DECODEAREADATA_AXEOBJ:
    AxeObj(bVar1);
    return true;

  case DECODEAREADATA_CHAINOBJ:
    ChainObj(bVar1);
    return true;

  case DECODEAREADATA_CASTLEBRIDGEOBJ:
    CastleBridgeObj(objoff, bVar1);
    return true;

  case DECODEAREADATA_SCROLLLOCKOBJECT_WARP:
    ScrollLockObject_Warp();
    return true;

  case DECODEAREADATA_SCROLLLOCKOBJECT_1:
  case DECODEAREADATA_SCROLLLOCKOBJECT_2:
    ScrollLockObject();
    return true;

  case DECODEAREADATA_AREAFRENZY_1:
  case DECODEAREADATA_AREAFRENZY_2:
  case DECODEAREADATA_AREAFRENZY_3:
    AreaFrenzy(bVar1);
    return true;

  case DECODEAREADATA_NOOP:
    // NES note: goes to "LoopCmdE" (a no-op)
    return true;

  case DECODEAREADATA_ALTERAREAATTRIBUTES:
    AlterAreaAttributes(objoff);
    return true;

#ifdef SMB2J_MODE
  case DECODEAREADATA_QUESTIONBLOCK_4:
  case DECODEAREADATA_QUESTIONBLOCK_5:
  case DECODEAREADATA_QUESTIONBLOCK_6:
    QuestionBlock(objoff, bVar1);
    return true;

  case DECODEAREADATA_BRICKWITHITEM_5:
    BrickWithItem(objoff, bVar1);
    return true;

  case DECODEAREADATA_UPSIDEDOWNPIPE_HIGH:
    UpsideDownPipe_High(objoff);
    return true;

  case DECODEAREADATA_UPSIDEDOWNPIPE_LOW:
    UpsideDownPipe_Low(objoff);
    return true;

  case DECODEAREADATA_WINDON:
    WindOn();
    return true;

  case DECODEAREADATA_WINDOFF:
    WindOff();
    return true;
#endif

  default:
    jmpengine_overflow(jmptable_idx);
  }
}


// SMB:96c5
// SM2MAIN:74e6
// Signature: [X] -> []
void AlterAreaAttributes(const byte param_1) {
  byte bVar1 = AreaData[(byte)(AreaObjOffsetBuffer[param_1] + 1)];
  if ((bVar1 & 0x40) == 0) {
    TerrainControl = bVar1 & 0xf;
    BackgroundScenery = (bVar1 & 0x30) >> 4;
    return;
  }
  bVar1 &= 7;
  ForegroundScenery = bVar1;
  if (bVar1 >= 4) {
    ForegroundScenery = 0;
    BackgroundColorCtrl = bVar1;
  }
}


// SMB:970d
// SM2MAIN:7564
// Signature: [] -> []
void ScrollLockObject(void) {
  ScrollLock = ScrollLock ^ 1;
}


// SMB:972b
// SM2MAIN:7582
// Signature: [r00] -> []
void AreaFrenzy(const byte param_1) {
  assert_eq_assumption(param_1 >= 8 && param_1 <= 10, true);

  u8 enemy_id;
  switch (param_1) {
  case 8:  enemy_id = A_FLYING_CHEEPCHEEP; break;
  case 9:  enemy_id = A_BULLET_BILL_OR_CHEEPCHEEP_FRENZY; break;
  case 10: enemy_id = A_STOP_FRENZY; break;
  default: assert_unreachable();
  }

  for (int i = 0; i < 5; i++) {
    if (Enemy_ID[i] == enemy_id) {
      EnemyFrenzyQueue = 0;
      return;
    }
  }

  EnemyFrenzyQueue = enemy_id;
}


// SMB:974c
// SM2MAIN:75a3
// Signature: [X] -> []
void TreeLedge(const byte param_1) {
  const struct_yr07 sVar2 = GetLrgObjAttrib(param_1);
  const byte bVar1 = sVar2.r07;

  const u8 areaobjlen = AreaObjectLength[param_1];
  if (areaobjlen == 0) {
    NoUnder(MT_TREELEDGE_R, bVar1);
    return;
  }

  if (areaobjlen >= 0x80) {
    AreaObjectLength[param_1] = sVar2.y;
    if ((CurrentPageLoc | CurrentColumnPos) != 0) {
      NoUnder(MT_TREELEDGE_L, bVar1);
      return;
    }
  }

  MetatileBuffer[bVar1] = MT_TREELEDGE_M;
  RenderUnderPart(MT_TREELEDGE_TRUNK, bVar1 + 1, 0xf);
}


// SMB:97b0
// SM2MAIN:75fc
// Signature: [A, r07] -> []
void NoUnder(const byte param_1, const byte param_2) {
  RenderUnderPart(param_1, param_2, 0);
}


// SMB:97ba
// SM2MAIN:7606
// Signature: [X] -> []
void PulleyRopeObject(const byte param_1) {
  const struct_ycr07 sVar2 = ChkLrgObjLength(param_1);
  if (sVar2.c) {
    MetatileBuffer[0] = MT_PULLEY_ROPE_TL;
  } else if (AreaObjectLength[param_1] != 0) {
    MetatileBuffer[0] = MT_PULLEY_ROPE_HORZ;
  } else {
    MetatileBuffer[0] = MT_PULLEY_ROPE_TR;
  }
}


// SMB:9806
// SM2MAIN:7652
// Signature: [X] -> []
void CastleObject(const byte objoff) {
  // objoff is always 0,1,2
  assert_eq_assumption(objoff <= 2, true);

  const struct_yr07 sVar5 = GetLrgObjAttrib(objoff);
  const byte start_at_y = sVar5.y;
  ChkLrgObjFixedLength(objoff, 4);

  const byte j = AreaObjectLength[objoff];

  assert_eq_assumption(j < 5, true);

  // sVar5.y is which y to start drawing the castle. it's 0 or 6.
  // shorter castles (in X-1 and X-2 levels) don't draw the bottom
  assert_eq_assumption(sVar5.y < 11, true);

  static const u8 _ = MT_0;
  static const u8 T = MT_CASTLE_TOP;
  static const u8 N = MT_CASTLE_NOTCH;
  static const u8 x = MT_CASTLE_BRICK;
  static const u8 D = MT_CASTLE_DOOR_T;
  static const u8 E = MT_CASTLE_DOOR_B;
  static const u8 L = MT_CASTLE_WINDOW_L;
  static const u8 R = MT_CASTLE_WINDOW_R;

  // Tiles are right-to-left
  static const u8 castle_metatiles[11][5] = {
    { _, T, T, T, _ },
    { _, R, x, L, _ },
    { T, N, N, N, T },
    { x, x, D, x, x },
    { x, x, E, x, x },

    { N, N, N, N, N },
    { x, D, x, D, x },
    { x, E, x, E, x },
    { x, x, x, x, x },
    { D, x, D, x, D },
    { E, x, E, x, E },
  };

  for (int i = start_at_y; i < 11; i++) {
    MetatileBuffer[i] = castle_metatiles[i - start_at_y][j];
  }

  if (CurrentPageLoc != 0) {
    if ((j == 1) || ((start_at_y == 0 && (j == 3)))) {
      // Put stopper block after the door
      // If it's a tall castle, ensure it's the first door

      MetatileBuffer[10] = MT_BRICK;
    } else if (j == 2) {
      const byte bStack0000 = GetAreaObjXPosition();
      const byte i = FindEmptyEnemySlot();

      // Note: If no slot is found, a value of 5 is used.

      Enemy_X_Position[i] = bStack0000;
      Enemy_PageLoc[i] = CurrentPageLoc;
      Enemy_Y_HighPos[i] = 1;
      Enemy_Flag[i] = 1;
      Enemy_Y_Position[i] = 0x90;
      Enemy_ID[i] = A_STARFLAG;
    }
  }
}


// SMB:986f
// SM2MAIN:76bb
// Signature: [X] -> []
void WaterPipe(const byte param_1) {
  const struct_yr07 sVar1 = GetLrgObjAttrib(param_1);
  MetatileBuffer[sVar1.r07] = MT_WATERPIPE_T;
  MetatileBuffer[sVar1.r07 + 1] = MT_WATERPIPE_B;
}


// SMB:9882
// SM2MAIN:76ce
// Signature: [X] -> []
void IntroPipe(const byte objoff) {
  // objoff is always 0,1,2
  assert_eq_assumption(objoff <= 2, true);

  ChkLrgObjFixedLength(objoff, 3);

  // Inlined: RenderSidewaysPipe
  // Note: Simplified

  const byte bVar2 = AreaObjectLength[objoff];
  assert_eq_assumption(bVar2 <= 3, true);

  const bool left_side = (bVar2 % 2) != 0;

  if (bVar2 < 2) {
    const u8 top_metatile = left_side ? MT_PIPE_VERT_WARP_TL : MT_PIPE_VERT_WARP_TR;
    const u8 under_metatile = left_side ? MT_PIPE_VERT_UNDER_L : MT_PIPE_VERT_UNDER_R;

    RenderUnderPart(under_metatile, 0, 8);
    for (int i = 0; i < 7; i++) {
      MetatileBuffer[i] = MT_0;
    }
    MetatileBuffer[7] = top_metatile;
    MetatileBuffer[9] = left_side ? MT_PIPE_CONNECTED_T : MT_PIPE_VERT_UNDER_R;
    MetatileBuffer[10] = left_side ? MT_PIPE_CONNECTED_B : MT_PIPE_VERT_UNDER_R;
  } else {
    MetatileBuffer[9] = left_side ? MT_PIPE_SIDEWAYS_TL : MT_PIPE_SIDEWAYS_MIDDLE_T;
    MetatileBuffer[10] = left_side ? MT_PIPE_SIDEWAYS_BL : MT_PIPE_SIDEWAYS_MIDDLE_B;
  }
}


// SMB:98ab
// SM2MAIN:76f7
// Signature: [X] -> []
void ExitPipe(const byte objoff) {
  // objoff is always 0,1,2
  assert_eq_assumption(objoff <= 2, true);

  ChkLrgObjFixedLength(objoff, 3);
  const struct_yr07 sVar1 = GetLrgObjAttrib(objoff);

  // Inlined: RenderSidewaysPipe

  const byte bVar2 = AreaObjectLength[objoff];
  assert_eq_assumption(bVar2 <= 3, true);

  assert_eq_assumption(sVar1.y >= 1, true);
  assert_eq_assumption(sVar1.y < 13, true);

  const bool left_side = (bVar2 % 2) != 0;

  if (bVar2 < 2) {
    const u8 under_metatile = left_side ? MT_PIPE_VERT_UNDER_L : MT_PIPE_VERT_UNDER_R;
    RenderUnderPart(under_metatile, 0, sVar1.y - 2);
    MetatileBuffer[sVar1.y - 1] = left_side ? MT_PIPE_CONNECTED_T : MT_PIPE_VERT_UNDER_R;
    MetatileBuffer[sVar1.y - 0] = left_side ? MT_PIPE_CONNECTED_B : MT_PIPE_VERT_UNDER_R;
  } else {
    MetatileBuffer[sVar1.y - 1] = left_side ? MT_PIPE_SIDEWAYS_TL : MT_PIPE_SIDEWAYS_MIDDLE_T;
    MetatileBuffer[sVar1.y - 0] = left_side ? MT_PIPE_SIDEWAYS_BL : MT_PIPE_SIDEWAYS_MIDDLE_B;
  }
}


// SMB:N/A (inlined in VerticalPipe)
// SM2MAIN:7772
// Signature: [A, X, r07] -> []
void SetupPiranhaPlant(const byte enemy_id, const byte param_2, const byte param_3) {
  const u16 xpos = (CurrentPageLoc << 8) + GetAreaObjXPosition() + 8;
  Enemy_X_Position[param_2] = xpos & 0xff;
  Enemy_PageLoc[param_2] = xpos >> 8;

  Enemy_Y_HighPos[param_2] = 1;
  Enemy_Y_Position[param_2] = GetAreaObjYPosition(param_3);

  Enemy_Flag[param_2] = 1;
  Enemy_ID[param_2] = enemy_id;

  InitPiranhaPlant(param_2);
}


// SMB:98e5
// SM2MAIN:7731
// Signature: [X, r00] -> []
void VerticalPipe(const byte param_1, const bool decorative) {
  const struct_yr06r07 sVar5 = GetPipeHeight(param_1);
  const byte bVar2 = sVar5.r07;
  const byte bVar1 = sVar5.r06;

  assert_eq_assumption(sVar5.y < 2, true);

  const bool left_side = sVar5.y != 0;

  bool check = AreaObjectLength[param_1] != 0;

#ifdef SMB1_MODE
  if (AreaNumber == 0 && WorldNumber == 0) {
    check = false;
  }
#endif

  if (check) {
    const byte i = FindEmptyEnemySlot();
    if (i != NO_AVAIL_ENEMY_SLOT) {
      SetupPiranhaPlant(A_PIRANHA_PLANT, i, bVar2);
    }
  }

  u8 top_metatile = left_side ? MT_PIPE_VERT_WARP_TL : MT_PIPE_VERT_WARP_TR;
  u8 under_metatile = left_side ? MT_PIPE_VERT_UNDER_L : MT_PIPE_VERT_UNDER_R;

  if (decorative) {
    // This pipe doesn't go somewhere
    top_metatile = left_side ? MT_PIPE_VERT_DECO_TL : MT_PIPE_VERT_DECO_TR;
  }

  MetatileBuffer[bVar2] = top_metatile;
  RenderUnderPart(under_metatile, bVar2 + 1, bVar1 - 1);
}


// SMB:9939
// SM2MAIN:7761
// Signature: [X] -> [Y, r06, r07]
struct_yr06r07 GetPipeHeight(const byte param_1) {
  ChkLrgObjFixedLength(param_1, 1);
  const struct_yr07 sVar1 = GetLrgObjAttrib(param_1);

  struct_yr06r07 res;
  res.y = AreaObjectLength[param_1];
  res.r06 = sVar1.y & 0x7;
  res.r07 = sVar1.r07;
  return res;
}


// SMB:994a
// SM2MAIN:7791
byte FindEmptyEnemySlot(void) {
  // Old signature: [] -> [X, C]
  // Rewritten to return a sentinel value if one is not found

  for (int i = 0; i < 5; i++) {
    if (Enemy_Flag[i] == 0) {
      return i;
    }
  }

  return NO_AVAIL_ENEMY_SLOT;
}


// SMB:9957
// SM2MAIN:779e
// Signature: [X] -> []
void Hole_Water(const byte param_1) {
  ChkLrgObjLength(param_1);
  MetatileBuffer[10] = MT_WATER_TOP;
  RenderUnderPart(MT_WATER_BLANK, 0xb, 1);
}


// SMB:9968
// SM2MAIN:77af
// Signature: [X] -> []
void QuestionBlockRow_High(const byte param_1) {
  ChkLrgObjLength(param_1);
  MetatileBuffer[3] = MT_QUESTIONBLOCK_COIN;
}


// SMB:996b
// SM2MAIN:77b2
// Signature: [X] -> []
void QuestionBlockRow_Low(const byte param_1) {
  ChkLrgObjLength(param_1);
  MetatileBuffer[7] = MT_QUESTIONBLOCK_COIN;
}


// SMB:9979
// SM2MAIN:77c0
// Signature: [X] -> []
void Bridge_High(const byte param_1) {
  ChkLrgObjLength(param_1);
  MetatileBuffer[6] = MT_BRIDGE_RAILING;
  RenderUnderPart(MT_BRIDGE_BLOCK, 7, 0);
}


// SMB:997c
// SM2MAIN:77c3
// Signature: [X] -> []
void Bridge_Middle(const byte param_1) {
  ChkLrgObjLength(param_1);
  MetatileBuffer[7] = MT_BRIDGE_RAILING;
  RenderUnderPart(MT_BRIDGE_BLOCK, 8, 0);
}


// SMB:997f
// SM2MAIN:77c6
// Signature: [X] -> []
void Bridge_Low(const byte param_1) {
  ChkLrgObjLength(param_1);
  MetatileBuffer[9] = MT_BRIDGE_RAILING;
  RenderUnderPart(MT_BRIDGE_BLOCK, 10, 0);
}


// SMB:9994
// SM2MAIN:77db
// Signature: [X] -> []
void FlagBalls_Residual(const byte param_1) {
  const struct_yr07 sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(MT_FLAGBALL, 2, sVar1.y);
}


// SMB:999e
// SM2MAIN:77e5
// Signature: [] -> []
void FlagpoleObject(void) {
  MetatileBuffer[0] = MT_FLAGPOLE_T;
  RenderUnderPart(MT_FLAGPOLE_M, 1, 8);
  MetatileBuffer[10] = MT_STAIR_BLOCK;
  const byte bVar1 = GetAreaObjXPosition();
  Enemy_X_Position[5] = bVar1 - 8;
  Enemy_PageLoc[5] = CurrentPageLoc - (bVar1 < 8);
  Enemy_Y_Position[5] = 0x30;
  FlagpoleFNum_Y_Pos = 0xb0;
  Enemy_ID[5] = A_FLAGPOLE;
  Enemy_Flag[5] = Enemy_Flag[5] + 1;
}


// SMB:99d0
// SM2MAIN:7817
// Signature: [] -> []
void EndlessRope(void) {
  RenderUnderPart(MT_ROPE_VERT, 0, 0xf);
}


// SMB:99d7
// SM2MAIN:781e
// Signature: [X] -> []
void BalancePlatRope(const byte param_1) {
  RenderUnderPart(MT_ROPE_NONE, 1, 0xf);
  const struct_yr07 sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(MT_ROPE_VERT, 1, sVar1.y);
}


// SMB:99f2
// SM2MAIN:7839
// Signature: [X] -> []
void RowOfCoins(const byte param_1) {
  const u8 metatile = AreaType != 0 ? MT_COIN : MT_COIN_UNDERWATER;
  const struct_ycr07 sVar1 = ChkLrgObjLength(param_1);
  RenderUnderPart(metatile, sVar1.r07, 0);
}


// SMB:9a01
// SM2MAIN:7848
// Signature: [X, r00] -> []
void CastleBridgeObj(const byte param_1, const byte param_2) {
  ChkLrgObjFixedLength(param_1, 0xc);
  ChainObj(param_2);
}


// SMB:9a09
// SM2MAIN:7850
// Signature: [r00] -> []
void AxeObj(const byte param_1) {
  VRAM_Buffer_AddrCtrl = ADDRCTRL_BOWSERPALETTEDATA;
  ChainObj(param_1);
}


// SMB:9a0e
// SM2MAIN:7855
// Signature: [r00] -> []
void ChainObj(const byte param_1) {
  assert_eq_assumption(param_1 >= 2 && param_1 < 5, true);

  const int i = param_1 - 2;

  static const u8 mt_y[3] = { 6, 7, 8 };
  static const u8 metatiles[3] = { MT_AXE, MT_BOWSERBRIDGE_CHAIN, MT_BOWSERBRIDGE_BLOCK };

  RenderUnderPart(metatiles[i], mt_y[i], 0);
}


// SMB:9a19
// SM2MAIN:7860
// Signature: [X] -> []
void EmptyBlock(const byte param_1) {
  const struct_yr07 sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(MT_BLOCK_EMPTY, sVar1.r07, 0);
}


// SMB:9a2e
// SM2MAIN:7875
// Signature: [X] -> []
void RowOfBricks(const byte param_1) {
  assert_eq_assumption(AreaType < 4, true);
  byte bVar1 = AreaType;
  if (CloudTypeOverride != 0) {
    bVar1 = 4;
  }
  static const u8 metatiles[5] = { MT_CORAL, MT_BRICK_2, MT_BRICK, MT_BRICK, MT_CLOUD_BLOCK };
  const u8 mt = metatiles[bVar1];
  const struct_ycr07 sVar2 = ChkLrgObjLength(param_1);
  RenderUnderPart(mt, sVar2.r07, 0);
}


// SMB:9a3e
// SM2MAIN:7885
// Signature: [X] -> []
void RowOfSolidBlocks(const byte param_1) {
  assert_eq_assumption(AreaType < 4, true);
  static const u8 metatiles[4] = { MT_UNDERWATER_GROUND, MT_STAIR_BLOCK, MT_STAIR_BLOCK, MT_CASTLE_INSIDE_WALL };
  const u8 mt = metatiles[AreaType];
  const struct_ycr07 sVar1 = ChkLrgObjLength(param_1);
  RenderUnderPart(mt, sVar1.r07, 0);
}


// SMB:9a50
// SM2MAIN:7897
// Signature: [X] -> []
void ColumnOfBricks(const byte param_1) {
  assert_eq_assumption(AreaType < 4, true);
  static const u8 metatiles[4] = { MT_CORAL, MT_BRICK_2, MT_BRICK, MT_BRICK };
  const u8 mt = metatiles[AreaType];
  const struct_yr07 sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(mt, sVar1.r07, sVar1.y);
}


// SMB:9a59
// SM2MAIN:78a0
// Signature: [X] -> []
void ColumnOfSolidBlocks(const byte param_1) {
  assert_eq_assumption(AreaType < 4, true);
  static const u8 metatiles[4] = { MT_UNDERWATER_GROUND, MT_STAIR_BLOCK, MT_STAIR_BLOCK, MT_CASTLE_INSIDE_WALL };
  const u8 mt = metatiles[AreaType];
  const struct_yr07 sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(mt, sVar1.r07, sVar1.y);
}


// SMB:9a69
// SM2MAIN:78b0
// Signature: [X] -> []
void BulletBillCannon(const byte param_1) {
  const struct_yr07 sVar3 = GetLrgObjAttrib(param_1);
  byte bVar1 = sVar3.r07;
  MetatileBuffer[bVar1] = MT_BULLETBILL_CANNON_T;
  if ((byte)(sVar3.y - 1) < 0x80) {
    MetatileBuffer[(byte)(bVar1 + 1)] = MT_BULLETBILL_CANNON_BODY;
    const byte bVar2 = sVar3.y - 2;
    if (bVar2 < 0x80) {
      RenderUnderPart(MT_BULLETBILL_CANNON_B, bVar1 + 2, bVar2);
    }
  }

  const byte y = GetAreaObjYPosition(bVar1);
  Cannon_Y_Position[Cannon_Or_Whirlpool_Offset] = y;
  Cannon_PageLoc[Cannon_Or_Whirlpool_Offset] = CurrentPageLoc;
  const byte x = GetAreaObjXPosition();
  Cannon_X_Position[Cannon_Or_Whirlpool_Offset] = x;

  Cannon_Or_Whirlpool_Offset += 1;
  if (Cannon_Or_Whirlpool_Offset > 5) {
    Cannon_Or_Whirlpool_Offset = 0;
  }
}


// SMB:9ab7
// SM2MAIN:78fe
// Signature: [X] -> []
void StaircaseObject(const byte param_1) {
  const struct_ycr07 sVar1 = ChkLrgObjLength(param_1);
  if (sVar1.c) {
    StaircaseControl = 9;
  }
  StaircaseControl -= 1;
  RenderUnderPart(MT_STAIR_BLOCK, StaircaseRowData[StaircaseControl], StaircaseHeightData[StaircaseControl]);
}


// SMB:9ad3
// SM2MAIN:791a
// Signature: [X] -> []
void Jumpspring(const byte param_1) {
  const struct_yr07 sVar4 = GetLrgObjAttrib(param_1);
  const byte bVar1 = sVar4.r07;
  const byte i = FindEmptyEnemySlot();

  if (SMB2J_ONLY && i == NO_AVAIL_ENEMY_SLOT) {
    return;
  }

  Enemy_X_Position[i] = GetAreaObjXPosition();
  Enemy_PageLoc[i] = CurrentPageLoc;
  const byte bVar2 = GetAreaObjYPosition(bVar1);
  Enemy_Y_Position[i] = bVar2;
  Jumpspring_FixedYPos[i] = bVar2;
  Enemy_ID[i] = A_JUMPSPRING;
  Enemy_Y_HighPos[i] = 1;
  Enemy_Flag[i] += 1;
  MetatileBuffer[bVar1] = MT_JUMPSPRING_T;
  MetatileBuffer[bVar1 + 1] = MT_JUMPSPRING_B;
}


// SMB:9b01
// SM2MAIN:794a
// Signature: [X, r00] -> []
void Hidden1UpBlock(const byte param_1, const byte param_2) {
  if (Hidden1UpFlag != 0) {
    Hidden1UpFlag = 0;
    BrickWithItem(param_1, param_2);
  }
}


// SMB:9b0e
// SM2MAIN:7957
// Signature: [X, r00] -> []
void QuestionBlock(const byte param_1, const byte param_2) {
  const byte bStack0000 = BrickQBlockMetatiles[param_2];
  const struct_yr07 sVar2 = GetLrgObjAttrib(param_1);
  RenderUnderPart(bStack0000, sVar2.r07, 0);
}


// SMB:9b14
// SM2MAIN:795d
// Signature: [X, r00] -> []
void BrickWithCoins(const byte param_1, const byte param_2) {
  BrickCoinTimerFlag = 0;
  BrickWithItem(param_1, param_2);
}


// SMB:9b19
// SM2MAIN:7962
// Signature: [X, r00] -> []
void BrickWithItem(const byte param_1, const byte param_2) {
  char cVar1 = 0;
  if (AreaType != 1) {
    cVar1 = ssw(5, 6);
  }
  const byte bStack0000 = BrickQBlockMetatiles[(byte)(cVar1 + param_2)];
  const struct_yr07 sVar3 = GetLrgObjAttrib(param_1);
  RenderUnderPart(bStack0000, sVar3.r07, 0);
}


// SMB:9b41
// SM2MAIN:798a
// Signature: [X] -> []
void Hole_Empty(const byte param_1) {
  const struct_ycr07 sVar3 = ChkLrgObjLength(param_1);
  const byte bVar2 = sVar3.y;
  if ((sVar3.c) && (AreaType == 0)) {
    const byte x = GetAreaObjXPosition();

    Whirlpool_X_Position[Cannon_Or_Whirlpool_Offset] = x - 0x10;
    Whirlpool_PageLoc[Cannon_Or_Whirlpool_Offset] = CurrentPageLoc - (x < 0x10);
    Whirlpool_Length[Cannon_Or_Whirlpool_Offset] = (bVar2 + 2) * 0x10;

    Cannon_Or_Whirlpool_Offset += 1;
    if (Cannon_Or_Whirlpool_Offset >= 5) {
      Cannon_Or_Whirlpool_Offset = 0;
    }
  }

  const u8 metatile = AreaType != 0 ? MT_0 : MT_WATER_BLANK;

  RenderUnderPart(metatile, 8, 0xf);
}


// SMB:9b7d
// SM2MAIN:79c6
// Signature: [A, X, Y] -> []
void RenderUnderPart(const byte mt, const byte mt_y, const byte param_3) {
  // Note: Removed AreaObjectHeight global variable ($0735).
  // It's only ever used in this subroutine.
  //
  // Note: X is used as a return value in the original, which is an added metatile buffer index. It's removed in this port.
  // if param_3 <= 0x80, it would return (mt_y+param_3+1) or 13, whichever one is smallest
  // if param_3 > 0x80, it would return (mt_y+1) or 13, whichever one is smallest

  byte j = mt_y;

  byte count = param_3 + 1;

  if (param_3 > 0x80) {
    count = 1;
  }

  for (int i = 0; i < count; i++) {
    const byte existing_mt = MetatileBuffer[j];

    bool draw_metatile = true;

    if (existing_mt == MT_TREELEDGE_M) {
        draw_metatile = false;
    }

#ifdef SMB1_MODE
    if (existing_mt == MT_MUSHROOMLEDGE_M) {
        draw_metatile = false;
    }

    if (mt == MT_MUSHROOMLEDGE_STEM_UNDER && existing_mt == MT_STONE) {
        draw_metatile = false;
    }
#endif

#ifdef SMB2J_MODE
    if (existing_mt == MT_CLOUDLEDGE_M) {
        draw_metatile = false;
    }
#endif

    if (existing_mt > 0xc0) {
        draw_metatile = false;
    }

    if (draw_metatile) {
      MetatileBuffer[j] = mt;
    }

    j += 1;

    if (j >= 13) {
      break;
    }
  }
}


// SMB:9bac
// SM2MAIN:79ed
// Signature: [X] -> [Y, C, r07]
struct_ycr07 ChkLrgObjLength(const byte param_1) {
  struct_ycr07 sVar3;

  const struct_yr07 sVar4 = GetLrgObjAttrib(param_1);
  const byte bVar1 = sVar4.r07;
  const byte bVar2 = sVar4.y;
  sVar3.c = ChkLrgObjFixedLength(param_1, bVar2);
  sVar3.y = bVar2;
  sVar3.r07 = bVar1;
  return sVar3;
}


// SMB:9baf
// SM2MAIN:79f0
// Signature: [X, Y] -> [C]
bool ChkLrgObjFixedLength(const byte param_1, const byte param_2) {
  const byte bVar1 = AreaObjectLength[param_1];
  if (bVar1 >= 0x80) {
    AreaObjectLength[param_1] = param_2;
  }
  return bVar1 >= 0x80;
}


// SMB:9bbb
// SM2MAIN:79fc
// Signature: [X] -> [Y, r07]
struct_yr07 GetLrgObjAttrib(const byte param_1) {
  struct_yr07 res;
  res.y = AreaData[(byte)(AreaObjOffsetBuffer[param_1] + 1)] & 0xf;
  res.r07 = AreaData[AreaObjOffsetBuffer[param_1]] & 0xf;
  return res;
}


// SMB:9bcb
// SM2MAIN:7a0c
// Signature: [] -> [A]
byte GetAreaObjXPosition(void) { return CurrentColumnPos << 4; }


// SMB:9bd3
// SM2MAIN:7a14
// Signature: [r07] -> [A]
byte GetAreaObjYPosition(const byte param_1) { return param_1 * 0x10 + 0x20; }


// SMB:9c03
// SM2MAIN:c2a4
// Signature: [] -> []
void LoadAreaPointer(void) {
  // Inlined: FindAreaPointer
  const byte area_pointer = AreaAddrOffsets[(byte)(WorldAddrOffsets[WorldNumber] + AreaNumber)];
  const byte area_type = (area_pointer & 0x60) >> 5;

  AreaPointer = area_pointer;
  AreaType = area_type;
}


// SMB:9c22
// SM2MAIN:c2c3
// Signature: [] -> []
void GetAreaDataAddrs(void) {
  // Inlined: GetAreaType
  const byte area_type = (AreaPointer & 0x60) >> 5;
  const byte loffset = AreaPointer & 0x1f;
  AreaType = area_type;
  AreaAddrsLOffset = loffset;

  {
#ifdef SMB1_MODE
    const byte off = EnemyAddrHOffsets[area_type] + loffset;
    const byte lo = EnemyDataAddrLow[off];
    const byte hi = EnemyDataAddrHigh[off];
#endif
#ifdef SMB2J_MODE
    const byte off = (EnemyAddrHOffsets[area_type] + loffset) * 2;
    const byte lo = EnemyDataAddrs[off];
    const byte hi = EnemyDataAddrs[off + 1];
#endif
    const u16 addr = (hi << 8) | lo;
    STORE_16(EnemyData_addr_hi, EnemyData_addr_lo, addr);
    EnemyData = rom_ptr(addr);
  }

  {
#ifdef SMB1_MODE
    const byte off = AreaDataHOffsets[area_type] + loffset;
    const byte lo = AreaDataAddrLow[off];
    const byte hi = AreaDataAddrHigh[off];
#endif
#ifdef SMB2J_MODE
    const byte off = (AreaDataHOffsets[area_type] + loffset) * 2;
    const byte lo = AreaDataAddrs[off];
    const byte hi = AreaDataAddrs[off + 1];
#endif
    const u16 addr = (hi << 8) | lo;
    STORE_16(AreaData_addr_hi, AreaData_addr_lo, addr);
    AreaData = rom_ptr(addr);
  }

  const byte area_data_0 = AreaData[0];
  // gg ppp fff

  const byte area_data_1 = AreaData[1];
  // aa bb tttt

  const byte gg = area_data_0 >> 6;
  const byte ppp = (area_data_0 & 0x38) >> 3;
  const byte fff = area_data_0 & 7;

  if (fff >= 4) {
    ForegroundScenery = 0;
    BackgroundColorCtrl = fff;
  } else {
    ForegroundScenery = fff;
  }
  PlayerEntranceCtrl = ppp;
  GameTimerSetting = gg;

  const byte aa = area_data_1 >> 6;
  const byte bb = (area_data_1 & 0x30) >> 4;
  const byte tttt = area_data_1 & 0xf;

  TerrainControl = tttt;
  BackgroundScenery = bb;
  if (aa == 3) {
    AreaStyle = 0;
    CloudTypeOverride = 3;
  } else {
    AreaStyle = aa;
  }

  ADD_UNSIGNED_16_8(AreaData_addr_hi, AreaData_addr_lo,
                    2);
  AreaData += 2;
}


#ifdef SMB2J_MODE


// SM2DATA4:c2c3
// Signature: [] -> []
void AltHard_GetAreaDataAddrs(void) {
  // Inlined: GetAreaType
  const byte area_type = (AreaPointer & 0x60) >> 5;
  const byte loffset = AreaPointer & 0x1f;
  AreaType = area_type;
  AreaAddrsLOffset = loffset;

  {
    const byte off = AltHard_EnemyAddrHOffsets[area_type] + loffset;
    const byte lo = AltHard_EnemyDataAddrs[(byte)(off * 2)];
    const byte hi = AltHard_EnemyDataAddrs[(byte)(off * 2) + 1];
    const u16 addr = (hi << 8) | lo;
    STORE_16(EnemyData_addr_hi, EnemyData_addr_lo, addr);
    EnemyData = rom_ptr(addr);
  }

  {
    const byte off = (AltHard_AreaDataHOffsets[area_type] + loffset) * 2;
    const byte lo = AltHard_AreaDataAddrs[off];
    const byte hi = AltHard_AreaDataAddrs[off + 1];
    const u16 addr = (hi << 8) | lo;
    STORE_16(AreaData_addr_hi, AreaData_addr_lo, addr);
    AreaData = rom_ptr(addr);
  }

  const byte area_data_0 = AreaData[0];
  // gg ppp fff

  const byte area_data_1 = AreaData[1];
  // aa bb tttt

  const byte gg = area_data_0 >> 6;
  const byte ppp = (area_data_0 & 0x38) >> 3;
  const byte fff = area_data_0 & 7;

  if (fff >= 4) {
    ForegroundScenery = 0;
    BackgroundColorCtrl = fff;
  } else {
    ForegroundScenery = fff;
  }
  PlayerEntranceCtrl = ppp;
  GameTimerSetting = gg;

  const byte aa = area_data_1 >> 6;
  const byte bb = (area_data_1 & 0x30) >> 4;
  const byte tttt = area_data_1 & 0xf;

  TerrainControl = tttt;
  BackgroundScenery = bb;
  AreaStyle = aa;
  if (aa == 3) {
    AreaStyle = 0;
    CloudTypeOverride = 3;
  } else {
    AreaStyle = aa;
  }

  ADD_UNSIGNED_16_8(AreaData_addr_hi, AreaData_addr_lo,
                    2);
  AreaData += 2;
}


#endif


static inline byte ScrollLockObject_Warp_smb2j_impl(void) {
  if (HardWorldFlag != 0) {
    // 121 = 0x100 - 0x87
    if (LevelNumber != 121) {
      return 0x87 + LevelNumber;
    }

    // NES note: Getting to this point would be a glitch in the original game.
    // The BNE instruction is meant to be unconditional.

    // The disassembly shows:
    //   LDA #$87
    //   CLC
    //   ADC LevelNumber
    //   BNE DumpWarpCtrl
  }

  if (HardWorldFlag == 0 && WorldNumber == 0) {
    if (AreaType == 1) {
      return 0x81;
    }

    if (AreaAddrsLOffset == 0) {
      return 0x80;
    }

    return 0x82;
  }

  if (WorldNumber == 2) {
    return 0x83;
  }

  if (WorldNumber == 4) {
    if (AreaAddrsLOffset == 0xb) {
      return 0x84;
    }

    if (AreaType != 1) {
      return 0x85;
    }

    return 0x86;
  }

  return 0x87;
}


// SMB:96f2
// SM2MAIN:7513
// Signature: [] -> []
void ScrollLockObject_Warp(void) {
#ifdef SMB1_MODE
  if (WorldNumber == 0) {
    WarpZoneControl = 4;
  } else if (AreaType != 1) {
    WarpZoneControl = 5;
  } else {
    WarpZoneControl = 6;
  }
  WriteGameText(WarpZoneControl);
#endif
#ifdef SMB2J_MODE
  WarpZoneControl = ScrollLockObject_Warp_smb2j_impl();
  WriteWarpZoneMessage(WarpZoneControl);
#endif
  KillEnemies(0xd);
  ScrollLockObject();
}


#ifdef SMB1_MODE
// SMB:9778
// Signature: [X] -> []
void MushroomLedge(const byte param_1) {
  const struct_ycr07 sVar4 = ChkLrgObjLength(param_1);
  const byte bVar3 = sVar4.r07;
  if (sVar4.c) {
    MushroomLedgeHalfLen[param_1] = AreaObjectLength[param_1] >> 1;
    NoUnder(MT_MUSHROOMLEDGE_L, bVar3);
    return;
  }

  const u8 areaobjlen = AreaObjectLength[param_1];
  if (areaobjlen == 0) {
    NoUnder(MT_MUSHROOMLEDGE_R, bVar3);
    return;
  }

  MetatileBuffer[bVar3] = MT_MUSHROOMLEDGE_M;

  // Draw the stem under the mushroom ledge

  const u8 bVar1 = MushroomLedgeHalfLen[param_1];
  if (areaobjlen == bVar1) {
    // Right under the mushroom
    MetatileBuffer[(byte)(bVar3 + 1)] = MT_MUSHROOMLEDGE_STEM_T;

    // The rest of the stem
    RenderUnderPart(MT_MUSHROOMLEDGE_STEM_UNDER, bVar3 + 2, 0xf);
  }
}
#endif


#ifdef SMB2J_MODE
// SM2MAIN:75cf
// Signature: [X] -> []
void CloudLedge(const byte param_1) {
  // Note: This is mostly the same as SMB1's MushroomLedge, but without the stem.
  // SMB2J replaced it with a cloud ledge.

  const struct_ycr07 sVar4 = ChkLrgObjLength(param_1);
  const byte bVar3 = sVar4.r07;
  if (sVar4.c) {
    MushroomLedgeHalfLen[param_1] = AreaObjectLength[param_1] >> 1;
    NoUnder(MT_CLOUDLEDGE_L, bVar3);
    return;
  }

  const byte areaobjlen = AreaObjectLength[param_1];
  if (areaobjlen == 0) {
    NoUnder(MT_CLOUDLEDGE_R, bVar3);
    return;
  }

  MetatileBuffer[bVar3] = MT_CLOUDLEDGE_M;
}
#endif

#ifdef SMB2J_MODE


// SM2MAIN:675e
// Signature: [A] -> []
void WriteWarpZoneMessage(const byte warp_zone_control) {
  // "Welcome to warp zone!"

  VRAM_Buffer1_Offset = 0;

  int i;
  for (i = 0; i < 256; i++) {
    const u8 val = WarpZone[i];
    VRAM_Buffer1[i] = val;
    if (val == 0) {
      break;
    }
  }

  assert_smb_crashbug(i < 256, "An infinite loop would've occurred in the original game");

  // Note: The original game would set the offset to a hard-coded value after the loop (36).
  // Here we're just setting it to the actual length of the data.
  VRAM_Buffer1_Offset = i;

  // Bit 7 is always set, so toggle it.
  const u8 idx = warp_zone_control ^ 0x80;
  VRAM_Buffer1[27] = WarpZoneNumbers[idx];
}

static inline void UpsideDownPipe_impl(const byte objoff, const byte val) {
  const struct_yr06r07 sVar6 = GetPipeHeight(objoff);
  const byte bVar3 = sVar6.r06;

  if (AreaObjectLength[objoff] != 0) {
    const byte bVar4 = FindEmptyEnemySlot();
    if (bVar4 != NO_AVAIL_ENEMY_SLOT) {
      SetupPiranhaPlant(A_PIRANHA_PLANT_SMB2J, bVar4, val);
      const byte cVar1 = bVar3 * 0x10 + Enemy_Y_Position[bVar4];
      const byte bVar2 = cVar1 - 10;
      Enemy_Y_Position[bVar4] = bVar2;
      PiranhaPlantDownYPos[bVar4] = bVar2;
      PiranhaPlantUpYPos[bVar4] = cVar1 + 0xe;
      PiranhaPlant_MoveFlag[bVar4] = PiranhaPlant_MoveFlag[bVar4] + 1;
    }
  }

  // bVar3 is 0..7, and val is 1 or 4

  assert_eq_assumption(sVar6.y < 2, true);

  const bool left_side = sVar6.y % 2 != 0;

  const u8 top_metatile   = left_side ? MT_PIPE_VERT_WARP_TL : MT_PIPE_VERT_WARP_TR;
  const u8 under_metatile = left_side ? MT_PIPE_VERT_UNDER_L : MT_PIPE_VERT_UNDER_R;

  RenderUnderPart(under_metatile, val, bVar3 - 1);
  if (bVar3 > 0) {
    MetatileBuffer[val + bVar3] = top_metatile;
  } else {
    MetatileBuffer[val + 1] = top_metatile;
  }
}

// SM2DATA2+SM2DATA4:c470
// Signature: [X] -> []
void UpsideDownPipe_High(const byte objoff) {
  UpsideDownPipe_impl(objoff, 1);
}


// SM2DATA2+SM2DATA4:c475
// Signature: [X] -> []
void UpsideDownPipe_Low(const byte objoff) {
  UpsideDownPipe_impl(objoff, 4);
}

// SM2DATA2+SM2DATA4:c5be
// Signature: [] -> []
void WindOn(void) {
  WindFlag = 1;
}


// SM2DATA2+SM2DATA4:c5c2
// Signature: [] -> []
void WindOff(void) {
  WindFlag = 0;
}

#endif
