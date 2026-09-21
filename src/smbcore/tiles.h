#ifndef TILES_H
#define TILES_H

enum metatiles {
  MT_0 = 0,
  MT_BLACK,

  MT_BUSH_L,
  MT_BUSH_M,
  MT_BUSH_R,

  MT_MOUNTAIN_L,
  MT_MOUNTAIN_DOTS_1,
  MT_MOUNTAIN_TOP,
  MT_MOUNTAIN_R,
  MT_MOUNTAIN_DOTS_2,
  MT_MOUNTAIN_GREEN,

  MT_BRIDGE_RAILING,

  MT_BOWSERBRIDGE_CHAIN,
  MT_TREE_TALL_1,
  MT_TREE_SHORT,
  MT_TREE_TALL_2,

  // 10
  MT_PIPE_VERT_WARP_TL,
  MT_PIPE_VERT_WARP_TR,
  MT_PIPE_VERT_DECO_TL,
  MT_PIPE_VERT_DECO_TR,
  MT_PIPE_VERT_UNDER_L,
  MT_PIPE_VERT_UNDER_R,

  // 16
  MT_TREELEDGE_L,
  MT_TREELEDGE_M,
  MT_TREELEDGE_R,

#ifdef SMB1_MODE
  MT_MUSHROOMLEDGE_L,
  MT_MUSHROOMLEDGE_M,
  MT_MUSHROOMLEDGE_R,
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

  // 22/1f
  MT_CORAL,

  MT_SPECIAL_BLOCKHIT,

  MT_FLAGPOLE_T,
  MT_FLAGPOLE_M,

  MT_SPECIAL_VINE,

  // no metatiles from here until 0x40

  MT_ROPE_VERT = 0x40,        // |
  MT_PULLEY_ROPE_HORZ,        // --
  MT_PULLEY_ROPE_TL,          // |-
  MT_PULLEY_ROPE_TR,          // -|
  MT_ROPE_NONE,

  MT_CASTLE_TOP,
  MT_CASTLE_WINDOW_L,
  MT_CASTLE_BRICK,
  MT_CASTLE_WINDOW_R,
  MT_CASTLE_NOTCH,
  MT_CASTLE_DOOR_T,
  MT_CASTLE_DOOR_B,

  MT_TREELEDGE_TRUNK,

  MT_FENCE,
  MT_TREE_TRUNK,

#ifdef SMB1_MODE
  MT_MUSHROOMLEDGE_STEM_T,
  MT_MUSHROOMLEDGE_STEM_UNDER,
#endif

  // MT_BRICK_2 has a white outline on the top
  // 51/4f
  MT_BRICK_2,
  MT_BRICK,
  MT_BRICK_UNUSED,

#ifdef SMB1_MODE
  MT_STONE,
#endif

  // 55/52
  MT_BRICK_2_POWERUP,
#ifdef SMB2J_MODE
  MT_BRICK_2_POISONSHROOM,
#endif
  MT_BRICK_2_VINE,
  MT_BRICK_2_STAR,
  MT_BRICK_2_COINS,
  MT_BRICK_2_1UP,

  // 5a/58
  MT_BRICK_POWERUP,
#ifdef SMB2J_MODE
  MT_BRICK_POISONSHROOM,
#endif
  MT_BRICK_VINE,
  MT_BRICK_STAR,
  MT_BRICK_COINS,
  MT_BRICK_1UP,

  // 5f/5e
  MT_HIDDEN_1COIN,
  MT_HIDDEN_1UP,
#ifdef SMB2J_MODE
  MT_HIDDEN_POISONSHROOM,
  MT_HIDDEN_POWERUP,
#endif

  // 61/62
  MT_STAIR_BLOCK,

  // 62/63
  MT_CASTLE_INSIDE_WALL,
  MT_BRIDGE_BLOCK,

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

  MT_unk18,

  // 6b/6d
  MT_WATERPIPE_T,
  MT_WATERPIPE_B,

  // 6d/6f. Might be residual code
  MT_FLAGBALL,

  // no metatiles from here until 0x80

  MT_CLOUD_TL=0x80,
  MT_CLOUD_TM,
  MT_CLOUD_TR,
  MT_CLOUD_BL,
  MT_CLOUD_BM,
  MT_CLOUD_BR,

  MT_WATER_TOP,
  MT_WATER_BLANK,

  MT_CLOUD_BLOCK,
  MT_BOWSERBRIDGE_BLOCK,

#ifdef SMB2J_MODE
  MT_CLOUDLEDGE_L,
  MT_CLOUDLEDGE_M,
  MT_CLOUDLEDGE_R,
#endif

  // 8a/8d
  MT_unk21,

  // no metatiles from here until 0xc0

  MT_QUESTIONBLOCK_COIN = 0xc0,

  MT_QUESTIONBLOCK_POWERUP,
#ifdef SMB2J_MODE
  MT_QUESTIONBLOCK_POISONSHROOM,
#endif

  // c2/c3
  MT_COIN,
  MT_COIN_UNDERWATER,
  MT_BLOCK_EMPTY,   // appears as a used coin block
  MT_AXE,
  MT_unk20
};

static inline bool metatile_is_itemblock(const u8 mt) {
  switch (mt) {
  case MT_QUESTIONBLOCK_POWERUP:
  case MT_QUESTIONBLOCK_COIN:
  case MT_HIDDEN_1COIN:
  case MT_HIDDEN_1UP:
  case MT_BRICK_2_POWERUP:
  case MT_BRICK_2_VINE:
  case MT_BRICK_2_STAR:
  case MT_BRICK_2_COINS:
  case MT_BRICK_2_1UP:
  case MT_BRICK_POWERUP:
  case MT_BRICK_VINE:
  case MT_BRICK_STAR:
  case MT_BRICK_COINS:
  case MT_BRICK_1UP:
    return true;

#ifdef SMB2J_MODE
  case MT_QUESTIONBLOCK_POISONSHROOM:
  case MT_HIDDEN_POISONSHROOM:
  case MT_HIDDEN_POWERUP:
  case MT_BRICK_2_POISONSHROOM:
  case MT_BRICK_POISONSHROOM:
    return true;
#endif

  default:
    return false;
  }
}

enum tiles {
  TILE_0 = 0, TILE_1, TILE_2, TILE_3, TILE_4, TILE_5, TILE_6, TILE_7, TILE_8, TILE_9,
  TILE_A, TILE_B, TILE_C, TILE_D, TILE_E, TILE_F, TILE_G, TILE_H, TILE_I, TILE_J, TILE_K, TILE_L, TILE_M, TILE_N, TILE_O, TILE_P, TILE_Q, TILE_R, TILE_S, TILE_T, TILE_U, TILE_V, TILE_W, TILE_X, TILE_Y, TILE_Z,

  // 24
  TILE_BLANK_0,
  TILE_BLANK_1,
  TILE_BLANK_2,
  TILE_BLANK_3,
  TILE_DASH,
  TILE_MULTIPLY,
  TILE__0x2a,
  TILE_EXCLAMATION,
  TILE__0x2c,
  TILE__0x2d,
  TILE__0x2e,
  TILE__0x2f,
  TILE__0x30,
  TILE__0x31,
  TILE__0x32,
  TILE__0x33,
  TILE__0x34,
  TILE__0x35,
  TILE__0x36,
  TILE__0x37,
  TILE__0x38,
  TILE__0x39,
  TILE__0x3a,
  TILE__0x3b,
  TILE__0x3c,
  TILE__0x3d,
  TILE__0x3e,
  TILE__0x3f,
  TILE__0x40,
  TILE__0x41,
  TILE__0x42,
  TILE__0x43,
  TILE__0x44,
  TILE__0x45,
  TILE__0x46,
  TILE__0x47,
  TILE__0x48,
  TILE__0x49,
  TILE__0x4a,
  TILE__0x4b,
  TILE__0x4c,
  TILE__0x4d,
  TILE__0x4e,
  TILE__0x4f,
  TILE__0x50,
  TILE__0x51,
  TILE__0x52,
  TILE__0x53,
  TILE__0x54,
  TILE__0x55,
  TILE__0x56,
  TILE__0x57,
  TILE__0x58,
  TILE__0x59,
  TILE__0x5a,
  TILE__0x5b,
  TILE__0x5c,
  TILE__0x5d,
  TILE__0x5e,
  TILE__0x5f,
  TILE__0x60,
  TILE__0x61,
  TILE__0x62,
  TILE__0x63,
  TILE__0x64,
  TILE__0x65,
  TILE__0x66,
  TILE__0x67,
  TILE__0x68,
  TILE__0x69,
  TILE__0x6a,
  TILE__0x6b,
  TILE__0x6c,
  TILE__0x6d,
  TILE__0x6e,
  TILE__0x6f,
  TILE__0x70,
  TILE__0x71,
  TILE__0x72,
  TILE__0x73,
  TILE__0x74,
  TILE__0x75,
  TILE__0x76,
  TILE__0x77,
  TILE__0x78,
  TILE__0x79,
  TILE__0x7a,
  TILE__0x7b,
  TILE__0x7c,
  TILE__0x7d,
  TILE__0x7e,
  TILE__0x7f,
  TILE__0x80,
  TILE__0x81,
  TILE__0x82,
  TILE__0x83,
  TILE__0x84,
  TILE__0x85,
  TILE__0x86,
  TILE__0x87,
  TILE__0x88,
  TILE__0x89,
  TILE__0x8a,
  TILE__0x8b,
  TILE__0x8c,
  TILE__0x8d,
  TILE__0x8e,
  TILE__0x8f,
  TILE__0x90,
  TILE__0x91,
  TILE__0x92,
  TILE__0x93,
  TILE__0x94,
  TILE__0x95,
  TILE__0x96,
  TILE__0x97,
  TILE__0x98,
  TILE__0x99,
  TILE__0x9a,
  TILE__0x9b,
  TILE__0x9c,
  TILE__0x9d,
  TILE__0x9e,
  TILE__0x9f,
  TILE__0xa0,
  TILE__0xa1,
  TILE__0xa2,
  TILE__0xa3,
  TILE__0xa4,
  TILE__0xa5,
  TILE__0xa6,
  TILE__0xa7,
  TILE__0xa8,
  TILE__0xa9,
  TILE__0xaa,
  TILE__0xab,
  TILE__0xac,
  TILE__0xad,
  TILE__0xae,
  TILE__0xaf,
  TILE__0xb0,
  TILE__0xb1,
  TILE__0xb2,
  TILE__0xb3,
  TILE__0xb4,
  TILE__0xb5,
  TILE__0xb6,
  TILE__0xb7,
  TILE__0xb8,
  TILE__0xb9,
  TILE__0xba,
  TILE__0xbb,
  TILE__0xbc,
  TILE__0xbd,
  TILE__0xbe,
  TILE__0xbf,
  TILE__0xc0,
  TILE__0xc1,
  TILE__0xc2,
  TILE__0xc3,
  TILE__0xc4,
  TILE__0xc5,
  TILE__0xc6,
  TILE__0xc7,
  TILE__0xc8,
  TILE__0xc9,
  TILE__0xca,
  TILE__0xcb,
  TILE__0xcc,
  TILE__0xcd,
  TILE__0xce,
  TILE__0xcf,
  TILE__0xd0,
  TILE__0xd1,
  TILE__0xd2,
  TILE__0xd3,
  TILE__0xd4,
  TILE__0xd5,
  TILE__0xd6,
  TILE__0xd7,
  TILE__0xd8,
  TILE__0xd9,
  TILE__0xda,
  TILE__0xdb,
  TILE__0xdc,
  TILE__0xdd,
  TILE__0xde,
  TILE__0xdf,
  TILE__0xe0,
  TILE__0xe1,
  TILE__0xe2,
  TILE__0xe3,
  TILE__0xe4,
  TILE__0xe5,
  TILE__0xe6,
  TILE__0xe7,
  TILE__0xe8,
  TILE__0xe9,
  TILE__0xea,
  TILE__0xeb,
  TILE__0xec,
  TILE__0xed,
  TILE__0xee,
  TILE__0xef,
  TILE__0xf0,
  TILE__0xf1,
  TILE__0xf2,
  TILE__0xf3,
  TILE__0xf4,
  TILE__0xf5,
  TILE__0xf6,
  TILE__0xf7,
  TILE__0xf8,
  TILE__0xf9,
  TILE__0xfa,
  TILE__0xfb,
  TILE__0xfc,
  TILE__0xfd,
  TILE__0xfe,
  TILE__0xff,
};

#endif

