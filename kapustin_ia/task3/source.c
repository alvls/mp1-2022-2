#include <iostream>
#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <windows.h> //нужен для вызова sllep()
#include <stdlib.h> // нужен для вызова функций rand(), srand()
#include <time.h> // нужен для вызова функции time()
int GetRan(int min, int max)
{
	// Установить генератор случайных чисел
	srand((int)time(NULL));
	// Получить случайное число
	int num = min + rand() % (max - min + 1);
	return num;
}
int main()
{

	setlocale(LC_ALL, "RUS");
	int ar[5] = { -1,-3,-4,-5,-6 };
	int ar1[5] = { -2,-7,-8,-9,-20 };
	int n, rad, g, i, s, bulls, cows;
    c:
	printf("Введите число n от 2 - 5, в зависимости от того, какое по значности число хотите угадывать\n");
	scanf_s("%i", &n);
    d:
	Sleep(1500);
	switch (n)
	{
	case 2:

		rad = GetRan(10, 99);
		/*printf("Число = %d\n", rad);*/
		break;
	case 3:
		rad = GetRan(100, 999);
		/*printf("Число = %d\n", rad);*/
		break;
	case 4:
		rad = GetRan(1000, 9999);
		/*printf("Число = %d\n", rad);*/
		break;
	case 5:
		rad = GetRan(10000, 99999);
		/*printf("Число = %d\n", rad);*/
		break;
	default:
		printf("Неверное значение n, попробуйте снова\n");
		goto c;
	}
	i = 0;
	while (rad > 0)
	{
		ar[i] = rad % 10;
		rad /= 10;
		/*printf("=%d\n", ar[i]);*/
		i++;
	}
	i = 0;
	while (i < 5)
	{
		for (int j = i + 1; j < 5; j++)
			if (ar[i] == ar[j])
			{
				goto d;
			}
		i++;
	}
    h:
	printf("Введите n-значное число; n = %d\n", n);
	scanf_s("%d", &s);
	i = 0;
	while (s > 0)
	{
		ar1[i] = s % 10;
		s /= 10;
		/*printf("=%d\n", ar1[i]);*/
		i++;
	}
	i = 0;
	cows = 0;
	bulls = 0;
	while (i < 5)
	{
		for (int j = 0; j < 5; j++)
			if (ar[i] == ar1[j])
			{
				cows = cows + 1;
				if (i == j)
					bulls = bulls + 1;
			}
		i++;
	}
	printf("коров = %d\n", cows);
	printf("быков = %d\n", bulls);
	if (bulls != n)
	{
		printf("Если хотите продолжить отгадывать нажмите 1, иначе 2\n");
		scanf_s("%d", &g);
		switch (g)
		{
		case 1:
			goto h;
		case 2:
			break;
		}
	}
	else
	{
		printf("Вы отгадали число!");
	}
	return 0;
}