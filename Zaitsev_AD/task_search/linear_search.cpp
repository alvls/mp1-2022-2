#include <stdlib.h>
#include <stdio.h>
#include "Header.h"
using namespace std;

int linear_search(int* values, int target, int length) {
	for (int i = 0; i < length; i++) {
		if (values[i] == target) return i;
	}
	return -1;
}
