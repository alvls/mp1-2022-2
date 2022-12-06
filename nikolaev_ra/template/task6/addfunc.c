#include "main.h"
#include "addfunc.h"

// Procedure for cleaning the input stream 
void clean_stdin()
{
	int c;
	do
		c = getchar();
	while (c != '\n' && c != EOF);
}

// Procedure for greeting the user
void user_greeting()
{
	printf("Hello!\nWelcome to the program for calculating the value of functions using their expansion in a Taylor series :)\n");
}

