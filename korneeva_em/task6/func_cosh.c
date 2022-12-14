#include "math_functions.h"

int validate_range_cosh(double x)
{
    return 1;
}

double approx_cosh(double x, double term, int n)
{
    if (n == 0)
    {
        return 1;
    }

    return term * ((x * x) / (((2. * n) - 1) * (2. * n)));
}