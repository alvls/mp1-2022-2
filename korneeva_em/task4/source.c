#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 7
#define len_code 4
const int codes[SIZE][len_code] = { {0,0,0,1},{0,0,0,2},{0,0,0,3},{0,0,0,4},{0,0,0,5},{0,0,0,6},{0,0,0,7} };
const char products[SIZE][20] = { "Хлеб","Молоко","Яйца","Йогурт","Чай","Кофе","Печенье" };
const int prices[SIZE] = { 34,80,72,54,87,297,125 };
const float discounts[SIZE] = { 0.20f,0.15f,0.05f,0.10f,0.00f,0.40f,0.25f };

int find_product(int code_now)
{
	int flag1 = 0;
	for (int i = 0; i < SIZE; i++)
	{
		int codeP = 0;
		int multiplier = 1;
		for (int j = len_code - 1; j >= 0; j--)
		{
			codeP += codes[i][j] * multiplier;
			multiplier *= 10;
		}
		if (code_now == codeP)
			return i;
	}
	return -1;
}
void main()
{
	setlocale(LC_ALL, "Russian");
	int count[SIZE] = { 0, 0, 0, 0, 0, 0, 0 };
	int sum,code_now, result = 0, cnt;
	float sum_discount, sum_with_discount, result_with_discount = 0, result_discount = 0;
	printf("----------------------------------------------------");
	printf("\n| Наименование  |  Штрих-код  |  Стоим. без скидки |\n");
	printf("----------------------------------------------------\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("| %-11s\t| ", products[i]);
		for (int j = 0; j < len_code; j++)
			printf("%d", codes[i][j]);
		printf("%8c|%10d%10c|\n",' ', prices[i], ' ');
	}
	printf("----------------------------------------------------\n");
	printf("*** Для вывода чека введите '0'\n");
	while (1)
	{
		printf("\nВведите штрих-код:");
		scanf_s("%d", &code_now);
		if (code_now == 0)
			break;
		if (find_product(code_now) != -1)
		{
			count[find_product(code_now)]++;
			printf("----------------------------------------------------------");
			printf("\n| Наименование  |  Кол-во  |  Стоим. за единицу | Скидка |\n");
			printf("----------------------------------------------------------\n");
			for (int i = 0; i < SIZE; i++)
			{
				if (count[i] > 0)
				{
					if ((discounts[i] * 10)>=1)
						printf("| %-11s\t|%5d%5c|%10d%10c|%2c%.0f%%%3c|\n", products[i], count[i], ' ', prices[i], ' ', ' ', discounts[i] * 100, ' ');
					else
						printf("| %-11s\t|%5d%5c|%10d%10c|%2c%.0f%%%4c|\n", products[i], count[i], ' ', prices[i], ' ', ' ', discounts[i] * 100, ' ');
				}
			}
			printf("----------------------------------------------------------\n");
		}
		else
			printf("Товара с таким штрих-кодом не существует");
	}
	printf("=========================================================================");
	printf("\n| Наименование  |  Кол-во  | Стоим. за ед.|    Скидка    |   Стоимость  |\n");
	printf("|-----------------------------------------------------------------------|\n");
	for (int i = 0; i < SIZE; i++)
	{
		sum_with_discount = 0.00;
		cnt = count[i];
		if (cnt == 0)
			continue;
		sum = prices[i] * count[i];
		result += sum;
		sum_discount = sum * discounts[i];
		result_discount+=sum_discount;
		sum_with_discount = sum - sum_discount;
		result_with_discount += sum_with_discount;
		printf("| %-14s|  %-8d|     %-9d|  %-12.2f|  %-11.2f |\n", products[i], cnt, prices[i], sum_discount, sum_with_discount);
	}
	printf("|-----------------------------------------------------------------------|\n");
	printf("| Итого:%8c|%10c| %6d руб.  -  %-5.2f руб. =  %-3.2f руб.  |\n",' ', ' ', result, result_discount, result_with_discount);
	printf("=========================================================================\n");
	getch();
}	