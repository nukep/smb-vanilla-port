#ifndef UI_HPP
#define UI_HPP

#include <memory>

class SMBSessionCpp;

class Ui {
public:
  Ui();
  ~Ui();

  void tick();

  void try_open_romfile(const char *path);

  // sdl_scancode is an SDL_Scancode, kept as a plain int here so this header
  // doesn't need to include SDL's.
  void on_keypress_change(int sdl_scancode, bool isdown);

  inline bool should_quit() {
    return _should_quit;
  }

  inline bool should_load_rom() {
    if (_should_load_rom) {
      _should_load_rom = false;
      return true;
    }
    return false;
  }

private:
  bool _show_demo_window = false;
  bool _should_quit = false;
  bool _should_load_rom = false;

  std::unique_ptr<SMBSessionCpp> _session;
};

#endif
