/* Definitions for common mathematical constants and functions (for example,
 * functions that SHOULD be in <math.h>, but are not for some reason).
 */

#ifndef MATHS_H
#define MATHS_H

#include <assert.h>

#ifndef MATHS_DEF
#define MATHS_DEF static inline
#endif // MATHS_DEF

constexpr double pi = {3.141592653589793};
constexpr float pi_f = {3.141592F};

MATHS_DEF int mini(int a, int b) { return a < b ? a : b; }
MATHS_DEF int maxi(int a, int b) { return a > b ? a : b; }
MATHS_DEF int clampi(int x, int min, int max) {
    assert(min <= max && "Invalid range.");
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}
MATHS_DEF int absi(int a) { return a < 0 ? -a : a; }
MATHS_DEF int lerpi(int a, int b, float t) { return a + (int)((b - a) * t); }

MATHS_DEF unsigned int minu(unsigned int a, unsigned int b) {
    return a < b ? a : b;
}
MATHS_DEF unsigned int maxu(unsigned int a, unsigned int b) {
    return a > b ? a : b;
}
MATHS_DEF unsigned int clampu(unsigned int x, unsigned int min,
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
MATHS_DEF unsigned int lerpu(unsigned int a, unsigned int b, float t) {
    // Check for negative values
    long long result = a + (long long)((b - a) * t);
    return result < 0 ? 0 : (unsigned int)result;
}

MATHS_DEF float minf(float a, float b) { return a < b ? a : b; }
MATHS_DEF float maxf(float a, float b) { return a > b ? a : b; }
MATHS_DEF float clampf(float x, float min, float max) {
    assert(min <= max && "Invalid range.");
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}
MATHS_DEF float lerpf(float a, float b, float t) { return a + (b - a) * t; }

MATHS_DEF double mind(double a, double b) { return a < b ? a : b; }
MATHS_DEF double maxd(double a, double b) { return a > b ? a : b; }
MATHS_DEF double clampd(double x, double min, double max) {
    assert(min <= max && "Invalid range.");
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}
MATHS_DEF double lerpd(double a, double b, double t) { return a + (b - a) * t; }

#endif // MATHS_H
