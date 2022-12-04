#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <math.h>
#include "Header.h"

#define M_PI_2    1.57079632679489661923

enum FUNK_KEYS {
	SIN, COS, EXP, TAN,
} ;

enum CONSTANTS {
	true = 1, false = 0, CHOICE_MENU = 2, MODE_MENU = 4,
};

enum KEYS {
	ESCAPE = 27, UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13, SPACE = 32, DEL = 8,
};

char Start_Menu[CHOICE_MENU][40] = { 
	"1 режим", 
	"2 режим",
};

char Mode_Menu[MODE_MENU][10] = {
	"sin(x)",
	"cos(x)",
	"exp(x)",
	"tg(x)",
};

void Setup(void)
{
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");
	SetConsoleTitle("Расчёт значений функций через разложение в ряд Тейлора");
	system("cls");
	hidecursor();
}

void input_x(double * X)
{
		system("cls");
		textcolor(WHITE);
		printf("Задайте точку x, в которой необходимо вычислить значение: ");
		scanf_s("%lf", X);
}

void input_deviation(int * adres)
{
	system("cls");
	textcolor(WHITE);
	printf("Задайте точность вычисления в знаках после запятой (от 1 до 6): ");
	scanf_s("%d", adres);
}

void input_count(int* adres, int rezhim)
{
	system("cls");
	textcolor(WHITE);
	if (rezhim == 1)
		printf("Задайте число элементов ряда для выполнения расчета (от 1 до 1000): ");
	else
		printf("Задайте число экспериментов (от 1 до 25): ");
	scanf_s("%d", adres);
}

double factorial(int n)
{
	double answer = 1;
	for (int i = 2; i <= n; i++)
		answer *= i;
	return answer;
}

void bernulli_arr(double* B, int N)
{
	double temp;
	double a, b, c, d, sochet;
	B[0] = 1;
	B[1] = -0.5;
	for (int n = 2; n < N; n++)
	{
		temp = 0;
		if (n % 2 == 1)
			continue;
		for (int k = 0; k < n; k++)
		{
			a = factorial(n);
			b = factorial(k);
			c = factorial(n - k);
			sochet = (a) / (b * c);
			d = B[k];
			temp += sochet * d / (n - k + 1);
		}
		B[n] = -temp;
	}
}

void print_info_1(double* answer_arr, int N, double etalon)
{
	int k = (int)answer_arr[0];
	system("cls");
	printf("Эталон: %lf\n", etalon);
	printf("Функция: %lf\n", answer_arr[k]);
	printf("Разница: %lf\n", etalon - answer_arr[k]);
	printf("Выполнено %d / %d\n", k, N);
	system("pause");
	system("cls");
}

void print_info_2(double* answer_arr, int N, double etalon)
{
	printf(" №  Значение    Разница\n");
	for (int i = 1; i <= N; i++)
		printf("%2d) %lf    %lf\n", i, answer_arr[i], etalon - answer_arr[i]);
	printf("Эталон: %lf\n", etalon);
	system("pause");
	system("cls");
}

void print_error(short mode)
{
	system("cls");
	switch (mode)
	{
	case EXP:
	case SIN:
	case COS:
		printf("Что-то пошло не так, попробуйте с другими значениями ;(\n");
		break;
	case TAN:
		printf("Что-то пошло не так, возможно введенное число не подходит под x принадлежит [-pi/2; pi/2]\n");
		break;
	}
	system("pause");
}

int my_exp(double x, int c, int N, double etalon, double * answer_arr)
{
	double answer = 0;
	int p = 0;
	for (int i = 0; i <= N; i++)
	{
		answer += (pow(x, i) / factorial(i));
		answer_arr[i + 1] = answer;
		if (fabs(etalon - answer) >= pow(10, -(c + 1)))
			p++;
	}
	if (p < N)
		answer_arr[0] = p;
	else
		answer_arr[0] = p - 1;
	return 0;
}

int my_sin(double x, int c, int N, double etalon, double* answer_arr)
{
	double answer = 0;
	int p = 0, p_min = 0;
	for (int n = 0; n <= N; n++)
	{
		answer += pow(-1, n) * pow(x, 2 * n + 1) / factorial(2 * n + 1);
		answer_arr[n + 1] = answer;
		if (fabs(etalon - answer) >= pow(10, -(c + 1)))
			p++;
			
	}
	if (p < N)
		answer_arr[0] = p;
	else
		answer_arr[0] = p - 1;
	return 0;
}

int my_cos(double x, int c, int N, double etalon, double* answer_arr)
{
	double answer = 0;
	int p = 0;
	for (int n = 0; n <= N; n++)
	{
		answer += pow(-1, n) * pow(x, 2 * n) / factorial(2 * n);
		answer_arr[n + 1] = answer;
		if (fabs(etalon - answer) >= pow(10, -(c + 1)))
			p++;
	}
	if (p < N)
		answer_arr[0] = p;
	else
		answer_arr[0] = p - 1;
	return 0;
}

int my_tg(double x, int c, int N, double etalon, double* answer_arr)
{
	if (fabs(x) > M_PI_2)
		return 1;
	int temp_N = N * 2;
	double answer = 0;
	int p = 0;
	double* B = calloc((size_t)temp_N, sizeof(double));
	if (!B)
		return 1;
	bernulli_arr(B, temp_N);

	for (int n = 1; n <= N; n++)
	{
		answer += B[2 * n] * pow(-4, n) * (1 - pow(4, n)) / factorial(2 * n) * pow(x, 2 * n - 1);
		answer_arr[n + 1] = answer;
		if (fabs(etalon - answer) >= pow(10, -(c + 1)))
			p++;
	}
	if (p < N)
		answer_arr[0] = p;
	else
		answer_arr[0] = p - 1;
	free(B);
	return 0;
}

void main(void)
{
	int (*my_func[MODE_MENU]) (double, int, int, double, double*) = { my_sin, my_cos, my_exp, my_tg };
	double (*etalon_func[MODE_MENU]) (double) = { sin, cos, exp, tan };
	short active_menu1 = 0, active_menu2 = 0;
	char ch;
	int c, N;
	double x;
	double etalon;
	double * answer_arr;
	int error;

	Setup();

	while (true)
	{
		gotoxy(0, 0);
		textcolor(WHITE);
		printf("Выбор режима работы программы:");
		for (short i = 0; i < CHOICE_MENU; i++)
		{
			if (i == active_menu1)
				textcolor(LIGHTGREEN);
			else
				textcolor(LIGHTGRAY);
			gotoxy(1, i + 1);
			printf("%s", Start_Menu[i]);
		}
		ch = _getch();
		if (ch == -32)
			ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu1 == 0)
				active_menu1 = CHOICE_MENU - 1;
			else
				active_menu1--;
			break;
		case DOWN:
			if (active_menu1 == CHOICE_MENU - 1)
				active_menu1 = 0;
			else
				active_menu1++;
			break;
		case RIGHT:
		case ENTER:
			system("cls");
			short flag = true;
			active_menu2 = 0;
			switch (active_menu1)
			{
			case 0:
				while (flag)
				{
					gotoxy(0, 0);
					textcolor(WHITE);
					printf("Режим работы №1:");
					for (short i = 0; i < MODE_MENU; i++)
					{
						if (i == active_menu2)
							textcolor(LIGHTGREEN);
						else
							textcolor(LIGHTGRAY);
						gotoxy(1, i + 1);
						printf("%s", Mode_Menu[i]);
					}
					ch = _getch();
					if (ch == -32)
						ch = _getch();
					switch (ch)
					{
					case UP:
						if (active_menu2 == 0)
							active_menu2 = MODE_MENU - 1;
						else
							active_menu2--;
						break;
					case DOWN:
						if (active_menu2 == MODE_MENU - 1)
							active_menu2 = 0;
						else
							active_menu2++;
						break;
					case LEFT:
						system("cls");
						flag = false;
						break;
					case RIGHT:
					case ENTER:
						showcursor();
						input_x(&x);
						input_deviation(&c);
						input_count(&N, 1);
						hidecursor();

						answer_arr = calloc((size_t)(N + 1), sizeof(etalon));
						if (!answer_arr)
							return;

						etalon = etalon_func[active_menu2](x);
						error = my_func[active_menu2](x, c, N, etalon, answer_arr);
						if (error)
							print_error(active_menu2);
						else
							print_info_1(answer_arr, N, etalon);
						break;
					}
				}
				break;
			case 1:
				while (flag)
				{
					gotoxy(0, 0);
					textcolor(WHITE);
					printf("Режим работы №2:");
					for (short i = 0; i < MODE_MENU; i++)
					{
						if (i == active_menu2)
							textcolor(LIGHTGREEN);
						else
							textcolor(LIGHTGRAY);
						gotoxy(1, i + 1);
						printf("%s", Mode_Menu[i]);
					}
					ch = _getch();
					if (ch == -32)
						ch = _getch();
					switch (ch)
					{
					case UP:
						if (active_menu2 == 0)
							active_menu2 = MODE_MENU - 1;
						else
							active_menu2--;
						break;
					case DOWN:
						if (active_menu2 == MODE_MENU - 1)
							active_menu2 = 0;
						else
							active_menu2++;
						break;
					case LEFT:
						system("cls");
						flag = false;
						break;
					case RIGHT:
					case ENTER:
						showcursor();
						input_x(&x);
						c = 6;
						input_count(&N, 2);
						hidecursor();
						
						answer_arr = calloc((size_t)(N + 1), sizeof(etalon));
						if (!answer_arr)
							return;

						etalon = etalon_func[active_menu2](x);
						error = my_func[active_menu2](x, c, N, etalon, answer_arr);
						if (error)
							print_error(active_menu2);
						else
							print_info_2(answer_arr, N, etalon);
						break;
					}
				}
				break;
			}
			break;
		case ESCAPE:
			exit(0);
			break;
		}
	}
}
