#include "imgui.h"
#ifdef USE_SDL2
#  include "imgui_impl_sdl2.h"
#else
#  include "imgui_impl_sdl3.h"
#endif
#include "imgui_impl_opengl3.h"

extern "C" {
#include "windowing_sdl.h"

#ifdef USE_SDL2
#  include <SDL.h>
#  include <SDL_opengl.h>
#else
#  include <SDL3/SDL.h>
#  include <SDL3/SDL_opengl.h>
#endif
}

void preprocess_event(void *userdata, SDL_Event *e) {
#ifdef USE_SDL2
  ImGui_ImplSDL2_ProcessEvent(e);
#else
  ImGui_ImplSDL3_ProcessEvent(e);
#endif
}

void on_keypress_change(void *userdata, SDL_Scancode sc, bool isdown) {

}

bool tick(void *userdata) {
  static bool show_demo_window = false;

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL3_NewFrame();
#ifdef USE_SDL2
  ImGui_ImplSDL2_NewFrame();
#else
  ImGui_ImplSDL3_NewFrame();
#endif
  ImGui::NewFrame();

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

  return true;
}

int main(int argc, char *argv[]) {
  const struct windowing_sdl_init_settings settings = {
    .opengl = true,
    .maxspeed = false,
    .video_scale = 2,
    .preprocess_event = preprocess_event,
    .on_keypress_change = on_keypress_change,
    .tick = tick,
  };

  windowing_init(&settings);

  float main_scale = 1.0f;

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

#ifdef USE_SDL2
  ImGui_ImplSDL2_InitForOpenGL(windowing_sdl_window(), windowing_sdl_glcontext());
#else
  ImGui_ImplSDL3_InitForOpenGL(windowing_sdl_window(), windowing_sdl_glcontext());
#endif
  ImGui_ImplOpenGL3_Init();

  windowing_loop();

  windowing_fini();
}
