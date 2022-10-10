#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
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
	while (res == TRUE) //Цикл для повтора игры//
	{
		srand(time(0));

		int cnt = 0, len_for_user_num = 0, i = 1, hint = 1, number0 = 10, number1 = 10, number2 = 10, number3 = 10;
		int n = 0, detecter, user_num, user_num_clone, user_numberi = 11, bol = 0, cow = 0;
		const int COUNT = 9, COUNT_word = 8, COUNT_num = 8;

		char ch, yn, array[] = {'W', 'e', 'l', 'c', 'o', 'm', 'e', '!'}; //Создаём массивы//
		int num[4], user_numbers[] = { 11, 12, 13, 14 }, rand_nums[4];

		printf("               ");
		for (int j = 0; j < COUNT_word; j++) //Выводим каждый элемент массива по отдельности при этом, меняем цвет элемента//
		{
			while (i < COUNT)
			{
				textcolor(i);
				printf("%c", array[j]);
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

		number0 = 1 + rand() % 9; //Создание случайного числа с не повторяющимися числами, с последующим добавлением в массив//
		if (n == 2)
		{
			while ((number1 = rand() % 9) == number0);
			num[0] = number1;
			num[1] = number0;
		}
		else if (n == 3)
		{
			while (number2 == number0 || number2 == number1 || number0 == number1)
			{
				number1 = rand() % 9;
				number2 = rand() % 9;
			}
			num[0] = number2;
			num[1] = number1;
			num[2] = number0;
		}
		else if (n == 4)
		{
			while (number2 == number0 || number2 == number1 || number0 == number1 || number3 == number0 || number3 == number1 || number3 == number2)
			{
				number1 = rand() % 9;
				number2 = rand() % 9;
				number3 = rand() % 9;
			}
			num[0] = number3;
			num[1] = number2;
			num[2] = number1;
			num[3] = number0;
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
				hint++;
			}
			else
			{
				for (int i = 0; i < 4; i++) //Разбиение пользовательского числа по цифрам//
				{
					if (user_num == 0)
						break;
					user_numberi = user_num % 10;
					user_num /= 10;
					user_numbers[i] = user_numberi;
				}
				for (int i = 0; i < 2; i++) //Проверка на совпадение цифр в пользовательском числе, с помощью 2х циклов for//
				{
					for (int j = i + 1; j < 3; j++)
					{
						if (user_numbers[i] == user_numbers[j])
						{
							textcolor(LIGHTRED);
							printf("\nОшибка!\n");
							textcolor(YELLOW);
							printf("В Вашем числе не должны встречаться повторяющиеся цифры!\nЧитайте правила внимательней!\n");
							detecter++;
							hint++;
							break;
						}
					}
					break;
				}
				if (detecter > 0)
				{
				}
				else
				{
					bol = 0;
					cow = 0;
					for (int i = 0; i < 4; i++) //Подсчёт "быков"//
					{
						if (num[i] == user_numbers[i])
							bol++;
					}

					for (int i = 3; i >= 0; i--) //Подсчёт "коров"//
					{
						for (int j = 3; j >= 0; j--)
						{
							if (i == j)
							{
								if (num[i] == user_numbers[j - 1])
									cow++;
								break;
							}
							if (num[i] == user_numbers[j])
								cow++;
						}
					}
					textcolor(YELLOW); //Вывод//
					printf("Количество коров: %d\n", cow);
					printf("Количество быков: %d\n", bol);
					hint++;
					if (n == bol) //Проверка на победу//
					{
						textcolor(YELLOW);
						printf("\nПобеда!\nВы угадали все число!\nХотите сыграть ещё раз? (Y/N)\n");
						textattr(WHITE);
						scanf_s("\n%c", &yn);
						if (yn == 'N' || yn == 'n')
						{
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
