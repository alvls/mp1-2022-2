#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>

#include <stdio.h>;
#include <math.h>;


void main() {
	double x1, x2, y1, y2, r1, r2, distance;
	setlocale(LC_ALL, "Rus");

	printf("Условие: r1 >= r2! Для удобства\n");

	printf("Введите x1, y1, r1\n");
	scanf("%lf %lf %lf", &x1, &y1, &r1);

	printf("Введите x2, y2, r2\n");
	scanf("%lf %lf %lf", &x2, &y2, &r2);

    distance = sqrt(pow(x1 - x2,2) + pow(y1 - y2,2));
	s
	if ((distance < r1 + r2 && distance > r1 - r2) && (distance != 0)) {
		printf("Окружности имеют 2 общие точки");
	}
	else if (r1 + r2 < distance) {
		printf("Окружности не имеют общих точек, одна не лежит в другой");
	}
	else if ((x1 == x2 && y1 == y2) && r1 != r2) {
		printf("Окружности концентрические, не имеют общих точек");
	}
	else if ((x1 == x2 && y1 == y2) && r1 == r2) {
		printf("Окружности наложены друг на друга(беск. кол-во общ точек)");
	}
	else if (distance < r1 - r2) {
		printf("Одна окружность лежит в другой, общих точек нет, центры не совпадают");
	}
	else if (distance == r1 - r2) {
		printf("Окружности касаются внутри");
	}
	else if (distance == r1 + r2) {
		printf("Окружности имеют 1 общую точку");
	}

	scanf("%lf %lf %lf", &x2, &y2, &r2); // для того, чтобы консоль не закрылась и можно было увидеть результат


}
