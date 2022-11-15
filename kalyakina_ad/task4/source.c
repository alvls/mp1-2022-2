#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#pragma warning(disable : 4996)

struct product
{
	char* code;
	char name[450];
	int price;
	int count;
	int discount;
};

char n_[10000][100];
void main()
{
	char t_[450], x_[450];
	int n, i, j, l = 10000;
	char answer[7], answer2[5];
	double s_now, s, k;
	char* h;
	struct product* vendor_code;
	setlocale(LC_ALL, "Rus");
	FILE* list = fopen("list.txt", "r");
	printf("Добрый день. Добро пожаловать в магазин современной художественной литературы!\n\n");
	printf("Какой метод обработки файла вы хотите использовать? (Метод 1 предназначен для обработки файла с большим количеством товаров, а метод 2 эффективен для небольшого количества товаров (до 1000)) ");
	scanf("%d", &j);
	if (j == 1)
	{
		vendor_code = (struct product*)malloc(sizeof(struct product) * 10000);
		if (list == NULL)
		{
			printf("Невозможно открыть файл\n");
		}
		else
		{
			j = 0;
			while (fgets(&n_[j], 100, list) != NULL)
			{
				i = atoi(n_[j]);
				vendor_code[i].code = n_[j];
				vendor_code[i].code[strlen(vendor_code[i].code) - 1] = ' ';
				fgets(&vendor_code[i].name, 450, list);
				vendor_code[i].name[strlen(vendor_code[i].name) - 1] = ' ';
				fgets(&t_, 450, list);
				vendor_code[i].price = atoi(t_);
				fgets(&x_, 450, list);
				vendor_code[i].discount = atoi(x_);
				vendor_code[i].count = 0;
				printf("%s %s\n", vendor_code[i].code, vendor_code[i].name);
				j++;
			}
		}
		printf("\nУбедительная просьба: вводите ответы в соответствии с регистром. Спасибо за понимание\n");
		i = 0;
		printf("\nХотите ли вы что-нибудь купить?(Если да, введите 'Yes', если нет, то - 'No') ");
		fgets(&answer2, 5, stdin);
		fgets(&answer2, 5, stdin);
		while (answer2[0] != 'N')
		{
			printf("Введите артикул желаемого товара: ");
			fgets(&answer, 7, stdin);
			if (strlen(answer) == 5)
			{
				i = atoi(answer);
				if ((i < 10000) && (vendor_code[i].price > 0))
				{
					printf("%s\nЦена товара: %d р\nДополнительная скидка на товар: %d%%\nХотите ли вы купить данный товар? (Да - 'Yes', нет - 'No')  ", vendor_code[i].name, vendor_code[i].price, vendor_code[i].discount);
					fgets(&answer2, 6, stdin);

					if (answer2[0] == 'Y')
					{
						printf("Какое количество товара вы хотите взять? ");
						scanf("%d", &n);
						vendor_code[i].count += n;
					}
					printf("\nХотите ли вы купить что-нибудь ещё? (Да - 'Yes', нет - 'No') ");
					fgets(&answer2, 6, stdin);
					if ((answer2[0] != 'Y') && (answer2[0] != 'N'))
						fgets(&answer2, 6, stdin);
				}
				else printf("\nНи один товар не соответствует данному артикулу. Пожалуйста, проверьте правильность введенного артикула и введите его снова\n");
			}
			else printf("\nАртикул введен неверно. Пожалуйста, проверьте количество введенных цифр\n");
		}
		printf("\n");
		s = 0;
		for (i = 0; i < l; i++)
			if (vendor_code[i].count > 0)
			{
				k = 1 - ((double)(vendor_code[i].discount) / 100);
				s_now = (double)vendor_code[i].price * vendor_code[i].count * (1 - ((double)(vendor_code[i].discount) / 100));
				s += s_now;
				printf("%s  %s  %*d  %d  %.2lf\n", vendor_code[i].code, vendor_code[i].name, 145 - strlen(vendor_code[i].name), vendor_code[i].price, vendor_code[i].count, s_now);
			}
	}
	else if (j == 2)
	{
		vendor_code = (struct product*)malloc(sizeof(struct product) * 1000);
		if (list == NULL)
		{
			printf("Невозможно открыть файл\n");
		}
		else
		{
			j = 0;
			i = 0;
			while (fgets(&n_[j], 100, list) != NULL)
			{
				vendor_code[i].code = n_[j];
				vendor_code[i].code[strlen(vendor_code[i].code) - 1] = ' ';
				fgets(&vendor_code[i].name, 450, list);
				vendor_code[i].name[strlen(vendor_code[i].name) - 1] = ' ';
				fgets(&t_, 450, list);
				vendor_code[i].price = atoi(t_);
				fgets(&x_, 450, list);
				vendor_code[i].discount = atoi(x_);
				vendor_code[i].count = 0;
				printf("%s %s\n", vendor_code[i].code, vendor_code[i].name);
				j++;
				i++;
			}
		}
		printf("\nУбедительная просьба: вводите ответы в соответствии с регистром. Спасибо за понимание\n");
		l = i;
		i = 0;
		printf("\nХотите ли вы что-нибудь купить?(Если да, введите 'Yes', если нет, то - 'No') ");
		fgets(&answer2, 5, stdin);
		fgets(&answer2, 5, stdin);
		while (answer2[0] != 'N')
		{
			printf("Введите артикул желаемого товара: ");
			fgets(&answer, 7, stdin);
			if (strlen(answer) == 5)
			{
				j = -1;
				for (i = 0; i < l; i++)
				{
					if (atoi(vendor_code[i].code) == atoi(answer))
						j = i;
					if (j >= 0)
						break;
				}
				if (j >= 0)
				{
					printf("%s\nЦена товара: %d р\nДополнительная скидка на товар: %d%%\nХотите ли вы купить данный товар? (Да - 'Yes', нет - 'No')  ", vendor_code[j].name, vendor_code[j].price, vendor_code[j].discount);
					fgets(&answer2, 6, stdin);
					if (answer2[0] == 'Y')
					{
						printf("Какое количество товара вы хотите взять? ");
						scanf("%d", &n);
						vendor_code[j].count += n;
					}
					printf("\nХотите ли вы купить что-нибудь ещё? (Да - 'Yes', нет - 'No') ");
					fgets(&answer2, 6, stdin);
					if ((answer2[0] != 'Y') && (answer2[0] != 'N'))
						fgets(&answer2, 6, stdin);
				}
				else printf("\nНи один товар не соответствует данному артикулу. Пожалуйста, проверьте правильность введенного артикула и введите его снова\n");
			}
			else printf("\nАртикул введен неверно. Пожалуйста, проверьте количество введенных цифр\n");
		}
		printf("\n");
		s = 0;
		for (i = 0; i < l; i++)
			if (vendor_code[i].count > 0)
			{
				k = 1 - ((double)(vendor_code[i].discount) / 100);
				s_now = (double)vendor_code[i].price * vendor_code[i].count * (1 - ((double)(vendor_code[i].discount) / 100));
				s += s_now;
				printf("%s  %s  %*d  %d  %.2lf\n", vendor_code[i].code, vendor_code[i].name, 145 - strlen(vendor_code[i].name), vendor_code[i].price, vendor_code[i].count, s_now);
			}
	}
	else
	{
		printf("Вы не указали метод или указали его неверно\n");
		system("pause");
		return;
	}
	if (s > 0)
	{
		printf("\nИтого к оплате: %.2lf р\nСпасибо за покупку\n", s);

	}
	printf("До свидания! Приходите снова\n");
	fclose(list);
	system("pause");
}