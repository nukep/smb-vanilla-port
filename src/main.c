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
#include "movie.h"
#include "audio.h"
#include "time.h"

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
    struct SMB_state *smb_state;
    struct SMB_audio *audio;

    SDL_Window *window;
    SDL_Surface *surf;
    int video_scale;
    struct Pixel *pixels;
    size_t pixels_stride;

    byte palette_indices[32];
    struct Pixel palette[0x40];
    struct Tile tiles[0x200];
};

static struct SMB_buttons PLAYER1_INPUTS;

void joy1(void *userdata, struct SMB_buttons *buttons) {
    *buttons = PLAYER1_INPUTS;
}
void joy2(void *userdata, struct SMB_buttons *buttons) {
}

void update_pattern_tables(void *userdata, const byte *chrrom) {
    struct frontend_userdata *fe = userdata;
    for (int tileidx = 0; tileidx < 512; tileidx++) {
        struct Tile *t = fe->tiles + tileidx;
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

void update_palette(void *userdata, const byte *palette_indices) {
    struct frontend_userdata *fe = userdata;
    memcpy(fe->palette_indices, palette_indices, 32);
}

void draw_tile(void *userdata, const struct SMB_tile tile) {
    struct frontend_userdata *fe = userdata;
    if (!fe->pixels) {
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

            struct Pixel *p = fe->pixels + jj + ii*fe->pixels_stride;
            byte v = fe->tiles[tile.tileidx].val[i][j];
            if (v == 0) {
                continue;
            }
            
            *p = fe->palette[fe->palette_indices[tile.paletteidx * 4 + v] & 0x3F];
        }
    }
}

bool load_palette(void *userdata, const char *filename) {
    struct frontend_userdata *fe = userdata;
    IOOPEN_READONLY(filename);
    byte out[3];

    for (int i = 0; i < 0x40; i++) {
        IOREAD(3, &out);
        struct Pixel *p = fe->palette + i;
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

const char *ppuram_filename = "ppuram.bin";
const char *ram_filename = "ram.bin";

int framecounter = 0;

static struct Movie *CURRENT_MOVIE;

bool advance_movie(struct SMB_state *smb_state) {
    if (!CURRENT_MOVIE) {
        return false;
    }

    struct MovieButtons movie_buttons;

    bool use_movie_buttons = movie_next(CURRENT_MOVIE, &movie_buttons, 0);
    if (use_movie_buttons) {
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

int sdl_tick(void *userdata) {
    struct frontend_userdata *fe = userdata;
    struct SMB_state *smb_state = fe->smb_state;
    SDL_Surface *surf = fe->surf;
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
            SDL_Scancode sc = eventData.key.keysym.scancode;
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
            return 1;
        }
    }

    // Fill with background color
    const struct Pixel bgcolor = fe->palette[fe->palette_indices[0]];
    SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, bgcolor.r, bgcolor.g, bgcolor.b));

    SDL_LockSurface(surf);
    struct Pixel *pixels = surf->pixels;

    fe->pixels = pixels;

    SMB_tick(smb_state);
    framecounter += 1;

    fe->pixels = 0;

    SDL_UnlockSurface(surf);

    const SDL_Rect srcrect = { 0, 0, 256, 240 };
    SDL_Rect dstrect = { 0, 0, 256 * fe->video_scale, 240 * fe->video_scale };
    SDL_BlitScaled(surf, &srcrect, SDL_GetWindowSurface(fe->window), &dstrect);

    SDL_UpdateWindowSurface(fe->window);
    return 0;
}

int sdl_frontend(void *userdata) {
    struct frontend_userdata *fe = userdata;
    fe->video_scale = 3;

    SDL_Window *window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
        "smb-port",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        256 * fe->video_scale, 240 * fe->video_scale,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }
    SDL_FillRect(SDL_GetWindowSurface(window), NULL, SDL_MapRGB(SDL_GetWindowSurface(window)->format, 0x00, 0x00, 0x00));
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    SDL_Surface *surf = SDL_CreateRGBSurface(0, 256, 240, 32, 0, 0, 0, 0);
    fe->surf = surf;
    fe->pixels_stride = 256;
    fe->window = window;

    // On an NTSC NES: clocks per second, divided by clocks per frame
    // (approx 60.0988 fps)
    const double fps = 1789773.0/29780.5;

    time_run_at_frequency(fps, userdata, sdl_tick);

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

bool open_rom(void *userdata, const char *filename) {
    struct frontend_userdata *fe = userdata;
    FILE *f = fopen(filename, "rb");
    fe->romfile = f;
    return f != 0;
}



bool read_rom_bytes(void *userdata, byte *buf, size_t size) {
    struct frontend_userdata *fe = userdata;
    return fread(buf, size, 1, fe->romfile) == 1;
}

bool seek_rom(void *userdata, size_t offset) {
    struct frontend_userdata *fe = userdata;
    fseek(fe->romfile, offset, SEEK_SET);
    return true;
}

void apu_write_register(void *userdata, ushort addr, byte data) {
    struct frontend_userdata *fe = userdata;
    if (fe->audio) {
        SMB_audio_write_register(fe->audio, addr, data);
    }
}
void apu_end_frame(void *userdata) {
    struct frontend_userdata *fe = userdata;
    if (fe->audio) {
        SMB_audio_end_frame(fe->audio);
    }
}

struct cli_args {
    const char *rom_filename;
    const char *movie_prefix;
    int world;
    int level;
};

#define PEEK_EQ(s) (i < argc && (strcmp(argv[i], s) == 0))
#define POP_IF_EXISTS() if (i >= argc) { ptr = 0; } ptr = argv[i++]
#define POP() if (i >= argc) { return false; } ptr = argv[i++]

bool parse_cli_args(int argc, char *argv[], struct cli_args *out) {
    char *ptr = 0;
    int i = 1;
    int last_i;

    out->world = 1;
    out->level = 1;

    // The rom is the first argument by default
    if (!out->rom_filename) {
        POP_IF_EXISTS();
        out->rom_filename = ptr;
    }

    do {
        last_i = i;
        if (PEEK_EQ("--rom")) { 
            POP();
            POP();
            out->rom_filename = ptr;
        }
        if (PEEK_EQ("--movie") || PEEK_EQ("-m")) {
            POP();
            POP();
            out->movie_prefix = ptr;
        }
        if (PEEK_EQ("--level") || PEEK_EQ("-l")) {
            int world=0;
            int level=0;
            POP();
            POP();
            if (sscanf(ptr, "%d-%d", &world, &level) == 2) {
                out->world = world;
                out->level = level;
            } else {
                return false;
            }
        }
    } while (last_i != i);

    return true;
}

#undef POP
#undef POP_IF_EXISTS
#undef PEEK_EQ

int main(int argc, char *argv[]) {
    struct cli_args args = {0};
    bool audio_enabled = true;

    if (!parse_cli_args(argc, argv, &args)) {
        printf("Could not parse args\n");
        return 1;
    }

    struct SMB_state *smb_state = malloc(SMB_state_size());
    struct frontend_userdata *userdata = malloc(sizeof(struct frontend_userdata));

    if (!smb_state || !userdata) {
        return 1;
    }

    struct SMB_audio *audio = 0;

    if (audio_enabled) {
        audio = malloc(SMB_audio_size());
    }

    memset(userdata, 0, sizeof(struct frontend_userdata));
    if (!args.rom_filename) {
        printf("Please provide a SMB1 or SMB2J (Lost Levels) rom!\n");
        return 1;
    }

    if (audio && !SMB_audio_init(audio)) {
        printf("Could not initialize audio!\n");
        free(audio);
        audio = 0;
        audio_enabled = false;
    }

    open_rom(userdata, args.rom_filename);

    struct SMB_callbacks callbacks = {0};
    callbacks.userdata = userdata;

    callbacks.read_rom_bytes = read_rom_bytes;
    callbacks.seek_rom = seek_rom;
    callbacks.smb2j_load_games_beaten = smb2j_load_games_beaten;
    callbacks.smb2j_save_games_beaten = smb2j_save_games_beaten;

    callbacks.apu_write_register = apu_write_register;
    callbacks.apu_end_frame = apu_end_frame;

    callbacks.update_pattern_tables = update_pattern_tables;
    callbacks.update_palette = update_palette;
    callbacks.draw_tile = draw_tile;
    callbacks.joy1 = joy1;
    callbacks.joy2 = joy2;

    SMB_state_init(smb_state, &callbacks);
    SMB_start_on_level(smb_state, args.world, args.level);
    userdata->smb_state = smb_state;

    printf("Started!\n");

    if (args.movie_prefix) {
        struct Movie *m = malloc(sizeof(struct Movie));
        char buttons_filename[1024];
        char ram_filename[1024];
        snprintf(buttons_filename, sizeof(buttons_filename), "%smovie-buttons.txt", args.movie_prefix);
        snprintf(ram_filename, sizeof(ram_filename), "%smovie-ram.bin", args.movie_prefix);
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
    userdata->audio = audio;

    HANDLEERR(load_palette(userdata, "palette.pal"), "Could not load palette");
    int exitcode = sdl_frontend(userdata);

    if (audio) {
        SMB_audio_fini(audio);
    }

    return exitcode;
}
