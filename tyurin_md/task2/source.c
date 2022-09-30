#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>

void main() {
	setlocale(LC_ALL, "Russian");
	int robot_number, user_number, attempt, cnt = 1, left = 1, right = 1001;
	int program_mode;
	char op;
	printf("Введите номер программы 1 (число загадывается программой) или 2 (число загадывается пользователем)\n");
	scanf_s("%d", &program_mode);
	switch (program_mode) {
		case 1: 
			srand(time(NULL));
			robot_number = rand() % 1000 + 1;
			printf("Угадайте число, которое загадала программа (от 1 до 1000)\n");
			while (1) {
				scanf_s("%d", &attempt);
				if (robot_number > attempt) {
					printf("Загаданное число больше твоего\n");
				}
				else if (robot_number < attempt) {
					printf("Загаданное число меньше твоего\n");
				}
				else {
					printf("Ты отгадал загаданное число, молодец!\n");
					break;
				}
				cnt ++;
			}
			printf("Ты потратил попыток: %d!\n", cnt);
			break;

		case 2: 
			printf("Загадайте число от 1 до 1000, которое должна отгадать программа\n");
			printf("Если ваше число больше предложенного, то введите знак '>', если ваше число меньше предложенного, то введите знак '<', а если ваше число равно предложенному, то введите знак '='\n");
			printf("Необходимо играть честно!\n");
			scanf_s(" %d", &user_number);
			if ((user_number >= 1) && (user_number <= 1000)) {
				printf("Я думаю, это число 500\n");
				scanf_s(" %c", &op, 1);
				attempt = 500;
				while (op != '=') {
					if (op == '<') {
						right = attempt;
						attempt = (((attempt - left) / 2) + left);
					}
					else if (op == '>') {
						left = attempt;
						attempt = (((right - attempt) / 2) + attempt);
					}
					else {
						printf("Вы ввели неправильную команду,попробуйте ввести знак еще раз!\n");
						cnt--;
					}
					cnt ++;
					printf("Я думаю это число %d\n", attempt);
					scanf_s(" %c", &op, 1);
					
				}
				printf("Программа угадала твое число!\n");
				printf("Программа потратила попыток: %d!\n", cnt);
				break;
			}
			else {
				printf("Вы загадали число не из заданного интервала\n");
				break;
			}


		default:                                                           
			printf("Такого режима не существует, выберите 1 или 2 режим!\n");
			break;
	}
	system("PAUSE");
}