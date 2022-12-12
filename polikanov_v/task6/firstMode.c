#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <locale.h> 
#include "mathFunctions.h"

extern int numOfFunc;
extern long double x;
extern long double acc;
extern int num_of_row_elem;
extern mathFunc func;
extern mathFunc* funcs[];


void first_mode() {
	do {
		printf("  Выберите нужную функцию из предложенного набора, введя соответствующую цифру: \n  sin (1),\n  cos (2),\n  exp (3),\n  coth (4)\n  ");
		scanf("%d", &numOfFunc);
		if (numOfFunc != 1 && numOfFunc != 2 && numOfFunc != 3 && numOfFunc != 4) {
			printf("  Вы выбрали несуществующую в наборе функцию. Выберите заново:\n");
			continue;
		}
	} while (numOfFunc != 1 && numOfFunc != 2 && numOfFunc != 3 && numOfFunc != 4);

	printf("  Введите точку (х) в радианах (пример: 1,213):\n  ");
	scanf("%lf", &x);

	do {
		printf("  Задайте точность вычисления (>= 0,000001):\n  ");
		scanf("%lf", &acc);
		if (acc < 0.000001) {
			printf("  Введена недопустимая точность. Введите заново:\n");
			continue;
		}
	} while (acc < 0.000001);

	do {
		printf("  Задайте число элементов ряда для выполнения расчета (N - от 1 до 1000)\n  ");
		scanf("%d", &num_of_row_elem);
		if (num_of_row_elem < 1 || num_of_row_elem > 1000) {
			printf("  Введено недопустимое число элементов ряда. Введите заново:\n  ");
			continue;
		}
	} while (num_of_row_elem < 1 || num_of_row_elem > 1000);

	func = funcs[numOfFunc - 1];
	func(x, acc, num_of_row_elem, 1, 1);
}