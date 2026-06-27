#ifndef BASE_PUBLIC_H
#define BASE_PUBLIC_H

#include <stdint.h>
#include <stddef.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

typedef uint8_t byte;

// Use Rust/Zig style typedefs for integers

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

typedef size_t usize;

#endif
