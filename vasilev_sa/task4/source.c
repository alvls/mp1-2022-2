#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include "header.h"

#define MAX_CHECK 40
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
char cods_array[TOVAR_COUNT][5] = {
"2075",
"9004",
"5444",
"2737",
"4477",
"2243",
"8097",
"5816",
"2368",
"3229",
"6720",
"2888",
"1261",
"8393",
"7919",
"0369",
"9132",
"2572",
"4254",
"4366",
"4561",
"0759",
"1482",
"6917",
"4885",
"3055",
"4118",
"5524",
"1763",
"2817",
};
//итоговый чек
short check[MAX_CHECK];

void print_info(int index);
void price_list(void);
int check_update(char* cod);
char* cod_inp(void);
void make_check(void);

void main()
{
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");
	clrscr();
	SetConsoleTitle("Электронная касса");
	setwindow(80, 35);
	getwindow(&window, &buf);

	int index, count = 0;
	char cod[5];
list_print:
	clrscr();
	price_list();
	textcolor(RED);
	system("pause");
	do
	{
		clrscr();
		strcpy_s(cod, 5, cod_inp());
		if (strcmp(cod, "exit") != 0)
		{
			if (strcmp(cod, "list") == 0)
				goto list_print;
			index = check_update(cod);
			print_info(index);
			if (index >= 0)
			{
				count++;
				check[index]++;
			}
			else
			{
				printf("Not in cods\n");
				textcolor(RED);
				system("pause");
				continue;
			}
			textcolor(RED);
			system("pause");
		}
		else
		{
			if (count != 0)
			{
				make_check();
				break;
			}
			clrscr();
			printf("Чек пуст, попробуйте ещё раз\n");
			textcolor(RED);
			system("pause");
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
		printf("%s", cods_array[i]);
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
int check_update(char* cod)
{
	for (int i = 0; i < TOVAR_COUNT; i++)
	{
		if (strcmp(cod, cods_array[i]) == 0)
			return i;
	}
	return -1;
}

//ввод штрих-кода
char* cod_inp(void)
{
	int count;
	char answer[5] = { 0 }, ch;
	do
	{
		clrscr();
		textcolor(GREEN);
		printf("Введите необходимый штрих-код, тогда выбранный товар добавится в чек. \nЧтобы закончить введите \"exit\", чтобы увидеть спписок \"list\"\n");
		printf("Введите штрих-код: ");
		textcolor(WHITE);
		scanf_s("%s", &answer, 5);
		while (ch = getchar() != '\n');
		if (strcmp(answer, "exit") == 0)
			return answer;
		count = atoi(answer);
	} while ((count < 0) || (count >= 10000));
	return answer;
}

//напечатать чек
void make_check(void)
{
	int all_sum_without_sell = 0, all_sell_sum = 0, price, new_price, count = 1, sell = 5, time_x1 = (window.Left + window.Right) / 2 - 3, time_x2 = (window.Left + window.Right) / 2 + 20;
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
			/*printf("%d) %s: %d руб./шт * %d шт. | %d рублей\n", count++, tovar_array[i], price_array[i], check[i], price);*/
			printf("%d) %s:", count++, tovar_array[i]);
			gotoxy(time_x1, wherey());
			printf("%d руб./шт. * %d шт.", price_array[i], check[i]);
			gotoxy(time_x2, wherey());
			printf("| %d руб.\n", price);
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
