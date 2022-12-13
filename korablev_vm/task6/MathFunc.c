 #include "MathFunc.h"

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
		temp *= x / (i - 1);
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
		temp *= ((-1) * (x * x) * (2 * (i-1) - 1)) / (2 * (i-1) + 1);
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
//вспомогательные функции
double factorial(int n)//факториал
{
	double answer = 1;
	for (int i = 2; i <= n; i++)
		answer *= i;
	return answer;
}
