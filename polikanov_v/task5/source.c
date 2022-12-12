#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h> 
#include <stdlib.h>  
#include <io.h>  
#include <time.h>
#include <malloc.h>
#include <memory.h> 
#include <omp.h> 

int count_of_files = 0;
int max_size_of_file = 0;


typedef struct _finddata_t files_info; 
files_info* copy_files;


files_info* finding_files() {
    int count = 0;
    struct _finddata_t c_file;

    intptr_t hFile;
    int wrong_directory = 1;
    char path[200];
    scanf("%s", path); 

    while(wrong_directory == 1){
        if ((hFile = _findfirst(path, &c_file)) == -1L){
            printf("  Нет файлов в данной директории\n");
            printf("  Введите верную директорию:\n\n  ");
            scanf("%s", path);
        }
        else {
            wrong_directory = 0;
        }
     }   

     do {
         char buffer[30];
         ctime_s(buffer, _countof(buffer), &c_file.time_write);
         count++;
         if (c_file.size > max_size_of_file) {
             max_size_of_file = c_file.size;
         }
     } while (_findnext(hFile, &c_file) == 0);


    files_info* files = (files_info*)malloc(count * sizeof(files_info));

    copy_files = (files_info*)malloc(count * sizeof(files_info));

    intptr_t h2File = _findfirst(path, &files[0]);

    for (int i = 1; i < count; i++) {
        _findnext(h2File, &files[i]);

    }

    intptr_t h2File_copy = _findfirst(path, &copy_files[0]);

    for (int i = 1; i < count; i++) {
        _findnext(h2File_copy, &copy_files[i]);

    }
    count_of_files = count;
    return files;

}

void bubble_sort(files_info* files, int count_of_files){
    int i, j;
    for (i = 0; i < count_of_files; i++)
    {
        for (j = 1; j < count_of_files; j++)
        {
            if (files[j - 1].size > files[j].size)
            {
                files_info tmp = files[j - 1];
                files[j - 1] = files[j];
                files[j] = tmp;
            }
        }

    }
}

void selection_sort(files_info* files, int count_of_files){
    int i, j, k;
    files_info tmp;
    for (i = 0; i < count_of_files; i++)
    {
        k = i; tmp = files[i];
        for (j = i + 1; j < count_of_files; j++)
        {
            if (files[j].size < tmp.size)
            {
                k = j;
                tmp = files[j];
            }
        }
        files[k] = files[i]; files[i] = tmp;
    }
}

void insertion_sort(files_info* files, int count_of_files){
    int i, j;
    files_info tmp;
    for (i = 1; i < count_of_files; i++)
    {
        tmp = files[i];
        for (j = i - 1; j >= 0; j--)
            if (files[j].size > tmp.size)
                files[j + 1] = files[j];
            else
                break;
        files[j + 1] = tmp;
    }
}

void merge(files_info* files, int lb, int split, int ub) {
    int pos1 = lb;
    int pos2 = split + 1;
    int pos3 = 0;
    files_info* tmp = (files_info*)malloc(sizeof(files_info) * (ub - lb + 1));

    if (tmp != NULL)
    {
        while (pos1 <= split && pos2 <= ub)
        {
            if (files[pos1].size < files[pos2].size)
                tmp[pos3++] = files[pos1++];
            else
                tmp[pos3++] = files[pos2++];
        }
        while (pos2 <= ub)
            tmp[pos3++] = files[pos2++];
        while (pos1 <= split)
            tmp[pos3++] = files[pos1++];

        for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
            files[lb + pos3] = tmp[pos3];
    }
    free(tmp);
}
void merge_sort(files_info *files, int lb, int ub){
    int split;
    if (lb < ub)
    {
        split = (lb + ub) / 2;
        merge_sort(files, lb, split);
        merge_sort(files, split + 1, ub);
        merge(files, lb, split, ub);
    }
}

void qs(files_info *files, int first, int last){
    if (first < last)
    {
        int left = first, right = last, middle = files[(left + right) / 2].size;
        do
        {
            while (files[left].size < middle) left++;
            while (files[right].size > middle) right--;
            if (left <= right)
            {
                files_info tmp = files[left];
                files[left] = files[right];
                files[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        qs(files, first, right);
        qs(files, left, last);
    } // C:/windows/system32/*.*
}

void shell_sort(files_info* files, int size) {
    for (int s = size / 2; s > 0; s /= 2) {
        for (int i = s; i < size; ++i) {
            for (int j = i - s; j >= 0 && files[j].size > files[j + s].size; j -= s) {
                files_info temp = files[j];
                files[j] = files[j + s];
                files[j + s] = temp;
            }
        }
    }
}
void counting_sort(files_info* files, int count_of_files, int max_size_of_file) {
    int* c = (int*)malloc((max_size_of_file + 1) * sizeof(*files));
    memset(c, 0, sizeof(*files) * (max_size_of_file + 1));

    for (int i = 0; i < count_of_files; ++i) {
        ++c[files[i].size];
    }

    int b = 0;
    for (int i = 0; i < max_size_of_file + 1; ++i) {
        for (int j = 0; j < c[i]; ++j) {
            files[b++].size = i;
        }
    }

    free(c);
}
void sorting_process(files_info* files) {

    double t1, t2 = 0;
    int sort_choice;
    int is_right_choice = 0;
    int count_of_errors = 0;
    int up_or_down = 1;
    while (is_right_choice == 0) {
        printf("  Каким именно методом Вы хотите отсортировать массив? Введите соответствующую цифру:\n\n  !!!Эксперименты со вводом приведут к вылету программы!!!\n\n  1) Пузырьковая сортировка\n  2) Сортировка выбором\n  3) Сортировка вставками\n  4) Сортировка слиянием\n  5) Сортировка Хоара(быстрая)\n  6) Сортировка Шелла\n  7) Сортировка подсчетом\n\n  ");
        scanf("%d", &sort_choice);
        if (count_of_errors > 9) {
            printf("  Аварийный вылет");
            exit(EXIT_FAILURE);
        }
        switch (sort_choice) {
        case 1:
            t1 = omp_get_wtime();
            bubble_sort(files, count_of_files);
            t2 = omp_get_wtime();
            printf("  Вывести результат по убыванию размеров файлов или по возрастанию? Введите 0 / 1 (дефолтное значение - возрастание)\n  ");
            scanf("%d", &up_or_down);
            if (up_or_down == 0) {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[count_of_files - 1 - i].name, files[count_of_files - 1 - i].size);
                }

            }
            else {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[i].name, files[i].size);
                }
            }
            printf("  Время сортировки: %lf сек\n\n", t2 - t1);
            is_right_choice = 1;
            break;
        case 2:
            t1 = omp_get_wtime();
            selection_sort(files, count_of_files);
            t2 = omp_get_wtime();
            printf("  Вывести результат по убыванию размеров файлов или по возрастанию? Введите 0 / 1 (дефолтное значение - возрастание)\n  ");
            scanf("%d", &up_or_down);
            if (up_or_down == 0) {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[count_of_files - 1 - i].name, files[count_of_files - 1 - i].size);
                }

            }
            else {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[i].name, files[i].size);
                }
            }
            printf("  Время сортировки: %lf сек\n\n", t2 - t1);
            is_right_choice = 1;
            break;
        case 3:
            t1 = omp_get_wtime();
            insertion_sort(files, count_of_files);
            t2 = omp_get_wtime();
            printf("  Вывести результат по убыванию размеров файлов или по возрастанию? Введите 0 / 1 (дефолтное значение - возрастание)\n  ");
            scanf("%d", &up_or_down);
            if (up_or_down == 0) {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[count_of_files - 1 - i].name, files[count_of_files - 1 - i].size);
                }

            }
            else {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[i].name, files[i].size);
                }
            }
            printf("  Время сортировки: %lf сек\n\n", t2 - t1);
            is_right_choice = 1;
            break;
        case 4:
            t1 = omp_get_wtime();
            merge_sort(files, 0, count_of_files - 1);
            t2 = omp_get_wtime();
            printf("  Вывести результат по убыванию размеров файлов или по возрастанию? Введите 0 / 1 (дефолтное значение - возрастание)\n  ");
            scanf("%d", &up_or_down);
            if (up_or_down == 0) {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[count_of_files - 1 - i].name, files[count_of_files - 1 - i].size);
                }

            }
            else {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[i].name, files[i].size);
                }
            }
            printf("  Время сортировки: %lf сек\n\n", t2 - t1);
            is_right_choice = 1;
            break;
        case 5:
            t1 = omp_get_wtime();
            qs(files, 0, count_of_files - 1);
            t2 = omp_get_wtime();
            printf("  Вывести результат по убыванию размеров файлов или по возрастанию? Введите 0 / 1 (дефолтное значение - возрастание)\n  ");
            scanf("%d", &up_or_down);
            if (up_or_down == 0) {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[count_of_files - 1 - i].name, files[count_of_files - 1 - i].size);
                }

            }
            else {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[i].name, files[i].size);
                }
            }
            printf("  Время сортировки: %lf сек\n\n", t2 - t1);
            is_right_choice = 1;
            break;
        case 6:
            t1 = omp_get_wtime();
            shell_sort(files, count_of_files);
            t2 = omp_get_wtime();
            printf("  Вывести результат по убыванию размеров файлов или по возрастанию? Введите 0 / 1 (дефолтное значение - возрастание)\n  ");
            scanf("%d", &up_or_down);
            if (up_or_down == 0) {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[count_of_files - 1 - i].name, files[count_of_files - 1 - i].size);
                }

            }
            else {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[i].name, files[i].size);
                }
            }
            printf("  Время сортировки: %lf сек\n\n", t2 - t1);
            is_right_choice = 1;
            break;
        case 7:
            t1 = omp_get_wtime();
            counting_sort(files, count_of_files, max_size_of_file);
            t2 = omp_get_wtime();
            printf("  Вывести результат по убыванию размеров файлов или по возрастанию? Введите 0 / 1 (дефолтное значение - возрастание)\n  ");
            scanf("%d", &up_or_down);
            if (up_or_down == 0) {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[count_of_files - 1 - i].name, files[count_of_files - 1 - i].size);
                }

            }
            else {
                for (int i = 0; i < count_of_files; i++) {
                    printf("  %s  %d\n", files[i].name, files[i].size);
                }
            }
            printf("  Время сортировки: %lf сек\n\n", t2 - t1);
            is_right_choice = 1;
            break;



        default:
            printf("  Всё-таки это был промах по клавиатуре? Введите число по инструкции:\n\n");
            count_of_errors += 1;
        }
    }

 }

void main() {

        files_info* files;
        int sort_again = 1;

        setlocale(LC_ALL, "Rus");

        printf("\n  Добрый день! Данная программа сортирует указанную директорию выбранным методом сортировки\n  Для начала введите директорию:\n\n  ");

        files = finding_files();

        while (sort_again == 1) {
            sorting_process(files);
            printf("  Хотите отсортировать директорию еще раз, но другим способом? ДА / НЕТ - 1 / 0 (дефолтное значение - НЕТ)\n  ");
            scanf("%d",&sort_again);
            files = copy_files;                       
        } 

        printf("  Спасибо за работу!\n");
        printf("  \n");

        system("PAUSE");
}
    //C:/windows/system32/*.*
//C:/Study/Scratch_3/resources/static/assets/*.*