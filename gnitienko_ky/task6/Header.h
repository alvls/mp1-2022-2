#pragma once
#include <Windows.h>
#include <stdio.h>
#include "Header.h"
#include <conio.h>
#include <io.h>

int menu(char* menu[], int j);
void (*pointer)(double, double, int);

void enterx(int* x, double* T, int* N);
void enterx2(int* x, double* T, int* N);
long factorial(int x);
void sinus(double x, double T, int N, void (*pointer)(double, double, int));
void cosinus(double x, double T, int N, void (*pointer)(double, double, int));
void exponent(double x, double T, int N, void (*pointer)(double, double, int));
void results(double a, double b, int count);
void results2(double a, double b, int count);

void sinus2(double x, double T, int N, void (*pointer)(double, double, int));
void cosinus2(double x, double T, int N, void (*pointer)(double, double, int));
void exponent2(double x, double T, int N, void (*pointer)(double, double, int));
void bernulli(double* B, int N);
void tg(double x, double T, int N, void (*pointer)(double, double, int));
void tg2(double x, double T, int N, void (*pointer)(double, double, int));