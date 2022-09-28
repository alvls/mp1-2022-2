#include <stdlib.h>
#include <stdio.h>
#include "Header.h"
using namespace std;

int barier_search(int* values, int target, int length)
{
	values[length - 1] = target;
	int i = 0;
	while (values[i] != target) { i++; }
	return i < length ? i : -1;
}