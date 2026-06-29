#ifndef RENDER_RASTER
#define RENDER_RASTER

#include <stdbool.h>
#include <stdlib.h>

struct SMBraster;

size_t SMBraster_size(void);

bool SMBraster_init(struct SMBraster *r);
void SMBraster_fini(struct SMBraster *r);

// Upload a list of 64 RGB values. The data is copied.
void SMBraster_provide_palette_lookup(struct SMBraster *r, const unsigned char *rgb);

void SMBraster_update_palette(struct SMBraster *r, const unsigned char *palette_indices);
void SMBraster_update_pattern_tables(struct SMBraster *r, const unsigned char *chrrom);
void SMBraster_draw_tile(struct SMBraster *r, const struct SMB_tile tile);

void SMBraster_set_buffer(struct SMBraster *r, unsigned char *rgb_pixels, int stride);
void SMBraster_clear(struct SMBraster *r);

#endif
