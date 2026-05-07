#include "time.h"

#include <emscripten.h>
#include <math.h>

struct em_userdata {
  int (*cb)(void *userdata);
  void *userdata;
};

void em_arg_callback(void *userdata) {
  struct em_userdata *data = userdata;
  int result = data->cb(data->userdata);
  if (result != 0) {
    // Note: This won't actually resume the code after emscripten_set_main_loop_arg().
    emscripten_cancel_main_loop();
  }
}

// Run the callback at the specified frequency (events per second, such as the fps).
int time_run_at_frequency(double hz, void *userdata, int (*cb)(void *userdata)) {
  // Use a static variable to avoid any potential dangling pointer issues when running emscripten_set_main_loop_arg().
  static struct em_userdata data;
  data.cb = cb;
  data.userdata = userdata;

  // So we're not actually using the "hz" argument at all.
  // In order to use requestAnimationFrame, we need to set this to 0.
  // TODO: RAF isn't always 60 fps. Address this later.
  (void)hz;
  int fps_rounded = 0;

  // Simulate an infinite loop
  emscripten_set_main_loop_arg(em_arg_callback, &data, fps_rounded, true);

  return 1;
}

