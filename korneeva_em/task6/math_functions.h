#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

typedef double (*MathFunction)(double x); 
typedef double (*ApproximateMathFunction)(double x, double term, int n); 

typedef struct _MathFunctionInfo
{
	char name[16];
	MathFunction std_func;
	ApproximateMathFunction approx_func;
	double initial_value;
} MathFunctionInfo;

double acot(double x);
double cot(double x);
double csc(double x);

double bernoulli(int n);
long long euler(int n);

int sign(int number);
long long factorial(int n);
long binomial_coefficient(int n, int k);
double to_radians(double x);

/* ** */ double approx_sin(double x, double term, int n);
/* ** */ double approx_cos(double x, double term, int n);
/* ** */ double approx_exp(double x, double term, int n);
/* 00 */// double approx_sqrtp1(double x, double term, int n);
/* 01 */// double approx_lnp1(double x, double term, int n);
/* 02 */ double approx_tan(double x, double term, int n);
/* 03 */ double approx_cot(double x, double term, int n);
/* 04 */ double approx_asin(double x, double term, int n);
/* 05 */ double approx_acos(double x, double term, int n);
/* 06 */ double approx_atan(double x, double term, int n);
/* 07 */ double approx_acot(double x, double term, int n);
/* 08 */ double approx_sinh(double x, double term, int n);
/* 09 */ double approx_cosh(double x, double term, int n);
/* 10 */// double approx_tanh(double x, double term, int n);
/* 11 */// double approx_coth(double x, double term, int n);
/* 12 */// double approx_asinh(double x, double term, int n);
/* 13 */ double approx_atanh(double x, double term, int n);
/* 14 */// double approx_sec(double x, double term, int n);
/* 15 */ double approx_csc(double x, double term, int n);
