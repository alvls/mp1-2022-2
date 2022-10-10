#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define DIGITS 10

// Function to clear the input sream
void clean_stdin()
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c!=EOF);
}

// Function to generate a random digit
int generate_random_digit()
{
    return rand() % DIGITS;
}

// Function to generate a number with non-repeating digits of a given lenth
int generate_hidden_number(int n)
{
    int number_result = 0;
    int digits_of_the_hidden_number[n];
    int used_digits_indicator[DIGITS] = {0};

    // Generating a number as an array
    for (int i = 0; i < n; i++)
    {
        do
            digits_of_the_hidden_number[i] = generate_random_digit();
        while ( (digits_of_the_hidden_number[0] == 0) || (used_digits_indicator[ digits_of_the_hidden_number[i] ] != 0) ) ;
        used_digits_indicator[ digits_of_the_hidden_number[i] ] = 1;
    }

    // Now let's convert our array to a number
    int number_rank = pow(10, n-1);
    for (int i = 0; i < n; i++)
    {
        if (digits_of_the_hidden_number[i] != 0)
            number_result += digits_of_the_hidden_number[i] * number_rank;
        number_rank /= 10;
    }
    return number_result;
}

void main()
{
    srand(time(NULL));

    char continue_game_condition;
    printf("Do you want to try your hand at \"Bulls and Cows\"?\nEnter any character to start the game. To leave the game, enter 'l': ");

    while (continue_game_condition = getchar() != 'l')
    {
        int n;
        printf("\nEnter the length of the hidden number (from 2 to 5): ");

        // Clearing the input stream
        clean_stdin();

        scanf("%d", &n);
        if ((n < 2) || (n > 5) )
            printf("The entered number is not the correct length. The game is over.\n\n");
        else
        {
            int guess_number;
            int hidden_number = generate_hidden_number(n);
            do
            {
                printf("Try to guess the number (Enter the number of the length you specified with non-repeating digits. If you want to give up, enter 0): ");
                scanf("%d", &guess_number);

                // The highlighted part of the code is needed in order to split the user's number into an array and check if the user entered it correctly
                // (whether digits are repeated in it)
                // ---------------------------------------------------------------------------------------------------------------------------------------
                int guess_number_digits[DIGITS] = {0};
                int guess_number_array[n];

                int temp_guess_number = guess_number;

                for (int i = n - 1; i >= 0; i--)
                {
                    guess_number_array[i] = temp_guess_number % 10;
                    guess_number_digits[ guess_number_array[i] ] += 1;
                    temp_guess_number /= 10;
                }

                // Checking if the digits of a number are repeated
                int flag = 0;
                for (int i = 0; i < DIGITS; i++)
                {
                    if (guess_number_digits[i] > 1)
                        flag = 1;
                }
                // ---------------------------------------------------------------------------------------------------------------------------------------

                if (guess_number == hidden_number)
                    printf("Absolutely right! You win!\n\n");
                else if (guess_number == 0)
                {
                    printf("The current game session has ended\n\n");
                    break;
                }
                else if ( ((guess_number / pow(10, n)) >= 1) || ( (guess_number / pow(10, n-1) ) < 1 ) )
                    printf("Check the required input format :)\n\n");
                else if (flag == 1)
                    printf("You have entered a number with repeated digits\n\n");
                else
                {
                    /*
                      Now we will convert the hidden number to an array and create a digit count array for it. We did the same above for the user number.
                      At the same time, we will reset the values of the guesses_number_digits array elements. In the future, this practice will come in handy so as not to confuse "cows" and "bulls"
                      (We will consider the digits of the hidden humber and the user's number only if they did not match in the assessment to the position (not "bull"). This practice is useful in order not to confuse "cows" and "bulls")
                    */
                    for (int i = 0; i < DIGITS; i++)
                        guess_number_digits[i] = 0;

                    int number_of_bulls = 0, number_of_cows = 0;
                    int hidden_number_digits[DIGITS] = {0};
                    int hidden_number_array[n];

                    int temp_hidden_number = hidden_number;
                    temp_guess_number = guess_number;
                    for (int i = n - 1; i >= 0; i--)
                    {
                        hidden_number_array[i] = temp_hidden_number % 10;
                        if (hidden_number_array[i] == guess_number_array[i])
                            number_of_bulls++;
                        else
                            hidden_number_digits[ hidden_number_array[i] ] = 1;
                            guess_number_digits[ guess_number_array[i] ] = 1;
                        temp_guess_number /= 10;
                        temp_hidden_number /= 10;
                    }

                    // Loop for counting "cows"
                    for (int i = 0; i < DIGITS; i++)
                    {
                        if ( (hidden_number_digits[i] == 1) && (hidden_number_digits[i] == guess_number_digits[i]) )
                            number_of_cows++;
                    }
                    printf("Number of bulls: %d, number of cows: %d\n\n", number_of_bulls, number_of_cows);
                }
            } while (guess_number != hidden_number);
        }
        printf("Maybe we can play again? (To leave the game, enter 'l', to continue playing, enter any other character): ");
        continue_game_condition = getchar();
    }
}
