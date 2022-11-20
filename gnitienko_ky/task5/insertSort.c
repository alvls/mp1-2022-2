# include "Header.h"

void insertSort(struct _finddata_t* data_set, long count) {
	struct _finddata_t temp;
	long i, j;

	for (i = 0; i < count; i++) {
		temp = data_set[i];
		for (j = i - 1; j >= 0 && data_set[j].size > temp.size; j--)
			data_set[j + 1] = data_set[j];
		data_set[j + 1] = temp;
	}
}