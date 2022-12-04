#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <conio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

#include "omp.h"
#include "MyMath.h"


#define ESCAPE 27
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define SPACE 32
#define BS 8
#define pi 3.1415926535
enum { True = 1, False = 0, SIZE1 = 2, SIZE2 = 9 };

char menu1[SIZE1][20] = { "������ �����", "������ �����" };
char menu2[SIZE2][10] = { "sin(x)", "cos(x)", "exp(x)", "sec(x)", "sh(x)", "ch(x)", "ln(1+x)", "arth(x)", "tg(x)"};



void main()
{
	setlocale(LC_ALL, "Russian");
	textcolor(GREEN);
	hidecursor();
	system("title ������� �������� �������������� �������");
	short active_menu1 = 0, active_menu2 = 0;
	char znak2, c;
	void (*pointer)(double, double, int);
	while (True)
	{
		system("cls");
		char znak;
		gotoxy(0, 0);
		hidecursor();
		textcolor(LIGHTGREEN);
		printf("�������� ����� ������:");
		for (long i = 0; i < SIZE1; i++)
		{
			if (i == active_menu1)
				textcolor(LIGHTGREEN);
			else
				textcolor(LIGHTGRAY);
			gotoxy(1, 1 + i);
			printf("* %s *", menu1[i]);
		}
		znak = _getch();
		if (znak == -32)
			znak = _getch();
		switch (znak)
		{
		case DOWN:
			if (active_menu1 < SIZE1 - 1)
				++active_menu1;
			else
				active_menu1 -= SIZE1 - 1;
			break;
		case UP:
			if (active_menu1 > 0)
				--active_menu1;
			else
				active_menu1 += SIZE1 - 1;
			break;
		case'1':
			active_menu1 = 0;
			break;
		case '2':
			active_menu1 = 1;
			break;
		case BS:
		case ESCAPE:
			exit(0);
			break;
		case SPACE:
		case RIGHT:
		case ENTER:
			system("cls");
			short mode = 1;
			double pog, x;
			int n, NMax;
			while (mode)
			{
				textcolor(GREEN);
				gotoxy(0, 0);
				printf("�������� �������:");
				for (int k = 0; k < SIZE2; k++)
				{
					if (active_menu2 == k)
						textcolor(LIGHTGREEN);
					else
						textcolor(LIGHTGRAY);
					gotoxy(1, k + 1);
					printf("* %s *", menu2[k]);
				}
				znak2 = _getch();
				if (znak2 == -32)
					znak2 = _getch();
				switch (znak2)
				{
				case UP:
					if (active_menu2 > 0)
						--active_menu2;
					else
						active_menu2 = active_menu2 + SIZE2 - 1;
					break;
				case DOWN:
					if (active_menu2 < SIZE2 - 1)
						++active_menu2;
					else
						active_menu2 = active_menu2 - SIZE2 + 1;
					break;
				case ESCAPE:
					exit(0);
					break;
				case '1':
					active_menu2 = 0;
					break;
				case '2':
					active_menu2 = 1;
					break;
				case '3':
					active_menu2 = 2;
					break;
				case '4':
					active_menu2 = 3;
					break;
				case '5':
					active_menu2 = 4;
					break;
				case '6':
					active_menu2 = 5;
					break;
				case '7':
					active_menu2 = 6;
					break;
				case '8':
					active_menu2 = 7;
				case '9':
					active_menu2 = 8;
					break;
					break;
				case BS:
				case LEFT:
					mode = 0;
					break;
				case SPACE:
				case RIGHT:
				case ENTER:
					system("cls");
					textcolor(GREEN);
					if (active_menu1 == 0)
					{
						pointer = myprintf;
						printf("������� ����� �: ");
						scanf_s("%lf", &x);
						while (c = getchar() != '\n');
						printf("������� ����������� (�� ����� 0.000001): ");
						scanf_s("%lf", &pog);
						if (pog < 0.000001)
						{
							textcolor(RED);
							printf("������� ��������� ��������\n");
							system("PAUSE");
							system("cls");
							break;
						}
						while (c = getchar() != '\n');
						printf("������� ���������� ������ ���� �������(1 - 1000): ");
						scanf_s("%d", &n);
						if ((n < 1) || (n > 1000))
						{
							textcolor(RED);
							printf("�������� ��������\n");
							system("PAUSE");
							system("cls");
							break;
						}
						while (c = getchar() != '\n');
						system("cls");
						gotoxy(0, 0);
						switch (active_menu2)
						{
						case 0:
							sinus(x, pog, n, pointer);
							break;
						case 1:
							cosinus(x, pog, n, pointer);
							break;
						case 2:
							exponenta(x, pog, n, pointer);
							break;
						case 3:
							if (n > 25)
							{
								textcolor(RED);
								printf("������� ������� �����\n");
								system("PAUSE");
								system("cls");
								break;
							}
							secans(x, pog, n, pointer);
							break;
						case 4:
							sh(x, pog, n, pointer);
							break;
						case 5:
							ch(x, pog, n, pointer);
							break;
						case 6:
							if (x >= 1 || x <= -1)
							{
								textcolor(RED);
								printf("�������� �� ����������\n");
								system("PAUSE");
								system("cls");
								break;
							}
							ln(x, pog, n, pointer);
							break;
						case 7:
							if (x >= 1 || x <= -1)
							{
								textcolor(RED);
								printf("�������� �� ����������\n");
								system("PAUSE");
								system("cls");
								break;
							}
							arth(x, pog, n, pointer);
							break;
						case 8:
							if (x >= pi/2 || x <= -pi/2)
							{
								textcolor(RED);
								printf("�������� �� ����������\n");
								system("PAUSE");
								system("cls");
								break;
							}
							tg(x, pog, n, pointer);
							break;
						}
						system("PAUSE");
						system("cls");
						break;
					}
					else
					{
						pointer = myprint;
						printf("������� ����� �: ");
						scanf_s("%lf", &x);
						while (c = getchar() != '\n');
						printf("������� ����� ������������� (1 - 25): ");
						scanf_s("%d", &NMax);
						if (NMax > 25 || NMax < 1)
						{
							textcolor(RED);
							printf("�������� ��������\n");
							system("PAUSE");
							system("cls");
							break;
						}
						while (c = getchar() != '\n');
						system("cls");
						printf("�����:     ��������� ��������:     ������������ ��������:    ��������:\n");
						printf("--------------------------------------------------------------------------\n");
						for (int i = 0; i < NMax; i++)
						{
							switch (active_menu2)
							{
							case 0:
								sinus(x, -1, i + 1, pointer);
								break;
							case 1:
								cosinus(x, -1, i + 1, pointer);
								break;
							case 2:
								exponenta(x, -1, i + 1, pointer);
								break;
							case 3:
								secans(x, -1, i + 1, pointer);
								break;
							case 4:
								sh(x, -1, i + 1, pointer);
								break;
							case 5:
								ch(x, -1, i + 1, pointer);
								break;
							case 6:
								if (x >= 1 || x <= -1)
								{
									textcolor(RED);
									printf("�������� �� ����������\n");
									system("PAUSE");
									system("cls");
									continue;
								}
								ln(x, -1, i + 1, pointer);
								break;
							case 7:
								if (x >= 1 || x <= -1)
								{
									textcolor(RED);
									printf("�������� �� ����������\n");
									system("PAUSE");
									system("cls");
									continue;
								}
								arth(x, -1, i + 1, pointer);
								break;
							case 8:
								if (x >= pi * 0.5 || x <= pi * (-0.5))
								{
									textcolor(RED);
									printf("�������� �� ����������\n");
									system("PAUSE");
									system("cls");
									continue;
								}
								tg(x, -1, i + 1, pointer);
								break;
							}
						}
						system("PAUSE");
						system("cls");
						break;
					}
				}
			}
		}
	}
}

