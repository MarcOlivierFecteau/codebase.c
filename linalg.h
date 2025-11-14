#ifndef LINALG_H
#define LINALG_H

#include <math.h>

#ifndef LINALG_DEF
#define LINALG_DEF static inline
#endif // LINALG_DEF

typedef union {
    struct { float x, y; };
    float e[2];
} vec2f_t;

#endif // LINALG_H
