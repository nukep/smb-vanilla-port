// The start of something magical! ✨

#include <cstdio>
#include <cstring>
#include <cstdint>
#include <utility>

typedef unsigned char byte;
typedef unsigned short ushort;
//#define warning printf
#define warning(...)
#define NOINLINE __attribute__ ((noinline))


// A global RAM buffer
static byte _rammem[0x10000];

// And a copy of CHR ROM
static byte _chrrom[0x2000];

byte& RAM(ushort offset) {
    return _rammem[offset];
}
template<typename T>
inline T& RAM(ushort offset) {
    byte* ptr = _rammem + offset;
    T* dataptr = (T*)ptr;
    return *dataptr;
}

byte& CHRROM_writable(ushort offset) {
    return _chrrom[offset & 0x1FFF];
}
inline const byte& CHRROM(ushort offset) {
    return _chrrom[offset & 0x1FFF];
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
    RamPtr *ptr = (RamPtr*)(_rammem + offset);
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


// An iterator that implements the "do-while i != 0" pattern.
// if i starts at 0, then it iterates 256 times (0, 255, 254, 253, ..., 1)
class countdown_zero {
private:
    byte i;
    bool started;
public:
    countdown_zero(): i(1), started(true) {}
    countdown_zero(byte i): i(i), started(false) {}

    countdown_zero begin() { return *this; }
    countdown_zero end() { return countdown_zero(); }
    byte operator*() { return i; }

    bool operator!=(const countdown_zero &other) {
        if (!started || !other.started) {
            return true;
        }
        return !(i == 0 || other.i == 0);
    }

    void operator++() {
        i -= 1;
        started = true;
    }
};

// An iterator that implements the "do-while (char)i >= 0" pattern.
// Never includes a "negative" number. Only yields 0-127 inclusive.
class countdown_positive {
private:
    byte i;
    bool started;
public:
    countdown_positive(): i(0), started(true) {}
    countdown_positive(byte i): i(i), started(false) {}

    countdown_positive begin() { return *this; }
    countdown_positive end() { return countdown_positive(); }
    byte operator*() { return i; }

    bool operator!=(const countdown_positive &other) {
        if (!started || !other.started) {
            return true;
        }
        return  !(i >= 128 || other.i >= 128);
    }

    void operator++() {
        i -= 1;
        started = true;
    }
};

// Workaround!!!
// Used to avoid some undefined behavior in MSVC
__declspec(noinline) static byte force_byte(byte x) {
    return x;
}

/////////////////////////
/// implemented code! ///
/////////////////////////

#include "generated/smb_romarrays.h"
#include "generated/smb_vars.h"
static const ConstRamByteArray AreaAddrOffsets = ConstRamByteArray(0x9CBC, 0x24);
static const ConstRamByteArray GameText = ConstRamByteArray(0x8752, 0x9B);

// Set 0's in memory.
// The provided number is up to which address in the $0700 page to set to zero.
// e.g. if i=0x14, then clear up to $0714 inclusive.
// Doesn't set the stack, between $0160 and $01FF inclusive.
// Note that this port, which doesn't target the 6502, doesn't use the stack at $0160-$1FFF at all.
// 
// SMB:90CC
// Signature: [Y] -> [A]
byte InitializeMemory(byte i) {
    memset(&RAM(0x000), 0, 0x160);
    memset(&RAM(0x200), 0, (size_t)0x700-0x200);
    memset(&RAM(0x700), 0, (byte)(i+1));
    return 0;
}

void jmpengine_overflow(byte index) {
    warning("JMPENGINE overflow! %02X\n", index);
}
void ppuctrl(byte x);
void ppumask(byte x);
void ppuscroll(byte x);
void ppuaddr(byte x);
void ppudata(byte x);
void joystick_strobe(byte x);
void apu_dmc_raw(byte x);
void apu_snd_chn(byte x);

byte ppustatus();
byte ppudata();
byte joy1();
byte joy2();

typedef uint64_t int3;
typedef uint64_t uint3;
typedef uint64_t uint6;
typedef uint64_t uint7;

#include "generated/smb.h"
#include "generated/smb.cpp"
#include "smb_functions.h"


// SMB:8000
// Signature: [] -> []
void Start() {
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


void announce_main_scroll();
void transfer_sprite_data(const byte*);


void SoundEngine() {
    // Stubbed out for now
    // Sound code is horrifying, so we're dealing with it later
}

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

static inline void dectimer(byte& timer) {
    if (timer != 0) {
        timer--;
    }
}

// SMB:8082
// Signature: [] -> []
void NonMaskableInterrupt() {
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
        if (TimerControl >= 2) {
            TimerControl -= 1;
        } else {
            // If TimerControl is 0 or 1...
            // decrement the timers.

            TimerControl = 0;

            // We unrolled a loop on the timers here
            // The NES version decrements in reverse order as listed here, but the order doesn't really matter

            dectimer(SelectTimer);      dectimer(PlayerAnimTimer);    dectimer(JumpSwimTimer);   dectimer(RunningTimer);
            dectimer(BlockBounceTimer); dectimer(SideCollisionTimer); dectimer(JumpspringTimer); dectimer(GameTimerCtrlTimer);
            dectimer(ClimbSideTimer);
            for (int i = 0; i < 5; i++) {
                dectimer(EnemyFrameTimer[i]);
            }
            dectimer(FrenzyEnemyTimer); dectimer(BowserFireBreathTimer); dectimer(StompTimer); dectimer(AirBubbleTimer);
            dectimer(UnusedTimer1);     dectimer(UnusedTimer2);
            // up to and including the timer at $0794

            IntervalTimerControl -= 1;
            if (IntervalTimerControl >= 0x80) {
                IntervalTimerControl = 20;
                dectimer(ScrollIntervalTimer);
                for (int i = 0; i < 7; i++) {
                    dectimer(EnemyIntervalTimer[i]);
                }
                dectimer(BrickCoinTimer); dectimer(InjuryTimer); dectimer(StarInvincibleTimer); dectimer(ScreenTimer);
                dectimer(WorldEndTimer);  dectimer(DemoTimer);   dectimer(UnusedTimer3);
                // up to and including the timer at $07A3
            }
        }
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
    announce_main_scroll();
}

// This is the only subroutine in all of SMB that writes to the PPU! (aside from WriteNTAddr, which blanks a nametable)
// Each draw buffer item has the format: <ppu_hi> <ppu_lo> <count> <data...>
// 
// SMB:8edd, SMB2:6d56
// Signature: [r00, r01] -> []
void UpdateScreen(const byte* buf) {
    while (buf[0] != 0) {
        // Start writing to the PPU address
        ppustatus();
        ppuaddr(buf[0]);
        ppuaddr(buf[1]);

        if (buf[2] & 0x80) {
            // Draw vertically
            Mirror_PPU_CTRL_REG1 |= 0x04;
        } else {
            // Draw horizontally
            Mirror_PPU_CTRL_REG1 &= ~0x04;
        }
        ppuctrl(Mirror_PPU_CTRL_REG1);

        int count = buf[2] & 0x3F;
        if (count == 0) {
            // The original SMB does a do-while loop, and so a count of 0 is actually 256
            count = 256;
        }

        if (buf[2] & 0x40) {
            // Run-length encoding
            for (int i = 0; i < count; i++) {
                ppudata(buf[3]);
            }
            buf += 3 + 1;
        } else {
            // Variable-length
            for (int i = 0; i < count; i++) {
                ppudata(buf[3 + i]);
            }
            buf += 3 + count;
        }

        // The original SMB does these extra, seemingly pointless assignments to the ppuaddr register
        ppuaddr(0x3f);
        ppuaddr(0);
        ppuaddr(0);
        ppuaddr(0);
    }
    ppustatus();
    ppuscroll(0);
    ppuscroll(0);
}

// SMB:8e2d
// Signature: [A] -> []
void WriteNTAddr(byte ppu_page) {
    ppuaddr(ppu_page);
    ppuaddr(0);

    // Fill the nametable with blank tiles
    for (int i = 0; i < 0x3C0; i++) {
        ppudata(0x24);
    }
    // ... and clear the colors of all metatiles to the first palette
    for (int i = 0; i < 0x40; i++) {
        ppudata(0x00);
    }

    VRAM_Buffer1_Offset = 0;
    VRAM_Buffer1[0] = 0;
    HorizontalScroll = 0;
    VerticalScroll = 0;
    ppuscroll(0);
    ppuscroll(0);
    return;
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
        std::swap(NumberofLives, OffScr_NumberofLives);
        std::swap(HalfwayPage,   OffScr_HalfwayPage);
        std::swap(LevelNumber,   OffScr_LevelNumber);
        std::swap(Hidden1UpFlag, OffScr_Hidden1UpFlag);
        std::swap(CoinTally,     OffScr_CoinTally);
        std::swap(WorldNumber,   OffScr_WorldNumber);
        std::swap(AreaNumber,    OffScr_AreaNumber);
        
        return false;
    } else {
        return true;
    }
}
