#ifndef UI_HPP
#define UI_HPP

#include "smbsession.hpp"

#include <memory>

class Ui {
public:
  Ui();
  ~Ui();

  void tick();

  void try_open_romfile(const char *path);

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

  std::unique_ptr<SMBSession> _session;
};

#endif
