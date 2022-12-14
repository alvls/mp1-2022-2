#pragma once

#include <windows.h>
#include <stdio.h>
#include <memory.h>

extern COORD wnd;

enum TColor {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
    LIGHTMAGENTA, YELLOW, WHITE
};

int wherex(void);
int wherey(void);
COORD wherexy(void);
void clrscr(void);
void gotoxy(int x, int y);
void textcolor(int color);
void textbackground(int color);
void textattr(int color);
void setwindow(int width, int height);
void setWindow(SMALL_RECT rect, COORD size);
void getwindow(SMALL_RECT* rect, COORD* size);
void hidecursor(void);
void showcursor(void);