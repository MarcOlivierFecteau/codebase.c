/* Script for procedurally generating the `linalg.h` library.
 *
 * This script is heavily inspired by Alexey Kutepov's project:
 * https://github.com/tsoding/la. Most of the credit goes to him.
 */

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

#define array_len(xs) (sizeof(xs) / sizeof(xs[0]))

typedef enum {
    FLOAT_T = 0,
    DOUBLE_T,
    INT_T,
    UINT_T,
    NUM_TYPES,
} type_s;

typedef struct {
    const char *keyword;
    const char *suffix;
    const char *fmt;
    const char *zero_literal;
} type_definition_s;

static_assert(NUM_TYPES == 4, "Number of types has changed.");
#ifdef USE_TYPEDEFS
static type_definition_s type_definitions[NUM_TYPES] = {
    [FLOAT_T] = {.keyword = "f32",
                 .suffix = "f",
                 .fmt = "f",
                 .zero_literal = "0.0f"},
    [DOUBLE_T] = {.keyword = "f64",
                  .suffix = "d",
                  .fmt = "lf",
                  .zero_literal = "0.0"},
    [INT_T] = {.keyword = "i32",
               .suffix = "i",
               .fmt = "d",
               .zero_literal = "0"},
    [UINT_T] = {.keyword = "u32",
                .suffix = "u",
                .fmt = "u",
                .zero_literal = "0U"},
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
    [INT_T] = {.keyword = "int",
               .suffix = "i",
               .fmt = "d",
               .zero_literal = "0"},
    [UINT_T] = {.keyword = "unsigned int",
                .suffix = "u",
                .fmt = "u",
                .zero_literal = "0U"},
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

#define FN_MAX_ARITY 4

typedef struct {
    const char *name;
    // NOTE: NULL means unsupported type.
    const char *generic_selection[NUM_TYPES];
    size_t arity;
    char *params[FN_MAX_ARITY];
} fn_definition_s;

static_assert(NUM_TYPES == 4, "Number of types has changed.");
static const fn_definition_s fn_definitions[] = {
    {
        .name = "min",
        .generic_selection =
            {
                [FLOAT_T] = "minf",
                [DOUBLE_T] = "mind",
                [INT_T] = "mini",
                [UINT_T] = "minu",
            },
        .arity = 2,
        .params = {"a", "b"},
    },
    {
        .name = "max",
        .generic_selection =
            {
                [FLOAT_T] = "maxf",
                [DOUBLE_T] = "maxd",
                [INT_T] = "maxi",
                [UINT_T] = "maxu",
            },
        .arity = 2,
        .params = {"a", "b"},
    },
    {
        .name = "floor",
        .generic_selection =
            {
                [FLOAT_T] = "floorf",
                [DOUBLE_T] = "floor",
            },
        .arity = 1,
        .params = {"v"},
    },
    {
        .name = "ceil",
        .generic_selection =
            {
                [FLOAT_T] = "ceilf",
                [DOUBLE_T] = "ceil",
            },
        .arity = 1,
        .params = {"v"},
    },
    {
        .name = "clamp",
        .generic_selection =
            {
                [FLOAT_T] = "clampf",
                [DOUBLE_T] = "clampd",
                [INT_T] = "clampi",
                [UINT_T] = "clampu",
            },
        .arity = 3,
        .params = {"v", "min", "max"},
    },
    {
        .name = "lerp",
        .generic_selection =
            {
                [FLOAT_T] = "lerpf",
                [DOUBLE_T] = "lerpd",
            },
        .arity = 3,
        .params = {"a", "b", "t"},
    },
};

const char *vec_type_name(size_t dim, type_s type) {
    return varia_temp_sprintf("vec%zu%s_t", dim, type_definitions[type].suffix);
}

const char *vec_constructor_name(size_t dim, type_s type) {
    return varia_temp_sprintf("vec%zu%s", dim, type_definitions[type].suffix);
}

const char *vec_prefix_name(size_t dim, size_t type) {
    return vec_constructor_name(dim, type);
}

const char *vec_fn_name(size_t dim, type_s type, const char *fn_name) {
    return varia_temp_sprintf("vec%zu%s_%s", dim, type_definitions[type].suffix,
                              fn_name);
}

const char *mat_prefix_name(size_t dim, type_s type) {
    return varia_temp_sprintf("mat%zu%s", dim, type_definitions[type].suffix);
}

void generate_head(FILE *restrict stream) {
    fprintf(stream, "#ifndef LINALG_H\n");
    fprintf(stream, "#define LINALG_H\n");
    EMPTY_LINE(stream);
    fprintf(stream, "#include \"src/common_math.h\"\n");
#ifdef USE_TYPEDEFS
    fprintf(stream, "#include \"src/typedefs.h\"\n");
#endif // USE_TYPEDEFS
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
    EMPTY_LINE(stream);
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
    fprintf(stream, INDENT "%s v = {{", vec_type);
    for (size_t component = 0; component < dim; ++component) {
        if (component > 0) {
            fprintf(stream, ", ");
        }
        fprintf(stream, "%c", vec_math_components[component]);
    }
    fprintf(stream, "}};\n");
    fprintf(stream, INDENT "return v;\n");
    fprintf(stream, "}\n");
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
    fprintf(stream, "}\n");
    fprintf(stream, "\n");
}

void generate_vec_operation(FILE *restrict stream, size_t dim, type_s type,
                            op_s op) {
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_fn = vec_fn_name(dim, type, op_definitions[op].name);
    fprintf(stream, "LINALG_DEF %s %s(", vec_type, vec_fn);
    fprintf(stream, "%s a, %s b) {\n", vec_type, vec_type);
    if (dim <= 4) {
        for (size_t component = 0; component < dim; ++component) {
            // Modulo operator does not support floating-point types.
            if (op == OP_MOD && type == FLOAT_T) {
                fprintf(stream, INDENT "a.%c = fmodf(a.%c, b.%c);\n",
                        vec_math_components[component],
                        vec_math_components[component],
                        vec_math_components[component]);
            } else if (op == OP_MOD && type == DOUBLE_T) {
                fprintf(stream, INDENT "a.%c = fmod(a.%c, b.%c);\n",
                        vec_math_components[component],
                        vec_math_components[component],
                        vec_math_components[component]);
            } else {
                fprintf(stream, INDENT "a.%c %s b.%c;\n",
                        vec_math_components[component],
                        op_definitions[op].keyword,
                        vec_math_components[component]);
            }
        }
    } else {
        for (size_t component = 0; component < dim; ++component) {
            // Modulo operator does not support floating-point types.
            if (op == OP_MOD && type == FLOAT_T) {
                fprintf(stream,
                        INDENT "a.e[%zu] = fmodf(a.e[%zu], b.e[%zu]);\n",
                        component, component, component);
            } else if (op == OP_MOD && type == DOUBLE_T) {
                fprintf(stream, INDENT "a.e[%zu] = fmod(a.e[%zu], b.e[%zu]);\n",
                        component, component, component);
            } else {
                fprintf(stream, INDENT "a.e[%zu] %s b.e[%zu];\n", component,
                        op_definitions[op].keyword, component);
            }
        }
    }
    fprintf(stream, INDENT "return a;\n");
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_vec_variadic_operation(FILE *restrict stream, size_t dim,
                                     type_s type, variadic_op_s op) {
    const char *vec_type = vec_type_name(dim, type);
    const char *result_name = variadic_op_definitions[op].name;
    const char *vec_fn =
        vec_fn_name(dim, type, variadic_op_definitions[op].name);
    const char *vec_op = vec_fn_name(dim, type, variadic_op_definitions[op].op);
    fprintf(stream, "LINALG_DEF %s %s(size_t n, ...) {\n", vec_type, vec_fn);
    fprintf(stream, INDENT "va_list args;\n");
    fprintf(stream, INDENT "va_start(args, n);\n");
    fprintf(stream, INDENT "%s %s = {0};\n", vec_type, result_name);
    fprintf(stream, INDENT "for (size_t i = 0; i < n; ++i) {\n");
    fprintf(stream, INDENT INDENT "%s v = va_arg(args, %s);\n", vec_type,
            vec_type);
    fprintf(stream, INDENT INDENT "%s = %s(%s, v);\n", result_name, vec_op,
            result_name);
    fprintf(stream, INDENT "}\n");
    fprintf(stream, INDENT "return %s;\n", result_name);
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_vec_function(FILE *restrict stream, size_t dim, type_s type,
                           size_t fn_index) {
    fn_definition_s fn = fn_definitions[fn_index];
    if (fn.generic_selection[type] == NULL) {
        return;
    }
    assert(fn.arity > 0);
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_fn = vec_fn_name(dim, type, fn.name);
    const char *type_keyword = type_definitions[type].keyword;
    const char *fn_name = fn.generic_selection[type];
    fprintf(stream, "LINALG_DEF %s %s(", vec_type, vec_fn);
    for (size_t param = 0; param < fn.arity; ++param) {
        if (param > 0) {
            fprintf(stream, ", ");
        }
        fprintf(stream, "%s %s", vec_type, fn.params[param]);
    }
    fprintf(stream, ") {\n");
    if (dim <= 4) {
        for (size_t component = 0; component < dim; ++component) {
            const char element = vec_math_components[component];
            fprintf(stream, INDENT "%s.%c = %s(", fn.params[0], element,
                    fn_name);
            for (size_t param = 0; param < fn.arity; ++param) {
                if (param > 0) {
                    fprintf(stream, ", ");
                }
                fprintf(stream, "%s.%c", fn.params[param], element);
            }
            fprintf(stream, ");\n");
        }
    } else {
        for (size_t component = 0; component < dim; ++component) {
            fprintf(stream, INDENT "%s.e[%zu] = %s(", fn.params[0], component,
                    fn_name);
            for (size_t param = 0; param < fn.arity; ++param) {
                if (param > 0) {
                    fprintf(stream, ", ");
                }
                fprintf(stream, "%s.e[%zu]", fn.params[param], component);
            }
            fprintf(stream, ");\n");
        }
    }
    fprintf(stream, INDENT "return %s;\n", fn.params[0]);
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_vec_dot(FILE *restrict stream, size_t dim, type_s type) {
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_fn = vec_fn_name(dim, type, "dot");
    const char *type_keyword = type_definitions[type].keyword;
    fprintf(stream, "LINALG_DEF %s %s(%s a, %s b) {\n", type_keyword, vec_fn,
            vec_type, vec_type);
    fprintf(stream, INDENT "return ");
    if (dim <= 4) {
        for (size_t component = 0; component < dim; ++component) {
            if (component > 0) {
                fprintf(stream, " + ");
            }
            fprintf(stream, "a.%c * b.%c", vec_math_components[component],
                    vec_math_components[component]);
        }
        fprintf(stream, ";\n");
    } else {
        fprintf(stream, INDENT "%s result = {0};\n", type_keyword);
        fprintf(stream,
                INDENT
                "for (size_t component = 0; component < %zu; ++component {\n)",
                dim);
        for (size_t component = 0; component < dim; ++component) {
            fprintf(stream, INDENT INDENT "result += a.e[%zu] * b.e[%zu];\n",
                    component, component);
        }
        fprintf(stream, INDENT "}\n");
        fprintf(stream, INDENT "return result;\n");
    }
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_vec_mag_squared(FILE *restrict stream, size_t dim, type_s type) {
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_fn = vec_fn_name(dim, type, "mag_squared");
    const char *vec_prefix = vec_prefix_name(dim, type);
    const char *type_keyword = type_definitions[type].keyword;
    fprintf(stream, "LINALG_DEF %s %s(%s v) {\n", type_keyword, vec_fn,
            vec_type);
    fprintf(stream, INDENT "return %s_dot(v, v);\n", vec_prefix);
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_vec_mag(FILE *restrict stream, size_t dim, type_s type) {
    if (!(type == FLOAT_T || type == DOUBLE_T)) {
        return; // sqrt function does not support integer values.
    }
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_fn = vec_fn_name(dim, type, "mag");
    const char *vec_prefix = vec_prefix_name(dim, type);
    const char *type_keyword = type_definitions[type].keyword;
    fprintf(stream, "LINALG_DEF %s %s(%s v) {\n", type_keyword, vec_fn,
            vec_type);
    fprintf(stream, INDENT "return sqrt%s(%s_mag_squared(v));\n",
            type == FLOAT_T ? "f" : "", vec_prefix);
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_vec_unit(FILE *restrict stream, size_t dim, type_s type) {
    if (!(type == FLOAT_T || type == DOUBLE_T)) {
        return; // sqrt function does not support integer values.
    }
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_fn = vec_fn_name(dim, type, "unit");
    const char *vec_prefix = vec_prefix_name(dim, type);
    fprintf(stream, "LINALG_DEF %s %s(%s v) {\n", vec_type, vec_fn, vec_type);
    fprintf(stream, INDENT "return %s_div(v, %s_splat(%s_mag(v)));\n",
            vec_prefix, vec_prefix, vec_prefix);
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
    // alias "norm"
    const char *vec_norm_fn = vec_fn_name(dim, type, "norm");
    fprintf(stream, "LINALG_DEF %s %s(%s v) {\n", vec_type, vec_norm_fn,
            vec_type);
    fprintf(stream, INDENT "return %s(v);\n", vec_fn);
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_vec_eq(FILE *restrict stream, size_t dim, type_s type) {
    if (!(type == FLOAT_T || type == DOUBLE_T)) {
        return; // TODO: implement abs for signed integer types.
    }
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_fn = vec_fn_name(dim, type, "eq");
    const char *type_keyword = type_definitions[type].keyword;
    const char *abs_op = type == FLOAT_T ? "fabsf" : "fabs";
    fprintf(stream, "LINALG_DEF _Bool %s(%s a, %s b, %s epsilon) {\n", vec_fn,
            vec_type, vec_type, type_keyword);
    if (dim <= 4) {
        for (size_t component = 0; component < dim; ++component) {
            char element = vec_math_components[component];
            fprintf(stream,
                    INDENT "if (%s(b.%c - a.%c) > epsilon) { return 0; }\n",
                    abs_op, element, element);
        }
    } else {
        for (size_t component = 0; component < dim; ++component) {
            fprintf(stream,
                    INDENT
                    "if (%s(b.e[%zu] - a.e[%zu]) > epsilon) { return 0; }\n",
                    abs_op, component, component);
        }
    }
    fprintf(stream, INDENT "return 1;\n");
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_vec_reflect(FILE *restrict stream, size_t dim, type_s type) {
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_fn = vec_fn_name(dim, type, "reflect");
    const char *vec_prefix = vec_prefix_name(dim, type);
    fprintf(stream, "LINALG_DEF %s %s(%s v, %s n) {\n", vec_type, vec_fn,
            vec_type, vec_type);
    fprintf(stream, INDENT "%s result = n;\n", vec_type);
    fprintf(stream, INDENT "result = %s_mul(result, %s_splat(%s_dot(v, n)));\n",
            vec_prefix, vec_prefix, vec_prefix);
    fprintf(stream, INDENT "result = %s_mul(result, %s_splat(2));\n",
            vec_prefix, vec_prefix);
    fprintf(stream, INDENT "result = %s_sub(v, result);\n", vec_prefix);
    fprintf(stream, INDENT "return result;\n");
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_vec_direction(FILE *restrict stream, size_t dim, type_s type) {
    if (!(type == FLOAT_T || type == DOUBLE_T)) {
        return; // sqrt function does not support integer values.
    }
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_fn = vec_fn_name(dim, type, "direction");
    const char *vec_prefix = vec_prefix_name(dim, type);
    fprintf(stream, "LINALG_DEF %s %s(%s a, %s b) {\n", vec_type, vec_fn,
            vec_type, vec_type);
    fprintf(stream, INDENT "%s delta = %s_sub(b, a);\n", vec_type, vec_prefix);
    fprintf(stream, INDENT "return %s_unit(delta);\n", vec_prefix);
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_vec_cross(FILE *restrict stream, size_t dim, type_s type) {
    if (!(dim == 2 || dim == 3)) {
        return;
    }
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_fn = vec_fn_name(dim, type, "cross");
    const char *return_type =
        dim == 2 ? type_definitions[type].keyword : vec_type;
    fprintf(stream, "LINALG_DEF %s %s(%s a, %s b) {\n", return_type, vec_fn,
            vec_type, vec_type);
    if (dim == 2) {
        fprintf(stream, INDENT "return a.x * b.y - a.y * b.x;\n");
    } else {
        fprintf(stream, INDENT "%s result = {0};\n", vec_type);
        fprintf(stream, INDENT "result.x = a.y * b.z - a.z * b.y;\n");
        fprintf(stream, INDENT "result.y = a.z * b.x - a.z * b.x;\n");
        fprintf(stream, INDENT "result.z = a.x * b.y - a.y * b.x;\n");
        fprintf(stream, INDENT "return result;\n");
    }
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_vec_angle_between(FILE *restrict stream, size_t dim,
                                type_s type) {
    if (!(dim == 2 || dim == 3)) {
        return; // I couldn't find any useful use for higher dimensions.
    }
    if (!(type == FLOAT_T || type == DOUBLE_T)) {
        return; // sqrt function does not support integer values.
    }
    const char *vec_type = vec_type_name(dim, type);
    const char *vec_fn = vec_fn_name(dim, type, "angle_between");
    const char *vec_prefix = vec_prefix_name(dim, type);
    const char *return_type = type_definitions[type].keyword;
    const char *acos_fn = type == FLOAT_T ? "acosf" : "acos";
    fprintf(stream, "LINALG_DEF %s %s(%s a, %s b) {\n", return_type, vec_fn,
            vec_type, vec_type);
    fprintf(stream, INDENT "%s a_unit = %s_unit(a);\n", vec_type, vec_prefix);
    fprintf(stream, INDENT "%s b_unit = %s_unit(b);\n", vec_type, vec_prefix);
    fprintf(stream, INDENT "return %s(%s_dot(a_unit, b_unit));\n", acos_fn,
            vec_prefix);
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_mat_definition(FILE *restrict stream, size_t dim, type_s type) {
    const char *type_keyword = type_definitions[type].keyword;
    fprintf(stream, "typedef union {\n");
    fprintf(stream, INDENT "struct {\n");
    for (size_t i = 0; i < dim; ++i) {
        fprintf(stream, INDENT INDENT "%s ", type_keyword);
        for (size_t j = 0; j < dim; ++j) {
            if (j > 0) {
                fprintf(stream, ", ");
            }
            fprintf(stream, "_%zu%zu", i + 1, j + 1);
        }
        fprintf(stream, ";\n");
    }
    fprintf(stream, INDENT "};\n");
    fprintf(stream, INDENT "%s M[%zu][%zu];\n", type_keyword, dim, dim);
    fprintf(stream, INDENT "%s e[%zu * %zu];\n", type_keyword, dim, dim);
    fprintf(stream, INDENT "%s v[%zu];\n", vec_type_name(dim, type), dim);
    fprintf(stream, "} mat%zu%s_t;\n", dim, type_definitions[type].suffix);
    EMPTY_LINE(stream);
}

void generate_mat_zero_constructor(FILE *stream, size_t dim, type_s type) {
    const char *type_suffix = type_definitions[type].suffix;
    fprintf(stream, "LINALG_DEF mat%zu%s_t mat%zu%s_zero(void) {\n", dim,
            type_suffix, dim, type_suffix);
    fprintf(stream, INDENT "mat%zu%s_t M = {0};\n", dim, type_suffix);
    fprintf(stream, INDENT "return M;\n");
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_mat_identity_constructor(FILE *restrict stream, size_t dim,
                                       type_s type) {
    const char *type_suffix = type_definitions[type].suffix;
    fprintf(stream, "LINALG_DEF mat%zu%s_t mat%zu%s_I(void) {\n", dim,
            type_suffix, dim, type_suffix);
    fprintf(stream, INDENT "mat%zu%s_t M = {0};\n", dim, type_suffix);
    for (size_t i = 0; i < dim; ++i) {
        fprintf(stream, INDENT "M._%zu%zu = 1;\n", i + 1, i + 1);
    }
    fprintf(stream, INDENT "return M;\n");
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_mat_mul(FILE *restrict stream, size_t dim, type_s type) {
    const char *mat_prefix = mat_prefix_name(dim, type);
    fprintf(stream, "LINALG_DEF %s_t %s_mul(%s_t A, %s_t B) {\n", mat_prefix,
            mat_prefix, mat_prefix, mat_prefix);
    fprintf(stream, INDENT "%s_t result;\n", mat_prefix);
    for (size_t i = 0; i < dim; ++i) {
        for (size_t j = 0; j < dim; ++j) {
            fprintf(stream, INDENT "result._%zu%zu = ", i + 1, j + 1);
            for (size_t k = 0; k < dim; ++k) {
                if (k > 0) {
                    fprintf(stream, " + ");
                }
                fprintf(stream, "A._%zu%zu * B._%zu%zu", i + 1, k + 1, k + 1,
                        j + 1);
            }
            fprintf(stream, ";\n");
        }
    }
    fprintf(stream, INDENT "return result;\n");
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

void generate_mat_mul_by_vec(FILE *restrict stream, size_t dim, type_s type) {
    const char *mat_prefix = mat_prefix_name(dim, type);
    const char *vec_prefix = vec_prefix_name(dim, type);
    fprintf(stream, "LINALG_DEF %s_t %s_mul_vec(%s_t M, %s_t v) {\n",
            vec_prefix, mat_prefix, mat_prefix, vec_prefix);
    fprintf(stream, INDENT "%s_t result;\n", vec_prefix);
    if (dim <= 4) {
        for (size_t component = 0; component < dim; ++component) {
            fprintf(stream, INDENT "result.%c = %s_dot(M.v[%zu], v);\n",
                    vec_math_components[component], vec_prefix, component);
        }
    } else {
        for (size_t component = 0; component < dim; ++component) {
            fprintf(stream, INDENT "result.e[%zu] = %s_dot(M.v[%zu], v);\n",
                    component, vec_prefix, component);
        }
    }
    fprintf(stream, INDENT "return result;\n");
    fprintf(stream, "}\n");
    EMPTY_LINE(stream);
}

int main() {
    generate_head(stdout);
    for (size_t dim = VEC_MIN_SIZE; dim <= VEC_MAX_SIZE; ++dim) {
        for (size_t type = 0; type < NUM_TYPES; ++type) {
            generate_vec_definition(stdout, dim, type);
            generate_mat_definition(stdout, dim, type);
        }
    }

    // NOTES:
    // - Constructors with math syntax only support up to 4 components;
    // - For matrices, I think higher dimension constructors add an unnecessary
    //   amount of bloat in the library.
    size_t max_supported_constructor_dim = VEC_MAX_SIZE < 4 ? VEC_MAX_SIZE : 4;
    for (size_t dim = VEC_MIN_SIZE; dim <= max_supported_constructor_dim;
         ++dim) {
        for (size_t type = 0; type < NUM_TYPES; ++type) {
            generate_vec_constructor(stdout, dim, type);
            generate_vec_scalar_constructor(stdout, dim, type);
            // NOTE: there are no matrix constructor generated, because the
            // number of possible ways to specify the parameters is too high.
            generate_mat_zero_constructor(stdout, dim, type);
            generate_mat_identity_constructor(stdout, dim, type);
        }
    }

    for (size_t dim = VEC_MIN_SIZE; dim <= VEC_MAX_SIZE; ++dim) {
        for (size_t type = 0; type < NUM_TYPES; ++type) {
            for (size_t op = 0; op < NUM_OPS; ++op) {
                generate_vec_operation(stdout, dim, type, op);
            }
            for (size_t fn = 0; fn < array_len(fn_definitions); ++fn) {
                generate_vec_function(stdout, dim, type, fn);
            }
            generate_vec_variadic_operation(stdout, dim, type, VARIADIC_OP_SUM);
            generate_vec_dot(stdout, dim, type);
            generate_vec_cross(stdout, dim, type);
            generate_vec_mag_squared(stdout, dim, type);
            generate_vec_mag(stdout, dim, type);
            generate_vec_unit(stdout, dim, type);
            generate_vec_eq(stdout, dim, type);
            generate_vec_reflect(stdout, dim, type);
            generate_vec_direction(stdout, dim, type);
            generate_vec_angle_between(stdout, dim, type);
            generate_mat_mul(stdout, dim, type);
            generate_mat_mul_by_vec(stdout, dim, type);
        }
    }

    fprintf(stdout, "#endif // LINALG_H\n");

    fprintf(stderr,
            "\033[93mBytes of temp stack used: %zu / %zu (%.4f%%)\033[0m\n",
            varia_temp_size, (size_t)VARIA_TEMP_CAPACITY,
            100 * (float)varia_temp_size / (float)VARIA_TEMP_CAPACITY);
    return 0;
}

// Ideas for additional features:
// - Implement rotation function (+ rotation matrices constructors);
// - Implement variadic matrix multiplication;
// - Add support for non-square matrices (definitions, zero, mul, mul_vec);
// - Implement integer lerping;
// - Implement type casting (same size);
// - Implement for size casting (downsizing first, then upsizing);
// - Add support for rudimentary (hard-coded) swizzling (?);
// - Add support for swizzling using parsing macro (?);
// - Add support for type generic operations and functions (C23< first, maybe
// C99);
// - Print statistics (loc generated, number of functions for each type, etc.).
