#include <stdlib.h>
#include <stdio.h>
#include "Header.h"
using namespace std;

int bin_search(int* a, int target, int length) {
	int min = 0;
	int max = length - 1;

	while (min <= max) {
		int mid = (min + max) / 2;
		if (target < a[mid])
		{
			max = mid - 1;
		}
		else if (target > a[mid]) {
			min = mid + 1;
		}
		else return mid;
	}
	return -1;

}
