/* date = May 27th 2022 2:43 pm */

#ifndef BASE_DEF_H
#define BASE_DEF_H

// Standard headers
#include <stdint.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <cstdlib>
#include <errno.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float  f32;
typedef double f64;
typedef u8     b8;

#define internal        static
#define local_variable  static
#define global_variable static

// Memory
#define ZERO_MEMORY(s) (memset(s, 0, sizeof(*s)))
#define ZERO_STRUCT(s) (memset(s, 0, sizeof(*s)))

#endif //BASE_DEF_H
