#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
void main()
{
	setlocale(LC_ALL, "Russian");
	int n, flag, cnt, mode, max, min, try;
	char sign;
	// mode - режим игры, n - загаданное число, try - попытки угадать, cnt - счётчик попыток
	// переменные max и min ограничения для угадывания числа во втором режиме
	printf("Выберите режим игры: \n (1 - число загадывается программой, 2 - число загадывает пользователь) \n");
	scanf_s("%d", &mode);
	cnt = 0;

	if (mode==1)
	{
		srand(time(NULL));
		n = 1 + rand() % 1001;
		while (1)
		{
			cnt += 1;
			printf("Введите значение: ");
			scanf_s("%d", &try);
			if (try < n)
				printf("Загаданное число больше \n");
			else if (try > n)
				printf("Загаданное число меньше \n");
			else if (try == n)
			{
				printf("Угадали\n");
				printf("Количество попыток:");
				printf("%d", cnt);
				break;
			}
		}
	}
	else if (mode==2)
	{
		printf("Введите загаданное число: \n");
		scanf_s("%d", &n);
		max = 1001;
		min = 1;
		flag = 0;
		while (1)
		{
			cnt += 1;
			try = round((max - min) / 2) + min;
			printf("Загаданное число %i?\n", try);
			printf("Укажите знаком загаданное число больше, меньше или равно: \n");
			scanf_s("\n%c", &sign);
			if (sign == '<')
				max = try;
			if (sign =='>')
				min = try;
			if (sign == '=')
			{
				printf("Угадано\n");
				printf("Количество попыток:");
				printf("%d", cnt);
				break;
			}
			
		}
	}
	

	getch();
}