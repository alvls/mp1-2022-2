#include "math_functions.h"

int validate_range_sec(double x)
{
    return (fabs(x) < M_PI_2);
}

double approx_sec(double x, double term, int n)
{
    if (n == 0)
    {
        return 1;
    }

    return (term * (-1) * euler(2 * n) * (x * x)) / (((2. * n) - 1) * (2. * n) * euler(2 * (n - 1)));
}