#include "foundation.h"
#include "common.h"

#include "smbcore/vars.h"

void set_world_and_level(byte world, byte level) {
  WorldNumber = world;
  LevelNumber = level;

  ushort WorldAddrOffsets = SMB1_ONLY ? 0x9CB4 : 0xC357;
  ushort AreaAddrOffsetsPtr = SMB1_ONLY ? 0x9CBC : 0xC360;

  byte off = 0;
  for (int i = 0; i < level; i++) {
    // skip "intermission" areas
    if (RAM(AreaAddrOffsetsPtr + RAM(WorldAddrOffsets + world) + off) == 0x29) {
      off += 1;
    }
    off += 1;
  }
  AreaNumber = off;
}

// Set 0's in memory.
// The provided number is up to which address in the $0700 page to set to zero.
// e.g. if i=0x14, then clear up to $0714 inclusive.
// Doesn't set the stack, between $0160 and $01FF inclusive.
// On SMB2J, doesn't set $0100 to $0108 inclusive.
// Note that this port, which doesn't target the 6502, doesn't use the stack at $0160-$1FFF at all.

// SMB:90CC, SM2MAIN:6f08
// Signature: [Y] -> [A]
byte InitializeMemory(byte i) {
  if (SMB1_ONLY) {
    memset(&RAM(0x000), 0, 0x160);
    memset(&RAM(0x200), 0, (size_t)0x700 - 0x200);
    memset(&RAM(0x700), 0, (byte)(i + 1));
  }
  if (SMB2J_ONLY) {
    memset(&RAM(0x000), 0, 0x100);
    memset(&RAM(0x109), 0, (size_t)0x160 - 0x109);
    memset(&RAM(0x200), 0, (size_t)0x700 - 0x200);
    memset(&RAM(0x700), 0, (byte)(i + 1));
  }
  return 0;
}

static inline void dectimer(byte &timer) {
  if (timer != 0) {
    timer--;
  }
}

void dectimers() {
  if (TimerControl >= 2) {
    TimerControl -= 1;
  } else {
    // If TimerControl is 0 or 1...
    // decrement the timers.

    TimerControl = 0;

    // We unrolled a loop on the timers here
    // The NES version decrements in reverse order as listed here, but the order doesn't really matter

    dectimer(SelectTimer);
    dectimer(PlayerAnimTimer);
    dectimer(JumpSwimTimer);
    dectimer(RunningTimer);
    dectimer(BlockBounceTimer);
    dectimer(SideCollisionTimer);
    dectimer(JumpspringTimer);
    dectimer(GameTimerCtrlTimer);
    dectimer(ClimbSideTimer);
    for (int i = 0; i < 5; i++) {
      dectimer(EnemyFrameTimer[i]);
    }
    dectimer(FrenzyEnemyTimer);
    dectimer(BowserFireBreathTimer);
    dectimer(StompTimer);
    dectimer(AirBubbleTimer);
    dectimer(UnusedTimer1);
    dectimer(UnusedTimer2);
    // up to and including the timer at $0794

    IntervalTimerControl -= 1;
    if (IntervalTimerControl >= 0x80) {
      IntervalTimerControl = 20;
      dectimer(ScrollIntervalTimer);
      for (int i = 0; i < 7; i++) {
        dectimer(EnemyIntervalTimer[i]);
      }
      dectimer(BrickCoinTimer);
      dectimer(InjuryTimer);
      dectimer(StarInvincibleTimer);
      dectimer(ScreenTimer);
      dectimer(WorldEndTimer);
      dectimer(DemoTimer);
      dectimer(UnusedTimer3);
      // up to and including the timer at $07A3
    }
  }
}

// This is the only subroutine in all of SMB that writes to the PPU! (aside from WriteNTAddr, which blanks a nametable)
// Each draw buffer item has the format: <ppu_hi> <ppu_lo> <count> <data...>
//
// SMB:8edd, SM2MAIN:6d56
// Signature: [r00, r01] -> []
void UpdateScreen(const byte *buf) {
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

// SMB:8e2d, SM2MAIN:6ca6
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

// SMB:8e5c, SM2MAIN:6cd5
// Signature: [] -> []
void ReadJoypads() {
  joystick_strobe(1);
  joystick_strobe(0);
  ReadPortBits(0);
  ReadPortBits(1);
}

// SMB:8e6a, SM2MAIN:6ce3
// Signature: [X] -> []
void ReadPortBits(byte joynum) {
  byte bits = 0;

  struct SMB_buttons buttons = {0};

  if (joynum == 0) {
    joy1(&buttons);
  } else {
    joy2(&buttons);
  }

  bits |= buttons.a ? 0x80 : 0;
  bits |= buttons.b ? 0x40 : 0;
  bits |= buttons.select ? 0x20 : 0;
  bits |= buttons.start ? 0x10 : 0;
  bits |= buttons.u ? 0x08 : 0;
  bits |= buttons.d ? 0x04 : 0;
  bits |= buttons.l ? 0x02 : 0;
  bits |= buttons.r ? 0x01 : 0;

  SavedJoypadBits[joynum] = bits;

  // If Select or Start were pressed last time this was called, then "unpress" them.
  if ((bits & (0x20 | 0x10) & JoypadBitMask[joynum]) != 0) {
    SavedJoypadBits[joynum] = bits & ~(0x20 | 0x10);
  } else {
    JoypadBitMask[joynum] = bits;
  }
}

// SMB1 and SMB2J's Pseudo-Random Number Generator
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
void update_prng(byte *prng) {
  byte a = prng[0] & 2;
  byte b = prng[1] & 2;
  bool newbit = a != b;

  for (int i = 0; i < 7; i++) {
    bool next = (prng[i] & 1) != 0;
    prng[i] = (newbit ? 0x80 : 0x00) | (prng[i] >> 1);
    newbit = next;
  }
}
