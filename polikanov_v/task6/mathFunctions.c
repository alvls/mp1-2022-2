#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <locale.h> 
#include <math.h>

int isDone = 0;

typedef long double (*mathFunc) (long double,long double, int, int, int);

void print_head(long double reference) {
	printf("  Эталонное значение = %lf\n", reference);
	printf("  Кол-во слагаемых      Вычисленная оценка значения функции       Разница оценки и эталона\n");
}

int check_reference(long double ans, long double ref, long double accuracy, int i) {
	if (ans - ref > 0) {
		if (ans - ref <= accuracy) {
			printf("                  %d                               %lf                       %lf\n", i, ans, ref - ans);
			return 1;
		}
	}
	else {
		if (ans - ref >= accuracy) {
			printf("                  %d                               %lf                       %lf\n", i, ans, ref - ans);
			return 1;
		}
	}
	return 0;

}

long double taylorSin(long double x,long double acc, int num_of_row_elem, int mode, int experiments) {
	long double factorial = 1;
	long double answer = 0;
	long double reference = sin(x);
	long double power = 1;


	if (mode == 2) {
		print_head(reference);
		for (int experiment = 1; experiment < experiments + 1; experiment += 1) {
			answer += (pow(-1, experiment + 1) * pow(x,power)) / factorial;
			power += 2;
			factorial = factorial * (power - 1) * power;
			printf("                %d                               %lf                       %lf\n", experiment, answer, reference - answer);

		}
	}
	
	else if (mode == 1) {
		print_head(reference);
		for (int i = 1; i < num_of_row_elem + 1; i++) {
			answer += (pow(-1, i + 1) * pow(x, power)) / factorial;
			power += 2;
			factorial = factorial * (power - 1) * power;
			isDone = check_reference(answer, reference, acc, i);
			if (isDone == 1) {
				break;
			}

		}

		if (isDone == 0) {
			printf("                  %d                               %lf                       %lf\n", num_of_row_elem, answer, reference - answer);
		}
	}


}

long double taylorCos(long double x, long double acc, int num_of_row_elem, int mode, int experiments) {

	long double factorial = 1;
	long double answer = 0;
	long double reference = cos(x);
	long double power = 0;

	if (mode == 2) {
		print_head(reference);
		for (int experiment = 1; experiment < experiments + 1; experiment += 1) {
			answer += (pow(-1, experiment + 1) * pow(x,power)) / factorial;
			power += 2;
			factorial = factorial * (power - 1) * power;
			printf("                %d                               %lf                       %lf\n", experiment, answer, reference - answer);

		}
	}

	else if (mode == 1) {
		print_head(reference);
		for (int i = 1; i < num_of_row_elem + 1; i++) {
			answer += (pow(-1, i + 1) * pow(x, power)) / factorial;
			power += 2;
			factorial = factorial * (power - 1) * power;
			isDone = check_reference(answer, reference, acc, i);
			if (isDone == 1) {
				break;
			}

		}

		if (isDone == 0) {
			printf("                %d                               %lf                       %lf\n", num_of_row_elem, answer, reference - answer);
		}
	}


}

long double taylorExp(long double x, long double acc, int num_of_row_elem, int mode, int experiments) {
	long double factorial = 1;
	long double answer = 0;
	long double reference = exp(x);
	long double power = 0;

	if (mode == 2) {
		print_head(reference);
		for (int experiment = 1; experiment < experiments + 1; experiment += 1) {
			answer += (pow(x, power)) / factorial;
			power += 1;
			factorial = factorial * power;
			printf("                  %d                               %lf                       %lf\n", experiment, answer, reference - answer);

		}
	}

	else if (mode == 1) {
		print_head(reference);
		for (int i = 1; i < num_of_row_elem + 1; i++) {
			answer += (pow(x, power)) / factorial;
			power += 1;
			factorial = factorial * power;
			if (reference - answer <= acc) {
				isDone = 1;
				printf("                  %d                               %lf                       %lf\n", i, answer, reference - answer);
				break;
			}

		}
		if (isDone == 0) {
			printf("                  %d                               %lf                       %lf\n", num_of_row_elem, answer, reference - answer);
		}
	}
}

long double taylorCoth(long double x, long double acc, int num_of_row_elem, int mode, int experiments) {
	long double factorialSinh = 1;
	long double factorialCosh = 1;
	long double answerCosh = 0;
	long double answerSinh = 0;
	long double powerSinh = 1;
	long double powerCosh = 0;
	long double reference = cosh(x) / sinh(x);


	if (mode == 2) {
		print_head(reference);
		for (int experiment = 1; experiment < experiments + 1; experiment += 1) {

			answerCosh += (pow(x, powerCosh)) / factorialCosh;
			powerCosh += 2;
			factorialCosh = factorialCosh * (powerCosh - 1) * powerCosh;

			answerSinh += (pow(x, powerSinh)) / factorialSinh;
			powerSinh += 2;
			factorialSinh = factorialSinh * (powerSinh - 1) * powerSinh;

			printf("                %d                               %lf                       %lf\n", experiment, answerCosh / answerSinh, reference - (answerCosh / answerSinh));


		}
	}
	
	else if (mode == 1) {
		print_head(reference);
		for (int i = 1; i < num_of_row_elem + 1; i++) {

			answerCosh += (pow(x, powerCosh)) / factorialCosh;
			powerCosh += 2;
			factorialCosh = factorialCosh * (powerCosh - 1) * powerCosh;

			answerSinh += (pow(x, powerSinh)) / factorialSinh;
			powerSinh += 2;
			factorialSinh = factorialSinh * (powerSinh - 1) * powerSinh;

			if (reference - answerCosh / answerSinh <= acc) {
				isDone = 1;
				printf("                  %d                               %lf                       %lf\n", i, answerCosh / answerSinh, reference - answerCosh / answerSinh);
				break;
			}


		}
		if (isDone == 0) {
			printf("                  %d                               %lf                       %lf\n", num_of_row_elem, answerCosh / answerSinh, reference - (answerCosh / answerSinh));
		}
	}


}