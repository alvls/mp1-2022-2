long binomial_coefficient(int n, int k)
{
    long res = 1;

    for (int i = 1; i <= n - k; i++)
    {
        res *= (double)(k + i) / i;
    }

    return res;
}

int sign(int number)
{
    return number >= 0 ? 1 : -1;
}