#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#if defined(__STDC_VERSION__) && __STDC_VERSION__ < 202000L &&                 \
    !defined(__STDBOOL_H)
typedef _Bool bool;
#define true 1
#define false 0
#endif // <C23 bool

typedef signed char i8;
typedef short i16;
typedef int i32;
typedef long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef float f32;
typedef double f64;
typedef long double f128;

typedef u8 byte;

typedef unsigned long uintptr_t; // NOTE: might be dangerous.

// Better scope semantics
#define global static
#define local static

#define UNUSED(x) (void)(x)

#endif // TYPEDEFS_H
