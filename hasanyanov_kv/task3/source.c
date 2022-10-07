#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include "console.h"

int povtor(int x, int y) // Введём функцию, которая будет проверять правильность ввода чисел (чтобы не было повторяющихся цифр).
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

int proverka_massiva(int massive[], int num) // Функция для проверки массива на наличие определённой цифры.
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

	textcolor(GREEN);
	textbackground(BLACK);

	setwindow(120, 30);
	SMALL_RECT window;
	COORD buf;
	getwindow(&window, &buf);
	hidecursor();
	gotoxy((window.Left + window.Right) / 2, (window.Top + window.Bottom) / 2);
	gotoxy(buf.X / 2 - 20, (buf.Y / 2) + 0);
	printf("Добро пожаловать в игру <<Быки и Коровы>>");
	gotoxy(0, 0);
	system("PAUSE");
	clrscr();
	gotoxy(buf.X / 2 - 15, (buf.Y / 2) + 0);
	printf("Сколько раз вы хотите сыграть?");
	gotoxy(buf.X / 2 - 0.5, (buf.Y / 2) + 1);
	
		
	
	int game = 1, kolichestvo, pravila;
	srand(time(NULL));

	scanf_s("%d", &kolichestvo);
	clrscr();

	gotoxy(buf.X / 2 - 50, (buf.Y / 2) + 0);
	printf("Правила игры:");
	gotoxy(buf.X / 2 - 51, (buf.Y / 2) + 1);
	printf(" Играют два игрока(человек и компьютер).");
	gotoxy(buf.X / 2 - 50, (buf.Y / 2) + 2);
	printf("Игрок выбирает длину загадываемого числа – n (от 2 до 5).");
	gotoxy(buf.X / 2 - 50, (buf.Y / 2) + 3);
	printf("Компьютер «задумывает» n-значное число с неповторяющимися цифрами.");
	gotoxy(buf.X / 2 - 50, (buf.Y / 2) + 4);
	printf("Игрок делает попытку отгадать число – вводит n-значное число с неповторяющимися цифрами.");
	gotoxy(buf.X / 2 - 50, (buf.Y / 2) + 5);
	printf("Компьютер сообщает, сколько цифр угадано без совпадения с их позициями в загаданном числе (коров)");
	gotoxy(buf.X / 2 - 50, (buf.Y / 2) + 6);
	printf("Компьютер сообщает,сколько угадано вплоть до позиции в загаданном числе (быков).");
	gotoxy(buf.X / 2 - 50, (buf.Y / 2) + 7);
	printf("Игрок делает попытки, пока не отгадает всю последовательность или не сдастся.");
	gotoxy(0, 0);
	system("PAUSE");
	clrscr();
	for (int r = 0; r < kolichestvo; r++) // С помощью цикла for зададим количество повторений игры.
	{
		int len, i, min, max, number, win = 0, count = 0, arrI[5], arrN[5];
		gotoxy(buf.X / 2 - 16, (buf.Y / 2) + 0);
		printf("Введите длину числа (2-5 цифр)");
		gotoxy(buf.X / 2 - 0.5, (buf.Y / 2) + 1);
		scanf_s("%d", &len);
		clrscr();
		if ((len > 5) || (len < 2)) // Проверка данных.
		{
			gotoxy(buf.X / 2 - 8, (buf.Y / 2) + 0);
			printf("Неверные данные");
			gotoxy(0, 0);
			system("PAUSE");
			clrscr();
		}
		else
		{
			min = (int)pow(10, len - 1);
			max = (int)pow(10, len) - 1;
			i = rand() % (max - min + 1) + min; // Загадаем рандомное число в диапазоне, зависящем от количества цифр в числе.
			while (povtor(i, len) == 0) // Проверим сгенерированное число на повторяющиеся цифры.
			{
				i = rand() % (max - min + 1) + min; //Если число не подходит, заменим на другое и проверим ещё раз.
			}
			gotoxy(buf.X / 2 - 14, (buf.Y / 2) + 0);
			printf("Попытайтесь угадать число:");
			gotoxy(buf.X / 2 - 14, (buf.Y / 2) + 1);
			printf("(Если сдаётесь, введите 9)"); //Код для получения ответа.

			while (win != 1)
			{
				int bulls = 0, kows = 0, temp;
				count++;
				temp = i;
				
				gotoxy(buf.X / 2 - 2, (buf.Y / 2) + 2);
				scanf_s("%d", &number);
				clrscr();
				if (((number > ((int)pow(10, len) - 1)) || (number < ((int)pow(10, len - 1)))) && number != 9) // Проверка на правильность введённого числа.
				{

					gotoxy(buf.X / 2 - 8, (buf.Y / 2) + 0);
					printf("Неверные данные");
					gotoxy(0, 0);
					system("PAUSE");
					clrscr();
					gotoxy(buf.X / 2 - 14, (buf.Y / 2) + 0);
					printf("Попытайтесь угадать число:");
				}
				else if (number == i) //Случай победы.
					win = 1;
				else if (number == 9)//Случай сдачи.
				{
					gotoxy(buf.X / 2 - 11, (buf.Y / 2) + 0);
					printf("Загаданное число : %d", i);
					gotoxy(0, 0);
					system("PAUSE");
					clrscr();
					gotoxy(buf.X / 2 - 14, (buf.Y / 2) + 0);
					printf("Попытайтесь угадать число:");
					gotoxy(buf.X / 2 - 2, (buf.Y / 2) + 0);
				}
				else
				{
					for (int k = 0; k < len; k++)//Заполним два массива цифрами из загаданного числа и введённого (порядок цифр поменяется, но позиции останутся).
					{
						arrI[k] = temp % 10;
						arrN[k] = number % 10;
						temp /= 10;
						number /= 10;
					}
					for (int c = 0; c < len; c++)//Будем сравнивать одинаковые позиции (поиск быков).
					{
						if (arrN[c] == arrI[c])
							bulls++;
						else if (proverka_massiva(arrI, arrN[c]) == 0) //А иначе ищем коров.
							kows++;
					}
					clrscr();
					gotoxy(buf.X / 2 - 11, (buf.Y / 2) - 1);
					printf("Количество коров: %d", kows);
					gotoxy(buf.X / 2 - 11, (buf.Y / 2) + 0);
					printf("Количество быков: %d", bulls);
					gotoxy(buf.X / 2 - 14, (buf.Y / 2) + 1);
					printf("Попытайтесь угадать число:");
				}
			}
		}
		textcolor(RED);
		textbackground(WHITE);
		clrscr();
		gotoxy(buf.X / 2 - 18, (buf.Y / 2) + 0);
		printf("ВЫ ВЫИГРАЛИ!!! КОЛИЧЕСТВО ПОПЫТОК: %d \n", count);
		gotoxy(0, 0);
		system("PAUSE");
		textcolor(GREEN);
		textbackground(BLACK);
		clrscr();
	}
	return 0;
}