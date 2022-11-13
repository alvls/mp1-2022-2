#define _CRT_SECURE_NO_WARNINGS
#define PATH_LENGTH 200
#define NAME_LENGTH 50
#define STR_NUM 100


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <time.h>
#include <stdbool.h>


typedef struct 
{
    char name[NAME_LENGTH];
    int size;
}myStruct;


void bubble(myStruct * A, int N)
{
    bool flag = false;
    char tmp[NAME_LENGTH];
    int t;

    while (flag == false)
    {
        flag = true;
        for (int i = 0; i < N - 1; i++)
        {
            if (A[i + 1].size < A[i].size)
            {
                strcpy(tmp, A[i].name);
                strcpy(A[i].name, A[i + 1].name);
                strcpy(A[i + 1].name, tmp);
                t = A[i].size;
                A[i].size = A[i + 1].size;
                A[i + 1].size = t;
                flag = false;
            }
        }
    }
}


void select(myStruct* A, int N)
{
    char tmp[NAME_LENGTH];
    int t;
    int beg = 0;
    int min_ind = 0;

    while (beg < N)
    {
        min_ind = beg;
        for (int i = beg; i < N; i++)
        {
            if (A[i].size < A[min_ind].size)
            {
                min_ind = i;
            }
        }
        strcpy(tmp, A[min_ind].name);
        strcpy(A[min_ind].name, A[beg].name);
        strcpy(A[beg].name, tmp);
        t = A[min_ind].size;
        A[min_ind].size = A[beg].size;
        A[beg].size = t;
        beg++;
    }
}


void insert(myStruct* A, int N)
{
    myStruct x;
    long i, j;

    for (i = 0; i < N; i++)
    {
        strcpy(x.name, A[i].name);
        x.size = A[i].size;

        for (j = i - 1; j >= 0 && A[j].size > x.size; j--)
        {
            strcpy(A[j + 1].name, A[j].name);
            A[j + 1].size = A[j].size;
        }

        strcpy(A[j + 1].name, x.name);
        A[j + 1].size = x.size;
    }
}


void merge_sort(int i, int j, myStruct a[], myStruct aux[])
{
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
            aux[k].size = a[pointer_right].size;
            strcpy(aux[k].name, a[pointer_right].name);
            pointer_right++;
        }
        else if (pointer_right == j + 1) {       
            aux[k].size = a[pointer_left].size;
            strcpy(aux[k].name, a[pointer_left].name);
            pointer_left++;
        }
        else if (a[pointer_left].size < a[pointer_right].size) {       
            aux[k].size = a[pointer_left].size;
            strcpy(aux[k].name, a[pointer_left].name);
            pointer_left++;
        }
        else {    
            aux[k].size = a[pointer_right].size;
            strcpy(aux[k].name, a[pointer_right].name);
            pointer_right++;
        }
    }

    for (k = i; k <= j; k++) {   
        a[k].size = aux[k].size;
        strcpy(a[k].name, aux[k].name);
    }
}


void quickSort(myStruct* numbers, int left, int right)
{
    myStruct pivot;
    int l_hold = left;
    int r_hold = right; 
    pivot.size = numbers[left].size;
    strcpy(pivot.name, numbers[left].name);
    while (left < right)
    {
        while ((numbers[right].size >= pivot.size) && (left < right))
            right--; 
        if (left != right)
        {
            numbers[left].size = numbers[right].size; 
            strcpy(numbers[left].name, numbers[right].name); 
            left++;
        }
        while ((numbers[left].size <= pivot.size) && (left < right))
            left++; 
        if (left != right) 
        {
            numbers[right].size = numbers[left].size; 
            strcpy(numbers[right].name, numbers[left].name); 
            right--; 
        }
    }
    numbers[left].size = pivot.size; 
    strcpy(numbers[left].name, pivot.name); 
    pivot.size = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot.size) 
        quickSort(numbers, left, pivot.size - 1);
    if (right > pivot.size)
        quickSort(numbers, pivot.size + 1, right);
}


void shell_sort(myStruct* array, int size)
{
    for (int s = size / 2; s > 0; s /= 2)
    {
        for (int i = s; i < size; ++i)
        {
            for (int j = i - s; j >= 0 && array[j].size > array[j + s].size; j -= s)
            {
                myStruct temp;
                temp.size = array[j].size;
                strcpy(temp.name, array[j].name);
                array[j].size = array[j + s].size;
                strcpy(array[j].name, array[j + s].name);
                array[j + s].size = temp.size;
                strcpy(array[j + s].name, temp.name);
            }
        }
    }
}


void countingSort(myStruct* array, int n, int k) {
    myStruct* c = (myStruct*)malloc((k + 1) * sizeof(*array));
    memset(c, 0, sizeof(*array) * (k + 1));

    for (int i = 0; i < n; ++i) {
        ++c[array[i].size].size;
        strcpy(c[array[i].size].name, array[i].name);

    }

    int b = 0;
    for (int i = 0; i < k + 1; ++i) {
        for (int j = 0; j < c[i].size; ++j) {
            array[b++].size = i;
            strcpy(array[b - 1].name, c[i].name);
        }
    }

    free(c);
}


int main()
{
    struct _finddata_t c_file;
    intptr_t hFile;
    char path[NAME_LENGTH];
    myStruct arr[STR_NUM];
    myStruct buf[STR_NUM];
    myStruct arr_copy[STR_NUM];
    int count = 0;
    int choice;
    int maxSize = 0;
    printf("Enter the path to the directory:\n");
    scanf("%s", &path);
    if ((hFile = _findfirst(path, &c_file)) == -1L)
    {
        printf("Error");
    }
    else
    {
        do
        {
            if ((strcmp(c_file.name, ".") != 0) && (strcmp(c_file.name, "..") != 0))
            {
                strcpy(arr[count].name, c_file.name);
                arr[count].size = c_file.size;
                if (c_file.size > maxSize)
                    maxSize = c_file.size;
                count++;
            }
        } while (_findnext(hFile, &c_file) == 0);
    }
    for (int i = 0; i < count; i++)
    {
        printf("%s  %d \n", arr[i].name, arr[i].size);
        arr_copy[i].size = arr[i].size;
        strcpy(arr_copy[i].name, arr[i].name);
    }

    printf("press 1 for bubble sort \n");
    printf("press 2 for select sort \n");
    printf("press 3 for insert sort \n");
    printf("press 4 for merge sort \n");
    printf("press 5 for quick sort \n");
    printf("press 6 for shella sort \n");
    printf("press 7 for count sort \n");
    printf("press 0 for exit \n");
    scanf("%d", &choice);

    while (choice != 0)
    {
        for (int i = 0; i < count; i++)
        {
            arr[i].size = arr_copy[i].size;
            strcpy(arr[i].name, arr_copy[i].name);
        }
        time_t t0 = time(0);


        switch (choice)
        {
        case 1:
            bubble(arr, count);
            break;
        case 2:
            select(arr, count);
            break;
        case 3:
            insert(arr, count);
            break;
        case 4:
            merge_sort(0, count - 1, arr, buf);
            break;
        case 5:
            quickSort(arr, 0, count - 1);
            break;
        case 6:
            shell_sort(arr, count);
            break;
        case 7:
            countingSort(arr, count, maxSize);
            break;
        default:
            break;
        }

        time_t t1 = time(0);
        double time_in_seconds = difftime(t1, t0);
        printf("Sort time %f \n", time_in_seconds);


        for (int i = 0; i < count; i++)
        {
            printf("%s  %d \n", arr[i].name, arr[i].size);
        }
        scanf("%d", &choice);
    }

}