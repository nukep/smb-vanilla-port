#ifndef RENDER_OPENGL
#define RENDER_OPENGL

#include <stdbool.h>
#include <stdlib.h>

struct SMBgl;

size_t SMBgl_size(void);

bool SMBgl_init(struct SMBgl *gl);
void SMBgl_fini(struct SMBgl *gl);

// Upload a list of 64 RGB values. The data is copied.
void SMBgl_provide_palette_lookup(struct SMBgl *gl, const unsigned char *rgb);

void SMBgl_update_palette(struct SMBgl *gl, const unsigned char *palette_indices);
void SMBgl_update_pattern_tables(struct SMBgl *gl, const unsigned char *chrrom);
void SMBgl_draw_tile(struct SMBgl *gl, const struct SMB_tile tile);

bool SMBgl_render_frame(struct SMBgl *gl);

#endif
