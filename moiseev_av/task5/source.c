#include <stdio.h> 
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <io.h>

#define MAXSTACK 2048
#define NUMBERS 8
#define bt_done_id 2
#define edt1_id 3
#define cb1_id 4
#define cb2_id 5

HWND hwnd;
HWND bt_done;
HWND cap1;
HWND cap2;
HWND cap2_1;
HWND cap2_2;
HWND cap2_3;
HWND cap3;
HWND cap3_1;
HWND cap3_2;
HWND cap3_3;
HWND cap4;
HWND cap5;
HWND CB;
HWND CB2;

int i = 0, j = 0, cnt = 0, min_or_max = 0, user_chose = 0, sizes[20];
float time_spent = 0.0;
char dir[100], c[100], ch;
char* names[20];

int results()
{
    DestroyWindow(cap3_1);
    DestroyWindow(cap3_2);
    DestroyWindow(cap3_3);

    SetWindowText(cap3, "Отсортированный список\nфайлов:\n");
    for (i = 0; i < cnt; i++)
    {
        for (j = 0; j < cnt; j++)
        {
            if (sizes[i] % 100 == j)
            {
                char text[20];
                sprintf_s(text, 20, "%lu", sizes[i] / 100);

                cap3_1 = CreateWindow("static", names[j], WS_VISIBLE | WS_CHILD, 545, 65 + i * 20, 150, 20, hwnd, NULL, NULL, NULL);
                cap3_2 = CreateWindow("static", text, WS_VISIBLE | WS_CHILD, 675, 65 + i * 20, 100, 20, hwnd, NULL, NULL, NULL);
                cap3_3 = CreateWindow("static", "Кбит", WS_VISIBLE | WS_CHILD, 755, 65 + i * 20, 35, 20, hwnd, NULL, NULL, NULL);
                break;
            }
        }
    }
    char* names = calloc(20, 1);
    int sizes = calloc(20, 1);

    char text[20];
    sprintf_s(text, 20, "%0.3f", time_spent - 0.001);

    cap5 = CreateWindow("static", "секунд", WS_VISIBLE | WS_CHILD, 590, 480, 50, 20, hwnd, NULL, NULL, NULL);
    cap5 = CreateWindow("static", text, WS_VISIBLE | WS_CHILD, 540, 480, 50, 20, hwnd, NULL, NULL, NULL);
}

void bublle_max_min()
{
    int x;
    time_spent = 0.0;
    clock_t begin = clock();

    for (i = 0; i < cnt; i++)
    {
        for (j = cnt - 1; j > i; j--)
        {
            if (sizes[j - 1] < sizes[j]) 
            {
                x = sizes[j - 1]; 
                sizes[j - 1] = sizes[j];
                sizes[j] = x;
            }
        }
    }
    Sleep(1);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    results();
}

void bublle_min_max()
{
    int x;
    time_spent = 0.0;
    clock_t begin = clock();

    for (i = 0; i < cnt; i++)
    {
        for (j = cnt - 1; j > i; j--)
        {
            if (sizes[j - 1] > sizes[j])
            {
                x = sizes[j - 1];
                sizes[j - 1] = sizes[j];
                sizes[j] = x;
            }
        }
    }
    Sleep(1);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    results();
}

void chose_max_min()
{
    int k, x;
    time_spent = 0.0;
    clock_t begin = clock();

    for (i = 0; i < cnt; i++)
    {
        k = i; 
        x = sizes[i];
        for (j = i + 1; j < cnt; j++)
        {
            if (sizes[j] > x)
            {
                k = j; x = sizes[j];
            }
        }
        sizes[k] = sizes[i];
        sizes[i] = x;
    }
    Sleep(1);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    results();
}

void chose_min_max()
{
    int k, x;
    time_spent = 0.0;
    clock_t begin = clock();

    for (i = 0; i < cnt; i++)
    {
        k = i;
        x = sizes[i];
        for (j = i + 1; j < cnt; j++)
        {
            if (sizes[j] < x)
            {
                k = j; x = sizes[j];
            }
        }
        sizes[k] = sizes[i];
        sizes[i] = x;
    }
    Sleep(1);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    results();
}

void insert_max_min()
{
    int x;
    long i, j;
    time_spent = 0.0;
    clock_t begin = clock();

    for (i = 0; i < cnt; i++)
    {
        x = sizes[i];
        for (j = i - 1; j >= 0 && sizes[j] < x; j--)
        {
            sizes[j + 1] = sizes[j];
        }
        sizes[j + 1] = x;
    }
    Sleep(1);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    results();
}

void insert_min_max()
{
    int x;
    long i, j;
    time_spent = 0.0;
    clock_t begin = clock();

    for (i = 0; i < cnt; i++)
    {
        x = sizes[i];
        for (j = i - 1; j >= 0 && sizes[j] > x; j--)
        {
            sizes[j + 1] = sizes[j];
        }
        sizes[j + 1] = x;
    }
    Sleep(1);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    results();
}

void merge_min_max(int size[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int R[20] = { 0 };
    int L[20] = { 0 };

    for (i = 0; i < n1; i++)
    {
        L[i] = size[l + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = size[m + 1 + j];
    }
        
    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j]) 
        {
            size[k] = L[i];
            i++;
        }
        else 
        {
            size[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {
        size[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        size[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort_min_max(int size[], int l, int r)
{
    if (l < r) 
    {
        int m = l + (r - l) / 2;

        mergeSort_min_max(size, l, m);
        mergeSort_min_max(size, m + 1, r);
        merge_min_max(size, l, m, r);
    }
}

void merge_max_min(int size[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int R[20] = { 0 };
    int L[20] = { 0 };

    for (i = 0; i < n1; i++)
        L[i] = size[l + i];
    for (j = 0; j < n2; j++)
        R[j] = size[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) 
    {
        if (L[i] > R[j])
        {
            size[k] = L[i];
            i++;
        }
        else 
        {
            size[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {
        size[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        size[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort_max_min(int size[], int l, int r)
{
    if (l < r) 
    {
        int m = l + (r - l) / 2;

        mergeSort_max_min(size, l, m);
        mergeSort_max_min(size, m + 1, r);
        merge_max_min(size, l, m, r);
    }
}

void hoara_min_max(int* s_arr, int first, int last)
{
    if (first < last)
    {
        int left = first, right = last, middle = s_arr[(left + right) / 2];
        do
        {
            while (s_arr[left] < middle) left++;
            while (s_arr[right] > middle) right--;
            if (left <= right)
            {
                int tmp = s_arr[left];
                s_arr[left] = s_arr[right];
                s_arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);

        hoara_min_max(s_arr, first, right);
        hoara_min_max(s_arr, left, last);
    }
}

void hoara_max_min(int* s_arr, int first, int last)
{
    if (first < last)
    {
        int left = first, right = last, middle = s_arr[(left + right) / 2];
        do
        {
            while (s_arr[left] > middle) left++;
            while (s_arr[right] < middle) right--;
            if (left <= right)
            {
                int tmp = s_arr[left];
                s_arr[left] = s_arr[right];
                s_arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);

        hoara_max_min(s_arr, first, right);
        hoara_max_min(s_arr, left, last);
    }
}

void shell_min_max()
{
    int step;
    int tmp;
    time_spent = 0.0;
    clock_t begin = clock();

    for (step = cnt / 2; step > 0; step /= 2)
    {
        for (i = step; i < cnt; i++)
        {
            tmp = sizes[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < sizes[j - step])
                {
                    sizes[j] = sizes[j - step];
                }
                else
                {
                    break;
                }
            }
            sizes[j] = tmp;
        }
    }
    Sleep(1);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    results();
}

void shell_max_min()
{
    int step;
    int tmp;
    time_spent = 0.0;
    clock_t begin = clock();

    for (step = cnt / 2; step > 0; step /= 2)
    {
        for (i = step; i < cnt; i++)
        {
            tmp = sizes[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp >= sizes[j - step])
                {
                    sizes[j] = sizes[j - step];
                }  
                else
                {
                    break;
                }   
            }
            sizes[j] = tmp;
        }
    }
    Sleep(1);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    results();
}

void countingSort_min_max() 
{
    int mx = 0;
    time_spent = 0.0;
    clock_t begin = clock();

    for (i = 0; i < cnt; i++)
    {
        if (sizes[i] > mx)
        {
            mx = sizes[i];
        }
    }

    int* c = (int*)malloc((mx + 1) * sizeof(*sizes));
    memset(c, 0, sizeof(*sizes) * (mx + 1));

    for (int i = 0; i < cnt; ++i)
    {
        ++c[sizes[i]];
    }

    int b = 0;

    for (int i = 0; i < mx + 1; ++i)
    {
        for (int j = 0; j < c[i]; ++j)
        {
            sizes[b++] = i;
        }
    }
    free(c);
    Sleep(1);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    results();
}

void countingSort_max_min()
{
    int mx = 0;
    time_spent = 0.0;
    clock_t begin = clock();

    for (i = 0; i < cnt; i++)
    {
        if (sizes[i] > mx)
        {
            mx = sizes[i];
        }
    }

    int* c = (int*)malloc((mx + 1) * sizeof(*sizes));
    memset(c, 0, sizeof(*sizes) * (mx + 1));

    for (int i = 0; i < cnt; ++i) 
    {
        ++c[sizes[i]];
    }

    int b = 0;

    for (int i = mx; i >= 0; --i) 
    {
        for (int j = c[i] - 1; j >= 0; --j)
        {
            sizes[b++] = i;
        }
    }
    free(c);
    Sleep(1);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    results();
}

void chose_for_switch()
{
    switch (user_chose)
    {
    case 0: if (min_or_max == 0)
            {
                bublle_min_max();
            }
            else
            {
                bublle_max_min();
            }
            break;

    case 1: if (min_or_max == 0)
            {
                chose_min_max();
            }
            else
            {
                chose_max_min();
            }
            break;

    case 2: if (min_or_max == 0)
            {
                insert_min_max();
            }
            else
            {
                insert_max_min();
            }
            break;

    case 3: if (min_or_max == 0)
            {
                time_spent = 0.0;
                clock_t begin = clock();

                mergeSort_min_max(sizes, 0, cnt - 1);

                Sleep(1);
                clock_t end = clock();
                time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

                results();
            }
            else
            {
                time_spent = 0.0;
                clock_t begin = clock();

                mergeSort_max_min(sizes, 0, cnt - 1);

                Sleep(1);
                clock_t end = clock();
                time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

                results();
            }
            break;

    case 4: if (min_or_max == 0)
            {
                time_spent = 0.0;
                clock_t begin = clock();
                
                hoara_min_max(sizes, 0, cnt - 1);

                Sleep(1);
                clock_t end = clock();
                time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

                results();
            }
            else
            {
                time_spent = 0.0;
                clock_t begin = clock();
                
                hoara_max_min(sizes, 0, cnt - 1);

                Sleep(1);
                clock_t end = clock();
                time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

                results();
            }
            break;

    case 5: if (min_or_max == 0)
            {
                shell_min_max();
            }
            else
            {
                shell_max_min();
            }
            break;

    case 6: if (min_or_max == 0)
            {
                countingSort_min_max();
            }
            else
            {
                countingSort_max_min();
            }
            break;

    default:
            break;
    }
}

void file()
{
    while (1)
    {
        size_t len1 = strlen(c);

        if (len1 == 0)
        {
            SetWindowText(cap3, "");
            cap5 = CreateWindow("static", " Время сортировки:", WS_VISIBLE | WS_CHILD, 400, 480, 250, 20, hwnd, NULL, NULL, NULL);
            SetWindowText(cap2, "Не выбрана директория\nПовторите попытку ввода!\n");
            return;
        }
        else
        {
            size_t len2 = strlen("\\*.*");
            char* result = malloc(len1 + len2 + 1);

            memcpy(result, c, len1);
            memcpy(result + len1, "\\*.*", len2 + 1);

            struct _finddata_t c_file;
            intptr_t hFile;

            if ((hFile = _findfirst(result, &c_file)) == -1L)
            {
                SetWindowText(cap3, "");
                cap5 = CreateWindow("static", " Время сортировки:", WS_VISIBLE | WS_CHILD, 400, 480, 250, 20, hwnd, NULL, NULL, NULL);
                SetWindowText(cap2, "Папка пуста или не верно выбрана директория\nПовторите попытку ввода!\n");
                free(result);
                return;
            }
            else
            {
                cnt = 0;
                free(result);

                DestroyWindow(cap2_1);
                DestroyWindow(cap2_2);
                DestroyWindow(cap2_3);
                SetWindowText(cap2, "Список файлов в выбранной директории:\n");
                
                do
                {
                    if (c_file.size / 1024 > 0 && cnt < 20)
                    {
                        
                        sizes[cnt] = c_file.size / 1024 * 100 + cnt;

                        names[cnt] = (char*)malloc(255);

                        strcpy_s(names[cnt], 255, c_file.name);

                        char text[20];
                        sprintf_s(text, 20, "%lu", c_file.size / 1024);

                        cap2_1 = CreateWindow("static", names[cnt], WS_VISIBLE | WS_CHILD, 265, 65 + cnt * 20, 150, 20, hwnd, NULL, NULL, NULL);
                        cap2_2 = CreateWindow("static", text, WS_VISIBLE | WS_CHILD, 395, 65 + cnt * 20, 100, 20, hwnd, NULL, NULL, NULL);
                        cap2_3 = CreateWindow("static", "Кбит", WS_VISIBLE | WS_CHILD, 475, 65 + cnt * 20, 35, 20, hwnd, NULL, NULL, NULL);

                        cnt++;
                    }

                } while (_findnext(hFile, &c_file) == 0);

                _findclose(hFile);
                chose_for_switch();
                return;
            }
        }
    }
}

LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
    }

    else if (message == WM_COMMAND)
    {
        if (LOWORD(wparam) == edt1_id)
        {
            int nc = HIWORD(wparam);
            GetWindowText(lparam, c, 100);
            if (nc == EN_UPDATE)
            {
                SetWindowText(cap1, c);
                printf("Полученная строка: %s\n", c);
            }
        }

        if (LOWORD(wparam) == cb2_id)
        {
            if (HIWORD(wparam) == CBN_SELCHANGE)
            {
                int id = SendMessage(lparam, CB_GETCURSEL, 0, 0);
                min_or_max = id;
                printf("\nВыбран способ № %d\n", min_or_max);
            }
        }

        if (LOWORD(wparam) == cb1_id)
        {
            if (HIWORD(wparam) == CBN_SELCHANGE)
            {
                int id = SendMessage(lparam, CB_GETCURSEL, 0, 0);
                user_chose = id;
                printf("\nВыбран метод № %d\n", user_chose);
            }
        }

        if (bt_done == lparam)
        {
            file();
        }
    }
    else
    {
        return DefWindowProcA(hwnd, message, wparam, lparam);
    }
}

void main()
{
    setlocale(LC_ALL, "Rus");

    WNDCLASSA wcl;
        
        memset(&wcl, 0, sizeof(WNDCLASSA)); //заполняем все байты памяти по адресу wcl нулями
        wcl.lpszClassName = "Window";
        wcl.lpfnWndProc = WndProc;          //обработка сообщений окна
 
    RegisterClassA(&wcl);

    hwnd = CreateWindow("Window", "Sorts", WS_OVERLAPPEDWINDOW, 10, 10, 820, 550, NULL, NULL, NULL, NULL); //создание окна

    ShowWindow(hwnd, SW_SHOWNORMAL);

    bt_done = CreateWindow("button", "Отсортировать!", WS_VISIBLE | WS_CHILD, 70, 450, 120, 50, hwnd, bt_done_id, NULL, NULL);

    HWND edt;
    edt = CreateWindow("edit", "example: C:\\", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE, 50, 90, 170, 20, hwnd, edt1_id, NULL, NULL, NULL);
    
    HWND name;
    name = CreateWindow("static", "SORTs", WS_VISIBLE | WS_CHILD | SS_CENTER, 75, 20, 120, 32, hwnd, NULL, NULL, NULL);

    HWND cap4;
    cap4 = CreateWindow("static", "Выберете способ:", WS_VISIBLE | WS_CHILD, 50, 150, 170, 20, hwnd, NULL, NULL, NULL);

    HWND cap5;
    cap5 = CreateWindow("static", " Время сортировки:", WS_VISIBLE | WS_CHILD, 400, 480, 250, 20, hwnd, NULL, NULL, NULL);

    HWND cap6;
    cap6 = CreateWindow("static", "Выберете метод:", WS_VISIBLE | WS_CHILD, 50, 250, 170, 20, hwnd, NULL, NULL, NULL);

    HWND style_for_name;
    style_for_name = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Comic Sans MS"));
    
    HWND font_for_main_text;
    font_for_main_text = CreateFont(15, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Arial"));
   
    cap1 = CreateWindow("static", "Введите путь к папке:", WS_VISIBLE | WS_CHILD, 50, 65, 170, 20, hwnd, NULL, NULL, NULL);
    
    cap2 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 260, 20, 250, 450, hwnd, NULL, NULL, NULL);
    
    cap2_1 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 265, 65, 150, 20, hwnd, NULL, NULL, NULL);

    cap2_2 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 395, 65, 100, 20, hwnd, NULL, NULL, NULL);

    cap2_3 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 475, 65, 35, 20, hwnd, NULL, NULL, NULL);

    cap3 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 540, 20, 250, 450, hwnd, NULL, NULL, NULL);

    cap3_1 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 545, 65, 150, 20, hwnd, NULL, NULL, NULL);

    cap3_2 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 675, 65, 100, 20, hwnd, NULL, NULL, NULL);

    cap3_3 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 755, 65, 35, 20, hwnd, NULL, NULL, NULL);

    CB = CreateWindow("combobox", "", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 50, 275, 170, 200, hwnd, cb1_id, NULL, NULL);

    CB2 = CreateWindow("combobox", "", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 50, 175, 170, 70, hwnd, cb2_id, NULL, NULL);


    SendMessage(name, WM_SETFONT, style_for_name, TRUE);
    SendMessage(edt, WM_SETFONT, font_for_main_text, TRUE);

    SendMessage(CB, WM_SETFONT, font_for_main_text, TRUE);
    SendMessage(CB2, WM_SETFONT, font_for_main_text, TRUE);
  
    SendMessage(CB, CB_ADDSTRING, 0, "Пузырьком");
    SendMessage(CB, CB_ADDSTRING, 0, "Выбором");
    SendMessage(CB, CB_ADDSTRING, 0, "Вставками");
    SendMessage(CB, CB_ADDSTRING, 0, "Слиянием");
    SendMessage(CB, CB_ADDSTRING, 0, "Хоара");
    SendMessage(CB, CB_ADDSTRING, 0, "Шелла");
    SendMessage(CB, CB_ADDSTRING, 0, "Подсчетом");
    SendMessage(CB, CB_SETCURSEL, 0, 0);

    SendMessage(CB2, CB_ADDSTRING, 0, "По возврастанию");
    SendMessage(CB2, CB_ADDSTRING, 0, "По убыванию");
    SendMessage(CB2, CB_SETCURSEL, 0, 0);


    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);   //передаем сообщение окну
    }
}
