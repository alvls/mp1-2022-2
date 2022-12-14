#include "math_functions.h"

int validate_range_asinh(double x)
{
    return (fabs(x) < 1);
}

double approx_asinh(double x, double term, int n)
{
    if (n == 0)
    {
        return x;
    }

    return term * (-1) * ((2. * n - 1) / (2. * n)) * (((2. * (n - 1.) + 1) * (x * x)) / ((2. * n) + 1));
}