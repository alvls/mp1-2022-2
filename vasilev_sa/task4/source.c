#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include "header.h"

#define MAX_CHECK 100
#define TOVAR_COUNT 30
#define MAX_LENGTH 44


SMALL_RECT window;
COORD buf;

//названия товаров
char tovar_array[TOVAR_COUNT][MAX_LENGTH] = {
"Молоко ультрапастеризованное",
"Молоко безлактозное",
"Молоко детское с 8 месяцев",
"Кефир 3,2%",
"Кефир обезжиренный",
"Ряженка термостатная",
"Сливки 10%",
"Сливки 35% для взбивания",
"Сметана 15%",
"Сметана 25%",
"Молоко кокосовое",
"Молоко овсяное",
"Творог 9% жирности",
"Творожок детский сладкий",
"Яйцо диетическое",
"Масло сливочное крестьянское",
"Крупа гречневая ядрица",
"Крупа манная",
"Крупа пшено",
"Крупа перловая",
"Рис круглозерный",
"Рис длиннозерный",
"Бурый рис",
"Макароны спагетти ",
"Макароны вермишель",
"Макароны рожки",
"Макароны перья",
"Сахар песок белый",
"Сахар демерара коричневый",
"Сахар рафинад быстрорастворимый",
};
//цены товаров
int price_array[TOVAR_COUNT] = {
57,
75,
35,
75,
70,
50,
38,
220,
55,
70,
190,
85,
60,
30,
70,
90,
100,
49,
90,
80,
105,
115,
120,
50,
52,
47,
45,
38,
85,
44,
};
//штрих-коды товаров
short cods_array[TOVAR_COUNT][4] = {
{2, 0, 7, 5},
{9, 0, 0, 4},
{5, 4, 4, 4},
{2, 7, 3, 7},
{4, 4, 7, 7},
{2, 2, 4, 3},
{8, 0, 9, 7},
{5, 8, 1, 6},
{2, 3, 6, 8},
{3, 2, 2, 9},
{6, 7, 2, 0},
{2, 8, 8, 8},
{1, 2, 6, 1},
{8, 3, 9, 3},
{7, 9, 1, 9},
{0, 3, 6, 9},
{9, 1, 3, 2},
{2, 5, 7, 2},
{4, 2, 5, 4},
{4, 3, 6, 6},
{4, 5, 6, 1},
{0, 7, 5, 9},
{1, 4, 8, 2},
{6, 9, 1, 7},
{4, 8, 8, 5},
{3, 0, 5, 5},
{4, 1, 1, 8},
{5, 5, 2, 4},
{1, 7, 6, 3},
{2, 8, 1, 7},
};
//итоговый чек
short check[MAX_CHECK];

void print_info(int index);
void print_arr(short arr[]);
void price_list(void);
int check_update(int cod);
int cod_inp(void);
int arr_to_int(short arr[]);
void make_check(void);

void main()
{
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");
	clrscr();
	SetConsoleTitle("Электронная касса");
	setwindow(80, 35);
	getwindow(&window, &buf);

	int cod, index, count = 0;
	price_list();
	textcolor(RED);
	system("pause");
	do
	{
		clrscr();
		cod = cod_inp();
		if (cod > 0)
		{
			index = check_update(cod);
			print_info(index);
			if (index >= 0)
				check[index]++;
			else
			{
				printf("Not in cods\n");
				textcolor(RED);
				system("pause");
				continue;
			}
			textcolor(RED);
			system("pause");
			count++;
		}
		else
		{
			make_check();
			break;
		}
	} while (1);
	textcolor(RED);
	system("pause");
}

//напечатать информацию о товаре
void print_info(int index)
{
	if (index != -1)
	{
		clrscr();
		textcolor(MAGENTA);
		printf("\t\tИнформация о товаре:\n");
		printf("----------------------------------------------------\n");
		textcolor(GREEN);
		printf("  % s: ", tovar_array[index]);
		textcolor(WHITE);
		printf("%d", price_array[index]);
		textcolor(GREEN);
		printf(" рублей/шт\n");
		textcolor(MAGENTA);
		printf("----------------------------------------------------\n");
	}
}

//напечатать массив
void print_arr(short arr[])
{
	for (int i = 0; i < 4; i++)
		printf("%d", arr[i]);
}

//напечатать список товаров
void price_list(void)
{
	int time_x = (window.Left + window.Right) / 2;
	textcolor(MAGENTA);
	printf("\t\tСписок доступной продукции:\n");
	printf("----------------------------------------------------\n");
	textcolor(GREEN);
	for (int i = 0; i < TOVAR_COUNT; i++)
	{
		textcolor(WHITE);
		print_arr(cods_array[i]);
		textcolor(GREEN);
		printf(": %s", tovar_array[i]);
		gotoxy(time_x, wherey());
		printf("| ");
		textcolor(WHITE);
		printf("%d", price_array[i]);
		textcolor(GREEN);
		printf(" рублей\n");
	}
	textcolor(MAGENTA);
	printf("----------------------------------------------------\n");
}

//вернуть индекс из массива кодов
int check_update(int cod)
{
	for (int i = 0; i < TOVAR_COUNT; i++)
	{
		if (cod == arr_to_int(cods_array[i]))
			return i;
	}
	return -1;
}

//ввод штрих-кода
int cod_inp(void)
{
	int answer, count;
	char ch;
	do
	{
		clrscr();
		textcolor(GREEN);
		printf("Введите штрих-код: ");
		textcolor(WHITE);
		count = scanf_s("%d", &answer);
		while (ch = getchar() != '\n');
		if (answer <= 0)
			return answer;
	} while (count < 1);
	return answer;
}

//массив в число
int arr_to_int(short arr[])
{
	int answer = 0;
	int n = 1000;
	for (int i = 0; i < 4; i++)
	{
		answer += arr[i] * n;
		n /= 10;
	}
	return answer;
}

//напечатать чек
void make_check(void)
{
	int all_sum_without_sell = 0, all_sell_sum = 0, price, new_price, count = 1, sell = 5;
	clrscr();
	textcolor(MAGENTA);
	printf("\t\tВаш список продуктов:\n");
	printf("----------------------------------------------------\n");
	textcolor(GREEN);
	for (int i = 0; i < sizeof(check) / sizeof(check[0]); i++)
	{
		new_price = 0;
		if (check[i] != 0)
		{
			sell = 950 - (check[i] - 1) * 25;
			price = check[i] * price_array[i];
			for (int j = 1; j <= check[i]; j++)
			{
				if (j % 10 == 0)
					sell = price_array[i] / 2;
				else
					sell = price_array[i] - (j % 10) * (price_array[i] / 20);
				new_price += sell;
			}
			printf("%d) %s: %d руб./шт * %d шт. | %d рублей\n", count++, tovar_array[i], price_array[i], check[i], price);
			all_sum_without_sell += price;
			all_sell_sum += price - new_price;
		}
	}
	textcolor(MAGENTA);
	printf("----------------------------------------------------\n");
	textcolor(GREEN);
	printf("Итого сумма: %d руб.\n", all_sum_without_sell);
	printf("Итого скидка: %d руб.\n", all_sell_sum);
	textcolor(WHITE);
	printf("К оплате: %d руб.\n", all_sum_without_sell - all_sell_sum);
}
