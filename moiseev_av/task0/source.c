#include <math.h>
#include <stdio.h>
#include <locale.h>


void main()
{
	setlocale(LC_ALL, "Rus");
	float x1, y1, r1, x2, y2, r2;
	float dist;

	printf("Введите x и y первой окружности, а затем её радиус: ");
	scanf("%f %f %f", &x1, &y1, &r1);	
	printf("Введите x и y второй окружности, а затем её радиус: ");
	scanf("%f %f %f", &x2, &y2, &r2);

	dist = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)); //функция pow - возведение в квадрат

	if ((r1 = r2) && (y1 = y2) && (x1 = x2)) // && - and
	{
	printf("Окружности совпадают, одна лежит на другой");
	}
	 else if (dist > (r1 + r2))
	{
		printf("Окружности отделены");
	}
	else if (dist < abs(r1 - r2))
	{
		printf("Одна окружность находится в другой");
	}
	else if (dist = abs(r1 - r2))
	{
		printf("Одна окружность находится в другой и при этом, они имеют общую точку");
	}
	else if (abs(r1 - r2) < dist < (r1 + r2))
	{
		printf("Окружности пересекаются, имеют две общие точки");
	}
	else if (dist = (r1 + r2))
	{
		printf("Окружности соприкасаются");
	}
}
