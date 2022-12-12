#include "math_functions.h"

int validate_range_sinh(double x)
{
    return 1;
}

double approx_sinh(double x, double term, int n)
{
    if (n == 0)
    {
        return x;
    }

    return term * ((x * x) / ((2. * n) * ((2. * n) + 1)));
}