// The start of something magical! ✨

#include <cstdio>
#include <cstring>
#include <cstdint>

typedef unsigned char byte;
typedef unsigned short ushort;
// #define warning printf
#define warning(...)
#define NOINLINE __attribute__ ((noinline))

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

// A global RAM buffer
static byte _rammem[0x10000];

static inline byte& RAM(ushort offset) {
    return _rammem[offset];
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
        if (i < 0 || i >= length) {
            warning("Out of bounds for array %04X[%d] at index %d (= %04X)\n", addr, length, i, eff);
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
        if (i < 0 || i >= length) {
            warning("Out of bounds for array %04X[%d] at index %d (= %04X)\n", addr, length, i, eff);
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
// SMB:90CC
// void InitializeMemory(byte i) {
//     memset(&RAM(0x000), 0, 0x160);
//     memset(&RAM(0x200), 0, 0x500);
//     memset(&RAM(0x700), 0, i+1);
// }

// // SMB:9C13
// byte FindAreaPointer() {
//     return AreaAddrOffsets[(byte)(WorldAddrOffsets[WorldNumber] + AreaNumber)];
// }

// // SMB:9C09
// void GetAreaType() {
//     AreaType = (AreaPointer / 0x20) % 4;
// }

// // SMB:9C03
// void LoadAreaPointer() {
//     AreaPointer = FindAreaPointer();
//     GetAreaType();
// }

// // SMB:8FCF
// void InitializeGame() {
//     InitializeMemory(0x6F);
//     for (int i = 0; i < 32; i++) {
//         SoundMemory[i] = 0;
//     }
//     DemoTimer = 24;
//     LoadAreaPointer();
//     // NOT YET IMPLEMENTED
//     // InitializeArea();
// }

void jmpengine_overflow(byte index) {
    warning("JMPENGINE overflow! %02X\n", index);
}
void ppuctrl(byte x) {
    printf("ppuctrl = %02X\n", x);
}
void ppumask(byte x) { printf("ppumask = %02X\n", x); }
void oamaddr(byte x) { printf("oamaddr = %02X\n", x); }
void ppuscroll(byte x) { printf("ppuscroll = %02X\n", x); }
void ppuaddr(byte x) { printf("ppuaddr = %02X\n", x); }
void ppudata(byte x) { }
void joystick_strobe(byte x) { printf("joystick_strobe = %02X\n", x); }
void apu_dmc_raw(byte x) { printf("apu_dmc_raw = %02X\n", x); }
void apu_oamdma(byte x) { printf("apu_oamdma = %02X\n", x); }
void apu_snd_chn(byte x) { printf("apu_snd_chn = %02X\n", x); }

byte ppustatus() {
    printf("<- ppustatus\n");
    return 0x80;
}
byte ppudata() {
    printf("<- ppudata\n");
    return 0;
}
byte joy1() {
    printf("<- joy1\n");
    return 0;
}
byte joy2() {
    printf("<- joy2\n");
    return 0; 
}

typedef uint64_t int3;
typedef uint64_t uint3;
typedef uint64_t uint6;
typedef uint64_t uint7;

#include "generated/smb.cpp"

int init_rom() {
    byte *rom_org = &RAM(0x8000);

    FILE *f = fopen("smb.nes", "rb");
    if (f) {
        fseek(f, 0x10, SEEK_SET);
        fread(rom_org, 1, 0x8000, f);
        fclose(f);
        printf("ROM loaded\n");
        return 1;
    } else {
        printf("Could not open ROM\n");
        return 0;
    }
}

void dump_ram() {
    const byte *ram = &RAM(0x0);
    FILE *f = fopen("ram.bin", "wb");
    if (f) {
        fwrite(ram, 1, 0x800, f);
        fclose(f);
        printf("RAM dumped\n");
    } else {
        printf("Could not dump RAM\n");
    }
}

int main()
{
    if (!init_rom()) {
        goto exit;
    }

    Start();

    // run a frame
    NonMaskableInterrupt();

exit:
    dump_ram();
}