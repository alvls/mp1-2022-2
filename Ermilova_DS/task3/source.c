#include <stdio.h>
#include <stdlib.h>


void main() {
	srand(time(0));
	int n, bulls, cows, x, b;
	printf("Enter n - number length (2..5):\n");
	scanf_s("%d", &n);
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	int number[5];
	int guess[5];

	x = 0 + rand() % 9;
	number[0] = a[x];
	printf("%d", number[0]);
	a[x] = 999;
	for (int i = 1; i < n; i++) {
		x = 0 + rand() % 10;
		if (a[x] != 999) {
			number[i] = a[x];
			a[x] = 999;
		}
		else {
			while (a[x] == 999) {
				x = 0 + rand() % 10;
			}
			number[i] = a[x];
			a[x] = 999;
		}
		printf("%d", number[i]);
	}
	
	
	

	do {
		bulls = cows = 0;
		printf("Guess the number long n (If you want to end the game write 0)\n");
		scanf_s("%d", &b);
		if (b == 0) {
			printf("The game is over\n");
			break;
		}
		for (int i = n - 1; i >= 0; i--) {
			x = b % 10;
			guess[i] = x;
			b = b / 10;
		}


		for (int i = 0; i < n; i++) {
			if (number[i] == guess[i]) {
				bulls++;
			}
			for (int j = 0; j < n; j++) {
				if (number[i] == guess[j]) {
					cows++;
				}
			}
		}
		cows = cows - bulls;
		printf("Number of bulls: %d\n", bulls);
		printf("Number of cows: %d\n", cows);
		if (bulls == n) {
			printf("You won!\n");
		}
	} while ( bulls!= n);

	system("pause");
} 

