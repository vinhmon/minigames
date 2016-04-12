#include <stdio.h>
#include <stdlib.h>	// Library for rand() and srand().
#include "Nim.h"

// The main user interaction function (conversation).
// Aline count = 6
void NIM_conv(NIM * rnim)
{
	NIM_setup(rnim);	// Performs any needed internal setup for class.
	NIM_hello(rnim);	// Announces the class to the user and rules of the game.
	do
	{
		NIM_listen(rnim);	// Asks/gets the user/brain input.
		NIM_respond(rnim);	// Does the needed processing for user/brain input.
	} while (0 != NIM_endcheck(rnim));	// Exit game if no more pebbles on the board.
	NIM_cleanup(rnim);	// Performs any needed internal shutdown for the class.
}

// Performs any needed internal setup for class.
// Touches: m_record, m_rowcnt, m_rows
// Aline count = 5
void NIM_setup(NIM * rnim)
{
	int i;	// For loop counter.
	rnim->m_record = 0;	// Initialize user/brain tracker to 0.

	rnim->m_rowcnt = rand() % 3 + 3;	// Randomly set number of rows (3-5).
	for (i = 0; i < rnim->m_rowcnt; i++)	// Loop to set pebble count (2-8) for each row.
	{
		rnim->m_rows[i] = rand() % 7 + 2;	// Randomly set pebble count for row.
	}
}

// Announces the class to the user and rules of the game.
// Aline count = 1
void NIM_hello(NIM * rnim)
{
	NIM_print_board(rnim);	// Call print function to print updated board.

	printf("\nHello! This is the Nim(NIM) class.\n");
	printf("In order to win, be the last player to remove all the pebbles from the last non-empty row.\n");
	printf("You can only remove pebbles for one row each turn\n");
	printf("Select the row and pebble count by input of \"row_pebblecount\"\n\n");
}

// Asks/gets the user/brain input.
// Touches: m_record, m_row_select, m_pebble_select
// Aline count = 10
void NIM_listen(NIM * rnim)
{
	char line[10];	// Character array for user input.
	int ax;	// Variable specifying user or brain for switch statement.

	rnim->m_record++;	// Increment m_record by 1.  Even integer is brain and odd integer is user.
	ax = rnim->m_record % 2;	// Modulus m_record to test if ax is 0.

	switch (ax)
	{
	case 0:	// For brain's turn.
		{
				NIM_brain_moves(rnim);	// Call function to handle brain move.
		break;
		}
	default:	// For user's turn.
		{
			do
			{
				printf("\nPlease select row and pebble count to be removed: ");
				fgets(line, sizeof(line), stdin);	// Get user input from stream and save to character array.
				sscanf_s(line, "%d %d", &rnim->m_row_select, &rnim->m_pebble_select);	// Save user input to Nim row and pebble slot.

				if (1 != NIM_is_valid_move(rnim))	// If the inputted selection is invalid.
				{
					printf("Please select non-empty row and a positive count!\n");
				}
			} while (0 == NIM_is_valid_move(rnim));	// Loop until inputted selection is valid.

			printf("You take %d pebbles from row %d\n", rnim->m_pebble_select, rnim->m_row_select);
			break;
		}
	}
}

// Does the needed processing for user/brain input.
// Touches: m_pebble_sum, m_pebble_select, m_rows, m_row_select
// Aline count = 4
void NIM_respond(NIM * rnim)
{
	if (rnim->m_pebble_select > rnim->m_rows[rnim->m_row_select])	// If the inputted pebble count is larger than pebble count in row.
	{
		rnim->m_rows[rnim->m_row_select] = 0;	// Remove all pebbles in row.
	}
	else
	{
		rnim->m_rows[rnim->m_row_select] -= rnim->m_pebble_select;	// Subtract inputted pebble count from row's pebble count.
	}

	NIM_calc_sum(rnim);	// Call function to calculate total pebble count left on board.
}

// Checks whether the user is done.
// Touches: m_exit
// Aline count = 1
int NIM_endcheck(NIM * rnim)
{
	return rnim->m_exit;	// Return the integer from exit-flag slot.
}

// Performs any needed internal shutdown for the class.
// ALine count = 3
void NIM_cleanup(NIM * rnim)
{
	if (0 != rnim->m_record % 2)
	{
		printf("Game has ended in %d rounds, You Win!\n", rnim->m_record);	// Print user as winner with round count.
	}
	else
	{
		printf("Game has ended in %d rounds, Brain Wins!\n", rnim->m_record);	// Print brain as winner with round count.
	}

}

// Displays the updated board.
// Touches: m_rowcnt, m_rows
// Aline count = 3
void NIM_print_board(NIM * rnim)
{
	int i;	// For loop counter.

	for (i = 0; i < rnim->m_rowcnt; i++)	// Loop through all the rows.
	{
		printf("  %d: %.*s\n", i, rnim->m_rows[i], "oooooooo");	// Print "o" according to pebble count for each row.
	}
}

// Checks to see if user/brain selected row and pebble count is valid.
// Touches: m_rows, m_row_select, m_pebble_select
// Aline count = 5
int NIM_is_valid_move(NIM * rnim)
{
	if (0 == rnim->m_rows[rnim->m_row_select])	// Checks for non-empty row selection.
		return 0;	// Returns 0 if selection is invalid.
	else if (0 >= rnim->m_pebble_select)	// Checks for valid pebble count selection.
		return 0;	// Returns 0 if selection is invalid.
	else
		return 1;	// Returns 1 if selection is valid.
}

// Brain selects random row and random pebble count.
// Touches:m_row_select, m_rowcnt, m_pebble_select
// Aline count = 3
void NIM_brain_moves(NIM * rnim)
{
	printf("\nBrain's turn to select row and pebble count to be removed: \n");
	do
	{
		rnim->m_row_select = rand() % rnim->m_rowcnt;	// Randomly select a row.
		rnim->m_pebble_select = rand() % 8 + 1;	// Randomly select a pebble count (1-8) to remove.
	} while (0 == NIM_is_valid_move(rnim));	// Loop until valid selections for row and count are made.

	printf("I take %d pebbles from row %d\n", rnim->m_pebble_select, rnim->m_row_select);
}

// Calculates the total sum of pebbles remaining on the board.
// Touches: m_rowcnt, m_pebble_sum, m_rows, m_record, m_exit
// Aline count = 7
void NIM_calc_sum(NIM * rnim)
{
	int i;	// For loop counter.
	rnim->m_pebble_sum = 0;	// Initialize pebble sum to 0.

	NIM_print_board(rnim);	// Call print function to print updated board.

	for (i = 0; i < rnim->m_rowcnt; i++)	// Loop through all the rows.
	{
		rnim->m_pebble_sum += rnim->m_rows[i];	// Accumulate the pebble count of each row.
	}

	if (0 == rnim->m_pebble_sum)	// If the pebble count sum is 0.
	{
		rnim->m_exit = 0;	// Set exit-flag to 0.
	}
}