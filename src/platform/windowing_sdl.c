// We've deliberately separated the SDL platform code from any UI code,
// so that a lightweight SDL version of the game can be compiled.

#include "windowing_sdl.h"
#include "timer.h"

#include <SDL3/SDL_video.h>
#include <stdio.h>

SDL_Window *window = 0;
SDL_GLContext glcontext = 0;
struct windowing_sdl_init_settings init_settings;

#define error(msg, ...) fprintf(stderr, "ERROR: " msg "\n", ##__VA_ARGS__)
#define info(msg, ...)  fprintf(stdout, "INFO: " msg "\n", ##__VA_ARGS__)

bool windowing_init(const struct windowing_sdl_init_settings *s) {
  init_settings = *s;

  const bool opengl = s->opengl;
  const bool maxspeed = s->maxspeed;
  const int video_scale = s->video_scale;

#ifdef USE_SDL2
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    error("Could not initialize SDL video: %s", SDL_GetError());
    return false;
  }
#else
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    error("Could not initialize SDL video: %s", SDL_GetError());
    return false;
  }
#endif

#ifdef USE_SDL2
  SDL_WindowFlags window_flags = SDL_WINDOW_SHOWN;
#else
  // No flags set
  SDL_WindowFlags window_flags = 0;
  window_flags |= SDL_WINDOW_HIGH_PIXEL_DENSITY;
#endif

  window_flags |= SDL_WINDOW_RESIZABLE;

#ifdef OPENGL_ENABLED
  if (opengl) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window_flags |= SDL_WINDOW_OPENGL;
  }
#endif

#ifdef USE_SDL2
  window = SDL_CreateWindow("SMB Vanilla", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 256 * video_scale, 240 * video_scale, window_flags);
#else
  window = SDL_CreateWindow("SMB Vanilla", 256 * video_scale, 240 * video_scale, window_flags);
#endif
  if (!window) {
    error("Could not create SDL window: %s", SDL_GetError());
    return false;
  }

#ifdef OPENGL_ENABLED
  if (opengl) {
    glcontext = SDL_GL_CreateContext(window);

    if (maxspeed) {
      // We want to play as fast as possible, so disable any vsync
      SDL_GL_SetSwapInterval(0);
    }
  }
#endif

  return true;
}

void windowing_sdl_glcontext_fini(void) {
  if (glcontext) {
#ifdef USE_SDL2
    SDL_GL_DeleteContext(glcontext);
#else
    SDL_GL_DestroyContext(glcontext);
#endif

    glcontext = 0;
  }
}

void windowing_fini(void) {
  windowing_sdl_glcontext_fini();
  if (window) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}

int sdl_tick(void *userdata) {
#ifdef USE_SDL2
  SDL_Event eventData;
  while (SDL_PollEvent(&eventData)) {
    if (init_settings.preprocess_event) {
      init_settings.preprocess_event(userdata, &eventData);
    }
    switch (eventData.type) {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
      {
        bool isdown = eventData.key.state == SDL_PRESSED;
        SDL_Scancode sc = eventData.key.keysym.scancode;
        if (!eventData.key.repeat) {
          init_settings.on_keypress_change(userdata, sc, isdown);
        }
      }
    break;

    case SDL_QUIT:
      return 1;
    }
  }
#else
  SDL_Event eventData;
  while (SDL_PollEvent(&eventData)) {
    if (init_settings.preprocess_event) {
      init_settings.preprocess_event(userdata, &eventData);
    }

    switch (eventData.type) {
    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP:
      {
        bool isdown = eventData.type == SDL_EVENT_KEY_DOWN;
        SDL_Scancode sc = eventData.key.scancode;
        if (!eventData.key.repeat) {
          init_settings.on_keypress_change(userdata, sc, isdown);
        }
      }
    break;

    case SDL_EVENT_QUIT:
      return 1;
    }
  }
#endif
  if (!init_settings.tick(userdata)) {
    return 1;
  }

  if (glcontext) {
    SDL_GL_SwapWindow(window);
  } else {
    SDL_UpdateWindowSurface(window);
  }

  return 0;
}

void windowing_loop(void) {
  //TODO
  const bool maxspeed = false;

  // On an NTSC NES: clocks per second, divided by clocks per frame
  // (approx 60.0988 fps)
  const double fps = 1789773.0 / 29780.5;

  void *userdata = init_settings.userdata;

  if (maxspeed) {
    while (1) {
      if (sdl_tick(userdata) != 0) {
        break;
      }
    }
  } else {
    timer_run_at_frequency(fps, userdata, sdl_tick);
  }
}

SDL_Window *windowing_sdl_window(void) {
  return window;
}

SDL_GLContext windowing_sdl_glcontext(void) {
  return glcontext;
}
