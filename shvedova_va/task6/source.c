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
	printf("������� �����, � ������� ���������� ��������� �������� (��������, 1,2345): ");
	scanf_s("%lf", &x);
	system("cls");
	printf("�������� ������� (������� �����):\n1) sin(x)\n2) cos(x)\n3) exp(x)\n4) sec(x)\n");
	scanf_s("%d", &f_type);
	func = f[f_type - 1];
	system("cls");
	printf("�������� ����� (������� �����):\n1) ����������� ������� ������� � �������� �����\n2) �������� �����������\n");
	scanf_s("%d", &regime);
	system("cls");
	switch (regime)
	{
	case 1:
		printf("������� �������� ���������� ���� (>=0,000001): ");
		scanf_s("%lf", &eps);
		system("cls");
		printf("������� ����� ��������� ���� ��� ���������� ������� (�� 1 �� 1000): ");
		scanf_s("%d", &n);
		system("cls");
		func(x, eps, n);
		break;
	case 2:
		printf("������� ����� ������������� (�� 1 �� 25): ");
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