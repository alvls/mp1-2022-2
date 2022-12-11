#pragma once

#include "math_functions.h"

#define MIN_PRECISION 0.000001F
#define N_MIN 1
#define N_MAX 1000
#define NMAX_MIN 1
#define NMAX_MAX 25

void mode_single(MathFunctionInfo* func, double x, int N, double precision);
void mode_serial(MathFunctionInfo* func, double x, int NMax);