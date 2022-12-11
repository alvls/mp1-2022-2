#include "math_functions.h"

// sigma (-1)^n * (x^(2n-1))/(2n-1)!)

double approx_sin(double x, double term, int n)
{
    if (n == 0)
    {
        return x;
    }
    return term * (-1) * ((x * x) / ((2 * n) * ((2 * n) + 1)));
}