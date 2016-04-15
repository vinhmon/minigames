#include <stdio.h>
#include <stdlib.h>	// Library for rand() and srand().
#include <time.h>	// Library for time().
#include "Gm.h"
#include "Cg.h"
#include "Nim.h"

// The main user interaction function (conversation).
// ALine count = 6
void GM_conv(GM * rgm)
{
	GM_setup(rgm);	// Calls setup function to perform any needed internal setup for class.
	GM_hello(rgm);	// Calls hello function to announce class to the user.
	do
	{
		GM_listen(rgm);	// Calls listen function to ask/get user input
		GM_respond(rgm);	// Calls respond function to process user input.
	} while (0 != GM_endcheck(rgm));	// Jump to beginning of Do loop until user input is "0: Quit".
	GM_cleanup(rgm);	// Calls cleanup function to perform any needed internal shutdown for the class.
}

// Performs any needed internal setup for class.
// ALine = 1
void GM_setup(GM * rgm)
{
	printf("GM_setup stub called.\n");
	srand (time(NULL));	// Generates new seed.
}

// Announces the class to the user.
// ALine count = 0
void GM_hello(GM * rgm)
{
	printf("Hello! This is the Game Manager (GM) class.\n");
}

// Asks/gets the user input.
// Touches: m_data
// ALine count = 6
void GM_listen(GM * rgm)
{
	char line[5];	// Character array for user input.

	GM_printmenu(rgm);	// Calls the function printmenu to print text menu.

	do
	{
		fgets(line, sizeof(line), stdin);	// Get user input from stream and save to character array.
		if ('\0' != line[2])
		{
			printf("Please choose valid option: ");
		}
	} while ('\0' != line[2]);	// Loop until user input is 1 character.

	sscanf(line, "%d", &(rgm->m_data));	// Save user input to Game Manager int slot.
}

// Does the needed processing for user input.
// ALine count = 8
void GM_respond(GM * rgm)
{
	int user_input = GM_endcheck(rgm);	// Initialize user input for expression in switch statement.

	switch(user_input)
	{
	case 1:	// For Guess-a-Card game.
		{
			GC gcx;	// Creates a Guess-a-Card object.
			GC_conv(&gcx);	// Address of object gcx passed to Guess-a-Card conversation function.
			break;
		}
	case 2:	// For Nim game.
		{
			NIM nx; // Creates a Nim object.
			NIM_conv(&nx);	// Address of object nx passed to Nim conversation function.
			break;
		}
	case 0:	// For quitting.
		{
			printf("\nThanks for playing.\n\n");
			break;
		}
	default:	// For illegal user input.
		{
			printf("Please choose valid option.\n");
			break;
		}
	}
}

// Checks whether the user is done.
// Touches: m_data
// Return: User input in Game Manager int slot.
// ALine count = 1
int GM_endcheck(GM * rgm)
{
	return rgm->m_data;	// Returns user input from the Game Manager int slot.
}

// Performs any needed internal shutdown for the class.
// ALine count = 0
void GM_cleanup(GM * rgm)
{
	printf("GM_cleanup stub called.\n");
}

// Outputs text menu containing game options and quit option.
// ALine count = 0
void GM_printmenu(GM * rgm)
{
	printf("\nPlease make your selection.\n");
	printf("  1: Guess-a-Card Game\n");
	printf("  2: Nim Game\n");
	printf("  0: Quit\n");
}