

// Write to $2000
static inline void ppuctrl(byte x) {
    PPU_STATE.t.NN = x & 0x03;
    PPU_STATE.increment_mode = (x & 0x04) ? 1 : 0;
}

static byte ENCOUNTERED[256];

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
    ushort& v = PPU_STATE.v.value;

    ushort addr = v & 0x3FFF;

    if (addr == 0x3F10) {
        addr = 0x3F00;
    }

    PPURAM(addr) = x;

    if (PPU_STATE.increment_mode == 0) {
        v += 1;
    } else {
        v += 32;
    }
}

// Read from $2002
static inline byte ppustatus() {
    PPU_STATE.w = 0;
    return 0x80;
}
