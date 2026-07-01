#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

#include "audio.h"
#include "smbcore/mario.h"
#include "movie.h"
#include "render_opengl.h"
#include "render_raster.h"
#include "timer.h"

#ifdef USE_SDL2
#  include <SDL.h>
#  include <SDL_opengl.h>
#else
#  include <SDL3/SDL.h>
#  include <SDL3/SDL_opengl.h>
#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log_error(msg, ...) fprintf(stderr, "ERROR: " msg "\n", ##__VA_ARGS__)
#define log_info(msg, ...)  fprintf(stdout, "INFO: " msg "\n", ##__VA_ARGS__)

#include "config.h"

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

struct sdl_key_scancodes {
  SDL_Scancode u,d,l,r,select,start,b,a;
};

struct frontend_userdata {
  FILE *romfile;
  struct SMB_state *smb_state;
  struct SMB_audio *audio;
  struct Movie *movie;
  struct SMB_buttons player1_buttons;
  struct SMB_buttons player2_buttons;
  bool rendering_enabled;
  struct config *cfg;

  SDL_Window *window;
  int video_scale;
  struct sdl_key_scancodes sdl_key_scancodes;

  u8 smb2j_games_beaten;

  // OpenGL mode
  struct SMBgl *smb_gl;

  // Raster mode
  struct SMBraster *smb_raster;
  unsigned char *raster_pixels;
  GLuint raster_texture;
};

static void joy1(void *userdata, struct SMB_buttons *buttons) {
  struct frontend_userdata *fe = (struct frontend_userdata *)userdata;
  *buttons = fe->player1_buttons;
}
static void joy2(void *userdata, struct SMB_buttons *buttons) {
  struct frontend_userdata *fe = (struct frontend_userdata *)userdata;
  *buttons = fe->player2_buttons;
}

static void update_pattern_tables(void *userdata, const u8 *chrrom) {
  struct frontend_userdata *fe = (struct frontend_userdata *)userdata;

  if (fe->smb_gl) {
    SMBgl_update_pattern_tables(fe->smb_gl, chrrom);
    return;
  } else if (fe->smb_raster) {
    SMBraster_update_pattern_tables(fe->smb_raster, chrrom);
  }
}

static void update_palette(void *userdata, const u8 *palette_indices) {
  struct frontend_userdata *fe = (struct frontend_userdata *)userdata;

  if (fe->smb_gl) {
    SMBgl_update_palette(fe->smb_gl, palette_indices);
  } else if (fe->smb_raster) {
    SMBraster_update_palette(fe->smb_raster, palette_indices);
  }
}
static void draw_tile(void *userdata, const struct SMB_tile tile) {
  struct frontend_userdata *fe = (struct frontend_userdata *)userdata;

  if (!fe->rendering_enabled) {
    return;
  }

  if (fe->smb_gl) {
    SMBgl_draw_tile(fe->smb_gl, tile);
  } else if (fe->smb_raster) {
    SMBraster_draw_tile(fe->smb_raster, tile);
  }
}

static bool load_palette(u8 *rgb_palette, const char *filename) {
  return io_readtobuffer(filename, (size_t)0x40*3, rgb_palette);
}

static bool load_ppuram(struct SMB_state *state, const char *filename) {
  return io_readtobuffer(filename, 0x4000, SMB_ppuram(state));
}

static bool dump_ppuram(struct SMB_state *state, const char *filename) {
  return io_writefrombuffer(filename, 0x4000, SMB_ppuram(state));
}

static bool load_ram(struct SMB_state *state, const char *filename) {
  if (!io_readtobuffer(filename, 0x800, SMB_ram(state))) {
    return false;
  }
  SMB_ram_finishwrite(state);
  return true;
}

static bool dump_ram(struct SMB_state *state, const char *filename) {
  return io_writefrombuffer(filename, 0x800, SMB_ram(state));
}

static u8 smb2j_load_games_beaten(void *userdata) {
  struct frontend_userdata *fe = (struct frontend_userdata *)userdata;
  return fe->smb2j_games_beaten;
}
static bool smb2j_save_games_beaten(void *userdata, u8 games_beaten) {
  struct frontend_userdata *fe = (struct frontend_userdata *)userdata;
  log_info("Pretending to save game...");
  log_info("Games beaten: %d", games_beaten);
  fe->smb2j_games_beaten = games_beaten;
  return true;
}

static bool advance_movie(struct frontend_userdata *fe) {
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

// Called whenever a key is newly pressed, or newly released
// Does not send repeat keys from holding it down
static int on_keypress_change(struct frontend_userdata *fe, SDL_Scancode sc, bool isdown) {
  struct SMB_state *smb_state = fe->smb_state;

  if (isdown) {
    switch (sc) {
    case SDL_SCANCODE_1:
      if (load_ppuram(smb_state, fe->cfg->debug.dump_ppu_filename)) {
        if (!load_ram(smb_state, fe->cfg->debug.dump_ram_filename)) {
          // Couldn't load RAM - exit
          return 1;
        }
      }
      break;

    case SDL_SCANCODE_0:
      // dump the RAM and PPU
      dump_ppuram(smb_state, fe->cfg->debug.dump_ppu_filename);
      dump_ram(smb_state, fe->cfg->debug.dump_ram_filename);
      break;

    case SDL_SCANCODE_ESCAPE:
      // Stop the movie and let the player take control
      if (fe->movie) {
        movie_fini(fe->movie);
        free(fe->movie);
        fe->movie = 0;
      }
      break;

    default:
      break;
    }
  }

#define KEY(key)  if (sc == fe->sdl_key_scancodes.key) { fe->player1_buttons.key = isdown; }
  KEY(u);
  KEY(d);
  KEY(l);
  KEY(r);
  KEY(select);
  KEY(start);
  KEY(b);
  KEY(a);
#undef KEY

  return 0;
}

static bool read_rom_bytes(void *userdata, u8 *buf, size_t size) {
  struct frontend_userdata *fe = (struct frontend_userdata *)userdata;
  return fread(buf, size, 1, fe->romfile) == 1;
}

static bool seek_rom(void *userdata, size_t offset) {
  struct frontend_userdata *fe = (struct frontend_userdata *)userdata;
  fseek(fe->romfile, offset, SEEK_SET);
  return true;
}

static void apu_write_register(void *userdata, u16 addr, u8 data) {
  struct frontend_userdata *fe = (struct frontend_userdata *)userdata;
  if (fe->audio) {
    SMB_audio_write_register(fe->audio, addr, data);
  }
}
static void apu_end_frame(void *userdata) {
  struct frontend_userdata *fe = (struct frontend_userdata *)userdata;
  if (fe->audio) {
    SMB_audio_end_frame(fe->audio);
  }
}

// Fit a 256x240 rect, centered, into an avail_w x avail_h area, preserving aspect ratio.
static void compute_letterbox(float avail_w, float avail_h, float *x, float *y, float *w, float *h) {
  const float aspect = 256.0f / 240.0f;
  float box_w = avail_w;
  float box_h = box_w / aspect;
  if (box_h > avail_h) {
    box_h = avail_h;
    box_w = box_h * aspect;
  }
  *w = box_w;
  *h = box_h;
  *x = (avail_w - box_w) * 0.5f;
  *y = (avail_h - box_h) * 0.5f;
}

// Go with one unashamedly-long tick function + main. (keep it simple!)

static int imgui_tick(void *userdata) {
  struct frontend_userdata *fe = (struct frontend_userdata *)userdata;
  struct SMB_state *smb_state = fe->smb_state;

  SDL_Event eventData;
  while (SDL_PollEvent(&eventData)) {
    ImGui_ImplSDL3_ProcessEvent(&eventData);

    switch (eventData.type) {
    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP:
      {
        bool isdown = eventData.type == SDL_EVENT_KEY_DOWN;
        SDL_Scancode sc = eventData.key.scancode;
        if (!eventData.key.repeat) {
          int res = on_keypress_change(fe, sc, isdown);
          if (res) {
            return res;
          }
        }
      }
      break;

    case SDL_EVENT_QUIT:
      return 1;

    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
      if (eventData.window.windowID == SDL_GetWindowID(fe->window)) {
        return 1;
      }
      break;
    }
  }

  // Overwrite the player buttons if a movie exists with remaining frames
  advance_movie(fe);

  if (SDL_GetWindowFlags(fe->window) & SDL_WINDOW_MINIMIZED) {
    SDL_Delay(10);
    return 0;
  }

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();

  ImGuiIO &io = ImGui::GetIO();
  int fb_w, fb_h;
  SDL_GetWindowSizeInPixels(fe->window, &fb_w, &fb_h);

  glViewport(0, 0, fb_w, fb_h);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  if (fe->smb_gl) {
    float lx, ly, lw, lh;
    compute_letterbox((float)fb_w, (float)fb_h, &lx, &ly, &lw, &lh);

    int gl_x = (int)lx;
    int gl_y = fb_h - (int)(ly + lh);
    int gl_w = (int)lw;
    int gl_h = (int)lh;

    glEnable(GL_SCISSOR_TEST);
    glScissor(gl_x, gl_y, gl_w, gl_h);
    glViewport(gl_x, gl_y, gl_w, gl_h);

    SMB_tick(smb_state);

    if (!SMBgl_render_frame(fe->smb_gl)) {
      log_error("Error rendering GL frame");
    }

    glDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, fb_w, fb_h);
  } else {
    SMBraster_set_buffer(fe->smb_raster, fe->raster_pixels, 256);
    SMBraster_clear(fe->smb_raster);
    SMB_tick(smb_state);

    glBindTexture(GL_TEXTURE_2D, fe->raster_texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 256, 240, GL_RGB, GL_UNSIGNED_BYTE, fe->raster_pixels);

    float lx, ly, lw, lh;
    compute_letterbox(io.DisplaySize.x, io.DisplaySize.y, &lx, &ly, &lw, &lh);

    ImGui::GetBackgroundDrawList()->AddImage(
        ImTextureRef((ImTextureID)(intptr_t)fe->raster_texture),
        ImVec2(lx, ly), ImVec2(lx + lw, ly + lh));
  }

  ImGui::BeginMainMenuBar();
  if (ImGui::BeginMenu("File")) {
    if (ImGui::MenuItem("Load ROM")) {
    }
    ImGui::Separator();
    if (ImGui::MenuItem("Quit")) {
      ImGui::EndMenu();
      ImGui::EndMainMenuBar();
      return 1;
    }
    ImGui::EndMenu();
  }
  static bool show_demo_window = false;
  if (ImGui::BeginMenu("Debug")) {
    if (ImGui::MenuItem("Show ImGui demo window", nullptr, show_demo_window)) {
      show_demo_window = !show_demo_window;
    }
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();

  if (show_demo_window) {
    ImGui::ShowDemoWindow(&show_demo_window);
  }

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(fe->window);

  return 0;
}

int main(int argc, char *argv[]) {
  /******** Declare/allocate some memory ********/

  struct SMB_state *smb_state = (struct SMB_state *)malloc(SMB_state_size());
  struct frontend_userdata *fe = (struct frontend_userdata *)malloc(sizeof(struct frontend_userdata));
  struct config cfg = {0};
  SDL_GLContext glcontext = 0;
  struct SMB_callbacks callbacks = {0};
  bool imgui_initialized = false;
  u8 palette_rgb[0x40][3];
  float main_scale = 1.0f;
  SDL_WindowFlags window_flags = 0;
  int skipto = 0;

  if (!smb_state || !fe) {
    goto exit;
  }
  memset(fe, 0, sizeof(struct frontend_userdata));

  if (!config_init(&cfg)) {
    goto exit;
  }

  fe->cfg = &cfg;


  /******** Config defaults ********/

  cfg.audio.enabled = true;
  cfg.audio.samplerate = 44100;
  cfg.audio.maxlatency_ms = 100;
  cfg.smb2j.override_games_beaten = -1;


  /******** Parse config, arguments ********/

  if (!parse_options("smbvanilla.ini", argc, argv, &cfg)) {
    log_error("Could not parse options");
    goto exit;
  }


  /******** Validate arguments ********/

  if (!cfg.general.rom_filename) {
    log_error("Please provide a SMB1 or SMB2J (Lost Levels) rom!");
    goto exit;
  }

  if (1) {
    SDL_Scancode *key_scancodes = &cfg.bindings.keys[0];
    fe->sdl_key_scancodes.u      = key_scancodes[0];
    fe->sdl_key_scancodes.d      = key_scancodes[1];
    fe->sdl_key_scancodes.l      = key_scancodes[2];
    fe->sdl_key_scancodes.r      = key_scancodes[3];
    fe->sdl_key_scancodes.select = key_scancodes[4];
    fe->sdl_key_scancodes.start  = key_scancodes[5];
    fe->sdl_key_scancodes.b      = key_scancodes[6];
    fe->sdl_key_scancodes.a      = key_scancodes[7];
  }

  if (cfg.smb2j.override_games_beaten >= 0) {
    fe->smb2j_games_beaten = (u8)cfg.smb2j.override_games_beaten;
  }


  /******** Initialize audio ********/

  if (cfg.audio.enabled) {
    fe->audio = (struct SMB_audio *)malloc(SMB_audio_size());
  }

  if (fe->audio && !SMB_audio_init(fe->audio, cfg.audio.samplerate, cfg.audio.maxlatency_ms)) {
    log_error("Could not initialize audio!");
    free(fe->audio);
    fe->audio = 0;
  }


  /******** Initialize SDL / OpenGL ********/

  if (cfg.general.palette_filename) {
    if (!load_palette(&palette_rgb[0][0], cfg.general.palette_filename)) {
      log_error("Could not load palette from file %s", cfg.general.palette_filename);
      goto exit;
    }
  }

  fe->video_scale = 3;

  if (cfg.graphics.video_scale != 0) {
    fe->video_scale = cfg.graphics.video_scale;
  }

  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
    log_error("Could not initialize SDL video: %s", SDL_GetError());
    goto exit;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
  window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;

  fe->window = SDL_CreateWindow("SMB Vanilla",
                                 (int)(256 * fe->video_scale * main_scale),
                                 (int)(240 * fe->video_scale * main_scale),
                                 window_flags);
  if (!fe->window) {
    log_error("Could not create SDL window: %s", SDL_GetError());
    goto exit;
  }

  glcontext = SDL_GL_CreateContext(fe->window);
  if (!glcontext) {
    log_error("Could not create OpenGL context: %s", SDL_GetError());
    goto exit;
  }
  SDL_GL_MakeCurrent(fe->window, glcontext);

  if (cfg.general.maxspeed) {
    // We want to play as fast as possible, so disable any vsync
    SDL_GL_SetSwapInterval(0);
  } else {
    SDL_GL_SetSwapInterval(1);
  }

#ifdef OPENGL_ENABLED
  if (cfg.graphics.opengl) {
    fe->smb_gl = (struct SMBgl *)malloc(SMBgl_size());
    if (!SMBgl_init(fe->smb_gl)) {
      log_error("Could not initialize OpenGL renderer");
      free(fe->smb_gl);
      fe->smb_gl = 0;
    }
  }
#endif

  if (cfg.graphics.software && !fe->smb_gl) {
    // Fallback to raster
    fe->smb_raster = (struct SMBraster *)malloc(SMBraster_size());
    if (!SMBraster_init(fe->smb_raster)) {
      log_error("Could not initialize software renderer");
      free(fe->smb_raster);
      fe->smb_raster = 0;
    }
  }

  if (fe->smb_gl) {
    log_info("Using OpenGL renderer");

    SMBgl_provide_palette_lookup(fe->smb_gl, &palette_rgb[0][0]);
  } else if (fe->smb_raster) {
    log_info("Using software renderer");
    SMBraster_provide_palette_lookup(fe->smb_raster, &palette_rgb[0][0]);
  } else {
    log_error("No renderer available");
    goto exit;
  }

  if (fe->smb_raster) {
    fe->raster_pixels = (unsigned char *)malloc(256 * 240 * 3);

    glGenTextures(1, &fe->raster_texture);
    glBindTexture(GL_TEXTURE_2D, fe->raster_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 240, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  }

  SDL_SetWindowPosition(fe->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
  SDL_ShowWindow(fe->window);

  /******** Initialize Dear ImGui ********/

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  {
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGuiStyle &style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;
  }

  ImGui_ImplSDL3_InitForOpenGL(fe->window, glcontext);
  ImGui_ImplOpenGL3_Init();
  imgui_initialized = true;


  /******** Load ROM, initialize SMB state ********/

  fe->romfile = fopen(cfg.general.rom_filename, "rb");
  if (!fe->romfile) {
    log_error("Could not open ROM %s: %s", cfg.general.rom_filename, strerror(errno));
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
  SMB_start_on_level(smb_state, cfg.world, cfg.level);
  fe->smb_state = smb_state;

  log_info("Started!");


  /******** Step through the movie, if one is provided ********/

  if (cfg.movie_prefix) {
    static const size_t filename_size = 1024;
    char *buttons_filename = 0;
    char *ram_filename = 0;

    buttons_filename = (char *)malloc(filename_size);
    snprintf(buttons_filename, filename_size, "%smovie-buttons.txt", cfg.movie_prefix);

    if (cfg.movie_readram) {
      ram_filename = (char *)malloc(filename_size);
      snprintf(ram_filename, filename_size, "%smovie-ram.bin", cfg.movie_prefix);
    }

    fe->movie = (struct Movie *)malloc(sizeof(struct Movie));

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

  skipto = cfg.movie_skip_to_before_frame;

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
      if (movie_is_valid && cfg.movie_readram) {
        movie_readram(fe->movie, SMB_ram(smb_state));
      }
    }
  }


  /******** Start game loop ********/

  fe->rendering_enabled = true;

  // On an NTSC NES: clocks per second, divided by clocks per frame
  // (approx 60.0988 fps)
  {
    const double fps = 1789773.0 / 29780.5;

    if (cfg.general.maxspeed) {
      while (1) {
        if (imgui_tick(fe) != 0) {
          break;
        }
      }
    } else {
      timer_run_at_frequency(fps, fe, imgui_tick);
    }
  }


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
    if (fe->raster_texture) {
      glDeleteTextures(1, &fe->raster_texture);
    }
    if (fe->raster_pixels) {
      free(fe->raster_pixels);
    }
    if (fe->romfile) {
      fclose(fe->romfile);
    }
    if (fe->movie) {
      movie_fini(fe->movie);
      free(fe->movie);
    }
    if (imgui_initialized) {
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplSDL3_Shutdown();
      ImGui::DestroyContext();
    }
    if (fe->window) {
      SDL_DestroyWindow(fe->window);
    }
    if (fe->audio) {
      SMB_audio_fini(fe->audio);
    }
    free(fe);
  }
  if (glcontext) {
    SDL_GL_DestroyContext(glcontext);
  }
  SDL_Quit();

  return 0;
}
