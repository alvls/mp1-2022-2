#include <math.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h> //библиотека для генерации случайных чисел//


void main()
{
	setlocale(LC_ALL, "Rus");

	int cnt, num, user_num, v1, v2, user_v;
	float answ, answ1, dist; //переменные для алгоритма бинарного поиска//
	char user_answ;

	printf("Добро пожаловать в игру 'Угадай число'!\n\n");
	printf("В какой вариант игры вы бы хотели сыграть,\nВ первый или во второй?\n(Введите соответствующее число):\n"); //выбор режима игры//
	scanf_s("%d", &user_v);

	if (user_v == 1)
	{
		srand(time(0));
		num = 1 + rand() % 1000;
		printf("\nПодсказка: %d\n\n", num);
		printf("Я загадал число от 1 до 1000\nВведите число, а я буду говорить - больше или меньше:\n");
		while (1)
		{
			scanf_s("%d", &user_num);
			if (user_num > num)
			{
				printf("Загаданное число меньше!\n");
			}
			else if (user_num < num)
			{
				printf("Загаданное число больше!\n");
			}
			else
			{
				printf("Угадали!\n");
				break;
			}
		}
	}
	else if (user_v == 2)
	{
		printf("Я гарантированно угадаю ваше число менее, чем за 10 попыток!\nВведите загаданное вами число (от 1 до 1000)\n");
		scanf_s("%d", &user_num);
		if ((1 <= user_num) && (user_num < 1000)) //проверка пользовательского числа//
		{
			printf("Для ответа вводите следущие символы: '<', '>', '=' \n");
			answ1 = 1000;
			dist = 0;
			answ = 500;
			cnt = 0;
			while (1) //здесь используется алгоритм бинарного поиска, для более быстрого поиска числа//
			{
				printf("Ваше число: %f?\n", answ);
				scanf_s(" %c", &user_answ);
				if (user_answ == '>')
				{
					dist = abs(answ1 - answ);
					answ1 = answ;
					answ = answ + (dist / 2);
					cnt++;
				}
				else if (user_answ == '<')
				{
					dist = abs(answ1 - answ);
					answ1 = answ;
					answ = answ - (dist / 2);
					cnt++;
				}
				else if (user_answ == '=')
				{
					printf("Ура!\nВаше число: %f\nКоличесвто попыток: %d\n", answ, cnt);
					break;
				}
				else
				{
					printf("Для ответа вводите следущие символы : '<', '>', '=' \n");
				}
			}
		}
		else
		{
			printf("Введите число от 1 до 1000!\n");
		}
	}
	else
	{
		printf("Ошибка выбора!\nВведите 1 или 2\n");
	}
}
