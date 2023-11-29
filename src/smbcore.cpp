// The start of something magical! ✨

#include "smbcore.h"

extern "C" {
void SMB1_Reset();
void SMB1_NMI();

bool smb2j_load_file(struct SMB_state *state, const char *name);
void SMB2J_Reset();
void SMB2J_NMI();
}

#include "smbcommon.h"

thread_local struct SMB_state *SMB_STATE;


static bool load_smb1(struct SMB_state *state, size_t prg_offset, size_t chr_offset) {
  if (!seek_rom(state, prg_offset)) { return false; }
  if (!read_rom_bytes(state, state->rammem + 0x8000, 0x8000)) { return false; }
  if (!seek_rom(state, chr_offset)) { return false; }
  if (!read_rom_bytes(state, state->chrrom, 0x2000)) { return false; }
  state->which_game = GAME_SMB1;
  update_pattern_tables(state);
  return true;
}


struct FdsFile {
  const char *name;
  size_t file_offset;
  ushort size;
  ushort org;
  int type;
};

#define TYPE_PRGRAM 0
#define TYPE_CHRRAM 1

#define SMB2J_FDS_FILES_COUNT 6

// hard-code some offsets for now
// the offsets are relative to after the 16-byte FDS header
static FdsFile SMB2J_FDS_FILES[SMB2J_FDS_FILES_COUNT] = {
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
    const FdsFile &a = SMB2J_FDS_FILES[i];
    bool eq = strncmp(name, a.name, 8) == 0;
    if (eq) {
      // Found it!
      byte *copy_to;
      if (a.type == TYPE_CHRRAM) {
        // Copy the bytes over to CHRRAM
        copy_to = state->chrrom + a.org;
      } else if (a.type == TYPE_PRGRAM) {
        // Copy the bytes over to RAM
        copy_to = state->rammem + a.org;
      }
      if (!seek_rom(state, state->smb2j_disk_offset + a.file_offset)) { return false; }
      if (!read_rom_bytes(state, copy_to, a.size)) { return false; }

      if (a.type == TYPE_CHRRAM) {
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
  byte headerbuf[16];
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
bool SMB_state_init(struct SMB_state *state, const struct SMB_callbacks *cb) {
  SMB_STATE = state;
  memset(state, 0, sizeof(struct SMB_state));
  state->callbacks = *cb;
  state->start_on_world = 1;
  state->start_on_level = 1;
  return detect_and_load_rom(state);
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
      //set_world_and_level(state->start_on_world - 1, state->start_on_level - 1);
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
  tile.extra_type = TILE_TYPE_BG;
  tile.extra_bg.x = tilex;
  tile.extra_bg.y = tilex;

  draw_tile(tile);
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
  if (!can_draw_tile()) {
    return;
  }

  for (int spriteidx = 0; spriteidx < 64; spriteidx++) {
    const struct sprite *s = state->sprites + (63 - spriteidx);
    if (s->draw_behind) {
      draw_tile(s->tile);
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
      draw_tile(s->tile);
    }
  }
}
