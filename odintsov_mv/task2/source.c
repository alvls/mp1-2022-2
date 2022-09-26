#include <stdio.h>
#include <locale.h>
#include <stdlib.h> 
#include <time.h>
void main() {
	int rezim;
	int r1_chislo;
	int r1_ans=0, r2_ans=500;
	int r1_counter = 0, r2_counter = 0;
	char us_ans;
	int flag = 1;
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	printf("Введите режим 1 или 2 \n");
	scanf_s("%i", &rezim);
	if (rezim == 1) {
		r1_chislo = (rand() % 1000) + 1;
		printf("Я загадал число, попробуй его отгодать \n");
		while (1) {
			printf("Введите число \n");
			scanf_s("%i", &r1_ans);
			r1_counter ++;
			if (r1_ans == r1_chislo) {
				printf("Ты победил. Количество ходов = %i",r1_counter);
				break;
			}
			if (r1_ans > r1_chislo) {
				printf("Загаданное число меньше \n");
			}
			if (r1_ans < r1_chislo) {
				printf("Загаданное число больше \n");
			}
		}
	}
	else {
		printf("Загадай число \n");
		while (flag) {
			printf("121212");
			r2_counter++;
			scanf_s("%c", &us_ans);
			if (us_ans == '=' ) {
				printf("Число угадано. Количесво ходов = %i", r2_counter);
				flag = 0;
			}
			if (us_ans == '<') {
				if ((r2_ans % 2) == 0) {
					r2_ans -=r2_ans / 2;
				}
				else {
					r2_ans -= (r2_ans + 1) / 2;
				}
			}
			if (us_ans == '>') {
				if ((r2_ans % 2) == 0) {
					r2_ans += (1000-r2_ans) / 2;
				}
				else {
					r2_ans += (1001-r2_ans ) / 2;
				}
			}
		}
	}










	system("pause");

}