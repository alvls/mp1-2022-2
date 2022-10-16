#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
void main()
{
	setlocale(LC_ALL, "Russian");
	int replay=1;
	while (replay != 0)
	{
		int num = 0, cnt1 = 0, cnt2, len, n, multiplier = 1, flag, try, bulls, cows, attempts = 0;
		// num - загаданное число; cnt1,cnt2 - счётчики; len - длина числа
		// try - предполагаемое число; bulls - быки; cows - коровы; attempts - счётчик попыток
		// multiplier - вспомогательный множитель для создания случайного числа без повторений
		int number[5]; // массив для записи цифр загаданного числа
		int guess[5]; // массив для записи цифр предполагаемого числа 
		printf("\nВведите длину загадываемого числа число от 2 до 5):");
		scanf_s("%d", &len);
		if ((len > 1) && (len < 6))
		{
			printf("Если захотите сдаться, введите '0'");
			srand(time(NULL));
			int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //массив из которого берутся случайные цифры
			while (cnt1 != len)
			{
				cnt1 += 1;
				flag = 0;
				n = rand() % 10;
				while (flag != 1)
				{
					if (a[n] != 100)
					{
						num += a[n] * multiplier;
						number[cnt1 - 1] = a[n]; //строчка для записи цифр загаданного числа в массив
						a[n] = 100; //взятый элемент массива заменяется на 100, для того чтобы эта цифра не взялась повторно
						flag = 1;
					}
					else n = rand() % 10; //если предполагаемая цифра уже была взята, снова выбирается рандомный индекс
				}
				if (cnt1 == len - 1)
					a[0] = 100; //это действие для того чтобы старшая цифра не оказалась нулём
				multiplier = multiplier * 10;
			}
			flag = 0;
			while (flag != 1)
			{
				printf("\nВведите преполагаемое число:");
				scanf_s("%d", &try);
				attempts++;
				bulls = 0;
				cows = 0;
				if (try!=0)
				{
					for (cnt1 = 0; cnt1 < len; cnt1++) //цикл для записи цифр предполагаемого числа в массив 
					{
						guess[cnt1] = try % 10;
						try /= 10;
					}
					for (cnt1 = 0; cnt1 < len; cnt1++) //два цикла for позволяют перебрать всевозможные пары цифр двух чисел
					{
						for (cnt2 = 0; cnt2 < len; cnt2++)
						{
							if ((cnt1 == cnt2) && (number[cnt1] == guess[cnt2]))
								bulls++;
							else if ((cnt1 != cnt2) && (number[cnt1] == guess[cnt2]))
								cows++;
						}

					}
					if (bulls == len)
					{
						flag = 1;
						printf("\nВы угадали! :)\n");
						printf("Количество неудачных попыток: %i ", (attempts - 1));
					}
					else
						printf("Количество быков: %i, количество коров: %i\n ", bulls, cows);
				}
				else 
				{
					printf("Загаданное число: %i ", num);
					printf("Количество неудачных попыток: %i ", (attempts - 1));
					flag = 1;
				}
			}
			printf("\n\nХотите ли вы сыграть ещё раз?\n(введите '1' если желаете продолжить, если же хотите завершить игру введите '0'): ");
			scanf_s("%d", &replay);
		}
		else printf("Введённое число некорректно\n");
	}
	getch();
}