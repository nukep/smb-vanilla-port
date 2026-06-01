#include "types.h"
#include "vars.h"

#include "area.h"


// If enabled, fixes a bug where if CurrentPageLoc is > 0x82, modulo 3 is not calculated.
// This bug is impractical if not impossible to execute in unmodified ROMs,
// but is still potentially achievable in modified levels.
//
// In practice, CurrentPageLoc only goes up to 24 in unmodified ROMs without jumping over the flagpole.
// It takes between 4 to 5 time units to travel 1 page location by running.
// To get from page 24 to 0x82, the player would travel 106 pages.
// If the player ran nonstop from page 24 to 0x82, it would take between 424 to 530 time units.
#define BUG_FIX_PAGELOC


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
static void AreaStyleObject(byte param_1);
static void TreeLedge(byte param_1);
static void NoUnder(byte param_1, byte param_2);
static void PulleyRopeObject(byte param_1);
static void CastleObject(byte param_1);
static void WaterPipe(byte param_1);
static void IntroPipe(byte param_1);
static void ExitPipe(byte param_1);
static struct_yc RenderSidewaysPipe(byte param_1, byte param_2);
static void SetupPiranhaPlant(byte param_1, byte param_2, byte param_3);
static void VerticalPipe(byte param_1, byte param_2);
static struct_yr06r07 GetPipeHeight(byte param_1);
static struct_xc FindEmptyEnemySlot(void);
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
static byte GetAreaObjectID(byte param_1);
static void Hole_Empty(byte param_1);
static byte RenderUnderPart(byte param_1, byte param_2, byte param_3);
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
    // note: setting this is likely not needed
    // setting to random values doesn't fail regression tests
    ObjectOffset = 0xff;
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
    MetatileBuffer[i] = 0;
  }

  if (BackgroundScenery != 0) {
    // NES note: If the page location is > 0x82, it breaks a loop that calculates modulo 3.

#ifdef BUG_FIX_PAGELOC
    const byte bVar44 = CurrentPageLoc % 3;

    const byte tmp2 = BSceneDataOffsets[BackgroundScenery - 1] + bVar44 * 16;
    const byte back_scenery_data = BackSceneryData[tmp2 + CurrentColumnPos];
#else
    const byte bVar44 = CurrentPageLoc <= 0x82 ? CurrentPageLoc % 3 : CurrentPageLoc;

    const byte v1 = bVar44 * 0x10;
    const byte v2 = BSceneDataOffsets[BackgroundScenery - 1];
    const bool bVar7 = (bVar44 & 0x10) != 0;

    const byte tmp2 = (v1 + v2 + bVar7) + ((u16)v1 + (u16)v2 + (u16)bVar7 >= 0x100);
    const byte back_scenery_data = BackSceneryData[tmp2 + CurrentColumnPos];
#endif

    if (back_scenery_data != 0) {
      const byte type = back_scenery_data & 0xf;
      const byte mt_y = back_scenery_data >> 4;

      byte metatile_offset = (type - 1) * 3;
      if (type == 0) {
        // NES note: This shouldn't normally happen.
        // This is 0xfe instead of 0xfd, because of the carry bit from ASL.
        metatile_offset = 0xfe;
      }

      for (int i = 0; i < 3; i++) {
        if (mt_y+i == 11) {
          break;
        }
        MetatileBuffer[mt_y + i] = BackSceneryMetatiles[(byte)(metatile_offset + i)];
      }
    }
  }

  if (ForegroundScenery != 0) {
    byte bVar44 = FSceneDataOffsets[ForegroundScenery - 1];
    for (int i = 0; i < 13; i++) {
      if (ForeSceneryData[bVar44] != 0) {
        MetatileBuffer[i] = ForeSceneryData[bVar44];
      }
      bVar44 += 1;
    }
  }

  // RendTerr
  {
    byte mt = TerrainMetatiles[AreaType];

    if (CloudTypeOverride != 0) {
      mt = 0x88;
    }

    // Special exception for water levels in world 8
    if ((AreaType == 0) && (WorldNumber == 7)) {
      mt = ssw(0x62, 0x63);
    }

    const byte bitidx = (byte)(TerrainControl << 1);

    // a 13-bit bitfield
    u16 bits = LOAD_16(TerrainRenderBits[bitidx+1], TerrainRenderBits[bitidx]);

    if (CloudTypeOverride != 0) {
      // Render 0-7, and 11
      bits &= 0x08ff;
    }

    for (int j = 0; j < 13; j++) {
      if ((AreaType == 2) && (j >= 11)) {
        mt = ssw(0x54, 0x6b);
      }

      if ((bits & (1 << j)) != 0) {
        MetatileBuffer[j] = mt;
      }
    }
  }

  // RendBBuf

  ProcessAreaData();

  // Inlined: GetBlockBufferAddr
  // Did it this way to use the Block_Buffers array directly

  const u16 offset = get_block_buffer_offset(BlockBufferColumnPos);

  for (int i = 0; i < 13; i++) {
    const byte mt = MetatileBuffer[i];
    const bool cond = mt >= BlockBuffLowBounds[mt >> 6];

    Block_Buffers[offset + (i*0x10)] = cond ? mt : 0;
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
  case DECODEAREADATA_VERTICALPIPE_2:
    VerticalPipe(objoff, bVar1);
    return true;

  case DECODEAREADATA_AREASTYLEOBJECT:
    AreaStyleObject(objoff);
    return true;

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
  byte bVar1 = 5;
  do {
    bVar1 -= 1;
    if (bVar1 >= 0x80) {
      EnemyFrenzyQueue = FrenzyIDData[param_1 - 8];
      return;
    }
  } while (FrenzyIDData[param_1 - 8] != Enemy_ID[bVar1]);
  EnemyFrenzyQueue = 0;
}


// SMB:9740
// SM2MAIN:7597
// Signature: [X] -> []
void AreaStyleObject(const byte param_1) {
  switch (AreaStyle) {
  case AREASTYLEOBJECT_TREELEDGE:
    TreeLedge(param_1);
    return;

  case AREASTYLEOBJECT_MUSHROOMLEDGE:
#ifdef SMB1_MODE
    MushroomLedge(param_1);
#endif
#ifdef SMB2J_MODE
    CloudLedge(param_1);
#endif
    return;

  case AREASTYLEOBJECT_BULLETBILLCANNON:
    BulletBillCannon(param_1);
    return;

  default:
    jmpengine_overflow(AreaStyle);
    return;
  }
}


// SMB:974c
// SM2MAIN:75a3
// Signature: [X] -> []
void TreeLedge(const byte param_1) {
  const struct_yr07 sVar2 = GetLrgObjAttrib(param_1);
  const byte bVar1 = sVar2.r07;

  const u8 areaobjlen = AreaObjectLength[param_1];
  if (areaobjlen == 0) {
    NoUnder(0x18, bVar1);
    return;
  }

  if (areaobjlen >= 0x80) {
    AreaObjectLength[param_1] = sVar2.y;
    if ((CurrentPageLoc | CurrentColumnPos) != 0) {
      NoUnder(0x16, bVar1);
      return;
    }
  }

  MetatileBuffer[bVar1] = 0x17;
  RenderUnderPart(0x4c, bVar1 + 1, 0xf);
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
    MetatileBuffer[0] = PulleyRopeMetatiles[0];
  } else if (AreaObjectLength[param_1] != 0) {
    MetatileBuffer[0] = PulleyRopeMetatiles[1];
  } else {
    MetatileBuffer[0] = PulleyRopeMetatiles[2];
  }
}


// SMB:9806
// SM2MAIN:7652
// Signature: [X] -> []
void CastleObject(const byte param_1) {
  struct_xc sVar6;
  byte bStack0000;

  const struct_yr07 sVar5 = GetLrgObjAttrib(param_1);
  const byte bVar3 = sVar5.y;
  ChkLrgObjFixedLength(param_1, 4);
  byte bVar4 = AreaObjectLength[param_1];
  char cVar1 = 0x0B;
  byte bVar2 = bVar3;
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
      MetatileBuffer[10] = ssw(0x52, 0x50);
    } else if (bVar4 == 2) {
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
}


// SMB:986f
// SM2MAIN:76bb
// Signature: [X] -> []
void WaterPipe(const byte param_1) {
  const struct_yr07 sVar1 = GetLrgObjAttrib(param_1);
  MetatileBuffer[sVar1.r07] = ssw(0x6b, 0x6d);
  MetatileBuffer[sVar1.r07 + 1] = ssw(0x6c, 0x6e);
}


// SMB:9882
// SM2MAIN:76ce
// Signature: [X] -> []
void IntroPipe(const byte param_1) {
  ChkLrgObjFixedLength(param_1, 3);
  const struct_yc sVar2 = RenderSidewaysPipe(param_1, 10);
  if (!sVar2.c) {
    for (int i = 0; i < 7; i++) {
      MetatileBuffer[i] = 0;
    }
    MetatileBuffer[7] = VerticalPipeData[sVar2.y];
  }
}


// SMB:98ab
// SM2MAIN:76f7
// Signature: [X] -> []
void ExitPipe(const byte param_1) {
  ChkLrgObjFixedLength(param_1, 3);
  const struct_yr07 sVar1 = GetLrgObjAttrib(param_1);
  RenderSidewaysPipe(param_1, sVar1.y);
}


// SMB:98b3
// SM2MAIN:76ff
// Signature: [X, Y] -> [Y, C]
struct_yc RenderSidewaysPipe(const byte param_1, const byte param_2) {
  struct_yc sVar4;

  byte bVar3 = param_2 - 1;
  const byte bVar2 = AreaObjectLength[param_1];
  const byte bVar1 = SidePipeShaftData[bVar2];
  if (bVar1 != 0) {
    bVar3 = RenderUnderPart(bVar1, 0, param_2 - 2);
  }
  MetatileBuffer[bVar3] = SidePipeTopPart[bVar2];
  MetatileBuffer[bVar3 + 1] = SidePipeBottomPart[bVar2];
  sVar4.c = bVar1 == 0;
  sVar4.y = bVar2;
  return sVar4;
}


// SMB:N/A (inlined in VerticalPipe)
// SM2MAIN:7772
// Signature: [A, X, r07] -> []
void SetupPiranhaPlant(const byte param_1, const byte param_2, const byte param_3) {
  const u16 xpos = (CurrentPageLoc << 8) + GetAreaObjXPosition() + 8;
  Enemy_X_Position[param_2] = xpos & 0xff;
  Enemy_PageLoc[param_2] = xpos >> 8;

  Enemy_Y_HighPos[param_2] = 1;
  Enemy_Y_Position[param_2] = GetAreaObjYPosition(param_3);

  Enemy_Flag[param_2] = 1;
  Enemy_ID[param_2] = param_1;

  InitPiranhaPlant(param_2);
}


// SMB:98e5
// SM2MAIN:7731
// Signature: [X, r00] -> []
void VerticalPipe(const byte param_1, const byte param_2) {
  struct_xc sVar6;

  const struct_yr06r07 sVar5 = GetPipeHeight(param_1);
  const byte bVar2 = sVar5.r07;
  const byte bVar1 = sVar5.r06;
  byte bStack0000 = sVar5.y;
  if (param_2 != 0) {
    bStack0000 += 4;
  }

  bool check = AreaObjectLength[param_1] != 0;

#ifdef SMB1_MODE
  if (AreaNumber == 0 && WorldNumber == 0) {
    check = false;
  }
#endif

  if (check) {
    sVar6 = FindEmptyEnemySlot();
    if (!sVar6.c) {
      SetupPiranhaPlant(0xd, sVar6.x, bVar2);
    }
  }

  MetatileBuffer[bVar2] = VerticalPipeData[bStack0000];
  RenderUnderPart(VerticalPipeData[bStack0000 + 2], bVar2 + 1, bVar1 - 1);
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
// Signature: [] -> [X, C]
struct_xc FindEmptyEnemySlot(void) {
  struct_xc sVar3;

  byte bVar1 = 0;
  bool bVar2;
  do {
    bVar2 = false;
    if (Enemy_Flag[bVar1] == 0)
      break;
    bVar1 += 1;
    bVar2 = bVar1 >= 5;
  } while (bVar1 != 5);
  sVar3.c = bVar2;
  sVar3.x = bVar1;
  return sVar3;
}


// SMB:9957
// SM2MAIN:779e
// Signature: [X] -> []
void Hole_Water(const byte param_1) {
  ChkLrgObjLength(param_1);
  MetatileBuffer[10] = 0x86;
  RenderUnderPart(0x87, 0xb, 1);
}


// SMB:9968
// SM2MAIN:77af
// Signature: [X] -> []
void QuestionBlockRow_High(const byte param_1) {
  const byte bStack0000 = 3;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xc0;
}


// SMB:996b
// SM2MAIN:77b2
// Signature: [X] -> []
void QuestionBlockRow_Low(const byte param_1) {
  const byte bStack0000 = 7;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xc0;
}


// SMB:9979
// SM2MAIN:77c0
// Signature: [X] -> []
void Bridge_High(const byte param_1) {
  const byte bStack0000 = 6;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xb;
  RenderUnderPart(ssw(0x63, 0x64), bStack0000 + 1, 0);
}


// SMB:997c
// SM2MAIN:77c3
// Signature: [X] -> []
void Bridge_Middle(const byte param_1) {
  const byte bStack0000 = 7;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xb;
  RenderUnderPart(ssw(0x63, 0x64), bStack0000 + 1, 0);
}


// SMB:997f
// SM2MAIN:77c6
// Signature: [X] -> []
void Bridge_Low(const byte param_1) {
  const byte bStack0000 = 9;
  ChkLrgObjLength(param_1);
  MetatileBuffer[bStack0000] = 0xb;
  RenderUnderPart(ssw(0x63, 0x64), bStack0000 + 1, 0);
}


// SMB:9994
// SM2MAIN:77db
// Signature: [X] -> []
void FlagBalls_Residual(const byte param_1) {
  const struct_yr07 sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(ssw(0x6d, 0x6f), 2, sVar1.y);
}


// SMB:999e
// SM2MAIN:77e5
// Signature: [] -> []
void FlagpoleObject(void) {
  MetatileBuffer[0] = ssw(0x24, 0x21);
  RenderUnderPart(ssw(0x25, 0x22), 1, 8);
  MetatileBuffer[10] = ssw(0x61, 0x62);
  const byte bVar1 = GetAreaObjXPosition();
  Enemy_X_Position[5] = bVar1 - 8;
  Enemy_PageLoc[5] = CurrentPageLoc - (bVar1 < 8);
  Enemy_Y_Position[5] = 0x30;
  FlagpoleFNum_Y_Pos = 0xb0;
  Enemy_ID[5] = 0x30;
  Enemy_Flag[5] = Enemy_Flag[5] + 1;
}


// SMB:99d0
// SM2MAIN:7817
// Signature: [] -> []
void EndlessRope(void) {
  RenderUnderPart(0x40, 0, 0xf);
}


// SMB:99d7
// SM2MAIN:781e
// Signature: [X] -> []
void BalancePlatRope(const byte param_1) {
  const byte bStack0000 = param_1;
  RenderUnderPart(0x44, 1, 0xf);
  const struct_yr07 sVar1 = GetLrgObjAttrib(bStack0000);
  RenderUnderPart(0x40, 1, sVar1.y);
}


// SMB:99f2
// SM2MAIN:7839
// Signature: [X] -> []
void RowOfCoins(const byte param_1) {
  const byte bStack0000 = CoinMetatileData[AreaType];
  const struct_ycr07 sVar1 = ChkLrgObjLength(param_1);
  RenderUnderPart(bStack0000, sVar1.r07, 0);
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
  RenderUnderPart(C_ObjectMetatile[param_1 - 2], C_ObjectRow[param_1 - 2], 0);
}


// SMB:9a19
// SM2MAIN:7860
// Signature: [X] -> []
void EmptyBlock(const byte param_1) {
  const struct_yr07 sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(ssw(0xc4, 0xc5), sVar1.r07, 0);
}


// SMB:9a2e
// SM2MAIN:7875
// Signature: [X] -> []
void RowOfBricks(const byte param_1) {
  byte bVar1 = AreaType;
  if (CloudTypeOverride != 0) {
    bVar1 = 4;
  }
  const byte bStack0000 = BrickMetatiles[bVar1];
  const struct_ycr07 sVar2 = ChkLrgObjLength(param_1);
  RenderUnderPart(bStack0000, sVar2.r07, 0);
}


// SMB:9a3e
// SM2MAIN:7885
// Signature: [X] -> []
void RowOfSolidBlocks(const byte param_1) {
  const byte bStack0000 = SolidBlockMetatiles[AreaType];
  const struct_ycr07 sVar1 = ChkLrgObjLength(param_1);
  RenderUnderPart(bStack0000, sVar1.r07, 0);
}


// SMB:9a50
// SM2MAIN:7897
// Signature: [X] -> []
void ColumnOfBricks(const byte param_1) {
  const byte bStack0000 = BrickMetatiles[AreaType];
  const struct_yr07 sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(bStack0000, sVar1.r07, sVar1.y);
}


// SMB:9a59
// SM2MAIN:78a0
// Signature: [X] -> []
void ColumnOfSolidBlocks(const byte param_1) {
  const byte bStack0000 = SolidBlockMetatiles[AreaType];
  const struct_yr07 sVar1 = GetLrgObjAttrib(param_1);
  RenderUnderPart(bStack0000, sVar1.r07, sVar1.y);
}


// SMB:9a69
// SM2MAIN:78b0
// Signature: [X] -> []
void BulletBillCannon(const byte param_1) {
  const struct_yr07 sVar3 = GetLrgObjAttrib(param_1);
  byte bVar1 = sVar3.r07;
  MetatileBuffer[bVar1] = ssw(0x64, 0x65);
  if ((byte)(sVar3.y - 1) < 0x80) {
    MetatileBuffer[(byte)(bVar1 + 1)] = ssw(0x65, 0x66);
    const byte bVar2 = sVar3.y - 2;
    if (bVar2 < 0x80) {
      RenderUnderPart(ssw(0x66, 0x67), bVar1 + 2, bVar2);
    }
  }
  const byte bVar2 = Cannon_Or_Whirlpool_Offset;
  bVar1 = GetAreaObjYPosition(bVar1);
  Cannon_Y_Position_Or_Whirlpool_Length[bVar2] = bVar1;
  Cannon_Or_Whirlpool_PageLoc[bVar2] = CurrentPageLoc;
  bVar1 = GetAreaObjXPosition();
  Cannon_X_Position_Or_Whirlpool_LeftExtent[bVar2] = bVar1;
  Cannon_Or_Whirlpool_Offset = bVar2 + 1;
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
  RenderUnderPart(ssw(0x61, 0x62), StaircaseRowData[StaircaseControl], StaircaseHeightData[StaircaseControl]);
}


// SMB:9ad3
// SM2MAIN:791a
// Signature: [X] -> []
void Jumpspring(const byte param_1) {
  const struct_yr07 sVar4 = GetLrgObjAttrib(param_1);
  const byte bVar1 = sVar4.r07;
  const struct_xc sVar5 = FindEmptyEnemySlot();
  const byte bVar3 = sVar5.x;
  if (SMB2J_ONLY && sVar5.c) {
    return;
  }
  byte bVar2 = GetAreaObjXPosition();
  Enemy_X_Position[bVar3] = bVar2;
  Enemy_PageLoc[bVar3] = CurrentPageLoc;
  bVar2 = GetAreaObjYPosition(bVar1);
  Enemy_Y_Position[bVar3] = bVar2;
  SpriteVarData1[bVar3] = bVar2;
  Enemy_ID[bVar3] = 0x32;
  Enemy_Y_HighPos[bVar3] = 1;
  Enemy_Flag[bVar3] = Enemy_Flag[bVar3] + 1;
  MetatileBuffer[bVar1] = ssw(0x67, 0x68);
  MetatileBuffer[bVar1 + 1] = ssw(0x68, 0x69);
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
  const byte bVar1 = GetAreaObjectID(param_2);
  const byte bStack0000 = BrickQBlockMetatiles[bVar1];
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
  const byte bVar2 = GetAreaObjectID(param_2);
  char cVar1 = 0;
  if (AreaType != 1) {
    cVar1 = ssw(5, 6);
  }
  const byte bStack0000 = BrickQBlockMetatiles[(byte)(cVar1 + bVar2)];
  const struct_yr07 sVar3 = GetLrgObjAttrib(param_1);
  RenderUnderPart(bStack0000, sVar3.r07, 0);
}


// SMB:9b36
// SM2MAIN:797f
// Signature: [r00] -> [Y]
byte GetAreaObjectID(const byte param_1) { return param_1; }


// SMB:9b41
// SM2MAIN:798a
// Signature: [X] -> []
void Hole_Empty(const byte param_1) {
  byte bVar1;

  const struct_ycr07 sVar3 = ChkLrgObjLength(param_1);
  const byte bVar2 = sVar3.y;
  if ((sVar3.c) && (AreaType == 0)) {
    bVar1 = GetAreaObjXPosition();
    Cannon_X_Position_Or_Whirlpool_LeftExtent[Cannon_Or_Whirlpool_Offset] = bVar1 - 0x10;
    Cannon_Or_Whirlpool_PageLoc[Cannon_Or_Whirlpool_Offset] = CurrentPageLoc - (bVar1 < 0x10);
    Cannon_Y_Position_Or_Whirlpool_Length[Cannon_Or_Whirlpool_Offset] = (bVar2 + 2) * 0x10;
    Cannon_Or_Whirlpool_Offset += 1;
    if (Cannon_Or_Whirlpool_Offset >= 5) {
      Cannon_Or_Whirlpool_Offset = 0;
    }
  }
  RenderUnderPart(HoleMetatiles[AreaType], 8, 0xf);
}


// SMB:9b7d
// SM2MAIN:79c6
// Signature: [A, X, Y] -> [X]
byte RenderUnderPart(const byte mt, const byte mt_y, const byte param_3) {
  // Note: Removed AreaObjectHeight global variable ($0735).
  // It's only ever used in this subroutine.

  byte j = mt_y;

  byte count = param_3 + 1;

  if (param_3 > 0x80) {
    count = 1;
  }

  for (int i = 0; i < count; i++) {
    const byte existing_mt = MetatileBuffer[j];

    bool draw_metatile = true;

    if (existing_mt == 0x17 || existing_mt == ssw(0x1a, 0x8b) || existing_mt > 0xc0) {
        draw_metatile = false;
    }

    if (SMB1_ONLY && mt == 0x50 && existing_mt == 0x54) {
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
  return j;
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
    NoUnder(0x19, bVar3);
    return;
  }

  const u8 areaobjlen = AreaObjectLength[param_1];
  if (areaobjlen == 0) {
    NoUnder(0x1b, bVar3);
    return;
  }

  MetatileBuffer[bVar3] = 0x1a;

  // Draw the stem under the mushroom ledge

  const u8 bVar1 = MushroomLedgeHalfLen[param_1];
  if (areaobjlen == bVar1) {
    // Right under the mushroom
    MetatileBuffer[(byte)(bVar3 + 1)] = 0x4f;

    // The rest of the stem
    RenderUnderPart(0x50, bVar3 + 2, 0xf);
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
    NoUnder(0x8a, bVar3);
    return;
  }

  const byte areaobjlen = AreaObjectLength[param_1];
  if (areaobjlen == 0) {
    NoUnder(0x8c, bVar3);
    return;
  }

  MetatileBuffer[bVar3] = 0x8b;
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


// SM2DATA2+SM2DATA4:c470
// Signature: [X] -> []
void UpsideDownPipe_High(const byte param_1) {
  char cVar1;
  byte bVar2;
  byte bVar4;
  struct_xc sVar6;

  byte bStack0000 = 1;
  const struct_yr06r07 sVar7 = GetPipeHeight(param_1);
  const byte bVar3 = sVar7.r06;
  byte bVar5 = bStack0000;
  bStack0000 = sVar7.y;
  if (AreaObjectLength[param_1] != 0) {
    sVar6 = FindEmptyEnemySlot();
    bVar4 = sVar6.x;
    if (!sVar6.c) {
      SetupPiranhaPlant(4, bVar4, bVar5);
      cVar1 = bVar3 * 0x10 + Enemy_Y_Position[bVar4];
      bVar2 = cVar1 - 10;
      Enemy_Y_Position[bVar4] = bVar2;
      CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[bVar4] = bVar2;
      BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[bVar4] = cVar1 + 0xe;
      SpriteVarData2[bVar4] = SpriteVarData2[bVar4] + 1;
    }
  }
  bVar5 = RenderUnderPart(VerticalPipeData[bStack0000 + 2], bVar5, bVar3 - 1);
  MetatileBuffer[bVar5] = VerticalPipeData[bStack0000];
}


// SM2DATA2+SM2DATA4:c475
// Signature: [X] -> []
void UpsideDownPipe_Low(const byte param_1) {
  char cVar1;
  byte bVar2;
  byte bVar4;
  struct_xc sVar7;

  byte bStack0000 = 4;
  const struct_yr06r07 sVar6 = GetPipeHeight(param_1);
  const byte bVar3 = sVar6.r06;
  byte bVar5 = bStack0000;
  bStack0000 = sVar6.y;
  if (AreaObjectLength[param_1] != 0) {
    sVar7 = FindEmptyEnemySlot();
    bVar4 = sVar7.x;
    if (!sVar7.c) {
      SetupPiranhaPlant(4, bVar4, bVar5);
      cVar1 = bVar3 * 0x10 + Enemy_Y_Position[bVar4];
      bVar2 = cVar1 - 10;
      Enemy_Y_Position[bVar4] = bVar2;
      CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[bVar4] = bVar2;
      BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[bVar4] = cVar1 + 0xe;
      SpriteVarData2[bVar4] = SpriteVarData2[bVar4] + 1;
    }
  }
  bVar5 = RenderUnderPart(VerticalPipeData[bStack0000 + 2], bVar5, bVar3 - 1);
  MetatileBuffer[bVar5] = VerticalPipeData[bStack0000];
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
