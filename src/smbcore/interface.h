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
  u16 value;
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

  // Native pointers to ROM
  // (right now these are either null or point to somewhere in rammmem)

  const byte *area_data;
  const byte *enemy_data;
  const byte *music_data;

  // For SMB2J
  byte patch_current_player;
};

// The singleton SMB_state used during the SMB_tick() invocation. This is considered internal and should not be used by callers of the library.
extern thread_local struct SMB_state *SMB_STATE;

#define RAM(offset) (SMB_STATE->rammem[offset])
#define PPURAM(offset) (SMB_STATE->ppuram[offset])
#define CHRROM(offset) (SMB_STATE->chrrom[offset])
#define RAM_CONST(offset) ((const byte)SMB_STATE->rammem[offset])

#define AreaData (SMB_STATE->area_data)
#define EnemyData (SMB_STATE->enemy_data)
#define MusicData (SMB_STATE->music_data)

#define PatchCurrentPlayer (SMB_STATE->patch_current_player)

#define SMB1_ONLY (SMB_STATE->which_game == GAME_SMB1)
#define SMB2J_ONLY (SMB_STATE->which_game == GAME_SMB2J)
#define SMB1_2J_SWITCH(smb1, smb2j) (SMB1_ONLY ? (smb1) : (smb2j))
#define ssw SMB1_2J_SWITCH

#define PPU_STATE (SMB_STATE->ppu)

static inline const byte * rom_ptr(const u16 addr) {
  if (unlikely(addr == 0)) {
    // Null pointer
    // We might get this on startup if RAM is uninitialized
    return 0;
  }

  if (unlikely(addr < 0x6000)) {
    warning("Attempt to resolve a pointer to non-ROM. Address: $%04X\n", addr);
  }

  return &RAM(addr);
}

// Array bounds checking is only available in C++
#ifndef __cplusplus
#  undef CHECK_ARRAY_BOUNDS
#endif

#ifndef CHECK_ARRAY_BOUNDS

// Access the RAM buffer directly, as pointers

#  define RAMARRAY(addr, length) (&RAM(addr))
#  define RAMARRAY_CONST(addr, length) ((const byte*)(&RAM(addr)))

#else

// Represents a byte array at a specific address.
class RamByteArray {
private:
  u16 addr;
  u16 length;
  int offset;

public:
  RamByteArray(u16 addr) : addr(addr), length(0), offset(0) {}
  RamByteArray(u16 addr, u16 length) : addr(addr), length(length), offset(0) {}
  RamByteArray(u16 addr, u16 length, int offset) : addr(addr), length(length), offset(offset) {}
  byte &operator*() const {
    return RAM(addr + offset);
  }
  byte *operator&() const {
    return &RAM(addr + offset);
  }
  RamByteArray operator+(int i) const {
    // Adding an array by a constant gives another array.
    return RamByteArray(addr, length, offset + i);
  }
  byte &operator[](int i) const {
    const int idx = offset + i;
    // equivalent to LDA addr,X
    u16 eff = addr + idx;

    // TODO: account for zero-page wraparound for some variables.
    // some arrays in zero-page use addressing modes that wraparound, while others do not.
    //
    // e.g.
    //    b930: b9 d7 00  lda $00d7, y
    // and
    //    b9c5: b5 0f     lda $0f, x
    //
    // i haven't observed a wraparound ever happening in practice, but this should be verified

    if (length != 0) {
      if (unlikely(idx < 0 || idx >= length)) {
        warning("Out of bounds for array $%04X length %d. accessed $%04X[%d] (= $%04X)\n", addr, length, addr+offset, i, eff);
      }
    }

    return RAM(eff);
  }
};

// Represents a byte array at a specific address.
// Read-only, can't write to these
class ConstRamByteArray {
private:
  u16 addr;
  u16 length;

public:
  ConstRamByteArray(u16 addr) : addr(addr), length(0) {}
  ConstRamByteArray(u16 addr, u16 length) : addr(addr), length(length) {}
  const byte &operator*() const {
    return RAM(addr);
  }
  const byte *operator&() const {
    return &RAM(addr);
  }
  const byte &operator[](int i) const {
    // equivalent to LDA addr,X
    u16 eff = addr + i;

    if (length != 0) {
      if (unlikely(i < 0 || i >= length)) {
        warning("Out of bounds for array $%04X length %d. accessed $%04X[%d] (= $%04X)\n", addr, length, addr, i, eff);
      }
    }

    return RAM(eff);
  }
};

#define RAMARRAY(addr, length) RamByteArray(addr, length)
#define RAMARRAY_CONST(addr, length) ConstRamByteArray(addr, length)

#endif


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

static inline void update_palette(void) {
  if (SMB_STATE->callbacks.update_palette) {
    SMB_STATE->callbacks.update_palette(SMB_STATE->callbacks.userdata, &PPURAM(0x3F00));
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

static inline void apu_write_register(u16 addr, byte data) {
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

// Write to $2000
static inline void ppuctrl(byte x) {
  PPU_STATE.t.NN = x & 0x03;
  PPU_STATE.increment_mode = (x & 0x04) ? 1 : 0;
}

// Write to $2001
static inline void ppumask(byte x) {
  // in smb1 and smb2j, it's only ever:
  // 0x06     (e.g. background and sprites disabled, leftmost column turned on)
  // 0x00     (e.g. everything disabled)
  // 0x1E     (e.g. background and sprites enabled, leftmost column turned on)

  // Effectively, we evaluate this as a boolean "screen is on" or "screen is off" state.
  // 0x18 is "enable background and sprites"

  PPU_STATE.screen_on = (x & 0x18) != 0;
}

// Write to $2005
static inline void ppuscroll(byte x) {
  if (PPU_STATE.w == 0) {
    PPU_STATE.t.XXXXX = x >> 3;
    PPU_STATE.x = x & 0x07;
  } else {
    PPU_STATE.t.YYYYY = x >> 3;
    PPU_STATE.t.yyy = x & 0x07;
  }
  PPU_STATE.w ^= 1;
}

// Write to $2006
static inline void ppuaddr(byte x) {
  if (PPU_STATE.w == 0) {
    PPU_STATE.t.hi = x & 0x3F;
  } else {
    PPU_STATE.t.lo = x;
    PPU_STATE.v = PPU_STATE.t;
  }
  PPU_STATE.w ^= 1;
}

// Write to $2007
static inline void ppudata(byte x) {
  u16 addr = PPU_STATE.v.value & 0x3FFF;

  if (addr == 0x3F10) {
    addr = 0x3F00;
  }

  PPURAM(addr) = x;

  if (PPU_STATE.increment_mode == 0) {
    PPU_STATE.v.value += 1;
  } else {
    PPU_STATE.v.value += 32;
  }
}

// Read from $2002
static inline byte ppustatus() {
  PPU_STATE.w = 0;
  return 0x80;
}
