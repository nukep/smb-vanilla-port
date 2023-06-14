// The start of something magical! ✨

#include "foundation.h"

extern "C" {
bool load_smb1(struct SMB_state *state, size_t prg_offset, size_t chr_offset);
void SMB1_Reset();
void SMB1_NMI();

bool load_smb2j(struct SMB_state *state, size_t disk_offset);
void SMB2J_Reset();
void SMB2J_NMI();
}

#include "common.h"

thread_local struct SMB_state *SMB_STATE;

static bool detect_and_load_rom(struct SMB_state *state) {
  byte headerbuf[16];
  if (!read_rom_bytes(state, headerbuf, 16)) {
    return false;
  }
  if (headerbuf[0] == 'N' && headerbuf[1] == 'E' && headerbuf[2] == 'S' && headerbuf[3] == 0x1A) {
    // An INES header. Probably SMB1.
    return load_smb1(state, 0x10, 0x8010);
  }
  if (headerbuf[0] == 'F' && headerbuf[1] == 'D' && headerbuf[2] == 'S' && headerbuf[3] == 0x1A) {
    // An FDS header. Probably SMB2J.
    // TODO: there's an FDS version of SMB1. Maybe handle it?
    return load_smb2j(state, 0x10);
  } else {
    // There are some ROMs that don't include an FDS header, but just the single disk image.
    return load_smb2j(state, 0);
  }
}

size_t SMB_state_size(void) { return sizeof(struct SMB_state); }
void SMB_state_init(struct SMB_state *state, const struct SMB_callbacks *cb) {
  memset(state, 0, sizeof(struct SMB_state));
  state->callbacks = *cb;
  state->start_on_world = 1;
  state->start_on_level = 1;
  detect_and_load_rom(state);
}
void SMB_start_on_level(struct SMB_state *state, byte world, byte level) {
  state->start_on_world = world;
  state->start_on_level = level;
}
int SMB_which_game(const struct SMB_state *state) { return state->which_game; }

byte *SMB_ram(struct SMB_state *state) { return state->rammem; }
byte *SMB_ppuram(struct SMB_state *state) { return state->ppuram; }

void SMB_tick(struct SMB_state *state) {
  // Set a global variable while it's being ticked
  SMB_STATE = state;
  if (state->which_game == GAME_SMB1) {
    if (!state->reset_occurred) {
      SMB1_Reset();
      SMB1_NMI();
      set_world_and_level(state->start_on_world - 1, state->start_on_level - 1);
      state->reset_occurred = true;
    } else {
      SMB1_NMI();
    }
  }
  if (state->which_game == GAME_SMB2J) {
    if (!state->reset_occurred) {
      SMB2J_Reset();
      SMB2J_NMI();
      // this hack doesn't work for smb2j
      set_world_and_level(state->start_on_world - 1, state->start_on_level - 1);
      state->reset_occurred = true;
    } else {
      SMB2J_NMI();
    }
  }
}

static inline void draw_nametable_tile(const struct SMB_state *state, int x, int y, ushort ppu_offset, int tilex,
                                       int tiley) {
  int j = tilex;
  int i = tiley;
  int off = i * 32 + j;
  int tileidx = state->ppuram[ppu_offset + off] + 0x100;
  // Find which part of the pallete to use
  // Look it up in the attribute table

  byte a = state->ppuram[ppu_offset + 0x03c0 + (i / 4) * 8 + (j / 4)];
  a >>= ((j / 2) % 2) * 2;
  a >>= ((i / 2) % 2) * 4;
  a &= 0x03;
  int paletteidx = a;

  struct SMB_tile tile;
  tile.x = x;
  tile.y = y;
  tile.tileidx = tileidx;
  tile.paletteidx = paletteidx;
  tile.flip_horz = false;
  tile.flip_vert = false;

  state->callbacks.draw_tile(state->callbacks.userdata, tile);
}

static inline void draw_nametable_rect(const struct SMB_state *state, int x, int y, ushort ppu_offset, int fromx,
                                       int fromy, int tox, int toy) {
  for (int i = fromy; i < toy; i++) {
    for (int j = fromx; j < tox; j++) {
      draw_nametable_tile(state, x + (j - fromx) * 8, y + (i - fromy) * 8, ppu_offset, j, i);
    }
  }
}

void draw_graphics(struct SMB_state *state) {
  if (state->callbacks.update_palette) {
    // The palette can change even if the screen is off (the background color, namely)
    state->callbacks.update_palette(state->callbacks.userdata, state->ppuram + 0x3F00);
  }

  if (!state->ppu.screen_on) {
    return;
  }
  if (!state->callbacks.draw_tile) {
    return;
  }

  for (int spriteidx = 0; spriteidx < 64; spriteidx++) {
    const struct sprite *s = state->sprites + (63 - spriteidx);
    if (s->draw_behind) {
      state->callbacks.draw_tile(state->callbacks.userdata, s->tile);
    }
  }

  // Status bar
  draw_nametable_rect(state, 0, 0, 0x2000, 0, 0, 32, 4);

  int scroll_off = -(state->scroll_x % 256);
  int scroll_nametable = state->scroll_x / 256;

  if (scroll_nametable == 0) {
    draw_nametable_rect(state, scroll_off, 32, 0x2000, 0, 4, 32, 30);
    draw_nametable_rect(state, 256 + scroll_off, 32, 0x2400, 0, 4, 32, 30);
  } else {
    draw_nametable_rect(state, scroll_off, 32, 0x2400, 0, 4, 32, 30);
    draw_nametable_rect(state, 256 + scroll_off, 32, 0x2000, 0, 4, 32, 30);
  }

  for (int spriteidx = 0; spriteidx < 64; spriteidx++) {
    const struct sprite *s = state->sprites + (63 - spriteidx);
    if (!s->draw_behind) {
      state->callbacks.draw_tile(state->callbacks.userdata, s->tile);
    }
  }
}
