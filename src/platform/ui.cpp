#include "ui.hpp"
#include "imgui.h"
#include "smbsession.hpp"

#include <memory>
#include <stdio.h>

#define log_error(msg, ...) fprintf(stderr, "ERROR: " msg "\n", ##__VA_ARGS__)
#define log_info(msg, ...)  fprintf(stdout, "INFO: " msg "\n", ##__VA_ARGS__)

Ui::Ui() {

}

Ui::~Ui() {

}

void Ui::tick() {
  if (this->_session) {
    auto viewport_size = ImGui::GetMainViewport()->Size;
    int viewport_width = (int)viewport_size.x;
    int viewport_height = (int)viewport_size.y;

    this->_session->pre_draw(0, 0, viewport_width, viewport_height);
    this->_session->tick();
    this->_session->post_draw();
  }

  ImGui::BeginMainMenuBar();
  if (ImGui::BeginMenu("File")) {
    if (ImGui::MenuItem("Load ROM")) {
      // Tell the windowing system to conjure up a file picker, and to eventually call try_open_romfile().
      this->_should_load_rom = true;
    }
    ImGui::Separator();
    if (ImGui::MenuItem("Quit")) {
      // Tell the windowing system to quit
      this->_should_quit = true;
    }
    ImGui::EndMenu();
  }
  if (ImGui::BeginMenu("Debug")) {
    if (ImGui::MenuItem("Show ImGui demo window", nullptr, this->_show_demo_window)) {
      this->_show_demo_window = !this->_show_demo_window;
    }
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();

  if (this->_show_demo_window) {
    ImGui::ShowDemoWindow(&this->_show_demo_window);
  }
}

void Ui::try_open_romfile(const char *path) {
  auto session = std::make_unique<SMBSessionCpp>(path);
  if (!session->valid()) {
    return;
  }
  this->_session = std::move(session);
}

void Ui::on_keypress_change(int sdl_scancode, bool isdown) {
  if (this->_session) {
    this->_session->on_keypress_change(sdl_scancode, isdown);
  }
}
