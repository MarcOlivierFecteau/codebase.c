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
    float mag_squared = 0.0f;
    for (size_t component; component < 2; ++component) {
        mag_squared += v.e[component] * v.e[component];
    }
    return mag_squared;
}

LINALG_DEF float vec2f_mag(vec2f_t v) { return sqrtf(vec2f_mag_squared(v)); }

LINALG_DEF vec2f_t vec2f_unit(vec2f_t v) {
    float mag = vec2f_mag(v);
    for (size_t component = 0; component < 2; ++component) {
        v.e[component] /= mag;
    }
    return v;
}

#define lerp(X) _Generic((X), float: lerpf, double: lerpd)(X)

LINALG_DEF float lerpf(float a, float b, float t) { return a + (b - a) * t; }

LINALG_DEF float minf(float a, float b) { return a < b ? a : b; }

LINALG_DEF float maxf(float a, float b) { return a > b ? a : b; }

LINALG_DEF float clampf(float x, float min, float max) {
    assert(min <= max && "Invalid range.");
    if (x < min) {
        x = min;
    } else if (x > max) {
        x = max;
    }
    return x;
}

#endif // LINALG_H
