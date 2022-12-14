#include "Header.h"
#include <math.h>

void results(double a, double b, int count) {
	printf("Ýòàëîííîå çíà÷åíèå: ");
	printf("%lf\n", a);
	printf("Âû÷èñëåííîå çíà÷åíèå: ");
	printf("%.6lf\n", b);
	printf("Ðàçíèöà ìåæäó çíà÷åíèÿìè: ");
	printf("%.6lf\n", fabs(a - b));
	printf("Êîë-âî ñëàãàåìûõ: ");
	printf("%d\n", count);
}

void results2(long double a, long double b, int count) {
	printf("%d ", count);
	printf("%50.6Lf", b);
	printf("%50.6Lf\n", fabs(a - b));
}

void enterx(double* x, double* T, int* N) {
	system("cls");
	printf("Ââåäèòå òî÷êó õ, â êîòîðîé íåîáõîäèìî âû÷èñëèòü çíà÷åíèå: ");
	scanf_s("%lf", x);
	printf("Ââåäèòå òî÷íîñòü âû÷èñëåíèÿ >= 0,000001: ");
	scanf_s("%lf", T);
	printf("Çàäàéòå ÷èñëî ýëåìåíòîâ ðÿäà N: ");
	scanf_s("%d", N);
}

void enterx2(double* x, double* T, int* N) {
	system("cls");
	printf("Ââåäèòå òî÷êó õ, â êîòîðîé íåîáõîäèìî âû÷èñëèòü çíà÷åíèå: ");
	scanf_s("%lf", x);
	printf("Ââåäèòå òî÷íîñòü âû÷èñëåíèÿ >= 0,000001: ");
	scanf_s("%lf", T);
	printf("Çàäàéòå êîë-âî ýêñïåðèìåíòîâ N: ");
	scanf_s("%d", N);
}

long double factorial(int x) {
	long double fact = 1;
	for (int i = 1; i <= x; i++)
		fact *= i;
	return fact;
}

void sinus(double x, double T, int N, void (*pointer)(double, double, int)) {
	long double sum = 0;
	int count = 0;
	do {
		sum += pow((-1), count) * ((pow(x, 2 * count + 1)) / factorial(2 * count + 1));
		count++;
	} while ((fabs(sin(x) - sum) > T) && (count < N));
	pointer(sin(x), sum, count);
}

void cosinus(double x, double T, int N, void (*pointer)(double, double, int)) {
	long double sum = 0;
	int count = 0;
	do {
		sum += pow((-1), count) * ((pow(x, 2 * count)) / factorial(2 * count));
		count++;
	} while ((fabs(cos(x) - sum) > T) && (count < N));
	pointer(cos(x), sum, count);
}

void exponent(double x, double T, int N, void (*pointer)(double, double, int)) {
	long double sum = 0;
	int count = 0;
	do {
		sum += pow(x, count) / factorial(count);
		count++;
	} while ((fabs(exp(x) - sum) > T) && (count < N));
	pointer(exp(x), sum, count);
}

void sinus2(double x, double T, int N, void (*pointer)(double, double, int)) {
	long double sum = 0;
	printf("Ýòàëîííîå çíà÷åíèå: %lf \n", sin(x));
	printf("Êîë-âî ñëàãàåìûõ                       Âû÷èñëåííîå çíà÷åíèå                        Ðàçíèöà ìåæäó çíà÷åíèÿìè\n");
	for (int i = 0; i <= N; i++) {
		sum += pow((-1), i) * ((pow(x, 2 * i + 1)) / factorial(2 * i + 1));
		pointer(sin(x), sum, i);
	}
}

void cosinus2(double x, double T, int N, void (*pointer)(double, double, int)) {
	long double sum = 0;
	printf("Ýòàëîííîå çíà÷åíèå: %lf \n", cos(x));
	printf("Êîë-âî ñëàãàåìûõ                       Âû÷èñëåííîå çíà÷åíèå                        Ðàçíèöà ìåæäó çíà÷åíèÿìè\n");
	for (int i = 0; i <= N; i++) {
		sum += pow((-1), i) * ((pow(x, 2 * i)) / factorial(2 * i));
		pointer(cos(x), sum, i);
	}
}

void exponent2(double x, double T, int N, void (*pointer)(double, double, int)) {
	long double sum = 0;
	printf("Ýòàëîííîå çíà÷åíèå: %lf \n", exp(x));
	printf("Êîë-âî ñëàãàåìûõ                       Âû÷èñëåííîå çíà÷åíèå                        Ðàçíèöà ìåæäó çíà÷åíèÿìè\n");
	for (int i = 0; i <= N; i++) {
		sum += pow(x, i) / factorial(i);
		pointer(exp(x), sum, i);
	}
}

void bernulli(double* B, int N) {
	memset(B, 0, N * sizeof(double));
	int n, k;
	long double C = 0, sum;
	B[0] = 1;
	B[1] = -0.5;
	for (n = 2; n < N; n += 2) {
		sum = 0;
		for (k = 1; k <= n; k++) {
			C = (factorial(n + 1) / (factorial(k + 1) * factorial(n - k)));
			sum += C * B[n - k];
		}
		B[n] = sum * (-1.) / (n + 1);
	}
}

void tg(double x, double T, int N, void (*pointer)(double, double, int)) {
	long double sum = 0;
	int count = 0;
	double* B = (double*)malloc(N * sizeof(double));
	bernulli(B, N);
	if (fabs(x) < (3.141592653 / 2)) {
		do {
			sum += ((B[2 * count] * pow(-4, count) * (1 - pow(4, count))) / factorial(2 * count)) * pow(x, 2 * count - 1);
			count++;
		} while ((fabs(tan(x) - sum) > T) && (count < N));
		free(B);
		pointer(tan(x), sum, count);
	}
	else { printf("Ââîäèòå õ, ãäå |x| < pi/2\n"); free(B); }
}

void tg2(double x, double T, int N, void (*pointer)(double, double, int)) {
	long double sum = 0;
	double* B = (double*)malloc(N * sizeof(double));
	bernulli(B, N);
	if (fabs(x) < (3.141592653 / 2)) {
		printf("Ýòàëîííîå çíà÷åíèå: %lf \n", tan(x));
		printf("Êîë-âî ñëàãàåìûõ                       Âû÷èñëåííîå çíà÷åíèå                        Ðàçíèöà ìåæäó çíà÷åíèÿìè\n");
		for (int i = 0; i <= N; i++) {
			sum += ((B[2 * i] * pow(-4, i) * (1 - pow(4, i))) / factorial(2 * i)) * pow(x, 2 * i - 1);
			pointer(tan(x), sum, i);
		}
		free(B);
	}
	else free(B);
}
