#ifndef SMBSESSION_H
#define SMBSESSION_H

#include <stdbool.h>
#include <stddef.h>

// Manages a gameplay session and its resources.
// Owns the SMB_state object, and ways to control it at a higher level.

struct SMBSession;

size_t SMBSession_size(void);

bool SMBSession_init(struct SMBSession *s, const char *rompath);
void SMBSession_fini(struct SMBSession *s);

void SMBSession_tick(struct SMBSession *s);

void SMBSession_on_keypress_change(struct SMBSession *s, int sdl_scancode, bool isdown);

bool SMBSession_valid(const struct SMBSession *s);

#endif
