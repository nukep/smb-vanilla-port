// If OpenGL is disabled, this module is compiled instead of the regular OpenGL one.
// This implements all the `SMBgl_` functions, but does nothing with them.
// I do it this way to avoid #ifdef'ing for OpenGL support (easier for now).

#include "mario.h"
#include "render_opengl.h"


// An empty struct. Keep it 1 byte, as it's technically the minimum size allowed in C.
struct SMBgl {
  char unused;
};

size_t SMBgl_size(void) {
 return sizeof(struct SMBgl); 
}

// Return false to announce an inability to run OpenGL
bool SMBgl_init(struct SMBgl *gl) {
  (void)gl;
  return false;
}

void SMBgl_fini(struct SMBgl *gl) {
 (void)gl; 
}

void SMBgl_provide_palette_lookup(struct SMBgl *gl, const unsigned char *rgb) {
 (void)gl; (void)rgb; 
}

void SMBgl_update_palette(struct SMBgl *gl, const unsigned char *palette_indices) {
 (void)gl; (void)palette_indices; 
}

void SMBgl_update_pattern_tables(struct SMBgl *gl, const unsigned char *chrrom) {
 (void)gl; (void)chrrom; 
}

void SMBgl_draw_tile(struct SMBgl *gl, const struct SMB_tile tile) {
 (void)gl; (void)tile; 
}

bool SMBgl_render_frame(struct SMBgl *gl) {
 (void)gl; return true; 
}

