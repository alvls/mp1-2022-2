#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <locale.h> 
#include "mathFunctions.h"

extern int numOfFunc;
extern long double x;
extern int experiments;
extern mathFunc func;
extern mathFunc* funcs[];

void second_mode() {
	do {
		printf("  �������� ������ ������� �� ������������� ������, ����� ��������������� �����: \n  sin (1),\n  cos (2),\n  exp (3),\n  coth (4)\n  ");
		scanf("%d", &numOfFunc);
		if (numOfFunc != 1 && numOfFunc != 2 && numOfFunc != 3 && numOfFunc != 4) {
			printf("  �� ������� �������������� � ������ �������. �������� ������:\n");
			continue;
		}
	} while (numOfFunc != 1 && numOfFunc != 2 && numOfFunc != 3 && numOfFunc != 4);

	printf("  ������� ����� (�) � �������� (������: 1,213):\n  ");
	scanf("%lf", &x);

	do {
		printf("  ������� ���-�� ������������� (����������� ����� �� 25):\n  ");
		scanf("%d", &experiments);
		if (experiments < 1 || experiments > 25) {
			printf("  ������� ������������ �����. ������� ������:\n  ");
			continue;
		}
	} while (experiments < 1 || experiments > 25);

	func = funcs[numOfFunc - 1];
	func(x, 1.0, 1, 2, experiments);
}