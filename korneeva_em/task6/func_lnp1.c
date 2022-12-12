#include "math_functions.h"

int validate_range_lnp1(double x)
{
    return ((x > -1) && (x <= 1));
}

double approx_lnp1(double x, double term, int n)
{
    n += 1;

    if (n == 1)
    {
        return x;
    }
    return (-1) * (term * x * (n - 1.)) / (n);
}