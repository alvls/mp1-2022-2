#include <stdio.h>

#define size 7


void main() {
	int sum = 0;
	int sum_discount = 0;
	int sum_with_discount = 0;
	int a[4];
	int b, c;
	int cnt = 0;


	int barcode[size][4] = { {1,2,3,4}, {1,2,5,6}, {1,7,5,4}, {2,3,8,4}, {6,9,6,3}, {9,6,8,4}, {1,8,7,3}};
	char* product[size] = { "t-shirt", "jeans", "gloves", "hat", "boots", "sweater", "vest" };
	int price[size] = { 1500, 2500, 900, 1000, 5000, 1700, 2000 };
	int discount[size] = { 5, 35, 10, 20, 25, 15, 30 };
	int count[size] = { 0, 0, 0, 0, 0, 0, 0 };



	do {
	printf("Enter the product barcode (enter 0 to exit):\n");
	scanf_s("%d", &b);
	c = b;
	for (int i = 3; i >= 0; i--) {
		a[i] = b % 10;
		b /= 10;
	}


	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 4; j++) {
			if (a[j] == barcode[i][j]) {
				cnt += 1;
			}
		}
		if (cnt == 4) {
			count[i] ++;
			printf("barcode: %d | name: ", c);
			printf(product[i]);
			printf("  | price: %d rubles | discount: %d %%\n", price[i], discount[i]);
		}
		cnt = 0;
	}
	} while (c != 0);


	for (int i = 0; i < size; i++) {
		sum += price[i] * count[i];
		sum_discount += price[i] * discount[i] / 100 * count[i];
		sum_with_discount += price[i] * (100 - discount[i]) / 100 * count[i];
	}


	system("cls");


	printf("Check -------------------------------------------\n");
	printf("poduct   price        amount  total cost         \n");

	for (int i = 0; i < size; i++) {
		if (count[i] != 0) {
			printf(product[i]);
			printf(" | %d rubles | %d | %d rubles \n", price[i], count[i], count[i] * price[i]);

		}
	}

	printf("-------------------------------------------------\n");
	printf("Sum: %d rubles\n", sum);
	printf("Discount: %d rubles\n", sum_discount);
	printf("To pay : %d rubles\n", sum_with_discount);
	printf("-------------------------------------------------\n");
	printf("Thanks for shopping!\n");


	system("pause");
}
