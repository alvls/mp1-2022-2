#pragma once

#include "math_functions.h"

MathFunctionInfo math_functions[] = {
    {"sin",   "x",    "",                sin,      approx_sin,    validate_range_sin,    0},
    {"cos",   "x",    "",                cos,      approx_cos,    validate_range_cos,    0},
    {"exp",   "x",    "",                exp,      approx_exp,    validate_range_exp,    0},
    {"sqrt",  "1+x",  ", |x| <= 1",      sqrtp1,   approx_sqrtp1, validate_range_sqrtp1, 0},
    {"ln",    "1+x",  ", -1 < x <= 1",   lnp1,     approx_lnp1,   validate_range_lnp1,   0},
    {"tan",   "x",    ", |x| < pi/2",    tan,      approx_tan,    validate_range_tan,    0},
    {"cot",   "x",    ", |x| < pi",      cot,      approx_cot,    validate_range_cot,    0},
    {"asin",  "x",    ", |x| <= 1",      asin,     approx_asin,   validate_range_asin,   0},
    {"acos",  "x",    ", |x| <= 1",      acos,     approx_acos,   validate_range_acos,   M_PI_2},
    {"atan",  "x",    ", |x| <= 1",      atan,     approx_atan,   validate_range_atan,   0},
    {"acot",  "x",    ", |x| <= 1",      acot,     approx_acot,   validate_range_acot,   M_PI_2},
    {"sinh",  "x",    "",                sinh,     approx_sinh,   validate_range_sinh,   0},
    {"cosh",  "x",    "",                cosh,     approx_cosh,   validate_range_cosh,   0},
    {"tanh",  "x",    ", |x| < pi/2",    tanh,     approx_tanh,   validate_range_tanh,   0},
    {"coth",  "x",    ", 0 < |x| < pi",  coth,     approx_coth,   validate_range_cot,    0},
    {"asinh", "x",    ", |x| < 1",       asinh,    approx_asinh,  validate_range_asinh,  0},
    {"atanh", "x",    ", |x| < 1",       atanh,    approx_atanh,  validate_range_atanh,  0},
    {"sec",   "x",    ", |x| < pi/2",    sec,      approx_sec,    validate_range_sec,    0},
    {"csc",   "x",    ", 0 < |x| < pi",  csc,      approx_csc,    validate_range_csc,    0},
};
#define AVAILABLE_MATH_FUNCTIONS (int)(sizeof(math_functions) / sizeof(MathFunctionInfo))
