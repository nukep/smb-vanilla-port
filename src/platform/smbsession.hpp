#ifndef SMBSESSION_HPP
#define SMBSESSION_HPP

#ifdef __cplusplus
extern "C" {
#endif

#  include "smbsession.h"

#ifdef __cplusplus
}
#endif

#include <cstdlib>

// A thin C++ wrapper around smbsession's C API

class SMBSessionCpp {
public:
  inline SMBSessionCpp(const char *rompath) {
    this->_session = (struct SMBSession*)malloc(SMBSession_size());
    SMBSession_init(this->_session, rompath);
  }

  inline ~SMBSessionCpp() {
    SMBSession_fini(this->_session);
    free(this->_session);
  }

  inline void tick() {
    SMBSession_tick(this->_session);
  }

  inline void on_keypress_change(int sdl_scancode, bool isdown) {
    SMBSession_on_keypress_change(this->_session, sdl_scancode, isdown);
  }

  // False if the ROM failed to load. The session is otherwise unusable.
  inline bool valid() const {
    return SMBSession_valid(this->_session);
  }

private:
  struct SMBSession *_session;
};

#endif
