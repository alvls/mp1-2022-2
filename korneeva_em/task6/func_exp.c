#include "math_functions.h"

int validate_range_exp(double x)
{
    return 1;
}

double approx_exp(double x, double term, int n)
{
    if (n == 0)
    {
        return 1;
    }

    return term * (x / n);
}