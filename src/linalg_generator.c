#include "typedefs.h"
#include "varia.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

#define VEC_MIN_SIZE 2
#define VEC_MAX_SIZE 4
static_assert(VEC_MIN_SIZE <= VEC_MAX_SIZE, "Empty set of vector sizes.");

#define INDENT "    "

static const char *vec_math_components = "xyzw";
static const char *vec_color_components = "rgba";

typedef enum {
    FLOAT_T = 0,
    DOUBLE_T,
    NUM_TYPES,
} type_s;

typedef struct {
    const char *keyword;
    const char *suffix;
    const char *fmt;
    const char *zero_literal;
} type_definition_s;

static_assert(NUM_TYPES == 2, "Number of types has changed.");
static type_definition_s type_definitions[NUM_TYPES] = {
    [FLOAT_T] = {.keyword = "float",
                 .suffix = "f",
                 .fmt = "f",
                 .zero_literal = "0.0f"},
    [DOUBLE_T] = {.keyword = "double",
                  .suffix = "d",
                  .fmt = "lf",
                  .zero_literal = "0.0"},
};

typedef enum {
    OP_ADD = 0,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    NUM_OPS,
} op_s;

typedef struct {
    const char *name;
    const char *keyword;
} op_definition_s;

static_assert(NUM_OPS == 4, "Number of operations has changed.");
static const op_definition_s op_definitions[NUM_OPS] = {
    [OP_ADD] = {.name = "add", .keyword = "+="},
    [OP_SUB] = {.name = "sub", .keyword = "-="},
    [OP_MUL] = {.name = "mul", .keyword = "*="},
    [OP_DIV] = {.name = "div", .keyword = "/="},
};

const char *vec_type_name(size_t dim, type_s type) {
    return varia_temp_sprintf("vec%zu%s_t", dim, type_definitions[type].suffix);
}

const char *vec_constructor_name(size_t dim, type_s type) {
    return varia_temp_sprintf("vec%zu%s", dim, type_definitions[type].suffix);
}

const char *vec_fn_name(size_t dim, type_s type, const char *fn_name) {
    return varia_temp_sprintf("vec%zu%s_%s", dim, type_definitions[type].suffix,
                              fn_name);
}

void generate_vec_definition(FILE *restrict stream, size_t dim, type_s type) {
    fprintf(stream, "typedef union {\n");
    if (dim <= 4) {
        // Math components
        fprintf(stream, INDENT "struct { %s ", type_definitions[type].keyword);
        for (size_t component = 0; component < dim; ++component) {
            if (component > 0) {
                fprintf(stream, ", ");
            }
            fprintf(stream, "%c", vec_math_components[component]);
        }
        fprintf(stream, "; };\n");
    }
    if (dim == 3 || dim == 4) {
        // Color components
        fprintf(stream, INDENT "struct { %s ", type_definitions[type].keyword);
        for (size_t component = 0; component < dim; ++component) {
            if (component > 0) {
                fprintf(stream, ", ");
            }
            fprintf(stream, "%c", vec_color_components[component]);
        }
        fprintf(stream, "; };\n");
    }
    fprintf(stream, INDENT "%s e[%zu];\n", type_definitions[type].keyword, dim);
    fprintf(stream, "} vec%zu%s_t;\n", dim, type_definitions[type].suffix);
    fprintf(stream, "\n");
}

void generate_vec_constructor(FILE *restrict stream, size_t dim, type_s type) {
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_constructor = vec_constructor_name(dim, type);
    fprintf(stream, "%s %s(", vec_type, vec_constructor);
    for (size_t component = 0; component < dim; ++component) {
        if (component > 0) {
            fprintf(stream, ", ");
        }
        fprintf(stream, "%s %c", type_definitions[type].keyword,
                vec_math_components[component]);
    }
    fprintf(stream, ") {\n");
    fprintf(stream, INDENT "%s v = {", vec_type);
    for (size_t component = 0; component < dim; ++component) {
        if (component > 0) {
            fprintf(stream, ", ");
        }
        fprintf(stream, "%c", vec_math_components[component]);
    }
    fprintf(stream, "};\n");
    fprintf(stream, INDENT "return v;\n");
    fprintf(stream, "};\n");
    fprintf(stream, "\n");
}

void generate_vec_operation(FILE *restrict stream, size_t dim, type_s type);

void generate_vec_function(FILE *restrict stream, size_t dim, type_s type,
                           bool applies_to);

int main() {
    for (size_t dim = VEC_MIN_SIZE; dim <= VEC_MAX_SIZE; ++dim) {
        for (size_t type = 0; type < NUM_TYPES; ++type) {
            generate_vec_definition(stdout, dim, type);
        }
    }

    // Constructors with math syntax only support up to 4 components
    size_t num_constructor_dims = VEC_MAX_SIZE < 4 ? VEC_MAX_SIZE : 4;
    for (size_t dim = VEC_MIN_SIZE; dim <= num_constructor_dims; ++dim) {
        for (size_t type = 0; type < NUM_TYPES; ++type) {
            generate_vec_constructor(stdout, dim, type);
        }
    }

    printf("Bytes of temp stack used: %zu\n", varia_temp_size);
    return 0;
}
