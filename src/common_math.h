/* Definitions for common mathematical functions (for example, functions that
 * SHOULD be in <math.h>, but are not for some reason).
 */

#ifndef COMMON_MATH_H
#define COMMON_MATH_H

#include <assert.h>

#ifndef MATH_DEF
#define MATH_DEF static inline
#endif // MATH_DEF

MATH_DEF int mini(int a, int b) { return a < b ? a : b; }
MATH_DEF int maxi(int a, int b) { return a > b ? a : b; }
MATH_DEF int clampi(int x, int min, int max) {
    assert(min <= max && "Invalid range.");
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}

MATH_DEF unsigned int minu(unsigned int a, unsigned int b) {
    return a < b ? a : b;
}
MATH_DEF unsigned int maxu(unsigned int a, unsigned int b) {
    return a > b ? a : b;
}
MATH_DEF unsigned int clampu(unsigned int x, unsigned int min,
                             unsigned int max) {
    assert(min <= max && "Invalid range.");
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}

MATH_DEF float minf(float a, float b) { return a < b ? a : b; }
MATH_DEF float maxf(float a, float b) { return a > b ? a : b; }
MATH_DEF float clampf(float x, float min, float max) {
    assert(min <= max && "Invalid range.");
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}
MATH_DEF float lerpf(float a, float b, float t) { return a + (b - a) * t; }

MATH_DEF double mind(double a, double b) { return a < b ? a : b; }
MATH_DEF double maxd(double a, double b) { return a > b ? a : b; }
MATH_DEF double clampd(double x, double min, double max) {
    assert(min <= max && "Invalid range.");
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}
MATH_DEF double lerpd(double a, double b, double t) { return a + (b - a) * t; }

#endif // COMMON_MATH_H
