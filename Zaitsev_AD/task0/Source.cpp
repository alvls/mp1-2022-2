#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>

int main() {
	setlocale(LC_CTYPE, "rus");
	float x1, x2, y1, y2, r1, r2;
	float diff, amount, length; 
	// distance - сумма радиусов, length - фактическое расстояние между центрами окружностей
	printf("Введите через пробел координаты и радиус первой окружности (x1 y1 r1): ");
	scanf_s("%f %f %f", &x1, &y1, &r1);

	printf("\nВведите через пробел координаты и радиус второй окружности (x2 y2 r2): ");
	scanf_s("%f %f %f", &x2, &y2, &r2);


	diff = fabs(r1-r2);
	amount = r1 + r2;
	length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	printf("\n>>>   ");

	if (x1 == x2 && y1 == y2 && r1 == r2) {
		printf("Окружности совпадают");
	}
	else if (amount == length) {
		printf("Окружности касаются внешним образом");
	}
	else if (diff == length) {
		printf("Окружности касаются внутренним образом");
	}
	else if (length > amount) {
		printf("Окружности не имеют общих точек");
	}
	else if (length == 0 || length < diff) {
		printf("Одна окружность лежит внутри другой");
	}
	else if (diff < length < amount) {
		printf("Окружности пересекаются в двух точках");
	}
	else if (length = 0 || length < diff) {
		printf("Одна окружность находится внутри другой");
	}

	printf("\n\n");
	system("pause");

	return 1;
}