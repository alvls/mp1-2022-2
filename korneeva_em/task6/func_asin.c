#include "math_functions.h"

int validate_range_asin(double x)
{
    return (fabs(x) <= 1);
}

double approx_asin(double x, double term, int n)
{
    if (n == 0)
    {
        return x;
    }

    return term * ((2. * n - 1) / (2. * n)) * (((2. * (n - 1.) + 1) * (x * x)) / ((2. * n) + 1));
}