#include "math_func.h"
#include <stdio.h>
#include <math.h>
void sin_series(double x, double eps, int N)
{
	double result = x, current = x, etalon;
	int count = 1, n, tmp;
	etalon = sin(x);
	printf("Эталонное значение: %lf\n", etalon);
	if (eps != -1)
	{
		tmp = 1;
		n = N;
	}
	else
	{
		tmp = N;
		n = 1;
	}
	printf("Кол-во слагаемых     Вычесленная оценка значения фун-и     Разница с эталонным значением\n");
	for (int i = 1;i <= tmp;i++)
	{
		while ((fabs(etalon - result) > eps) && (count < n))
		{
			current *= (-1) * pow(x, 2) / ((2 * count + 1) * 2 * count);
			result += current;
			count++;
		}
		printf("%4d          %15lf                       %15lf\n", count, result, fabs(result - etalon));
		n++;
	}
}
void cos_series(double x, double eps, int N)
{
	double result = 1, current = 1, etalon;
	int count = 1, n, tmp;
	etalon = cos(x);
	printf("Эталонное значение: %lf\n", etalon);
	if (eps != -1)
	{
		tmp = 1;
		n = N;
	}
	else
	{
		tmp = N;
		n = 1;
	}
	printf("Кол-во слагаемых     Вычесленная оценка значения фун-и     Разница с эталонным значением\n");
	for (int i = 1;i <= tmp;i++)
	{
		while ((fabs(etalon - result) > eps) && (count < n))
		{
			current *= (-1) * pow(x, 2) / ((2 * count - 1) * 2 * count);
			result += current;
			count++;
		}
		printf("%4d          %15lf                       %15lf\n", count, result, fabs(result - etalon));
		n++;
	}
}
void exp_series(double x, double eps, int N)
{
	double result = 1, current = 1, etalon;
	int count = 1, n, tmp;
	etalon = exp(x);
	printf("Эталонное значение: %lf\n", etalon);
	if (eps != -1)
	{
		tmp = 1;
		n = N;
	}
	else
	{
		tmp = N;
		n = 1;
	}
	printf("Кол-во слагаемых     Вычесленная оценка значения фун-и     Разница с эталонным значением\n");
	for (int i = 1;i <= tmp;i++)
	{
		while ((fabs(etalon - result) > eps) && (count < n))
		{
			current *= x / count;
			result += current;
			count++;
		}
		printf("%4d          %15lf                       %15lf\n", count, result, fabs(result - etalon));
		n++;
	}
}
void sec_series(double x, double eps, int N)
{
	double result = 1, current = 1, etalon;
	int count = 1, n, tmp;
	if (cos(x) != 0)
	{
		etalon = 1 / cos(x);
		printf("Эталонное значение: %lf\n", etalon);
		if (eps != -1)
		{
			tmp = 1;
			n = N;
		}
		else
		{
			tmp = N;
			n = 1;
		}
		printf("Кол-во слагаемых     Вычесленная оценка значения фун-и     Разница с эталонным значением\n");
		for (int i = 1;i <= tmp;i++)
		{
			while ((fabs(etalon - 1 / result) > eps) && (count < n))
			{
				current *= (-1) * pow(x, 2) / ((2 * count - 1) * 2 * count);
				result += current;
				count++;
			}
			printf("%4d          %15lf                       %15lf\n", count, 1 / result, fabs(1 / result - etalon));
			n++;
		}
	}
	else
		printf("В данной точке невозможно вычислить значение секанса");
}