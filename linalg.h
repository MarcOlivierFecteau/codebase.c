#ifndef LINALG_H
#define LINALG_H

#include "src/maths.h"
#include <math.h>
#include <stdarg.h>

#if !defined(__STDDEF_H)
typedef unsigned long size_t;
#endif // __STDDEF_H

#ifndef LINALG_DEF
#define LINALG_DEF static inline
#endif // LINALG_DEF

typedef enum {
    AXIS_X = 0,
    AXIS_Y,
    AXIS_Z,
} rotate_axis_s;

typedef union {
    struct {
        float x, y;
    };
    struct {
        float real, imag;
    };
    float e[2];
} vec2f_t;

typedef union {
    struct {
        float _11, _12;
        float _21, _22;
    };
    float M[2][2];
    float e[2 * 2];
    vec2f_t v[2];
} mat2f_t;

typedef union {
    struct {
        double x, y;
    };
    struct {
        double real, imag;
    };
    double e[2];
} vec2d_t;

typedef union {
    struct {
        double _11, _12;
        double _21, _22;
    };
    double M[2][2];
    double e[2 * 2];
    vec2d_t v[2];
} mat2d_t;

typedef union {
    struct {
        int x, y;
    };
    int e[2];
} vec2i_t;

typedef union {
    struct {
        int _11, _12;
        int _21, _22;
    };
    int M[2][2];
    int e[2 * 2];
    vec2i_t v[2];
} mat2i_t;

typedef union {
    struct {
        unsigned int x, y;
    };
    unsigned int e[2];
} vec2u_t;

typedef union {
    struct {
        unsigned int _11, _12;
        unsigned int _21, _22;
    };
    unsigned int M[2][2];
    unsigned int e[2 * 2];
    vec2u_t v[2];
} mat2u_t;

typedef union {
    struct {
        float x, y, z;
    };
    struct {
        float r, g, b;
    };
    float e[3];
} vec3f_t;

typedef union {
    struct {
        float _11, _12, _13;
        float _21, _22, _23;
        float _31, _32, _33;
    };
    float M[3][3];
    float e[3 * 3];
    vec3f_t v[3];
} mat3f_t;

typedef union {
    struct {
        double x, y, z;
    };
    struct {
        double r, g, b;
    };
    double e[3];
} vec3d_t;

typedef union {
    struct {
        double _11, _12, _13;
        double _21, _22, _23;
        double _31, _32, _33;
    };
    double M[3][3];
    double e[3 * 3];
    vec3d_t v[3];
} mat3d_t;

typedef union {
    struct {
        int x, y, z;
    };
    struct {
        int r, g, b;
    };
    int e[3];
} vec3i_t;

typedef union {
    struct {
        int _11, _12, _13;
        int _21, _22, _23;
        int _31, _32, _33;
    };
    int M[3][3];
    int e[3 * 3];
    vec3i_t v[3];
} mat3i_t;

typedef union {
    struct {
        unsigned int x, y, z;
    };
    struct {
        unsigned int r, g, b;
    };
    unsigned int e[3];
} vec3u_t;

typedef union {
    struct {
        unsigned int _11, _12, _13;
        unsigned int _21, _22, _23;
        unsigned int _31, _32, _33;
    };
    unsigned int M[3][3];
    unsigned int e[3 * 3];
    vec3u_t v[3];
} mat3u_t;

typedef union {
    struct {
        float x, y, z, w;
    };
    struct {
        float r, g, b, a;
    };
    float e[4];
} vec4f_t;

typedef union {
    struct {
        float _11, _12, _13, _14;
        float _21, _22, _23, _24;
        float _31, _32, _33, _34;
        float _41, _42, _43, _44;
    };
    float M[4][4];
    float e[4 * 4];
    vec4f_t v[4];
} mat4f_t;

typedef union {
    struct {
        double x, y, z, w;
    };
    struct {
        double r, g, b, a;
    };
    double e[4];
} vec4d_t;

typedef union {
    struct {
        double _11, _12, _13, _14;
        double _21, _22, _23, _24;
        double _31, _32, _33, _34;
        double _41, _42, _43, _44;
    };
    double M[4][4];
    double e[4 * 4];
    vec4d_t v[4];
} mat4d_t;

typedef union {
    struct {
        int x, y, z, w;
    };
    struct {
        int r, g, b, a;
    };
    int e[4];
} vec4i_t;

typedef union {
    struct {
        int _11, _12, _13, _14;
        int _21, _22, _23, _24;
        int _31, _32, _33, _34;
        int _41, _42, _43, _44;
    };
    int M[4][4];
    int e[4 * 4];
    vec4i_t v[4];
} mat4i_t;

typedef union {
    struct {
        unsigned int x, y, z, w;
    };
    struct {
        unsigned int r, g, b, a;
    };
    unsigned int e[4];
} vec4u_t;

typedef union {
    struct {
        unsigned int _11, _12, _13, _14;
        unsigned int _21, _22, _23, _24;
        unsigned int _31, _32, _33, _34;
        unsigned int _41, _42, _43, _44;
    };
    unsigned int M[4][4];
    unsigned int e[4 * 4];
    vec4u_t v[4];
} mat4u_t;

LINALG_DEF vec2f_t vec2f(float x, float y) {
    vec2f_t v = {{x, y}};
    return v;
}

vec2f_t vec2f_splat(float x) {
    vec2f_t v = {{x, x}};
    return v;
}

LINALG_DEF mat2f_t mat2f_zero(void) {
    mat2f_t M = {0};
    return M;
}

LINALG_DEF mat2f_t mat2f_I(void) {
    mat2f_t M = {0};
    M._11 = 1;
    M._22 = 1;
    return M;
}

LINALG_DEF mat2f_t mat2f_splat(float x) {
    mat2f_t M = {0};
    M._11 = x;
    M._22 = x;
    return M;
}

LINALG_DEF mat2f_t mat2f_diag(vec2f_t diag) {
    mat2f_t M = {0};
    M._11 = diag.e[0];
    M._22 = diag.e[1];
    return M;
}

LINALG_DEF mat2f_t mat2f_R(float angle) {
    mat2f_t R;
    R._11 = cosf(angle);
    R._12 = -sinf(angle);
    R._21 = sinf(angle);
    R._22 = cosf(angle);
    return R;
}

LINALG_DEF vec2d_t vec2d(double x, double y) {
    vec2d_t v = {{x, y}};
    return v;
}

vec2d_t vec2d_splat(double x) {
    vec2d_t v = {{x, x}};
    return v;
}

LINALG_DEF mat2d_t mat2d_zero(void) {
    mat2d_t M = {0};
    return M;
}

LINALG_DEF mat2d_t mat2d_I(void) {
    mat2d_t M = {0};
    M._11 = 1;
    M._22 = 1;
    return M;
}

LINALG_DEF mat2d_t mat2d_splat(double x) {
    mat2d_t M = {0};
    M._11 = x;
    M._22 = x;
    return M;
}

LINALG_DEF mat2d_t mat2d_diag(vec2d_t diag) {
    mat2d_t M = {0};
    M._11 = diag.e[0];
    M._22 = diag.e[1];
    return M;
}

LINALG_DEF mat2d_t mat2d_R(double angle) {
    mat2d_t R;
    R._11 = cos(angle);
    R._12 = -sin(angle);
    R._21 = sin(angle);
    R._22 = cos(angle);
    return R;
}

LINALG_DEF vec2i_t vec2i(int x, int y) {
    vec2i_t v = {{x, y}};
    return v;
}

vec2i_t vec2i_splat(int x) {
    vec2i_t v = {{x, x}};
    return v;
}

LINALG_DEF mat2i_t mat2i_zero(void) {
    mat2i_t M = {0};
    return M;
}

LINALG_DEF mat2i_t mat2i_I(void) {
    mat2i_t M = {0};
    M._11 = 1;
    M._22 = 1;
    return M;
}

LINALG_DEF mat2i_t mat2i_splat(int x) {
    mat2i_t M = {0};
    M._11 = x;
    M._22 = x;
    return M;
}

LINALG_DEF mat2i_t mat2i_diag(vec2i_t diag) {
    mat2i_t M = {0};
    M._11 = diag.e[0];
    M._22 = diag.e[1];
    return M;
}

LINALG_DEF vec2u_t vec2u(unsigned int x, unsigned int y) {
    vec2u_t v = {{x, y}};
    return v;
}

vec2u_t vec2u_splat(unsigned int x) {
    vec2u_t v = {{x, x}};
    return v;
}

LINALG_DEF mat2u_t mat2u_zero(void) {
    mat2u_t M = {0};
    return M;
}

LINALG_DEF mat2u_t mat2u_I(void) {
    mat2u_t M = {0};
    M._11 = 1;
    M._22 = 1;
    return M;
}

LINALG_DEF mat2u_t mat2u_splat(unsigned int x) {
    mat2u_t M = {0};
    M._11 = x;
    M._22 = x;
    return M;
}

LINALG_DEF mat2u_t mat2u_diag(vec2u_t diag) {
    mat2u_t M = {0};
    M._11 = diag.e[0];
    M._22 = diag.e[1];
    return M;
}

LINALG_DEF vec3f_t vec3f(float x, float y, float z) {
    vec3f_t v = {{x, y, z}};
    return v;
}

vec3f_t vec3f_splat(float x) {
    vec3f_t v = {{x, x, x}};
    return v;
}

LINALG_DEF mat3f_t mat3f_zero(void) {
    mat3f_t M = {0};
    return M;
}

LINALG_DEF mat3f_t mat3f_I(void) {
    mat3f_t M = {0};
    M._11 = 1;
    M._22 = 1;
    M._33 = 1;
    return M;
}

LINALG_DEF mat3f_t mat3f_splat(float x) {
    mat3f_t M = {0};
    M._11 = x;
    M._22 = x;
    M._33 = x;
    return M;
}

LINALG_DEF mat3f_t mat3f_diag(vec3f_t diag) {
    mat3f_t M = {0};
    M._11 = diag.e[0];
    M._22 = diag.e[1];
    M._33 = diag.e[2];
    return M;
}

LINALG_DEF mat3f_t mat3f_R(rotate_axis_s axis, float angle) {
    mat3f_t R = {0};
    size_t i = (axis + 1) % 3;
    size_t j = (axis + 2) % 3;
    R.M[i][i] = cosf(angle);
    R.M[i][j] = -sinf(angle);
    R.M[j][i] = sinf(angle);
    R.M[j][j] = cosf(angle);
    return R;
}

LINALG_DEF vec3d_t vec3d(double x, double y, double z) {
    vec3d_t v = {{x, y, z}};
    return v;
}

vec3d_t vec3d_splat(double x) {
    vec3d_t v = {{x, x, x}};
    return v;
}

LINALG_DEF mat3d_t mat3d_zero(void) {
    mat3d_t M = {0};
    return M;
}

LINALG_DEF mat3d_t mat3d_I(void) {
    mat3d_t M = {0};
    M._11 = 1;
    M._22 = 1;
    M._33 = 1;
    return M;
}

LINALG_DEF mat3d_t mat3d_splat(double x) {
    mat3d_t M = {0};
    M._11 = x;
    M._22 = x;
    M._33 = x;
    return M;
}

LINALG_DEF mat3d_t mat3d_diag(vec3d_t diag) {
    mat3d_t M = {0};
    M._11 = diag.e[0];
    M._22 = diag.e[1];
    M._33 = diag.e[2];
    return M;
}

LINALG_DEF mat3d_t mat3d_R(rotate_axis_s axis, double angle) {
    mat3d_t R = {0};
    size_t i = (axis + 1) % 3;
    size_t j = (axis + 2) % 3;
    R.M[i][i] = cos(angle);
    R.M[i][j] = -sin(angle);
    R.M[j][i] = sin(angle);
    R.M[j][j] = cos(angle);
    return R;
}

LINALG_DEF vec3i_t vec3i(int x, int y, int z) {
    vec3i_t v = {{x, y, z}};
    return v;
}

vec3i_t vec3i_splat(int x) {
    vec3i_t v = {{x, x, x}};
    return v;
}

LINALG_DEF mat3i_t mat3i_zero(void) {
    mat3i_t M = {0};
    return M;
}

LINALG_DEF mat3i_t mat3i_I(void) {
    mat3i_t M = {0};
    M._11 = 1;
    M._22 = 1;
    M._33 = 1;
    return M;
}

LINALG_DEF mat3i_t mat3i_splat(int x) {
    mat3i_t M = {0};
    M._11 = x;
    M._22 = x;
    M._33 = x;
    return M;
}

LINALG_DEF mat3i_t mat3i_diag(vec3i_t diag) {
    mat3i_t M = {0};
    M._11 = diag.e[0];
    M._22 = diag.e[1];
    M._33 = diag.e[2];
    return M;
}

LINALG_DEF vec3u_t vec3u(unsigned int x, unsigned int y, unsigned int z) {
    vec3u_t v = {{x, y, z}};
    return v;
}

vec3u_t vec3u_splat(unsigned int x) {
    vec3u_t v = {{x, x, x}};
    return v;
}

LINALG_DEF mat3u_t mat3u_zero(void) {
    mat3u_t M = {0};
    return M;
}

LINALG_DEF mat3u_t mat3u_I(void) {
    mat3u_t M = {0};
    M._11 = 1;
    M._22 = 1;
    M._33 = 1;
    return M;
}

LINALG_DEF mat3u_t mat3u_splat(unsigned int x) {
    mat3u_t M = {0};
    M._11 = x;
    M._22 = x;
    M._33 = x;
    return M;
}

LINALG_DEF mat3u_t mat3u_diag(vec3u_t diag) {
    mat3u_t M = {0};
    M._11 = diag.e[0];
    M._22 = diag.e[1];
    M._33 = diag.e[2];
    return M;
}

LINALG_DEF vec4f_t vec4f(float x, float y, float z, float w) {
    vec4f_t v = {{x, y, z, w}};
    return v;
}

vec4f_t vec4f_splat(float x) {
    vec4f_t v = {{x, x, x, x}};
    return v;
}

LINALG_DEF mat4f_t mat4f_zero(void) {
    mat4f_t M = {0};
    return M;
}

LINALG_DEF mat4f_t mat4f_I(void) {
    mat4f_t M = {0};
    M._11 = 1;
    M._22 = 1;
    M._33 = 1;
    M._44 = 1;
    return M;
}

LINALG_DEF mat4f_t mat4f_splat(float x) {
    mat4f_t M = {0};
    M._11 = x;
    M._22 = x;
    M._33 = x;
    M._44 = x;
    return M;
}

LINALG_DEF mat4f_t mat4f_diag(vec4f_t diag) {
    mat4f_t M = {0};
    M._11 = diag.e[0];
    M._22 = diag.e[1];
    M._33 = diag.e[2];
    M._44 = diag.e[3];
    return M;
}

LINALG_DEF mat4f_t mat4f_R(rotate_axis_s axis, float angle) {
    mat4f_t R = {0};
    size_t i = (axis + 1) % 3;
    size_t j = (axis + 2) % 3;
    R.M[i][i] = cosf(angle);
    R.M[i][j] = -sinf(angle);
    R.M[j][i] = sinf(angle);
    R.M[j][j] = cosf(angle);
    return R;
}

LINALG_DEF mat4f_t mat4f_T(rotate_axis_s axis, float angle) {
    mat4f_t T = {0};
    size_t i = (axis + 1) % 3;
    size_t j = (axis + 2) % 3;
    T.M[i][i] = cosf(angle);
    T.M[i][j] = -sinf(angle);
    T.M[j][i] = sinf(angle);
    T.M[j][j] = cosf(angle);
    T.M[3][3] = 1;
    return T;
}

LINALG_DEF vec4d_t vec4d(double x, double y, double z, double w) {
    vec4d_t v = {{x, y, z, w}};
    return v;
}

vec4d_t vec4d_splat(double x) {
    vec4d_t v = {{x, x, x, x}};
    return v;
}

LINALG_DEF mat4d_t mat4d_zero(void) {
    mat4d_t M = {0};
    return M;
}

LINALG_DEF mat4d_t mat4d_I(void) {
    mat4d_t M = {0};
    M._11 = 1;
    M._22 = 1;
    M._33 = 1;
    M._44 = 1;
    return M;
}

LINALG_DEF mat4d_t mat4d_splat(double x) {
    mat4d_t M = {0};
    M._11 = x;
    M._22 = x;
    M._33 = x;
    M._44 = x;
    return M;
}

LINALG_DEF mat4d_t mat4d_diag(vec4d_t diag) {
    mat4d_t M = {0};
    M._11 = diag.e[0];
    M._22 = diag.e[1];
    M._33 = diag.e[2];
    M._44 = diag.e[3];
    return M;
}

LINALG_DEF mat4d_t mat4d_R(rotate_axis_s axis, double angle) {
    mat4d_t R = {0};
    size_t i = (axis + 1) % 3;
    size_t j = (axis + 2) % 3;
    R.M[i][i] = cos(angle);
    R.M[i][j] = -sin(angle);
    R.M[j][i] = sin(angle);
    R.M[j][j] = cos(angle);
    return R;
}

LINALG_DEF mat4d_t mat4d_T(rotate_axis_s axis, double angle) {
    mat4d_t T = {0};
    size_t i = (axis + 1) % 3;
    size_t j = (axis + 2) % 3;
    T.M[i][i] = cos(angle);
    T.M[i][j] = -sin(angle);
    T.M[j][i] = sin(angle);
    T.M[j][j] = cos(angle);
    T.M[3][3] = 1;
    return T;
}

LINALG_DEF vec4i_t vec4i(int x, int y, int z, int w) {
    vec4i_t v = {{x, y, z, w}};
    return v;
}

vec4i_t vec4i_splat(int x) {
    vec4i_t v = {{x, x, x, x}};
    return v;
}

LINALG_DEF mat4i_t mat4i_zero(void) {
    mat4i_t M = {0};
    return M;
}

LINALG_DEF mat4i_t mat4i_I(void) {
    mat4i_t M = {0};
    M._11 = 1;
    M._22 = 1;
    M._33 = 1;
    M._44 = 1;
    return M;
}

LINALG_DEF mat4i_t mat4i_splat(int x) {
    mat4i_t M = {0};
    M._11 = x;
    M._22 = x;
    M._33 = x;
    M._44 = x;
    return M;
}

LINALG_DEF mat4i_t mat4i_diag(vec4i_t diag) {
    mat4i_t M = {0};
    M._11 = diag.e[0];
    M._22 = diag.e[1];
    M._33 = diag.e[2];
    M._44 = diag.e[3];
    return M;
}

LINALG_DEF vec4u_t vec4u(unsigned int x, unsigned int y, unsigned int z,
                         unsigned int w) {
    vec4u_t v = {{x, y, z, w}};
    return v;
}

vec4u_t vec4u_splat(unsigned int x) {
    vec4u_t v = {{x, x, x, x}};
    return v;
}

LINALG_DEF mat4u_t mat4u_zero(void) {
    mat4u_t M = {0};
    return M;
}

LINALG_DEF mat4u_t mat4u_I(void) {
    mat4u_t M = {0};
    M._11 = 1;
    M._22 = 1;
    M._33 = 1;
    M._44 = 1;
    return M;
}

LINALG_DEF mat4u_t mat4u_splat(unsigned int x) {
    mat4u_t M = {0};
    M._11 = x;
    M._22 = x;
    M._33 = x;
    M._44 = x;
    return M;
}

LINALG_DEF mat4u_t mat4u_diag(vec4u_t diag) {
    mat4u_t M = {0};
    M._11 = diag.e[0];
    M._22 = diag.e[1];
    M._33 = diag.e[2];
    M._44 = diag.e[3];
    return M;
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

LINALG_DEF vec2f_t vec2f_abs(vec2f_t v) {
    v.x = fabsf(v.x);
    v.y = fabsf(v.y);
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

LINALG_DEF vec2f_t vec2f_product(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec2f_t product = vec2f_splat(1);
    for (size_t i = 0; i < n; ++i) {
        vec2f_t v = va_arg(args, vec2f_t);
        product = vec2f_mul(product, v);
    }
    return product;
}

LINALG_DEF float vec2f_dot(vec2f_t a, vec2f_t b) {
    return a.x * b.x + a.y * b.y;
}

LINALG_DEF float vec2f_cross(vec2f_t a, vec2f_t b) {
    return a.x * b.y - a.y * b.x;
}

LINALG_DEF float vec2f_sqrlen(vec2f_t v) { return vec2f_dot(v, v); }

LINALG_DEF float vec2f_1norm(vec2f_t v) {
    v = vec2f_abs(v);
    float norm = 0;
    norm += v.x;
    norm += v.y;
    return norm;
}

LINALG_DEF float vec2f_2norm(vec2f_t v) { return sqrtf(vec2f_sqrlen(v)); }

LINALG_DEF vec2f_t vec2f_unit(vec2f_t v) {
    return vec2f_div(v, vec2f_splat(vec2f_2norm(v)));
}

LINALG_DEF vec2f_t vec2f_norm(vec2f_t v) { return vec2f_unit(v); }

LINALG_DEF _Bool vec2f_eq(vec2f_t a, vec2f_t b, float epsilon) {
    if (fabsf(b.x - a.x) > epsilon) {
        return 0;
    }
    if (fabsf(b.y - a.y) > epsilon) {
        return 0;
    }
    return 1;
}

LINALG_DEF vec2f_t vec2f_reflect(vec2f_t v, vec2f_t n) {
    vec2f_t result = n;
    result = vec2f_mul(result, vec2f_splat(vec2f_dot(v, n)));
    result = vec2f_mul(result, vec2f_splat(2));
    result = vec2f_sub(v, result);
    return result;
}

LINALG_DEF vec2f_t vec2f_direction(vec2f_t a, vec2f_t b) {
    vec2f_t delta = vec2f_sub(b, a);
    return vec2f_unit(delta);
}

LINALG_DEF float vec2f_angle_between(vec2f_t a, vec2f_t b) {
    vec2f_t a_unit = vec2f_unit(a);
    vec2f_t b_unit = vec2f_unit(b);
    return acosf(vec2f_dot(a_unit, b_unit));
}

LINALG_DEF mat2f_t mat2f_mul(mat2f_t A, mat2f_t B) {
    mat2f_t result;
    result._11 = A._11 * B._11 + A._12 * B._21;
    result._12 = A._11 * B._12 + A._12 * B._22;
    result._21 = A._21 * B._11 + A._22 * B._21;
    result._22 = A._21 * B._12 + A._22 * B._22;
    return result;
}

LINALG_DEF mat2f_t mat2f_nmul(size_t n, ...) {
    va_list args;
    va_start(args, n);
    mat2f_t product = mat2f_I();
    for (size_t i = 0; i < n; ++i) {
        mat2f_t A = va_arg(args, mat2f_t);
        product = mat2f_mul(product, A);
    }
    return product;
}

LINALG_DEF vec2f_t mat2f_mul_vec(mat2f_t M, vec2f_t v) {
    vec2f_t result;
    result.x = vec2f_dot(M.v[0], v);
    result.y = vec2f_dot(M.v[1], v);
    return result;
}

LINALG_DEF mat2f_t mat2f_hadamard(mat2f_t A, mat2f_t B) {
    A.e[0] *= B.e[0];
    A.e[1] *= B.e[1];
    return A;
}

LINALG_DEF mat2f_t mat2f_rotate(mat2f_t A, float angle) {
    A._11 *= cosf(angle);
    A._12 *= -sinf(angle);
    A._21 *= sinf(angle);
    A._22 *= cosf(angle);
    return A;
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

LINALG_DEF vec2d_t vec2d_abs(vec2d_t v) {
    v.x = fabs(v.x);
    v.y = fabs(v.y);
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

LINALG_DEF vec2d_t vec2d_product(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec2d_t product = vec2d_splat(1);
    for (size_t i = 0; i < n; ++i) {
        vec2d_t v = va_arg(args, vec2d_t);
        product = vec2d_mul(product, v);
    }
    return product;
}

LINALG_DEF double vec2d_dot(vec2d_t a, vec2d_t b) {
    return a.x * b.x + a.y * b.y;
}

LINALG_DEF double vec2d_cross(vec2d_t a, vec2d_t b) {
    return a.x * b.y - a.y * b.x;
}

LINALG_DEF double vec2d_sqrlen(vec2d_t v) { return vec2d_dot(v, v); }

LINALG_DEF double vec2d_1norm(vec2d_t v) {
    v = vec2d_abs(v);
    double norm = 0;
    norm += v.x;
    norm += v.y;
    return norm;
}

LINALG_DEF double vec2d_2norm(vec2d_t v) { return sqrt(vec2d_sqrlen(v)); }

LINALG_DEF vec2d_t vec2d_unit(vec2d_t v) {
    return vec2d_div(v, vec2d_splat(vec2d_2norm(v)));
}

LINALG_DEF vec2d_t vec2d_norm(vec2d_t v) { return vec2d_unit(v); }

LINALG_DEF _Bool vec2d_eq(vec2d_t a, vec2d_t b, double epsilon) {
    if (fabs(b.x - a.x) > epsilon) {
        return 0;
    }
    if (fabs(b.y - a.y) > epsilon) {
        return 0;
    }
    return 1;
}

LINALG_DEF vec2d_t vec2d_reflect(vec2d_t v, vec2d_t n) {
    vec2d_t result = n;
    result = vec2d_mul(result, vec2d_splat(vec2d_dot(v, n)));
    result = vec2d_mul(result, vec2d_splat(2));
    result = vec2d_sub(v, result);
    return result;
}

LINALG_DEF vec2d_t vec2d_direction(vec2d_t a, vec2d_t b) {
    vec2d_t delta = vec2d_sub(b, a);
    return vec2d_unit(delta);
}

LINALG_DEF double vec2d_angle_between(vec2d_t a, vec2d_t b) {
    vec2d_t a_unit = vec2d_unit(a);
    vec2d_t b_unit = vec2d_unit(b);
    return acos(vec2d_dot(a_unit, b_unit));
}

LINALG_DEF mat2d_t mat2d_mul(mat2d_t A, mat2d_t B) {
    mat2d_t result;
    result._11 = A._11 * B._11 + A._12 * B._21;
    result._12 = A._11 * B._12 + A._12 * B._22;
    result._21 = A._21 * B._11 + A._22 * B._21;
    result._22 = A._21 * B._12 + A._22 * B._22;
    return result;
}

LINALG_DEF mat2d_t mat2d_nmul(size_t n, ...) {
    va_list args;
    va_start(args, n);
    mat2d_t product = mat2d_I();
    for (size_t i = 0; i < n; ++i) {
        mat2d_t A = va_arg(args, mat2d_t);
        product = mat2d_mul(product, A);
    }
    return product;
}

LINALG_DEF vec2d_t mat2d_mul_vec(mat2d_t M, vec2d_t v) {
    vec2d_t result;
    result.x = vec2d_dot(M.v[0], v);
    result.y = vec2d_dot(M.v[1], v);
    return result;
}

LINALG_DEF mat2d_t mat2d_hadamard(mat2d_t A, mat2d_t B) {
    A.e[0] *= B.e[0];
    A.e[1] *= B.e[1];
    return A;
}

LINALG_DEF mat2d_t mat2d_rotate(mat2d_t A, double angle) {
    A._11 *= cos(angle);
    A._12 *= -sin(angle);
    A._21 *= sin(angle);
    A._22 *= cos(angle);
    return A;
}

LINALG_DEF vec2i_t vec2i_add(vec2i_t a, vec2i_t b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

LINALG_DEF vec2i_t vec2i_sub(vec2i_t a, vec2i_t b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

LINALG_DEF vec2i_t vec2i_mul(vec2i_t a, vec2i_t b) {
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

LINALG_DEF vec2i_t vec2i_div(vec2i_t a, vec2i_t b) {
    a.x /= b.x;
    a.y /= b.y;
    return a;
}

LINALG_DEF vec2i_t vec2i_mod(vec2i_t a, vec2i_t b) {
    a.x %= b.x;
    a.y %= b.y;
    return a;
}

LINALG_DEF vec2i_t vec2i_min(vec2i_t a, vec2i_t b) {
    a.x = mini(a.x, b.x);
    a.y = mini(a.y, b.y);
    return a;
}

LINALG_DEF vec2i_t vec2i_max(vec2i_t a, vec2i_t b) {
    a.x = maxi(a.x, b.x);
    a.y = maxi(a.y, b.y);
    return a;
}

LINALG_DEF vec2i_t vec2i_clamp(vec2i_t v, vec2i_t min, vec2i_t max) {
    v.x = clampi(v.x, min.x, max.x);
    v.y = clampi(v.y, min.y, max.y);
    return v;
}

LINALG_DEF vec2i_t vec2i_abs(vec2i_t v) {
    v.x = absi(v.x);
    v.y = absi(v.y);
    return v;
}

LINALG_DEF vec2i_t vec2i_sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec2i_t sum = {0};
    for (size_t i = 0; i < n; ++i) {
        vec2i_t v = va_arg(args, vec2i_t);
        sum = vec2i_add(sum, v);
    }
    return sum;
}

LINALG_DEF vec2i_t vec2i_product(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec2i_t product = vec2i_splat(1);
    for (size_t i = 0; i < n; ++i) {
        vec2i_t v = va_arg(args, vec2i_t);
        product = vec2i_mul(product, v);
    }
    return product;
}

LINALG_DEF int vec2i_dot(vec2i_t a, vec2i_t b) { return a.x * b.x + a.y * b.y; }

LINALG_DEF int vec2i_cross(vec2i_t a, vec2i_t b) {
    return a.x * b.y - a.y * b.x;
}

LINALG_DEF int vec2i_sqrlen(vec2i_t v) { return vec2i_dot(v, v); }

LINALG_DEF int vec2i_1norm(vec2i_t v) {
    v = vec2i_abs(v);
    int norm = 0;
    norm += v.x;
    norm += v.y;
    return norm;
}

LINALG_DEF vec2i_t vec2i_reflect(vec2i_t v, vec2i_t n) {
    vec2i_t result = n;
    result = vec2i_mul(result, vec2i_splat(vec2i_dot(v, n)));
    result = vec2i_mul(result, vec2i_splat(2));
    result = vec2i_sub(v, result);
    return result;
}

LINALG_DEF mat2i_t mat2i_mul(mat2i_t A, mat2i_t B) {
    mat2i_t result;
    result._11 = A._11 * B._11 + A._12 * B._21;
    result._12 = A._11 * B._12 + A._12 * B._22;
    result._21 = A._21 * B._11 + A._22 * B._21;
    result._22 = A._21 * B._12 + A._22 * B._22;
    return result;
}

LINALG_DEF mat2i_t mat2i_nmul(size_t n, ...) {
    va_list args;
    va_start(args, n);
    mat2i_t product = mat2i_I();
    for (size_t i = 0; i < n; ++i) {
        mat2i_t A = va_arg(args, mat2i_t);
        product = mat2i_mul(product, A);
    }
    return product;
}

LINALG_DEF vec2i_t mat2i_mul_vec(mat2i_t M, vec2i_t v) {
    vec2i_t result;
    result.x = vec2i_dot(M.v[0], v);
    result.y = vec2i_dot(M.v[1], v);
    return result;
}

LINALG_DEF mat2i_t mat2i_hadamard(mat2i_t A, mat2i_t B) {
    A.e[0] *= B.e[0];
    A.e[1] *= B.e[1];
    return A;
}

LINALG_DEF vec2u_t vec2u_add(vec2u_t a, vec2u_t b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

LINALG_DEF vec2u_t vec2u_sub(vec2u_t a, vec2u_t b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

LINALG_DEF vec2u_t vec2u_mul(vec2u_t a, vec2u_t b) {
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

LINALG_DEF vec2u_t vec2u_div(vec2u_t a, vec2u_t b) {
    a.x /= b.x;
    a.y /= b.y;
    return a;
}

LINALG_DEF vec2u_t vec2u_mod(vec2u_t a, vec2u_t b) {
    a.x %= b.x;
    a.y %= b.y;
    return a;
}

LINALG_DEF vec2u_t vec2u_min(vec2u_t a, vec2u_t b) {
    a.x = minu(a.x, b.x);
    a.y = minu(a.y, b.y);
    return a;
}

LINALG_DEF vec2u_t vec2u_max(vec2u_t a, vec2u_t b) {
    a.x = maxu(a.x, b.x);
    a.y = maxu(a.y, b.y);
    return a;
}

LINALG_DEF vec2u_t vec2u_clamp(vec2u_t v, vec2u_t min, vec2u_t max) {
    v.x = clampu(v.x, min.x, max.x);
    v.y = clampu(v.y, min.y, max.y);
    return v;
}

LINALG_DEF vec2u_t vec2u_sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec2u_t sum = {0};
    for (size_t i = 0; i < n; ++i) {
        vec2u_t v = va_arg(args, vec2u_t);
        sum = vec2u_add(sum, v);
    }
    return sum;
}

LINALG_DEF vec2u_t vec2u_product(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec2u_t product = vec2u_splat(1);
    for (size_t i = 0; i < n; ++i) {
        vec2u_t v = va_arg(args, vec2u_t);
        product = vec2u_mul(product, v);
    }
    return product;
}

LINALG_DEF unsigned int vec2u_dot(vec2u_t a, vec2u_t b) {
    return a.x * b.x + a.y * b.y;
}

LINALG_DEF unsigned int vec2u_cross(vec2u_t a, vec2u_t b) {
    return a.x * b.y - a.y * b.x;
}

LINALG_DEF unsigned int vec2u_sqrlen(vec2u_t v) { return vec2u_dot(v, v); }

LINALG_DEF unsigned int vec2u_1norm(vec2u_t v) {
    unsigned int norm = 0;
    norm += v.x;
    norm += v.y;
    return norm;
}

LINALG_DEF vec2u_t vec2u_reflect(vec2u_t v, vec2u_t n) {
    vec2u_t result = n;
    result = vec2u_mul(result, vec2u_splat(vec2u_dot(v, n)));
    result = vec2u_mul(result, vec2u_splat(2));
    result = vec2u_sub(v, result);
    return result;
}

LINALG_DEF mat2u_t mat2u_mul(mat2u_t A, mat2u_t B) {
    mat2u_t result;
    result._11 = A._11 * B._11 + A._12 * B._21;
    result._12 = A._11 * B._12 + A._12 * B._22;
    result._21 = A._21 * B._11 + A._22 * B._21;
    result._22 = A._21 * B._12 + A._22 * B._22;
    return result;
}

LINALG_DEF mat2u_t mat2u_nmul(size_t n, ...) {
    va_list args;
    va_start(args, n);
    mat2u_t product = mat2u_I();
    for (size_t i = 0; i < n; ++i) {
        mat2u_t A = va_arg(args, mat2u_t);
        product = mat2u_mul(product, A);
    }
    return product;
}

LINALG_DEF vec2u_t mat2u_mul_vec(mat2u_t M, vec2u_t v) {
    vec2u_t result;
    result.x = vec2u_dot(M.v[0], v);
    result.y = vec2u_dot(M.v[1], v);
    return result;
}

LINALG_DEF mat2u_t mat2u_hadamard(mat2u_t A, mat2u_t B) {
    A.e[0] *= B.e[0];
    A.e[1] *= B.e[1];
    return A;
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

LINALG_DEF vec3f_t vec3f_abs(vec3f_t v) {
    v.x = fabsf(v.x);
    v.y = fabsf(v.y);
    v.z = fabsf(v.z);
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

LINALG_DEF vec3f_t vec3f_product(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec3f_t product = vec3f_splat(1);
    for (size_t i = 0; i < n; ++i) {
        vec3f_t v = va_arg(args, vec3f_t);
        product = vec3f_mul(product, v);
    }
    return product;
}

LINALG_DEF float vec3f_dot(vec3f_t a, vec3f_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

LINALG_DEF vec3f_t vec3f_cross(vec3f_t a, vec3f_t b) {
    vec3f_t result = {0};
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.z * b.x;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

LINALG_DEF float vec3f_sqrlen(vec3f_t v) { return vec3f_dot(v, v); }

LINALG_DEF float vec3f_1norm(vec3f_t v) {
    v = vec3f_abs(v);
    float norm = 0;
    norm += v.x;
    norm += v.y;
    norm += v.z;
    return norm;
}

LINALG_DEF float vec3f_2norm(vec3f_t v) { return sqrtf(vec3f_sqrlen(v)); }

LINALG_DEF vec3f_t vec3f_unit(vec3f_t v) {
    return vec3f_div(v, vec3f_splat(vec3f_2norm(v)));
}

LINALG_DEF vec3f_t vec3f_norm(vec3f_t v) { return vec3f_unit(v); }

LINALG_DEF _Bool vec3f_eq(vec3f_t a, vec3f_t b, float epsilon) {
    if (fabsf(b.x - a.x) > epsilon) {
        return 0;
    }
    if (fabsf(b.y - a.y) > epsilon) {
        return 0;
    }
    if (fabsf(b.z - a.z) > epsilon) {
        return 0;
    }
    return 1;
}

LINALG_DEF vec3f_t vec3f_reflect(vec3f_t v, vec3f_t n) {
    vec3f_t result = n;
    result = vec3f_mul(result, vec3f_splat(vec3f_dot(v, n)));
    result = vec3f_mul(result, vec3f_splat(2));
    result = vec3f_sub(v, result);
    return result;
}

LINALG_DEF vec3f_t vec3f_direction(vec3f_t a, vec3f_t b) {
    vec3f_t delta = vec3f_sub(b, a);
    return vec3f_unit(delta);
}

LINALG_DEF float vec3f_angle_between(vec3f_t a, vec3f_t b) {
    vec3f_t a_unit = vec3f_unit(a);
    vec3f_t b_unit = vec3f_unit(b);
    return acosf(vec3f_dot(a_unit, b_unit));
}

LINALG_DEF mat3f_t mat3f_mul(mat3f_t A, mat3f_t B) {
    mat3f_t result;
    result._11 = A._11 * B._11 + A._12 * B._21 + A._13 * B._31;
    result._12 = A._11 * B._12 + A._12 * B._22 + A._13 * B._32;
    result._13 = A._11 * B._13 + A._12 * B._23 + A._13 * B._33;
    result._21 = A._21 * B._11 + A._22 * B._21 + A._23 * B._31;
    result._22 = A._21 * B._12 + A._22 * B._22 + A._23 * B._32;
    result._23 = A._21 * B._13 + A._22 * B._23 + A._23 * B._33;
    result._31 = A._31 * B._11 + A._32 * B._21 + A._33 * B._31;
    result._32 = A._31 * B._12 + A._32 * B._22 + A._33 * B._32;
    result._33 = A._31 * B._13 + A._32 * B._23 + A._33 * B._33;
    return result;
}

LINALG_DEF mat3f_t mat3f_nmul(size_t n, ...) {
    va_list args;
    va_start(args, n);
    mat3f_t product = mat3f_I();
    for (size_t i = 0; i < n; ++i) {
        mat3f_t A = va_arg(args, mat3f_t);
        product = mat3f_mul(product, A);
    }
    return product;
}

LINALG_DEF vec3f_t mat3f_mul_vec(mat3f_t M, vec3f_t v) {
    vec3f_t result;
    result.x = vec3f_dot(M.v[0], v);
    result.y = vec3f_dot(M.v[1], v);
    result.z = vec3f_dot(M.v[2], v);
    return result;
}

LINALG_DEF mat3f_t mat3f_hadamard(mat3f_t A, mat3f_t B) {
    A.e[0] *= B.e[0];
    A.e[1] *= B.e[1];
    A.e[2] *= B.e[2];
    return A;
}

LINALG_DEF mat3f_t mat3f_rotate(mat3f_t A, rotate_axis_s axis, float angle) {
    size_t i = (axis + 1) % 3;
    size_t j = (axis + 2) % 3;
    A.M[i][i] *= cosf(angle);
    A.M[i][j] *= -sinf(angle);
    A.M[j][i] *= sinf(angle);
    A.M[j][j] *= cosf(angle);
    return A;
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

LINALG_DEF vec3d_t vec3d_abs(vec3d_t v) {
    v.x = fabs(v.x);
    v.y = fabs(v.y);
    v.z = fabs(v.z);
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

LINALG_DEF vec3d_t vec3d_product(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec3d_t product = vec3d_splat(1);
    for (size_t i = 0; i < n; ++i) {
        vec3d_t v = va_arg(args, vec3d_t);
        product = vec3d_mul(product, v);
    }
    return product;
}

LINALG_DEF double vec3d_dot(vec3d_t a, vec3d_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

LINALG_DEF vec3d_t vec3d_cross(vec3d_t a, vec3d_t b) {
    vec3d_t result = {0};
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.z * b.x;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

LINALG_DEF double vec3d_sqrlen(vec3d_t v) { return vec3d_dot(v, v); }

LINALG_DEF double vec3d_1norm(vec3d_t v) {
    v = vec3d_abs(v);
    double norm = 0;
    norm += v.x;
    norm += v.y;
    norm += v.z;
    return norm;
}

LINALG_DEF double vec3d_2norm(vec3d_t v) { return sqrt(vec3d_sqrlen(v)); }

LINALG_DEF vec3d_t vec3d_unit(vec3d_t v) {
    return vec3d_div(v, vec3d_splat(vec3d_2norm(v)));
}

LINALG_DEF vec3d_t vec3d_norm(vec3d_t v) { return vec3d_unit(v); }

LINALG_DEF _Bool vec3d_eq(vec3d_t a, vec3d_t b, double epsilon) {
    if (fabs(b.x - a.x) > epsilon) {
        return 0;
    }
    if (fabs(b.y - a.y) > epsilon) {
        return 0;
    }
    if (fabs(b.z - a.z) > epsilon) {
        return 0;
    }
    return 1;
}

LINALG_DEF vec3d_t vec3d_reflect(vec3d_t v, vec3d_t n) {
    vec3d_t result = n;
    result = vec3d_mul(result, vec3d_splat(vec3d_dot(v, n)));
    result = vec3d_mul(result, vec3d_splat(2));
    result = vec3d_sub(v, result);
    return result;
}

LINALG_DEF vec3d_t vec3d_direction(vec3d_t a, vec3d_t b) {
    vec3d_t delta = vec3d_sub(b, a);
    return vec3d_unit(delta);
}

LINALG_DEF double vec3d_angle_between(vec3d_t a, vec3d_t b) {
    vec3d_t a_unit = vec3d_unit(a);
    vec3d_t b_unit = vec3d_unit(b);
    return acos(vec3d_dot(a_unit, b_unit));
}

LINALG_DEF mat3d_t mat3d_mul(mat3d_t A, mat3d_t B) {
    mat3d_t result;
    result._11 = A._11 * B._11 + A._12 * B._21 + A._13 * B._31;
    result._12 = A._11 * B._12 + A._12 * B._22 + A._13 * B._32;
    result._13 = A._11 * B._13 + A._12 * B._23 + A._13 * B._33;
    result._21 = A._21 * B._11 + A._22 * B._21 + A._23 * B._31;
    result._22 = A._21 * B._12 + A._22 * B._22 + A._23 * B._32;
    result._23 = A._21 * B._13 + A._22 * B._23 + A._23 * B._33;
    result._31 = A._31 * B._11 + A._32 * B._21 + A._33 * B._31;
    result._32 = A._31 * B._12 + A._32 * B._22 + A._33 * B._32;
    result._33 = A._31 * B._13 + A._32 * B._23 + A._33 * B._33;
    return result;
}

LINALG_DEF mat3d_t mat3d_nmul(size_t n, ...) {
    va_list args;
    va_start(args, n);
    mat3d_t product = mat3d_I();
    for (size_t i = 0; i < n; ++i) {
        mat3d_t A = va_arg(args, mat3d_t);
        product = mat3d_mul(product, A);
    }
    return product;
}

LINALG_DEF vec3d_t mat3d_mul_vec(mat3d_t M, vec3d_t v) {
    vec3d_t result;
    result.x = vec3d_dot(M.v[0], v);
    result.y = vec3d_dot(M.v[1], v);
    result.z = vec3d_dot(M.v[2], v);
    return result;
}

LINALG_DEF mat3d_t mat3d_hadamard(mat3d_t A, mat3d_t B) {
    A.e[0] *= B.e[0];
    A.e[1] *= B.e[1];
    A.e[2] *= B.e[2];
    return A;
}

LINALG_DEF mat3d_t mat3d_rotate(mat3d_t A, rotate_axis_s axis, double angle) {
    size_t i = (axis + 1) % 3;
    size_t j = (axis + 2) % 3;
    A.M[i][i] *= cos(angle);
    A.M[i][j] *= -sin(angle);
    A.M[j][i] *= sin(angle);
    A.M[j][j] *= cos(angle);
    return A;
}

LINALG_DEF vec3i_t vec3i_add(vec3i_t a, vec3i_t b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

LINALG_DEF vec3i_t vec3i_sub(vec3i_t a, vec3i_t b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

LINALG_DEF vec3i_t vec3i_mul(vec3i_t a, vec3i_t b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a;
}

LINALG_DEF vec3i_t vec3i_div(vec3i_t a, vec3i_t b) {
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    return a;
}

LINALG_DEF vec3i_t vec3i_mod(vec3i_t a, vec3i_t b) {
    a.x %= b.x;
    a.y %= b.y;
    a.z %= b.z;
    return a;
}

LINALG_DEF vec3i_t vec3i_min(vec3i_t a, vec3i_t b) {
    a.x = mini(a.x, b.x);
    a.y = mini(a.y, b.y);
    a.z = mini(a.z, b.z);
    return a;
}

LINALG_DEF vec3i_t vec3i_max(vec3i_t a, vec3i_t b) {
    a.x = maxi(a.x, b.x);
    a.y = maxi(a.y, b.y);
    a.z = maxi(a.z, b.z);
    return a;
}

LINALG_DEF vec3i_t vec3i_clamp(vec3i_t v, vec3i_t min, vec3i_t max) {
    v.x = clampi(v.x, min.x, max.x);
    v.y = clampi(v.y, min.y, max.y);
    v.z = clampi(v.z, min.z, max.z);
    return v;
}

LINALG_DEF vec3i_t vec3i_abs(vec3i_t v) {
    v.x = absi(v.x);
    v.y = absi(v.y);
    v.z = absi(v.z);
    return v;
}

LINALG_DEF vec3i_t vec3i_sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec3i_t sum = {0};
    for (size_t i = 0; i < n; ++i) {
        vec3i_t v = va_arg(args, vec3i_t);
        sum = vec3i_add(sum, v);
    }
    return sum;
}

LINALG_DEF vec3i_t vec3i_product(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec3i_t product = vec3i_splat(1);
    for (size_t i = 0; i < n; ++i) {
        vec3i_t v = va_arg(args, vec3i_t);
        product = vec3i_mul(product, v);
    }
    return product;
}

LINALG_DEF int vec3i_dot(vec3i_t a, vec3i_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

LINALG_DEF vec3i_t vec3i_cross(vec3i_t a, vec3i_t b) {
    vec3i_t result = {0};
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.z * b.x;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

LINALG_DEF int vec3i_sqrlen(vec3i_t v) { return vec3i_dot(v, v); }

LINALG_DEF int vec3i_1norm(vec3i_t v) {
    v = vec3i_abs(v);
    int norm = 0;
    norm += v.x;
    norm += v.y;
    norm += v.z;
    return norm;
}

LINALG_DEF vec3i_t vec3i_reflect(vec3i_t v, vec3i_t n) {
    vec3i_t result = n;
    result = vec3i_mul(result, vec3i_splat(vec3i_dot(v, n)));
    result = vec3i_mul(result, vec3i_splat(2));
    result = vec3i_sub(v, result);
    return result;
}

LINALG_DEF mat3i_t mat3i_mul(mat3i_t A, mat3i_t B) {
    mat3i_t result;
    result._11 = A._11 * B._11 + A._12 * B._21 + A._13 * B._31;
    result._12 = A._11 * B._12 + A._12 * B._22 + A._13 * B._32;
    result._13 = A._11 * B._13 + A._12 * B._23 + A._13 * B._33;
    result._21 = A._21 * B._11 + A._22 * B._21 + A._23 * B._31;
    result._22 = A._21 * B._12 + A._22 * B._22 + A._23 * B._32;
    result._23 = A._21 * B._13 + A._22 * B._23 + A._23 * B._33;
    result._31 = A._31 * B._11 + A._32 * B._21 + A._33 * B._31;
    result._32 = A._31 * B._12 + A._32 * B._22 + A._33 * B._32;
    result._33 = A._31 * B._13 + A._32 * B._23 + A._33 * B._33;
    return result;
}

LINALG_DEF mat3i_t mat3i_nmul(size_t n, ...) {
    va_list args;
    va_start(args, n);
    mat3i_t product = mat3i_I();
    for (size_t i = 0; i < n; ++i) {
        mat3i_t A = va_arg(args, mat3i_t);
        product = mat3i_mul(product, A);
    }
    return product;
}

LINALG_DEF vec3i_t mat3i_mul_vec(mat3i_t M, vec3i_t v) {
    vec3i_t result;
    result.x = vec3i_dot(M.v[0], v);
    result.y = vec3i_dot(M.v[1], v);
    result.z = vec3i_dot(M.v[2], v);
    return result;
}

LINALG_DEF mat3i_t mat3i_hadamard(mat3i_t A, mat3i_t B) {
    A.e[0] *= B.e[0];
    A.e[1] *= B.e[1];
    A.e[2] *= B.e[2];
    return A;
}

LINALG_DEF vec3u_t vec3u_add(vec3u_t a, vec3u_t b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

LINALG_DEF vec3u_t vec3u_sub(vec3u_t a, vec3u_t b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

LINALG_DEF vec3u_t vec3u_mul(vec3u_t a, vec3u_t b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a;
}

LINALG_DEF vec3u_t vec3u_div(vec3u_t a, vec3u_t b) {
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    return a;
}

LINALG_DEF vec3u_t vec3u_mod(vec3u_t a, vec3u_t b) {
    a.x %= b.x;
    a.y %= b.y;
    a.z %= b.z;
    return a;
}

LINALG_DEF vec3u_t vec3u_min(vec3u_t a, vec3u_t b) {
    a.x = minu(a.x, b.x);
    a.y = minu(a.y, b.y);
    a.z = minu(a.z, b.z);
    return a;
}

LINALG_DEF vec3u_t vec3u_max(vec3u_t a, vec3u_t b) {
    a.x = maxu(a.x, b.x);
    a.y = maxu(a.y, b.y);
    a.z = maxu(a.z, b.z);
    return a;
}

LINALG_DEF vec3u_t vec3u_clamp(vec3u_t v, vec3u_t min, vec3u_t max) {
    v.x = clampu(v.x, min.x, max.x);
    v.y = clampu(v.y, min.y, max.y);
    v.z = clampu(v.z, min.z, max.z);
    return v;
}

LINALG_DEF vec3u_t vec3u_sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec3u_t sum = {0};
    for (size_t i = 0; i < n; ++i) {
        vec3u_t v = va_arg(args, vec3u_t);
        sum = vec3u_add(sum, v);
    }
    return sum;
}

LINALG_DEF vec3u_t vec3u_product(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec3u_t product = vec3u_splat(1);
    for (size_t i = 0; i < n; ++i) {
        vec3u_t v = va_arg(args, vec3u_t);
        product = vec3u_mul(product, v);
    }
    return product;
}

LINALG_DEF unsigned int vec3u_dot(vec3u_t a, vec3u_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

LINALG_DEF vec3u_t vec3u_cross(vec3u_t a, vec3u_t b) {
    vec3u_t result = {0};
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.z * b.x;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

LINALG_DEF unsigned int vec3u_sqrlen(vec3u_t v) { return vec3u_dot(v, v); }

LINALG_DEF unsigned int vec3u_1norm(vec3u_t v) {
    unsigned int norm = 0;
    norm += v.x;
    norm += v.y;
    norm += v.z;
    return norm;
}

LINALG_DEF vec3u_t vec3u_reflect(vec3u_t v, vec3u_t n) {
    vec3u_t result = n;
    result = vec3u_mul(result, vec3u_splat(vec3u_dot(v, n)));
    result = vec3u_mul(result, vec3u_splat(2));
    result = vec3u_sub(v, result);
    return result;
}

LINALG_DEF mat3u_t mat3u_mul(mat3u_t A, mat3u_t B) {
    mat3u_t result;
    result._11 = A._11 * B._11 + A._12 * B._21 + A._13 * B._31;
    result._12 = A._11 * B._12 + A._12 * B._22 + A._13 * B._32;
    result._13 = A._11 * B._13 + A._12 * B._23 + A._13 * B._33;
    result._21 = A._21 * B._11 + A._22 * B._21 + A._23 * B._31;
    result._22 = A._21 * B._12 + A._22 * B._22 + A._23 * B._32;
    result._23 = A._21 * B._13 + A._22 * B._23 + A._23 * B._33;
    result._31 = A._31 * B._11 + A._32 * B._21 + A._33 * B._31;
    result._32 = A._31 * B._12 + A._32 * B._22 + A._33 * B._32;
    result._33 = A._31 * B._13 + A._32 * B._23 + A._33 * B._33;
    return result;
}

LINALG_DEF mat3u_t mat3u_nmul(size_t n, ...) {
    va_list args;
    va_start(args, n);
    mat3u_t product = mat3u_I();
    for (size_t i = 0; i < n; ++i) {
        mat3u_t A = va_arg(args, mat3u_t);
        product = mat3u_mul(product, A);
    }
    return product;
}

LINALG_DEF vec3u_t mat3u_mul_vec(mat3u_t M, vec3u_t v) {
    vec3u_t result;
    result.x = vec3u_dot(M.v[0], v);
    result.y = vec3u_dot(M.v[1], v);
    result.z = vec3u_dot(M.v[2], v);
    return result;
}

LINALG_DEF mat3u_t mat3u_hadamard(mat3u_t A, mat3u_t B) {
    A.e[0] *= B.e[0];
    A.e[1] *= B.e[1];
    A.e[2] *= B.e[2];
    return A;
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

LINALG_DEF vec4f_t vec4f_abs(vec4f_t v) {
    v.x = fabsf(v.x);
    v.y = fabsf(v.y);
    v.z = fabsf(v.z);
    v.w = fabsf(v.w);
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

LINALG_DEF vec4f_t vec4f_product(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec4f_t product = vec4f_splat(1);
    for (size_t i = 0; i < n; ++i) {
        vec4f_t v = va_arg(args, vec4f_t);
        product = vec4f_mul(product, v);
    }
    return product;
}

LINALG_DEF float vec4f_dot(vec4f_t a, vec4f_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

LINALG_DEF float vec4f_sqrlen(vec4f_t v) { return vec4f_dot(v, v); }

LINALG_DEF float vec4f_1norm(vec4f_t v) {
    v = vec4f_abs(v);
    float norm = 0;
    norm += v.x;
    norm += v.y;
    norm += v.z;
    norm += v.w;
    return norm;
}

LINALG_DEF float vec4f_2norm(vec4f_t v) { return sqrtf(vec4f_sqrlen(v)); }

LINALG_DEF vec4f_t vec4f_unit(vec4f_t v) {
    return vec4f_div(v, vec4f_splat(vec4f_2norm(v)));
}

LINALG_DEF vec4f_t vec4f_norm(vec4f_t v) { return vec4f_unit(v); }

LINALG_DEF _Bool vec4f_eq(vec4f_t a, vec4f_t b, float epsilon) {
    if (fabsf(b.x - a.x) > epsilon) {
        return 0;
    }
    if (fabsf(b.y - a.y) > epsilon) {
        return 0;
    }
    if (fabsf(b.z - a.z) > epsilon) {
        return 0;
    }
    if (fabsf(b.w - a.w) > epsilon) {
        return 0;
    }
    return 1;
}

LINALG_DEF vec4f_t vec4f_reflect(vec4f_t v, vec4f_t n) {
    vec4f_t result = n;
    result = vec4f_mul(result, vec4f_splat(vec4f_dot(v, n)));
    result = vec4f_mul(result, vec4f_splat(2));
    result = vec4f_sub(v, result);
    return result;
}

LINALG_DEF vec4f_t vec4f_direction(vec4f_t a, vec4f_t b) {
    vec4f_t delta = vec4f_sub(b, a);
    return vec4f_unit(delta);
}

LINALG_DEF mat4f_t mat4f_mul(mat4f_t A, mat4f_t B) {
    mat4f_t result;
    result._11 = A._11 * B._11 + A._12 * B._21 + A._13 * B._31 + A._14 * B._41;
    result._12 = A._11 * B._12 + A._12 * B._22 + A._13 * B._32 + A._14 * B._42;
    result._13 = A._11 * B._13 + A._12 * B._23 + A._13 * B._33 + A._14 * B._43;
    result._14 = A._11 * B._14 + A._12 * B._24 + A._13 * B._34 + A._14 * B._44;
    result._21 = A._21 * B._11 + A._22 * B._21 + A._23 * B._31 + A._24 * B._41;
    result._22 = A._21 * B._12 + A._22 * B._22 + A._23 * B._32 + A._24 * B._42;
    result._23 = A._21 * B._13 + A._22 * B._23 + A._23 * B._33 + A._24 * B._43;
    result._24 = A._21 * B._14 + A._22 * B._24 + A._23 * B._34 + A._24 * B._44;
    result._31 = A._31 * B._11 + A._32 * B._21 + A._33 * B._31 + A._34 * B._41;
    result._32 = A._31 * B._12 + A._32 * B._22 + A._33 * B._32 + A._34 * B._42;
    result._33 = A._31 * B._13 + A._32 * B._23 + A._33 * B._33 + A._34 * B._43;
    result._34 = A._31 * B._14 + A._32 * B._24 + A._33 * B._34 + A._34 * B._44;
    result._41 = A._41 * B._11 + A._42 * B._21 + A._43 * B._31 + A._44 * B._41;
    result._42 = A._41 * B._12 + A._42 * B._22 + A._43 * B._32 + A._44 * B._42;
    result._43 = A._41 * B._13 + A._42 * B._23 + A._43 * B._33 + A._44 * B._43;
    result._44 = A._41 * B._14 + A._42 * B._24 + A._43 * B._34 + A._44 * B._44;
    return result;
}

LINALG_DEF mat4f_t mat4f_nmul(size_t n, ...) {
    va_list args;
    va_start(args, n);
    mat4f_t product = mat4f_I();
    for (size_t i = 0; i < n; ++i) {
        mat4f_t A = va_arg(args, mat4f_t);
        product = mat4f_mul(product, A);
    }
    return product;
}

LINALG_DEF vec4f_t mat4f_mul_vec(mat4f_t M, vec4f_t v) {
    vec4f_t result;
    result.x = vec4f_dot(M.v[0], v);
    result.y = vec4f_dot(M.v[1], v);
    result.z = vec4f_dot(M.v[2], v);
    result.w = vec4f_dot(M.v[3], v);
    return result;
}

LINALG_DEF mat4f_t mat4f_hadamard(mat4f_t A, mat4f_t B) {
    A.e[0] *= B.e[0];
    A.e[1] *= B.e[1];
    A.e[2] *= B.e[2];
    A.e[3] *= B.e[3];
    return A;
}

LINALG_DEF mat4f_t mat4f_rotate(mat4f_t A, rotate_axis_s axis, float angle) {
    size_t i = (axis + 1) % 3;
    size_t j = (axis + 2) % 3;
    A.M[i][i] *= cosf(angle);
    A.M[i][j] *= -sinf(angle);
    A.M[j][i] *= sinf(angle);
    A.M[j][j] *= cosf(angle);
    return A;
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

LINALG_DEF vec4d_t vec4d_abs(vec4d_t v) {
    v.x = fabs(v.x);
    v.y = fabs(v.y);
    v.z = fabs(v.z);
    v.w = fabs(v.w);
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

LINALG_DEF vec4d_t vec4d_product(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec4d_t product = vec4d_splat(1);
    for (size_t i = 0; i < n; ++i) {
        vec4d_t v = va_arg(args, vec4d_t);
        product = vec4d_mul(product, v);
    }
    return product;
}

LINALG_DEF double vec4d_dot(vec4d_t a, vec4d_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

LINALG_DEF double vec4d_sqrlen(vec4d_t v) { return vec4d_dot(v, v); }

LINALG_DEF double vec4d_1norm(vec4d_t v) {
    v = vec4d_abs(v);
    double norm = 0;
    norm += v.x;
    norm += v.y;
    norm += v.z;
    norm += v.w;
    return norm;
}

LINALG_DEF double vec4d_2norm(vec4d_t v) { return sqrt(vec4d_sqrlen(v)); }

LINALG_DEF vec4d_t vec4d_unit(vec4d_t v) {
    return vec4d_div(v, vec4d_splat(vec4d_2norm(v)));
}

LINALG_DEF vec4d_t vec4d_norm(vec4d_t v) { return vec4d_unit(v); }

LINALG_DEF _Bool vec4d_eq(vec4d_t a, vec4d_t b, double epsilon) {
    if (fabs(b.x - a.x) > epsilon) {
        return 0;
    }
    if (fabs(b.y - a.y) > epsilon) {
        return 0;
    }
    if (fabs(b.z - a.z) > epsilon) {
        return 0;
    }
    if (fabs(b.w - a.w) > epsilon) {
        return 0;
    }
    return 1;
}

LINALG_DEF vec4d_t vec4d_reflect(vec4d_t v, vec4d_t n) {
    vec4d_t result = n;
    result = vec4d_mul(result, vec4d_splat(vec4d_dot(v, n)));
    result = vec4d_mul(result, vec4d_splat(2));
    result = vec4d_sub(v, result);
    return result;
}

LINALG_DEF vec4d_t vec4d_direction(vec4d_t a, vec4d_t b) {
    vec4d_t delta = vec4d_sub(b, a);
    return vec4d_unit(delta);
}

LINALG_DEF mat4d_t mat4d_mul(mat4d_t A, mat4d_t B) {
    mat4d_t result;
    result._11 = A._11 * B._11 + A._12 * B._21 + A._13 * B._31 + A._14 * B._41;
    result._12 = A._11 * B._12 + A._12 * B._22 + A._13 * B._32 + A._14 * B._42;
    result._13 = A._11 * B._13 + A._12 * B._23 + A._13 * B._33 + A._14 * B._43;
    result._14 = A._11 * B._14 + A._12 * B._24 + A._13 * B._34 + A._14 * B._44;
    result._21 = A._21 * B._11 + A._22 * B._21 + A._23 * B._31 + A._24 * B._41;
    result._22 = A._21 * B._12 + A._22 * B._22 + A._23 * B._32 + A._24 * B._42;
    result._23 = A._21 * B._13 + A._22 * B._23 + A._23 * B._33 + A._24 * B._43;
    result._24 = A._21 * B._14 + A._22 * B._24 + A._23 * B._34 + A._24 * B._44;
    result._31 = A._31 * B._11 + A._32 * B._21 + A._33 * B._31 + A._34 * B._41;
    result._32 = A._31 * B._12 + A._32 * B._22 + A._33 * B._32 + A._34 * B._42;
    result._33 = A._31 * B._13 + A._32 * B._23 + A._33 * B._33 + A._34 * B._43;
    result._34 = A._31 * B._14 + A._32 * B._24 + A._33 * B._34 + A._34 * B._44;
    result._41 = A._41 * B._11 + A._42 * B._21 + A._43 * B._31 + A._44 * B._41;
    result._42 = A._41 * B._12 + A._42 * B._22 + A._43 * B._32 + A._44 * B._42;
    result._43 = A._41 * B._13 + A._42 * B._23 + A._43 * B._33 + A._44 * B._43;
    result._44 = A._41 * B._14 + A._42 * B._24 + A._43 * B._34 + A._44 * B._44;
    return result;
}

LINALG_DEF mat4d_t mat4d_nmul(size_t n, ...) {
    va_list args;
    va_start(args, n);
    mat4d_t product = mat4d_I();
    for (size_t i = 0; i < n; ++i) {
        mat4d_t A = va_arg(args, mat4d_t);
        product = mat4d_mul(product, A);
    }
    return product;
}

LINALG_DEF vec4d_t mat4d_mul_vec(mat4d_t M, vec4d_t v) {
    vec4d_t result;
    result.x = vec4d_dot(M.v[0], v);
    result.y = vec4d_dot(M.v[1], v);
    result.z = vec4d_dot(M.v[2], v);
    result.w = vec4d_dot(M.v[3], v);
    return result;
}

LINALG_DEF mat4d_t mat4d_hadamard(mat4d_t A, mat4d_t B) {
    A.e[0] *= B.e[0];
    A.e[1] *= B.e[1];
    A.e[2] *= B.e[2];
    A.e[3] *= B.e[3];
    return A;
}

LINALG_DEF mat4d_t mat4d_rotate(mat4d_t A, rotate_axis_s axis, double angle) {
    size_t i = (axis + 1) % 3;
    size_t j = (axis + 2) % 3;
    A.M[i][i] *= cos(angle);
    A.M[i][j] *= -sin(angle);
    A.M[j][i] *= sin(angle);
    A.M[j][j] *= cos(angle);
    return A;
}

LINALG_DEF vec4i_t vec4i_add(vec4i_t a, vec4i_t b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

LINALG_DEF vec4i_t vec4i_sub(vec4i_t a, vec4i_t b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

LINALG_DEF vec4i_t vec4i_mul(vec4i_t a, vec4i_t b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;
    return a;
}

LINALG_DEF vec4i_t vec4i_div(vec4i_t a, vec4i_t b) {
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;
    return a;
}

LINALG_DEF vec4i_t vec4i_mod(vec4i_t a, vec4i_t b) {
    a.x %= b.x;
    a.y %= b.y;
    a.z %= b.z;
    a.w %= b.w;
    return a;
}

LINALG_DEF vec4i_t vec4i_min(vec4i_t a, vec4i_t b) {
    a.x = mini(a.x, b.x);
    a.y = mini(a.y, b.y);
    a.z = mini(a.z, b.z);
    a.w = mini(a.w, b.w);
    return a;
}

LINALG_DEF vec4i_t vec4i_max(vec4i_t a, vec4i_t b) {
    a.x = maxi(a.x, b.x);
    a.y = maxi(a.y, b.y);
    a.z = maxi(a.z, b.z);
    a.w = maxi(a.w, b.w);
    return a;
}

LINALG_DEF vec4i_t vec4i_clamp(vec4i_t v, vec4i_t min, vec4i_t max) {
    v.x = clampi(v.x, min.x, max.x);
    v.y = clampi(v.y, min.y, max.y);
    v.z = clampi(v.z, min.z, max.z);
    v.w = clampi(v.w, min.w, max.w);
    return v;
}

LINALG_DEF vec4i_t vec4i_abs(vec4i_t v) {
    v.x = absi(v.x);
    v.y = absi(v.y);
    v.z = absi(v.z);
    v.w = absi(v.w);
    return v;
}

LINALG_DEF vec4i_t vec4i_sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec4i_t sum = {0};
    for (size_t i = 0; i < n; ++i) {
        vec4i_t v = va_arg(args, vec4i_t);
        sum = vec4i_add(sum, v);
    }
    return sum;
}

LINALG_DEF vec4i_t vec4i_product(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec4i_t product = vec4i_splat(1);
    for (size_t i = 0; i < n; ++i) {
        vec4i_t v = va_arg(args, vec4i_t);
        product = vec4i_mul(product, v);
    }
    return product;
}

LINALG_DEF int vec4i_dot(vec4i_t a, vec4i_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

LINALG_DEF int vec4i_sqrlen(vec4i_t v) { return vec4i_dot(v, v); }

LINALG_DEF int vec4i_1norm(vec4i_t v) {
    v = vec4i_abs(v);
    int norm = 0;
    norm += v.x;
    norm += v.y;
    norm += v.z;
    norm += v.w;
    return norm;
}

LINALG_DEF vec4i_t vec4i_reflect(vec4i_t v, vec4i_t n) {
    vec4i_t result = n;
    result = vec4i_mul(result, vec4i_splat(vec4i_dot(v, n)));
    result = vec4i_mul(result, vec4i_splat(2));
    result = vec4i_sub(v, result);
    return result;
}

LINALG_DEF mat4i_t mat4i_mul(mat4i_t A, mat4i_t B) {
    mat4i_t result;
    result._11 = A._11 * B._11 + A._12 * B._21 + A._13 * B._31 + A._14 * B._41;
    result._12 = A._11 * B._12 + A._12 * B._22 + A._13 * B._32 + A._14 * B._42;
    result._13 = A._11 * B._13 + A._12 * B._23 + A._13 * B._33 + A._14 * B._43;
    result._14 = A._11 * B._14 + A._12 * B._24 + A._13 * B._34 + A._14 * B._44;
    result._21 = A._21 * B._11 + A._22 * B._21 + A._23 * B._31 + A._24 * B._41;
    result._22 = A._21 * B._12 + A._22 * B._22 + A._23 * B._32 + A._24 * B._42;
    result._23 = A._21 * B._13 + A._22 * B._23 + A._23 * B._33 + A._24 * B._43;
    result._24 = A._21 * B._14 + A._22 * B._24 + A._23 * B._34 + A._24 * B._44;
    result._31 = A._31 * B._11 + A._32 * B._21 + A._33 * B._31 + A._34 * B._41;
    result._32 = A._31 * B._12 + A._32 * B._22 + A._33 * B._32 + A._34 * B._42;
    result._33 = A._31 * B._13 + A._32 * B._23 + A._33 * B._33 + A._34 * B._43;
    result._34 = A._31 * B._14 + A._32 * B._24 + A._33 * B._34 + A._34 * B._44;
    result._41 = A._41 * B._11 + A._42 * B._21 + A._43 * B._31 + A._44 * B._41;
    result._42 = A._41 * B._12 + A._42 * B._22 + A._43 * B._32 + A._44 * B._42;
    result._43 = A._41 * B._13 + A._42 * B._23 + A._43 * B._33 + A._44 * B._43;
    result._44 = A._41 * B._14 + A._42 * B._24 + A._43 * B._34 + A._44 * B._44;
    return result;
}

LINALG_DEF mat4i_t mat4i_nmul(size_t n, ...) {
    va_list args;
    va_start(args, n);
    mat4i_t product = mat4i_I();
    for (size_t i = 0; i < n; ++i) {
        mat4i_t A = va_arg(args, mat4i_t);
        product = mat4i_mul(product, A);
    }
    return product;
}

LINALG_DEF vec4i_t mat4i_mul_vec(mat4i_t M, vec4i_t v) {
    vec4i_t result;
    result.x = vec4i_dot(M.v[0], v);
    result.y = vec4i_dot(M.v[1], v);
    result.z = vec4i_dot(M.v[2], v);
    result.w = vec4i_dot(M.v[3], v);
    return result;
}

LINALG_DEF mat4i_t mat4i_hadamard(mat4i_t A, mat4i_t B) {
    A.e[0] *= B.e[0];
    A.e[1] *= B.e[1];
    A.e[2] *= B.e[2];
    A.e[3] *= B.e[3];
    return A;
}

LINALG_DEF vec4u_t vec4u_add(vec4u_t a, vec4u_t b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

LINALG_DEF vec4u_t vec4u_sub(vec4u_t a, vec4u_t b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

LINALG_DEF vec4u_t vec4u_mul(vec4u_t a, vec4u_t b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;
    return a;
}

LINALG_DEF vec4u_t vec4u_div(vec4u_t a, vec4u_t b) {
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;
    return a;
}

LINALG_DEF vec4u_t vec4u_mod(vec4u_t a, vec4u_t b) {
    a.x %= b.x;
    a.y %= b.y;
    a.z %= b.z;
    a.w %= b.w;
    return a;
}

LINALG_DEF vec4u_t vec4u_min(vec4u_t a, vec4u_t b) {
    a.x = minu(a.x, b.x);
    a.y = minu(a.y, b.y);
    a.z = minu(a.z, b.z);
    a.w = minu(a.w, b.w);
    return a;
}

LINALG_DEF vec4u_t vec4u_max(vec4u_t a, vec4u_t b) {
    a.x = maxu(a.x, b.x);
    a.y = maxu(a.y, b.y);
    a.z = maxu(a.z, b.z);
    a.w = maxu(a.w, b.w);
    return a;
}

LINALG_DEF vec4u_t vec4u_clamp(vec4u_t v, vec4u_t min, vec4u_t max) {
    v.x = clampu(v.x, min.x, max.x);
    v.y = clampu(v.y, min.y, max.y);
    v.z = clampu(v.z, min.z, max.z);
    v.w = clampu(v.w, min.w, max.w);
    return v;
}

LINALG_DEF vec4u_t vec4u_sum(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec4u_t sum = {0};
    for (size_t i = 0; i < n; ++i) {
        vec4u_t v = va_arg(args, vec4u_t);
        sum = vec4u_add(sum, v);
    }
    return sum;
}

LINALG_DEF vec4u_t vec4u_product(size_t n, ...) {
    va_list args;
    va_start(args, n);
    vec4u_t product = vec4u_splat(1);
    for (size_t i = 0; i < n; ++i) {
        vec4u_t v = va_arg(args, vec4u_t);
        product = vec4u_mul(product, v);
    }
    return product;
}

LINALG_DEF unsigned int vec4u_dot(vec4u_t a, vec4u_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

LINALG_DEF unsigned int vec4u_sqrlen(vec4u_t v) { return vec4u_dot(v, v); }

LINALG_DEF unsigned int vec4u_1norm(vec4u_t v) {
    unsigned int norm = 0;
    norm += v.x;
    norm += v.y;
    norm += v.z;
    norm += v.w;
    return norm;
}

LINALG_DEF vec4u_t vec4u_reflect(vec4u_t v, vec4u_t n) {
    vec4u_t result = n;
    result = vec4u_mul(result, vec4u_splat(vec4u_dot(v, n)));
    result = vec4u_mul(result, vec4u_splat(2));
    result = vec4u_sub(v, result);
    return result;
}

LINALG_DEF mat4u_t mat4u_mul(mat4u_t A, mat4u_t B) {
    mat4u_t result;
    result._11 = A._11 * B._11 + A._12 * B._21 + A._13 * B._31 + A._14 * B._41;
    result._12 = A._11 * B._12 + A._12 * B._22 + A._13 * B._32 + A._14 * B._42;
    result._13 = A._11 * B._13 + A._12 * B._23 + A._13 * B._33 + A._14 * B._43;
    result._14 = A._11 * B._14 + A._12 * B._24 + A._13 * B._34 + A._14 * B._44;
    result._21 = A._21 * B._11 + A._22 * B._21 + A._23 * B._31 + A._24 * B._41;
    result._22 = A._21 * B._12 + A._22 * B._22 + A._23 * B._32 + A._24 * B._42;
    result._23 = A._21 * B._13 + A._22 * B._23 + A._23 * B._33 + A._24 * B._43;
    result._24 = A._21 * B._14 + A._22 * B._24 + A._23 * B._34 + A._24 * B._44;
    result._31 = A._31 * B._11 + A._32 * B._21 + A._33 * B._31 + A._34 * B._41;
    result._32 = A._31 * B._12 + A._32 * B._22 + A._33 * B._32 + A._34 * B._42;
    result._33 = A._31 * B._13 + A._32 * B._23 + A._33 * B._33 + A._34 * B._43;
    result._34 = A._31 * B._14 + A._32 * B._24 + A._33 * B._34 + A._34 * B._44;
    result._41 = A._41 * B._11 + A._42 * B._21 + A._43 * B._31 + A._44 * B._41;
    result._42 = A._41 * B._12 + A._42 * B._22 + A._43 * B._32 + A._44 * B._42;
    result._43 = A._41 * B._13 + A._42 * B._23 + A._43 * B._33 + A._44 * B._43;
    result._44 = A._41 * B._14 + A._42 * B._24 + A._43 * B._34 + A._44 * B._44;
    return result;
}

LINALG_DEF mat4u_t mat4u_nmul(size_t n, ...) {
    va_list args;
    va_start(args, n);
    mat4u_t product = mat4u_I();
    for (size_t i = 0; i < n; ++i) {
        mat4u_t A = va_arg(args, mat4u_t);
        product = mat4u_mul(product, A);
    }
    return product;
}

LINALG_DEF vec4u_t mat4u_mul_vec(mat4u_t M, vec4u_t v) {
    vec4u_t result;
    result.x = vec4u_dot(M.v[0], v);
    result.y = vec4u_dot(M.v[1], v);
    result.z = vec4u_dot(M.v[2], v);
    result.w = vec4u_dot(M.v[3], v);
    return result;
}

LINALG_DEF mat4u_t mat4u_hadamard(mat4u_t A, mat4u_t B) {
    A.e[0] *= B.e[0];
    A.e[1] *= B.e[1];
    A.e[2] *= B.e[2];
    A.e[3] *= B.e[3];
    return A;
}

#endif // LINALG_H
