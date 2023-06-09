#ifndef MARIO_H
#define MARIO_H

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

typedef unsigned char byte;
typedef unsigned short ushort;

struct SMB_buttons {
    bool u:1;
    bool d:1;
    bool l:1;
    bool r:1;
    bool a:1;
    bool b:1;
    bool select:1;
    bool start:1;
};

struct SMB_tile {
    int tileidx;
    int paletteidx;
    bool flip_horz;
    bool flip_vert;
    int x;
    int y;
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

    void (*joy1)(void *userdata, struct SMB_buttons *buttons);
    void (*joy2)(void *userdata, struct SMB_buttons *buttons);
};

struct SMB_state;

size_t SMB_state_size();
void SMB_state_init(struct SMB_state *state, const struct SMB_callbacks *cb);
void SMB_tick(struct SMB_state *state);
byte* SMB_ram(struct SMB_state *state);
byte* SMB_ppuram(struct SMB_state *state);
//byte* SMB_get_chrrom();

#ifdef __cplusplus
}
#endif

#endif