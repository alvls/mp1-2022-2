#include "math_functions.h"

double acot(double x)
{
	return M_PI_2 - atan(x);
}

double cot(double x)
{
	return tan(M_PI_2 - x);
}

double csc(double x)
{
	return 1 / sin(x);
}

double sec(double x)
{
	return 1 / cos(x);
}

double coth(double x)
{
	return 1 / tanh(x);
}

double lnp1(double x)
{
	return log(1 + x);
}

double sqrtp1(double x)
{
	return sqrt(1 + x);
}