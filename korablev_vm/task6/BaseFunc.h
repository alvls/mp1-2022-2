#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>

void exit_prog();
int GetCounts();
int GetSlags();
double GetRates();
void FirstMode(void(*function)(double, double, int), double x, double ethalon);
void SecondMode(void(*function)(double, double, int), double x, double ethalon);
void hello(Start);
int menu_mode(char* arr[], int size);