#include "math_functions.h"

int validate_range_atanh(double x)
{
    return (fabs(x) < 1);
}

double approx_atanh(double x, double term, int n)
{
    if (n == 0)
    {
        return x;
    }

    return term * ((((2. * n) - 1) * (x * x)) / ((2. * n) + 1));
}