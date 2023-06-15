#ifndef MARIO_H
#define MARIO_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

typedef unsigned char byte;
typedef unsigned short ushort;

#define GAME_SMB1 0
#define GAME_SMB2J 1

struct SMB_buttons {
  bool u : 1;
  bool d : 1;
  bool l : 1;
  bool r : 1;
  bool a : 1;
  bool b : 1;
  bool select : 1;
  bool start : 1;
};

#define TILE_TYPE_SPRITE 0
#define TILE_TYPE_BG 1

struct SMB_tile {
  int tileidx;
  int paletteidx;
  bool flip_horz;
  bool flip_vert;
  int x;
  int y;

  byte extra_type;
  union {
	byte extra_spriteidx;
	struct {
	  ushort x;
	  ushort y;
	} extra_bg;
  };
};

struct SMB_callbacks {
  void *userdata;
  bool (*read_rom_bytes)(void *userdata, byte *buf, size_t size);
  bool (*seek_rom)(void *userdata, size_t offset);
  byte (*smb2j_load_games_beaten)(void *userdata);
  bool (*smb2j_save_games_beaten)(void *userdata, byte games_beaten);

  void (*update_pattern_tables)(void *userdata, const byte *chrrom);
  void (*update_palette)(void *userdata, const byte *palette_indices);
  void (*draw_tile)(void *userdata, const struct SMB_tile tile);

  void (*apu_write_register)(void *userdata, ushort addr, byte data);
  void (*apu_end_frame)(void *userdata);

  void (*joy1)(void *userdata, struct SMB_buttons *buttons);
  void (*joy2)(void *userdata, struct SMB_buttons *buttons);
};

struct SMB_state;

size_t SMB_state_size(void);
void SMB_state_init(struct SMB_state *state, const struct SMB_callbacks *cb);
int SMB_which_game(const struct SMB_state *state);
void SMB_start_on_level(struct SMB_state *state, byte world, byte level);
void SMB_tick(struct SMB_state *state);
byte *SMB_ram(struct SMB_state *state);
byte *SMB_ppuram(struct SMB_state *state);

#ifdef __cplusplus
}
#endif

#endif
