#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Maths.h"

void function(double x, double definition, int n, short choice)
{
	double etalon, now = 0;
	int i = 0;
	double* experiments = (double*)malloc(n * sizeof(double));
	if ((choice == 4) || (choice == 5))
		etalon = choice_of_function1[choice](x + 1);
	else etalon = choice_of_function1[choice](x);
	printf("��������� ��������: %lf\n", etalon);
	do
	{
		now += choice_of_function2[choice](x, i);
		experiments[i] = now;
		i++;
	} while (((fabs(etalon - now) > definition) || (definition == 5)) && (i < n));
	if (definition != 5)
		printf("���������� ���������: %d\n������ ��������: %lf\n�������� ����� ������� � ��������� ���������: %lf\n", i, experiments[i - 1], etalon - experiments[i - 1]);
	else
	{
		printf("���������� ���������   ������ ��������   �������� ����� ������� � ��������� ���������\n", i, experiments[i - 1], etalon - experiments[i - 1]);
		for (int j = 0; j < i; j++)
		{
			if (j<9)
			printf("%d %29lf %17lf\n", j + 1, experiments[j], etalon - experiments[j]);
			else printf("%d %28lf %17lf\n", j + 1, experiments[j], etalon - experiments[j]);
		}
	}
	free(experiments);
}

void clean_of_buffer()
{
	while (getchar() != '\n');
}

void main()
{
	double x, definition;
	int n = 0, mode;
	short choice;
	char answer;
	setlocale(LC_ALL, "Rus");
	filling();
	printf("������ ����!\n������ ��������� ��������� ��������� ������ �������� ��� ���������� ������ ������� � �������� ����� � �������� ������������ �� ���� ���������� ���� ������� � ��� �������.\n");
	do
	{
		printf("������� ����� ������(1 - ����������� ������, 2 - �������� �����������): ");
		scanf_s("%d", &mode);
		clean_of_buffer();
		definition = 5;
		if ((mode == 1) || (mode == 2))
		{
			do
			{
				printf("������� ����� �������:\n1. exp(x)\n2. sin(x)\n3. cos(x)\n4. arcsin(x) (-1 <= x <= 1)\n5. lg(x) (-1 < x <= 1)\n6. sqrt(x) (-1 <= x <= 1)\n7. arctg(x) (-1 <= x <= 1)\n8. sh(x)\n9. ch(x)\n10. arsh(x) (-1 < x < 1)\n11. arth(x) (-1 < x < 1)\n��� ����� ");
				scanf_s("\n%hi", &choice);
				clean_of_buffer();
				if ((choice < 12) && (choice > 0))
				{
					choice--;
					do
					{
						if (mode == 1)
						{
							printf("������� ����� ������ �������� ��������� (x), �������� ���������� � ���������� ��������� (����������: ����� � ��������� ������ ���������� ������� � �������(�������� 0,6)): ");
							scanf_s("%lf", &x);
							scanf_s("%lf", &definition);
							scanf_s("%d", &n);
							clean_of_buffer();
						}
						else if (mode == 2)
						{
							printf("������� ����� ������ �������� ��������� (x) � ���������� ��������� (����������: ����� � ��������� ������ ���������� ������� � �������(�������� 0,6)): ");
							scanf_s("%lf", &x);
							scanf_s("%d", &n);
							clean_of_buffer();
						}
						if ((n > 5000) || (n < 0))
							printf("���������� ��������� ������� �����������. ����������, ���������, �� �������� �� ��� ������� ������� ��� ������� ���������. ������ �� �� ������ ��������� �����, ������� ������ �������, ������� ����� ��� ��������� ������ ���������? (����� �������� ��������� ������� 'x', ������� ������ ������� - 'f', ������� ����� - 'm', ��������� ������ ��������� - 'e')");
						else if (n == 0) 
							printf("��������� ������� �����������. ����������, ��������� ������������ ����� ����������. ������ �� �� ������ ��������� �����, ������� ������ �������, ������� ����� ��� ��������� ������ ���������? (����� �������� ��������� ������� 'x', ������� ������ ������� - 'f', ������� ����� - 'm', ��������� ������ ��������� - 'e')");
						else if (!((fabs(x) <= 1) && ((choice == 3) || (choice == 5) || (choice == 6))) && !((fabs(x) < 1) && ((choice == 9) || (choice == 10) || (choice == 4))) && !((x == 1) && (choice == 4)) && !(choice==0) && !(choice == 1) && !(choice == 2) && !(choice == 7) && !(choice == 8))
							printf("��������� �������� ��������� �� ������ � ������� ����������� �������. ������ �� �� ������ ��������� �����, ������� ������ �������, ������� ����� ��� ��������� ������ ���������? (����� �������� ��������� ������� 'x', ������� ������ ������� - 'f', ������� ����� - 'm', ��������� ������ ��������� - 'e')");
						else
						{
							function(x, definition, n, choice);
							printf("������ �� �� ������� ������ �������, �������� ��������� ������ ��� ������� �����? (����� ������� ������ �������, ������� 'f', �������� ��������� - 'x', ������� ����� - 'm', ��������� ������ ��������� - 'e')");
						}
						scanf_s("%c", &answer);
						clean_of_buffer();
					} while (answer == 'x');
				}
				else
				{
					printf("����� ������ ������ �����������. ������ �� �� ������� ������ ������� (��� ������� ��� �� �����), ������� ����� ��� ��������� ������ ���������? (����� ������� ������ �������, ������� 'f', ������� ����� - 'm', ��������� ������ ��������� - 'e')");
					scanf_s("%c", &answer);
					clean_of_buffer();
				}
			} while (answer == 'f');
		}
		else
		{
			printf("����� ������ ������ �����������. ������ �� �� ������ ����� ������ ����� ��� ��������� ������ ���������? (����� ������ ����� ������ �����, ������� 'm', ��������� ������ ��������� - 'e')\n");
			scanf_s("%c", &answer);
			clean_of_buffer();
		}
	} while (answer == 'm');
	printf("�� ��������! �������� ���)\n");
	system("pause");
}