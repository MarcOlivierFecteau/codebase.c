#ifndef VARIA_H
#define VARIA_H

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define VARIA_DEF static inline
#define VARIA_TEMP_CAPACITY (8 * 1024 * 1024) // 8 MB "internal stack" capacity

typedef unsigned long uintptr_t; // NOTE: might be dangerous.

static size_t varia_temp_size = 0;
static char varia_temp_stack[VARIA_TEMP_CAPACITY] = {0};

VARIA_DEF void *varia_temp_alloc(size_t requested) {
    size_t word_size = sizeof(uintptr_t);
    // NOTE: floor with "multiply by one" trick.
    size_t size = (requested + word_size - 1) / word_size * word_size;
    if (varia_temp_size + size > VARIA_TEMP_CAPACITY) {
        return NULL;
    }
    void *result = &varia_temp_stack[varia_temp_size];
    varia_temp_size += size;
    return result;
}

VARIA_DEF char *varia_temp_sprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int n = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    assert(n >= 0);
    char *result = (char *)varia_temp_alloc(n + 1);
    assert(result != NULL && "Extend the size of the temporary allocator.");

    va_start(args, fmt);
    vsnprintf(result, n + 1, fmt, args);
    va_end(args);

    return result;
}

VARIA_DEF size_t varia_strlen(const char str[static 1]) {
    size_t len = 0;
    while (*str++ != '\0') {
        ++len;
    }
    return len;
}

VARIA_DEF char *varia_strdup(const char *s) {
    size_t len = 0;
    while (s[len] != '\0') {
        ++len;
    }
    char *result = varia_temp_alloc(len);
    char *ptr = result; // Iterate while leaving original pointer intact.
    while (*s) {
        *ptr++ = *s++;
    }
    *ptr = '\0';
    return result;
}

#endif // VARIA_H
