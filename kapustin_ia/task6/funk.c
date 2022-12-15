#include "funk.h"
#include <math.h>
#define M_PI            3.14159265358979323846
typedef double (*PFunc) (double, double, int, int*);
double sinus(double x0, double epsilon, int n1, int* count)
{
	double sum1 , sum2, row_elem;
	int swap_sign, count_iteration, coef;
	swap_sign = 1;
	double (*inexact)(double, double);
	inexact = inexactness;
	count_iteration = 0;
	sum1 = 0;
	sum2 = 10;
	coef = 1;
	x0 = x0 * 3.14 / 180; // deg in rad
	row_elem = x0;
	while (fabs(sum1 - sum2) >= epsilon && count_iteration < n1)
	{
		sum2 = sum1;
		sum1 = sum1 + swap_sign * row_elem;
		if (epsilon == 0)
		{
			printf("%-5d                                         %-5.20lf                                              %-8.20lf\n", count_iteration + 1, sum1, sum1 - sinl(x0));
		}
		row_elem = row_elem * (x0 / (coef + 1)) * (x0 / (coef + 2));
		coef = coef + 2;
		count_iteration++;
		swap_sign = -swap_sign;
	} 
	*count = count_iteration;
	return (sum1);
}

double cosinus(double x0, double epsilon, int n1, int* count)
{
	double sum1 = 0, sum2 = 10, row_elem, etal;
	int swap_sign = 1, count_eteration = 0, coef = 0;
	row_elem = 1;
	x0 = x0 * 3.14 / 180;
	etal = cosl(x0);
	while (fabs(sum1 - sum2) >= epsilon && count_eteration <= n1)
	{
		sum2 = sum1;
		sum1 = sum1 + swap_sign * row_elem;
		if (epsilon == 0)
		{
			printf("%-5d                                         %-5.20lf                                              %-8.20lf\n", count_eteration + 1, sum1, sum1 - etal);
		}
		row_elem = row_elem * (x0 / (coef + 1)) * (x0 / (coef + 2));
		coef = coef + 2;
		count_eteration++;
		swap_sign = -swap_sign;
	} 
	*count = count_eteration;
	return(sum1);
}

double expo(double x0, double epsilon, int n1, int* count)
{
	double sum1 = 0, sum2 = 10, row_elem;
	int count_eteration = 0;
	int coef = 0;
	sum1 = 0;
	sum2 = 10;
	coef = 0;
	row_elem = 1;
	while ((count_eteration < n1) && (fabs(sum1 - sum2) >= epsilon))
	{
		count_eteration++;
		sum2 = sum1;
		sum1 = sum1 + row_elem;
		if (epsilon == 0)
		{
			printf("%-5d                                         %-5.20lf                                                   %-8.20lf \n", count_eteration , sum1, sum1 - exp(x0));
		}
		row_elem = row_elem * (x0 / (coef + 1));
		coef = coef + 1;
	}
	*count = count_eteration;
	return(sum1);
}

double arccos(double x0, double epsilon, int n1, int* count)
{
	double sum1 = 0, sum2 = 10, row_elem;
	int count_eteration = 0, coef = 0;
	sum1 = 0;
	sum2 = 10;
	coef = 1;
	if (x0 < -1 || x0>1)
	{
		printf("                                Введено неверное значение!!! Попробуйте снова\n");
	} 
	else
	{
		row_elem = x0;
		while (fabs(sum1 - sum2) >= epsilon && count_eteration < n1)
		{
			sum2 = sum1;
			sum1 = sum1 + row_elem;
			if (epsilon == 0)
			{
				printf("%-5d                                         %-5.20lf                                              %-8.20lf\n", count_eteration + 1, 3.14/2 - sum1,3.14/2 - sum1 - acosl(x0));
			}
			row_elem = row_elem * (x0 / (coef + 1)) * (x0 / (coef + 2)) * coef * coef;
			coef = coef + 2;
			count_eteration++;
		}
		sum1 = 3.14 / 2 - sum1;
		*count = count_eteration;
		return(sum1);
	}
}
double inexactness(double meaning, double math_meaning)
{
	double inexact;
	inexact = math_meaning - meaning;
	return(inexact);
}
double math_meaning(int numb_f, double meaning)
{
	if (numb_f == 0)
	{
		meaning = meaning * M_PI / 180;
		return (sin(meaning));
	}
	if (numb_f == 1)
	{
		meaning = meaning * M_PI / 180;
		return (cos(meaning));
	}
	if (numb_f == 2)
	{
		return(exp(meaning));
	}
	if (numb_f == 3)
	{
		return(acos(meaning));
	}
}