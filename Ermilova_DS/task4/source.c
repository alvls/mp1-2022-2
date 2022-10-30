#include <stdio.h>

#define size 7


void main() {
	int sum = 0;
	int sum_discount = 0;
	int sum_with_discount = 0;
	int a;


	int barcode[size] = { 1234, 1256, 1754, 2384, 6963, 9684, 1873 };
	char* product[size] = { "t-shirt", "jeans", "gloves", "hat", "boots", "sweater", "vest" };
	int price[size] = { 1500, 2500, 900, 1000, 5000, 1700, 2000 };
	int discount[size] = { 5, 35, 10, 20, 25, 15, 30 };
	int count[size] = { 0, 0, 0, 0, 0, 0, 0 };


	do {
		printf("Enter the product barcode (enter 0 to exit):\n");
		scanf_s("%d", &a);
		for (int i = 0; i < size; i++) {
			if (barcode[i] == a)
			{	
				count[i] ++;
				printf("barcode: %d | name: ", barcode[i]);
				printf(product[i]);
				printf("  | price: %d rubles | discount: %d %%\n", price[i], discount[i]);

			}
		}
	} while (a != 0);


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
