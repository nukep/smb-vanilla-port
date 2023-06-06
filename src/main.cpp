#include <SDL.h>
#include <stdio.h>

#include "config.h"

// Declare these - these are the entrypoints of the game
void Reset();
void NMI();

typedef unsigned char byte;
typedef unsigned short ushort;
byte& RAM(ushort offset);
byte& CHRROM_writable(ushort offset);
const byte& CHRROM(ushort offset);


// Represents the internal PPU register.
union ppureg {
    struct {
        // least to most significant order
        byte XXXXX : 5;
        byte YYYYY : 5;
        byte NN : 2;
        byte yyy : 3;
    };
    struct {
        byte lo : 8;
        byte hi : 7;
    };
    ushort value;
};

struct Pixel {
    byte b;
    byte g;
    byte r;
    byte a;
};

struct Tile {
    byte val[8][8];
};

struct ppu_state {
    byte buffer[0x4000];

    // internal regs
    ppureg v;
    ppureg t;
    byte x;
    byte w;
    byte increment_mode;

    Pixel palette[0x40];
    Tile tiles[0x200];
};

static ppu_state PPU_STATE;

// Write to $2000
void ppuctrl(byte x) {
    PPU_STATE.t.NN = x & 0x03;
    PPU_STATE.increment_mode = (x & 0x04) ? 1 : 0;
}

// Write to $2001
void ppumask(byte x) {
}

// Write to $2005
void ppuscroll(byte x) {
    if (PPU_STATE.w == 0) {
        PPU_STATE.t.XXXXX = x >> 3;
        PPU_STATE.x = x & 0x07;
    }
    else {
        PPU_STATE.t.YYYYY = x >> 3;
        PPU_STATE.t.yyy = x & 0x07;
    }
    PPU_STATE.w ^= 1;
}

// Write to $2006
void ppuaddr(byte x) {
    if (PPU_STATE.w == 0) {
        PPU_STATE.t.hi = x & 0x3F;
    }
    else {
        PPU_STATE.t.lo = x;
        PPU_STATE.v = PPU_STATE.t;
    }
    PPU_STATE.w ^= 1;
}

// Write to $2007
void ppudata(byte x) {
    ushort& v = PPU_STATE.v.value;

    ushort addr = v & 0x3FFF;

    if (addr == 0x3F10) {
        addr = 0x3F00;
    }

    PPU_STATE.buffer[addr] = x;

    if (PPU_STATE.increment_mode == 0) {
        v += 1;
    }
    else {
        v += 32;
    }
}
// Write to $4016
void joystick_strobe(byte x) {
}
// Write to $4011
void apu_dmc_raw(byte x) {
}
// Write to $4015
void apu_snd_chn(byte x) {
}

// Read from $2002
byte ppustatus() {
    PPU_STATE.w = 0;
    return 0x80;
}

struct PlayerInput {
    bool a, b, select, start;
    bool u, d, l, r;
};

static PlayerInput PLAYER1_INPUTS;
static int PLAYER1_INPUT_COUNTER = 0;


byte joy1() {
    PlayerInput& c = PLAYER1_INPUTS;
    PLAYER1_INPUT_COUNTER %= 8;
    switch (PLAYER1_INPUT_COUNTER++) {
    case 0: return c.a;
    case 1: return c.b;
    case 2: return c.select;
    case 3: return c.start;
    case 4: return c.u;
    case 5: return c.d;
    case 6: return c.l;
    case 7: return c.r;
    default: return 0;
    }
}
byte joy2() {
    return 0;
}

static byte SCROLL_WITHIN_NT = 0;
static byte SCROLL_NT = 0;

void announce_main_scroll() {
    int scroll = PPU_STATE.t.XXXXX*8 + PPU_STATE.x;
    SCROLL_WITHIN_NT = scroll;
    SCROLL_NT = PPU_STATE.t.NN;
}

struct Sprite {
    int x;
    int y;
    int tileidx;
    int palette;
    bool draw_behind;
    bool flip_horz;
    bool flip_vert;
};

static Sprite ACTIVE_SPRITES[64];

void transfer_sprite_data(const byte *data) {
    for (int i = 0; i < 64; i++) {
        Sprite &s = ACTIVE_SPRITES[i];
        s.y = data[i * 4 + 0] + 1;
        s.tileidx = data[i * 4 + 1];
        byte attr = data[i * 4 + 2];
        s.x = data[i * 4 + 3];

        s.palette = attr & 0x03;
        s.draw_behind = (attr & 0x20) != 0;
        s.flip_horz = (attr & 0x40) != 0;
        s.flip_vert = (attr & 0x80) != 0;
    }
}

void load_pattern_tables() {
    for (int tileidx = 0; tileidx < 512; tileidx++) {
        Tile* t = PPU_STATE.tiles + tileidx;
        const byte* buf = &CHRROM(tileidx * 0x10);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                const byte hibit = (buf[i + 8] >> (7 - j)) & 1;
                const byte lobit = (buf[i + 0] >> (7 - j)) & 1;
                t->val[i][j] = (hibit << 1) | lobit;
            }
        }
    }
}

void draw_tile(Pixel *pixels, int stride, int tileidx, int paletteidx, bool flip_horz, bool flip_vert, int x, int y) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int ii = i;
            int jj = j;
            if (flip_horz) {
                jj = 7-jj;
            }
            if (flip_vert) {
                ii = 7-ii;
            }
            jj += x;
            ii += y;
            if (ii < 0 || ii >= 240) {
                continue;
            }
            if (jj < 0 || jj >= 256) {
                continue;
            }

            Pixel *p = pixels + jj + ii*stride;
            byte v = PPU_STATE.tiles[tileidx].val[i][j];
            if (v == 0) {
                continue;
            }
            *p = PPU_STATE.palette[PPU_STATE.buffer[0x3F00 + paletteidx * 4 + v] & 0x3F];
        }
    }
}

void draw_nametable_tile(Pixel *pixels, int stride, int x, int y, ushort ppu_offset, int tilex, int tiley) {
    int j = tilex;
    int i = tiley;
    int off = i * 32 + j;
    int tileidx = PPU_STATE.buffer[ppu_offset + off] + 0x100;
    // Find which part of the pallete to use
    // Look it up in the attribute table

    byte a = PPU_STATE.buffer[ppu_offset + 0x03c0 + (i / 4) * 8 + (j / 4)];
    a >>= ((j / 2) % 2) * 2;
    a >>= ((i / 2) % 2) * 4;
    a &= 0x03;
    int paletteidx = a;

    draw_tile(pixels, stride, tileidx, paletteidx, false, false, x, y);
}

void draw_nametable_rect(Pixel* pixels, int stride, int x, int y, ushort ppu_offset, int fromx, int fromy, int tox, int toy) {
    for (int i = fromy; i < toy; i++) {
        for (int j = fromx; j < tox; j++) {
            draw_nametable_tile(pixels, stride, x + (j - fromx) * 8, y + (i-fromy) * 8, ppu_offset, j, i);
        }
    }
}

int load_palette() {
    FILE* f = fopen("palette.pal", "rb");
    if (!f) {
        return 0;
    }
    byte out[3];

    for (int i = 0; i < 0x40; i++) {
        if (fread(&out, 1, 3, f) != 3) {
            return 0;
        }
        Pixel* p = PPU_STATE.palette + i;
        p->r = out[0];
        p->g = out[1];
        p->b = out[2];
        p->a = 255;
    }
    fclose(f);
    return 1;
}

int load_ppuram(const char *filename) {
    FILE* f = fopen(filename, "rb");
    if (f) {
        fread(&PPU_STATE.buffer, 1, 0x4000, f);
        fclose(f);
        printf("PPU RAM loaded\n");
        return 1;
    } else {
        printf("Could not load PPU RAM\n");
        return 0;
    }
}

void dump_ppuram(const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (f) {
        fwrite(&PPU_STATE.buffer, 1, 0x4000, f);
        fclose(f);
        printf("PPU RAM dumped\n");
    } else {
        printf("Could not dump PPU RAM\n");
    }
}

int load_ram(const char* filename) {
    byte* ram = &RAM(0x0);
    FILE* f = fopen(filename, "rb");
    if (f) {
        fread(ram, 1, 0x800, f);
        fclose(f);
        printf("RAM loaded\n");
        return 1;
    } else {
        printf("Could not load RAM\n");
        return 0;
    }
}

void dump_ram(const char *filename) {
    const byte* ram = &RAM(0x0);
    FILE* f = fopen(filename, "wb");
    if (f) {
        fwrite(ram, 1, 0x800, f);
        fclose(f);
        printf("RAM dumped\n");
    } else {
        printf("Could not dump RAM\n");
    }
}

int init_rom(const char* filename) {
    byte* rom_org = &RAM(0x8000);
    byte* chrrom_org = &CHRROM_writable(0x0000);

    FILE* f = fopen(filename, "rb");
    if (f) {
        fseek(f, 0x10, SEEK_SET);
        fread(rom_org, 1, 0x8000, f);
        fread(chrrom_org, 1, 0x2000, f);
        fclose(f);
        load_pattern_tables();

        printf("ROM loaded\n");
        return 1;
    } else {
        printf("Could not open ROM\n");
        return 0;
    }
}

struct FdsFile {
    const char *name;
    size_t file_offset;
    ushort size;
    ushort org;
    int type;
    void *data;
};

#define TYPE_PRGRAM 0
#define TYPE_CHRRAM 1


#define FDS_FILES_COUNT 7

// hard-code some offsets for now
// assuming file has a 16-byte header (starts with 46 44 53, i.e. "FDS")
static FdsFile FDS_FILES[FDS_FILES_COUNT] = {
    {"SM2CHAR1", 0x014C, 0x2000, 0x0000, TYPE_CHRRAM},
    {"SM2CHAR2", 0x215D, 0x0040, 0x0760, TYPE_CHRRAM},
    {"SM2MAIN ", 0x21AE, 0x8000, 0x6000, TYPE_PRGRAM},
    {"SM2DATA2", 0xA1BF, 0x0E2F, 0xC470, TYPE_PRGRAM},
    {"SM2DATA3", 0xAFFF, 0x0CCF, 0xC5D0, TYPE_PRGRAM},
    {"SM2DATA4", 0xBCDF, 0x0F4C, 0xC2B4, TYPE_PRGRAM},
    {"SM2SAVE ", 0xCC3C, 0x0001, 0xD29F, TYPE_PRGRAM},
};

#include <cstring>


bool write_games_beaten_to_provider(byte games_beaten) {
    const char *name = "SM2SAVE ";
    for (int i = 0; i < FDS_FILES_COUNT; i++) {
        const FdsFile& a = FDS_FILES[i];
        bool eq = strncmp(name, a.name, 8) == 0;
        if (eq) {
            // Found it!
            // TODO - persist this somewhere
            byte *data = (byte*)a.data;
            data[0] = games_beaten;
            return true;
        }
    }
    return false;
}

bool load_file_from_provider(const char *name) {
    for (int i = 0; i < FDS_FILES_COUNT; i++) {
        const FdsFile& a = FDS_FILES[i];
        bool eq = strncmp(name, a.name, 8) == 0;
        if (eq) {
            // Found it!
            if (a.type == TYPE_CHRRAM) {
                // Copy the bytes over to CHRRAM
                memcpy(&CHRROM_writable(a.org), a.data, a.size);
                load_pattern_tables();
            } else if (a.type == TYPE_PRGRAM) {
                // Copy the bytes over to RAM
                memcpy(&RAM(a.org), a.data, a.size);
            }
            return true;
        }
    }
    return false;
}

int init_smb2j_rom(const char* filename) {
    byte* rom_org = &RAM(0x8000);
    byte* chrrom_org = &CHRROM_writable(0x0000);

    FILE* f = fopen(filename, "rb");
    if (f) {
        for (int i = 0; i < FDS_FILES_COUNT; i++) {
            // We're not bothering to free it, it lasts as long as the game itself
            FdsFile &a = FDS_FILES[i];
            a.data = malloc(a.size);
            fseek(f, a.file_offset, SEEK_SET);
            fread(a.data, 1, a.size, f);
        }
        fclose(f);

        // Load these automatically
        load_file_from_provider("SM2CHAR1");
        load_file_from_provider("SM2MAIN ");
        load_file_from_provider("SM2SAVE ");

        printf("ROM loaded\n");
        return 1;
    } else {
        printf("Could not open ROM\n");
        return 0;
    }
}

#include "movie.h"


#include <thread>
#include <chrono>

template <typename F>
void run_at_60fps(F callback) {
    while (true) {
        auto last_time = std::chrono::high_resolution_clock::now();
        bool result = callback();
        if (result) {
            break;
        }
        auto next_time = last_time + std::chrono::duration<double, std::ratio<1, 60>>(1);
        std::this_thread::sleep_for(next_time - std::chrono::high_resolution_clock::now());
    }
}

const char *ppuram_filename = "ppuram.bin";
const char *ram_filename = "ram.bin";

int framecounter = 0;

int main(int argc, char* argv[]) {
    if (!load_palette()) {
        return 1;
    }
#ifdef SMB1_MODE
    const char* filename = argc > 1 ? argv[1] : "smb.nes";
    if (!init_rom(filename)) {
        return 1;
    }
#elif SMB2J_MODE
    const char* filename = argc > 1 ? argv[1] : "smb2j.fds";
    if (!init_smb2j_rom(filename)) {
        return 1;
    }
#endif

    const int video_scale = 3;

    SDL_Window* window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
        "smb-port",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        256*video_scale, 240*video_scale,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }
    SDL_FillRect(SDL_GetWindowSurface(window), NULL, SDL_MapRGB(SDL_GetWindowSurface(window)->format, 0x00, 0x00, 0x00));
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    SDL_Surface *surf = SDL_CreateRGBSurface(0, 256*2, 240, 32, 0, 0, 0, 0);
    const int stride = 256 * 2;

    // SMB: reset vector
    Reset();

#ifdef USE_MOVIE
    auto movie = Movie(USE_MOVIE "-buttons.txt", USE_MOVIE "-ram.bin");

    auto advance_movie = [&movie]() {
        auto movie_buttons = movie.next();
        bool use_movie_buttons = movie_buttons.has_value();
        if (use_movie_buttons) {
#ifdef USE_MOVIE_COMPARERAM
            byte rambuf[0x800];
            if (movie.get_ram(rambuf, 0)) {
                byte* compareto = &RAM(0x0000);

                // RAM errors start at frame 16600, when we go underwater

                auto mem_eq_range = [&rambuf, &compareto](size_t from, size_t upto) {
                    const byte* a = rambuf;
                    const byte* b = compareto;
                    size_t len = upto + 1 - from;
                    for (size_t i = from; i <= upto; i++) {
                        if (a[i] != b[i]) {
                            printf("Frame %05d: RAM not equal: At %04X: %02X expected vs %02X actual\n", framecounter, i, a[i], b[i]);
                            //return;
                        }
                    }
                };

                // Missing ranges:
                // $F0-$FF and $7B0-$7CA are sound related. we haven't implemented sound subroutines yet.
                // $160-$1FF is the stack (this port doesn't use this)

#ifdef SMB1_MODE
                mem_eq_range(0x0008, 0x00EF);
                mem_eq_range(0x0100, 0x015F);
#elif SMB2J_MODE
                // FDS may modify $00-$0F and $F5-$FF with BIOS subroutines, so they're unreliable
                mem_eq_range(0x0010, 0x00EF);
                mem_eq_range(0x0109, 0x015F);
#endif
                mem_eq_range(0x0200, 0x07AF);
                mem_eq_range(0x07CB, 0x07FF);
            } else {
                printf("Could not read ramseq\n");
            }
#endif

            const auto& in = *movie_buttons;
            PLAYER1_INPUTS.u = in.u;
            PLAYER1_INPUTS.d = in.d;
            PLAYER1_INPUTS.l = in.l;
            PLAYER1_INPUTS.r = in.r;
            PLAYER1_INPUTS.b = in.b;
            PLAYER1_INPUTS.a = in.a;
            PLAYER1_INPUTS.select = in.select;
            PLAYER1_INPUTS.start = in.start;
        }
        return use_movie_buttons;
    };

    int skipto = USE_MOVIE_SKIPAHEAD;

    if (skipto > 0) {
        bool movie_is_valid = true;

        for (int i = 0; i < skipto; i++) {
            if (advance_movie()) {
                NMI();
                framecounter += 1;
            } else {
                movie_is_valid = false;
                break;
            }
        }

#ifdef USE_MOVIE_LOAD_RAM_AFTER_SKIPAHEAD
        if (movie_is_valid) {
            movie.get_ram(&RAM(0x0000), 1);
        }
#endif
    }
#endif

#ifdef USE_MOVIE
    run_at_60fps([&advance_movie, window, surf]() {
#else
    run_at_60fps([window, surf]() {
#endif
        bool use_movie_buttons = false;
        
#ifdef USE_MOVIE
        use_movie_buttons = advance_movie();
#endif

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
                        if (load_ppuram(ppuram_filename)) {
                            if (!load_ram(ram_filename)) {
                                // Couldn't load RAM - exit
                                return true;
                            }
                        }
                        break;
                    case SDL_SCANCODE_0:
                        // dump the RAM and PPU
                        dump_ppuram(ppuram_filename);
                        dump_ram(ram_filename);
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
                return true;
            }
        }

        // SMB: NMI vector
        // runs each frame
        NMI();
        framecounter += 1;

        // Fill with background color
        const Pixel &bgcolor = PPU_STATE.palette[PPU_STATE.buffer[0x3f00]];
        SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, bgcolor.r, bgcolor.g, bgcolor.b));

        SDL_LockSurface(surf);
        Pixel* pixels = (Pixel*)surf->pixels;

        for (int spriteidx = 0; spriteidx < 64; spriteidx++) {
            Sprite& s = ACTIVE_SPRITES[63-spriteidx];
            if (s.draw_behind) {
                draw_tile(pixels, stride, s.tileidx, s.palette + 4, s.flip_horz, s.flip_vert, s.x, s.y);
            }
        }

        // Status bar
        draw_nametable_rect(pixels, stride, 0, 0, 0x2000, 0, 0, 32, 4);

        int scroll_off = -((int)SCROLL_WITHIN_NT);

        if (SCROLL_NT == 0) {
            draw_nametable_rect(pixels, stride, scroll_off,     32, 0x2000, 0, 4, 32, 30);
            draw_nametable_rect(pixels, stride, 256+scroll_off, 32, 0x2400, 0, 4, 32, 30);
        } else {
            draw_nametable_rect(pixels, stride, scroll_off,     32, 0x2400, 0, 4, 32, 30);
            draw_nametable_rect(pixels, stride, 256+scroll_off, 32, 0x2000, 0, 4, 32, 30);
        }

        for (int spriteidx = 0; spriteidx < 64; spriteidx++) {
            Sprite& s = ACTIVE_SPRITES[63-spriteidx];
            if (!s.draw_behind) {
                draw_tile(pixels, stride, s.tileidx, s.palette+4, s.flip_horz, s.flip_vert, s.x, s.y);
            }
        }

        SDL_UnlockSurface(surf);

        const SDL_Rect srcrect = { 0, 0, 256, 240 };
        SDL_Rect dstrect = { 0, 0, 256*video_scale, 240*video_scale };
        SDL_BlitScaled(surf, &srcrect, SDL_GetWindowSurface(window), &dstrect);
        SDL_UpdateWindowSurface(window);

        return false;
    });

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
