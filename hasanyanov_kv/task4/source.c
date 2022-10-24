#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include "Header.h"
#define SIZE 13

const char* KODES[SIZE] = {"1234", "2345", "3456", "4567", "5678", "6789", "7890", "6534", "3556", "0000", "0110", "0123", "5437"};
const char* NAMES[SIZE] = { "Кружка пивная", "Ручка шариковая", "Клавиатура", "Стол письменный","Рюкзак школьный","Портмоне кожаное","Морозильная камера","Монитор IPS", "Мяч волейбольный  ", "Кроссовки беговые ", "Наушники", "Куртка зимняя", "Кольцо серебряное"};
const int COSTS[SIZE] = { 300, 35, 8200, 12000, 3000, 1550, 18500, 31000, 7800, 5700, 16500, 9000, 7000 };
const int DISCOUNTS[SIZE] = { 10, 5, 20, 15, 10, 5, 25, 30, 35, 50, 40, 45, 10 };
int kol[SIZE] = { 0 };

int find_ind(char* x)
{
	
	for (int i = 0; i < SIZE; i++)
	{
		if (strcmp(KODES[i],x) == 0)
		{
			return i;
		}
	}
	return -1;
}










int main()
{
	setlocale(LC_ALL, "Russian");
	textcolor(GREEN);
	textbackground(BLACK);

	setwindow(120, 40);
	SMALL_RECT window;
	COORD buf;
	getwindow(&window, &buf);
	hidecursor();
	gotoxy((window.Left + window.Right) / 2, (window.Top + window.Bottom) / 2);
	gotoxy(buf.X / 2 - 20, (buf.Y / 2) + 0);
	int  ind, cost, mode = 1, count = 0;
	double summ = 0;
	char  x[5], name, znak; //4 символа и нуль-терминатор
	
	printf("Добро пожаловать в онлайн-дискаунтер!!!");
	gotoxy(0, 0);
	system("PAUSE");
	clrscr();
	
	while (mode == 1)
	{
		clrscr();
		gotoxy(0, 2);
		printf("================================================================================\n");
		printf("Наш ассортимент:");
		printf("\n%-25s %-20s %-5s\n", "Штрих-код:", "Наименование:", "Цена (скидка):\n");
		for (int k = 0; k < SIZE; k++)
		{
			printf("%-25s %-20s %-5d (%d%%)\n", KODES[k], NAMES[k], COSTS[k], DISCOUNTS[k]);
		}

		printf("================================================================================\n");
		gotoxy(buf.X / 2 - 12, (buf.Y / 2) + 2);
		printf("Введите цифры штрих-кода:");
		gotoxy(buf.X / 2 - 2, (buf.Y / 2) + 3);
		scanf_s("%s", &x, sizeof(x));
		ind = find_ind(x);
		if (ind == -1)
		{
			gotoxy(buf.X / 2 - 8.5, (buf.Y / 2) + 4);
			printf("Продукт не найден\n");
			gotoxy(0, 0);
			system("PAUSE");
			clrscr();
		}
		else
		{
			
			gotoxy(0, (buf.Y / 2) + 4);
			printf("Наименование: %s\nЦена: %d\nКол-во: %d\nСкидка(%%): %d\n", NAMES[ind], COSTS[ind], kol[ind], DISCOUNTS[ind]);
			printf("Нажмите '$'  чтобы распечатать чек, '+' чтобы добавить товар в чек, '-' чтобы удалить выбранный товар.\n");
			gotoxy(buf.X / 2 - 0.5, (buf.Y / 2) + 4);
			scanf_s(" %c", &znak);
			clrscr();
			gotoxy(buf.X / 2 - 12, (buf.Y / 2) + 2);
			switch (znak)
			{
			case'$':
			{
				mode = 0;
				kol[ind]++;
				gotoxy(buf.X / 2 - 33, (buf.Y / 2) + 0);
				printf("**********************************************************************");
				gotoxy(buf.X / 2 - 5.5, (buf.Y / 2) + 1);
				printf("КАССОВЫЙ ЧЕК");
				gotoxy(buf.X / 2 - 31.5, (buf.Y / 2) + 2);
				printf("Наименование:         Цена:       Количество:  Скидка:   Стоимость:\n");
				for (int i = 0; i < SIZE; i++)
				{
					if (kol[i] == 0)
					{
						;
					}
					else
					{
						count++;
						summ += COSTS[i] * kol[i] - COSTS[i] * kol[i] * DISCOUNTS[i] / 100;


						gotoxy(buf.X / 2 - 31.5, (buf.Y / 2) + count + 2);
						printf("%d)", count);
						gotoxy(buf.X / 2 - 31.5 + 3, (buf.Y / 2) + count + 2);
						printf("%s", NAMES[i]);
						gotoxy(buf.X / 2 - 31.5 + 22, (buf.Y / 2) + count + 2);

						printf("%dруб.", COSTS[i]);

						gotoxy(buf.X / 2 - 31.5 + 38.5, (buf.Y / 2) + count + 2);

						printf("%d", kol[i]);

						gotoxy(buf.X / 2 - 31.5 + 48.5, (buf.Y / 2) + count + 2);

						printf("%d%%", DISCOUNTS[i]);

						gotoxy(buf.X / 2 - 31.5 + 57, (buf.Y / 2) + count + 2);

						printf("%dруб.", COSTS[i] * kol[i] - COSTS[i] * kol[i] * DISCOUNTS[i] / 100);

					}
				}
				gotoxy(buf.X / 2 - 31.5, (buf.Y / 2) + 3 + count);
				printf("ИТОГО К ОПЛАТЕ: %gруб.", summ);
				gotoxy(buf.X / 2 - 33, (buf.Y / 2) + 4 + count);
				printf("**********************************************************************");
				break;
			}			
			case '-':
			{
				break;
			}			
			case '+':
			{
				kol[ind]++;
				break;
			}
			default:
			{
				gotoxy(buf.X / 2 - 6.5, (buf.Y / 2) + 0);
				printf("Неверный знак\n");
				gotoxy(0, 0);
				system("PAUSE");
			}
			}
		
		}
	}
	gotoxy(0, 0);
	system("PAUSE");
}
	