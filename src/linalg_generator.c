#ifdef USE_TYPEDEFS
#include "typedefs.h"
#endif // USE_TYPEDEFS
#include "varia.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

#define VEC_MIN_SIZE 2
#define VEC_MAX_SIZE 4
static_assert(VEC_MIN_SIZE <= VEC_MAX_SIZE, "Empty set of vector sizes.");

#define INDENT "    "
#define EMPTY_LINE(stream) fprintf(stream, "\n")

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
#ifdef USE_TYPEDEFS
static type_definition_s type_definitions[NUM_TYPES] = {
    [FLOAT_T] = {.keyword = "f32",
                 .suffix = "f",
                 .fmt = "f",
                 .zero_literal = "0.0f"},
    USE_TYPEDEFS[DOUBLE_T] = {.keyword = "f64",
                              .suffix = "d",
                              .fmt = "lf",
                              .zero_literal = "0.0"},
};
#else
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
#endif // USE_TYPEDEFS

typedef enum {
    OP_ADD = 0,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    NUM_OPS,
} op_s;

typedef struct {
    const char *name;
    const char *keyword;
} op_definition_s;

static_assert(NUM_OPS == 5, "Number of operations has changed.");
static const op_definition_s op_definitions[NUM_OPS] = {
    [OP_ADD] = {.name = "add", .keyword = "+="},
    [OP_SUB] = {.name = "sub", .keyword = "-="},
    [OP_MUL] = {.name = "mul", .keyword = "*="},
    [OP_DIV] = {.name = "div", .keyword = "/="},
    [OP_MOD] = {.name = "mod", .keyword = "%="},
};

typedef enum {
    VARIADIC_OP_SUM = 0,
    NUM_VARIADIC_OPS,
} variadic_op_s;

typedef struct {
    const char *name;
    const char *op;
} variadic_op_definition_s;

static_assert(NUM_VARIADIC_OPS == 1,
              "Number of variadic operations has changed.");
static const variadic_op_definition_s
    variadic_op_definitions[NUM_VARIADIC_OPS] = {
        [VARIADIC_OP_SUM] = {.name = "sum", .op = "add"},
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

void generate_head(FILE *restrict stream) {
    fprintf(stream, "#ifndef LINALG_H\n");
    fprintf(stream, "#define LINALG_H\n");
    EMPTY_LINE(stream);
    fprintf(stream, "#include \"typedefs.h\"\n");
    fprintf(stream, "#include <math.h>\n");
    fprintf(stream, "#include <stdarg.h>\n");
    EMPTY_LINE(stream);
    fprintf(stream, "#if !defined(__STDDEF_H)\n");
    fprintf(stream, "typedef unsigned long size_t;\n");
    fprintf(stream, "#endif // __STDDEF_H\n");
    EMPTY_LINE(stream);
    fprintf(stream, "#ifndef LINALG_DEF\n");
    fprintf(stream, "#define LINALG_DEF static inline\n");
    fprintf(stream, "#endif // LINALG_DEF\n");
    EMPTY_LINE(stream);
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

void generate_vec_scalar_constructor(FILE *restrict stream, size_t dim,
                                     type_s type) {
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_splat_name = vec_fn_name(dim, type, "splat");
    fprintf(stream, "%s %s(%s x) {\n", vec_type, vec_splat_name,
            type_definitions[type].keyword);
    fprintf(stream, INDENT "%s v = {{", vec_type);
    for (size_t component = 0; component < dim; ++component) {
        if (component > 0) {
            fprintf(stream, ", ");
        }
        fprintf(stream, "x");
    }
    fprintf(stream, "}};\n");
    fprintf(stream, INDENT "return v;\n");
    fprintf(stream, "};\n");
    fprintf(stream, "\n");
}

void generate_vec_operation(FILE *restrict stream, size_t dim, type_s type,
                            op_s op) {
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_fn = vec_fn_name(dim, type, op_definitions[op].name);
    fprintf(stream, "LINALG_DEF %s %s(", vec_type, vec_fn);
    fprintf(stream, "%s a, %s b) {\n", type_definitions[type].keyword,
            type_definitions[type].keyword);
    if (dim <= 4) {
        for (size_t component = 0; component < dim; ++component) {
            fprintf(stream, INDENT "a.%c %s b.%c;\n",
                    vec_math_components[component], op_definitions[op].keyword,
                    vec_math_components[component]);
        }
    } else {
        for (size_t component = 0; component < dim; ++component) {
            fprintf(stream, INDENT "a.e[%zu] %s b.e[%zu];\n", component,
                    op_definitions[op].keyword, component);
        }
    }
    fprintf(stream, INDENT "return a;\n");
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_variadic_operation(FILE *restrict stream, size_t dim, type_s type,
                                 variadic_op_s op) {
    const char *vec_type = vec_type_name(dim, type);
    const char *result_name = variadic_op_definitions[op].name;
    const char *vec_fn = vec_fn_name(dim, type, variadic_op_definitions[op].op);
    fprintf(stream, "LINALG_DEF %s %s(size_t n, ...) {\n", vec_type, vec_fn);
    fprintf(stream, INDENT "va_list args;\n");
    fprintf(stream, INDENT "va_start(args, n);\n");
    fprintf(stream, INDENT "%s %s = {0};\n", vec_type, result_name);
    fprintf(stream, INDENT "for (size_t i = 0; i < n; ++i) {\n");
    fprintf(stream, INDENT INDENT "%s v = va_args(args, %s);\n", vec_type,
            vec_type);
    fprintf(stream, INDENT INDENT "%s = %s(%s, v);\n", result_name, vec_fn,
            result_name);
    fprintf(stream, INDENT "}\n");
    fprintf(stream, INDENT "return %s;\n", result_name);
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

int main() {
    generate_head(stdout);
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
            generate_vec_scalar_constructor(stdout, dim, type);
        }
    }

    for (size_t dim = VEC_MIN_SIZE; dim <= num_constructor_dims; ++dim) {
        for (size_t type = 0; type < NUM_TYPES; ++type) {
            for (size_t op = 0; op < NUM_OPS; ++op) {
                generate_vec_operation(stdout, dim, type, op);
            }
            generate_variadic_operation(stdout, dim, type, VARIADIC_OP_SUM);
        }
    }

    fprintf(stdout, "#endif // LINALG_H\n");

    fprintf(stderr, "Bytes of temp stack used: %zu / %zu (%.4f%%)\n",
            varia_temp_size, (size_t)VARIA_TEMP_CAPACITY,
            100 * (float)varia_temp_size / (float)VARIA_TEMP_CAPACITY);
    return 0;
}
