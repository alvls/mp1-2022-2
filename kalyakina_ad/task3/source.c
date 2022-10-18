#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
int digits_controle(int i)
{
	int m, k;
	int a[10];
	m = 0;
	for (k = 0; k <= 9; k++) a[k] = 0;
	while (i > 0)
	{
		a[i % 10]++;
		i /= 10;
	}
	for (k = 0; k <= 9; k++)
		if (a[k] > 1) m++;
	return m;
}

void main()
{
	int num_c, num_p;
	int j, l;
	int cows, bulls, s;
	short n, answer;
	int* digits_num_p = (int*)malloc(1 * sizeof(int));
	int* digits_num_c = (int*)malloc(1 * sizeof(int));
	setlocale(LC_ALL, "Rus");
	printf("Добрый день! Хотите ли вы сыграть в игру 'Быки и коровы'? (Если да, то введите '1', иначе - '0')\n");
	scanf_s("%hd", &answer);
	while (answer == 1)
	{
		s = 0;
		printf("Начинаем!\nЕсли захотите сдаться, то просто введите '-1'\nВведите количество цифр в числе ");
		scanf_s("\n%hd", &n);
		if (n == -1)
		{
			printf("Спасибо за игру\n");
			system("pause");
			return;
		}
		while (!((n > 1) && (n < 6)))
		{
			printf("Введен неверный порядок числа\n");
			printf("Введите количество цифр в числе ");
			scanf_s("\n%hd", &n);
			if (n == -1)
			{
				printf("Спасибо за игру\n");
				system("pause");
				return;
			}
		};
		digits_num_p = (int*)realloc(digits_num_p, n * sizeof(int));
		digits_num_c = (int*)realloc(digits_num_c, n * sizeof(int));
		n--;
		srand(time(NULL));
		do
		{
			num_c = (int)(pow(10, n)) + rand() % (int)(9.9999 * pow(10, n) - pow(10, n) + 1);
		} while (digits_controle(num_c) != 0);
		l = num_c;
		for (j = n; j >= 0; j--)
		{
			digits_num_c[j] = l % 10;
			l = l / 10;
		}
		do
		{
			cows = 0;
			bulls = 0;
			printf("Ваш вариант ответа: ");
			scanf_s("\n%d", &num_p);
			if (num_p == -1)
			{
				printf("Спасибо за игру\n");
				system("pause");
				return;
			}
			if (digits_controle(num_p) != 0)
			{
				printf("Число введено некорректно. Введите число, состоящее из неповторяющихся цифр\n");
			}
			else
			{
				l = num_p;
				for (j = n; j >= 0; j--)
				{
					digits_num_p[j] = l % 10;
					l = l / 10;
				};

				for (l = 0; l <= n; l++)
				{
					for (j = 0; j <= n; j++)
					{
						if (digits_num_c[l] == digits_num_p[j])
						{
							if (l == j) bulls++;
							else cows++;
						}
					}
				}
				s++;
				printf("Быков: %d;   Коров: %d\n", bulls, cows);
			}
		} while (num_c != num_p);
		printf("Вы выиграли!Количество попыток : % d\n", s);
		printf("Хотите сыграть ещё? (Если да, то введите '1', иначе - '0') ");
		scanf_s("\n%hd", &answer);
	}
	printf("Спасибо за игру\n");
	system("pause");
}