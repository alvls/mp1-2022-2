#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

typedef double (*MathFunction)(double x);
typedef double (*ApproximateMathFunction)(double x, double term, int n);

typedef int (*RangeValidator)(double x);

typedef struct _MathFunctionInfo
{
	char name[16];
	char usage[8];
	char range[16];
	MathFunction std_func;
	ApproximateMathFunction approx_func;
	RangeValidator validate_range;
	double initial_value;
} MathFunctionInfo;

double acot(double x);
double cot(double x);
double csc(double x);
double sec(double x);
double coth(double x);
double lnp1(double x);
double sqrtp1(double x);

double bernoulli(int n);
long long euler(int n);

int sign(int number);
long binomial_coefficient(int n, int k);

////////////////////////////////////////////////////////////////////////
/* ** */ double approx_sin(double x, double term, int n);
/* ** */ double approx_cos(double x, double term, int n);
/* ** */ double approx_exp(double x, double term, int n);
/* 00 */ double approx_sqrtp1(double x, double term, int n);
/* 01 */ double approx_lnp1(double x, double term, int n);
/* 02 */ double approx_tan(double x, double term, int n);
/* 03 */ double approx_cot(double x, double term, int n);
/* 04 */ double approx_asin(double x, double term, int n);
/* 05 */ double approx_acos(double x, double term, int n);
/* 06 */ double approx_atan(double x, double term, int n);
/* 07 */ double approx_acot(double x, double term, int n);
/* 08 */ double approx_sinh(double x, double term, int n);
/* 09 */ double approx_cosh(double x, double term, int n);
/* 10 */ double approx_tanh(double x, double term, int n);
/* 11 */ double approx_coth(double x, double term, int n);
/* 12 */ double approx_asinh(double x, double term, int n);
/* 13 */ double approx_atanh(double x, double term, int n);
/* 14 */ double approx_sec(double x, double term, int n);
/* 15 */ double approx_csc(double x, double term, int n);


////////////////////////////////////////////////////////////////////////
/* ** */ int validate_range_sin(double x);
/* ** */ int validate_range_cos(double x);
/* ** */ int validate_range_exp(double x);
/* 00 */ int validate_range_sqrtp1(double x);
/* 01 */ int validate_range_lnp1(double x);
/* 02 */ int validate_range_tan(double x);
/* 03 */ int validate_range_cot(double x);
/* 04 */ int validate_range_asin(double x);
/* 05 */ int validate_range_acos(double x);
/* 06 */ int validate_range_atan(double x);
/* 07 */ int validate_range_acot(double x);
/* 08 */ int validate_range_sinh(double x);
/* 09 */ int validate_range_cosh(double x);
/* 10 */ int validate_range_tanh(double x);
/* 11 */ int validate_range_coth(double x);
/* 12 */ int validate_range_asinh(double x);
/* 13 */ int validate_range_atanh(double x);
/* 14 */ int validate_range_sec(double x);
/* 15 */ int validate_range_csc(double x);
