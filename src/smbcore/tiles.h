#ifndef TILES_H
#define TILES_H

enum metatiles {
  MT_0 = 0,

  MT_BUSH_L = 0x02,
  MT_BUSH_M,
  MT_BUSH_R,

  MT_MOUNTAIN_L,
  MT_MOUNTAIN_DOTS_1,
  MT_MOUNTAIN_TOP,
  MT_MOUNTAIN_R,
  MT_MOUNTAIN_DOTS_2,
  MT_MOUNTAIN_GREEN,

  MT_BRIDGE_CHAIN = 0x0c,
  MT_TREE_TALL_1,
  MT_TREE_SHORT,
  MT_TREE_TALL_2,

  MT_PIPE_VERT_WARP_TL,
  MT_PIPE_VERT_WARP_TR,
  MT_PIPE_VERT_DECO_TL,
  MT_PIPE_VERT_DECO_TR,
  MT_PIPE_VERT_UNDER_L,
  MT_PIPE_VERT_UNDER_R,

  MT_unk=0x18,
#ifdef SMB1_MODE
  MT_unk1,
  MT_unk2,
  MT_unk3,
#endif

  // 1c/19
  MT_PIPE_SIDEWAYS_TL,
  MT_PIPE_SIDEWAYS_MIDDLE_T,

  // top of connnected pipe (as found at the beginning of 1-2 before Mario goes to underground)
  // 1e/1b
  MT_PIPE_CONNECTED_T,
  MT_PIPE_SIDEWAYS_BL,
  MT_PIPE_SIDEWAYS_MIDDLE_B,
  MT_PIPE_CONNECTED_B,

  MT_CORAL,

  MT_PULLEY_ROPE_HORZ=0x41,   // --
  MT_PULLEY_ROPE_TL,          // |-
  MT_PULLEY_ROPE_TR,          // -|

  MT_CASTLE_TOP=0x45,
  MT_CASTLE_WINDOW_L,
  MT_CASTLE_BRICK,
  MT_CASTLE_WINDOW_R,
  MT_CASTLE_NOTCH,
  MT_CASTLE_DOOR_T,
  MT_CASTLE_DOOR_B,

  MT_FENCE = 0x4d,
  MT_TREE_TRUNK,

  // MT_BRICK_2 has a white outline on the top

#ifdef SMB2J_MODE
  MT_BRICK_2 = 0x4f,
#endif
#ifdef SMB1_MODE
  MT_BRICK_2 = 0x51,
#endif
  MT_BRICK,

#ifdef SMB1_MODE
  MT_STONE = 0x54,
#endif

  MT_unk4=0x60,
#ifdef SMB2J_MODE
  MT_unk5,
#endif

  // 61/62
  MT_STAIR_BLOCK,

  // 62/63
  MT_CASTLE_INSIDE_WALL,
  MT_unk7,

  MT_BULLETBILL_CANNON_T,
  MT_BULLETBILL_CANNON_BODY,
  MT_BULLETBILL_CANNON_B,

  MT_JUMPSPRING_T,
  MT_JUMPSPRING_B,

  // 69/6a
  MT_UNDERWATER_GROUND,
#ifdef SMB2J_MODE
  MT_STONE,
#endif

  MT_CLOUD_TL=0x80,
  MT_CLOUD_TM,
  MT_CLOUD_TR,
  MT_CLOUD_BL,
  MT_CLOUD_BM,
  MT_CLOUD_BR,

  MT_WATER_TOP,
  MT_WATER_BLANK,

  MT_CLOUD_BLOCK,
  MT_BRIDGE_BLOCK,

  MT_unk13=0xc1,
#ifdef SMB2J_MODE
  MT_unk14,
#endif

  MT_COIN,
  MT_COIN_UNDERWATER,
  MT_unk15,
  MT_AXE,
};


#ifdef SMB1_MODE
static const byte BrickQBlockMetatiles[] = {
  0xc1, 0xc0, 0x5f, 0x60,                   // used by question blocks
  0x55, 0x56, 0x57, 0x58, 0x59,             // used by ground level types
  0x5a, 0x5b, 0x5c, 0x5d, 0x5e,             // used by other level types
};
#endif

#ifdef SMB2J_MODE
static const byte BrickQBlockMetatiles[] = {
  0xc1, 0xc2, 0xc0, 0x5e, 0x5f, 0x60, 0x61, // used by question blocks
  0x52, 0x53, 0x54, 0x55, 0x56, 0x57,       // used by ground level bricks
  0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d,       // used by other level bricks
};
#endif

#endif

