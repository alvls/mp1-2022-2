#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define a 0
#define d 1000
void main()
{
	int i = RAND_MAX;
	int pm;
	int rad = 0;
	int b, max, min, medium, n;
	int summ = 0;
	setlocale(LC_ALL, "RUS");
	printf("Выберите режим и введите номер: 1 -  если ПК загадывает число; 2 - если вы загадываете, а ПК пытается угадать\n");
	scanf("%i", &pm);
	switch (pm)
	{
	case 1:
		setlocale(LC_ALL, "RUS");
		srand((int)time(NULL));
		for (i = 0; i < 1; i++) {
			rad = rand() % (d - a) + a;
		}
		do
		{
		c:
			printf("Введите число\n");
			scanf("%i", &b);
			if (b == rad)
			{
				printf("Угадали!\n"); summ++;
			}

			if (b > rad)
			{
				printf("Загаданное число меньше\n"); summ++; goto c;
			}
			if (b < rad)
			{
				printf("Загаданное число больше\n"); summ++; goto c;
			}
			{
				printf("Правильное число = %i\n", rad);
				printf("Попыток = %i\n", summ);
				break;
			}
		} while (1);
	case 2:
		setlocale(LC_ALL, "RUS");
		min = 0;
		max = 1000;
		medium = 500;
		n = 0;
		char op;
		while (1)
		{
			printf("Это число = %i?\n", medium);
			printf("Если да, то нажмите '=', если меньше - '<', если больше - '>'\n");
			scanf_s(" %c", &op);
			if (op == '>')
			{
				min = medium;
				medium = (medium + max) / 2;
				n++;
			}
			else if (op == '<')
			{
				max = medium;
				medium = (medium + min) / 2;
				n++;
			}
			else if (op = '=')
			{
				n++;
				printf("Вы загадали число = %i\n", medium);
				printf("Число попыток = %i\n", n);
				break;
			}
		}
		system("pause");

	}
}





