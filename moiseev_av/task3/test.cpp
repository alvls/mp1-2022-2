#include <windows.h>
#include <stdio.h>
#include <memory.h>

enum TColor {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
    LIGHTMAGENTA, YELLOW, WHITE
};

//-----------------------------------------------------------------------------
int wherex(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return -1;

    CONSOLE_SCREEN_BUFFER_INFO buf;

    GetConsoleScreenBufferInfo(Console, &buf);
    return buf.dwCursorPosition.X;
}

//-----------------------------------------------------------------------------
int wherey(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return -1;

    CONSOLE_SCREEN_BUFFER_INFO buf;

    GetConsoleScreenBufferInfo(Console, &buf);
    return buf.dwCursorPosition.Y;
}

//-----------------------------------------------------------------------------
COORD wherexy(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { -1, -1 };
    if (!Console)
        return pos;

    CONSOLE_SCREEN_BUFFER_INFO buf;

    GetConsoleScreenBufferInfo(Console, &buf);
    return buf.dwCursorPosition;
}

//-----------------------------------------------------------------------------
void clrscr(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    WORD Attr;
    DWORD Count;
    COORD pos = buf.dwCursorPosition;
    ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

    int col = Attr;
    int width = buf.dwSize.X;
    int height = buf.dwSize.Y;

    COORD zpos;
    zpos.X = 0;
    zpos.Y = 0;
    SetConsoleCursorPosition(Console, zpos);

    FillConsoleOutputAttribute(Console, col, width * height, zpos, &Count);
    FillConsoleOutputCharacter(Console, ' ', width * height, zpos, &Count);
}

//-----------------------------------------------------------------------------
void gotoxy(int x, int y)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    COORD pos;
    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(Console, pos);
}

//-----------------------------------------------------------------------------
void textcolor(int color)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    WORD Attr;
    DWORD Count;
    COORD pos = buf.dwCursorPosition;
    ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

    int bk_col = Attr / 16;
    int col = color % 16;
    col = col + bk_col * 16;

    SetConsoleTextAttribute(Console, col);

    char ch;
    pos = wherexy();
    ReadConsoleOutputCharacter(Console, &ch, 1, pos, &Count);
    printf("%c", ch);
    gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void textbackground(int color)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    WORD Attr;
    DWORD Count;
    COORD pos = buf.dwCursorPosition;
    ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

    int text_col = Attr % 16;
    int col = color % 16;
    col = color * 16 + text_col;

    SetConsoleTextAttribute(Console, col);

    char ch;
    pos = wherexy();
    ReadConsoleOutputCharacter(Console, &ch, 1, pos, &Count);
    printf("%c", ch);
    gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void textattr(int color)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    SetConsoleTextAttribute(Console, color);

    DWORD Count;
    char ch;
    COORD pos = wherexy();
    ReadConsoleOutputCharacter(Console, &ch, 1, pos, &Count);
    printf("%c", ch);
    gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void setwindow(int width, int height)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    SMALL_RECT rect;
    rect.Left = 0;
    rect.Right = width - 1;
    rect.Top = 0;
    rect.Bottom = height - 1;
    COORD size;
    size.X = width;
    size.Y = height;
    SetConsoleWindowInfo(Console, 1, &rect);
    SetConsoleScreenBufferSize(Console, size);
}

//-----------------------------------------------------------------------------
void setWindow(SMALL_RECT rect, COORD size)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    SetConsoleScreenBufferSize(Console, size);
    SetConsoleWindowInfo(Console, 1, &rect);
}

//-----------------------------------------------------------------------------
void getwindow(SMALL_RECT* rect, COORD* size)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    *rect = buf.srWindow;
    size->X = buf.dwSize.X;
    size->Y = buf.dwSize.Y;
}

//-----------------------------------------------------------------------------
void hidecursor(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_CURSOR_INFO buf;
    GetConsoleCursorInfo(Console, &buf);
    buf.bVisible = 0;
    SetConsoleCursorInfo(Console, &buf);
}

//-----------------------------------------------------------------------------
void showcursor(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_CURSOR_INFO buf;
    GetConsoleCursorInfo(Console, &buf);
    buf.bVisible = 1;
    SetConsoleCursorInfo(Console, &buf);
}

//-----------------------------------------------------------------------------
int main()
{
    const int COUNT = 16 * 16;
    SMALL_RECT window;
    COORD buf;
    getwindow(&window, &buf);
    hidecursor();
    printf("%d %d %d %d", window.Left, window.Top, window.Right, window.Bottom);
    setwindow(80, 25);
    getchar();
    textattr(LIGHTGRAY);

    clrscr();

    gotoxy(10, 10);
    printf("test\n");

    gotoxy(0, 12);
    textattr(RED);
    printf("abcd");
    getchar();

    gotoxy(2, 12);
    textbackground(BLUE);
    printf("cdef");
    getchar();

    gotoxy(4, 12);
    textcolor(BLUE);
    textbackground(YELLOW);
    printf("efgh");

    for (int i = 0; i < COUNT; i++)
    {
        textcolor(i);
        textbackground(i / 16);
        printf("a");
    }

    textattr(LIGHTGRAY);

    int page = GetConsoleOutputCP();
    printf("page = %d", page);
    SetConsoleOutputCP(1251);

    printf("press any key");
    getchar();
    setWindow(window, buf);

    showcursor();

    return 0;
}
//- end of file ---------------------------------------------------------------
