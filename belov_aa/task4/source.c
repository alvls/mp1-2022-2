#include <stdio.h>

#define PRODUCT_COUNT 7

// Строка из 5 символов (4 + нуль-терминатор) будет
// занимать всего 5 байт, в то время, как
// массив даже из short будет занимать 8 байт
const char barcodes[PRODUCT_COUNT][5] = {
	"0001",
	"0002",
	"0026",
	"1111",
	"1234",
	"2428",
	"4591"
};
const char* names[PRODUCT_COUNT] = {
	"Paper",
	"Copybook",
	"Pencil",
	"Pen",
	"Scissors",
	"Eraser",
	"Textbook"
};
const int prices[PRODUCT_COUNT] = {
	45,
	30,
	10,
	90,
	70,
	50,
	80
};
const float discounts[PRODUCT_COUNT] = {
	0.00f,
	0.05f,
	0.15f,
	0.30f,
	0.10f,
	0.40f,
	0.20f
};


int find_product(char* barcode)
{
	for (int i = 0; i < PRODUCT_COUNT; i++)
	{
		if (strcmp(barcodes[i], barcode) == 0)
		{
			return i;
		}
	}
	return -1;
}


void process_customer()
{
	int i, id, is_remove;
	char barcode[6];

	int purchases[PRODUCT_COUNT] = { 0 };

	while (1)
	{
		printf("> Enter BARCODE: ");
		scanf_s("%s", &barcode, sizeof(barcode));
		if (barcode[0] == '*')
		{
			break;
		}
		else if (barcode[0] == '.')
		{
			printf("*** Customer processing cancelled\n");
			return;
		}

		is_remove = barcode[0] == '-';

		// Смещаем указатель на элемент вперед, чтобы исключить
		// минус из сравнения
		id = find_product(is_remove ? barcode + 1 : barcode);
		if (id == -1)
		{
			printf("  -> Product not found\n");
			continue;
		}

		if (purchases[id] == 0 && is_remove)
		{
			printf("  -> This product is not in the cart\n");
			continue;
		}

		purchases[id] += is_remove ? -1 : 1;
		printf("  -> %s '%s'\n\n", is_remove ? "Removed" : "Added", names[id]);

		printf("\n%-25s %-20s\n", "Name", "Amount");
		printf("=========================================================================================\n");
		for (i = 0; i < PRODUCT_COUNT; i++)
		{
			if (purchases[i] == 0) continue;
			printf("%-25s %-15d\n", names[i], purchases[i]);
		}
		printf("=========================================================================================\n\n");
	}

	int amount;
	float discount, sum = 0, total = 0;

	printf("\n%-25s %-20s %-15s %-15s %-15s\n", "Name", "Price", "Amount", "Discount", "Total");
	printf("=========================================================================================\n");
	for (id = 0; id < PRODUCT_COUNT; id++)
	{
		amount = purchases[id];
		if (amount == 0) continue;

		sum = prices[id] * amount;
		discount = sum * discounts[id];
		sum -= discount;

		total += sum;

		printf("%-25s %-20d %-15d %-15.2f %-15.2f\n", names[id], prices[id], amount, discount, sum);
	}
	printf("%-79c%.2f\n", ' ', total);
	printf("=========================================================================================\n\n");

}
void main()
{
	printf("\n");
	printf("                       ***********************************\n");
	printf("                       *                                 *\n");
	printf("                       *             CASHDESK            *\n");
	printf("                       *                                 *\n");
	printf("                       *    Enter '*' to print cheque    *\n");
	printf("                       *    Use '-' to remove from cart  *\n");
	printf("                       *    Enter '.' to cancel          *\n");
	printf("                       ***********************************\n");
	printf("\n");
	printf("\n%-25s %-20s %-15s %-15s\n", "Name", "Barcode", "Price", "Discount (%%)");
	printf("=========================================================================================\n");
	for (int i = 0; i < PRODUCT_COUNT; i++)
	{
		printf("%-25s %-20s %-15d %-15.0f\n",
			names[i], barcodes[i], prices[i], discounts[i] * 100.0f);
	}
	printf("=========================================================================================\n");
	do {
		printf("\n\n");
		process_customer();
		printf("\n\nDo you want to process another customer? [y/N]: ");

	} while (getch() == 'y');
}