#include "time.h"
#include <SDL.h>
#include <math.h>

// Run the callback at the specified frequency (events per second, such as the fps).
int time_run_at_frequency(double hz, void *userdata, int (*cb)(void *userdata)) {
  SDL_Init(SDL_INIT_TIMER);

  uint64_t perffreq = SDL_GetPerformanceFrequency();
  uint64_t begin = SDL_GetPerformanceCounter();
  uint64_t period = (uint64_t)floor((double)perffreq / (double)hz);

  while (1) {
    int result = cb(userdata);
    if (result != 0) {
      return result;
    }

    uint64_t end = SDL_GetPerformanceCounter();
    uint64_t next_time = begin + period;

    uint64_t sleep_for = next_time - end;
    if (sleep_for >= (uint64_t)INT64_MIN) {
      // this is "sleep_for < 0", but the unsigned modulo version of it
      begin = end;
    } else {
      begin = next_time;

      uint32_t ms = (uint32_t)(sleep_for * 1000 / perffreq);

      SDL_Delay(ms);
    }
  }
}
