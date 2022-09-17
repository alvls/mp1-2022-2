#include <stdio.h>
#include <math.h>
void main()
{
	double R1, R2, x1, y1, x2, y2, d;
	printf("введите R1");
	scanf_s("%lf", &R1);
	printf("введите координаты x1 и y1");
	scanf_s("%lf %lf", &x1, &y1);
	printf("введите R2");
	scanf_s("%lf", &R2);
	printf("введите координаты x2 и y2");
	scanf_s("%lf %lf", &x2, &y2);
	d = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)); //расстояние между центрами окружностей
	if ((R1 < R2 + d) && (R2 < R1 + d) && (d < R1 + R2))
		printf("окружности пересекаются");
	if (abs(R1 - R2) == d)
		printf("окружности касаются внутренним образом");
	if (R1 + R2 == d)
		printf("окружности касаются внешним образом");
	if (R1 + R2 < d)
		printf("окружности лежат вне друг друга");
	if ((R1 + d < R2) || (R2 + d < R1))
		printf("окружности расположены одна внутри другой");
	if ((R1 == R2) && (x1 == x2) && (y1 == y2))
		printf("окружности наложены друг на друга");
	system("pause");
}

