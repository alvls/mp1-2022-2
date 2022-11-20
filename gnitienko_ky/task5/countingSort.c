#include <math.h>
#include <stdlib.h>
#include "Header.h"

void countingSort(struct _finddata_t* data_set, long count) {
		long max_size = 0;
		for (int i = 0; i < count; i++)
			if (data_set[i].size > max_size)
				max_size = data_set[i].size;
		if (max_size > pow(10, 9))
			return 0;
		long* buff = (long*)malloc((max_size + 1) * sizeof(long));
		if (buff == NULL)
			return 0;
		for (int i = 0; i < max_size; i++) buff[i] = 0;
		for (int i = 0; i < count; i++)
			buff[data_set[i].size]++;
		for (int i = max_size - 1; i > 0; i--)
			buff[i] = buff[i - 1];
		struct _finddata_t* answer_buf = (struct _finddata_t*)malloc((int)count * sizeof(struct _finddata_t)); 
		if (answer_buf == NULL)
			return 0;
		for (int i = 0; i < count; i++) {
			answer_buf[buff[data_set[i].size] - 1] = data_set[i];
			buff[data_set[i].size]++;
		}
		for (int i = 0; i < count; i++)
			data_set[i] = answer_buf[i];
		free(buff);
		free(answer_buf);
		return 1;
	}