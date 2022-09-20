#include <stdio.h>
#include <math.h>
#include <locale.h>
void main()
{
	setlocale(LC_ALL, "Rus");
	double r, R, x1, x2, y1, y2;
	double distance, sum_r;
	printf("Введите координаты центров и радиусы окружностей: ");
	scanf_s("%lf %lf %lf %lf %lf %lf", &x1, &y1, &r, &x2, &y2, &R);
	sum_r = r + R;
	distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	if (distance == 0 && r == R)
	{
		printf("Окружности совпадают");
	}
	else {
		if (distance > sum_r)
		{
			printf("Окружности расположены на расстоянии друг от друга ");
		}
		else {
			if (distance == 0 || distance < fabs(r - R) && x1 == x2 && y1 == y2)
			{
				printf("Малая окружность находится внутри большой ");
			}
			else {
				if (sum_r == fabs(r - R))
				{
					printf("Окружности внешне касаются друг друга ");
				}
				else {
					if (distance == fabs(r - R))
					{
						printf("Окружности внутренне касаются ");
					}
					else {
						if (distance < sum_r)
						{
							printf("Окружности пересекаются ");
						}
						system("pause");
					}
				}
			}
		}
	}
}