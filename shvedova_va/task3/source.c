#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define c_size 5
void main()
{
	int length, number_enter, check_number, c_digits, n, bulls, cows, match, computer[c_size], digit, i = 1, j = 0, c, end;
	setlocale(LC_ALL, "Rus");
	printf("Введите длину загадываемого числа (2<=n<=5): ");
	scanf_s("%d", &length);
	if ((length < 2) || (length > 5))
		printf("Введена некорректная длина, длина должна быть от 2 до 5");
	srand(time(NULL));
	digit = (1 + rand() % 9);
	computer[0] = digit;
	do {
		digit = -1;
		while (digit == -1) {
			digit = rand() % 10;
			if ((digit != computer[0]) && (digit != computer[1]) && (digit != computer[2]) && (digit != computer[3]) && (digit != computer[04]))
				computer[i] = digit;
			else
				digit = -1;
		}
		i ++;
	} while (i < length);
	//while (j < length)
		//printf("%d", computer[j++]);//вывод составленного числа
	while (1) {
		printf("\nПопробуйте угадать число заданной длины и введите его (все цифры числа различны): ");
		scanf_s("%d", &number_enter);
		check_number = number_enter;
		c_digits = 0;
		while (check_number > 0) {
			c_digits ++;
			check_number /= 10;
		}
		if (c_digits != length) {
			printf("Введено число несоответсвующей длины, заданная длина: %d ", length);
			break;
		}
		//считаем количество "быков" (точных совпадений)
		n = number_enter;
		c = 0;
		bulls = 0;
		cows = 0;
		match = 0;
		while (n > 0) {
			c += 1;
			if ((n % 10) == computer[length - c]) {
				bulls += 1;
				n /= 10;
			}
			else
				n = n / 10;
		}
		if (bulls == length) {
			printf("Вы угадали число!\n");
			break;
		}
		else {
			//считаем общее количество совпадений
			n = number_enter;
			while (n > 0) {
				if (((n % 10) == computer[0]) || ((n % 10) == computer[1]) || ((n % 10) == computer[2]) || ((n % 10) == computer[3]) || ((n % 10) == computer[4])) {
					match += 1;
					n /= 10;
				}
				else
					n /= 10;
			}
			//считаем количество "коров" (цифры, угаданные без соответсвия позиций)
			cows = match - bulls;
			printf("\nКоличество 'быков' (точных совпадений) : % d", bulls);
			printf("\nКоличество 'коров' (совпадений без соответствия позиций) : % d", cows);
		}
		printf("\nЧтобы продолжить попытку введите 1, если вы хотите сдаться и завершить игру, введите 0: ");
		scanf_s("%d", &end);
		if (end == 0)
			break;
	}
	system("pause");
}