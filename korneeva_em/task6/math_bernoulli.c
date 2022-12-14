#include "calc_modes.h"

// ������������ ��������� ������������� NMax = 1000 �� �������,
// ����� �������� � �������� 2n ������������ ��� ������� ���������,
// ������, ����� ����� � ������������ ����� �������� �� 0 �� 2*NMax = 2000 ������������

double bernoulli_numbers[N_MAX * 2 / 2] = { 1 };
int calculated_bernoulli_numbers = 0;

double calculate_bernoulli_number(int n)
{
    double result = 0;

    for (int k = 1; k <= n; k++)
    {
        result += binomial_coefficient(n + 1, k + 1) * bernoulli(n - k);
    }

    result *= (-1.) / (n + 1.);

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