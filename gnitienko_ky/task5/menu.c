#include "Header.h"
#include "Windows.h"

#define KEY_EXIT 27
#define KEY_ENTER 13
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

int menu(char* menu[], int j) {
    int key = 0;
    int code = 0;
    COORD cursor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    do {
        system("cls");
        if (code == KEY_ARROW_UP) key--;
        if (code == KEY_ARROW_DOWN) key++;
        if (key < 0) key = j-1;
        if (key > j-1) key = 0;
        SetConsoleTextAttribute(hStdOut, 10);
        for (int i = 0; i < j; i++) {
            printf("  %s\n", menu[i]);
        }
        SetConsoleTextAttribute(hStdOut, 15);
        cursor.Y = key;
        cursor.X = 2;
        SetConsoleCursorPosition(hStdOut, cursor);
        printf("%s", menu[key]);
        if ((code = _getch()) == KEY_EXIT) {
            key = KEY_EXIT;
            break;
        }
    } while ((code = _getch()) != KEY_ENTER);
    return key;
}