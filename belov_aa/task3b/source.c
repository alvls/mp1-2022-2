#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include <Windows.h>
#include "ConsoleHelper.h"

int wndCenterX, wndCenterY;

void cons_center(int offset_x, int offset_y)
{
    gotoxy(wndCenterX + offset_x, wndCenterY + offset_y);
}

void pause()
{
    cons_center(-44 / 2, 2);
    system("PAUSE");
}

int rand_number(int begin, int end)
{
    return begin + (rand() % ((end - begin) + 1));
}

void shuffle_array(int* arr, int len, int excludeZeroIndex)
{
    int i, j, t;
    for (i = 0; i < len; i++)
    {
        j = rand_number(0, len - 1);
        t = arr[j];
        if ((arr[i] == 0 || t == 0) && (i == excludeZeroIndex || j == excludeZeroIndex)) continue;
        arr[j] = arr[i];
        arr[i] = t;
    }
}

void play_game(int n)
{
    int seed[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    shuffle_array(&seed, sizeof(seed) / sizeof(seed[0]), n - 1);

    int i, j;

    //////////////////////////////////////////////////////////////////////////
    int guess = 0;
    for (i = 0; i < n; i++)
    {
        guess += seed[i] * pow(10, i);
    }
    char title[64];
    snprintf(title, sizeof(title), "Bulls and Cows (answer: %d)", guess);
    SetConsoleTitle(title);
    //////////////////////////////////////////////////////////////////////////

    int ans;
    int attempts = 0;
    int cows, bulls;

    int guess_digit, ans_digit;

    clrscr();
    while (1)
    {
        attempts++;

        cons_center(-14 / 2, 0);
        textcolor(LIGHTGRAY);
        textbackground(BLACK);
        printf("YOUR ATTEMPT (%d):", attempts);
        Beep(750, 300);

        cons_center(-n / 2, 2);
        textcolor(BLUE);
        textbackground(YELLOW);
        for (i = 0; i < n; i++)
        {
            printf(" ");
        }
        cons_center(-n / 2, 2);

        scanf_s("%d", &ans);

        cows = 0, bulls = 0;

        for (i = 0; i < n; i++)
        {
            ans_digit = ans % 10;

            for (j = 0; j < n; j++)
            {
                if (seed[j] == ans_digit)
                {
                    if (i == j)
                    {
                        bulls++;
                        cons_center((-n / 2) + (n - i - 1), 2);
                        textcolor(GREEN);
                        textbackground(YELLOW);
                        printf("%d", ans_digit);
                    }
                    else
                    {
                        cows++;
                    }
                    break;
                }
            }

            ans /= 10;
        }

        if (bulls == n)
        {
            textbackground(BLACK);
            textcolor(GREEN);
            clrscr();
            cons_center(-27 / 2, 0);
            printf("You've won in %d attempts!", attempts);
            gotoxy(0, 0);
            break;
        }

        cons_center(-8 / 2, 4);
        textcolor(WHITE);
        textbackground(BLACK);
        printf("Cows:  %d", cows);

        cons_center(-8 / 2, 5);
        printf("Bulls: %d", bulls);

        Sleep(800);
    }
}

int main()
{
    SetConsoleTitle("Bulls and Cows");

    setwindow(80, 30);
    SMALL_RECT window;
    COORD windowSize;
    getwindow(&window, &windowSize);
    wndCenterX = windowSize.X / 2, wndCenterY = windowSize.Y / 2;

    hidecursor();

    clrscr();

    cons_center(-16 / 2, 0);

    textattr(BROWN);
    printf("BULLS");
    textattr(WHITE);
    printf(" and ");
    textattr(YELLOW);
    printf("COWS");

    //Sleep(1200);
    pause();

    clrscr();

    cons_center(-32 / 2, 0);
    textattr(LIGHTGREEN);

    int n;
    printf("Guess a number in range [2; 5]:\n");

    cons_center(-1 / 2, 2);
    textcolor(BLUE);
    textbackground(YELLOW);
    printf(" ");
    cons_center(-1 / 2, 2);
    scanf_s(" %d", &n);

    clrscr();

    srand(time(0));
    play_game(n);

    pause();
}