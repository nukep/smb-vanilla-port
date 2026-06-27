#ifndef BASE_H
#define BASE_H

#include "base_public.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#  define NOINLINE __declspec(noinline)
#  define NORETURN __declspec(noreturn)
#  define likely(x)   (x)
#  define unlikely(x) (x)
#elif __GNUC__
#  define NOINLINE __attribute__((noinline))
#  define NORETURN __attribute__((noreturn))
#  define likely(x)   (__builtin_expect(!!(x), 1))
#  define unlikely(x) (__builtin_expect(!!(x), 0))
#endif

#ifdef PRINT_WARNINGS_AND_ERRORS
#  define error(fmt, ...) fprintf(stderr, "ERROR: " fmt, ##__VA_ARGS__)
#  define warning(fmt, ...) fprintf(stdout, "WARN: " fmt, ##__VA_ARGS__)
#else
#  define error(...)
#  define warning(...)
#endif

static inline void assert_smb_crashbug(bool condition, const char *message) {
  if (unlikely(!condition)) {
    error("%s\n", message);
    abort();
  }
}

static inline NORETURN void jmpengine_overflow(byte index) {
  error("JMPENGINE overflow! %02X\n", index);
  abort();
}

#define assert_eq_assumption(expected, actual) assert((expected) == (actual))
#define assert_eq_regressiontest(expected, actual) assert((expected) == (actual))

// Expected behavior in the original. Won't fatally break the game if it's false. Mostly there to give a heads-up to anyone modifying the code.
// Code may rely on the assumption.
// These are conditions that could be relaxed for things like enhancements to the game.
#define assume_weak_original(truthy) { \
  if (unlikely(!(truthy))) { warning("Behavior differs from expectation. %s:%d:%s: assume_weak_original(%s)\n", __FILE__, __LINE__, __func__, #truthy); } \
}

#define assert_unreachable() assert(0)

// Implementation of Ghidra decompiler functions.

static inline bool CARRY1(byte a, byte b) {
  u16 r = (u16)a + (u16)b;
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

// Performs `dst = dst - src`.
// dst_* and src_* are 8-bit integers.
#define SUB_24_24(dst_hi, dst_me, dst_lo, src_hi, src_me, src_lo) { \
  u32 dst = ((u32)(dst_hi) << 16) | ((u32)(dst_me) << 8) | ((u32)(dst_lo)); \
  u32 src = ((u32)(src_hi) << 16) | ((u32)(src_me) << 8) | ((u32)(src_lo)); \
  dst -= src; \
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

// Calcules the signed absolute difference between two bytes.
// e.g. (0, 255) -> 1
static inline byte ABS_DIFF_SIGNED(i8 a, i8 b) {
  byte d = a - b;
  if (d >= 0x80) {
    return -d;
  } else {
    return d;
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

#endif
