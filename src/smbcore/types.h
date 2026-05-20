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

#define BLOCK_BUFFER_PAGE 0x0500
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

#endif
