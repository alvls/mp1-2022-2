#define ARROW_UP 72
#define ARROW_DOWN 80
#define ENTER 13


#include <stdio.h>
#include <math.h>
#include <locale.h>
#include "Console.h"
#include "MyMathFuncs.h"

char mod_menu[2][45] = { "����������� ������ ������� � �������� �����", "�������� �����������" };
char func_menu[4][10] = { "sin(x)", "cos(x)", "exp(x)", "sqrt(1+x)" };

void printf_mode1(double calculated_value, double etalon_value, int count_of_terms, int N)
{

	textcolor(LIGHTBLUE);
	printf(" * ��������� ��������: %lf\n", etalon_value);
	printf(" * ������������ ��������: %lf\n", calculated_value);
	printf(" * �����������: %lf\n", fabs(etalon_value - calculated_value));
	printf(" * ���������� ���������: %d/%d\n", count_of_terms, N);
	textcolor(WHITE);

}

void printf_mode2(double calculated_value, double etalon_value, int count_of_terms)
{
	printf("%2d) %15lf %15lf\n", count_of_terms + 1, calculated_value, fabs(etalon_value - calculated_value));
}

void mode1(double (*myfunc)(double, int), double (*et_func)(double), double x, double inaccuracy) // single calculation
{
	int n;
	printf("������� �������� ���������� (>= 0.000001): ");
	scanf_s("%lf", &inaccuracy);
	printf("������� ����� ��������� ���� ������� (1-1000): ");
	scanf_s("%d", &n);
	if (inaccuracy < 0.000001)
	{
		textcolor(LIGHTRED);
		printf("�������� ���������� ������ ���� >= 0.000001!\n");
		system("PAUSE");

		return;
	}
	double res = 0, etalon_value = et_func(x);
	int cnt = 0;
	do {
		res += myfunc(x, cnt);
		cnt++;
	} while ((fabs(etalon_value - res) > inaccuracy) && (cnt < n));
	printf_mode1(res, etalon_value, cnt, n);
}

void mode2(double (*myfunc)(double, int), double (*et_func)(double), double x) // serial experiment
{
	int NMax;
	printf("������� ����� ������������� (1-25): ");
	scanf_s("%d", &NMax);
	if ((NMax < 1) || (NMax > 25))
	{
		textcolor(LIGHTRED);
		printf("����� ������������� ������ ���� �� 1 �� 25!\n");
		system("PAUSE");
		system("cls");
		return;
	}

	double res = 0, etalon_value = et_func(x);
	int cnt = 0;
	textcolor(LIGHTBLUE);
	printf(" �  ����������� ��������  �����������\n");
	textcolor(WHITE);
	do {
		res += myfunc(x, cnt);
		printf_mode2(res, etalon_value, cnt);
		cnt++;
	} while (cnt < NMax);
	textcolor(LIGHTGREEN);
	printf("   * ��������� �������� = %lf\n", etalon_value);
	textcolor(WHITE);
}

double sqrt_1plusx_eth(double x)
{
	return sqrt(1 + x);
}
double (*myFuncs_pointers[4])(double, int) = { sinus, cosinus, exponent, sqrt_1plusx };
double (*etalonFuncs_pointers[4])(double) = { sin, cos, exp, sqrt_1plusx_eth };
double (*mode_pointers[2])(double (*myfunc)(double, int), double (*et_func)(double), double) = { mode1, mode2 };


void main()
{
	char key;
	short menu_selection_mode = 0, menu_selection_func = 0;
	setlocale(LC_ALL, "RUS");
	system("chcp 1251");
	clrscr();
	system("title ������ �������� ������� � �������� ����� ���� �� ���������� � ��� �������");
	hidecursor();
	while (1)
	{
		clrscr();
		textcolor(WHITE);
		hidecursor();
		printf("�������� �����:\n");
		for (int i = 0; i < 2; i++)
		{
			if (i == menu_selection_mode)
				textcolor(BROWN);
			else
				textcolor(DARKGRAY);
			printf("  %s\n", mod_menu[i]);
		}
		key = _getch();
		if (key == -32)
			key = getch();

		switch (key)
		{
		case ARROW_UP:
			if (menu_selection_mode > 0)
				--menu_selection_mode;
			else
				menu_selection_mode += 2 - 1;
			break;
		case ARROW_DOWN:
			if (menu_selection_mode < 2 - 1)
				++menu_selection_mode;
			else
				menu_selection_mode -= 2 - 1;
			break;
		case ENTER:
			clrscr();
			textcolor(WHITE);
			double x, inaccuracy;
			int n;
			while (key != -1)
			{
				clrscr();
				textcolor(WHITE);
				hidecursor();
				printf("�������� �������:\n");
				for (int i = 0; i < 4; i++)
				{
					if (i == menu_selection_func)
						textcolor(BROWN);
					else
						textcolor(DARKGRAY);
					printf("  %s\n", func_menu[i]);
				}
				key = _getch();
				if (key == -32)
					key = getch();
				switch (key)
				{
				case ARROW_UP:
					if (menu_selection_func > 0)
						--menu_selection_func;
					else
						menu_selection_func = menu_selection_func + 4 - 1;
					break;
				case ARROW_DOWN:
					if (menu_selection_func < 4 - 1)
						++menu_selection_func;
					else
						menu_selection_func = menu_selection_func - 4 + 1;
					break;
				case ENTER:
					clrscr();
					textcolor(WHITE);
					printf("������� ����� �, � ������� ���������� ��������� ��������: ");
					scanf_s("%lf", &x);
					if (menu_selection_func == 3 && fabs(x) > 1)
					{
						textcolor(RED);
						printf("��������� ��������� ��������! |x| �� ������ ��������� 1\n");
						textcolor(WHITE);
						system("PAUSE");
						key = -1;
						break;
					}
					mode_pointers[menu_selection_mode](myFuncs_pointers[menu_selection_func], etalonFuncs_pointers[menu_selection_func], x);
					key = -1;
					getch();
				}
			}

		}


	}
	system("PAUSE");
}
