#ifndef LINALG_H
#define LINALG_H

#include <assert.h>
#include <math.h>
#include <stdarg.h>

#if !defined(__STDDEF_H)
typedef unsigned long size_t;
#endif // __STDDEF_H

#ifndef LINALG_DEF
#define LINALG_DEF static inline
#endif // LINALG_DEF

typedef union {
    struct {
        float x, y;
    };
    float e[2];
} vec2f_t;

LINALG_DEF vec2f_t vec2f_splat(float x) {
    vec2f_t v = {{x, x}};
    return v;
}

LINALG_DEF vec2f_t vec2f_add(vec2f_t a, vec2f_t b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

LINALG_DEF vec2f_t vec2f_div(vec2f_t a, vec2f_t b);
LINALG_DEF vec2f_t vec2f_splat(float x);

LINALG_DEF vec2f_t vec2f_sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec2f_t sum = {0};
    for (size_t i = 0; i < n; ++i) {
        vec2f_t v = va_arg(args, vec2f_t);
        sum = vec2f_add(sum, v);
    }
    return sum;
}

LINALG_DEF float vec2f_mag_squared(vec2f_t v) {
    return v.x * v.x + v.y * v.y;
}

LINALG_DEF float vec2f_mag(vec2f_t v) { return sqrtf(vec2f_mag_squared(v)); }

LINALG_DEF vec2f_t vec2f_unit(vec2f_t v) {
    float mag = vec2f_mag(v);
    return vec2f_div(v, vec2f_splat(mag));
}

#endif // LINALG_H
