#include "main.h"
#include "navigation.h"
#include "addfunc.h"
#include "mode.h"

// An array of function pointers to implement navigation
void (*navigation_functions[COUNT_OF_NAVIGATION_FUNCTIONS]) (void) = { program_exit, program_info, working_with_functions, joke_minute };

// Main menu of the program
void main_menu()
{
	char act = '-';
	printf("What you want to do?\n\n");
	printf("1 - view information about the program\n");
	printf("2 - go to work with functions\n");
	printf("3 - watch a joke (not funny again)\n\n");
	printf("0 - exit the program\n");

	while ((act != '0') && (act != '1') && (act != '2') && (act != '3'))
	{
		printf("\nSelect one of the items: ");

		act = getchar();
		clean_stdin();

		int res_act = act - '0';
		if (res_act != 0 && res_act != 1 && res_act != 2 && res_act != 3)
		{
			printf("\nAnd what did you mean by that?\nCheck the entered data and try again!\n");
			continue;
		}
		else
			navigation_functions[res_act]();
	}
}

// Procedure to return to the main menu
void return_to_main_menu()
{
	printf("\n\nEnter any character to return to the menu: ");
	getchar();
	clean_stdin();
	system("cls");
	main_menu();
}

// Procedure for displaying program information
void program_info()
{
	system("cls");
	printf("As mentioned in the introduction, this program uses the Taylor expansion of functions to calculate their values.\n");
	printf("The program has two operating modes:\n\n");
	printf("MODE 1: single calculation of the function value at a given point;\n");
	printf("MODE 2: serial experiment (table in the terminal);\n");
	printf("\nNow try to work with them!\n");
	return_to_main_menu();
}

// Anecdote for the user
void joke_minute()
{
	system("cls");
	printf("\"There are 10 kinds of people in the world: Those who know binary and those who don't.\"\n");
	return_to_main_menu();
}

// Variable for mode selection (used in mode.c)
char mode;

// Procedure for switching from the main menu to working with functions
void working_with_functions()
{
	char cont_working;
	do
	{
		system("cls");
		mode = '-';
		while (mode != '1' && mode != '2')
		{
			printf("Choose an operating mode:\n");
			printf("\nMODE 1: single calculation\n");
			printf("MODE 2: serial experiment\n");
			printf("\nChoose one of the items: ");

			mode = getchar();
			clean_stdin();

			if (mode != '1' && mode != '2')
			{
				printf("\nAnd what did you mean by that?\nCheck the entered data and try again!\n");
				continue;
			}
		}
		operating_mode();

		printf("\nDo you want to continue calculating function values?\n");
		printf("If yes, enter '1'. To exit the function calculation mode, enter any other character: ");

		cont_working = getchar();
		clean_stdin();
	} while (cont_working == '1');

	return_to_main_menu();
}

// Exit the program at the user's request
void program_exit()
{
	system("cls");
	printf("Thank you for using this program\nCome again :)\n");
	system("pause");
	exit(EXIT_SUCCESS);
}