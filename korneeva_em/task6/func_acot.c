#include "math_functions.h"

int validate_range_acot(double x)
{
    return (fabs(x) <= 1);
}

double approx_acot(double x, double term, int n)
{
    if (n == 0)
    {
        return -x;
    }

    return term * (-1) * (((2. * (n - 1.) + 1) * (x * x)) / ((2. * n) + 1));
}