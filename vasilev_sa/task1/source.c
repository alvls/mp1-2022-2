#include <stdio.h>
#include <math.h>
#include <locale.h>

int Count_of_shelfs(float start_h, float t5)
{
	float count = 0, all_height = 40;
	while ((all_height + t5) < start_h)
	{
		count += 1;
		all_height += (40 + t5);
	}
	return (int)count;
}

void main() 
{
	// локализация
	setlocale(LC_ALL, "Russian");
	// объявление переменных
	float h = 0, w = 0, d = 0, t1 = 0.5, t2 = 1.5 , t3 = 1.5, t4 = 1, t5 = 0;
	double value_1, value_2, value_3, value_4, value_5, all_value;
	double material_DSP = 0.00075, material_DVP = 0.0004, material_wood = 0.00065;
	int count;
	// ввод значений с непринятием неверных
	printf("Необходимо внести параметры изделия:\n(если значения вне диапазона, то программа потребует ввести другие)\n");
	while ((h < 180)||(h > 220))
	{
		printf("Введите высоту от 180 до 220 (в см): ");
		scanf_s("%f", &h);
	}
	while ((w < 80)||(w > 120))
	{
		printf("Введите ширину от 80 до 120 (в см): ");
		scanf_s("%f", &w);
	}
	while ((d < 50)||(d > 90))
	{
		printf("Введите глубину от 50 до 90 (в см): ");
		scanf_s("%f", &d);
	}
	while ((t5 <= 0) || (t5 > 10))
	{
		printf("Введите толщину полок до 10 (в см): ");
		scanf_s("%f", &t5);
	}
	// вычисление объёмов
	count = Count_of_shelfs(h, t5);
	value_1 = h * w * t1;								// задняя стенка из ДВП
	value_2 = 2 * (h * d * t2);							// боковые стенки из ДСП
	value_3 = 2 * (w * d * t3);							// крышки из ДСП
	value_4 = h * w * t4;								// двери из дерева
	value_5 = (w * d * t5) * count;						// внутренние полки из ДСП
	// весь объём
	all_value = material_DVP * (value_1) + material_DSP * (value_2 + value_3 + value_5) + material_wood * (value_4);
	// вывод ответа
	printf("\nИтого:\nПолок %d, ", count);
	printf("вес шкафа %.2lf кг \n(при плостности ДСП = 750 кг/кубометр, ДВП = 400 кг/кубометр и дерева = 650 кг/кубометр)\n\n", all_value);
	system("pause");
}