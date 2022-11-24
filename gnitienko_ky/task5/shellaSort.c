#include "Header.h"

int increment(long inc[], long size) {
  int p1, p2, p3, s;

  p1 = p2 = p3 = 1;
  s = -1;
  do {
    if (++s % 2) {
      inc[s] = 8*p1 - 6*p2 + 1;
    } else {
      inc[s] = 9*p1 - 9*p3 + 1;
      p2 *= 2;
      p3 *= 2;
    }
	p1 *= 2;
  } while(3*inc[s] < size);  

  return s > 0 ? --s : 0;
}

void shellSort(struct _finddata_t* data_set, long size) {
  long inc, i, j, seq[40];
  int s;

  // вычисление последовательности приращений
  s = increment(seq, size);
  while (s >= 0) {
	// сортировка вставками с инкрементами inc[] 
	inc = seq[s--];

    for (i = inc; i < size; i++) {
      struct _finddata_t temp = data_set[i];
      for (j = i-inc; (j >= 0) && (data_set[j].size > temp.size); j -= inc)
        data_set[j+inc] = data_set[j];
      data_set[j+inc] = temp;
    }
  }
}