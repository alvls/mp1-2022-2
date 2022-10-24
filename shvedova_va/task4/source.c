#include <stdio.h>
#include <string.h>
#define arr_size 45
int main()
{
	char* product[arr_size] = { "Кофе латте 400мл.", "Кофе капучино 400мл.", "Кофе американо 100мл.", "Кофе эспрессо 35мл.", "Какао 300мл.","Чай 250мл.",
		"Молоко 2,5% 1л.", "Кефир 3,2% 1л.", "Ряженка 4% 350мл.", "Творог 9% 400г.", "Сметана 20% 180г.", "Сыр Ламбер 50% 150г.",
		"Сыр Маасдам 45% 150г.", "Сыр Российский 50% 150г.", "Сыр Творожный 140г.", "Сыр Плавленный 200г.", "Колбаса Сырокопченная 250г.", "Колбаса Докторская 500г.",
		"Фарш говяжий 1кг.", "Фарш из индейки 1кг.", "Фарш куриный 1кг.", "Минтай свежемороженый 1кг.", "Тунец натуральный 240г.", "Яблоки Антоновка 1кг.",
		"Груши 1 кг.", "Бананы 1кг.", "Виноград Изабелла", "Апельсины 1кг.", "Томаты тепличные 1кг.", "Огурцы 1кг.",
		"Перец красный 1кг.", "Батон нарезной 330г.", "Хлеб Финский заварной 250г.", "Печенье Овсяное 500г.", "Печенье Венское 500г.", "Пирог с вишней",
		"Пирог с капустой", "Ватрушка с творогом", "Шоколад темный с миндалем", "Шоколад темный 55%", "Шоколад молочный", "Шоколад с карамелью",
		"Сок вишневый 1л.", "Сок яблочный 1л.", "Сок виноградный 1л." };
	char* barcode[arr_size] = { "1201", "1202", "1203", "1204", "1205", "1206", "1401", "1402", "1403", "1404", "1405", "1901", "1902", "1903", "1904", "1905",
		"1601", "1602", "2201", "2202", "2203", "1001", "2001", "3301", "3302", "3303", "3304", "3305", "1601", "1602", "1603", "2301", "2302", "1701", "1702",
		"1703", "1704", "1705", "2601", "2602", "2603", "2604", "0301", "0302", "0303" };
	int price_for_one[arr_size] = { 150, 150, 90, 50, 60, 40, 72, 80, 49, 149, 65, 135, 136, 150, 137, 184, 220, 249, 450, 419, 389, 249, 159, 87, 129, 74, 109,
		119, 139, 80, 119, 48, 43, 189, 170, 76, 40, 50, 125, 100, 78, 90, 149, 139, 129 };
	int count_in_check[arr_size]={0}, discount[arr_size]={0};
	int flag, summa = 0, number = 0, count_of_products = 0;
	float price, all_discount, summa_with_discount = 0;
	char barcode_scan[5], add[4];
	system("chcp 1251");
	system("cls");
	//каталог товаров
	printf("КАТАЛОГ ТОВАРОВ В НАЛИЧИИ: \n");
	for (int i = 0; i < arr_size; i++)
		printf("%d) %s - АРТ.: %s \n", i + 1, product[i], barcode[i]);
	//рассчет скидки в зависимости от стоимости за единицу товара
	for (int i = 0; i < arr_size; i++)
	{
		if (price_for_one[i] <= 50)
			discount[i] = 5;
		else
			if ((price_for_one[i] > 50) && (price_for_one[i] <= 80))
				discount[i] = 10;
			else
				if ((price_for_one[i] > 80) && (price_for_one[i] < 100))
					discount[i] = 15;
				else
					if ((price_for_one[i] >= 100) && (price_for_one[i] < 130))
						discount[i] = 20;
					else
						if ((price_for_one[i] >= 130) && (price_for_one[i] < 150))
							discount[i] = 25;
						else
							if ((price_for_one[i] >= 150) && (price_for_one[i] <= 170))
								discount[i] = 30;
							else
								if ((price_for_one[i] > 170) && (price_for_one[i] <= 200))
									discount[i] = 35;
								else
									if ((price_for_one[i] > 200) && (price_for_one[i] < 350))
										discount[i] = 40;
									else
										if ((price_for_one[i] >= 350) && (price_for_one[i] < 450))
											discount[i] = 45;
										else
											discount[i] = 50;
	}
	//сканирование штрих-кода
	while (1)
	{
		printf("\nВведите штрих-код товара из каталога (или введите 0, чтобы сформировать чек): ");
		scanf_s("%s", barcode_scan, (int)sizeof barcode_scan);
		flag = 0;
		if (strcmp("0", barcode_scan) != 0)
		{
			for (int i = 0; i < arr_size; i++)
			{
				if (strcmp(barcode[i], barcode_scan) == 0)
				{
					system("cls");
					printf("%s - %d руб.\nКол-во в чеке на данный момент: %d\nДобавить товар в чек? (да/нет): ", product[i], price_for_one[i], count_in_check[i]);
					scanf_s("%s", add, (int)sizeof add);
					if (strcmp("да", add) == 0)
					{
						count_in_check[i]++;
						count_of_products++;
						summa += price_for_one[i];
						system("cls");
						printf("Товар успешно добавлен\nИтого (без учета скидки): %d руб.", summa);
					}
					flag = 1;
					break;
				}
			}
			if (flag == 0)
				printf("Введен неверный штрих-код\n");
		}
		else
			break;
	}
	system("cls");
	//формирование чека
	if (count_of_products != 0)
	{
		printf("\tКАССОВЫЙ ЧЕК:\n");
		for (int i = 0; i < arr_size; i++)
		{
			if (count_in_check[i] != 0)
			{
				number++;
				price = (price_for_one[i] - (price_for_one[i] * discount[i] / 100)) * count_in_check[i];
				summa_with_discount += price;
				printf("%d) %s\n%dx%d руб.\nс учетом скидки %d процентов: %.2f руб.\n", number, product[i], count_in_check[i], price_for_one[i], discount[i], price);
			}
		}
		all_discount = summa - summa_with_discount;
		printf("\nОбщая сумма скидок: %.2f руб.\n", all_discount);
		printf("ИТОГО: %.2f руб.\n", summa_with_discount);
	}
	else
		printf("В вашем чеке нет товаров...\n");
	system("pause");
	return 0;
}