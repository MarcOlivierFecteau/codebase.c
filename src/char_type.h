/* Functions to check the type of a character. Most of it is taken from
 * musl-1.2.5. It aims to replace <ctype.h> to reduce the dependency on the GNU
 * C standard library.
 */

#ifndef CTYPE_H
#define CTYPE_H

#if defined(__STDC_VERSION__) && __STDC_VERSION__ < 202311L &&                 \
    !defined(__STDBOOL_H)
#include "typedefs.h"
#endif // <C23 bool

#ifndef CTYPE_DEF
#define CTYPE_DEF static inline
#endif // CTYPE_DEF

// Checks if a character is alphanumeric
CTYPE_DEF bool is_alnum(int c);

// Checks if a character is alphabetic
CTYPE_DEF bool is_alpha(int c);

// Checks if a character is a ASCII character
CTYPE_DEF bool is_ascii(int c);

// Checks if a character is lowercase
CTYPE_DEF bool is_lower(int c);

// Checks if a character is uppercase
CTYPE_DEF bool is_upper(int c);

// Checks if a character is a digit
CTYPE_DEF bool is_digit(int c);

// Checks if a character is a hexadecimal digit
CTYPE_DEF bool is_xdigit(int c);

// Checks if a character is a control character
CTYPE_DEF bool is_ctl(int c);

// Checks if a character is a graphical character
CTYPE_DEF bool is_graph(int c);

// Checks if a character is a space character
CTYPE_DEF bool is_space(int c);

// Checks if a character is a blank character
CTYPE_DEF bool is_blank(int c);

// Checks if a character is printable
CTYPE_DEF bool is_printable(int c);

// Checks if a character is a punctuation character
CTYPE_DEF bool is_punct(int c);

// Converts a character to ASCII
CTYPE_DEF int to_ascii(int c);

// Converts a character to lowercase
CTYPE_DEF int to_lower(int c);

// Converts a character to uppercase
CTYPE_DEF int to_upper(int c);

#define CTYPE_IMPLEMENTATION
#ifdef CTYPE_IMPLEMENTATION

CTYPE_DEF bool is_alnum(int c) { return is_alpha(c) || is_digit(c); }

CTYPE_DEF bool is_alpha(int c) { return ((unsigned)c | 0x20) - 'a' < 26; }

CTYPE_DEF bool is_ascii(int c) { return (unsigned)c < 128; }

CTYPE_DEF bool is_lower(int c) { return (unsigned)c - 'a' < 26; }

CTYPE_DEF bool is_upper(int c) { return (unsigned)c - 'A' < 26; }

CTYPE_DEF bool is_digit(int c) { return (unsigned)c - '0' < 10; }

CTYPE_DEF bool is_xdigit(int c) {
    return is_digit(c) || ((unsigned)c | 0x20) - 'a' < 6;
}

CTYPE_DEF bool is_ctl(int c) { return (unsigned)c < 0x20 || c == 0x7F; }

CTYPE_DEF bool is_graph(int c) { return (unsigned)c - 0x21 < 0x5E; }

CTYPE_DEF bool is_space(int c) { return c == ' ' || (unsigned)c - '\t' < 5; }

CTYPE_DEF bool is_blank(int c) { return c == ' ' || c == '\t'; }

CTYPE_DEF bool is_printable(int c) { return (unsigned)c - 0x20 < 0x5F; }

CTYPE_DEF bool is_punct(int c) { return is_graph(c) && !is_alnum(c); }

CTYPE_DEF int to_ascii(int c) { return c & 0x7F; }

CTYPE_DEF int to_lower(int c) {
    if (is_upper(c)) {
        return c | 0x20;
    }
    return c;
}

CTYPE_DEF int to_upper(int c) {
    if (is_lower(c)) {
        return c & 0x5F;
    }
    return c;
}

#endif // CTYPE_IMPLEMENTATION

#endif // CTYPE_H
