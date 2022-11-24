#include "Header.h"

void selectSort(struct _finddata_t* data_set, long count) {
	long k;
	struct _finddata_t temp;
	for (long i = 0; i < count; i++) {
		k = i;
		temp = data_set[i];
		for (long j = i + 1; j < count; j++) {
			if (data_set[j].size < temp.size) {
				k = j;
				temp = data_set[j];
			}
		}
		data_set[k] = data_set[i];
		data_set[i] = temp;
	}
}