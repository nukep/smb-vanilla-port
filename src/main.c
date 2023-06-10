//#define HEADLESS_MODE

//#define USE_MOVIE_SKIP_TO_BEFORE_FRAME 28000
//#define USE_MOVIE_COMPARERAM
//#define USE_MOVIE_LOAD_RAM_AFTER_SKIPAHEAD

#ifndef HEADLESS_MODE
#include <SDL.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "mario.h"

typedef void (*error_callback_t)(const char*);

static const char *ERROR_CONTEXT;

void default_error_cb(const char *message) {
    if (ERROR_CONTEXT) {
        fprintf(stderr, "%s: ", ERROR_CONTEXT);
    }
    fprintf(stderr, "%s\n", message);
}

static error_callback_t error_cb = default_error_cb;

void set_error_context(const char *context) {
    ERROR_CONTEXT = context;
}

#define IOOPEN_READONLY(filename) FILE *__file = fopen(filename, "rb"); if (!__file) { error_cb(strerror(errno)); goto err; }
#define IOOPEN_WRITEONLY(filename) FILE *__file = fopen(filename, "wb"); if (!__file) { error_cb(strerror(errno)); goto err; }
#define IOSEEKTO(offset) if (fseek(__file, offset, SEEK_SET) != 0) { error_cb("Could not seek to offset in file"); goto err; }
#define IOREAD(size, buf) if (fread(buf, size, 1, __file) != 1) { error_cb("Could not read bytes in file"); goto err; }
#define IOWRITE(size, buf) if (fwrite(buf, size, 1, __file) != 1) { error_cb("Could not write bytes in file"); goto err; }
#define IOCLOSE() if (fclose(__file) != 0) { error_cb("Could not close file"); goto err; } return true; err: return false;


struct Pixel {
    byte b;
    byte g;
    byte r;
    byte a;
};

struct Tile {
    byte val[8][8];
};

struct frontend_userdata {
    FILE *romfile;
    byte palette_indices[32];
    size_t pixels_stride;
    struct Pixel *pixels;
    struct Pixel palette[0x40];
    struct Tile tiles[0x200];
};

static struct SMB_buttons PLAYER1_INPUTS;

void joy1(void *userdata, struct SMB_buttons *buttons) {
    *buttons = PLAYER1_INPUTS;
}
void joy2(void *userdata, struct SMB_buttons *buttons) {
}

void update_pattern_tables(struct frontend_userdata *userdata, const byte *chrrom) {
    for (int tileidx = 0; tileidx < 512; tileidx++) {
        struct Tile *t = userdata->tiles + tileidx;
        const byte *buf = chrrom + tileidx*0x10;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                const byte hibit = (buf[i + 8] >> (7 - j)) & 1;
                const byte lobit = (buf[i + 0] >> (7 - j)) & 1;
                t->val[i][j] = (hibit << 1) | lobit;
            }
        }
    }
}

void update_palette(struct frontend_userdata *userdata, const byte *palette_indices) {
    memcpy(userdata->palette_indices, palette_indices, 32);
}

void draw_tile(struct frontend_userdata *userdata, const struct SMB_tile tile) {
    if (!userdata->pixels) {
        return;
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int ii = i;
            int jj = j;
            if (tile.flip_horz) {
                jj = 7-jj;
            }
            if (tile.flip_vert) {
                ii = 7-ii;
            }
            jj += tile.x;
            ii += tile.y;
            if (ii < 0 || ii >= 240) {
                continue;
            }
            if (jj < 0 || jj >= 256) {
                continue;
            }

            struct Pixel *p = userdata->pixels + jj + ii*userdata->pixels_stride;
            byte v = userdata->tiles[tile.tileidx].val[i][j];
            if (v == 0) {
                continue;
            }
            
            *p = userdata->palette[userdata->palette_indices[tile.paletteidx * 4 + v] & 0x3F];
        }
    }
}

bool load_palette(struct frontend_userdata *userdata, const char *filename) {
    IOOPEN_READONLY(filename);
    byte out[3];

    for (int i = 0; i < 0x40; i++) {
        IOREAD(3, &out);
        struct Pixel *p = userdata->palette + i;
        p->r = out[0];
        p->g = out[1];
        p->b = out[2];
        p->a = 255;
    }
    IOCLOSE();
}

bool load_ppuram(struct SMB_state *state, const char *filename) {
    IOOPEN_READONLY(filename);
    IOREAD(0x4000, SMB_ppuram(state));
    IOCLOSE();
}

bool dump_ppuram(struct SMB_state *state, const char *filename) {
    IOOPEN_WRITEONLY(filename);
    IOWRITE(0x4000, SMB_ppuram(state));
    IOCLOSE();
}

bool load_ram(struct SMB_state *state, const char *filename) {
    IOOPEN_READONLY(filename);
    IOREAD(0x800, SMB_ram(state));
    IOCLOSE();
}

bool dump_ram(struct SMB_state *state, const char *filename) {
    IOOPEN_WRITEONLY(filename);
    IOWRITE(0x800, SMB_ram(state));
    IOCLOSE();
}

byte smb2j_load_games_beaten(void *userdata) {
    // A decent test value - lets us test Worlds A-D
    return 8;
}
bool smb2j_save_games_beaten(void *userdata, byte games_beaten) {
    printf("Pretending to save game...");
    printf("Games beaten: %d\n", games_beaten);
    return true;
}

#include "movie.h"

bool run_at_60fps() {
    // This needs to be implemented properly, but that'll happen when we get audio
    SDL_Delay(15);

    return true;
}

const char *ppuram_filename = "ppuram.bin";
const char *ram_filename = "ram.bin";

int framecounter = 0;

static struct Movie *CURRENT_MOVIE;

bool advance_movie(struct SMB_state *smb_state) {
    if (!CURRENT_MOVIE) {
        return false;
    }

    struct MovieButtons movie_buttons;

    byte *ram = 0;
#ifdef USE_MOVIE_COMPARERAM
    byte rambuf[0x800];
    ram = rambuf;
#endif

    bool use_movie_buttons = movie_next(CURRENT_MOVIE, &movie_buttons, ram);
    if (use_movie_buttons) {
#ifdef USE_MOVIE_COMPARERAM
        if (framecounter != 0) {
            // Don't compare the first frame, because the movie's ramseq's first frame occurs after Reset and before the first NMI.
            // SMB_tick calls Reset if it hasn't been called before. If we're here, then Reset has never been called.
            // Additionally, we can go without comparing it, as memory before the first NMI is not very interesting.

            byte *compareto = SMB_ram(smb_state);

            // RAM errors start at frame 16600, when we go underwater

#define mem_eq_range(from, upto) do { \
                const byte *a = ram; \
                const byte *b = compareto; \
                size_t len = (upto) + 1 - (from); \
                for (size_t i = (from); i <= (upto); i++) { \
                    if (a[i] != b[i]) { \
                        printf("Caused by frame %05d: RAM not equal: At %04lX: %02X expected vs %02X actual\n", framecounter-1, i, a[i], b[i]); \
                    } \
                } \
            } while (0)

            // Missing ranges:
            // $160-$1FF is the stack (this port doesn't use this)

            if (SMB_which_game(smb_state) == GAME_SMB1) {
                mem_eq_range(0x0008, 0x00FF);
                mem_eq_range(0x0100, 0x015F);
                mem_eq_range(0x0200, 0x07FF);
            } else if (SMB_which_game(smb_state) == GAME_SMB2J) {
                // FDS may modify $00-$0F and $F5-$FF with BIOS subroutines, so they're unreliable
                mem_eq_range(0x0010, 0x00EF);
                mem_eq_range(0x0109, 0x015F);
                mem_eq_range(0x0200, 0x07FF);
            }
        }
#endif

        PLAYER1_INPUTS.u = movie_buttons.u;
        PLAYER1_INPUTS.d = movie_buttons.d;
        PLAYER1_INPUTS.l = movie_buttons.l;
        PLAYER1_INPUTS.r = movie_buttons.r;
        PLAYER1_INPUTS.b = movie_buttons.b;
        PLAYER1_INPUTS.a = movie_buttons.a;
        PLAYER1_INPUTS.select = movie_buttons.select;
        PLAYER1_INPUTS.start = movie_buttons.start;
    }
    return use_movie_buttons;
}

int sdl_frontend(struct SMB_state *smb_state, struct frontend_userdata *userdata) {
    const int video_scale = 3;

    SDL_Window *window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
        "smb-port",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        256 * video_scale, 240 * video_scale,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }
    SDL_FillRect(SDL_GetWindowSurface(window), NULL, SDL_MapRGB(SDL_GetWindowSurface(window)->format, 0x00, 0x00, 0x00));
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    SDL_Surface *surf = SDL_CreateRGBSurface(0, 256 * 2, 240, 32, 0, 0, 0, 0);
    const int stride = 256 * 2;

    while (run_at_60fps()) {
        bool use_movie_buttons = false;

        use_movie_buttons = advance_movie(smb_state);

        SDL_Event eventData;
        while (SDL_PollEvent(&eventData))
        {
            switch (eventData.type)
            {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                bool isdown = eventData.key.state == SDL_PRESSED;
                auto sc = eventData.key.keysym.scancode;
                if (isdown && !eventData.key.repeat) {
                    switch (sc) {
                    case SDL_SCANCODE_1:
                        if (load_ppuram(smb_state, ppuram_filename)) {
                            if (!load_ram(smb_state, ram_filename)) {
                                // Couldn't load RAM - exit
                                return true;
                            }
                        }
                        break;
                    case SDL_SCANCODE_0:
                        // dump the RAM and PPU
                        dump_ppuram(smb_state, ppuram_filename);
                        dump_ram(smb_state, ram_filename);
                        break;
                    }
                }
                if (!use_movie_buttons) {
                    switch (sc) {
                    case SDL_SCANCODE_W: PLAYER1_INPUTS.u = isdown; break;
                    case SDL_SCANCODE_S: PLAYER1_INPUTS.d = isdown; break;
                    case SDL_SCANCODE_A: PLAYER1_INPUTS.l = isdown; break;
                    case SDL_SCANCODE_D: PLAYER1_INPUTS.r = isdown; break;
                    case SDL_SCANCODE_J: PLAYER1_INPUTS.b = isdown; break;
                    case SDL_SCANCODE_K: PLAYER1_INPUTS.a = isdown; break;
                    case SDL_SCANCODE_U: PLAYER1_INPUTS.select = isdown; break;
                    case SDL_SCANCODE_I: PLAYER1_INPUTS.start = isdown; break;
                    }
                }
            }
            break;
            case SDL_QUIT:
                goto exit;
            }
        }

        // Fill with background color
        const struct Pixel bgcolor = userdata->palette[userdata->palette_indices[0]];
        SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, bgcolor.r, bgcolor.g, bgcolor.b));

        SDL_LockSurface(surf);
        struct Pixel *pixels = surf->pixels;

        userdata->pixels = pixels;
        userdata->pixels_stride = stride;

        SMB_tick(smb_state);
        framecounter += 1;

        userdata->pixels = 0;

        SDL_UnlockSurface(surf);

        const SDL_Rect srcrect = { 0, 0, 256, 240 };
        SDL_Rect dstrect = { 0, 0, 256 * video_scale, 240 * video_scale };
        SDL_BlitScaled(surf, &srcrect, SDL_GetWindowSurface(window), &dstrect);


        SDL_UpdateWindowSurface(window);
    }

exit:
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


#ifndef USE_MOVIE_SKIP_TO_BEFORE_FRAME
#	define USE_MOVIE_SKIP_TO_BEFORE_FRAME 0
#endif

#define HANDLEERR(expr, context) do { \
    set_error_context(context); \
    int val = expr; \
    set_error_context(0); \
    if (!val) { return 1; } \
} while(0)

bool open_rom(struct frontend_userdata *userdata, const char *filename) {
    FILE *f = fopen(filename, "rb");
    userdata->romfile = f;
    return f != 0;
}



bool read_rom_bytes(struct frontend_userdata *userdata, byte *buf, size_t size) {
    return fread(buf, size, 1, userdata->romfile) == 1;
}

bool seek_rom(struct frontend_userdata *userdata, size_t offset) {
    fseek(userdata->romfile, offset, SEEK_SET);
    return true;
}

int main(int argc, char *argv[]) {
    struct SMB_state *smb_state = malloc(SMB_state_size());
    struct frontend_userdata *userdata = malloc(sizeof(struct frontend_userdata));

    if (!smb_state || !userdata) {
        return 1;
    }

    memset(userdata, 0, sizeof(struct frontend_userdata));
    if (argc <= 1) {
        printf("Please provide a SMB1 or SMB2J (Lost Levels) rom!\n");
        return 1;
    }

    open_rom(userdata, argv[1]);

    struct SMB_callbacks callbacks = {
        .userdata = userdata,

        .read_rom_bytes = read_rom_bytes,
        .seek_rom = seek_rom,
        .smb2j_load_games_beaten = smb2j_load_games_beaten,
        .smb2j_save_games_beaten = smb2j_save_games_beaten,

        .update_pattern_tables = update_pattern_tables,
        .update_palette = update_palette,
        .draw_tile = draw_tile,
        .joy1 = joy1,
        .joy2 = joy2,
    };

    SMB_state_init(smb_state, &callbacks);

    printf("Started!\n");

    if (argc > 2) {
        struct Movie *m = malloc(sizeof(struct Movie));
        char buttons_filename[1024];
        char ram_filename[1024];
        snprintf(buttons_filename, sizeof(buttons_filename), "%smovie-buttons.txt", argv[2]);
        snprintf(ram_filename, sizeof(ram_filename), "%smovie-ram.bin", argv[2]);
        if (!movie_init(m, buttons_filename, ram_filename)) {
            printf("Could not load movie\n");
        }
        CURRENT_MOVIE = m;
    }

    int skipto = USE_MOVIE_SKIP_TO_BEFORE_FRAME;

    if (skipto > 0) {
        bool movie_is_valid = true;

        for (int i = 0; i < skipto; i++) {
            if (advance_movie(smb_state)) {
                SMB_tick(smb_state);
                framecounter += 1;
            } else {
                movie_is_valid = false;
                break;
            }
        }

#ifdef USE_MOVIE_LOAD_RAM_AFTER_SKIPAHEAD
        if (movie_is_valid) {
            movie_readram(CURRENT_MOVIE, SMB_ram(smb_state));
        }
#endif
    }

    HANDLEERR(load_palette(userdata, "palette.pal"), "Could not load palette");
    return sdl_frontend(smb_state, userdata);
}
