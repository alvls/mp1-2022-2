#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <stdlib.h>  
#include <io.h>  
#include <time.h>  
#include <locale.h>
#include <Windows.h>
#include <conio.h>
#include "Header.h"
#include "omp.h"

void print(struct _finddata_t* data_set, int count) {
    system("cls");
    for (int i = 0; i < count; i++)
        printf("%-5.15s %20lld \n", data_set[i].name, data_set[i].size);

}

struct _finddata_t* buf;

int main(void)
{
    system("title File manager");
    CONSOLE_CURSOR_INFO structCursorInfo;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
    SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND);
    system("cls");

    setlocale(LC_CTYPE, "Rus");
    struct _finddata_t c_file;
    intptr_t hFile;

    char path[200];
    int size = 0;
    long count = 0;
    //buf = malloc(1000000 * sizeof(struct _finddata_t));

    // Find first file in directory 
    printf("Введите расположение файла\n");
    gets_s(path, 150, stdin);
    strcat(path, "\\*.*");

    count = find_count(path);

    data_set = calloc(count, sizeof(struct _finddata_t));

    if ((hFile = _findfirst(("%s", path), &c_file)) == -1L)
        printf("No files in current directory!\n");
    else {
        do
        {
            if (c_file.size > 0)
                size++;
        } while (_findnext(hFile, &c_file) == 0);
    }

    if ((hFile = _findfirst(("%s", path), &c_file)) == -1L)
        printf("No files in current directory!\n");
    else
    {
        printf("Listing of files\n\n");
        printf("FILE              DATE %24c    SIZE\n", ' ');
        printf("----              ---- %24c    ----\n", ' ');
        do {
            char buffer[30];
            ctime_s(buffer, _countof(buffer), &c_file.time_write);
            if (count < size && c_file.size > 0) {
                printf("%-12.15s | %.24s | %10ld\n", c_file.name, buffer, c_file.size);
                for (int i = count; i <= count; i++) {
                    buf[i] = c_file;
                }
                //printf("%-12.15s | %.24s | %10ld\n", user.name, user.data, user.size);
            }
            if (c_file.size == 0) count--;
        } while (_findnext(hFile, &c_file) == 0);
        _findclose(hFile);
        printf("\ncount of files: %d\n", count);
        system("pause");
        char* menu2[7] = { (char*)"1. Сортировка пузырьком", (char*)"2. Сортировка выбором" , (char*)"3. Сортировка вставками", (char*)"4. Сортировка слиянием", (char*)"5. Сортировка Хоара", (char*)"6. Сортировка Шелла", (char*)"7. Сортировка подсчетом" };
        char* menu1[2] = { (char*)"1. Сортировка по возрастанию", (char*)"2. Сортировка по убыванию" };
        int answer;
        while (1) {
            for (int i = 0; i < count; i++)
                data_set[i] = buf[i];
            answer = menu(menu1, 2);
            double T = 0;
            if (answer == 27) {
                system("cls");  break;
            }
            system("cls");
            switch (answer) {
            case 0: {
                int answer2 = menu(menu2, 7);
                switch (answer2) {
                case 0: {
                    double t = omp_get_wtime();
                    bubbleSort(data_set, count);
                    double t1 = omp_get_wtime();
                    T = t1 - t;
                    print(data_set, count);
                    printf("Time of sorting - %.15lf sec\n", T);
                    system("pause");
                    break;
                }
                case 1: {
                    double t = omp_get_wtime();
                    selectSort(data_set, count);
                    double t1 = omp_get_wtime();
                    T = t1 - t;
                    print(data_set, count);
                    printf("Time of sorting - %.15lf sec\n", T);
                    system("pause");
                    break;
                }
                case 2: {
                    double t = omp_get_wtime();
                    insertSort(data_set, count);
                    double t1 = omp_get_wtime();
                    T = t1 - t;
                    print(data_set, count);
                    printf("Time of sorting - %.15lf sec\n", T);
                    system("pause");
                    break;
                }
                case 3: {
                    double t = omp_get_wtime();
                    mergeSort(data_set, 0, count - 1);
                    double t1 = omp_get_wtime();
                    T = t1 - t;
                    print(data_set, count);
                    printf("Time of sorting - %.15lf sec\n", T);
                    system("pause");
                    break;
                }
                case 4: {
                    double t = omp_get_wtime();
                    quickSortR(data_set, count);
                    double t1 = omp_get_wtime();
                    T = t1 - t;
                    print(data_set, count);
                    printf("Time of sorting - %.15lf sec\n", T);
                    system("pause");
                    break;
                }
                case 5: {
                    double t = omp_get_wtime();
                    shellSort(data_set, count);
                    double t1 = omp_get_wtime();
                    T = t1 - t;
                    print(data_set, count);
                    printf("Time of sorting - %.15lf sec\n", T);
                    system("pause");
                    break;
                }
                case 6: {
                    double t = omp_get_wtime();
                    countingSort(data_set, count);
                    double t1 = omp_get_wtime();
                    T = t1 - t;
                    print(data_set, count);
                    printf("Time of sorting - %.15lf sec\n", T);
                    system("pause");
                    break;
                }
                case 27: {
                    break;
                }
                }
                break;
            }
            case 1: {
                quickSortR(data_set, count);
                reverse(data_set, count);
                print(data_set, count);
                system("pause");
            }
            }

        }
    }
}

long find_count(char* path)
{
    struct _finddata_t c_file;
    struct _finddata_t* tmp;
    intptr_t hFile;
    long count = 0, size = 0;
    while (1){
        if ((hFile = _findfirst(("%s", path), &c_file)) == -1L) {   
            system("pause");
            continue;
        }
        do {
            if (c_file.size > 0)
                size++;
        } while (_findnext(hFile, &c_file) == 0);
        if (size == 0) {
            system("pause");
            continue;
        }
        tmp = calloc(size, sizeof(struct _finddata_t));
        if (tmp != NULL)
            buf = tmp;
        else
            break;
        hFile = _findfirst(("%s", path), &c_file);
        do
        {
            if ((c_file.size > 0) && (count < size))
                buf[count++] = c_file;
        } while (_findnext(hFile, &c_file) == 0);
        _findclose(hFile);
        break;
    }
    return count;
}