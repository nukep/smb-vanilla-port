#ifndef SMBCORE_TYPES_H
#define SMBCORE_TYPES_H

#define BUTTON_A 0x80
#define BUTTON_B 0x40
#define BUTTON_SELECT 0x20
#define BUTTON_START 0x10
#define BUTTON_U 0x08
#define BUTTON_D 0x04
#define BUTTON_L 0x02
#define BUTTON_R 0x01

#define BLOCK_BUFFER_1_OFFSET 0x00
#define BLOCK_BUFFER_2_OFFSET 0xd0

// Note that `i` is modulo 64 for bounding boxes, hence the `(byte)` cast.

#define BBOX_TOPLEFT_X(i)  BoundingBoxCoords[(byte)((i)*4) + 0]
#define BBOX_TOPLEFT_Y(i)  BoundingBoxCoords[(byte)((i)*4) + 1]
#define BBOX_BOTRIGHT_X(i) BoundingBoxCoords[(byte)((i)*4) + 2]
#define BBOX_BOTRIGHT_Y(i) BoundingBoxCoords[(byte)((i)*4) + 3]

#define NOWRAP_BBOX_TOPLEFT_X(i)  BoundingBoxCoords[(i)*4 + 0]
#define NOWRAP_BBOX_TOPLEFT_Y(i)  BoundingBoxCoords[(i)*4 + 1]
#define NOWRAP_BBOX_BOTRIGHT_X(i) BoundingBoxCoords[(i)*4 + 2]
#define NOWRAP_BBOX_BOTRIGHT_Y(i) BoundingBoxCoords[(i)*4 + 3]

#define _sprite_offset_assert(offset) assert_eq_assumption((offset) % 4, 0),
// #define _sprite_offset_assert(offset)

// Calculate a sprite offset that wraparounds: offset + n*4, modulo 256.
//
// NES note: The sprite data is page $0200 in memory. It's 256 bytes.
// The accesses should be constrained there, but edge cases could possibly occur
// in the SPRITE_* macros we have where it goes into $0300.
// (TODO: find such cases)
//
// It's common to see something like this in the disassembly:
//
//     STA $021A, Y
//
// which would access the 5th tile's attribute component ($021A = $0200 + 6*4 + 2).
// The Y register is a multiple of 4 that offsets this.
// But if Y is sufficiently large, it can cross into page $0300, which contains the VRAM buffer.
//
// Because of that, we're careful about wrapping the value whenever the NES does.
#define SPRITE_calculate_wrap(offset, n) ((byte)((offset) + (n)*4))

#define SPRITE_Y(offset, n)    (_sprite_offset_assert(offset) Sprite_Data[(byte)(offset) + (n)*4 + 0])
#define SPRITE_TILE(offset, n) (_sprite_offset_assert(offset) Sprite_Data[(byte)(offset) + (n)*4 + 1])
#define SPRITE_ATTR(offset, n) (_sprite_offset_assert(offset) Sprite_Data[(byte)(offset) + (n)*4 + 2])
#define SPRITE_X(offset, n)    (_sprite_offset_assert(offset) Sprite_Data[(byte)(offset) + (n)*4 + 3])

// Keeps in the $0200 page and never leaves.

#define SPRITE_Y_strict(offset, n) (_sprite_offset_assert(offset) Sprite_Data[(byte)((offset) + (n)*4 + 0)])
#define SPRITE_X_strict(offset, n) (_sprite_offset_assert(offset) Sprite_Data[(byte)((offset) + (n)*4 + 3)])

// semistrict is like strict, but the component part may be out of bounds.

#define SPRITE_TILE_semistrict(offset, n) (_sprite_offset_assert(offset) Sprite_Data[(byte)((offset) + (n)*4) + 1])
#define SPRITE_ATTR_semistrict(offset, n) (_sprite_offset_assert(offset) Sprite_Data[(byte)((offset) + (n)*4) + 2])
#define SPRITE_X_semistrict(offset, n) (_sprite_offset_assert(offset) Sprite_Data[(byte)((offset) + (n)*4) + 3])

#define SPRITE_Y_OFFSCREEN 0xf8


#define SPRATTR_FLIPVERT 0x80
#define SPRATTR_FLIPHORZ 0x40
#define SPRATTR_DRAWBEHIND 0x20
#define SPRATTR_USED_MASK (~0x1c)

enum ADDRCTRL {
  ADDRCTRL_VRAM_BUFFER1 = 0,
  ADDRCTRL_WATERPALETTEDATA = 1,
  ADDRCTRL_GROUNDPALETTEDATA,
  ADDRCTRL_UNDERGROUNDPALETTEDATA,
  ADDRCTRL_CASTLEPALETTEDATA,

  ADDRCTRL_VRAM_BUFFER2 = 6,
  ADDRCTRL_VRAM_BUFFER2_unused,

  ADDRCTRL_BOWSERPALETTEDATA = 8,
  ADDRCTRL_DAYSNOWPALETTEDATA,
  ADDRCTRL_NIGHTSNOWPALETTEDATA,
  ADDRCTRL_MUSHROOMPALETTEDATA,
};

enum ADDRCTRL_SMB1 {
  ADDRCTRL_SMB1_VRAM_PAGE=5,

  ADDRCTRL_SMB1_THANKYOUMARIO = 12,
  ADDRCTRL_SMB1_THANKYOULUIGI,
  ADDRCTRL_SMB1_BUTOURPRINCESSISINANOTHERCASTLE,
  ADDRCTRL_SMB1_YOURQUESTISOVER,
  ADDRCTRL_SMB1_WEPRESENTYOUANEWQUEST,
  ADDRCTRL_SMB1_PUSHBUTTONB,
  ADDRCTRL_SMB1_TOSELECTAWORLD,
};

enum ADDRCTRL_SMB2J {
  ADDRCTRL_SMB2J_TITLESCREENGFXDATA=5,

  ADDRCTRL_SMB2J_THANKYOUMESSAGE = 12,
  ADDRCTRL_SMB2J_BUTOURPRINCESSISINANOTHERCASTLE,
  ADDRCTRL_SMB2J_UNUSEDATTRIBDATA,

  ADDRCTRL_SMB2J_FINALROOMPALETTE,
  ADDRCTRL_SMB2J_THANKYOUMESSAGEFINAL,
  ADDRCTRL_SMB2J_PEACEISPAVED,
  ADDRCTRL_SMB2J_WITHKINGDOMSAVED,
  ADDRCTRL_SMB2J_HURRAH,
  ADDRCTRL_SMB2J_OURONLYHERO,
  ADDRCTRL_SMB2J_THISENDSYOURTRIP,
  ADDRCTRL_SMB2J_OFALONGFRIENDSHIP,
  ADDRCTRL_SMB2J_POINTSADDED,
  ADDRCTRL_SMB2J_FOREACHPLAYERLEFT,

  ADDRCTRL_SMB2J_DISKERRORMAIN,
  ADDRCTRL_SMB2J_DISKSCREENPALETTE,
  ADDRCTRL_SMB2J_PRINCESSPEACHSROOM,

  ADDRCTRL_SMB2J_MENUCURSORTEMPLATE,

  // Note: These two are used in SMB2J subroutines that are not ported over yet
  ADDRCTRL_SMB2J_FANTASYWORLD9,
  ADDRCTRL_SMB2J_SUPERPLAYER,
};


// Draw vertically
#define DRAW_FLAG_VERTICAL 0x80

// Run-length encoding
#define DRAW_FLAG_RLE 0x40

static inline void vram_buffer1_draw(u16 ppu_addr, bool vertical, int count, const u8 *items) {
  const u8 flags = (vertical ? DRAW_FLAG_VERTICAL : 0);
  const u8 vramoff = VRAM_Buffer1_Offset;

  VRAM_Buffer1[vramoff + 0] = ppu_addr >> 8;
  VRAM_Buffer1[vramoff + 1] = ppu_addr & 0xff;
  VRAM_Buffer1[vramoff + 2] = flags | (count & 0x3f);
  for (int i = 0; i < count; i++) {
    VRAM_Buffer1[vramoff + 3 + i] = items[i];
  }
  VRAM_Buffer1[vramoff + 3 + count] = 0;
  VRAM_Buffer1_Offset += 3 + count;
}

static inline void vram_buffer1_rle(u16 ppu_addr, bool vertical, int count, u8 value) {
  const u8 flags = DRAW_FLAG_RLE | (vertical ? DRAW_FLAG_VERTICAL : 0);
  const u8 vramoff = VRAM_Buffer1_Offset;
  VRAM_Buffer1[vramoff + 0] = ppu_addr >> 8;
  VRAM_Buffer1[vramoff + 1] = ppu_addr & 0xff;
  VRAM_Buffer1[vramoff + 2] = flags | (count & 0x3f);
  VRAM_Buffer1[vramoff + 3] = value;
  VRAM_Buffer1[vramoff + 4] = 0;
  VRAM_Buffer1_Offset += 4;
}

#ifdef __cplusplus

  static inline void vram_buffer1_draw_int(u16 ppu_addr, bool vertical, int count, const int *items) {
    // This exists solely because of the VRAM1_DRAW macro. C++ forbids integer narrowing in constant literals. In C, this wouldn't be necessary.
    u8 arr[count];
    for (int i = 0; i < count; i++) {
      arr[i] = items[i];
    }

    vram_buffer1_draw(ppu_addr, vertical, count, &arr[0]);
  }

#define _VRAM_DRAW_COUNT(...) (sizeof((const int[]){__VA_ARGS__}) / sizeof(int))

// Draws a list of items to VRAM_Buffer1.
// Assumes no wraparound behavior
#define VRAM1_DRAW(ppu_addr, ...) \
  vram_buffer1_draw_int(ppu_addr, false, _VRAM_DRAW_COUNT(__VA_ARGS__), (const int[]){ __VA_ARGS__ })

#define VRAM1_DRAW_VERTICAL(ppu_addr, ...) \
vram_buffer1_draw_int(ppu_addr, true, _VRAM_DRAW_COUNT(__VA_ARGS__), (const int[]){ __VA_ARGS__ })

#else

#define _VRAM_DRAW_COUNT(...) (sizeof((const u8[]){__VA_ARGS__}) / sizeof(u8))

// Draws a list of items to VRAM_Buffer1.
// Assumes no wraparound behavior
#define VRAM1_DRAW(ppu_addr, ...) \
  vram_buffer1_draw(ppu_addr, false, _VRAM_DRAW_COUNT(__VA_ARGS__), (const u8[]){ __VA_ARGS__ })

#define VRAM1_DRAW_VERTICAL(ppu_addr, ...) \
  vram_buffer1_draw(ppu_addr, true, _VRAM_DRAW_COUNT(__VA_ARGS__), (const u8[]){ __VA_ARGS__ })

#endif


// Draws a single item "length" times to VRAM_Buffer1. Run-length encoding.
// Assumes no wraparound behavior
#define VRAM1_DRAW_RLE(ppu_addr, length, value) \
  vram_buffer1_rle(ppu_addr, false, length, value)

// Get the PPU address for the tile at nametable 0, position (x, y).
#define PPU_ADDR_NT0_XY(x, y) (0x2000 | ((y)*32) | (x))

#define PPU_ADDR_PALETTE_BG(palette, i) (0x3f00 | ((palette)*4 + (i)))
#define PPU_ADDR_PALETTE_SPR(palette, i) (0x3f10 | ((palette)*4 + (i)))

// The status bar takes up this many metatiles worth of space
#define MT_Y_TOP_MARGIN 2

static inline u16 MTX_MTY_TO_BLOCKOFF(const u16 mt_x, const u16 mt_y) {
  const u16 off = (mt_x % 32) < 16 ? BLOCK_BUFFER_1_OFFSET : BLOCK_BUFFER_2_OFFSET;

  return off + (mt_x % 16) + (mt_y & 0xf) * 16;
}

static inline u8 MTX_TO_R06(const u16 mt_x) {
  return MTX_MTY_TO_BLOCKOFF(mt_x, 0);
}

static inline u16 R06_TO_MTX_lossy(const u8 r06) {
  if (r06 < BLOCK_BUFFER_2_OFFSET) {
    return r06;
  } else {
    return 16 + r06 - BLOCK_BUFFER_2_OFFSET;
  }
}

static inline u8 get_metatile(const u16 mt_x, const u16 mt_y) {
  const u16 blockoff = MTX_MTY_TO_BLOCKOFF(mt_x, mt_y);

  if (blockoff >= 0x1a0) {
    // Block_Buffers overlaps with other variables, and they're accidentally accessed regularly.
    // This access would be out of bounds
    // Read whichever variable would be read in the original memory layout

    // cannot be >= 0x1d0
    assert_eq_assumption(blockoff < 0x1d0, true);

#define X(addr, var) if (blockoff == (addr)-0x500) { return var; }
#define XARRAY(addr, var) if (blockoff >= (addr)-0x500) { return var[blockoff - ((addr) - 0x500)]; }

    // mt_y = 15

    X(0x06CF, DuplicateObj_Offset);
    X(0x06CE, FireballCounter);
    X(0x06CD, EnemyFrenzyQueue);
    X(0x06CC, SecondaryHardMode);
    X(0x06CB, EnemyFrenzyBuffer);

    // mt_y = 14

    XARRAY(0x06BE, Misc_Collision_Flag);
    X(0x06BC, BrickCoinTimerFlag);
    X(0x06B7, JumpCoinMiscOffset);

    // mt_y = 13

    XARRAY(0x06AE, HammerEnemyOffset);
    XARRAY(0x06A1, MetatileBuffer);
    X(0x06A0, BlockBufferColumnPos);

#undef XARRAY
#undef X

  }
  return Block_Buffers[blockoff];
}

static inline void set_metatile(const u16 mt_x, const u16 mt_y, const u8 metatile) {
  const u16 blockoff = MTX_MTY_TO_BLOCKOFF(mt_x, mt_y);
  if (blockoff >= 0x1a0) {
    warning("SET METATILE OVERFLOW: (%d,%d) <- 0x%02X\n", mt_x, mt_y, metatile);
  }
  Block_Buffers[blockoff] = metatile;
}


#endif
