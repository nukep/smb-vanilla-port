#include "smbsession.h"
#include "audio.h"
#include "smbcore/mario.h"
#include "render_opengl.h"
#include "render_raster.h"
#include "windowing_sdl.h"
#include "palette_builtin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log_error(msg, ...) fprintf(stderr, "ERROR: " msg "\n", ##__VA_ARGS__)
#define log_info(msg, ...)  fprintf(stdout, "INFO: " msg "\n", ##__VA_ARGS__)

struct sdl_key_scancodes {
  SDL_Scancode u,d,l,r,select,start,b,a;
};

struct SMBSession {
  FILE *romfile;
  struct SMB_state *smb_state;
  struct SMB_audio *audio;

  struct sdl_key_scancodes sdl_key_scancodes;

  struct SMB_buttons player1_buttons;
  struct SMB_buttons player2_buttons;

  u8 smb2j_games_beaten;

  // OpenGL mode
  struct SMBgl *smb_gl;

  // Raster mode
  struct SMBraster *smb_raster;
  SDL_Texture *texture;
};

size_t SMBSession_size(void) {
  return sizeof(struct SMBSession);
}

bool SMBSession_valid(const struct SMBSession *s) {
  return s->smb_state != 0;
}

static bool load_palette(unsigned char *rgb_palette, const char *filename) {
  FILE *f = fopen(filename, "rb");
  if (!f) {
    return false;
  }
  bool ok = fread(rgb_palette, 0x40*3, 1, f) == 1;
  fclose(f);
  return ok;
}

static bool read_rom_bytes(void *userdata, unsigned char *buf, size_t size) {
  struct SMBSession *s = userdata;
  return fread(buf, size, 1, s->romfile) == 1;
}

static bool seek_rom(void *userdata, size_t offset) {
  struct SMBSession *s = userdata;
  return fseek(s->romfile, offset, SEEK_SET) == 0;
}

static u8 smb2j_load_games_beaten(void *userdata) {
  struct SMBSession *s = userdata;
  return s->smb2j_games_beaten;
}

static bool smb2j_save_games_beaten(void *userdata, u8 games_beaten) {
  struct SMBSession *s = userdata;
  log_info("Pretending to save game...");
  log_info("Games beaten: %d", games_beaten);
  s->smb2j_games_beaten = games_beaten;
  return true;
}

static void update_pattern_tables(void *userdata, const unsigned char *chrrom) {
  struct SMBSession *s = userdata;

  if (s->smb_gl) {
    SMBgl_update_pattern_tables(s->smb_gl, chrrom);
  } else if (s->smb_raster) {
    SMBraster_update_pattern_tables(s->smb_raster, chrrom);
  }
}

static void update_palette(void *userdata, const unsigned char *palette_indices) {
  struct SMBSession *s = userdata;

  if (s->smb_gl) {
    SMBgl_update_palette(s->smb_gl, palette_indices);
  } else if (s->smb_raster) {
    SMBraster_update_palette(s->smb_raster, palette_indices);
  }
}

static void draw_tile(void *userdata, struct SMB_tile tile) {
  struct SMBSession *s = userdata;

  if (s->smb_gl) {
    SMBgl_draw_tile(s->smb_gl, tile);
  } else if (s->smb_raster) {
    SMBraster_draw_tile(s->smb_raster, tile);
  }
}

static void apu_write_register(void *userdata, uint16_t addr, uint8_t data) {
  struct SMBSession *s = userdata;
  if (s->audio) {
    SMB_audio_write_register(s->audio, addr, data);
  }
}

static void apu_end_frame(void *userdata) {
  struct SMBSession *s = userdata;
  if (s->audio) {
    SMB_audio_end_frame(s->audio);
  }
}

static void joy1(void *userdata, struct SMB_buttons *buttons) {
  struct SMBSession *s = userdata;
  *buttons = s->player1_buttons;
}

static void joy2(void *userdata, struct SMB_buttons *buttons) {
  struct SMBSession *s = userdata;
  *buttons = s->player2_buttons;
}

bool SMBSession_init(struct SMBSession *s, const char *rompath) {
  memset(s, 0, sizeof(struct SMBSession));

  // TODO
  s->smb2j_games_beaten = 8;

  s->sdl_key_scancodes.u = SDL_SCANCODE_W;
  s->sdl_key_scancodes.d = SDL_SCANCODE_S;
  s->sdl_key_scancodes.l = SDL_SCANCODE_A;
  s->sdl_key_scancodes.r = SDL_SCANCODE_D;
  s->sdl_key_scancodes.select = SDL_SCANCODE_RSHIFT;
  s->sdl_key_scancodes.start = SDL_SCANCODE_RETURN;
  s->sdl_key_scancodes.b = SDL_SCANCODE_J;
  s->sdl_key_scancodes.a = SDL_SCANCODE_K;

  s->romfile = fopen(rompath, "rb");
  if (!s->romfile) {
    log_error("Could not open ROM %s", rompath);
    goto err;
  }

  /******** Initialize audio ********/

  s->audio = malloc(SMB_audio_size());
  if (!SMB_audio_init(s->audio, 44100, 100)) {
    log_error("Could not initialize audio");
    free(s->audio);
    s->audio = 0;
  }

  /******** Use OpenGL or software renderer ********/

#ifdef OPENGL_ENABLED
  if (windowing_sdl_glcontext()) {
    s->smb_gl = malloc(SMBgl_size());
    if (!SMBgl_init(s->smb_gl)) {
      log_error("Could not initialize OpenGL renderer");
      free(s->smb_gl);
      s->smb_gl = 0;
    }
  }
#endif

  SDL_Renderer *renderer = windowing_sdl_renderer();

  if (!s->smb_gl && renderer) {
    // Fallback to raster
    s->smb_raster = malloc(SMBraster_size());
    if (!SMBraster_init(s->smb_raster)) {
      log_error("Could not initialize software renderer");
      free(s->smb_raster);
      s->smb_raster = 0;
    } else {
      s->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, 256, 240);
      if (!s->texture) {
        log_error("Could not create SDL texture: %s", SDL_GetError());
        SMBraster_fini(s->smb_raster);
        free(s->smb_raster);
        s->smb_raster = 0;
      }
    }
  }

  if (!s->smb_gl && !s->smb_raster) {
    log_error("No renderer available");
    goto err;
  }

  u8 palette_rgb[NUM_PALETTE_ENTRIES][3] = {0};

  memcpy(&palette_rgb[0][0], &PALETTE_BUILTIN[0][0], sizeof(palette_rgb));

  if (!load_palette(&palette_rgb[0][0], "palette.pal")) {
    log_info("Could not load palette from file %s. Using built-in palette.", "palette.pal");
  }

  if (s->smb_gl) {
    SMBgl_provide_palette_lookup(s->smb_gl, &palette_rgb[0][0]);
  } else {
    SMBraster_provide_palette_lookup(s->smb_raster, &palette_rgb[0][0]);
  }

  /******** Load the ROM, initialize SMB state ********/

  s->smb_state = malloc(SMB_state_size());

  struct SMB_callbacks callbacks = {0};
  callbacks.userdata = s;

  callbacks.read_rom_bytes = read_rom_bytes;
  callbacks.seek_rom = seek_rom;
  callbacks.smb2j_load_games_beaten = smb2j_load_games_beaten;
  callbacks.smb2j_save_games_beaten = smb2j_save_games_beaten;

  callbacks.apu_write_register = apu_write_register;
  callbacks.apu_end_frame = apu_end_frame;

  callbacks.update_pattern_tables = update_pattern_tables;
  callbacks.update_palette = update_palette;
  callbacks.draw_tile = draw_tile;

  callbacks.joy1 = joy1;
  callbacks.joy2 = joy2;

  if (!SMB_state_init(s->smb_state, &callbacks)) {
    log_error("Could not initialize game");
    goto err;
  }

  SMB_start_on_level(s->smb_state, 1, 1);

  return true;

err:
  // If initialization fails at any point, go here and clean up anything that was created
  SMBSession_fini(s);
  return false;
}

void SMBSession_fini(struct SMBSession *s) {
  if (s->smb_state) {
    free(s->smb_state);
  }
  if (s->romfile) {
    fclose(s->romfile);
  }
  if (s->audio) {
    SMB_audio_fini(s->audio);
    free(s->audio);
  }
  if (s->texture) {
    SDL_DestroyTexture(s->texture);
  }
  if (s->smb_gl) {
    SMBgl_fini(s->smb_gl);
    free(s->smb_gl);
  }
  if (s->smb_raster) {
    SMBraster_fini(s->smb_raster);
    free(s->smb_raster);
  }
}

void SMBSession_tick(struct SMBSession *s) {
  if (!SMBSession_valid(s)) {
    return;
  }

  if (s->smb_gl) {
    SMB_tick(s->smb_state);

    if (!SMBgl_render_frame(s->smb_gl)) {
      log_error("Error rendering GL frame");
    }
    return;
  }

  void *pixels = 0;
  int pitch = 0;

#ifdef USE_SDL2
  bool locked = SDL_LockTexture(s->texture, 0, &pixels, &pitch) == 0;
#else
  bool locked = SDL_LockTexture(s->texture, 0, &pixels, &pitch);
#endif
  if (!locked) {
    log_error("Could not lock SDL texture: %s", SDL_GetError());
    return;
  }
  
  // "pitch" is in bytes. Divide by 3 to get pixels.
  SMBraster_set_buffer(s->smb_raster, (unsigned char*)pixels, pitch / 3);
  SMBraster_clear(s->smb_raster);
  SMB_tick(s->smb_state);

  SDL_UnlockTexture(s->texture);

  SDL_Renderer *renderer = windowing_sdl_renderer();

  int window_width = 0;
  int window_height = 0;
  SDL_GetWindowSize(windowing_sdl_window(), &window_width, &window_height);

#ifdef USE_SDL2
  const SDL_Rect dstrect = {0, 0, window_width, window_height};
  SDL_RenderCopy(renderer, s->texture, 0, &dstrect);
#else
  const SDL_FRect dstrect = {0, 0, (float)window_width, (float)window_height};
  SDL_RenderTexture(renderer, s->texture, 0, &dstrect);
#endif
}

// Called whenever a key is newly pressed or newly released (not on repeat).
void SMBSession_on_keypress_change(struct SMBSession *s, int sdl_scancode, bool isdown) {
#define KEY(key)  if (sdl_scancode == s->sdl_key_scancodes.key) { s->player1_buttons.key = isdown; }
  KEY(u);
  KEY(d);
  KEY(l);
  KEY(r);
  KEY(select);
  KEY(start);
  KEY(b);
  KEY(a);
#undef KEY
}
