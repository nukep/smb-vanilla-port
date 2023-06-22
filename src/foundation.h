#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mario.h"

typedef unsigned char byte;
typedef unsigned short ushort;
// #define warning printf
#define warning(...)

#define assert_smb_crashbug(condition, message) assert(condition)

#ifdef _MSC_VER
#define NOINLINE __declspec(noinline)
#define thread_local __declspec(thread)
#elif __GNUC__
#define NOINLINE __attribute__((noinline))
#endif

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
  byte start_on_world;
  byte start_on_level;

  struct SMB_callbacks callbacks;
  size_t smb2j_disk_offset;
  ppu_state ppu;
  unsigned short scroll_x;
  struct sprite sprites[64];
};

extern thread_local struct SMB_state *SMB_STATE;

#define RAM(offset) (SMB_STATE->rammem[offset])
#define PPURAM(offset) (SMB_STATE->ppuram[offset])
#define CHRROM(offset) (SMB_STATE->chrrom[offset])

#define SMB1_ONLY (SMB_STATE->which_game == GAME_SMB1)
#define SMB2J_ONLY (SMB_STATE->which_game == GAME_SMB2J)

#define PPU_STATE (SMB_STATE->ppu)
#include "ppu.h"
#undef PPU_STATE

static inline bool seek_rom(struct SMB_state *state, size_t offset) {
  return state->callbacks.seek_rom(state->callbacks.userdata, offset);
}
static inline bool read_rom_bytes(struct SMB_state *state, byte *buf, size_t size) {
  return state->callbacks.read_rom_bytes(state->callbacks.userdata, buf, size);
}

// Write to $4016
static void joystick_strobe(byte x) {
}

static inline void apu_write_register(struct SMB_state *state, ushort addr, byte data) {
  if (state->callbacks.apu_write_register) {
    state->callbacks.apu_write_register(state->callbacks.userdata, addr, data);
  }
}
static inline void apu_end_frame(struct SMB_state *state) {
  if (state->callbacks.apu_end_frame) {
    state->callbacks.apu_end_frame(state->callbacks.userdata);
  }
}

#define APU_REG(name, addr) \
  static inline void name(byte x) { apu_write_register(SMB_STATE, addr, x); }

APU_REG(apu_sq1_vol, 0x4000)
APU_REG(apu_sq1_sweep, 0x4001)
APU_REG(apu_sq1_lo, 0x4002)
APU_REG(apu_sq1_hi, 0x4003)
APU_REG(apu_sq2_vol, 0x4004)
APU_REG(apu_sq2_sweep, 0x4005)
APU_REG(apu_sq2_lo, 0x4006)
APU_REG(apu_sq2_hi, 0x4007)
APU_REG(apu_tri_linear, 0x4008)
APU_REG(apu_tri_lo, 0x400a)
APU_REG(apu_tri_hi, 0x400b)
APU_REG(apu_noise_vol, 0x400c)
APU_REG(apu_noise_lo, 0x400e)
APU_REG(apu_noise_hi, 0x400f)
APU_REG(apu_dmc_freq, 0x4010)
APU_REG(apu_dmc_raw, 0x4011)
APU_REG(apu_dmc_start, 0x4012)
APU_REG(apu_dmc_len, 0x4013)
APU_REG(apu_snd_chn, 0x4015)
APU_REG(apu_framecounter_ctrl, 0x4017)

#undef APU_REG

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

    s[i].tile.extra_type = TILE_TYPE_SPRITE;
    s[i].tile.extra_spriteidx = i;

    s[i].draw_behind = (attr & 0x20) != 0;
  }
}

static void jmpengine_overflow(byte index) {
  warning("JMPENGINE overflow! %02X\n", index);
}

void draw_graphics(struct SMB_state *state);

// Implementation of Ghidra decompiler functions.

#define BITMASK_HELPER(bytes) ((1ULL << (8 * (bytes))) - 1)
// "Concatenate"
// CONCAT42(a,b) means: input is 4 bytes + 2 bytes, output is 6 bytes total.
// Their order is the same as written order (we write numbers in big endian).
// e.g. CONCAT42(0xaabbccdd,0x0123) = 0xaabbccdd0123
#define CONCATimpl(x, y)                                                   \
  static inline uint64_t CONCAT##x##y(uint64_t a, uint64_t b) {            \
    return (a & BITMASK_HELPER(x)) << (8 * (y)) | (b & BITMASK_HELPER(y)); \
  }
// "Subpiece"
// SUB42(a,b) means: input is 4 bytes, output is 2 bytes.
// a is the input, b is the number of lower bytes being truncated.
// e.g. SUB42(0xaabbccdd,1) = 0xbbcc
#define SUBimpl(x, y)                                                \
  static inline uint64_t SUB##x##y(uint64_t a, uint64_t b) {         \
    return ((a & BITMASK_HELPER(x)) >> (8 * b)) & BITMASK_HELPER(y); \
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

#define SUBPIECE(var, a, b) ((CAST_TO_INT(var) >> (a * 8)) & BITMASK_HELPER(b))

CONCATimpl(1, 1);
CONCATimpl(1, 2);
CONCATimpl(2, 2);
CONCATimpl(2, 3);
CONCATimpl(3, 3);
CONCATimpl(3, 4);
SUBimpl(4, 2);
SUBimpl(3, 2);
SUBimpl(6, 2);

static inline bool CARRY1(byte a, byte b) {
  ushort r = (ushort)a + (ushort)b;
  return r >= 256;
}

// Negate the byte, assuming the value is signed two's complement.
// e.g. 255 => -1  => 1
//      240 => -16 => 16
static inline byte NEGATE(byte x) {
  return (x ^ 0xFF) + 1;
}

typedef uint64_t int3;
typedef uint64_t uint3;
typedef uint64_t uint6;
typedef uint64_t uint7;
typedef uint64_t undefined3;

// Represents a pointer type. Size is 2 bytes.
class RamPtr {
public:
  // fields, as laid out in 6502 memory
  union {
    byte lo;
    byte _0_1_; // ghidra labels it this
  };
  union {
    byte hi;
    byte _1_1_; // ghidra labels it this
  };

  RamPtr(ushort addr) : lo(addr & 0xFF), hi(addr >> 8) {}
  byte &operator*() {
    return RAM((hi << 8) | lo);
  }
  byte &operator[](int i) {
    // equivalent to LDA (ptr),Y
    return RAM(((hi << 8) | lo) + i);
  }
};

static RamPtr &RAMPtr(ushort offset) {
  RamPtr *ptr = (RamPtr *)(&RAM(offset));
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
  byte &operator*() const {
    return RAM(addr);
  }
  byte *operator&() const {
    return &RAM(addr);
  }
  byte &operator[](int i) const {
    // equivalent to LDA addr,X
    ushort eff = addr + i;
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
  const byte &operator*() const {
    return RAM(addr);
  }
  const byte *operator&() const {
    return &RAM(addr);
  }
  const byte &operator[](int i) const {
    // equivalent to LDA addr,X
    ushort eff = addr + i;
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

#define RAMPTR RAMPtr
#define RAMARRAY RamByteArray
#define RAMARRAY_CONST ConstRamByteArray

void update_prng(byte *prng);