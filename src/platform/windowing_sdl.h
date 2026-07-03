#ifndef WINDOWING_SDL_H
#define WINDOWING_SDL_H

#include <stdbool.h>

#ifdef USE_SDL2
#  include <SDL.h>
#else
#  include <SDL3/SDL.h>
#endif

struct windowing_sdl_init_settings {
  bool opengl;
  bool maxspeed;
  int video_scale;
  void *userdata;
  void (*preprocess_event)(void*, SDL_Event *e);
  void (*on_keypress_change)(void*, SDL_Scancode sc, bool isdown);
  bool (*tick)(void*);
};

bool windowing_init(const struct windowing_sdl_init_settings *s);
void windowing_fini(void);
void windowing_loop(void);

SDL_Window *windowing_sdl_window(void);
SDL_GLContext windowing_sdl_glcontext(void);
void windowing_sdl_glcontext_fini(void);

#endif
