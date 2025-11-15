#ifndef LINALG_H
#define LINALG_H

#ifdef USE_TYPEDEFS
#include "typedefs.h"
#endif // USE_TYPEDEFS
#include "common_math.h"
#include <math.h>
#include <stdarg.h>

#if !defined(__STDDEF_H)
typedef unsigned long size_t;
#endif // __STDDEF_H

#ifndef LINALG_DEF
#define LINALG_DEF static inline
#endif // LINALG_DEF

typedef union {
    struct { float x, y; };
    float e[2];
} vec2f_t;

typedef union {
    struct { double x, y; };
    double e[2];
} vec2d_t;

typedef union {
    struct { float x, y, z; };
    struct { float r, g, b; };
    float e[3];
} vec3f_t;

typedef union {
    struct { double x, y, z; };
    struct { double r, g, b; };
    double e[3];
} vec3d_t;

typedef union {
    struct { float x, y, z, w; };
    struct { float r, g, b, a; };
    float e[4];
} vec4f_t;

typedef union {
    struct { double x, y, z, w; };
    struct { double r, g, b, a; };
    double e[4];
} vec4d_t;

vec2f_t vec2f(float x, float y) {
    vec2f_t v = {{x, y}};
    return v;
}

vec2f_t vec2f_splat(float x) {
    vec2f_t v = {{x, x}};
    return v;
}

vec2d_t vec2d(double x, double y) {
    vec2d_t v = {{x, y}};
    return v;
}

vec2d_t vec2d_splat(double x) {
    vec2d_t v = {{x, x}};
    return v;
}

vec3f_t vec3f(float x, float y, float z) {
    vec3f_t v = {{x, y, z}};
    return v;
}

vec3f_t vec3f_splat(float x) {
    vec3f_t v = {{x, x, x}};
    return v;
}

vec3d_t vec3d(double x, double y, double z) {
    vec3d_t v = {{x, y, z}};
    return v;
}

vec3d_t vec3d_splat(double x) {
    vec3d_t v = {{x, x, x}};
    return v;
}

vec4f_t vec4f(float x, float y, float z, float w) {
    vec4f_t v = {{x, y, z, w}};
    return v;
}

vec4f_t vec4f_splat(float x) {
    vec4f_t v = {{x, x, x, x}};
    return v;
}

vec4d_t vec4d(double x, double y, double z, double w) {
    vec4d_t v = {{x, y, z, w}};
    return v;
}

vec4d_t vec4d_splat(double x) {
    vec4d_t v = {{x, x, x, x}};
    return v;
}

LINALG_DEF vec2f_t vec2f_add(vec2f_t a, vec2f_t b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

LINALG_DEF vec2f_t vec2f_sub(vec2f_t a, vec2f_t b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

LINALG_DEF vec2f_t vec2f_mul(vec2f_t a, vec2f_t b) {
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

LINALG_DEF vec2f_t vec2f_div(vec2f_t a, vec2f_t b) {
    a.x /= b.x;
    a.y /= b.y;
    return a;
}

LINALG_DEF vec2f_t vec2f_mod(vec2f_t a, vec2f_t b) {
    a.x = fmodf(a.x, b.x);
    a.y = fmodf(a.y, b.y);
    return a;
}

LINALG_DEF vec2f_t vec2f_min(vec2f_t a, vec2f_t b) {
    a.x = minf(a.x, b.x);
    a.y = minf(a.y, b.y);
    return a;
}

LINALG_DEF vec2f_t vec2f_max(vec2f_t a, vec2f_t b) {
    a.x = maxf(a.x, b.x);
    a.y = maxf(a.y, b.y);
    return a;
}

LINALG_DEF vec2f_t vec2f_floor(vec2f_t v) {
    v.x = floorf(v.x);
    v.y = floorf(v.y);
    return v;
}

LINALG_DEF vec2f_t vec2f_ceil(vec2f_t v) {
    v.x = ceilf(v.x);
    v.y = ceilf(v.y);
    return v;
}

LINALG_DEF vec2f_t vec2f_clamp(vec2f_t v, vec2f_t min, vec2f_t max) {
    v.x = clampf(v.x, min.x, max.x);
    v.y = clampf(v.y, min.y, max.y);
    return v;
}

LINALG_DEF vec2f_t vec2f_lerp(vec2f_t a, vec2f_t b, vec2f_t t) {
    a.x = lerpf(a.x, b.x, t.x);
    a.y = lerpf(a.y, b.y, t.y);
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

LINALG_DEF vec2d_t vec2d_add(vec2d_t a, vec2d_t b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

LINALG_DEF vec2d_t vec2d_sub(vec2d_t a, vec2d_t b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

LINALG_DEF vec2d_t vec2d_mul(vec2d_t a, vec2d_t b) {
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

LINALG_DEF vec2d_t vec2d_div(vec2d_t a, vec2d_t b) {
    a.x /= b.x;
    a.y /= b.y;
    return a;
}

LINALG_DEF vec2d_t vec2d_mod(vec2d_t a, vec2d_t b) {
    a.x = fmod(a.x, b.x);
    a.y = fmod(a.y, b.y);
    return a;
}

LINALG_DEF vec2d_t vec2d_min(vec2d_t a, vec2d_t b) {
    a.x = mind(a.x, b.x);
    a.y = mind(a.y, b.y);
    return a;
}

LINALG_DEF vec2d_t vec2d_max(vec2d_t a, vec2d_t b) {
    a.x = maxd(a.x, b.x);
    a.y = maxd(a.y, b.y);
    return a;
}

LINALG_DEF vec2d_t vec2d_floor(vec2d_t v) {
    v.x = floor(v.x);
    v.y = floor(v.y);
    return v;
}

LINALG_DEF vec2d_t vec2d_ceil(vec2d_t v) {
    v.x = ceil(v.x);
    v.y = ceil(v.y);
    return v;
}

LINALG_DEF vec2d_t vec2d_clamp(vec2d_t v, vec2d_t min, vec2d_t max) {
    v.x = clampd(v.x, min.x, max.x);
    v.y = clampd(v.y, min.y, max.y);
    return v;
}

LINALG_DEF vec2d_t vec2d_lerp(vec2d_t a, vec2d_t b, vec2d_t t) {
    a.x = lerpd(a.x, b.x, t.x);
    a.y = lerpd(a.y, b.y, t.y);
    return a;
}

LINALG_DEF vec2d_t vec2d_sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec2d_t sum = {0};
    for (size_t i = 0; i < n; ++i) {
        vec2d_t v = va_arg(args, vec2d_t);
        sum = vec2d_add(sum, v);
    }
    return sum;
}

LINALG_DEF vec3f_t vec3f_add(vec3f_t a, vec3f_t b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

LINALG_DEF vec3f_t vec3f_sub(vec3f_t a, vec3f_t b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

LINALG_DEF vec3f_t vec3f_mul(vec3f_t a, vec3f_t b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a;
}

LINALG_DEF vec3f_t vec3f_div(vec3f_t a, vec3f_t b) {
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    return a;
}

LINALG_DEF vec3f_t vec3f_mod(vec3f_t a, vec3f_t b) {
    a.x = fmodf(a.x, b.x);
    a.y = fmodf(a.y, b.y);
    a.z = fmodf(a.z, b.z);
    return a;
}

LINALG_DEF vec3f_t vec3f_min(vec3f_t a, vec3f_t b) {
    a.x = minf(a.x, b.x);
    a.y = minf(a.y, b.y);
    a.z = minf(a.z, b.z);
    return a;
}

LINALG_DEF vec3f_t vec3f_max(vec3f_t a, vec3f_t b) {
    a.x = maxf(a.x, b.x);
    a.y = maxf(a.y, b.y);
    a.z = maxf(a.z, b.z);
    return a;
}

LINALG_DEF vec3f_t vec3f_floor(vec3f_t v) {
    v.x = floorf(v.x);
    v.y = floorf(v.y);
    v.z = floorf(v.z);
    return v;
}

LINALG_DEF vec3f_t vec3f_ceil(vec3f_t v) {
    v.x = ceilf(v.x);
    v.y = ceilf(v.y);
    v.z = ceilf(v.z);
    return v;
}

LINALG_DEF vec3f_t vec3f_clamp(vec3f_t v, vec3f_t min, vec3f_t max) {
    v.x = clampf(v.x, min.x, max.x);
    v.y = clampf(v.y, min.y, max.y);
    v.z = clampf(v.z, min.z, max.z);
    return v;
}

LINALG_DEF vec3f_t vec3f_lerp(vec3f_t a, vec3f_t b, vec3f_t t) {
    a.x = lerpf(a.x, b.x, t.x);
    a.y = lerpf(a.y, b.y, t.y);
    a.z = lerpf(a.z, b.z, t.z);
    return a;
}

LINALG_DEF vec3f_t vec3f_sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec3f_t sum = {0};
    for (size_t i = 0; i < n; ++i) {
        vec3f_t v = va_arg(args, vec3f_t);
        sum = vec3f_add(sum, v);
    }
    return sum;
}

LINALG_DEF vec3d_t vec3d_add(vec3d_t a, vec3d_t b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

LINALG_DEF vec3d_t vec3d_sub(vec3d_t a, vec3d_t b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

LINALG_DEF vec3d_t vec3d_mul(vec3d_t a, vec3d_t b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a;
}

LINALG_DEF vec3d_t vec3d_div(vec3d_t a, vec3d_t b) {
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    return a;
}

LINALG_DEF vec3d_t vec3d_mod(vec3d_t a, vec3d_t b) {
    a.x = fmod(a.x, b.x);
    a.y = fmod(a.y, b.y);
    a.z = fmod(a.z, b.z);
    return a;
}

LINALG_DEF vec3d_t vec3d_min(vec3d_t a, vec3d_t b) {
    a.x = mind(a.x, b.x);
    a.y = mind(a.y, b.y);
    a.z = mind(a.z, b.z);
    return a;
}

LINALG_DEF vec3d_t vec3d_max(vec3d_t a, vec3d_t b) {
    a.x = maxd(a.x, b.x);
    a.y = maxd(a.y, b.y);
    a.z = maxd(a.z, b.z);
    return a;
}

LINALG_DEF vec3d_t vec3d_floor(vec3d_t v) {
    v.x = floor(v.x);
    v.y = floor(v.y);
    v.z = floor(v.z);
    return v;
}

LINALG_DEF vec3d_t vec3d_ceil(vec3d_t v) {
    v.x = ceil(v.x);
    v.y = ceil(v.y);
    v.z = ceil(v.z);
    return v;
}

LINALG_DEF vec3d_t vec3d_clamp(vec3d_t v, vec3d_t min, vec3d_t max) {
    v.x = clampd(v.x, min.x, max.x);
    v.y = clampd(v.y, min.y, max.y);
    v.z = clampd(v.z, min.z, max.z);
    return v;
}

LINALG_DEF vec3d_t vec3d_lerp(vec3d_t a, vec3d_t b, vec3d_t t) {
    a.x = lerpd(a.x, b.x, t.x);
    a.y = lerpd(a.y, b.y, t.y);
    a.z = lerpd(a.z, b.z, t.z);
    return a;
}

LINALG_DEF vec3d_t vec3d_sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec3d_t sum = {0};
    for (size_t i = 0; i < n; ++i) {
        vec3d_t v = va_arg(args, vec3d_t);
        sum = vec3d_add(sum, v);
    }
    return sum;
}

LINALG_DEF vec4f_t vec4f_add(vec4f_t a, vec4f_t b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

LINALG_DEF vec4f_t vec4f_sub(vec4f_t a, vec4f_t b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

LINALG_DEF vec4f_t vec4f_mul(vec4f_t a, vec4f_t b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;
    return a;
}

LINALG_DEF vec4f_t vec4f_div(vec4f_t a, vec4f_t b) {
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;
    return a;
}

LINALG_DEF vec4f_t vec4f_mod(vec4f_t a, vec4f_t b) {
    a.x = fmodf(a.x, b.x);
    a.y = fmodf(a.y, b.y);
    a.z = fmodf(a.z, b.z);
    a.w = fmodf(a.w, b.w);
    return a;
}

LINALG_DEF vec4f_t vec4f_min(vec4f_t a, vec4f_t b) {
    a.x = minf(a.x, b.x);
    a.y = minf(a.y, b.y);
    a.z = minf(a.z, b.z);
    a.w = minf(a.w, b.w);
    return a;
}

LINALG_DEF vec4f_t vec4f_max(vec4f_t a, vec4f_t b) {
    a.x = maxf(a.x, b.x);
    a.y = maxf(a.y, b.y);
    a.z = maxf(a.z, b.z);
    a.w = maxf(a.w, b.w);
    return a;
}

LINALG_DEF vec4f_t vec4f_floor(vec4f_t v) {
    v.x = floorf(v.x);
    v.y = floorf(v.y);
    v.z = floorf(v.z);
    v.w = floorf(v.w);
    return v;
}

LINALG_DEF vec4f_t vec4f_ceil(vec4f_t v) {
    v.x = ceilf(v.x);
    v.y = ceilf(v.y);
    v.z = ceilf(v.z);
    v.w = ceilf(v.w);
    return v;
}

LINALG_DEF vec4f_t vec4f_clamp(vec4f_t v, vec4f_t min, vec4f_t max) {
    v.x = clampf(v.x, min.x, max.x);
    v.y = clampf(v.y, min.y, max.y);
    v.z = clampf(v.z, min.z, max.z);
    v.w = clampf(v.w, min.w, max.w);
    return v;
}

LINALG_DEF vec4f_t vec4f_lerp(vec4f_t a, vec4f_t b, vec4f_t t) {
    a.x = lerpf(a.x, b.x, t.x);
    a.y = lerpf(a.y, b.y, t.y);
    a.z = lerpf(a.z, b.z, t.z);
    a.w = lerpf(a.w, b.w, t.w);
    return a;
}

LINALG_DEF vec4f_t vec4f_sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec4f_t sum = {0};
    for (size_t i = 0; i < n; ++i) {
        vec4f_t v = va_arg(args, vec4f_t);
        sum = vec4f_add(sum, v);
    }
    return sum;
}

LINALG_DEF vec4d_t vec4d_add(vec4d_t a, vec4d_t b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

LINALG_DEF vec4d_t vec4d_sub(vec4d_t a, vec4d_t b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

LINALG_DEF vec4d_t vec4d_mul(vec4d_t a, vec4d_t b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;
    return a;
}

LINALG_DEF vec4d_t vec4d_div(vec4d_t a, vec4d_t b) {
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;
    return a;
}

LINALG_DEF vec4d_t vec4d_mod(vec4d_t a, vec4d_t b) {
    a.x = fmod(a.x, b.x);
    a.y = fmod(a.y, b.y);
    a.z = fmod(a.z, b.z);
    a.w = fmod(a.w, b.w);
    return a;
}

LINALG_DEF vec4d_t vec4d_min(vec4d_t a, vec4d_t b) {
    a.x = mind(a.x, b.x);
    a.y = mind(a.y, b.y);
    a.z = mind(a.z, b.z);
    a.w = mind(a.w, b.w);
    return a;
}

LINALG_DEF vec4d_t vec4d_max(vec4d_t a, vec4d_t b) {
    a.x = maxd(a.x, b.x);
    a.y = maxd(a.y, b.y);
    a.z = maxd(a.z, b.z);
    a.w = maxd(a.w, b.w);
    return a;
}

LINALG_DEF vec4d_t vec4d_floor(vec4d_t v) {
    v.x = floor(v.x);
    v.y = floor(v.y);
    v.z = floor(v.z);
    v.w = floor(v.w);
    return v;
}

LINALG_DEF vec4d_t vec4d_ceil(vec4d_t v) {
    v.x = ceil(v.x);
    v.y = ceil(v.y);
    v.z = ceil(v.z);
    v.w = ceil(v.w);
    return v;
}

LINALG_DEF vec4d_t vec4d_clamp(vec4d_t v, vec4d_t min, vec4d_t max) {
    v.x = clampd(v.x, min.x, max.x);
    v.y = clampd(v.y, min.y, max.y);
    v.z = clampd(v.z, min.z, max.z);
    v.w = clampd(v.w, min.w, max.w);
    return v;
}

LINALG_DEF vec4d_t vec4d_lerp(vec4d_t a, vec4d_t b, vec4d_t t) {
    a.x = lerpd(a.x, b.x, t.x);
    a.y = lerpd(a.y, b.y, t.y);
    a.z = lerpd(a.z, b.z, t.z);
    a.w = lerpd(a.w, b.w, t.w);
    return a;
}

LINALG_DEF vec4d_t vec4d_sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec4d_t sum = {0};
    for (size_t i = 0; i < n; ++i) {
        vec4d_t v = va_arg(args, vec4d_t);
        sum = vec4d_add(sum, v);
    }
    return sum;
}

#endif // LINALG_H
