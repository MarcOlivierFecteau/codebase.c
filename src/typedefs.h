#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ < 202000) &&               \
    !defined(__STDBOOL_H)
typedef _Bool bool;
#define true 1
#define false 0
#endif

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

#endif // TYPEDEFS_H
