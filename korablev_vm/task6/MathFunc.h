#define _USE_MATH_DEFINES 
#include <math.h>

void GetSin(double x, double rate, int N)
{
	int i = 2;
	double ethalon = sin(x);
	double answ = x;
	double temp = x;
	for (i = 2; (i <= N) && (fabs(ethalon - answ) > rate); i++)
	{
		temp *= (-1) * x * x / ((2 * i - 1) * (2 * i - 2));
		answ += temp;
	}
	printf("%16d   %26.6lf   %20.6lf\n", i - 1, answ, fabs(ethalon - answ));
}
void GetCos(double x, double rate, int N)
{
	int i;
	double ethalon = cos(x);
	double answ = 1;
	double temp = 1;
	for (i = 2; (i <= N) && (fabs(ethalon - answ) >= rate); i++)
	{
		temp *= (-1) * x * x / ((2 * i - 2) * (2 * i - 3));
		answ += temp;
	}
	printf("%16d   %26.6lf   %32.6lf\n", i - 1, answ, fabs(ethalon - answ));
}
void GetExp(double x, double rate, int N)
{
	int i;
	double ethalon = exp(x);
	double answ = 1;
	double temp = 1;
	for (i = 2; (i <= N) && (fabs(ethalon - answ) > rate); i++)
	{
		answ *= x / (i - 1);
		answ += temp;
	}
	printf("%16d   %26.6lf   %32.6lf\n", i - 1, answ, fabs(ethalon - answ));
}
void GetArctg(double x, double rate, int N)
{
	int i;
	double ethalon = atan(x);
	double answ = x;
	double temp = x;
	for (i = 2; (i <= N) && (fabs(ethalon - answ) > rate); i++)
	{
		temp *= (-1) * (x * x) * (2 * (i - 1) + 1) / (2 * i + 1);
		answ += temp;
	}
	printf("%16d   %26.6lf   %32.6lf\n", i - 1, answ, fabs(ethalon - answ));
}
void GetCosh(double x, double rate, int N)
{
	int i;
	double ethalon = cosh(x);
	double answ = 1;
	double temp = 1;
	for (i = 2; (i <= N) && (fabs(ethalon - answ) > rate); i++)
	{
		temp *= (x / (i - 1));
		if (i % 2 == 1)
			answ += temp;
	}
	printf("%16d   %26.6lf   %32.6lf\n", i - 1, answ, fabs(ethalon - answ));
}
void GetSh(double x, double rate, int N)
{
	int i;
	double ethalon = sinh(x);
	double answ = x;
	double temp = x;
	for (i = 2; i <= N; i++)
	{
		temp *= ((x * x) / ((2 * i - 2) * (2 * i - 1)));
		answ += temp;
	}
	N = i - 1;
	printf("%16d   %26.6lf   %32.6lf\n", i - 1, answ, fabs(ethalon - answ));
}

//sec(x)
double factorial(int n)
{
	double answer = 1;
	for (int i = 2; i <= n; i++)
		answer *= i;
	return answer;
}
double arr_b(int i)
{
	if (i == 0)
		return 1;
	int N = i+1;
	double* B = calloc((double)N, sizeof(double));
	double temp, answ;
	double a, b, c, d, sch;
	B[0] = 1;
	if (((N-1) % 2 != 0)&&(N-1 != 1))
		return 0;
	for (int n = 1; n < N; n++)
	{
		temp = 0;
		if ((n > 2) && (n % 2 == 1))
			continue;
		for (int k = 0; k < n; k++)
		{
			a = factorial(n);
			b = factorial(k);
			c = factorial(n - k);
			sch = (a) / (b * c);
			d = B[k];
			temp += sch * d / (n - k + 1);
		}
		B[n] = -temp;
		answ = B[n];
	}
	return answ;
}