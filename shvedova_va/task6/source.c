#include <stdio.h>
#include <locale.h>
#include <math.h>
#include "math_func.h"
#define arr_size 4
int main()
{
	typedef double (*functions)(double, double, int);
	double x;
	double eps;
	int n, f_type, regime;
	functions func;
	void (*f[arr_size])(double, double, int) = { sin_series, cos_series, exp_series, sec_series };
	setlocale(LC_ALL, "rus");
	printf("Введите точку, в которой необходимо вычислить значение (например, 1,2345): ");
	scanf_s("%lf", &x);
	system("cls");
	printf("Выберите функцию (введите номер):\n1) sin(x)\n2) cos(x)\n3) exp(x)\n4) sec(x)\n");
	scanf_s("%d", &f_type);
	func = f[f_type - 1];
	system("cls");
	printf("Выберите режим (введите номер):\n1) однократный рассчет функции в заданной точке\n2) серийный эксперимент\n");
	scanf_s("%d", &regime);
	system("cls");
	switch (regime)
	{
	case 1:
		printf("Введите точность вычисления ряда (>=0,000001): ");
		scanf_s("%lf", &eps);
		system("cls");
		printf("Введите число элементов ряда для выполнения расчета (от 1 до 1000): ");
		scanf_s("%d", &n);
		system("cls");
		func(x, eps, n);
		break;
	case 2:
		printf("Введите число экспериментов (от 1 до 25): ");
		scanf_s("%d", &n);
		system("cls");
		func(x, -1, n);
		break;
	default:
		break;
	}
	system("pause");
	return 0;
}