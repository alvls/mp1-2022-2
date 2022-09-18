#include <stdio.h>
#include <iostream>
#include <locale>

int main()
{
	setlocale(LC_ALL, "Russian");

	double d, R, r, x, y, X, Y;
	printf("Введите r, x, y\n");
	scanf_s("%lf %lf %lf", &r, &x, &y);
	printf("Введите R, X, Y\n");
	scanf_s("%lf %lf %lf ", &R, &X, &Y);
	if (((X - x) * (X - x) + (Y - y) * (Y - y)) > R + r)
		printf("Окружности не касаются\n");
	else if (((X - x) * (X - x) + (Y - y) * (Y - y)) < R - r)
		printf("Одна окружность находитс¤ в другой\n");
	else if (((X - x) * (X - x) + (Y - y) * (Y - y)) == R - r)
		printf("Одна окружность касаетс¤ другой изнутри\n");
	else if (R - r < ((X - x) * (X - x) + (Y - y) * (Y - y)) < R + r)
		printf("Окружности пересекаются\n");
	else if (((X - x) * (X - x) + (Y - y) * (Y - y)) == R + r)
		printf("Окружности касаются\n");
	return 0;
}
