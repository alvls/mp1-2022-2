#include <stdio.h>
#include <locale.h>
#include <stdlib.h> 
#include <time.h>
#include <io.h> 
#include <malloc.h>
#include <omp.h>
// ���������� ���������
void Buble_Sort (int a[], int size) {
	int tmp,j;
	for (int i = 0; i < size-1; i++) {
		for (j = size - 1; j > i; j--) {
			if (a[j - 1] > a[j]) {
				tmp = a[j];
				a[j] = a[j-1];
				a[j-1] = tmp;
			}
		}
	}
}
// ���������� �������
void SelectSort(int a[], int size) {
	int i, j, k;
	int x;
	for (i = 0; i < size; i++) {
		k = i; x = a[i];
		for (j = i + 1; j < size; j++) {
			if (a[j] < x) {
				k = j; x = a[j];
			}
		}
		a[k] = a[i]; a[i] = x;
	}
}
// ��������� ���������
void InsertSort(int a[], int size) {
	int x;
	int i, j;
	for (i = 0; i < size; i++) {  
		x = a[i];
		for (j = i - 1; j >= 0 && a[j] > x; j--)
			a[j + 1] = a[j];
		a[j + 1] = x;
	}
}
// ���������� ��������
void merge_sort(int i, int j, int a[], int aux[]) {
	if (j <= i) {
		return;  
	}
	int mid = (i + j) / 2;
	merge_sort(i, mid, a, aux);     
	merge_sort(mid + 1, j, a, aux);     
	int pointer_left = i;     
	int pointer_right = mid + 1;        
	int k;     
	for (k = i; k <= j; k++) {
		if (pointer_left == mid + 1) {   
			aux[k] = a[pointer_right];
			pointer_right++;
		}
		else if (pointer_right == j + 1) {  
			aux[k] = a[pointer_left];
			pointer_left++;
		}
		else if (a[pointer_left] < a[pointer_right]) { 
			aux[k] = a[pointer_left];
			pointer_left++;
		}
		else { 
			aux[k] = a[pointer_right];
			pointer_right++;
		}
	}
	for (k = i; k <= j; k++) { 
		a[k] = aux[k];
	}
}
// ���������� �����
void quicksort(int number[25], int first, int last) {
	int i, j, pivot, temp;
	if (first < last) {
		pivot = first;
		i = first;
		j = last;
		while (i < j) {
			while (number[i] <= number[pivot] && i < last)
				i++;
			while (number[j] > number[pivot])
				j--;
			if (i < j) {
				temp = number[i];
				number[i] = number[j];
				number[j] = temp;
			}

		}
		temp = number[pivot];
		number[pivot] = number[j];
		number[j] = temp;
		quicksort(number, first, j - 1);
		quicksort(number, j + 1, last);
	}

}
// ���������� �����
void ShellSort(int n, int mass[])
{
	int i, j, step;
	int tmp;
	for (step = n / 2; step > 0; step /= 2)
		for (i = step; i < n; i++)
		{
			tmp = mass[i];
			for (j = i; j >= step; j -= step)
			{
				if (tmp < mass[j - step])
					mass[j] = mass[j - step];
				else
					break;
			}
			mass[j] = tmp;
		}
}
// ���������� ���������
void countingSort(int* array, int n, int k) {
	int* c = (int*)malloc((k + 1) * sizeof(*array));
	memset(c, 0, sizeof(*array) * (k + 1));
	for (int i = 0; i < n; ++i) {
		++c[array[i]];
	}
	int b = 0;
	for (int i = 0; i < k + 1; ++i) {
		for (int j = 0; j < c[i]; ++j) {
			array[b++] = i;
		}
	}
	free(c);
}
// ����� ������� �� �����
void pr(int a[], int size, char path[]) {
	struct _finddata_t c_file;
	intptr_t hFile;
	if ((hFile = _findfirst(path, &c_file)) == -1L)
		printf("No files in current directory!\n");
	else
	{
		do {
			if (a[0] == c_file.size)
				printf("%-12.12s - %10ld ����\n", c_file.name, c_file.size);
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile);
		for (int i = 1; i < size; i++) {
			if (a[i] != a[i - 1]){
				if ((hFile = _findfirst(path, &c_file)) == -1L)
					printf("No files in current directory!\n");
				else
				{
					do {
						if (a[i] == c_file.size) {
							printf("%-12.12s - %10ld ����\n", c_file.name, c_file.size);
						}
					} while (_findnext(hFile, &c_file) == 0);
					_findclose(hFile);
				}
			}
		}
	}
}
// ��������������� �������
void reverse_a(int a[], int size) {
	int tmp;
	for (int i = 0; i <(size/2); i++) {
		tmp = a[i];
		a[i] = a[size - i - 1];
		a[size - i - 1] = tmp;
	}
}
void main() {
	//�������������
	int i,ans,maxim=-1,size=0;
	double t1, t2;
	char path[200];
	int tmp=0;
	int* a;
	int flag = 1;
	int* b;
	int ans_1 = 0;
	setlocale(LC_ALL, "Russian");
	struct _finddata_t c_file;
	intptr_t hFile;
	printf("������� ����� �����\n");
	printf("��������: d:\\test\\*.* \n");
	gets(path);
	// ���������� ������� ������� �
	if ((hFile = _findfirst(path, &c_file)) == -1L)
		printf("No files in current directory!\n");
	else
	{
		do {
			size += 1;
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile);
	}
	size = size - 2;
	a = (int*)malloc(size * sizeof(struct _finddata_t));
	// ���� � ����������
	while(flag){
		// ���������� ������� �
		tmp = 0;
		if ((hFile = _findfirst(path, &c_file)) != -1L) {
			tmp = 0;
			do {
				tmp += 1;
				if (tmp > 2) {
					a[tmp - 3] = c_file.size;		
				}
			} while (_findnext(hFile, &c_file) == 0);
			_findclose(hFile);
		}
		printf("������� ����� ������� ��� ��������\n");
		printf("1 - ���������� ��������� \n");
		printf("2 - ���������� ������� \n");
		printf("3 - ��������� ��������� \n");
		printf("4 - ���������� �������� \n");
		printf("5 - ���������� ����� \n");
		printf("6 - ���������� ����� \n");
		printf("7 - ���������� ��������� \n");
		printf("8 - ����� \n");
		scanf_s("%i", &ans);
		printf("1-���������� �� �����������.\n");
		printf("2-���������� �� ��������.\n");
		scanf_s("%i", &ans_1);
		switch (ans){
		case 1:
			t1 = omp_get_wtime();
			Buble_Sort(a,size, path);
			t2 = omp_get_wtime();
			if (ans_1 == 1) {
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
			if (ans_1 == 2) {
				reverse_a(a, size);
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
			break;
		case 2:
			t1 = omp_get_wtime();
			SelectSort(a, size, path);
			t2 = omp_get_wtime();
			if (ans_1 == 1) {
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
			if (ans_1 == 2) {
				reverse_a(a, size);
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
			break;
		case 3:
			t1 = omp_get_wtime();
			InsertSort(a, size, path);
			t2 = omp_get_wtime();
			if (ans_1 == 1) {
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
			if (ans_1 == 2) {
				reverse_a(a, size);
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
	
			break;
		case 4:
			t1 = omp_get_wtime();
			b = (int*)malloc(size * sizeof(struct _finddata_t));
			merge_sort(0, size - 1, a, b);
			t2 = omp_get_wtime();
			if (ans_1 == 1) {
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
			if (ans_1 == 2) {
				reverse_a(a, size);
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
			break;
		case 5:
			t1 = omp_get_wtime();
			quicksort(a, 0, size - 1);
			t2 = omp_get_wtime();
			if (ans_1 == 1) {
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
			if (ans_1 == 2) {
				reverse_a(a, size);
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
			
			break;
		case 6:
			t1 = omp_get_wtime();
			ShellSort(size, a);
			t2 = omp_get_wtime();
			if (ans_1 == 1) {
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
			if (ans_1 == 2) {
				reverse_a(a, size);
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
			break;
		case 7:
			t1 = omp_get_wtime();
			for (int i = 0; i < size; i++) {
				if (a[i] > maxim)
					maxim = a[i];
			}
			countingSort(a, size, maxim);
			t2 = omp_get_wtime();
			if (ans_1 == 1) {
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
			if (ans_1 == 2) {
				reverse_a(a, size);
				pr(a, size, path);
				printf("time - %lf\n", t2 - t1);
			}
			break;
		case 8:
			flag = 0;
			break;
		}

	}
	
	system("pause");
}