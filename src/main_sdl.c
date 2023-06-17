#include "audio.h"
#include "mario.h"
#include "movie.h"
#include "render_opengl.h"
#include "render_raster.h"
#include "time.h"

#include <SDL.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log_error(msg, ...) fprintf(stderr, "ERROR: " msg "\n", ##__VA_ARGS__)
#define log_info(msg, ...)  fprintf(stdout, "INFO: " msg "\n", ##__VA_ARGS__)

static bool io_readtobuffer(const char *filename, size_t size, void *buf) {
  FILE *f = fopen(filename, "rb");
  if (!f) {
    log_error("%s", strerror(errno));
    return false;
  }
  if (fread(buf, size, 1, f) != 1) {
    log_error("Could not read bytes in file");
    return false;
  }
  if (fclose(f) != 0) {
    log_error("Could not close file");
    return false;
  }
  return true;
}

static bool io_writefrombuffer(const char *filename, size_t size, void *buf) {
  FILE *f = fopen(filename, "wb");
  if (!f) {
    log_error("%s", strerror(errno));
    return false;
  }
  if (fwrite(buf, size, 1, f) != 1) {
    log_error("Could not write bytes in file");
    return false;
  }
  if (fclose(f) != 0) {
    log_error("Could not close file");
    return false;
  }
  return true;
}

struct frontend_userdata {
  FILE *romfile;
  struct SMB_state *smb_state;
  struct SMB_audio *audio;
  struct Movie *movie;
  struct SMB_buttons player1_buttons;
  struct SMB_buttons player2_buttons;

  SDL_Window *window;
  int video_scale;

  // OpenGL mode
  struct SMBgl *smb_gl;

  // Raster mode
  struct SMBraster *smb_raster;
  SDL_Surface *surf;
  int pixels_stride;
};

void joy1(void *userdata, struct SMB_buttons *buttons) {
  struct frontend_userdata *fe = userdata;
  *buttons = fe->player1_buttons;
}
void joy2(void *userdata, struct SMB_buttons *buttons) {
  struct frontend_userdata *fe = userdata;
  *buttons = fe->player2_buttons;
}


void update_pattern_tables(void *userdata, const byte *chrrom) {
  struct frontend_userdata *fe = userdata;

  if (fe->smb_gl) {
    SMBgl_update_pattern_tables(fe->smb_gl, chrrom);
    return;
  } else if (fe->smb_raster) {
    SMBraster_update_pattern_tables(fe->smb_raster, chrrom);
  }
}

void update_palette(void *userdata, const byte *palette_indices) {
  struct frontend_userdata *fe = userdata;

  if (fe->smb_gl) {
    SMBgl_update_palette(fe->smb_gl, palette_indices);
  } else if (fe->smb_raster) {
    SMBraster_update_palette(fe->smb_raster, palette_indices);
  }
}
void draw_tile(void *userdata, const struct SMB_tile tile) {
  struct frontend_userdata *fe = userdata;

  if (fe->smb_gl) {
    SMBgl_draw_tile(fe->smb_gl, tile);
  } else if (fe->smb_raster) {
    SMBraster_draw_tile(fe->smb_raster, tile);
  }
}

bool load_palette(byte *rgb_palette, const char *filename) {
  return io_readtobuffer(filename, (size_t)0x40*3, rgb_palette);
}

bool load_ppuram(struct SMB_state *state, const char *filename) {
  return io_readtobuffer(filename, 0x4000, SMB_ppuram(state));
}

bool dump_ppuram(struct SMB_state *state, const char *filename) {
  return io_writefrombuffer(filename, 0x4000, SMB_ppuram(state));
}

bool load_ram(struct SMB_state *state, const char *filename) {
  return io_readtobuffer(filename, 0x800, SMB_ram(state));
}

bool dump_ram(struct SMB_state *state, const char *filename) {
  return io_writefrombuffer(filename, 0x800, SMB_ram(state));
}

byte smb2j_load_games_beaten(void *userdata) {
  // A decent test value - lets us test Worlds A-D
  return 8;
}
bool smb2j_save_games_beaten(void *userdata, byte games_beaten) {
  log_info("Pretending to save game...");
  log_info("Games beaten: %d", games_beaten);
  return true;
}

const char *ppuram_filename = "ppuram.bin";
const char *ram_filename = "ram.bin";

bool advance_movie(struct frontend_userdata *fe) {
  if (!fe->movie) {
    return false;
  }

  struct MovieButtons movie_buttons;

  bool use_movie_buttons = movie_next(fe->movie, &movie_buttons, 0);
  if (use_movie_buttons) {
    fe->player1_buttons.u = movie_buttons.u;
    fe->player1_buttons.d = movie_buttons.d;
    fe->player1_buttons.l = movie_buttons.l;
    fe->player1_buttons.r = movie_buttons.r;
    fe->player1_buttons.b = movie_buttons.b;
    fe->player1_buttons.a = movie_buttons.a;
    fe->player1_buttons.select = movie_buttons.select;
    fe->player1_buttons.start = movie_buttons.start;
  }
  return use_movie_buttons;
}

int sdl_tick(void *userdata) {
  struct frontend_userdata *fe = userdata;
  struct SMB_state *smb_state = fe->smb_state;
  bool use_movie_buttons = false;

  use_movie_buttons = advance_movie(fe);

  SDL_Event eventData;
  while (SDL_PollEvent(&eventData)) {
    switch (eventData.type) {
    case SDL_KEYDOWN:
    case SDL_KEYUP: {
      bool isdown = eventData.key.state == SDL_PRESSED;
      SDL_Scancode sc = eventData.key.keysym.scancode;
      if (isdown && !eventData.key.repeat) {
        switch (sc) {
        case SDL_SCANCODE_1:
          if (load_ppuram(smb_state, ppuram_filename)) {
            if (!load_ram(smb_state, ram_filename)) {
              // Couldn't load RAM - exit
              return 1;
            }
          }
          break;
        case SDL_SCANCODE_0:
          // dump the RAM and PPU
          dump_ppuram(smb_state, ppuram_filename);
          dump_ram(smb_state, ram_filename);
          break;
        }
      }
      if (!use_movie_buttons) {
        switch (sc) {
        case SDL_SCANCODE_W:
          fe->player1_buttons.u = isdown;
          break;
        case SDL_SCANCODE_S:
          fe->player1_buttons.d = isdown;
          break;
        case SDL_SCANCODE_A:
          fe->player1_buttons.l = isdown;
          break;
        case SDL_SCANCODE_D:
          fe->player1_buttons.r = isdown;
          break;
        case SDL_SCANCODE_J:
          fe->player1_buttons.b = isdown;
          break;
        case SDL_SCANCODE_K:
          fe->player1_buttons.a = isdown;
          break;
        case SDL_SCANCODE_U:
          fe->player1_buttons.select = isdown;
          break;
        case SDL_SCANCODE_I:
          fe->player1_buttons.start = isdown;
          break;
        }
      }
    } break;
    case SDL_QUIT:
      return 1;
    }
  }

  if (fe->smb_gl) {
    if (!SMBgl_render_frame(fe->smb_gl)) {
      log_error("Error rendering GL frame");
    }

    SMB_tick(smb_state);

    SDL_GL_SwapWindow(fe->window);
    return 0;
  } else {
    // raster framebuffer

    SDL_Surface *surf = fe->surf;
    
    SDL_LockSurface(surf);

    // draw to the buffer!
    // draw_tile is invoked for each tile during SMB_tick, and will update the pixel buffer
    SMBraster_set_buffer(fe->smb_raster, surf->pixels, fe->pixels_stride);
    SMBraster_clear(fe->smb_raster);
    SMB_tick(smb_state);

    SDL_UnlockSurface(surf);

    const SDL_Rect srcrect = {0, 0, 256, 240};
    SDL_Rect dstrect = {0, 0, 256 * fe->video_scale, 240 * fe->video_scale};
    SDL_BlitScaled(surf, &srcrect, SDL_GetWindowSurface(fe->window), &dstrect);

    SDL_UpdateWindowSurface(fe->window);
    return 0;
  }
}

bool read_rom_bytes(void *userdata, byte *buf, size_t size) {
  struct frontend_userdata *fe = userdata;
  return fread(buf, size, 1, fe->romfile) == 1;
}

bool seek_rom(void *userdata, size_t offset) {
  struct frontend_userdata *fe = userdata;
  fseek(fe->romfile, offset, SEEK_SET);
  return true;
}

void apu_write_register(void *userdata, ushort addr, byte data) {
  struct frontend_userdata *fe = userdata;
  if (fe->audio) {
    SMB_audio_write_register(fe->audio, addr, data);
  }
}
void apu_end_frame(void *userdata) {
  struct frontend_userdata *fe = userdata;
  if (fe->audio) {
    SMB_audio_end_frame(fe->audio);
  }
}

#include "cli_args.h"

// Go with one unashamedly-long main. (keep it simple!)

int main(int argc, char *argv[]) {
  /******** Declare/allocate some memory ********/

  struct SMB_state *smb_state = malloc(SMB_state_size());
  struct frontend_userdata *fe = malloc(sizeof(struct frontend_userdata));
  struct cli_args args = {0};
  struct SMB_audio *audio = 0;
  SDL_Window *window = 0;
  SDL_GLContext glcontext = 0;
  struct SMB_callbacks callbacks = {0};

  if (!smb_state || !fe) {
    goto exit;
  }
  memset(fe, 0, sizeof(struct frontend_userdata));


  /******** Parse arguments ********/

  bool audio_enabled = true;

  if (!parse_cli_args(argc, argv, &args)) {
    log_error("Could not parse args");
    goto exit;
  }


  /******** Validate arguments ********/

  if (!args.rom_filename) {
    log_error("Please provide a SMB1 or SMB2J (Lost Levels) rom!");
    goto exit;
  }


  /******** Initialize audio ********/

  if (audio_enabled) {
    audio = malloc(SMB_audio_size());
  }

  if (audio && !SMB_audio_init(audio)) {
    log_error("Could not initialize audio!");
    free(audio);
    audio = 0;
    audio_enabled = false;
  }


  /******** Initialize SDL / OpenGL ********/

  unsigned char pal_rgb[0x40][3];
  if (!load_palette(&pal_rgb[0][0], "palette.pal")) {
    log_error("Could not load palette");
    goto exit;
  }

  fe->video_scale = 3;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    log_error("Could not initialize SDL2 video: %s", SDL_GetError());
    goto exit;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  window = SDL_CreateWindow("smb-port", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 256 * fe->video_scale,
                            240 * fe->video_scale, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (!window) {
    log_error("Could not create SDL2 window: %s", SDL_GetError());
    goto exit;
  }

  glcontext = SDL_GL_CreateContext(window);
  if (glcontext) {
    fe->smb_gl = malloc(SMBgl_size());
    if (!SMBgl_init(fe->smb_gl)) {
      log_error("Could not initialize OpenGL");
      free(fe->smb_gl);
      fe->smb_gl = 0;
      SDL_GL_DeleteContext(glcontext);
      glcontext = 0;
    }
  }

  if (!fe->smb_gl) {
    // Fallback to raster
    fe->smb_raster = malloc(SMBraster_size());
    if (!SMBraster_init(fe->smb_raster)) {
      log_error("Could not initialize software renderer");
      free(fe->smb_raster);
      fe->smb_raster = 0;
    }
  }

  if (fe->smb_gl) {
    log_info("Using OpenGL renderer");

    SMBgl_provide_palette_lookup(fe->smb_gl, &pal_rgb[0][0]);
  } else if (fe->smb_raster) {
    log_info("Using software renderer");
    SMBraster_provide_palette_lookup(fe->smb_raster, &pal_rgb[0][0]);
  } else {
    log_error("No renderer available");
    goto exit;
  }


  /******** Load ROM, initialize SMB state ********/

  fe->romfile = fopen(args.rom_filename, "rb");
  if (!fe->romfile) {
    goto exit;
  }

  callbacks.userdata = fe;

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

  if (!SMB_state_init(smb_state, &callbacks)) {
    log_error("Could not initialize game");
    goto exit;
  }
  SMB_start_on_level(smb_state, args.world, args.level);
  fe->smb_state = smb_state;

  log_info("Started!");


  /******** Step through the movie, if one is provided ********/

  if (args.movie_prefix) {
    static const size_t filename_size = 1024;
    char *buttons_filename = 0;
    char *ram_filename = 0;

    buttons_filename = malloc(filename_size);
    snprintf(buttons_filename, filename_size, "%smovie-buttons.txt", args.movie_prefix);

    if (args.movie_readram) {
      ram_filename = malloc(filename_size);
      snprintf(ram_filename, filename_size, "%smovie-ram.bin", args.movie_prefix);
    }

    fe->movie = malloc(sizeof(struct Movie));

    if (!movie_init(fe->movie, buttons_filename, ram_filename)) {
      log_error("Could not load movie");
      free(fe->movie);
      fe->movie = 0;
    }
    if (ram_filename) {
      free(ram_filename);
    }
    if (buttons_filename) {
      free(buttons_filename);
    }
  }

  int skipto = args.movie_skip_to_before_frame;

  if (skipto > 0) {
    bool movie_is_valid = true;

    if (fe->movie) {
      for (int i = 0; i < skipto; i++) {
        if (advance_movie(fe)) {
          SMB_tick(smb_state);
        } else {
          movie_is_valid = false;
          break;
        }
      }
      if (movie_is_valid && args.movie_readram) {
        movie_readram(fe->movie, SMB_ram(smb_state));
      }
    }
  }
  fe->audio = audio;
  fe->window = window;

  if (fe->smb_raster) {
    fe->surf = SDL_CreateRGBSurface(0, 256, 240, 24, 0x0000FF, 0x00FF00, 0xFF0000, 0);
    if (!fe->surf) {
      log_error("Could not create SDL2 surface: %s", SDL_GetError());
      goto exit;
    }
    fe->pixels_stride = 256;
  }


  /******** Start game loop ********/

  // On an NTSC NES: clocks per second, divided by clocks per frame
  // (approx 60.0988 fps)
  const double fps = 1789773.0 / 29780.5;

  time_run_at_frequency(fps, fe, sdl_tick);


  /******** Cleanup ********/

  // a successful exit, as well as error conditions, jump here and finalize/free anything that needs to be
exit:

  if (smb_state) {
    free(smb_state);
  }
  if (fe) {
    if (fe->smb_gl) {
      SMBgl_fini(fe->smb_gl);
      free(fe->smb_gl);
    }
    if (fe->smb_raster) {
      SMBraster_fini(fe->smb_raster);
      free(fe->smb_raster);
    }
    if (fe->romfile) {
      fclose(fe->romfile);
    }
    if (fe->movie) {
      movie_fini(fe->movie);
      free(fe->movie);
    }
    free(fe);
  }
  if (glcontext) {
    SDL_GL_DeleteContext(glcontext);
  }

  if (window) {
    SDL_DestroyWindow(window);
  }
  if (audio) {
    SMB_audio_fini(audio);
  }
  SDL_Quit();

  return 0;
}
