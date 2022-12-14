#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>
//вспомогательные функции
long double factorial(long int n) {
	long double del = 1;
	for (long int c = 1; c <= n; c++) {
		del *= c;
	}
	return del;
}
long double C(int n, int k) {
	long double h = 1;
	for (int i = 0; i < k; i++) {
		h *= (n - i);
	}
	return h/factorial(k);
}
long double  Bernuli(int n) {
	long double A[1000]={0};
	long double s = 1;
	A[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			s= C(i + 1, j + 1) * A[i - j];
			A[i] +=s;

		}
		A[i] *= (-1.) / (i + 1);
	}


	return A[n];
}
//режим 1
void rT_sin_r1( double x,  double pogr, int n) {
	double absol = sin(x);
	long double  rT = 0;
	long double razn = 0;
	long double del;
	long long flag = 1;
	for (int tmp = 0; tmp < n; tmp++) {
		del = factorial(2*tmp+1);
		rT += (pow(-1, tmp) * pow(x, 2 * tmp + 1)) / del;
		if (absol <= rT) {
			razn = rT - absol;
		}
		else {
			razn = absol - rT;
		}
		if (razn < pogr) {
			printf("эталонное значение  - %.11Lf\n", absol);
			printf("вычисленная оценка значения функции - %.11Lf\n", rT);
			printf("разница между оценкой и эталонным значением - %.11Lf\n", razn);
			printf("количество слагаемых, которое было вычислено - %ld\n", tmp+1 );
			flag = 0;
			break;
		}
		
	}
	if (flag){
		printf("эталонное значение - %lf\n", absol);
		printf("вычисленная оценка значения функции - %lf\n", rT);
		printf("разница между оценкой и эталонным значением - %lf\n", razn);
		printf("количество слагаемых, которое было вычислено - %ld\n", n);
	}
}
void rT_cos_r1(double x, double pogr, int n) {
	double absol = cos(x);
	long double  rT = 0;
	long double razn = 0;
	long double del;
	long long flag = 1;
	for (int tmp = 0; tmp < n; tmp++) {
		del = factorial(2 * tmp);
		rT += (pow(-1, tmp) * pow(x, 2 * tmp)) / del;
		if (absol <= rT) {
			razn = rT - absol;
		}
		else {
			razn = absol - rT;
		}
		if (razn < pogr) {
			printf("эталонное значение - %.11Lf\n", absol);
			printf("вычисленная оценка значения функции - %.11Lf\n", rT);
			printf("разница между оценкой и эталонным значением - %.11Lf\n", razn);
			printf("количество слагаемых, которое было вычислено - %i\n", tmp + 1);
			flag = 0;
			break;
		}

	}
	if (flag) {
		printf("эталонное значение - %lf\n", absol);
		printf("вычисленная оценка значения функции - %lf\n", rT);
		printf("разница между оценкой и эталонным значением - %lf\n", razn);
		printf("количество слагаемых, которое было вычислено - %i\n", n);
	}
}
void rT_exp_r1(double x, double pogr, int n) {
	double absol = exp(x);
	long double  rT = 0;
	long double razn = 0;
	long double del;
	long long flag = 1;
	for (int tmp = 0; tmp < n; tmp++) {
		del = factorial(tmp);
		rT += pow(x, tmp) / del;
		if (absol <= rT) {
			razn = rT - absol;
		}
		else {
			razn = absol - rT;
		}
		if (razn < pogr) {
			printf("эталонное значение - %.11Lf\n", absol);
			printf("вычисленная оценка значения функции - %.11Lf\n", rT);
			printf("разница между оценкой и эталонным значением - %.11Lf\n", razn);
			printf("количество слагаемых, которое было вычислено - %i\n", tmp + 1);
			flag = 0;
			break;
		}

	}
	if (flag) {
		printf("эталонное значение - %lf\n", absol);
		printf("вычисленная оценка значения функции - %lf\n", rT);
		printf("разница между оценкой и эталонным значением - %lf\n", razn);
		printf("количество слагаемых, которое было вычислено - %i\n", n);
	}
}
void rT_th_r1(double x, double pogr, int n) {
	double absol = tanh(x);
	long double  rT = 0;
	long double razn = 0;
	long double del;
	long long flag = 1;
	for (int tmp = 1; tmp <= n; tmp++) {
		del = factorial(2*tmp);
		rT += ((Bernuli(2*tmp)*(pow(4,tmp))*(pow(4, tmp)-1))/del)*pow(x,2*tmp-1);
		if (absol <= rT) {
			razn = rT - absol;
		}
		else {
			razn = absol - rT;
		}
		if (razn < pogr) {
			printf("эталонное значение - %.11Lf\n", absol);
			printf("вычисленная оценка значения функции - %.11Lf\n", rT);
			printf("разница между оценкой и эталонным значением - %.11Lf\n", razn);
			printf("количество слагаемых, которое было вычислено - %i\n", tmp + 1);
			flag = 0;
			break;
		}

	}
	if (flag) {
		printf("эталонное значение - %lf\n", absol);
		printf("вычисленная оценка значения функции - %lf\n", rT);
		printf("разница между оценкой и эталонным значением - %lf\n", razn);
		printf("количество слагаемых, которое было вычислено - %i\n", n);
	}
} 
// режим 2
void rT_sin_r2(double x,int nMax) {
	double absol = sin(x);
	long double  rT = 0;
	long double razn = 0;
	long double del;
	long long flag = 1;
	printf("Абсолютная величина = %lf\n", absol);
	printf("Количество Значение   Разница с Абсолютной величиной\n");
	for (int tmp = 0; tmp < nMax; tmp++) {
		del = factorial(2 * tmp + 1);
		rT += (pow(-1, tmp) * pow(x, 2 * tmp + 1)) / del;
		if (absol <= rT) {
			razn = rT - absol;
		}
		else {
			razn = absol - rT;
		}
		printf("%i         |%.11lf   |%.11lf\n", tmp + 1, rT, razn);
	}
}
void rT_cos_r2(double x, int nMax) {
	double absol = cos(x);
	long double  rT = 0;
	long double razn = 0;
	long double del;
	long long flag = 1;
	printf("Абсолютная величина = %lf\n", absol);
	printf("Количество Значение   Разница с Абсолютной величиной\n");
	for (int tmp = 0; tmp < nMax; tmp++) {
		del = factorial(2 * tmp);
		rT += (pow(-1, tmp) * pow(x, 2 * tmp)) / del;
		if (absol <= rT) {
			razn = rT - absol;
		}
		else {
			razn = absol - rT;
		}
		printf("%i         |%.11Lf   |%.11Lf\n", tmp + 1, rT, razn);
	}
}
void rT_exp_r2(double x, int nMax) {
	double absol = exp(x);
	long double  rT = 0;
	long double razn = 0;
	long double del;
	long long flag = 1;
	printf("Абсолютная величина = %lf\n", absol);
	printf("Количество Значение   Разница с Абсолютной величиной\n");
	for (int tmp = 0; tmp < nMax; tmp++) {
		del = factorial(tmp);
		rT += pow(x, tmp) / del;
		if (absol <= rT) {
			razn = rT - absol;
		}
		else {
			razn = absol - rT;
		}
		printf("%i         %.11Lf   %.11Lf\n", tmp + 1, rT, razn);
	}
}
void rT_th_r2(double x, int nMax) {
	double absol = tanh(x);
	long double  rT = 0;
	long double razn = 0;
	long double del;
	long long flag = 1;
	printf("Абсолютная величина = %lf\n", absol);
	printf("Количество Значение   Разница с Абсолютной величиной\n");
	for (int tmp = 1; tmp <= nMax; tmp++) {
		del = factorial(2 * tmp);
		rT += ((Bernuli(2 * tmp) * (pow(4, tmp)) * (pow(4, tmp) - 1)) / del) * pow(x, 2 * tmp - 1);
		if (absol <= rT) {
			razn = rT - absol;
		}
		else {
			razn = absol - rT;
		}
		printf("%i         %.11Lf   %.11Lf\n", tmp + 1, rT, razn);
	}
}
void main() {
	int ans_1, flag = 1, ans_2,Nmax;
	double x;
	double pogr;
	int n;
	setlocale(LC_ALL, "Russian");
	void (*arr1[])(double x, double pogr, int n) = { rT_sin_r1,rT_cos_r1,rT_exp_r1,rT_th_r1 };
	void (*arr2[])(double x,int nMax) = { rT_sin_r2,rT_cos_r2,rT_exp_r2,rT_th_r2 };
	while (1) {
		printf("Режим 1 - Вычисление функции с помощью ряда Тейлора.Расчет оценки значения выбранной функции выполняется либо до достижения заданной точности, либо до исчерпания введенного числа слагаемых.\n");
		printf("Режим 2 - Вычисление функции с помощью ряда Тейлора. Вычисляется таблица из веденного количества строк (NMax) со следующими столбцами: кол-во слагаемых (от 1 до NMax), вычисленную оценку значения функции, разницу между оценкой и эталонным значением.\n");
		printf("Нажмите на цифру с нужным для вас пунктом.\n");
		printf("1 - Выбрать режим 1\n");
		printf("2 - Выбрать режим 2\n");
		printf("3 - Выход\n");
		scanf_s("%i", &ans_1);
		if (ans_1 == 1) {
			printf("Выберите функцию\n");
			printf("1 - sin(x)\n");
			printf("2 - cos(x)\n");
			printf("3 - exp(x)\n");
			printf("4 - th(x)\n");
			scanf_s("%i", &ans_2);
			if (ans_2 == 4) {
				printf("Введите x (|x|<Пи/2), точность вычисления (>= 0,000001),число элементов ряда для выполнения расчета (N - от 1 до 1000)\n");
			}
			else
				printf("Введите x , точность вычисления (>= 0,000001),число элементов ряда для выполнения расчета (N - от 1 до 1000)\n");
			scanf_s("%lf %lf %i", &x,&pogr, &n);
			arr1[ans_2 - 1](x, pogr, n);
		}
		else if (ans_1 == 2) {
			printf("Выберите функцию\n");
			printf("1 - sin(x)\n");
			printf("2 - cos(x)\n");
			printf("3 - exp(x)\n");
			printf("4 - th(x)\n");
			scanf_s("%i", &ans_2);
			if (ans_2 == 4) {
				printf("Введите x (|x|<Пи/2) и количество экспериментов. (от 1 до 25)\n");
			}
			else
				printf("Введите x и количество экспериментов. (от 1 до 25)\n");
			scanf_s("%lf %i", &x,&Nmax);
			arr2[ans_2 - 1](x,Nmax);
		}
		else if (ans_1==3)
			break;
	}	
system("pause");
}
