#ifndef STR_H
#define STR_H

#include "char_type.h"
#include "typedefs.h"

#ifndef STR_DEF
#define STR_DEF static inline
#endif // STR_DEF

typedef struct {
    u8 *data;
    u64 size;
} str_t;

typedef struct {
    struct str_node_t *next;
    str_t string;
} str_node_t;

typedef struct {
    str_node_t *first;
    str_node_t *last;
    u64 num_nodes;
    u64 total_size;
} str_list_t;

typedef struct {
    str_t *elements;
    u64 size;
    u64 capacity;
} str_array_t;

STR_DEF u64 cstrlen(const u8 *cstr);
STR_DEF str_t str_from_parts(const u8 *str, u64 size);
STR_DEF str_t str_from_cstr(const u8 *cstr);
STR_DEF str_t str_trim_left(str_t str);
STR_DEF str_t str_trim_right(str_t str);
STR_DEF str_t str_trim(str_t str);
STR_DEF bool str_eq(str_t a, str_t b, u64 n);
STR_DEF bool str_starts_with(str_t str, str_t expected_prefix);

#define STR_IMPLEMENTATION
#ifdef STR_IMPLEMENTATION

STR_DEF u64 cstrlen(const u8 *cstr) {
    u64 len = 0;
    while (*cstr++ != '\0') {
        ++len;
    }
    return len;
}

STR_DEF str_t str_from_parts(const u8 *str, u64 size) {
    return (str_t){.data = (u8 *)str, .size = size};
}

STR_DEF str_t str_from_cstr(const u8 *cstr) {
    return str_from_parts(cstr, cstrlen(cstr));
}

STR_DEF str_t str_trim_left(str_t str) {
    u64 i = 0;
    while (i < str.size && is_space(str.data[i])) {
        ++i;
    }

    return str_from_parts(str.data + i, str.size - i);
}

STR_DEF str_t str_trim_right(str_t str) {
    u64 i = 0;
    while (i < str.size && is_space(str.data[str.size - 1 - i])) {
        ++i;
    }

    return str_from_parts(str.data, str.size - i);
}

STR_DEF str_t str_trim(str_t str) { return str_trim_right(str_trim_left(str)); }

STR_DEF bool str_eq(str_t a, str_t b, u64 n) {
    if (a.size != b.size) {
        return false;
    } else {
        const u8 *lhs = a.data, *rhs = b.data;
        for (; n > 0 && *lhs == *rhs; --n, lhs++, rhs++) {
            ;
        }
        return true;
    }
}

STR_DEF bool str_starts_with(str_t str, str_t expected_prefix) {
    if (expected_prefix.size <= str.size) {
        str_t prefix = str_from_parts(str.data, expected_prefix.size);
        return str_eq(expected_prefix, prefix, expected_prefix.size);
    }
    return false;
}

#endif // STR_IMPLEMENTATION

#endif // STR_H
