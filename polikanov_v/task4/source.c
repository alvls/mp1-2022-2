#define _CRT_SECURE_NO_WARNINGS
#include <limits.h> 
#include <locale.h> 
#include <stdio.h> 
#include <math.h> 
#include <stdlib.h> // возможно,некоторые библиотеки лишние. При удалении библиотеки <string.h> ф-я strcmp почему-то работает
#include <string.h> 
#define COUNT_OF_PRODUCTS 7

char* products[COUNT_OF_PRODUCTS] = { "Яйцо куриное С2 \"Лента\" упаковка 10шт ","Яблоки \"С родного дерева \" пакет 500гр", "   Банка пива \" Пей скорей \" 0.33л    ","        Батон \" С пылу с жару\"        ","   Творог \"Однушка в городе\" 300гр    ","Авокадо \"То, что надо\" упаковка 350гр ","     Жвачка \"Love is programming\"     " };
char* codes[COUNT_OF_PRODUCTS] = { "0001","0002","0003","0004","0005","0006","0007"};
int prices[COUNT_OF_PRODUCTS] = { 90,70,65,40,110,150,35 };
int discounts[COUNT_OF_PRODUCTS] = { 0,0,0,0,0,0,0 }; // массив скидок. Заполняется рандомно с помощью time(NULL)
int numberInCheck[COUNT_OF_PRODUCTS] = { 0,0,0,0,0,0,0 }; // кол-во продуктов каждого вида
int finallyCostThisProduct = 0; // цена конкретного продукта с учетом скидки
int allCost = 0; // общая цена без учета скидки
int finallyCostSumm = 0; // общая цена с учетом скидки

int scan() {

	char code[100]; // массив длины 100 прозапас. Если вводится строка длиннее 100 символов, программа вылетает
	unsigned int isIn = 0; // есть ли введенный код в массиве кодов
	unsigned int numberInProducts = 0; // индекс сканированного кода продукта в списке продуктов

	printf("Введите четырёхзначный код товара:\n");
	scanf("%s", code);
	printf("\n");

	if (strcmp(code, "0") == 0) { // возвращаем -1, если ввели 0
		return -1;
	}

	for (int i = 0; i < COUNT_OF_PRODUCTS; i++) { // сравнение введенного кода с достоверными
		if (strcmp(code,codes[i]) == 0) {
			isIn = 1;
			numberInProducts = i;
		}
	}
	if (isIn == 1) {
		printf("| Товар %s | %s | стоимость %d рублей | скидка %d%% | \n\n", codes[numberInProducts], products[numberInProducts], prices[numberInProducts], discounts[numberInProducts]);
		return numberInProducts; // возвращаем позицию введенного штрих-кода(понадобится)

	}
	else {
		printf("Товара с таким кодом нет в наличии\n");
		return -2; // возврат значения -2 в случае не того кода (но отличного от 0!)
	}

}

void main(){
	int scanResult = 0;

	setlocale(LC_ALL, "Rus");

	printf("Время 21:59, завтра отпуск, Вы стоите за кассой, ваша задача - с честью пробить покупку последнему покупателю\nКаждый набор штрих-кода даётся с трудом, пальцы, словно ватные, не слушаются разума, в душе Вы уже не у кассы, а в душе\n\nКоды: 0001 - яйца 0002 - яболоки 0003 - пиво 0004 - хлеб 0005 - творог 0006 - авокадо 0007 - жвачка\nДля завершения сканирования введите 0\n");

	srand(time(NULL)); // время в секундах от 1 января 1970г

	for (int i = 0; i < COUNT_OF_PRODUCTS; i++) { // выставляем скидки рандомно каждой позиции
		discounts[i] = abs(rand() % 10 + 1) * 5;
	}

	printf("\n");

	while (scanResult != -1) { // обработчки введенных кодов
		scanResult = scan();
		if (scanResult != -2 && scanResult != -1) {
			numberInCheck[scanResult]++; // работа с кол-вом товаров в чеке (массив)
		}
	}

	printf("|          Ваш чек:          |\n");
		for (int i = 0; i < COUNT_OF_PRODUCTS; i++) {
			if (numberInCheck[i] != 0) {
				finallyCostThisProduct = round((prices[i] * (100 - discounts[i])) / 100 * numberInCheck[i]) / 1; // цена конкретного продукта с учетом скидки
				finallyCostSumm += finallyCostThisProduct; // сумма к оплате(со скидкой)
				allCost += prices[i] * numberInCheck[i]; // общая стоимость(без скидки)
				printf("| Товар %s | %s | стоимость за единицу %d рублей | количество %d | общая стоимость с учетом скидки = %dр |\n", codes[i], products[i],prices[i], numberInCheck[i], finallyCostThisProduct);
			}
		}
		printf("\nОбщая стоимость товаров: %dр\nСуммарная скидка: %dр\nСумма к оплате: %dp\nЧай? Кофе?\n", allCost,allCost-finallyCostSumm,finallyCostSumm);

	


	system("PAUSE");
}                 