#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

    // Debug has been added for easy checking of the program's operability and can be removed
    printf(" (DEBUG: I've guessed number ");
    for (i = n - 1; i >= 0; i--)
    {
        printf("%d", seed[i]);
    }
    printf(")\n");
    //////////////////////////////////////////////////////////////////////////

    int ans;
    int attempts = 0;
    int cows, bulls;

    int guess_digit, ans_digit;
    while (1)
    {
        attempts++;

        printf("Your attempt: ");
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
            printf("You've won in %d attempts!\n", attempts);
            break;
        }

        printf(" -> Cows: %d\n -> Bulls: %d\n", cows, bulls);
    }
}

int main()
{
    printf(" ===> Bulls and Cows <===\n\n");

    int n;
    printf("Guess a number in range [2; 5]: ");
    scanf_s("%d", &n);

    srand(time(0));
    play_game(n);

    system("PAUSE");
}