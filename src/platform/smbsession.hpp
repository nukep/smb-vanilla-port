#ifndef SMBSESSION_HPP
#define SMBSESSION_HPP

struct SMB_state;

// A class to manage a gameplay session and its resources.
// Includes the SMB_state object, and ways to control it at a higher level.

class SMBSession {
public:
  SMBSession(const char *rompath);
  ~SMBSession();

  void tick();
private:
  struct SMB_state *smb_state = nullptr;
};

#endif
