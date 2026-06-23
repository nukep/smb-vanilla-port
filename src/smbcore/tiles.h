#ifndef TILES_H
#define TILES_H

enum metatiles {
  MT_NULL = 0,

  MT_PIPE_VERT_WARP_TL = 0x10,
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

