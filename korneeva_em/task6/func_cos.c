#include "math_functions.h"

int validate_range_cos(double x)
{
    return 1;
}

double approx_cos(double x, double term, int n)
{
    if (n == 0)
    {
        return 1;
    }

    return term * (-1) * ((x * x) / (((2. * n) - 1) * (2. * n)));
}