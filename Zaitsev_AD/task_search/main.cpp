#include <stdlib.h>
#include <stdio.h>
#include "Header.h"
using namespace std;

int main()
{
	int target = 4;
	int a[] = { 1, 13, 4, 7, 9, 15, 17, 19 };
	int s_a[] = { 1, 4, 7, 9, 13, 15, 17, 19 }; //Отсортированный a для бинарного поиска
	int length = sizeof(a) / sizeof(int);

	printf("      Looking for 4 in array { 1, 13, 4, 7, 9, 15, 17, 19 } and sorted array { 1, 4, 7, 9, 13, 15, 17, 19 } in case \n   of using a binary search algorithm\n\n");

	int t = linear_search(a, target, length);
	printf(">>>   Linear Search: %d", t);
	
	t = bin_search(s_a, target, length);
	printf("\n>>>   Binary_search: %d", t);
	
	t = barier_search(a, target, length);
	printf("\n>>>   Barier_search: %d\n", t);

	printf("\n Note that the binary search function searches for needed values in a different sorted array\n\n");

	system("pause");
	return 0;
}