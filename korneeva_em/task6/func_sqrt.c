#include "math_functions.h"

int validate_range_sqrtp1(double x)
{
    return (fabs(x) <= 1);
}

double approx_sqrtp1(double x, double term, int n)
{
    if (n == 0)
    {
        return 1;
    }

    return term * (x * (1.5 - n) / n);
}