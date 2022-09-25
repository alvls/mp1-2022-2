#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	double h, w, d, massa, t1, t2, t3, back_wall, side_walls, lids, doors, shelves;
	int cnt, p1, p2, p3;
	t1 = 0.005; // t1, t2, t3 - толщина  в метрах
	t2 = 0.015;
	t3 = 0.01;
	p1 = 800; // примерная плотность ДСП (кг/м2)
	p2 = 820; // примерная плотность ДВП (кг/м2)
	p3 = 600; // примерная плотность дерева (кг/м2)
	printf("Введите размер шкафа (высоту, ширину и глубину(в метрах))");
	scanf_s("%lf %lf %lf", &h, &w, &d);
	if ((h > 1.8) && (h < 2.2) && (w > 0.8) && (w < 1.2) && (d > 0.5) && (d < 0.9)) {
		cnt = (h / 0.4); // количество полок
		back_wall = h * w * t1; // объемы деталей
		side_walls = 2 * h * d * t2;
		lids = 2 * w * d * t2;
		doors = 2 * h * w * t3;
		shelves = cnt * d * w * t2;
		massa = (back_wall * p2) + (side_walls * p1) + (lids * p1) + (doors * p3) + (shelves * p1);
		printf("Масса шкафа равна %lf", massa);
	}
	else {
		printf("Неверные данные");
	}
	system("pause");
}










