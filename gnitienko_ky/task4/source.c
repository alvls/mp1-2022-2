#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 9


char product[SIZE][100] = {
	"Áàòîí ïøåíè÷íûé         ",
	"Ïå÷åíüå                 ",
	"×àé                     ",
	"Ìàñëî ïîäñîëíå÷íîå      ",
	"Âîäà ïèòüåâàÿ           ",
	"Ñîëü                    ",
	"Ñàõàğ áåëûé             ",
	"Ñòåéê Black Angus       ",
	"×èïñû êàğòîôåëüíûå Lay's" };

int code[SIZE][4] = {
	{5,8,7,5},
	{1,4,6,1},
	{3,7,6,9},
	{7,5,3,2},
	{9,5,1,3},
	{3,5,7,8},
	{1,5,9,7},
	{1,3,4,6},
	{7,9,8,5}
};

int price[SIZE] = {
	35,
	60,
	80,
	120,
	30,
	10,
	50,
	950,
	120
};

int sale[SIZE] = {
	5,
	20,
	20,
	10,
	15,
	0,
	0,
	25,
	10
};

int purchases[SIZE][4];

int cnt_of_products[SIZE] = { 0 };


short definer(short user) {
	int a;
	a = user % 10;
	return a;
}

double sAle(int* purchase) {
	float price_with_sale;
	int j = 0;
	for (j; j < SIZE; j++) {
		int flag = 1;
		for (int i = 0; i < 4; i++)
			if (code[j][i] != purchase[i])
				flag = 0;
		if (flag) break;
	}
	price_with_sale = (float)(price[j]) * ((float)(100 - sale[j]) / 100);
	return price_with_sale;
}

void add(int* bar, int* purchases) {

}


void main()
{
	setlocale(LC_CTYPE, "Rus");



	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < 4; j++) {
			purchases[i][j] = code[i][j];
		}
	}

	int cnt_of_purchase = -1;

	printf("ÑÒÎÈÌÎÑÒÜ               | ØÒĞÈÕ-ÊÎÄ |    ÖÅÍÀ\n");
	for (int i = 0; i < SIZE; i++) {
		printf("%-25s - ", product[i]);
		for (int j = 0; j < 4; j++)
			printf("%d", code[i][j]);
		printf(" - %8hi", price[i]);
		printf("\n");
	}

	printf("\n\nÑÊÀÍÈĞÓÉÒÅ!\n");
	int purchase[4] = { 0 };
	short user = 0;
	while (1) {
		scanf_s("%hi", &user);
		if (user == 1) break;
		while (user != 0) {
			for (int i = 3; i >= 0; i--) {
				purchase[i] = definer(user);
				user /= 10;
			}
		}
		//for (int i = 0; i < 4; i++)
			//printf("%i", purchase[i]);

		int j = 0;
		for (j; j < SIZE; j++) {
			int count = 0;
			for (int i = 0; i < 4; i++) {
				if (purchase[i] == code[j][i]) {
					count++;
				}
				else
					count = 0;
				if (count == 4) {
					for (j; j < SIZE; j++) {
						printf("%s ", product[j]);
						cnt_of_products[j]++;
						for (int i = 0; i < 4; i++) {
							printf("%i", code[j][i]);
						}
						printf(" ÖÅÍÀ = %.2lf ", sAle(purchase));
						printf(" ÑÊÈÄÊÀ = %d %% \n", sale[j]);
						break;
					}
				}
			}
		}

	}
	printf("\n\n\nÍÀÈÌÅÍÎÂÀÍÈÅ ÒÎÂÀĞÀ        |  ÊÎËÈ×ÅÑÒÂÎ  |  ÑÒÎÈÌÎÑÒÜ  |      ÑÊÈÄÊÀ      |  ÈÒÎÃÎ ÇÀ ÒÎÂÀĞ\n");
	float summary_sale = 0, total = 0;
	for (int i = 0; i < SIZE; i++) {
		if (cnt_of_products[i] != 0) {
			for (int k = 0; k < 25; k++) printf("%c", product[i][k]);
			printf("          %d", cnt_of_products[i]);
			printf("            %d", price[i]);
			printf(" %18.2f", price[i] * (float)(sale[i]) / 100);
			printf("   %15.2f\n", (float)price[i] * (float)cnt_of_products[i] * (float)(100 - sale[i]) / 100);
			total = total + cnt_of_products[i] * price[i];
			summary_sale += cnt_of_products[i] * price[i] * (float)(sale[i]) / 100;
		}
	}
	printf("\nÈÒÎÃÎ ÁÅÇ ÑÊÈÄÊÈ: %.2f\nÑÓÌÌÀĞÍÀß ÑÊÈÄÊÀ: %.2f\n\nÈÒÎÃÎ Ñ Ó×ÅÒÎÌ ÑÊÈÄÊÈ: %.2f\n\n", total, summary_sale, total - summary_sale);
	system("pause");
}