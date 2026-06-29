// The start of something magical! ✨

#include "mario.h"
#include "base.h"
#include "smbcore/interface.h"
#include "smbcore/vars.h"

#include <string.h>

void smb1_Reset(void);
void smb1_NMI(void);

bool smb2j_load_file(struct SMB_state *state, const char *name);
void smb2j_Reset(void);
void smb2j_NMI(void);

void smb1_sync_data(void);
void smb2j_sync_data(void);

void smb1_set_world_and_level(u8 world, u8 level);
void smb2j_set_world_and_level(u8 world, u8 level);


struct sprite {
  struct SMB_tile tile;
  bool draw_behind;
};

static inline void transfer_sprite_data(struct sprite sprites[64], const u8 *data) {
  for (int i = 0; i < 64; i++) {
    sprites[i].tile.y = data[i * 4 + 0] + 1;
    sprites[i].tile.tileidx = data[i * 4 + 1];
    u8 attr = data[i * 4 + 2];
    sprites[i].tile.x = data[i * 4 + 3];

    sprites[i].tile.paletteidx = (attr & 0x03) + 4;
    sprites[i].tile.flip_horz = (attr & 0x40) != 0;
    sprites[i].tile.flip_vert = (attr & 0x80) != 0;

    sprites[i].tile.extra_type = TILE_TYPE_SPRITE;
    sprites[i].tile.extra_spriteidx = i;

    sprites[i].draw_behind = (attr & 0x20) != 0;
  }
}

static void draw_graphics(const struct sprite sprites[64]);

#ifdef THREAD_LOCAL_SMBSTATE
thread_local struct SMB_state *SMB_STATE;
#else
struct SMB_state *SMB_STATE;
#endif

static bool load_smb1(struct SMB_state *state, size_t prg_offset, size_t chr_offset) {
  if (!seek_rom(state, prg_offset)) { return false; }
  if (!read_rom_bytes(state, state->rammem + 0x8000, 0x8000)) { return false; }
  if (!seek_rom(state, chr_offset)) { return false; }
  if (!read_rom_bytes(state, state->chrrom, 0x2000)) { return false; }
  state->which_game = GAME_SMB1;
  update_pattern_tables(state);
  return true;
}


struct fds_file {
  const char *name;
  size_t file_offset;
  u16 size;
  u16 org;
  int type;
};

#define TYPE_PRGRAM 0
#define TYPE_CHRRAM 1

#define SMB2J_FDS_FILES_COUNT 6

// hard-code some offsets for now
// the offsets are relative to after the 16-byte FDS header
static struct fds_file SMB2J_FDS_FILES[SMB2J_FDS_FILES_COUNT] = {
  {"SM2CHAR1", 0x013C, 0x2000, 0x0000, TYPE_CHRRAM},
  {"SM2CHAR2", 0x214D, 0x0040, 0x0760, TYPE_CHRRAM},
  {"SM2MAIN ", 0x219E, 0x8000, 0x6000, TYPE_PRGRAM},
  {"SM2DATA2", 0xA1AF, 0x0E2F, 0xC470, TYPE_PRGRAM},
  {"SM2DATA3", 0xAFEF, 0x0CCF, 0xC5D0, TYPE_PRGRAM},
  {"SM2DATA4", 0xBCCF, 0x0F4C, 0xC2B4, TYPE_PRGRAM},
};

bool smb2j_load_file(struct SMB_state *state, const char *name) {
  if (strncmp(name, "SM2SAVE ", 8) == 0) {
    // treat the save byte specially

    state->rammem[0xD29F] = smb2j_load_games_beaten();

    return true;
  }

  for (int i = 0; i < SMB2J_FDS_FILES_COUNT; i++) {
    const struct fds_file *a = &SMB2J_FDS_FILES[i];
    bool eq = strncmp(name, a->name, 8) == 0;
    if (eq) {
      // Found it!
      u8 *copy_to;
      if (a->type == TYPE_CHRRAM) {
        // Copy the bytes over to CHRRAM
        copy_to = state->chrrom + a->org;
      } else if (a->type == TYPE_PRGRAM) {
        // Copy the bytes over to RAM
        copy_to = state->rammem + a->org;
      }
      if (!seek_rom(state, state->smb2j_disk_offset + a->file_offset)) { return false; }
      if (!read_rom_bytes(state, copy_to, a->size)) { return false; }

      if (a->type == TYPE_CHRRAM) {
        update_pattern_tables(state);
      }

      return true;
    }
  }
  return false;
}

bool load_smb2j(struct SMB_state *state, size_t disk_offset) {
  // In this case, the 16 bit header is this:
  static char fds_disk_verification[16] = {0x01, '*', 'N', 'I', 'N', 'T', 'E', 'N', 'D', 'O', '-', 'H', 'V', 'C', '*', 0x01};
  u8 headerbuf[16];
  if (!seek_rom(state, disk_offset)) { return false; }
  if (!read_rom_bytes(state, headerbuf, 16)) { return false; }

  bool match = memcmp(headerbuf, fds_disk_verification, 16) == 0;
  if (!match) { return false; }
  state->which_game = GAME_SMB2J;
  state->smb2j_disk_offset = disk_offset;

  // Load these automatically
  smb2j_load_file(state, "SM2CHAR1");
  smb2j_load_file(state, "SM2MAIN ");
  smb2j_load_file(state, "SM2SAVE ");
  return true;
}


static bool detect_and_load_rom(struct SMB_state *state) {
  u8 headerbuf[16];
  if (!read_rom_bytes(state, headerbuf, 16)) {
    return false;
  }

  if (headerbuf[0] == 'N' && headerbuf[1] == 'E' && headerbuf[2] == 'S' && headerbuf[3] == 0x1A) {
    // An INES header. Probably SMB1.
    if (!load_smb1(state, 0x10, 0x8010)) {
      return false;
    }
  } else if (headerbuf[0] == 'F' && headerbuf[1] == 'D' && headerbuf[2] == 'S' && headerbuf[3] == 0x1A) {
    // An FDS header. Probably SMB2J.
    // TODO: there's an FDS version of SMB1. Maybe handle it?
    if (!load_smb2j(state, 0x10)) {
      return false;
    }
  } else {
    // There are some ROMs that don't include an FDS header, but just the single disk image.
    if (!load_smb2j(state, 0)) {
      return false;
    }
  }

  SMB_ram_finishwrite(state);

  return true;
}

size_t SMB_state_size(void) { return sizeof(struct SMB_state); }

bool SMB_state_init(struct SMB_state *state, const struct SMB_callbacks *cb) {
  SMB_STATE = state;

  memset(state, 0, sizeof(struct SMB_state));
  state->callbacks = *cb;
  state->start_on_world = 1;
  state->start_on_level = 1;

  return detect_and_load_rom(state);
}

void SMB_start_on_level(struct SMB_state *state, u8 world, u8 level) {
  state->start_on_world = world;
  state->start_on_level = level;
}

int SMB_which_game(const struct SMB_state *state) { return state->which_game; }

u8 *SMB_ram(struct SMB_state *state) { return state->rammem; }

u8 *SMB_ppuram(struct SMB_state *state) { return state->ppuram; }

void SMB_ram_finishwrite(struct SMB_state *state) {
  // Set a global variable while accessing the RAM values
  SMB_STATE = state;

  if (state->which_game == GAME_SMB1) {
    smb1_sync_data();
  }
  if (state->which_game == GAME_SMB2J) {
    smb2j_sync_data();
  }
}

void SMB_tick(struct SMB_state *state) {
  // Set a global variable while it's being ticked
  SMB_STATE = state;

  struct sprite sprites[64];

  if (state->which_game == GAME_SMB1) {
    if (!state->reset_occurred) {
      smb1_Reset();
    }

    // The NES wrote to OAM registers to initiate copying sprites
    // $2003 = 0
    // $4014 = 2
    transfer_sprite_data(&sprites[0], &Sprite_Data[0]);
    smb1_NMI();

    if (!state->reset_occurred) {
      smb1_set_world_and_level(state->start_on_world - 1, state->start_on_level - 1);
      state->reset_occurred = true;
    }
  }

  if (state->which_game == GAME_SMB2J) {
    if (!state->reset_occurred) {
      smb2j_Reset();
    }

    // The NES wrote to OAM registers to initiate copying sprites
    // $2003 = 0
    // $4014 = 2
    transfer_sprite_data(&sprites[0], &Sprite_Data[0]);
    smb2j_NMI();

    if (!state->reset_occurred) {
      smb2j_set_world_and_level(state->start_on_world - 1, state->start_on_level - 1);
      state->reset_occurred = true;
    }
  }

  draw_graphics(&sprites[0]);
}

static inline void draw_nametable_tile(int x, int y, u16 ppu_offset, int tilex,
                                       int tiley) {
  int j = tilex;
  int i = tiley;
  int off = i * 32 + j;
  int tileidx = PPURAM(ppu_offset + off) + 0x100;
  // Find which part of the pallete to use
  // Look it up in the attribute table

  u8 a = PPURAM(ppu_offset + 0x03c0 + (i / 4) * 8 + (j / 4));
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
  tile.extra_type = TILE_TYPE_BG;
  tile.extra_bg.x = tilex;
  tile.extra_bg.y = tilex;

  draw_tile(tile);
}

static inline void draw_nametable_rect(int x, int y, u16 ppu_offset, int fromx,
                                       int fromy, int tox, int toy) {
  for (int i = fromy; i < toy; i++) {
    for (int j = fromx; j < tox; j++) {
      draw_nametable_tile(x + (j - fromx) * 8, y + (i - fromy) * 8, ppu_offset, j, i);
    }
  }
}

void draw_graphics(const struct sprite sprites[64]) {
  // The palette can change even if the screen is off (the background color, namely)
  update_palette();

  if (!PPU_STATE.screen_on) {
    return;
  }
  if (!can_draw_tile()) {
    return;
  }

  for (int spriteidx = 64-1; spriteidx >= 0; spriteidx--) {
    if (sprites[spriteidx].draw_behind) {
      draw_tile(sprites[spriteidx].tile);
    }
  }

  const u16 scroll_x = PPU_STATE.t.NN * 256 + PPU_STATE.t.XXXXX * 8 + PPU_STATE.x;

  // Status bar
  draw_nametable_rect(0, 0, 0x2000, 0, 0, 32, 4);

  int scroll_off = -(scroll_x % 256);
  int scroll_nametable = scroll_x / 256;

  if (scroll_nametable == 0) {
    draw_nametable_rect(scroll_off, 32, 0x2000, 0, 4, 32, 30);
    draw_nametable_rect(256 + scroll_off, 32, 0x2400, 0, 4, 32, 30);
  } else {
    draw_nametable_rect(scroll_off, 32, 0x2400, 0, 4, 32, 30);
    draw_nametable_rect(256 + scroll_off, 32, 0x2000, 0, 4, 32, 30);
  }

  for (int spriteidx = 64-1; spriteidx >= 0; spriteidx--) {
    if (!sprites[spriteidx].draw_behind) {
      draw_tile(sprites[spriteidx].tile);
    }
  }
}
