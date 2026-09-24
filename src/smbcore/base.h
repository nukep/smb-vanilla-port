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

// Make the compiler assume the condition is true.
// Should always work as an expression. Value is unimportant.
#if defined(__GNUC__)
  #define assume(cond) ((void)((cond) ? (void)0 : __builtin_unreachable()))
#elif defined(_MSC_VER)
  #define assume(cond) __assume(cond)
#else
  #define assume(cond) ((void)0)
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

static inline NORETURN void jmpengine_overflow(u8 index) {
  error("JMPENGINE overflow! %02X\n", index);
  abort();
}

// Declare expected behavior in the original. May break the game if it's false.
// This could be optimized by the compiler if we're daring enough (by default, we're not).
#ifdef ASSUME_EXPECTS
#  define expect(truthy) assume(truthy)
#else
#  define expect(truthy) assert(truthy)
#endif

// Expected behavior in the original. Won't fatally break the game if it's false. Mostly there to give a heads-up to anyone modifying the code.
// Code may rely on the expectation.
// These are conditions that could be relaxed for things like enhancements to the game.
#define expect_weak(truthy) { \
  if (unlikely(!(truthy))) { warning("Behavior differs from expectation. %s:%d:%s: expect_weak(%s)\n", __FILE__, __LINE__, __func__, #truthy); } \
}

#define unreachable() expect(false)

#ifdef USE_POISON_DEBUG

#include <stdlib.h>
#include <time.h>

static inline u8 _poison_u8_random(void) {
  static bool RAND_INIT = false;
  if (!RAND_INIT) {
    // The typical lousy way of initializing a seed
    srand((unsigned int)time(NULL));
    RAND_INIT = true;
  }

  int v = rand();

  // 25% chance that we set to 0 or 1
  // We want an increased chance of these, because values like 0 and 1 are more likely to be significant
  const bool as_boolean  = (v & 0x300) == 0;

  if (as_boolean) {
    return v & 1;
  } else {
    return v & 0xff;
  }
}

// For debugging: Set the 8-bit variable to a "poisoned" state.
// A poisoned state means that the value should not be read, and that doing so is an error.
// A defined write reverts the poisoned state.
// This is implementation-defined. One idea is to use instrumention or a tool like Valgrind to poison values.
// The poor-man's approach is to set it to a random value so that tests would likely fail if the poisoned value is read.
#define poison_u8(var) var = _poison_u8_random();

#else

#define poison_u8(var)

#endif

#define INVBITS_u8(bits) \
  (u8)(~(bits))


#define SWAP(a, b) \
  do {             \
    u8 tmp = a;  \
    a = b;         \
    b = tmp;       \
  } while (0)


// Higher-bit math helpers

// Loads a 16-bit value from two 8-bit values.
// Used as an RHS expression.
static inline u16 LOAD_16(const u8 src_hi, const u8 src_lo) {
  return (u16)(((u16)src_hi << 8) | (u16)src_lo);
}

static inline i16 LOAD_i16(const i8 src_hi, const i8 src_lo) {
  return (i16)LOAD_16((u8)src_hi, (u8)src_lo);
}

// Store a 16-bit value into two 8-bit values from a 16-bit value.
// Unsigned and signed.
#define STORE_16(dst_hi, dst_lo, val) { \
  u16 val_to_store = (u16)(val); \
  dst_hi = (val_to_store) >> 8; \
  dst_lo = (val_to_store) & 0xff; \
}

// Performs `dst = src`.
// Mostly here for symmetry with the other arithmetic operators
// Unsigned and signed.
#define SET_16_16(dst_hi, dst_lo, src_hi, src_lo) { \
  u8 src_lo_expand = (u8)(src_lo); \
  dst_hi = (u8)(src_hi); \
  dst_lo = src_lo_expand; \
}

// Performs `dst = dst + src`.
// dst_* and src_* are 8-bit integers.
// Unsigned and signed.
#define ADD_16_16(dst_hi, dst_lo, src_hi, src_lo) { \
  u16 dst = ((u16)(u8)(dst_hi) << 8) | ((u16)(u8)(dst_lo)); \
  u16 src = ((u16)(u8)(src_hi) << 8) | ((u16)(u8)(src_lo)); \
  dst += src; \
  dst_hi = (dst >> 8) & 0xff; \
  dst_lo = dst & 0xff; \
}

#define SUB_16_16(dst_hi, dst_lo, src_hi, src_lo) { \
  u16 dst = ((u16)(u8)(dst_hi) << 8) | ((u16)(u8)(dst_lo)); \
  u16 src = ((u16)(u8)(src_hi) << 8) | ((u16)(u8)(src_lo)); \
  dst -= src; \
  dst_hi = (dst >> 8) & 0xff; \
  dst_lo = dst & 0xff; \
}

// Performs `dst = dst + src`.
// dst_* and src_* are 8-bit integers.
// Unsigned and signed.
#define ADD_24_24(dst_hi, dst_me, dst_lo, src_hi, src_me, src_lo) { \
  u32 dst = ((u32)(u8)(dst_hi) << 16) | ((u32)(u8)(dst_me) << 8) | ((u32)(u8)(dst_lo)); \
  u32 src = ((u32)(u8)(src_hi) << 16) | ((u32)(u8)(src_me) << 8) | ((u32)(u8)(src_lo)); \
  dst += src; \
  dst_hi = (dst >> 16) & 0xff; \
  dst_me = (dst >> 8) & 0xff; \
  dst_lo = dst & 0xff; \
}

// Performs `dst = dst - src`.
// dst_* and src_* are 8-bit integers.
// Unsigned and signed.
#define SUB_24_24(dst_hi, dst_me, dst_lo, src_hi, src_me, src_lo) { \
  u32 dst = ((u32)(u8)(dst_hi) << 16) | ((u32)(u8)(dst_me) << 8) | ((u32)(u8)(dst_lo)); \
  u32 src = ((u32)(u8)(src_hi) << 16) | ((u32)(u8)(src_me) << 8) | ((u32)(u8)(src_lo)); \
  dst -= src; \
  dst_hi = (dst >> 16) & 0xff; \
  dst_me = (dst >> 8) & 0xff; \
  dst_lo = dst & 0xff; \
}

// Performs `dst = dst + src`.
// dst_* are 8-bit integers.
// src is an 8-bit integer, sign-extended to a 16-bit addend.
#define ADD_SIGNED_16_8(dst_hi, dst_lo, src) { \
  i8 src_expand = src; \
  ADD_16_16(dst_hi, dst_lo, src_expand < 0 ? -1 : 0, src_expand); \
}

// Performs `dst = dst + src`.
// dst_* and src_* are 8-bit integers.
// src is a 16-bit integer, sign-extended to a 24-bit addend.
#define ADD_SIGNED_24_16(dst_hi, dst_me, dst_lo, src_me, src_lo) { \
  i8 src_me_expand = src_me; \
  i8 src_lo_expand = src_lo; \
  ADD_24_24(dst_hi, dst_me, dst_lo, src_me_expand < 0 ? -1 : 0, src_me_expand, src_lo_expand); \
}

// Performs `dst = dst + src`.
// dst_* are 8-bit integers.
// src is an 8-bit integer.
#define ADD_UNSIGNED_16_8(dst_hi, dst_lo, src) { \
  u8 src_expand = src; \
  ADD_16_16(dst_hi, dst_lo, 0, src_expand); \
}

#define SUB_UNSIGNED_16_8(dst_hi, dst_lo, src) { \
  u8 src_expand = src; \
  SUB_16_16(dst_hi, dst_lo, 0, src_expand); \
}

// Performs `dst = src + addend`.
#define ADD_UNSIGNED_16_16_8(dst_hi, dst_lo, src_hi, src_lo, addend) { \
  u8 addend_expand = addend; \
  u16 src = ((u16)(u8)(src_hi) << 8) | (u16)(u8)(src_lo); \
  src += addend_expand; \
  dst_lo = src & 0xff; \
  dst_hi = src >> 8; \
}

// Calculates the absolute difference between two bytes.
static inline u8 ABS_DIFF(u8 a, u8 b) {
  if (a < b) {
    return b - a;
  } else {
    return a - b;
  }
}

// Calcules the signed absolute difference between two bytes.
// e.g. (0, 255) -> 1
static inline u8 ABS_DIFF_SIGNED(i8 a, i8 b) {
  u8 d = (u8)(a - b);
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
static inline u8 find_first_bit_position(u8 bits) {
  if (bits == 0) {
    return 0;
  }

#if defined(__has_builtin) && __has_builtin(__builtin_ctz)
  // Count trailing zeros, plus 1
  return __builtin_ctz(bits) + 1;
#else
  // C impl
  u8 i = 0;
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
