#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "movie.h"

static void report_stderror(const char* message) {
    perror(message);
}

bool movie_init(struct Movie* m, const char* buttons_filename, const char* ramseq_filename) {
    m->buttons_file = fopen(buttons_filename, "rb");
    if (!m->buttons_file) {
        report_stderror("Could not open buttons moviefile");
        return false;
    }
    if (ramseq_filename) {
        m->ramseq_file = fopen(ramseq_filename, "rb");
        if (!m->ramseq_file) {
            report_stderror("Could not open ramseq moviefile");
            return false;
        }
    } else {
        m->ramseq_file = 0;
    }
    m->counter = 0;
    return true;
}

void movie_fini(struct Movie* m) {
    if (m->buttons_file) {
        fclose(m->buttons_file);
    }
    if (m->ramseq_file) {
        fclose(m->ramseq_file);
    }
}

bool movie_readram(struct Movie* m, void* ram) {
    if (m->ramseq_file) {
        // Only write to the ram buffer if it's set and the file's there
        fseek(m->ramseq_file, m->counter * 0x800, SEEK_SET);
        if (fread(ram, 0x800, 1, m->ramseq_file) != 1) {
            // Couldn't read the RAM
            return false;
        }
    } else {
        // The caller asked for RAM, which we can't provide, so it's an error.
        return false;
    }
}

bool movie_next(struct Movie* m, struct MovieButtons* buttons, void *ram) {
    char buf[16];

    // read the line. Note we always read this, even if buttons is null
    if (!fgets(buf, sizeof(buf), m->buttons_file)) {
        return false;
    }

    if (buttons) {
        // Initialize buttons to 0 (false),
        memset(buttons, 0, sizeof(struct MovieButtons));
        // ...and read the buttons on the line
        for (int i = 0; i < sizeof(buf); i++) {
            char c = buf[i];
            if (c == 0) { break; }

            buttons->u      |= c == 'U';
            buttons->d      |= c == 'D';
            buttons->l      |= c == 'L';
            buttons->r      |= c == 'R';
            buttons->a      |= c == 'A';
            buttons->b      |= c == 'B';
            buttons->select |= c == 'S';
            buttons->start  |= c == 'T';
        }
    }

    if (ram && !movie_readram(m, ram)) {
        return false;
    }

    m->counter += 1;
    return true;
}
