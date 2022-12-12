#include "math_functions.h"

int validate_range_coth(double x)
{
    return ((fabs(x) > 0) && (fabs(x) < M_PI));
}

double approx_coth(double x, double term, int n)
{
    if (n == 0)
    {
        return 1 / x;
    }

    return term * ((4 * bernoulli(2 * n) * (x * x)) / (((2. * n) - 1) * (2. * n) * bernoulli(2 * (n - 1))));
}