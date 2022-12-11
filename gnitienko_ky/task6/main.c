#include <math.h>
#include <stdio.h>
#include <locale.h>
#include "Header.h"

#define KEY_EXIT 27
#define KEY_ENTER 13

char* menu1[3] = { (char*)"Выберите режим работы программы", (char*)"1. Однократный расчет функции в заданной точке", (char*)"2. Серийный эксперимент" };
char* menu2[5] = { (char*)"Выберите функцию", (char*)"1. sin(x)", (char*)"2. cos(x)", (char*)"3. exp(x)", (char*)"4. tg(x)" };

void (*pointer)(double, long double, int);

void main() {
    setlocale(LC_ALL, "Rus");

    int method = 0;
    int x = 0, N = 0;
    double T = 0;

    while (method != KEY_EXIT) {
        method = menu(menu1, 3);
        if (method == KEY_EXIT) break;
        if (method == 1)
            pointer = results;
        if (method == 2)
            pointer = results2;
        system("cls");
        int func = 0;
        while (func != KEY_EXIT) {
            func = menu(menu2, 5);
            switch (func) {
            case 1: {
                if (method == 1) {
                    enterx(&x, &T, &N);
                    system("cls");
                    sinus(x, T, N, pointer);
                }
                if (method == 2) {
                    enterx2(&x, &T, &N);
                    system("cls");
                    sinus2(x, T, N, pointer);
                }
                system("pause");
                break;
            }
            case 2: {
                if (method == 1) {
                    enterx(&x, &T, &N);
                    system("cls");
                    cosinus(x, T, N, pointer);
                }
                if (method == 2) {
                    enterx2(&x, &T, &N);
                    system("cls");
                    cosinus2(x, T, N, pointer);
                }
                system("pause");
                break;
            }
            case 3: {
                if (method == 1) {
                    enterx(&x, &T, &N);
                    system("cls");
                    exponent(x, T, N, pointer);
                }
                if (method == 2) {
                    enterx2(&x, &T, &N);
                    system("cls");
                    exponent2(x, T, N, pointer);
                }
                system("pause");
                break;
            }
            case 4: {
                if (method == 1) {
                    enterx(&x, &T, &N);
                    system("cls");
                    tg(x, T, N, pointer);
                }
                if (method == 2) {
                    enterx2(&x, &T, &N);
                    system("cls");
                    tg2(x, T, N, pointer);
                }
                system("pause");
                break;
            }
            }
        }
    }
}