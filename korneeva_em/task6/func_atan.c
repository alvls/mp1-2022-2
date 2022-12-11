#include "math_functions.h"

double approx_atan(double x, double term, int n)
{
    if (n == 0)
    {
        return x;
    }
    return term * (-1) * (((2 * n - 1) * (x * x)) / ((2 * n) + 1));
}
