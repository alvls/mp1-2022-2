// Если пытаться как-то сохранять факториалы и не считать их
// каждый раз, то в определенный момент они просто не влезут в тип
long binomial_coefficient(int n, int k)
{
    long res = 1;

    for (int i = 1; i <= n - k; i++)
    {
        res *= (double)(k + i) / i;
    }

    return res;
}