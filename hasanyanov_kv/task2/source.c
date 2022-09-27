#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	int kpop = 0, i, n, win = 0, mode; // i - Загаданное число, n - предположение, mode - режим игры, kpop - количество попыток.
	printf("Введите режим игры:\n1 - Вы угадываете число\n2 - Программа угадывает число\n");
	scanf_s("%d", &mode);
	if (mode == 1)
	{
		srand(time(NULL)); // Для перебора значений введём рандомайзер.
		i = (rand() % 1000) + 1; 
		printf("Если сдаётесь, введите значение '1001'\n");
		printf("Угадайте число (от 1 до 1000)\n");
		while (win != 1)
		{
			kpop++;
			scanf_s("%d", &n); // Если нет времени угадывать, но надо проверить работу программу.
			if (n == 1001)
				printf("%d\n", i);
			else if (n > i)
				printf("Загаданноне число меньше\n");
			else if (n < i)
				printf("Загаданное число больше\n");
			else if (n == i) {
				printf("Угадали!!!\n");
				win = 1;
			}
		}
		printf("Вы выиграли, число попыток:" "%d\n", kpop);
		system("PAUSE");
	}
	else if (mode == 2)
	{
		char znak;
		int min = 0, max = 1000; // Будем после каждого предположения ограничивать диапазон значения, пока не получим нужный ответ.
		printf("Загадайте число от 1 до 1000, а я попробую его отгадать\n");
		system("PAUSE");
		srand(time(NULL)); // Для перебора значений введём рандомайзер.
		scanf_s("%c", &znak);
		while (win != 1)
		{
			i = rand() % ((max - min) + 1) + min;
			printf("Это число ""%d?\n", i);
			scanf_s(" %c", &znak);
			switch (znak)
			{
				case '>': 
				{
					kpop++;
					min = i;
					break;
				}
				case '<':
				{
					kpop++;
					max = i;
					break;
				}
				case '=':
				{
					kpop++;
					win = 1;
					break;
				}
				default:
				{
					printf("Неверные данные!\n");
					system("PAUSE");
				}
			}
		}
		printf("Я выиграл!!!\n Количество попыток:" "%d\n", kpop);
		system("PAUSE");
	}
	return 0;
}
