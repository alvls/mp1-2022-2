#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include <io.h>  
#include <time.h>
#include <omp.h>

#define TOO_MANY_FILES   100
#define MAX_PATH_LENGTH  200

typedef struct _finddata_t file_data;

// Procedure for cleaning the input stream
void clean_stdin()
{
    int c;
    do
        c = getchar();
    while (c != '\n' && c != EOF);
}

// Prototypes of procedures for working with navigation
void user_greeting();
void main_menu();
void return_to_main_menu();
void information_about_the_program();
void minute_of_a_joke();
void exit_the_program();

// Prototypes of procedures and functions for working with files
void working_with_directory();
void display_sorting_files_information(file_data *files_array, int count_of_files, char asc_or_desc);
int is_empty_directory(char *path_to_directory);
int count_of_files(char *path_to_directory);

// Main function
int main()
{
    user_greeting();
    main_menu();
    return 0;
}

//--------------------------------------------//
// Sortings and additional functions for them //
//--------------------------------------------//

// Exchange of values (structures)
void swap(file_data *first_item, file_data *second_item)
{
    file_data temp = *first_item;
    *first_item = *second_item;
    *second_item = temp;
}

// Bubble sort
void bubble_sort(file_data *files_array, int count_of_files)
{
    int i, j;
    int count = 0; // To optimize sorting performance
    for (i = 0; i < count_of_files; i++)
    {
        for (j = 1; j < count_of_files; j++)
        {
            if (files_array[j - 1].size > files_array[j].size)
            {
                swap(&files_array[j - 1], &files_array[j]);
                count = 1;
            }
        }
        if (count == 0)
            break;
    }
}

// Selection sort
void selection_sort(file_data *files_array, int count_of_files)
{
    int i, j, k;
    file_data tmp_structure;
    for (i = 0; i < count_of_files; i++)
    {
        k = i;
        tmp_structure = files_array[i];
        for (j = i + 1; j < count_of_files; j++)
        {
            if (files_array[j].size < tmp_structure.size)
            {
                k = j;
                tmp_structure = files_array[j];
            }
        }
        files_array[k] = files_array[i];
        files_array[i] = tmp_structure;
    }
}

// Insertion sort 
void insertion_sort(file_data *files_array, int count_of_files)
{
    int i, j;
    file_data tmp_structure;
    for (i = 1; i < count_of_files; i++)
    {
        tmp_structure = files_array[i];
        for (j = i - 1; j >= 0; j--)
            if (files_array[j].size > tmp_structure.size)
                files_array[j + 1] = files_array[j];
            else
                break;
        files_array[j + 1] = tmp_structure;
    }
}

// for Merge sort
void merge(file_data *files_array, int lb, int split, int ub)
{
    long pos1 = lb;
    long pos2 = split + 1;
    long pos3 = 0;
    file_data *temp_array = (file_data *)malloc(sizeof(file_data) * (ub - lb + 1));

    if (temp_array != NULL)
    {
        while (pos1 <= split && pos2 <= ub)
        {
            if (files_array[pos1].size < files_array[pos2].size)
                temp_array[pos3++] = files_array[pos1++];
            else
                temp_array[pos3++] = files_array[pos2++];
        }
        while (pos2 <= ub)
            temp_array[pos3++] = files_array[pos2++];
        while (pos1 <= split)
            temp_array[pos3++] = files_array[pos1++];

        for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
            files_array[lb + pos3] = temp_array[pos3];
    }
    free(temp_array);
}
// Merge sort
void merge_sort(file_data *files_array, int lb, int ub)
{
    int split;
    if (lb < ub)
    {
        split = (lb + ub) / 2;
        merge_sort(files_array, lb, split);
        merge_sort(files_array, split + 1, ub);
        merge(files_array, lb, split, ub);
    }
}

// Recursion for Quick sort
void quick_sort_rec(file_data *files_array, int low, int high)
{
    if (low < high)
    {
        int pivot_index = partition(files_array, low, high);
        quick_sort_rec(files_array, low, pivot_index - 1);
        quick_sort_rec(files_array, pivot_index + 1, high);
    }
}

// Quick (Hoare's) sort
void quick_sort(file_data *files_array, int count_of_files)
{
    quick_sort_rec(files_array, 0, count_of_files - 1);
}

// Partition for Quick sort
int partition(file_data *files_array, int low, int high)
{
    file_data pivot_value = files_array[high];
    int i = low;
    for (int j = low; j < high; j++)
    {
        if (files_array[j].size <= pivot_value.size)
        {
            swap(&files_array[i], &files_array[j]);
            i++;
        }
    }
    swap(&files_array[i], &files_array[high]);
    return i;
}

// Shell sort
void shell_sort(file_data *files_array, int count_of_files)
{
    for (int interval = count_of_files / 2; interval > 0; interval /= 2)
    {
        for (int i = interval; i < count_of_files; i++)
        {
            file_data tmp_structure = files_array[i];
            int j;
            for (j = i; j >= interval && files_array[j - interval].size > tmp_structure.size; j -= interval)
                files_array[j] = files_array[j - interval];
            files_array[j] = tmp_structure;
        }
    }
}

// Maximum file size for Counting sort
unsigned long max_file_size(file_data *files_array, int count_of_files)
{
    unsigned long result = 0;
    for (int i = 0; i < count_of_files; i++)
        result = max(result, files_array[i].size);
    return result;
}

// Counting sort
void counting_sort(file_data *files_array, int count_of_files, int max_file_size)
{
    file_data *res_array = (file_data *)malloc(count_of_files * sizeof(file_data));
    int *count_array = (int *)malloc((max_file_size + 1) * sizeof(int));
    unsigned long *sorted_size_array = (long *)malloc((count_of_files) * sizeof(long));

    if (res_array != NULL && count_array != NULL && sorted_size_array != NULL)
    {
        //memset(count_array, 0, sizeof(int) * (max_file_size)+1);
        for (unsigned long i = 0; i <= max_file_size; i++)
            count_array[i] = 0;

        for (int i = 0; i < count_of_files; i++)
            count_array[files_array[i].size]++;

        int k = 0;
        for (unsigned long i = 0; i <= max_file_size; i++)
            for (int j = 0; j < count_array[i]; j++)
                sorted_size_array[k++] = i;

        for (int i = 0; i < count_of_files; i++)
            for (int j = 0; j < count_of_files; j++)
                if (sorted_size_array[i] == files_array[j].size)
                {
                    res_array[i] = files_array[j];
                    files_array[j].size = max_file_size + 1;
                    break;
                }
        for (int i = 0; i < count_of_files; i++)
            files_array[i] = res_array[i];
    }
    free(res_array);
    free(count_array);
    free(sorted_size_array);
}

// -------------------//
// Working with files // 
// -------------------//

// Function to check if a given directory is empty
int is_empty_directory(char *path_to_directory)
{
    file_data c_file;
    intptr_t hFile;
    if ((hFile = _findfirst(path_to_directory, &c_file)) == -1L)
        return 1;
    else
        return 0;
}

// Function to count the files in a given directory
int count_of_files(char *path_to_directory)
{
    file_data c_file;
    intptr_t hFile = _findfirst(path_to_directory, &c_file);
    int result = 0;
    do
        result++;
    while (_findnext(hFile, &c_file) == 0);
    return result;
}

// Procedure for displaying information about sorting files in a given directory
void display_sorting_files_information(file_data *files_array, int count_of_files, char asc_or_desc)
{
    printf("\nCount of files: %d\n", count_of_files);
    char act = '0';
    if (count_of_files >= TOO_MANY_FILES)
    {
        printf("\nThere are quite a lot of files in this directory (>=100)\n\n");
        printf("Enter 's' to skip displaying file information on the screen\n");
        printf("Enter any other character to display file information anyway\n");
        printf("(WARNING: displaying files can take a very long time): ");

        act = getchar();

        clean_stdin();
        if (act == 's')
            return;
    }
    printf("\n");
    printf("FILE NAME                                                                                                FILE SIZE\n");
    printf("------------------------------------------------------------------------------------------------------------------\n");
    int i;
    if (asc_or_desc == '1')
        for (i = 0; i < count_of_files; i++)
            printf("%-80s\t%20lu bytes\n", files_array[i].name, files_array[i].size);
    else
        for (i = count_of_files - 1; i >= 0; i--)
            printf("%-80s\t%20lu bytes\n", files_array[i].name, files_array[i].size);

}

// Working with directory...
void working_with_directory()
{
    file_data c_file;
    intptr_t hFile;
    char path[MAX_PATH_LENGTH];

    system("cls");
    printf("Enter the directory path: ");
    gets_s(path, MAX_PATH_LENGTH);

    strcat(path, "\\*");

    if (is_empty_directory(path))
        printf("No files in current directory!");
    else
    {
        int count = count_of_files(path);
        file_data *files_array = (file_data *)malloc(sizeof(file_data) * count);
        if (files_array != NULL)
        {
            char cont_working = '0';
            do
            {
                intptr_t hFile = _findfirst(path, &files_array[0]);  // Reading data into a structure
                for (int i = 1; i < count; i++)
                    _findnext(hFile, &files_array[i]);

                char asc_or_desc = '0';
                while ((asc_or_desc != '1') && (asc_or_desc != '2'))
                {
                    (cont_working == 'y') ? printf("How will we sort the files?\n\n") : printf("\nHow will we sort the files?\n\n");  // Bringing beauty
                    printf("1 - sort in ascending order\n");
                    printf("2 - sort in descending order\n");
                    printf("\nChoose one of the items: ");

                    asc_or_desc = getchar();
                    clean_stdin();

                    if ((asc_or_desc != '1') && (asc_or_desc != '2'))
                    {
                        printf("\nAnd what did you mean by that?\nCheck the entered data and try again!\n");
                        continue;
                    }
                }
                system("cls");
                char sorting_method = '0';
                while ((sorting_method != '1') && (sorting_method != '2') && (sorting_method != '3') && (sorting_method != '4') && (sorting_method != '5') && (sorting_method != '6') && (sorting_method != '7'))
                {
                    printf("Choose a sorting method:\n\n");
                    printf("1 - Bubble sort\n");
                    printf("2 - Selection sort\n");
                    printf("3 - Insertion sort\n");
                    printf("4 - Merge sort\n");
                    printf("5 - Quick sort\n");
                    printf("6 - Shell sort\n");
                    printf("7 - Counting sort\n");
                    printf("\nChoose one of the items: ");

                    sorting_method = getchar();
                    clean_stdin();

                    if ((sorting_method != '1') && (sorting_method != '2') && (sorting_method != '3') && (sorting_method != '4') && (sorting_method != '5') && (sorting_method != '6') && (sorting_method != '7'))
                    {
                        printf("\nAnd what did you mean by that?\nCheck the entered data and try again!\n");
                        continue;
                    }
                }
                system("cls");
                double t1 = 0, t2 = 0; // to calculate sorting time
                switch (sorting_method)
                {
                case '1': t1 = omp_get_wtime();
                    bubble_sort(files_array, count);
                    t2 = omp_get_wtime();
                    break;
                case '2': t1 = omp_get_wtime();
                    selection_sort(files_array, count);
                    t2 = omp_get_wtime();
                    break;
                case '3': t1 = omp_get_wtime();
                    insertion_sort(files_array, count);
                    t2 = omp_get_wtime();
                    break;
                case '4': t1 = omp_get_wtime();
                    merge_sort(files_array, 0, count);
                    t2 = omp_get_wtime();
                    break;
                case '5': t1 = omp_get_wtime();
                    quick_sort(files_array, count);
                    t2 = omp_get_wtime();
                    break;
                case '6': t1 = omp_get_wtime();
                    shell_sort(files_array, count);
                    t2 = omp_get_wtime();
                    break;
                case '7': t1 = omp_get_wtime();
                    counting_sort(files_array, count, max_file_size(files_array, count));
                    t2 = omp_get_wtime();
                    break;
                default:  printf("\nUnexpected program error\n");
                    system("pause");
                    exit(EXIT_FAILURE);
                    break;
                }
                double sorting_time = t2 - t1;
                printf("The files have been sorted\nSorting time: %lf seconds\n", sorting_time);
                display_sorting_files_information(files_array, count, asc_or_desc);

                printf("\nDo you want to change the file sorting options for a given directory?\n");
                printf("If yes, enter 'y'. To exit the mode of working with directory files, enter any other character: ");

                cont_working = getchar();
                clean_stdin();

                if (cont_working == 'y') system("cls");
            } while (cont_working == 'y');
        }
        else
        {
            printf("Memory allocation error");
            system("pause");
            exit(EXIT_FAILURE);
        }
        free(files_array);
        files_array = NULL;
    }
    return_to_main_menu();
}

// -------------------//
//     Navigation     //
// -------------------//

// Procedure for greeting the user
void user_greeting()
{
    printf("Hello!\nWelcome to my file manager prototype :)\n\n");
}

// Procedure that implements the main menu of the program
void main_menu()
{
    char act = '0';
    printf("What do you want to do?\n\n");
    printf("1 - view information about the program\n");
    printf("2 - go to work with the directory\n");
    printf("3 - watch a joke (not funny)\n");
    printf("4 - exit the program\n");

    while ((act != '1') && (act != '2') && (act != '3') && (act != '4'))
    {
        printf("\nSelect one of the items: ");
        act = getchar();
        clean_stdin();
        switch (act)
        {
        case '1': information_about_the_program();
            break;
        case '2': working_with_directory();
            break;
        case '3': minute_of_a_joke();
            break;
        case '4': exit_the_program();
            break;
        default:  printf("\nAnd what did you mean by that?\nCheck the entered data and try again!\n");
            break;
        }
    }
}

// Procedure for returning to the menu
void return_to_main_menu()
{
    printf("\n\nEnter any character to return to the menu: ");
    getchar();
    clean_stdin();
    system("cls");
    main_menu();
}

// Procedure for displaying program information
void information_about_the_program()
{
    system("cls");
    printf("This program is designed to display sorted files in a given directory\n");
    printf("You have the option to sort files in ascending and descending order of size");
    return_to_main_menu();
}

// Anecdote for the user
void minute_of_a_joke()
{
    system("cls");
    printf("Two bytes meet. The first byte asks, \"Are you ill?\" The second byte replies, \"No, just feeling a bit off.\"");
    return_to_main_menu();
};

// Procedure for exiting the program
void exit_the_program()
{
    system("cls");
    printf("Thank you for using my program\nCome again :)\n");
    system("pause");
    exit(EXIT_SUCCESS);
}
