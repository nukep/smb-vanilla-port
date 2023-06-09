#ifndef MOVIE_H
#define MOVIE_H

#include <stdbool.h>
#include <stdio.h>

struct MovieButtons {
    bool u, d, l, r, a, b, select, start;
};

struct Movie {
    FILE* buttons_file;
    FILE* ramseq_file;
    size_t counter;
};

#ifdef __cplusplus
extern "C" {
#endif

bool movie_init(struct Movie *m, const char *buttons_filename, const char *ramseq_filename);
void movie_fini(struct Movie *m);
bool movie_next(struct Movie *m, struct MovieButtons* buttons, void *ram);
bool movie_readram(struct Movie* m, void* ram);

#ifdef __cplusplus
}
#endif

#endif
