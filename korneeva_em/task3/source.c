#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
void main()
{
	setlocale(LC_ALL, "Russian");
	int len,n,num=0,cnt=0;
	printf("¬ведите длину загадываемого числа:");
	scanf_s("%d", &len);
	srand(time(NULL));
	printf("%d", num);
	getch();
}