#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "design.h"
#include <conio.h>
void exit_prog()
{
	system("cls");
	printf("Спасибо за использование программы!\n");
	system("pause");
	exit(0);
}

int GetCounts()
{
	int counts;
	system("cls");
	printf("Введите количество испытаний (от 1 до 25) - ");
	do
	{
		scanf_s("%d", &counts);
	} while (counts < 1 || counts > 25);
	system("cls");
	return counts;
}
int GetSlags()
{
	int counts;
	system("cls");
	printf("Введите количество слагаемых (от 1 до 1000) - ");
	do
	{
		scanf_s("%d", &counts);
	} while (counts < 1 || counts > 1000);
	system("cls");
	return counts;
}
double GetRates()
{
	double rate;
	system("cls");
	printf("Введите точность вычисления (>= 0,000001) - ");
	do
	{
		scanf_s("%lf", &rate);
	} while (rate < 0.000001);
	system("cls");
	return rate;
}
void FirstMode(void(*function)(double, double, int), double x, double ethalon)
{
	double rate;
	int count;
	rate = GetRates();
	count = GetSlags();
	printf("\nЭталонное значение:   %lf\n", ethalon);
	printf("\nКол-во слагаемых   Вычисленная оценка функции   Разница между оценкой и эталоном\n");
	function(x, rate, count);
}
void SecondMode(void(*function)(double, double, int), double x, double ethalon)
{
	int count, i;
	count = GetCounts();
	printf("Эталонное значение:   %lf\n", ethalon);
	printf("\nКол-во слагаемых   Вычисленная оценка функции   Разница между оценкой и эталоном\n");
	for (i = 0; i < count; i++)
		function(x, -2, i + 1);
}
void hello(Start)
{
	if (Start == 0)
	{
		printf("Добро пожаловать в программу расчета значений мат. функций\n");
		printf("В программе реализовано два режима работы:\n");
		printf("В первом режиме вы сами задаете точность вычислений и количество слагаемых\n");
		printf("Во втором режиме вы задаете количество экспериментов, по которым высчитывается значение\n");
		system("pause");
		system("cls");
	}
}
int menu_mode(char* arr[], int size)
{
	char ch = 0;
	int choice = 1, i;
	while (ch != 13)
	{
		system("cls");
		for (i = 0; i < size; i++)
		{
			if (i == choice)
			{
				textcolor(BLUE);
			}
			else
			{
				textcolor(WHITE);
			}
			printf("%s \n", arr[i]);
		}
		hidecursor();
		textcolor(WHITE);
		ch = _getch();
		if (ch == -32)
			ch = _getch();
		switch (ch)
		{
		case 72:
			choice--;
			break;
		case 80:
			choice++;
			break;
		case 27:
			exit_prog();
		}
		if (choice >= size)
			choice = 1;
		if (choice < 1)
			choice = size - 1;
	}
	return choice;
}