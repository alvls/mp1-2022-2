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