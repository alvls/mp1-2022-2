#include <stdio.h>
#include <locale.h>
#include <string.h>
void main() {
	char Code[4];
	int Scan_Code;
	int i,ans,tmp;
	int flag;
	char check[10]={0,0,0,0,0,0,0,0,0,0};
	char *Base_name[10] = {"молоко","хлеб","кефир","бананы","пельмени","квас","сосиски","арбуз","соус","масло"};
	int Base_cost[10] = { 50,30,70,90,150,80,200,250,110,120 };
	int Base_code[10] = { 1212,3345,5321,9099,8753,9101,7721,5529,4808,1170 };
	int Base_discount[10] = { 10,20,5,15,50,40,10,50,10,30 };
	int final_cost = 0;
	setlocale(LC_ALL, "Russian");
	// информация о товарах их ценах и штрих кодах находиться в exel таблице "Товары"
	while (1) {
		// Сканирование кода
		printf("Введите скан товара \n");
		for (i = 0; i < 4; i++) {
			scanf_s(" %c", &Code[i]);
		}
		// перевод кода в число
		Scan_Code = (int)(Code[0] - '0') * 1000 + (int)(Code[1] - '0') * 100 + (int)(Code[2] - '0') * 10 + (int)(Code[3] - '0');
		// поиск товара в базе данных
		tmp = -1;
		for (i = 0; i < 10; i++) {
			if (Base_code[i] == Scan_Code) {
				tmp = i;
			}
		}
		if (tmp == -1) {
			printf("Товара с таким штрих кодом нет в наличии\n");
		}
		else {
			//описание товара
			printf("Введите 1, если хотите узнать информацию о товаре, и другое число, если вам это не нужно\n");
			scanf_s("%i", &ans);
			if (ans == 1) {
				printf("Название ");
				puts(Base_name[tmp]);
				printf("Цена = %i\n", Base_cost[tmp]);
				printf("Скидка = %i\n", Base_discount[tmp]);
			}
			//подсчет итоговой стоимости
			final_cost += (int)(Base_cost[tmp]-Base_cost[tmp] * Base_discount[tmp] * 0.01);
			// Добавление товара в чек
			check[tmp]++;
			// Будут ли ещё покупки?
			printf("Если вы хотите закончить нажмите 0, если нет, то введите любое число \n");
			scanf_s("%i", &flag);
			if (flag == 0) {
				break;
			}
		}
	}
	// формирование чека
	for (i = 0; i < 10; i++) {
		if (check[i] != 0) {
			puts(Base_name[i]);
			printf("Цена = %i, количесво = %i, общая стоимость=%i\n",Base_cost[i], check[i], (int)(Base_cost[i] * check[i] - Base_cost[i] * check[i] * Base_discount[i] * 0.01));
		}
	}
	printf("Итого с вас %i рублей\n", final_cost);
	system("pause");
}