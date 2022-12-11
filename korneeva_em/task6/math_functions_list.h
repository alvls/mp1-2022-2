#pragma once

#include "math_functions.h"

MathFunctionInfo math_functions[] = {
   //{"sqrt(1 + x)",  sqrtp1,   approx_sqrtp1},
   //{"ln(1 + x)",    lnp1,     approx_lnp1},
    {"sin",       sin,      approx_sin, 0},
    {"cos",       cos,      approx_cos, 0},
    {"exp",       exp,      approx_exp, 0},
    {"tan",       tan,      approx_tan, 0},
    {"cot",       cot,      approx_cot, 0},
    {"asin",      asin,     approx_asin, 0},
    {"acos",      acos,     approx_acos, M_PI_2},
    {"atan",      atan,     approx_atan, 0},
    {"acot",      acot,     approx_acot, M_PI_2},
    {"sinh",      sinh,     approx_sinh, 0},
    {"cosh",      cosh,     approx_cosh, 0},
   //{"tanh(x)",      tanh,     approx_tanh},
   //{"coth(x)",      coth,     approx_coth},
   //{"asinh(x)",     asinh,    approx_asinh},
    {"atanh",     atanh,    approx_atanh, 0},
   //{"sec(x)",       sec,      approx_sec},
    {"csc(x)",       csc,      approx_csc, 0},
};
#define AVAILABLE_MATH_FUNCTIONS (int)(sizeof(math_functions) / sizeof(MathFunctionInfo))
