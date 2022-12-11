#include "calc_modes.h"

// максимальное количство экспериментов NMax = 1000 по условию,
// числа Ѕернулли с индексом 2n используютс€ при расчете тангенсов,
// значит, нужно иметь в расположении числа Ѕернулли от 0 до 2*NMax = 2000 включительно

double bernoulli_numbers[NMAX_MAX * 2 / 2] = { 1 };
int calculated_bernoulli_numbers = 0;

double calculate_bernoulli_number(int n)
{
    double result = 0;

    for (int k = 1; k <= n; k++)
    {
        result += binomial_coefficient(n + 1, k + 1) * bernoulli(n - k);
    }

    result *= (-1.) / (n + 1);

    bernoulli_numbers[n / 2] = result;
    calculated_bernoulli_numbers++;

    return result;
}

double bernoulli(int n)
{
    if (n == 1)
    {
        return -0.5;
    }
    if (n % 2 != 0)
    {
        return 0;
    }

    n /= 2;

    if (n <= calculated_bernoulli_numbers)
    {
        return bernoulli_numbers[n];
    }

    return calculate_bernoulli_number(n * 2);
}