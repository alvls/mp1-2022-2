#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Maths.h"

void function(double x, double definition, int n, short choice)
{
	double etalon, now = 0;
	int i = 0;
	double* experiments = (double*)malloc(n * sizeof(double));
	if ((choice == 4) || (choice == 5))
		etalon = choice_of_function1[choice](x + 1);
	else etalon = choice_of_function1[choice](x);
	printf("Эталонное значение: %lf\n", etalon);
	do
	{
		now += choice_of_function2[choice](x, i);
		experiments[i] = now;
		i++;
	} while (((fabs(etalon - now) > definition) || (definition == 5)) && (i < n));
	if (definition != 5)
		printf("Количество слагаемых: %d\nОценка значения: %lf\nРазность между оценкой и эталонным значением: %lf\n", i, experiments[i - 1], etalon - experiments[i - 1]);
	else
	{
		printf("Количество слагаемых   Оценка значения   Разность между оценкой и эталонным значением\n", i, experiments[i - 1], etalon - experiments[i - 1]);
		for (int j = 0; j < i; j++)
		{
			if (j<9)
			printf("%d %29lf %17lf\n", j + 1, experiments[j], etalon - experiments[j]);
			else printf("%d %28lf %17lf\n", j + 1, experiments[j], etalon - experiments[j]);
		}
	}
	free(experiments);
}

void clean_of_buffer()
{
	while (getchar() != '\n');
}

void main()
{
	double x, definition;
	int n = 0, mode;
	short choice;
	char answer;
	setlocale(LC_ALL, "Rus");
	filling();
	printf("Добрый день!\nДанная программа позволяет выполнять расчет значений для некоторого набора функций в заданной точке с заданной погрешностью за счет разложения этих функций в ряд Тейлора.\n");
	do
	{
		printf("Введите номер режима(1 - однократный расчет, 2 - серийный эксперимент): ");
		scanf_s("%d", &mode);
		clean_of_buffer();
		definition = 5;
		if ((mode == 1) || (mode == 2))
		{
			do
			{
				printf("Введите номер функции:\n1. exp(x)\n2. sin(x)\n3. cos(x)\n4. arcsin(x) (-1 <= x <= 1)\n5. lg(x) (-1 < x <= 1)\n6. sqrt(x) (-1 <= x <= 1)\n7. arctg(x) (-1 <= x <= 1)\n8. sh(x)\n9. ch(x)\n10. arsh(x) (-1 < x < 1)\n11. arth(x) (-1 < x < 1)\nВаш выбор ");
				scanf_s("\n%hi", &choice);
				clean_of_buffer();
				if ((choice < 12) && (choice > 0))
				{
					choice--;
					do
					{
						if (mode == 1)
						{
							printf("Введите через пробел значение аргумента (x), точность вычислений и количество слагаемых (ПРИМЕЧАНИЕ: числа с плавающей точкой необходимо вводить с запятой(например 0,6)): ");
							scanf_s("%lf", &x);
							scanf_s("%lf", &definition);
							scanf_s("%d", &n);
							clean_of_buffer();
						}
						else if (mode == 2)
						{
							printf("Введите через пробел значение аргумента (x) и количество слагаемых (ПРИМЕЧАНИЕ: числа с плавающей точкой необходимо вводить с запятой(например 0,6)): ");
							scanf_s("%lf", &x);
							scanf_s("%d", &n);
							clean_of_buffer();
						}
						if ((n > 5000) || (n < 0))
							printf("Количество слагаемых введено некорректно. Пожалуйста, проверьте, не является ли оно слишком большим или слишком маленьким. Хотите ли вы ввести параметры снова, выбрать другую фунццию, сменить режим или завершить работу программы? (Чтобы изменить параметры введите 'x', вызвать другую функцию - 'f', сменить режим - 'm', завершить работу программы - 'e')");
						else if (n == 0) 
							printf("Параметры введены некорректно. Пожалуйста, проверьте соответствие ввода примечанию. Хотите ли вы ввести параметры снова, выбрать другую фунццию, сменить режим или завершить работу программы? (Чтобы изменить параметры введите 'x', вызвать другую функцию - 'f', сменить режим - 'm', завершить работу программы - 'e')");
						else if (!((fabs(x) <= 1) && ((choice == 3) || (choice == 5) || (choice == 6))) && !((fabs(x) < 1) && ((choice == 9) || (choice == 10) || (choice == 4))) && !((x == 1) && (choice == 4)) && !(choice==0) && !(choice == 1) && !(choice == 2) && !(choice == 7) && !(choice == 8))
							printf("Введенное значение аргумента не входит в область определения функции. Хотите ли вы ввести параметры снова, выбрать другую фунццию, сменить режим или завершить работу программы? (Чтобы изменить параметры введите 'x', вызвать другую функцию - 'f', сменить режим - 'm', завершить работу программы - 'e')");
						else
						{
							function(x, definition, n, choice);
							printf("Хотите ли Вы вызвать другую функцию, изменить параметры вызова или сменить режим? (Чтобы вызвать другую функцию, введите 'f', изменить параметры - 'x', сменить режим - 'm', закончить работу программы - 'e')");
						}
						scanf_s("%c", &answer);
						clean_of_buffer();
					} while (answer == 'x');
				}
				else
				{
					printf("Номер режима введен некорректно. Хотите ли Вы вызвать другую функцию (или вызвать эту же снова), сменить режим или закончить работу программы? (Чтобы вызвать другую функцию, введите 'f', сменить режим - 'm', закончить работу программы - 'e')");
					scanf_s("%c", &answer);
					clean_of_buffer();
				}
			} while (answer == 'f');
		}
		else
		{
			printf("Номер режима введен некорректно. Хотите ли вы ввести номер режима снова или закончить работу программы? (Чтобы ввести номер режима снова, введите 'm', закончить работу программы - 'e')\n");
			scanf_s("%c", &answer);
			clean_of_buffer();
		}
	} while (answer == 'm');
	printf("До свидания! Хорошего дня)\n");
	system("pause");
}