#include "Header.h"

void reverse(struct _finddata_t* data_set, int size) {
	struct _finddata_t user;
	for (int i = 0; i < (size / 2); i++) {
		user = data_set[i];
		data_set[i] = data_set[size - i - 1];
		data_set[size - i - 1] = user;
	}
}