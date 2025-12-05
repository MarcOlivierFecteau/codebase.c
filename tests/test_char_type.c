#include <assert.h>
#include <stdio.h>

#define CTYPE_IMPLEMENTATION
#include "../src/char_type.h"

static const char lowercase[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                   'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                   's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

static const char uppercase[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                                   'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                                   'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

static const char digits[10] = {'0', '1', '2', '3', '4',
                                '5', '6', '7', '8', '9'};

static const char xdigits[22] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                 '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
                                 'a', 'b', 'c', 'd', 'e', 'f'};

void test_is_alpha(void) {
    // Lowercase letters
    for (unsigned long l = 0; l < sizeof(lowercase); ++l) {
        assert(is_alpha(lowercase[l]));
    }

    // Uppercase letters
    for (unsigned long l = 0; l < sizeof(uppercase); ++l) {
        assert(is_alpha(uppercase[l]));
    }

    // Non-alphabetic
    for (unsigned long d = 0; d < sizeof(digits); ++d) {
        assert(!is_alpha(digits[d]));
    }
    assert(!is_alpha(' '));
    assert(!is_alpha('!'));
    assert(!is_alpha(0x0));
}

void test_is_digit(void) {
    // Valid digits
    for (unsigned long d = 0; d < sizeof(digits); ++d) {
        assert(is_digit(digits[d]));
    }

    // Non-digits
    for (unsigned long l = 0; l < sizeof(lowercase); ++l) {
        assert(!is_digit(lowercase[l]));
    }
    for (unsigned long l = 0; l < sizeof(uppercase); ++l) {
        assert(!is_digit(uppercase[l]));
    }
    assert(!is_digit(' '));
    assert(!is_digit('/'));
    assert(!is_digit(':'));
    assert(!is_digit(0x0));
}

void test_is_alnum(void) {
    // Alphanumeric
    for (unsigned long l = 0; l < sizeof(lowercase); ++l) {
        assert(is_alnum(lowercase[l]));
    }
    for (unsigned long l = 0; l < sizeof(uppercase); ++l) {
        assert(is_alnum(uppercase[l]));
    }
    for (unsigned long d = 0; d < sizeof(digits); ++d) {
        assert(is_alnum(digits[d]));
    }

    // Non-alphanumeric
    assert(!is_alnum(' '));
    assert(!is_alnum('!'));
    assert(!is_alnum('@'));
    assert(!is_alnum(0x0));
}

void test_is_lower(void) {
    // Lowercase
    for (unsigned long l = 0; l < sizeof(lowercase); ++l) {
        assert(is_lower(lowercase[l]));
    }

    // Not lowercase
    for (unsigned long l = 0; l < sizeof(uppercase); ++l) {
        assert(!is_lower(uppercase[l]));
    }
    for (unsigned long d = 0; d < sizeof(digits); ++d) {
        assert(!is_lower(digits[d]));
    }
    assert(!is_lower(' '));
    assert(!is_lower('!'));
    assert(!is_lower('@'));
    assert(!is_lower(0x0));
}

void test_is_upper(void) {
    // Uppercase
    for (unsigned long l = 0; l < sizeof(uppercase); ++l) {
        assert(is_upper(uppercase[l]));
    }

    // Not uppercase
    for (unsigned long l = 0; l < sizeof(lowercase); ++l) {
        assert(!is_upper(lowercase[l]));
    }
    for (unsigned long d = 0; d < sizeof(digits); ++d) {
        assert(!is_upper(digits[d]));
    }
    assert(!is_upper(' '));
    assert(!is_upper('!'));
    assert(!is_upper('@'));
    assert(!is_upper(0x0));
}

void test_is_xdigit(void) {
    // Valid hex digits (0-9, A-F, a-f)
    for (unsigned long x = 0; x < sizeof(xdigits); ++x) {
        assert(is_xdigit(xdigits[x]));
    }

    // Invalid hex digits
    assert(!is_xdigit('g'));
    assert(!is_xdigit('G'));
    assert(!is_xdigit(' '));
    assert(!is_xdigit('!'));
    assert(!is_xdigit('@'));
    assert(!is_xdigit(0x0));
}

void test_is_ascii(void) {
    // ASCII characters
    for (unsigned long l = 0; l < sizeof(lowercase); ++l) {
        assert(is_ascii(lowercase[l]));
    }
    for (unsigned long l = 0; l < sizeof(uppercase); ++l) {
        assert(is_ascii(uppercase[l]));
    }
    for (unsigned long d = 0; d < sizeof(digits); ++d) {
        assert(is_ascii(digits[d]));
    }
    assert(is_ascii(0x0));
    assert(is_ascii(0x7F));

    // Non-ASCII
    assert(!is_ascii(0x80));
    assert(!is_ascii(0xFF));
}

void test_is_ctl(void) {
    // Control characters
    assert(is_ctl(0x0));
    assert(is_ctl('\t'));
    assert(is_ctl('\n'));
    assert(is_ctl(0x1F));
    assert(is_ctl(0x7F));

    // Non-control
    for (unsigned long l = 0; l < sizeof(lowercase); ++l) {
        assert(!is_ctl(lowercase[l]));
    }
    for (unsigned long l = 0; l < sizeof(uppercase); ++l) {
        assert(!is_ctl(uppercase[l]));
    }
    for (unsigned long d = 0; d < sizeof(digits); ++d) {
        assert(!is_ctl(digits[d]));
    }
}

void test_is_space(void) {
    // Space characters
    assert(is_space(' '));
    assert(is_space('\t'));
    assert(is_space('\n'));
    assert(is_space('\v'));
    assert(is_space('\f'));
    assert(is_space('\r'));

    // Non-space
    for (unsigned long l = 0; l < sizeof(lowercase); ++l) {
        assert(!is_space(lowercase[l]));
    }
    for (unsigned long l = 0; l < sizeof(uppercase); ++l) {
        assert(!is_space(uppercase[l]));
    }
    for (unsigned long d = 0; d < sizeof(digits); ++d) {
        assert(!is_space(digits[d]));
    }
    assert(!is_space(0x0));
}

void test_is_blank(void) {
    // Blank characters
    assert(is_blank(' '));
    assert(is_blank('\t'));

    // Non-blank
    for (unsigned long l = 0; l < sizeof(lowercase); ++l) {
        assert(!is_blank(lowercase[l]));
    }
    for (unsigned long l = 0; l < sizeof(uppercase); ++l) {
        assert(!is_blank(uppercase[l]));
    }
    for (unsigned long d = 0; d < sizeof(digits); ++d) {
        assert(!is_blank(digits[d]));
    }
    assert(!is_blank('\n'));
    assert(!is_blank(0x0));
}

void test_is_graph(void) {
    // Graphical characters
    assert(is_graph('!'));
    assert(is_graph('A'));
    assert(is_graph('z'));
    assert(is_graph('~'));

    // Non-graphical
    assert(!is_graph(' '));
    assert(!is_graph('\t'));
    assert(!is_graph(0));
}

void test_is_printable(void) {
    // Printable characters
    assert(is_printable(' '));
    assert(is_printable('A'));
    assert(is_printable('~'));

    // Non-printable
    assert(!is_printable(0x0));
    assert(!is_printable('\t'));
    assert(!is_printable('\n'));
    assert(!is_printable('\v'));
    assert(!is_printable('\f'));
    assert(!is_printable('\r'));
    assert(!is_printable(0x7F));
}

void test_is_punct(void) {
    // Punctuation
    assert(is_punct('!'));
    assert(is_punct('?'));
    assert(is_punct('.'));
    assert(is_punct(','));

    // Non-punctuation
    assert(!is_punct('A'));
    assert(!is_punct('5'));
    assert(!is_punct(' '));
}

void test_to_lower(void) {
    // Uppercase to lowercase
    assert(to_lower('A') == 'a');
    assert(to_lower('Z') == 'z');
    assert(to_lower('M') == 'm');

    // Already lowercase
    assert(to_lower('a') == 'a');
    assert(to_lower('z') == 'z');

    // Non-alphabetic
    assert(to_lower('5') == '5');
    assert(to_lower(' ') == ' ');
}

void test_to_upper(void) {
    // Lowercase to uppercase
    assert(to_upper('a') == 'A');
    assert(to_upper('z') == 'Z');
    assert(to_upper('m') == 'M');

    // Already uppercase
    assert(to_upper('A') == 'A');
    assert(to_upper('Z') == 'Z');

    // Non-alphabetic
    assert(to_upper('5') == '5');
    assert(to_upper(' ') == ' ');
}

void test_to_ascii(void) {
    // Clear high bit
    assert(to_ascii(0xFF) == 0x7F);
    assert(to_ascii(0x85) == 0x05);

    // ASCII unchanged
    for (unsigned long l = 0; l < sizeof(lowercase); ++l) {
        assert(to_ascii(lowercase[l]) == lowercase[l]);
    }
    for (unsigned long l = 0; l < sizeof(uppercase); ++l) {
        assert(to_ascii(uppercase[l]) == uppercase[l]);
    }
    for (unsigned long d = 0; d < sizeof(digits); ++d) {
        assert(to_ascii(digits[d]) == digits[d]);
    }
    assert(to_ascii(0x7F) == 0x7F);
}

int main(void) {
    test_is_alpha();
    test_is_digit();
    test_is_alnum();
    test_is_lower();
    test_is_upper();
    test_is_xdigit();
    test_is_ascii();
    test_is_ctl();
    test_is_space();
    test_is_blank();
    test_is_graph();
    test_is_printable();
    test_is_punct();
    test_to_lower();
    test_to_upper();
    test_to_ascii();

    printf("All tests passed!\n");
    return 0;
}
