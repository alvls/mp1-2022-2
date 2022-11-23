#include <stdio.h> 
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <math.h>

#define MAXSTACK 2048
#define MAXSTRING 55
#define FILESMAX 20
#define bt_done_id 2
#define edt1_id 3
#define cb1_id 4
#define cb2_id 5


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

LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
    }

    //else if (message == WM_COMMAND)
    //{
    //    if (LOWORD(wparam) == edt1_id)
    //    {
    //        int nc = HIWORD(wparam);
    //        char c[100];
    //        GetWindowText(lparam, c, MAXSTRING);
    //        if (nc == EN_UPDATE)
    //        {
    //            SetWindowText(cap1, c);
    //            printf("Полученная строка: %s\n", c);
    //        }
    //    }

    //    if (LOWORD(wparam) == cb2_id)
    //    {
    //        if (HIWORD(wparam) == CBN_SELCHANGE)
    //        {
    //            int id = SendMessage(lparam, CB_GETCURSEL, 0, 0);
    //            printf("\nВыбран способ № %d\n", id);
    //        }
    //    }

    //    if (LOWORD(wparam) == cb1_id)
    //    {
    //        if (HIWORD(wparam) == CBN_SELCHANGE)
    //        {
    //            int id = SendMessage(lparam, CB_GETCURSEL, 0, 0);
    //            printf("\nВыбран метод № %d\n", id);
    //        }
    //    }

    //    if (bt_done == lparam)
    //    {
    //        printf("Нажато\n");
    //    }
    //}
    else
    {
        return DefWindowProcA(hwnd, message, wparam, lparam);
    }
}

void main()
{
    ShowWindow(GetConsoleWindow(), SW_SHOW); //SW_HIDE - спрятать консоль SW_SHOW - показать консоль

    setlocale(LC_ALL, "Rus");

    WNDCLASSA wcl;

    memset(&wcl, 0, sizeof(WNDCLASSA)); //заполняем все байты памяти по адресу wcl нулями
    wcl.lpszClassName = "Window";
    wcl.lpfnWndProc = WndProc;          //обработка сообщений окна

    RegisterClassA(&wcl);
    HWND hwnd;
    hwnd = CreateWindow("Window", "Sorts", WS_OVERLAPPEDWINDOW, 10, 10, 870, 557, NULL, NULL, NULL, NULL); //создание окна

    ShowWindow(hwnd, SW_SHOWNORMAL);
    ///////////////////////////////////////////////////////////////
    HDC hdc;
    PAINTSTRUCT ps;
    hdc = BeginPaint(hwnd, &ps);

    int y0 = 200, x0 = 200, x1 = 200, x2 = 200;
    for (int i = 0; i < 50; i++)
    {
        SetPixel(hdc, x1, y0, RGB(255, 0, 0));
        SetPixel(hdc, x2, y0, RGB(255, 0, 0));
        y0--;
        x1 = x1 + 1;
        x2 = x2 - 1;
    }
    EndPaint(hwnd, &ps);
    ///////////////////////////////////////////////////////////////

    //bt_done = CreateWindow("button", "Отсортировать!", WS_VISIBLE | WS_CHILD, 65, 450, 130, 50, hwnd, bt_done_id, NULL, NULL, TEXT("Arial"));

    //HWND edt;
    //edt = CreateWindow("edit", "example: C:\\", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE, 50, 90, 170, 20, hwnd, edt1_id, NULL, NULL, NULL);

    //HWND name;
    //name = CreateWindow("static", "SORTs", WS_VISIBLE | WS_CHILD | SS_CENTER, 75, 20, 120, 32, hwnd, NULL, NULL, NULL);

    //HWND cap4;
    //cap4 = CreateWindow("static", "Выберете способ:", WS_VISIBLE | WS_CHILD, 50, 150, 170, 17, hwnd, NULL, NULL, NULL, TEXT("Arial"));

    //HWND cap5;
    //cap5 = CreateWindow("static", " Время сортировки:", WS_VISIBLE | WS_CHILD, 360, 480, 377, 20, hwnd, NULL, NULL, NULL);

    //HWND cap6;
    //cap6 = CreateWindow("static", "Выберете метод:", WS_VISIBLE | WS_CHILD, 50, 250, 170, 17, hwnd, NULL, NULL, NULL, TEXT("Arial"));

    //HWND style_for_name;
    //style_for_name = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Comic Sans MS"));

    //HWND font_for_main_text;
    //font_for_main_text = CreateFont(15, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Arial"));


    //cap1 = CreateWindow("static", "Введите путь к папке:", WS_VISIBLE | WS_CHILD, 50, 65, 170, 17, hwnd, NULL, NULL, NULL, TEXT("Arial"));

    //cap2 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 260, 20, 275, 450, hwnd, NULL, NULL, NULL);

    //cap2_1 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 265, 65, 150, 20, hwnd, NULL, NULL, NULL);

    //cap2_2 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 395, 65, 100, 20, hwnd, NULL, NULL, NULL);

    //cap2_3 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 475, 65, 35, 20, hwnd, NULL, NULL, NULL);

    //cap3 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 565, 20, 275, 450, hwnd, NULL, NULL, NULL);

    //cap3_1 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 570, 65, 150, 20, hwnd, NULL, NULL, NULL);

    //cap3_2 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 700, 65, 100, 20, hwnd, NULL, NULL, NULL);

    //cap3_3 = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 780, 65, 35, 20, hwnd, NULL, NULL, NULL);

    //CB = CreateWindow("combobox", "", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 50, 275, 170, 200, hwnd, cb1_id, NULL, NULL);

    //CB2 = CreateWindow("combobox", "", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 50, 175, 170, 70, hwnd, cb2_id, NULL, NULL);


    //SendMessage(name, WM_SETFONT, style_for_name, TRUE);
    //SendMessage(edt, WM_SETFONT, font_for_main_text, TRUE);
    //SendMessage(cap1, WM_SETFONT, font_for_main_text, TRUE);
    //SendMessage(cap4, WM_SETFONT, font_for_main_text, TRUE);
    //SendMessage(cap6, WM_SETFONT, font_for_main_text, TRUE);
    //SendMessage(bt_done, WM_SETFONT, font_for_main_text, TRUE);
    //SendMessage(CB, WM_SETFONT, font_for_main_text, TRUE);
    //SendMessage(CB2, WM_SETFONT, font_for_main_text, TRUE);

    //SendMessage(CB, CB_ADDSTRING, 0, "Пузырьком");
    //SendMessage(CB, CB_ADDSTRING, 0, "Выбором");
    //SendMessage(CB, CB_ADDSTRING, 0, "Вставками");
    //SendMessage(CB, CB_ADDSTRING, 0, "Слиянием");
    //SendMessage(CB, CB_ADDSTRING, 0, "Хоара");
    //SendMessage(CB, CB_ADDSTRING, 0, "Шелла");
    //SendMessage(CB, CB_ADDSTRING, 0, "Подсчетом");
    //SendMessage(CB, CB_SETCURSEL, 0, 0);

    //SendMessage(CB2, CB_ADDSTRING, 0, "По возрастанию");
    //SendMessage(CB2, CB_ADDSTRING, 0, "По убыванию");
    //SendMessage(CB2, CB_SETCURSEL, 0, 0);


    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);   //передаем сообщение окну
    }
}
