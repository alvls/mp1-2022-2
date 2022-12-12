#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <locale.h> 
#include "mathFunctions.h"
#include "secondMode.h"
#include "firstMode.h"

int numOfMode = 0;
int numOfFunc = 0;
long double x = 0;
int experiments = 0;
long double acc = 0;
int num_of_row_elem = 0;
mathFunc func;
mathFunc* funcs[] = { taylorSin, taylorCos, taylorExp, taylorCoth };

void greetings() {
	printf("\n  Добрый день! Данная программа выполняет расчет значений для некоторого набора функций в заданной точке с заданной погрешностью за счет разложения этих функций в ряд Тейлора.\n  Программа работает в 2 режимах.\n\n  Первый режим - однократный расчет функции в заданной точке.\n  Второй режим - серийный эксперимент.\n");
}

int chooseMode() {
	int choosenMode = 0;
	printf("  Выберите режим работы программы (1/2):\n  ");
	scanf("  %d", &choosenMode);
	if (choosenMode == 1) {
		return 1;
	}
	else if (choosenMode == 2) {
		return 2;
	}
	else {
		printf("  Такого режима работы нет. Выберите один из двух возможных режимов.\n\n");
		return 0;
	}

}

void main(){

	setlocale(LC_ALL, "Rus");

	greetings();

	while (numOfMode == 0){
		numOfMode = chooseMode();
		if (numOfMode == 1) {
			first_mode();
		}
		else if (numOfMode == 2) {
			second_mode();
		}
	}

	printf("  Спасибо за работу!\n");

	system("pause");
}