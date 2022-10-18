#include <stdio.h>
#include <locale.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>
void main() {
	int n;
	int flag = 1;
	int number,tmp,us_ans;
	int A[10], i;
	int B[10];
	int cow, bull;
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	printf("Правила игры:\n");
	printf("Игрок выбирает длину загадываемого числа – n (от 2 до 5).\n");
	printf("Компьютер «задумывает» n-значное число с неповторяющимися цифрами\n");
	printf("Игрок делает попытку отгадать число – вводит n-значное число с неповторяющимися цифрами.\n");
	printf("Компьютер сообщает, сколько цифр угадано без совпадения с их позициями в загаданном числе (то есть количество коров) и сколько угадано вплоть до позиции в загаданном числе (то есть количество быков).\n");
	printf("Введите длину числа от 2 до 5");
	scanf_s(" %i", &n);
	if ((n < 2) || (n > 5)) {
		printf("Неверные данные");
	}
	// генерация случайного числа с неповторяющимися цифрами
	else{
		while (flag){
			number = rand() % (int)pow(10, n);
			if ((number / (int)pow(10, n-1)) != 0) {
				tmp = number;
				flag = 0;
				for (i = 0; i < 10; i++) {
					A[i]=0;
				}
				for (i = 0; i < n; i++) {
					A[tmp % 10] += 1;
					tmp /= 10;
				}
				for (i = 0; i < 10; i++) {
					if (A[i] > 1) {
						flag = 1;
					}
				}
			}
		}
	}
	while (1) {
		printf("Введите число");
		scanf_s("%i", &us_ans);
		// проверка на то, чтобы пользователь не ввел число с одинаковыми цыфрами 
		tmp = us_ans;
		flag = 1;
		for (i = 0; i < 10; i++) {
			B[i] = 0;
		}
		for (i = 0; i < n; i++) {
			B[tmp % 10] += 1;
			tmp /= 10;
		}
		for (i = 0; i < 10; i++) {
			if (B[i] > 1) {
				flag = 0;
			}
		}
		//сама игра
		if (flag) {
			if (us_ans == number) {
				printf("Ты угадал \n");
				break;
			}
			tmp = number;
			cow = 0;
			bull = 0;
			for (i = 0; i < n; i++) {
				if ((us_ans % 10) == (tmp % 10)) {
					bull++;
				}
				else if (A[us_ans % 10] == 1) {
					cow++;
				}
				tmp /= 10;
				us_ans /= 10;
			}
			printf("коров = %i\n", cow);
			printf("быков = %i\n", bull);
		}
		else{
			printf("Число содержит повторяющиеся цифры \n");
		}
	}
system("pause");
}