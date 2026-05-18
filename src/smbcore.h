#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mario.h"

typedef uint8_t byte;
typedef uint16_t ushort;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

// #define warning printf
#define warning(...)

#define assert_smb_crashbug(condition, message) assert(condition)
#define assert_eq_assumption(expected, actual) assert((expected) == (actual))
#define assert_eq_regressiontest(expected, actual) assert((expected) == (actual))

#ifdef _MSC_VER
#define NOINLINE __declspec(noinline)
//#define thread_local __declspec(thread)
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

// The singleton SMB_state used during the SMB_tick() invocation. This is considered internal and should not be used by callers of the library.
extern thread_local struct SMB_state *SMB_STATE;

static inline bool read_rom_bytes(struct SMB_state *state, byte *buf, size_t size) {
  return state->callbacks.read_rom_bytes(state->callbacks.userdata, buf, size);
}
static inline bool seek_rom(struct SMB_state *state, size_t offset) {
  return state->callbacks.seek_rom(state->callbacks.userdata, offset);
}
static inline byte smb2j_load_games_beaten() {
  if (SMB_STATE->callbacks.smb2j_load_games_beaten) {
    return SMB_STATE->callbacks.smb2j_load_games_beaten(SMB_STATE->callbacks.userdata);
  } else {
    return 0;
  }
}
static inline bool smb2j_save_games_beaten(byte games_beaten) {
  if (SMB_STATE->callbacks.smb2j_save_games_beaten) {
    return SMB_STATE->callbacks.smb2j_save_games_beaten(SMB_STATE->callbacks.userdata, games_beaten);
  } else {
    return false;
  }
}

static inline void update_pattern_tables(struct SMB_state *state) {
  if (state->callbacks.update_pattern_tables) {
    state->callbacks.update_pattern_tables(state->callbacks.userdata, state->chrrom);
  }
}

static inline bool can_draw_tile() {
  return SMB_STATE->callbacks.draw_tile != 0;
}

static inline void draw_tile(const struct SMB_tile tile) {
  if (SMB_STATE->callbacks.draw_tile) {
    SMB_STATE->callbacks.draw_tile(SMB_STATE->callbacks.userdata, tile);
  }
}

static inline void apu_write_register(ushort addr, byte data) {
  if (SMB_STATE->callbacks.apu_write_register) {
    SMB_STATE->callbacks.apu_write_register(SMB_STATE->callbacks.userdata, addr, data);
  }
}
static inline void apu_end_frame() {
  if (SMB_STATE->callbacks.apu_end_frame) {
    SMB_STATE->callbacks.apu_end_frame(SMB_STATE->callbacks.userdata);
  }
}
static inline void joy1(struct SMB_buttons *buttons) {
  if (SMB_STATE->callbacks.joy1) {
    return SMB_STATE->callbacks.joy1(SMB_STATE->callbacks.userdata, buttons);
  } else {
    *buttons = {0};
  }
}
static inline void joy2(struct SMB_buttons *buttons) {
  if (SMB_STATE->callbacks.joy2) {
    return SMB_STATE->callbacks.joy2(SMB_STATE->callbacks.userdata, buttons);
  } else {
    *buttons = {0};
  }
}

#define RAM(offset) (SMB_STATE->rammem[offset])
#define PPURAM(offset) (SMB_STATE->ppuram[offset])
#define CHRROM(offset) (SMB_STATE->chrrom[offset])

#define SMB1_ONLY (SMB_STATE->which_game == GAME_SMB1)
#define SMB2J_ONLY (SMB_STATE->which_game == GAME_SMB2J)
#define SMB1_2J_SWITCH(smb1, smb2j) (SMB1_ONLY ? (smb1) : (smb2j))
#define ssw SMB1_2J_SWITCH

#define FOR_LT(v, count) while (v += 1, v < count)
#define FOR_NE(v, count) while (v += 1, v != count)


#define PPU_STATE (SMB_STATE->ppu)
#include "ppu.h"
#undef PPU_STATE


// Write to $4016
static inline void joystick_strobe(byte x) {
}

#define APU_REG(name, addr) \
  static inline void name(byte x) { apu_write_register(addr, x); }

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

static inline void announce_main_scroll(unsigned short scroll_x) {
  SMB_STATE->scroll_x = scroll_x;
}
static inline void transfer_sprite_data(const byte *data) {
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

static inline void jmpengine_overflow(byte index) {
  warning("JMPENGINE overflow! %02X\n", index);
}

void draw_graphics(struct SMB_state *state);

// Implementation of Ghidra decompiler functions.

static inline ushort CONCAT11(byte a, byte b) {
  return (((ushort)a) << 8) | ((ushort)b);
}

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


#define SWAP(a, b) \
  do {             \
    byte tmp = a;  \
    a = b;         \
    b = tmp;       \
  } while (0)


// Higher-bit math helpers

// Loads a 16-bit value from two 8-bit values.
// Used as an RHS expression.
#define LOAD_16(src_hi, src_lo) ((u16)(((src_hi) << 8) | ((u8)(src_lo))))

// Store a 16-bit value into two 8-bit values from a 16-bit value.
#define STORE_16(dst_hi, dst_lo, val) { \
  u16 val_to_store = val; \
  dst_hi = (val_to_store) >> 8; \
  dst_lo = (val_to_store) & 0xff; \
}

// Performs `dst = src`.
// Mostly here for symmetry with the other arithmetic operators
#define SET_16_16(dst_hi, dst_lo, src_hi, src_lo) { \
  u8 src_lo_expand = src_lo; \
  dst_hi = src_hi; \
  dst_lo = src_lo_expand; \
}

// Performs `dst = dst + src`.
// dst_* and src_* are 8-bit integers.
#define ADD_16_16(dst_hi, dst_lo, src_hi, src_lo) { \
  u16 dst = ((u16)(dst_hi) << 8) | ((u16)(dst_lo)); \
  u16 src = ((u16)(src_hi) << 8) | ((u16)(src_lo)); \
  dst += src; \
  dst_hi = (dst >> 8) & 0xff; \
  dst_lo = dst & 0xff; \
}

#define SUB_16_16(dst_hi, dst_lo, src_hi, src_lo) { \
  u16 dst = ((u16)(dst_hi) << 8) | ((u16)(dst_lo)); \
  u16 src = ((u16)(src_hi) << 8) | ((u16)(src_lo)); \
  dst -= src; \
  dst_hi = (dst >> 8) & 0xff; \
  dst_lo = dst & 0xff; \
}

// Performs `dst = dst + src`.
// dst_* and src_* are 8-bit integers.
#define ADD_24_24(dst_hi, dst_me, dst_lo, src_hi, src_me, src_lo) { \
  u32 dst = ((u32)(dst_hi) << 16) | ((u32)(dst_me) << 8) | ((u32)(dst_lo)); \
  u32 src = ((u32)(src_hi) << 16) | ((u32)(src_me) << 8) | ((u32)(src_lo)); \
  dst += src; \
  dst_hi = (dst >> 16) & 0xff; \
  dst_me = (dst >> 8) & 0xff; \
  dst_lo = dst & 0xff; \
}

// Performs `dst = dst + src`.
// dst_* are 8-bit integers.
// src is an 8-bit integer, sign-extended to a 16-bit addend.
#define ADD_SIGNED_16_8(dst_hi, dst_lo, src) { \
  u8 h = src; \
  ADD_16_16(dst_hi, dst_lo, h >= 0x80 ? -1 : 0, h); \
}

// Performs `dst = dst + src`.
// dst_* and src_* are 8-bit integers.
// src is a 16-bit integer, sign-extended to a 24-bit addend.
#define ADD_SIGNED_24_16(dst_hi, dst_me, dst_lo, src_me, src_lo) { \
  u8 h = src_me; \
  ADD_24_24(dst_hi, dst_me, dst_lo, h >= 0x80 ? -1 : 0, h, src_lo); \
}

// Performs `dst = dst + src`.
// dst_* are 8-bit integers.
// src is an 8-bit integer.
#define ADD_UNSIGNED_16_8(dst_hi, dst_lo, src) { \
  ADD_16_16(dst_hi, dst_lo, 0, src); \
}

#define SUB_UNSIGNED_16_8(dst_hi, dst_lo, src) { \
  SUB_16_16(dst_hi, dst_lo, 0, src); \
}

// Performs `dst = src + addend`.
#define ADD_UNSIGNED_16_16_8(dst_hi, dst_lo, src_hi, src_lo, addend) { \
  u16 src = ((src_hi) << 8) | (src_lo); \
  src += (byte)(addend); \
  dst_lo = src & 0xff; \
  dst_hi = src >> 8; \
}

// Calculates the absolute difference between two bytes.
static inline byte ABS_DIFF(byte a, byte b) {
  if (a < b) {
    return b - a;
  } else {
    return a - b;
  }
}

// Get the first set bit position, where the LSB is position 1.
// Providing bits=0 returns 0.
//
// e.g. 142 => 2, because:
// 142 = 10001110
//             ^ position 2
//
// e.g. 64 => 7, because:
//  64 = 01000000
//        ^ position 7
static inline byte find_first_bit_position(byte bits) {
  if (bits == 0) {
    return 0;
  }

#if defined(__has_builtin) && __has_builtin(__builtin_ctz)
  // Count trailing zeros, plus 1
  return __builtin_ctz(bits) + 1;
#else
  // C impl
  byte i = 0;
  while (1) {
    i += 1;
    if (bits & 1) {
      break;
    }
    bits >>= 1;
  }
  return i;
#endif
}

// Represents a pointer type. Size is 2 bytes.
class RamPtr {
public:
  // fields, as laid out in 6502 memory
  byte lo;
  byte hi;

  RamPtr(ushort addr) : lo(addr & 0xFF), hi(addr >> 8) {}
  byte &operator*() {
    return RAM((hi << 8) | lo);
  }
  byte &operator[](int i) {
    // equivalent to LDA (ptr),Y
    return RAM(((hi << 8) | lo) + i);
  }
  operator ushort() const {
    return (hi << 8) | lo;
  }
  RamPtr& operator+=(int i) {
    ushort addr = *this;
    *this = RamPtr(addr + i);
    return *this;
  }
};

static inline RamPtr &RAMPtr(ushort offset) {
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

#define RAMPTR(addr) RAMPtr(addr)
#define RAMARRAY(addr, length) RamByteArray(addr, length)
#define RAMARRAY_CONST(addr, length) ConstRamByteArray(addr, length)
