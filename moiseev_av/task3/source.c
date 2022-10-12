#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h> //Библиотеки для работы с консолью//
#include <memory.h>


enum TColor {            //Набор цветов//
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
	DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
	LIGHTMAGENTA, YELLOW, WHITE
};

void textattr(int color) //Функция, отвечающая за цвет атрибута//
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console, color);
}

void textcolor(int color)  //Функция, отвечающая за цвет текста//
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;
	COORD pos = buf.dwCursorPosition;
	ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

	int bk_col = Attr / 16;
	int col = color % 16;
	col = col + bk_col * 16;

	SetConsoleTextAttribute(Console, col);
}

void setwindow(int width, int height)  //Функция, отвечающая за размер окна//
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	SMALL_RECT rect;
	rect.Left = 0;
	rect.Right = width - 1;
	rect.Top = 0;
	rect.Bottom = height - 1;
	COORD size;
	size.X = width;
	size.Y = height;
	SetConsoleWindowInfo(Console, 1, &rect);
	SetConsoleScreenBufferSize(Console, size);
}

void main()
{
	setwindow(86, 30); //Применение параметров размера окна//

	setlocale(LC_ALL, "Rus");

	int res = TRUE;
	const int COUNT = 9, COUNT_word = 8;
	char ch, yn, word[] = { 'W', 'e', 'l', 'c', 'o', 'm', 'e', '!' };

	while (res == TRUE) //Цикл для повтора игры//
	{
		int n = 1, cnt = 0, bul = 0, cow = 0, betw = 0, j = 0, i = 1, hint = 1;
		int user_num, len_for_user_num = 0, user_numberi = 0, degree, detecter;
		int computer_num[4], user_numbers[4], numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		srand(time(0));

		printf("\n               ");
		for (j = 0; j < COUNT_word; j++) //Выводим каждый элемент массива по отдельности при этом, меняем цвет элемента//
		{
			while (i < COUNT)
			{
				textcolor(i);
				printf("%c", word[j]);
				i++;
				break;
			}
		}
	
		textcolor(YELLOW); //Вступление//
		printf("\n\nДобро пожаловать в игру 'Быки и коровы'!\n");
		textcolor(YELLOW);
		printf("\n               Правила:\n");
		textattr(LIGHTGRAY);
		printf("\n1. Играют два игрока(человек и компьютер)\n2. Игрок выбирает длину загадываемого числа n – (от 2 до 5)\n3. Компьютер 'задумывает' n - значное число с неповторяющимися цифрами\n4. Игрок пытается отгадать число: вводит n - значное число с неповторяющимися цифрами\n5. Компьютер сообщает, сколько цифр угадано -\n   без совпадения с их позициями в загаданном числе (то есть количество коров)\n   И сколько угадано вплоть до позиции в загаданном числе (то есть количество быков)\n6. Игрок делает попытки, пока не отгадает всю последовательность или не сдастся\n");
		textcolor(LIGHTRED);
		printf("\nДля выхода введите : '0'\n\n");

		while ((n < 2) || (n >= 5)) //Контроль ввода//
		{
			textcolor(LIGHTCYAN);
			printf("Ввведите длину числа (от 2 до 5): ");
			textattr(WHITE);
			scanf_s("%d", &n);

			while (ch = getchar() != '\n'); //Отчистка буфера//

			if (n == 0) //Выход из программы//
			{
				textcolor(YELLOW);
				printf("\nДо свидания!\n");
				textcolor(WHITE);
				return 0;
			}
			else if ((n < 2) || (n >= 5))
			{
				textcolor(LIGHTRED);
				printf("\nОшибка!\n");
				textcolor(YELLOW);
				printf("Недопустимая длина числа!\n");
				textcolor(WHITE);
			}
			else
			{
				break;
			}
		}

		for (i = 9; i >= 1; i--)  //Перемешиваем массив, тем самым создаем случайное число с неповторяющимеся цифрами//
		{
			j = rand() % (i + 1);
			betw = numbers[j];
			numbers[j] = numbers[i];
			numbers[i] = betw;
		}

		computer_num[0] = numbers[0];
		computer_num[1] = numbers[1];

		if (computer_num[0] == 0) //Проверка равенства первой цифры нулю//
		{
			computer_num[0] = numbers[4];
		}

		switch (n)
		{
			case 3: computer_num[2] = numbers[2];
				break;
			case 4: computer_num[2] = numbers[2], computer_num[3] = numbers[3];
				break;
		}

		textcolor(YELLOW);
		printf("\nЯ загадал число\nТеперь ваша задача угадать загаданную последовательность.\n");
		while (1)
		{
			detecter = 0;
			if (hint % 3 == 0) //Спустя 3 неудачных попыток компьютер будет предлагать сдасться//
			{
				textcolor(LIGHTRED);
				printf("\nЕсли хотите сдаться введите: '0'\n");
			}
			textcolor(LIGHTCYAN);
			printf("\nВведите вашу догадку: ");
			textattr(WHITE);
			scanf_s("%d", &user_num);

			while (ch = getchar() != '\n'); //Отчистка буфера//
			if (user_num == 0)
			{
				textcolor(YELLOW); //Выход из программы//
				printf("\nДо свидания!\n");
				textcolor(WHITE);
				res = FALSE;
				break;
			}

			len_for_user_num = user_num;
			cnt = 0;

			while (len_for_user_num != 0) //Подсчёт количества цифр в пользовательском числе//
			{
				len_for_user_num /= 10;
				cnt++;
			}
			if (n != cnt)
			{
				textcolor(LIGHTRED);
				printf("\nОшибка!\n");
				textcolor(YELLOW);
				printf("Ваше число не соответствует нужной длине!\n");
			}
			else
			{
				for (i = 0, degree = n - 1; i < n; i++, degree--) //Разбиение пользовательского числа по цифрам, //
				{												 //с последующим добавлением цифр в массив по порядку//
					int c = pow(10, degree);
					user_numberi = user_num  / c;
					user_num %= c;
					user_numbers[i] = user_numberi;
				}
				
				for (i = 0; i < n - 1; i++) //Проверка на совпадение цифр в пользовательском числе, с помощью 2х циклов for//
				{
					for (j = i + 1; j < n; j++)
					{
						if (user_numbers[i] == user_numbers[j])
						{
							textcolor(LIGHTRED);
							printf("\nОшибка!\n");
							textcolor(YELLOW);
							printf("В Вашем числе не должны встречаться повторяющиеся цифры!\nЧитайте правила внимательней!\n");
							detecter++;
							break;
						}
					}
				}
				if (detecter > 0)
				{
				}
				else
				{
					bul = 0;
					cow = 0;
					for (i = 0; i < n; i++) //Подсчёт "быков"//
					{
						if (computer_num[i] == user_numbers[i])
							bul++;
					}

					for (i = 0; i < n; i++) //Подсчёт "коров"//
					{
						for (j = 0; j < n; j++)
						{
							if (i != j)
							{
								if (computer_num[i] == user_numbers[j])
								{
									cow++;
								}
							}
						}
					}
					textcolor(YELLOW); //Вывод//
					printf("Количество коров: %d\n", cow);
					printf("Количество быков: %d\n", bul);
					hint++;
					if (n == bul) //Проверка на победу//
					{
						hint--;
						textcolor(YELLOW);
						printf("\nПобеда!\nВы угадали все число!\nКоличество попыток: %d\nХотите сыграть ещё раз? (Y/N) ", hint);
						textattr(WHITE);
						scanf_s("\n%c", &yn);
						if (yn == 'N' || yn == 'n')
						{
							textcolor(YELLOW);
							printf("\nДо свидания!\n");
							textcolor(WHITE);
							res = FALSE;
							break;
						}
						else
						{
							break;
						}
					}
				}
			}
		}
	}
}
