#include "mario.h"

#include "base.h"

#include "smbcore/interface.h"

struct sprite {
  struct SMB_tile tile;
  bool draw_behind;
};

static inline void transfer_sprite_data(struct sprite sprites[64], const byte *data) {
  for (int i = 0; i < 64; i++) {
    sprites[i].tile.y = data[i * 4 + 0] + 1;
    sprites[i].tile.tileidx = data[i * 4 + 1];
    byte attr = data[i * 4 + 2];
    sprites[i].tile.x = data[i * 4 + 3];

    sprites[i].tile.paletteidx = (attr & 0x03) + 4;
    sprites[i].tile.flip_horz = (attr & 0x40) != 0;
    sprites[i].tile.flip_vert = (attr & 0x80) != 0;

    sprites[i].tile.extra_type = TILE_TYPE_SPRITE;
    sprites[i].tile.extra_spriteidx = i;

    sprites[i].draw_behind = (attr & 0x20) != 0;
  }
}

void draw_graphics(const struct sprite sprites[64]);

