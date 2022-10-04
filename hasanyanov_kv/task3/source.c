#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>

int povtor(int x, int y)
{
	int mass[5], temp;
	for (int h = 0; h < y; h++)
	{
		temp = x % 10;
		if (proverka_massiva(mass, temp) == 1)
		{
			mass[h] = temp;
			x /= 10;
		}
		else
			return 0;
	}
	return 1;
}

int proverka_massiva(int massive[], int num)
{
	int k;
	for (k = 0; k < 5; k++)
	{
		if (num == massive[k])
			return 0;
	}
	return 1;
}



int main()
{
	setlocale(LC_ALL, "Russian");
	int game = 1, kolichestvo;
	srand(time(NULL));
	printf("*****************************************\nДобро пожаловать в игру <<Быки и Коровы>>\nСколько раз вы хотите сыграть?\n");
	scanf_s("%d", &kolichestvo);
	for (int r = 0; r < kolichestvo; r++)
	{
		while (game == 1)
		{
			int len, i, min, max, number, win = 0, count = 0, arrI[5], arrN[5];
			printf("Введите длину числа (2-5 цифр)\n");
			scanf_s("%d", &len);
			if ((len > 5) || (len < 2))
			{
				printf("Неверные данные\n");
				system("PAUSE");
			}
			else
			{
				min = (int)pow(10, len - 1);
				max = (int)pow(10, len) - 1;
				i = rand() % (max - min + 1) + min;
				while (povtor(i, len) == 0)
				{
					i = rand() % (max - min + 1) + min;
				}
				printf("(Если сдаётесь, введите 9)\n");
				while (win != 1)
				{
					int bulls = 0, kows = 0, temp;
					count++;
					temp = i;
					printf("Попытайтесь угадать число:\n");
					scanf_s("%d", &number);
					if (((number > ((int)pow(10, len) - 1)) || (number < ((int)pow(10, len - 1)))) && number != 9)
					{
						printf("Неверные данные\n");
						system("PAUSE");
					}
					else if (number == i)
						win = 1;
					else if (number == 9)
						printf("Загаданное число : %d \n", i);
					else
					{
						for (int k = 0; k < len; k++)
						{
							arrI[k] = temp % 10;
							arrN[k] = number % 10;
							temp /= 10;
							number /= 10;
						}
						for (int c = 0; c < len; c++)
						{
							if (arrN[c] == arrI[c])
								bulls++;
							else if (proverka_massiva(arrI, arrN[c]) == 0)
								kows++;
						}
						printf("Количество коров: %d \nКоличество быков: %d \n", kows, bulls);
					}
				}
			}
			printf("Вы выиграли, количество попыток: %d \n", count);
			system("PAUSE");
			printf("******************************************\n");
		}
	}
	return 0;
}