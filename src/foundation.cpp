// The start of something magical! ✨

#include <cstdio>
#include <cstring>
#include <cstdint>
#include <utility>

#include "mario.h"

typedef unsigned char byte;
typedef unsigned short ushort;
//#define warning printf
#define warning(...)

#ifdef _MSC_VER
#define NOINLINE __declspec(noinline)
#define thread_local __declspec(thread)
#else
#define NOINLINE __attribute__ ((noinline))
#define thread_local _Thread_local
#endif

void SMB1_Reset();
void SMB1_NMI();
void SMB2J_Reset();
void SMB2J_NMI();

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

struct ppu_state {
    // internal regs
    ppureg v;
    ppureg t;
    byte x;
    byte w;
    byte increment_mode;
    bool screen_on;
};

#define GAME_SMB1 0
#define GAME_SMB2J 1

struct sprite {
    struct SMB_tile tile;
    bool draw_behind;
};

struct SMB_state {
    byte rammem[0x10000];
    byte chrrom[0x2000];
    byte ppuram[0x4000];
    int which_game;
    bool reset_occurred;

    struct SMB_callbacks callbacks;
    size_t smb2j_disk_offset;
    ppu_state ppu;
    unsigned short scroll_x;
    struct sprite sprites[64];
};

thread_local static struct SMB_state *SMB_STATE;

#define RAM(offset) (SMB_STATE->rammem[offset])
#define PPURAM(offset) (SMB_STATE->ppuram[offset])
#define CHRROM(offset) (SMB_STATE->chrrom[offset])

// Write to $4016
void joystick_strobe(byte x) {
}
// Write to $4011
void apu_dmc_raw(byte x) {
}
// Write to $4015
void apu_snd_chn(byte x) {
}

static void joy1(struct SMB_buttons *buttons) {
    if (SMB_STATE->callbacks.joy1) {
        return SMB_STATE->callbacks.joy1(SMB_STATE->callbacks.userdata, buttons);
    }
}
static void joy2(struct SMB_buttons *buttons) {
    if (SMB_STATE->callbacks.joy2) {
        return SMB_STATE->callbacks.joy2(SMB_STATE->callbacks.userdata, buttons);
    }
}
static void announce_main_scroll(unsigned short scroll_x) {
    SMB_STATE->scroll_x = scroll_x;
}
static void transfer_sprite_data(const byte *data) {
    struct sprite *s = SMB_STATE->sprites;
    for (int i = 0; i < 64; i++) {
        s[i].tile.y = data[i * 4 + 0] + 1;
        s[i].tile.tileidx = data[i * 4 + 1];
        byte attr = data[i * 4 + 2];
        s[i].tile.x = data[i * 4 + 3];

        s[i].tile.paletteidx = (attr & 0x03) + 4;
        s[i].tile.flip_horz = (attr & 0x40) != 0;
        s[i].tile.flip_vert = (attr & 0x80) != 0;

        s[i].draw_behind = (attr & 0x20) != 0;
    }
}

static bool seek_rom(struct SMB_state *state, size_t offset) {
    return state->callbacks.seek_rom(state->callbacks.userdata, offset);
}
static bool read_rom_bytes(struct SMB_state *state, byte* buf, size_t size) {
    return state->callbacks.read_rom_bytes(state->callbacks.userdata, buf, size);
}

static bool load_smb1(struct SMB_state *state, size_t prg_offset, size_t chr_offset) {
    if (!seek_rom(state, prg_offset)) { return false; }
    if (!read_rom_bytes(state, state->rammem+0x8000, 0x8000)) { return false; }
    if (!seek_rom(state, chr_offset)) { return false; }
    if (!read_rom_bytes(state, state->chrrom, 0x2000)) { return false; }
    state->which_game = GAME_SMB1;
    state->callbacks.update_pattern_tables(state->callbacks.userdata, state->chrrom);
    return true;
}


struct FdsFile {
    const char *name;
    size_t file_offset;
    ushort size;
    ushort org;
    int type;
};

#define TYPE_PRGRAM 0
#define TYPE_CHRRAM 1


#define SMB2J_FDS_FILES_COUNT 6

// hard-code some offsets for now
// assuming file has a 16-byte header (starts with 46 44 53, i.e. "FDS")
static FdsFile SMB2J_FDS_FILES[SMB2J_FDS_FILES_COUNT] = {
    {"SM2CHAR1", 0x013C, 0x2000, 0x0000, TYPE_CHRRAM},
    {"SM2CHAR2", 0x214D, 0x0040, 0x0760, TYPE_CHRRAM},
    {"SM2MAIN ", 0x219E, 0x8000, 0x6000, TYPE_PRGRAM},
    {"SM2DATA2", 0xA1AF, 0x0E2F, 0xC470, TYPE_PRGRAM},
    {"SM2DATA3", 0xAFEF, 0x0CCF, 0xC5D0, TYPE_PRGRAM},
    {"SM2DATA4", 0xBCCF, 0x0F4C, 0xC2B4, TYPE_PRGRAM},
};

bool smb2j_load_file(struct SMB_state *state, const char *name) {
    if (strncmp(name, "SM2SAVE ", 8) == 0) {
        // treat the save byte specially

        if (state->callbacks.smb2j_load_games_beaten) {
            state->rammem[0xD29F] = state->callbacks.smb2j_load_games_beaten(state->callbacks.userdata);
        } else {
            state->rammem[0xD29F] = 0;
        }

        return true;
    }

    for (int i = 0; i < SMB2J_FDS_FILES_COUNT; i++) {
        const FdsFile& a = SMB2J_FDS_FILES[i];
        bool eq = strncmp(name, a.name, 8) == 0;
        if (eq) {
            // Found it!
            byte *copy_to;
            if (a.type == TYPE_CHRRAM) {
                // Copy the bytes over to CHRRAM
                copy_to = state->chrrom + a.org;
            } else if (a.type == TYPE_PRGRAM) {
                // Copy the bytes over to RAM
                copy_to = state->rammem + a.org;
            }
            if (!seek_rom(state, state->smb2j_disk_offset + a.file_offset)) { return false; }
            if (!read_rom_bytes(state, copy_to, a.size)) { return false; }

            if (a.type == TYPE_CHRRAM) {
                state->callbacks.update_pattern_tables(state->callbacks.userdata, state->chrrom);
            }

            return true;
        }
    }
    return false;
}
bool smb2j_save_games_beaten(struct SMB_state *state, byte games_beaten) {
    if (state->callbacks.smb2j_save_games_beaten) {
        return state->callbacks.smb2j_save_games_beaten(state->callbacks.userdata, games_beaten);
    } else {
        return false;
    }
}

static bool load_smb2j(struct SMB_state *state, size_t disk_offset) {
    // In this case, the 16 bit header is this:
    static char fds_disk_verification[16] = {0x01, '*','N','I','N','T','E','N','D','O','-','H','V','C','*', 0x01};
    byte headerbuf[16];
    if (!seek_rom(state, disk_offset)) { return false; }
    if (!read_rom_bytes(state, headerbuf, 16)) { return false; }

    bool match = memcmp(headerbuf, fds_disk_verification, 16) == 0;
    if (!match) { return false; }
    state->which_game = GAME_SMB2J;
    state->smb2j_disk_offset = disk_offset;

    // Load these automatically
    smb2j_load_file(state, "SM2CHAR1");
    smb2j_load_file(state, "SM2MAIN ");
    smb2j_load_file(state, "SM2SAVE ");
    return true;
}

static bool detect_and_load_rom(struct SMB_state *state) {
    byte headerbuf[16];
    if (!read_rom_bytes(state, headerbuf, 16)) {
        return false;
    }
    if (headerbuf[0] == 'N' && headerbuf[1] == 'E' && headerbuf[2] == 'S' && headerbuf[3] == 0x1A) {
        // An INES header. Probably SMB1.
        return load_smb1(state, 0x10, 0x8010);
    } else if (headerbuf[0] == 'F' && headerbuf[1] == 'D' && headerbuf[2] == 'S' && headerbuf[3] == 0x1A) {
        // An FDS header. Probably SMB2J.
        // TODO: there's an FDS version of SMB1. Maybe handle it?
        return load_smb2j(state, 0x10);
    } else {
        // There are some ROMs that don't include an FDS header, but just the single disk image.
        return load_smb2j(state, 0);
    }
}

struct SMB_state *SMB_get_state() {
    return SMB_STATE;
}
size_t SMB_state_size() {
    return sizeof(struct SMB_state);
}
void SMB_state_init(struct SMB_state *state, const struct SMB_callbacks *cb) {
    memset(state, 0, sizeof(struct SMB_state));
    state->callbacks = *cb;
    detect_and_load_rom(state);
}

byte* SMB_ram(struct SMB_state *state) {
    return state->rammem;
}
byte* SMB_ppuram(struct SMB_state *state) {
    return state->ppuram;
}


void SMB_tick(struct SMB_state *state) {
    // Set a global variable while it's being ticked
    SMB_STATE = state;
#ifdef SMB1_MODE
    if (state->which_game == GAME_SMB1) {
        if (!state->reset_occurred) {
            SMB1_Reset();
            state->reset_occurred = true;
        }
        SMB1_NMI();
    }
#endif
#ifdef SMB2J_MODE
    if (state->which_game == GAME_SMB2J) {
        if (!state->reset_occurred) {
            SMB2J_Reset();
            state->reset_occurred = true;
        }
        SMB2J_NMI();
    }
#endif
}


#define PPU_STATE (SMB_STATE->ppu)
#include "ppu.h"
#undef PPU_STATE

static inline void draw_nametable_tile(const struct SMB_state *state, int x, int y, ushort ppu_offset, int tilex, int tiley) {
    int j = tilex;
    int i = tiley;
    int off = i * 32 + j;
    int tileidx = state->ppuram[ppu_offset + off] + 0x100;
    // Find which part of the pallete to use
    // Look it up in the attribute table

    byte a = state->ppuram[ppu_offset + 0x03c0 + (i / 4) * 8 + (j / 4)];
    a >>= ((j / 2) % 2) * 2;
    a >>= ((i / 2) % 2) * 4;
    a &= 0x03;
    int paletteidx = a;

    struct SMB_tile tile;
    tile.x = x;
    tile.y = y;
    tile.tileidx = tileidx;
    tile.paletteidx = paletteidx;
    tile.flip_horz = false;
    tile.flip_vert = false;

    state->callbacks.draw_tile(state->callbacks.userdata, tile);
}

static inline void draw_nametable_rect(const struct SMB_state *state, int x, int y, ushort ppu_offset, int fromx, int fromy, int tox, int toy) {
    for (int i = fromy; i < toy; i++) {
        for (int j = fromx; j < tox; j++) {
            draw_nametable_tile(state, x + (j - fromx) * 8, y + (i-fromy) * 8, ppu_offset, j, i);
        }
    }
}

void draw_graphics(struct SMB_state* state) {
    if (state->callbacks.update_palette) {
        // The palette can change even if the screen is off (the background color, namely)
        state->callbacks.update_palette(state->callbacks.userdata, state->ppuram + 0x3F00);
    }

    if (!state->ppu.screen_on) {
        return;
    }
    if (!state->callbacks.draw_tile) {
        return;
    }

    for (int spriteidx = 0; spriteidx < 64; spriteidx++) {
        const struct sprite *s = state->sprites + (63 - spriteidx);
        if (s->draw_behind) {
            state->callbacks.draw_tile(state->callbacks.userdata, s->tile);
        }
    }

    // Status bar
    draw_nametable_rect(state, 0, 0, 0x2000, 0, 0, 32, 4);

    int scroll_off = -(state->scroll_x % 256);
    int scroll_nametable = state->scroll_x / 256;

    if (scroll_nametable == 0) {
        draw_nametable_rect(state, scroll_off, 32, 0x2000, 0, 4, 32, 30);
        draw_nametable_rect(state, 256 + scroll_off, 32, 0x2400, 0, 4, 32, 30);
    } else {
        draw_nametable_rect(state, scroll_off, 32, 0x2400, 0, 4, 32, 30);
        draw_nametable_rect(state, 256 + scroll_off, 32, 0x2000, 0, 4, 32, 30);
    }

    for (int spriteidx = 0; spriteidx < 64; spriteidx++) {
        const struct sprite *s = state->sprites + (63 - spriteidx);
        if (!s->draw_behind) {
            state->callbacks.draw_tile(state->callbacks.userdata, s->tile);
        }
    }
}














// Implementation of Ghidra decompiler functions.

#define BITMASK_HELPER(bytes) ((1ULL<<(8*(bytes)))-1)
// "Concatenate"
// CONCAT42(a,b) means: input is 4 bytes + 2 bytes, output is 6 bytes total.
// Their order is the same as written order (we write numbers in big endian).
// e.g. CONCAT42(0xaabbccdd,0x0123) = 0xaabbccdd0123
#define CONCATimpl(x,y) static inline uint64_t CONCAT##x##y(uint64_t a, uint64_t b) { \
    return (a & BITMASK_HELPER(x))<<(8*(y)) | (b & BITMASK_HELPER(y)); \
}
// "Subpiece"
// SUB42(a,b) means: input is 4 bytes, output is 2 bytes.
// a is the input, b is the number of lower bytes being truncated.
// e.g. SUB42(0xaabbccdd,1) = 0xbbcc
#define SUBimpl(x,y) static inline uint64_t SUB##x##y(uint64_t a, uint64_t b) { \
    return ((a & BITMASK_HELPER(x)) >> (8*b)) & BITMASK_HELPER(y); \
}

static inline uint64_t CAST_TO_INT_helper(void *var, size_t sz) {
    uint64_t v = 0;
    if (sz > sizeof(v)) {
        printf("Nope\n");
        return 0;
    }
    memcpy(&v, var, sz);
    return v;
}

#define CAST_TO_INT(var) CAST_TO_INT_helper(&(var), sizeof(var))

#define SUBPIECE(var,a,b) ((CAST_TO_INT(var)>>(a*8)) & BITMASK_HELPER(b))

CONCATimpl(1,1)
CONCATimpl(1,2)
CONCATimpl(2,2)
CONCATimpl(2,3)
CONCATimpl(3,3)
CONCATimpl(3,4)
SUBimpl(4,2)
SUBimpl(3,2)
SUBimpl(6,2)

static inline bool CARRY1(byte a, byte b) {
    ushort r = (ushort)a + (ushort)b;
    return r >= 256;
}


// Represents a pointer type. Size is 2 bytes.
class RamPtr {
public:
    // fields, as laid out in 6502 memory
    union {
        byte lo;
        byte _0_1_;      // ghidra labels it this
    };
    union {
        byte hi;
        byte _1_1_;      // ghidra labels it this
    };

    RamPtr(ushort addr) : lo(addr&0xFF), hi(addr>>8) {}
    byte& operator*() {
        return RAM((hi<<8) | lo);
    }
    byte& operator[](int i) {
        // equivalent to LDA (ptr),Y
        return RAM(((hi<<8) | lo) + i);
    }
};

RamPtr& RAMPtr(ushort offset) {
    RamPtr *ptr = (RamPtr*)(&RAM(offset));
    return *ptr;
}

// Represents a byte array at a specific address.
class RamByteArray {
private:
    ushort addr;
    ushort length;
public:
    RamByteArray(ushort addr) : addr(addr), length(0) {}
    RamByteArray(ushort addr, ushort length) : addr(addr), length(length) {}
    byte& operator*() const {
        return RAM(addr);
    }
    byte* operator&() const {
        return &RAM(addr);
    }
    byte& operator[](int i) const {
        // equivalent to LDA addr,X
        ushort eff = addr+i;
        if (addr <= 0xFF) {
            // zero-page wraparound for zero-page adddresses.
            // in SMB, all indexes of zero-page addresses work like this.
            // i.e. the imm16,x or imm16,y address modes are never used for zero-page
            eff = eff & 0xFF;
        }
        if (length != 0) {
            if (i < 0 || i >= length) {
                warning("Out of bounds for array %04X[%d] at index %d (= %04X)\n", addr, length, i, eff);
            }
        }
        return RAM(addr + i);
    }
};

// Represents a byte array at a specific address.
// Read-only, can't write to these
class ConstRamByteArray {
private:
    ushort addr;
    ushort length;
public:
    ConstRamByteArray(ushort addr) : addr(addr), length(0) {}
    ConstRamByteArray(ushort addr, ushort length) : addr(addr), length(length) {}
    const byte& operator*() const {
        return RAM(addr);
    }
    const byte* operator&() const {
        return &RAM(addr);
    }
    const byte& operator[](int i) const {
        // equivalent to LDA addr,X
        ushort eff = addr+i;
        if (addr <= 0xFF) {
            // zero-page wraparound for zero-page adddresses.
            // in SMB, all indexes of zero-page addresses work like this.
            // i.e. the imm16,x or imm16,y address modes are never used for zero-page
            eff = eff & 0xFF;
        }
        if (length != 0) {
            if (i < 0 || i >= length) {
                warning("Out of bounds for array %04X[%d] at index %d (= %04X)\n", addr, length, i, eff);
            }
        }
        return RAM(addr + i);
    }
};

// Workaround!!!
// Used to avoid some undefined behavior in MSVC
NOINLINE static byte force_byte(byte x) {
    return x;
}


















/////////////////////////
/// implemented code! ///
/////////////////////////

#define RAMPTR RAMPtr
#define RAMARRAY RamByteArray
#define RAMARRAY_CONST ConstRamByteArray

#ifdef SMB1_MODE

#include "generated/smb_romarrays.h"
#include "generated/smb_vars.h"
static const ConstRamByteArray AreaAddrOffsets = ConstRamByteArray(0x9CBC, 0x24);
static const ConstRamByteArray GameText = ConstRamByteArray(0x8752, 0x9B);

#elif defined(SMB2J_MODE)

#include "generated/smb2j_romarrays.h"
#include "generated/smb2j_vars.h"

#endif


// Set 0's in memory.
// The provided number is up to which address in the $0700 page to set to zero.
// e.g. if i=0x14, then clear up to $0714 inclusive.
// Doesn't set the stack, between $0160 and $01FF inclusive.
// On SMB2J, doesn't set $0100 to $0108 inclusive.
// Note that this port, which doesn't target the 6502, doesn't use the stack at $0160-$1FFF at all.

#ifdef SMB1_MODE
    // SMB:90CC
    // Signature: [Y] -> [A]
    byte InitializeMemory(byte i) {
        memset(&RAM(0x000), 0, 0x160);
        memset(&RAM(0x200), 0, (size_t)0x700 - 0x200);
        memset(&RAM(0x700), 0, (byte)(i + 1));
        return 0;
    }

#elif defined(SMB2J_MODE)

    // SM2MAIN:6f08
    // Signature: [Y] -> [A]
    byte InitializeMemory(byte i) {
        memset(&RAM(0x000), 0, 0x100);
        memset(&RAM(0x109), 0, (size_t)0x160 - 0x109);
        memset(&RAM(0x200), 0, (size_t)0x700 - 0x200);
        memset(&RAM(0x700), 0, (byte)(i + 1));
        return 0;
    }
#endif

void jmpengine_overflow(byte index) {
    warning("JMPENGINE overflow! %02X\n", index);
}


typedef uint64_t int3;
typedef uint64_t uint3;
typedef uint64_t uint6;
typedef uint64_t uint7;
typedef uint64_t undefined3;


#ifdef SMB1_MODE

#include "generated/smb.h"
#include "common.h"

void DrawTitleScreen();
bool TransposePlayers();

#include "generated/smb.cpp"
#include "smb_functions.h"

#elif defined(SMB2J_MODE)

// read $4032
byte FDS_drive_status() { return 0; }

#include "generated/smb2j.h"
#include "common.h"

void ScrollScreen(byte);
struct_ayz LoadFiles();
void UpdateGamesBeaten();

#include "generated/smb2j.cpp"
#include "smb_functions.h"

#endif


// SMB1 and SMBLL's Pseudo-Random Number Generator
//
// How it works, in plain language:
// The PRNG is a 56-bit string (7 * 8 bits) that's shifted to the right each iteration.
// A new bit is fed in from the left depending on the following:
//     If two specific bits in the string are equal, then the new bit is 0. Otherwise the new bit is 1.
//     (you can also interpret this as XORing the two bits to get the new bit).
//
// The seed value is A5 00 00 00 00 00 00.
//
// Example iterations:
//       >     a       b
// 61st: 00100010101101001111000110011000011110110100101110111101  (a=1, b=0. new bit for 62 is 1)
// 62nd: 10010001010110100111100011001100001111011010010111011110  (a=0, b=1. new bit for 63 is 1)
// 63rd: 11001000101011010011110001100110000111101101001011101111  (a=0, b=0. new bit for 64 is 0)
// 64th: 01100100010101101001111000110011000011110110100101110111  (a=0, b=1. new bit for 65 is 1)
//
// For iteration 61, a=1 and b=0, which are not equal, so the new bit to be used for iteration 62 is 1.
//
// Fun fact: This PRNG has a period of 32767 iterations. The cycle starts at the 40th iteration.
// That's about 546.1 seconds or 9.1 minutes at 60fps!
// After which, it'll generate the same values on loop.
// 1st iteration (seed):       A5 00 00 00 00 00 00 (10100101000000000000000000000000000000000000000000000000)
// 40th and 32807th iteration: 33 0F 69 77 A5 4A 00 (00110011000011110110100101110111101001010100101000000000)
static void update_prng(byte *prng) {
    byte a = prng[0] & 2;
    byte b = prng[1] & 2;
    bool newbit = a != b;

    for (int i = 0; i < 7; i++) {
        bool next = (prng[i] & 1) != 0;
        prng[i] = (newbit ? 0x80 : 0x00) | (prng[i] >> 1);
        newbit = next;
    }
}

#ifdef SMB1_MODE

// SMB:8000
// Signature: [] -> []
void SMB1_Reset() {
    ppuctrl(0x10);
    // ppu_waituntilvblank();   // wait until ppustatus() & 0x80 == 1
    // ppu_waituntilvblank();   // wait until ppustatus() & 0x80 == 1

    byte initialize_upto = WarmBootValidation == 0xa5 ? 0xd6 : 0xfe;

    for (int i = 0; i < 6; i++) {
        if (DisplayDigits_Or_TopScoreDisplay[i] > 9) {
            initialize_upto = 0xfe;
            break;
        }
    }

    InitializeMemory(initialize_upto);
    OperMode = 0;
    apu_dmc_raw(0);
    WarmBootValidation = 0xa5;
    PseudoRandomBitReg[0] = 0xa5;
    apu_snd_chn(0xf);
    ppumask(6);
    MoveAllSpritesOffscreen();
    InitializeNameTables();
    DisableScreenFlag += 1;

    Mirror_PPU_CTRL_REG1 |= 0x80;
    ppuctrl(Mirror_PPU_CTRL_REG1);

    // There was an infinite do-nothing loop here for the NES.
    // At this point, the NMI would interrupt the loop each frame.
    // But as for the port, we just call the NMI ourselves.
}

// SMB:8082
// Signature: [] -> []
void SMB1_NMI() {
    Mirror_PPU_CTRL_REG1 = Mirror_PPU_CTRL_REG1 & ~0x80;
    ppuctrl(Mirror_PPU_CTRL_REG1 & ~0x81);

    if (DisableScreenFlag == 0) {
        Mirror_PPU_CTRL_REG2 |= 0x1e;
    } else {
        Mirror_PPU_CTRL_REG2 &= 0xe6;
    }
    ppumask(Mirror_PPU_CTRL_REG2 & 0xe7);

    ppustatus();
    ppuscroll(0);
    ppuscroll(0);

    // The NES wrote to OAM registers to initiate copying sprites
    // $2003 = 0
    // $4014 = 2
    transfer_sprite_data(&Sprite_Data);

    // VRAM_Buffer_AddrCtrl of 0, 5, 6, 7 are in RAM ($301, $300, $341, $341 respectively). All other ones are in ROM.
    UpdateScreen(&RAM(VRAM_AddrTable_High[VRAM_Buffer_AddrCtrl]*0x100 + VRAM_AddrTable_Low[VRAM_Buffer_AddrCtrl]));

    if (VRAM_Buffer_AddrCtrl == 6) {
        // in SMB ROM, VRAM_Buffer_Offset[1] = 0x40
        RAM(0x300 + VRAM_Buffer_Offset[1]) = 0;
        VRAM_Buffer1[VRAM_Buffer_Offset[1]] = 0;
    } else {
        // in SMB ROM, VRAM_Buffer_Offset[0] = 0x00
        RAM(0x300 + VRAM_Buffer_Offset[0]) = 0;
        VRAM_Buffer1[VRAM_Buffer_Offset[0]] = 0;
    }

    VRAM_Buffer_AddrCtrl = 0;
    ppumask(Mirror_PPU_CTRL_REG2);
    SoundEngine();
    ReadJoypads();
    PauseRoutine();
    UpdateTopScore();
    if ((GamePauseStatus & 1) == 0) {
        dectimers();
        FrameCounter += 1;
    }

    // Update PRNG (pseudo-random number generator)
    update_prng(&PseudoRandomBitReg);

    if (Sprite0HitDetectFlag != 0) {
        // In the NES version, the game waits here until a Sprite 0 hit (the bottom of the status bar).
        if ((GamePauseStatus & 1) == 0) {
            MoveSpritesOffscreen();
            SpriteShuffler();
        }
        // In the NES version, the game waits here until Sprite 0 is no longer being hit.
        // In the NES version, the game wastes 101 CPU cycles here to get the PPU off the bottom of the status bar.
    }
    ppuscroll(HorizontalScroll);
    ppuscroll(VerticalScroll);

    byte prev_mirror_ppu_ctrl = Mirror_PPU_CTRL_REG1;
    ppuctrl(Mirror_PPU_CTRL_REG1);
    if ((GamePauseStatus & 1) == 0) {
        // bug in analyzer. parameter is eventually unused, should not accept one.
        OperModeExecutionTree(0);
    }
    ppustatus();

    // Enable NMI (our port ignores this)
    ppuctrl(prev_mirror_ppu_ctrl | 0x80);

    // The scroll is known
    announce_main_scroll(SMB_STATE->ppu.t.NN * 256 + SMB_STATE->ppu.t.XXXXX * 8 + SMB_STATE->ppu.x);
    draw_graphics(SMB_STATE);
}

// SMB:86ff
// Signature: [] -> []
void DrawTitleScreen() {
    if (OperMode == 0) {
        // The drawing data for the title screen is stored in CHR ROM!
        for (int i = 0; i < 0x13A; i++) {
            RAM(0x300 + i) = CHRROM(0x1EC0 + i);
        }
        VRAM_Buffer_AddrCtrl = 5;
        ScreenRoutineTask = ScreenRoutineTask + 1;
    } else {
        OperMode_Task = OperMode_Task + 1;
    }
}

#define SWAP(a, b) do { byte tmp = a; a = b; b = tmp; } while (0)

// Switch between Mario and Luigi.
// Save and restore their states.
// 
// SMB:9282
// Signature: [] -> [C]
bool TransposePlayers() {
    // If there are two players, and the other one isn't out of lives
    if ((NumberOfPlayers != 0) && (OffScr_NumberofLives < 0x80)) {
        CurrentPlayer ^= 1;
        // We unrolled a loop here
        SWAP(NumberofLives, OffScr_NumberofLives);
        SWAP(HalfwayPage,   OffScr_HalfwayPage);
        SWAP(LevelNumber,   OffScr_LevelNumber);
        SWAP(Hidden1UpFlag, OffScr_Hidden1UpFlag);
        SWAP(CoinTally,     OffScr_CoinTally);
        SWAP(WorldNumber,   OffScr_WorldNumber);
        SWAP(AreaNumber,    OffScr_AreaNumber);
        
        return false;
    } else {
        return true;
    }
}

#elif defined(SMB2J_MODE)

void IRQHandler();

static bool RUN_IRQ = false;

void trigger_scroll_irq_if_havent_yet() {
    if (RUN_IRQ) {
        IRQHandler();
        RUN_IRQ = false;
        if (IRQAckFlag != 0) {
            printf("IRQAckFlag is non-zero after the IRQ handler. This shouldn't happen!\n");
        }
    }
}

void disable_interrupt() {}
void enable_interrupt() {}

byte FDS_AcknowledgeIrq() {
    return 0x01;
}
void FDSBIOS_Delay132(byte _) {}
void FDS_IrqTimer_Ctrl(byte _) {}

// SM2MAIN:c0f4
// Signature: [] -> [A, Y, Z]
struct_ayz LoadFiles() {
    // The FDS version calls FDS BIOS subroutines to read the files from disk, but in the port, we're just gonna load from a buffer.
    // The BIOS call is responsible for a lot of lag frames on the original hardware! Fortunately we don't deal with those here.

    byte files = 0;
    bool success = false;

    switch (FileListNumber) {
    case 0: // Worlds 1-4: SM2CHAR1, SM2MAIN, SM2SAVE
        if (!smb2j_load_file(SMB_STATE, "SM2CHAR1")) { goto end; }
        if (!smb2j_load_file(SMB_STATE, "SM2MAIN ")) { goto end; }
        if (!smb2j_load_file(SMB_STATE, "SM2SAVE ")) { goto end; }
        success = true;
        files = 3;
        break;
    case 1: // Worlds 5-8: SM2DATA2
        if (!smb2j_load_file(SMB_STATE, "SM2DATA2")) { goto end; }
        success = true;
        files = 1;
        break;
    case 2: // Ending, w9: SM2CHAR2, SM2DATA3, SM2SAVE
        if (!smb2j_load_file(SMB_STATE, "SM2CHAR2")) { goto end; }
        if (!smb2j_load_file(SMB_STATE, "SM2DATA3")) { goto end; }
        if (!smb2j_load_file(SMB_STATE, "SM2SAVE ")) { goto end; }
        success = true;
        files = 3;

        // The FDS BIOS call overwrites some zero-page variables that are used during the ending.
        // This is a supremely gross hack.
        // Omitting this hack doesn't break the game, but it'd cause different conditionals to occur regarding Mario's sprites and fail RAM regression tests.
        
        // This isn't an issue for the other file loads, because when the worlds are loaded,
        // the memory is unused and is cleared on the next frame with InitializeMemory.

        // These are values when FileListNumber = 2, during a specific run of the game (idk if this changes):
        // TODO - set these to their corresponding variables when we're more sure what's going on
        RAM(0x08) = 0x0F;
        RAM(0x09) = 0x00;
        RAM(0x0A) = 0xA0;
        RAM(0x0B) = 0xD2;
        RAM(0x0C) = 0xFF;
        RAM(0x0D) = 0xFF;
        RAM(0x0E) = 0x03;
        RAM(0x0F) = 0x01;
        RAM(0xF9) = 0xF7;
        RAM(0xFA) = 0x27;
        break;
    case 3: // Worlds A-D: SM2DATA4
        smb2j_load_file(SMB_STATE, "SM2DATA4");
        success = true;
        files = 1;
        break;
    default:
        break;
    }

end:
    // this runs long enough for the scroll code of the irq to trigger
    trigger_scroll_irq_if_havent_yet();

    // A is the error code, should there be an error
    // Y is how many files were read
    // Z is set to 1 if the load is successful
    struct_ayz res;
    res.a = 0;
    res.y = files;
    res.z = success;
    return res;
}

void FDS_Ctrl(byte ctrl) {
    // $4025
}


// SM2MAIN:6000
// Signature: [] -> []
void SMB2J_Reset() {
    FDS_Ctrl(RAM(0xfa) & ~0x08);

    // On a hard reset, the World number is a value such as 0xFF
    // assuming a hard reset:
    WorldNumber = 0xFF;

    byte last_worldnumber = WorldNumber;

    byte initialize_upto = WarmBootValidation == 0xa5 ? 0xd6 : 0xfe;

    for (int i = 0; i < 6; i++) {
        if (DisplayDigits_Or_TopScoreDisplay[i] > 9) {
            initialize_upto = 0xfe;
            break;
        }
    }

    InitializeMemory(initialize_upto);
    OperMode = 0;
    apu_dmc_raw(0);
    WorldNumber = last_worldnumber;
    WarmBootValidation = 0xa5;
    PseudoRandomBitReg[0] = 0xa5;
    apu_snd_chn(0xf);
    ppumask(6);
    DiskIOTask = 0;
    MoveAllSpritesOffscreen();
    InitializeNameTables();
    DisableScreenFlag += 1;

    FDSBIOS_IRQFlag = 0xc0;
    enable_interrupt();

    Mirror_PPU_CTRL_REG1 |= 0x80;
    ppuctrl(Mirror_PPU_CTRL_REG1);

    // There was an infinite do-nothing loop here for the FDS.
    // At this point, the NMI would interrupt the loop each frame.
    // But as for the port, we just call the NMI ourselves.
}

// SM2MAIN:60a0
// Signature: [] -> []
void SMB2J_NMI() {
    Mirror_PPU_CTRL_REG1 = Mirror_PPU_CTRL_REG1 & ~0x81;
    ppuctrl(Mirror_PPU_CTRL_REG1);

    disable_interrupt();

    RUN_IRQ = false;

    if (IRQUpdateFlag != 0) {
        // Set IRQ timer to 0x1658 (until the scanline reaches the bottom of the status bar)
        // $4020 = 0x58
        // $4021 = 0x16
        // Enable IRQ timer
        // $4022 = 0x02
        IRQAckFlag += 1;
        RUN_IRQ = true;
    }

    if (DisableScreenFlag == 0) {
        Mirror_PPU_CTRL_REG2 |= 0x1e;
    } else {
        Mirror_PPU_CTRL_REG2 &= 0xe6;
    }
    ppumask(Mirror_PPU_CTRL_REG2 & 0xe7);
    
    ppustatus();
    ppuscroll(0);
    ppuscroll(0);

    // The NES wrote to OAM registers to initiate copying sprites
    // $2003 = 0
    // $4014 = 2
    transfer_sprite_data(&Sprite_Data);

    // Unlike SMB1, SMB2J's address table is 16-bit words, not segmented in hi and lo portions
    // Also unlike SMB1, index 5 (the title screen) is from the ROM.
    // VRAM_Buffer_AddrCtrl of 0, 6, 7 are in RAM ($301, $341, $341 respectively). All other ones are in ROM.
    UpdateScreen(&RAM(VRAM_AddrTable[VRAM_Buffer_AddrCtrl*2 + 1]*0x100 + VRAM_AddrTable[VRAM_Buffer_AddrCtrl*2]));

    if (VRAM_Buffer_AddrCtrl == 6) {
        // in SMB ROM, VRAM_Buffer_Offset[1] = 0x40
        RAM(0x300 + VRAM_Buffer_Offset[1]) = 0;
        VRAM_Buffer1[VRAM_Buffer_Offset[1]] = 0;
    } else {
        // in SMB ROM, VRAM_Buffer_Offset[0] = 0x00
        RAM(0x300 + VRAM_Buffer_Offset[0]) = 0;
        VRAM_Buffer1[VRAM_Buffer_Offset[0]] = 0;
    }

    VRAM_Buffer_AddrCtrl = 0;
    ppumask(Mirror_PPU_CTRL_REG2);
    enable_interrupt();
    SoundEngine();
    ReadJoypads();
    PauseRoutine();
    UpdateTopScore();
    if ((GamePauseStatus & 1) == 0) {
        dectimers();
        FrameCounter += 1;
    }

    // Update PRNG (pseudo-random number generator)
    update_prng(&PseudoRandomBitReg);

    if ((GamePauseStatus & 1) == 0) {
        if (IRQUpdateFlag != 0) {
            MoveSpritesOffscreen();
            SpriteShuffler();
        }
        if (WorldNumber > 8) {
            TerminateGame();
        }
        // bug in analyzer. parameter is eventually unused, should not accept one.
        OperModeExecutionTree(0);
    }

    // The FDS version loops here until IRQAckFlag is 0.
    trigger_scroll_irq_if_havent_yet();

    // The scroll is known
    announce_main_scroll(SMB_STATE->ppu.t.NN * 256 + SMB_STATE->ppu.t.XXXXX * 8 + SMB_STATE->ppu.x);
    draw_graphics(SMB_STATE);

    ppustatus();

    // Enable NMI (our port ignores this)
    Mirror_PPU_CTRL_REG1 |= 0x80;
    ppuctrl(Mirror_PPU_CTRL_REG1);
}

// SM2MAIN:61a2
// Signature: [] -> []
void IRQHandler() {
    disable_interrupt();
    byte status = FDS_AcknowledgeIrq();

    if ((status & 0x02) == 0) {
        if ((status & 0x01) != 0) {
            // Scrolling the screen right below the status bar
            // first 2 bits are 01: not transferring bytes, and an irq occurred

            Mirror_PPU_CTRL_REG1 = (Mirror_PPU_CTRL_REG1 & ~0x08) | NameTableSelect;
            ppuctrl(Mirror_PPU_CTRL_REG1);
            FDS_IrqTimer_Ctrl(0x00);  // disable IRQ timer for the rest of the frame
            ppuscroll(HorizontalScroll);
            ppuscroll(VerticalScroll);
            IRQAckFlag = 0;
        }
    } else {
        // FDS is transferring bytes
        FDSBIOS_Delay132(status);
    }
    enable_interrupt();
}


// SM2MAIN:7b20
// Signature: [Y] -> []
void ScrollScreen(byte scroll_amount) {
    // The FDS version loops here until IRQAckFlag is 0.
    trigger_scroll_irq_if_havent_yet();

    int x_pos = ScreenLeft_X_Pos + scroll_amount;

    ScrollThirtyTwo = ScrollThirtyTwo + scroll_amount;
    HorizontalScroll = x_pos % 256;
    if (x_pos >= 256) {
        ScreenLeft_PageLoc += 1;
    }
    NameTableSelect = ScreenLeft_PageLoc % 2;
    ScreenLeft_X_Pos = HorizontalScroll;
    ScrollAmount = scroll_amount;
    GetScreenPosition();
    ScrollIntervalTimer = 8;
    ChkPOffscr();
}


// SM2DATA3::c759
// Signature: [] -> []
void UpdateGamesBeaten() {
    // The FDS version would use an FDS BIOS subroutine
    bool success = smb2j_save_games_beaten(SMB_STATE, GamesBeatenCount[0]);
    byte error_code = 0;

    if (!success) {
        DiskIOTask += 1;
        DiskErrorHandler(error_code);
        return;
    }

    // Revert "JSR SoundEngine" in the NMI back to the original address
    RAM(0x611e) = 0xd2;
    RAM(0x611d) = 0xa0;

    DiskIOTask = 0;
    OperMode_Task = 0;
    if ((HardWorldFlag == 0) && (CompletedWorlds == 0xff)) {
        CompletedWorlds = 0;
        NumberofLives = 0;
        FantasyW9MsgFlag = 0;
        AreaNumber = 0;
        LevelNumber = 0;
        OperMode_Task = 0;
        WorldNumber += 1;
        if (WorldNumber > 7) {
            WorldNumber = 8;
        }
        LoadAreaPointer();
        FetchNewGameTimerFlag = FetchNewGameTimerFlag + 1;
        OperMode = 1;
    } else {
        CompletedWorlds = 0;
        OperMode = 0;
        AttractModeSubs();
    }
}

#endif
