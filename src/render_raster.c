// Functions to render SMB to a 256x240 RGB buffer in software.
// About as simple as it gets.

#include "mario.h"
#include "render_raster.h"

#include <string.h>

typedef unsigned char byte;

struct Pixel {
  byte r,g,b;
};

struct Tile {
  byte val[8][8];
};

struct SMBraster {
  struct Pixel *pixels;
  size_t pixels_stride;
  byte palette_indices[32];
  struct Pixel palette[0x40];
  struct Tile tiles[0x200];
};

size_t SMBraster_size(void) {
  return sizeof(struct SMBraster);
}

bool SMBraster_init(struct SMBraster *r) {
  memset(r, 0, sizeof(struct SMBraster));
  return true;
}
void SMBraster_fini(struct SMBraster *r) {

}

// Upload a list of 64 RGB values. The data is copied.
void SMBraster_provide_palette_lookup(struct SMBraster *r, const unsigned char *rgb) {
  memcpy(r->palette, rgb, sizeof(r->palette));
}

void SMBraster_update_palette(struct SMBraster *r, const unsigned char *palette_indices) {
  memcpy(r->palette_indices, palette_indices, 32);
}

void SMBraster_update_pattern_tables(struct SMBraster *r, const unsigned char *chrrom) {
  for (int tileidx = 0; tileidx < 512; tileidx++) {
    struct Tile *t = r->tiles + tileidx;
    const byte *buf = chrrom + tileidx * 0x10;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        const byte hibit = (buf[i + 8] >> (7 - j)) & 1;
        const byte lobit = (buf[i + 0] >> (7 - j)) & 1;
        t->val[i][j] = (hibit << 1) | lobit;
      }
    }
  }
}

void SMBraster_draw_tile(struct SMBraster *r, const struct SMB_tile tile) {
  if (!r->pixels) {
    return;
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int ii = i;
      int jj = j;
      if (tile.flip_horz) {
        jj = 7 - jj;
      }
      if (tile.flip_vert) {
        ii = 7 - ii;
      }
      jj += tile.x;
      ii += tile.y;
      if (ii < 0 || ii >= 240) {
        continue;
      }
      if (jj < 0 || jj >= 256) {
        continue;
      }

      struct Pixel *p = r->pixels + jj + ii * r->pixels_stride;
      byte v = r->tiles[tile.tileidx].val[i][j];
      if (v == 0) {
        continue;
      }

      *p = r->palette[r->palette_indices[tile.paletteidx * 4 + v] & 0x3F];
    }
  }
}


void SMBraster_set_buffer(struct SMBraster *r, unsigned char *rgb_pixels, int stride) {
  r->pixels = rgb_pixels;
  r->pixels_stride = stride;
}

void SMBraster_clear(struct SMBraster *r) {
  // fill every pixel with the background color
  for (int i = 0; i < 256*240; i++) {
    r->pixels[i] = r->palette[r->palette_indices[0]];
  }
}
