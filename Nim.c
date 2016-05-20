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
// Touches: m_record, m_rowcnt, m_rows, m_user_name
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
	
	printf("Please enter your name: ");
	fgets(rnim->m_user_name, sizeof(rnim->m_user_name), stdin);	// Get user input from stream and save to character array.

	NIM_read_score(rnim);	// Call read text file function.
}

// Announces the class to the user and rules of the game.
// Aline count = 1
void NIM_hello(NIM * rnim)
{
	printf("\nHello! This is the Nim (NIM) class.\n");
	printf("In order to win, be the last player to remove all the pebbles from the last non-empty row.\n");
	printf("You can only remove pebbles from one row each turn.\n");
	printf("Select the row and pebble count by input of \"row_pebblecount\".\n\n");

	NIM_print_board(rnim);	// Call print function to print updated board.
}

// Asks/gets the user/brain input.
// Touches: m_record, m_row_select, m_pebble_select
// Aline count = 8
void NIM_listen(NIM * rnim)
{
	char line[10];	// Character array for user input.
	rnim->m_record++;	// Increment m_record by 1.  Even integer is brain and odd integer is user.

	if (0 == rnim->m_record % 2)	// Modulus m_record to test if equal to 0.
	{
		NIM_brain_moves(rnim);	// Call function to handle brain move.
	}
	else  // User's turn.
	{
		do
		{
			printf("\nPlease select row and pebble count to be removed: ");
			fgets(line, sizeof(line), stdin);	// Get user input from stream and save to character array.
			sscanf(line, "%d %d", &rnim->m_row_select, &rnim->m_pebble_select);	// Save user input to Nim row and pebble slot.

			if (1 != NIM_is_valid_move(rnim))	// If the inputted selection is invalid.
			{
				printf("Please select non-empty row and a positive count!\n");
			}
		} while (0 == NIM_is_valid_move(rnim));	// Loop until inputted selection is valid.

		printf("You take %d pebbles from row %d\n", rnim->m_pebble_select, rnim->m_row_select);
	}
}

// Does the needed processing for user/brain input.
// Touches: m_pebble_select, m_rows, m_row_select
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
// Returns: Exit-flag in Nim int slot.
// Aline count = 1
int NIM_endcheck(NIM * rnim)
{
	return rnim->m_exit;	// Return the integer from exit-flag slot.
}

// Performs any needed internal shutdown for the class.
// Touches: m_record
// ALine count = 3
void NIM_cleanup(NIM * rnim)
{
	if (0 != rnim->m_record % 2)	// Modulus m_record to test if equal to 0.
	{
		printf("Game has ended in %d rounds, You Win!\n", rnim->m_record);	// Print user as winner with round count.
		NIM_write_score(rnim);	// Writes their score and name to text file.
	}
	else
	{
		printf("Game has ended in %d rounds, Brain Wins!\n", rnim->m_record);	// Print brain as winner with round count.
	}
}

// Displays the updated board.
// Touches: m_rowcnt, m_rows
// Aline count = 2
void NIM_print_board(NIM * rnim)
{
	int i;	// For loop counter.

	for (i = 0; i < rnim->m_rowcnt; i++)	// Loop through all the rows.
	{
		printf("  %d: %.*s\n", i, rnim->m_rows[i], "oooooooo");	// Print "o" according to pebble count of each row.
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
// Aline count = 5
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

// Write the user's score and name to text file.
// Touches: m_record, m_user_name
// Aline count = 8
void NIM_write_score(NIM * rnim)
{
	FILE *pfout = fopen("Nim-scores.txt", "a");	// Opens the text file in append mode.

	do
	{
		if (!pfout)	// If file was not opened.
		{
			printf("Cannot open file.\n");
			break;
		}

		fprintf(pfout, "%d %s", rnim->m_record, rnim->m_user_name);	// Write user's name and score to text file.

		fclose(pfout);	// Close the file that was opened.
	} while(0);	// Loop once.

	if (pfout) printf("Score has been written to file.\n");
	else printf("Was unable to write score to file.\n");
}

// Read text file and save the user's name with best score.
// Touches: m_file_score, m_file_name
// Aline count = 10
void NIM_read_score(NIM * rnim)
{
	FILE *pfin = fopen("Nim-scores.txt", "r");	// Opens the text file in read mode.
	char line[101];	// Character array to store line from text file.
	int temp_score = 0;	// Temporary variable to hold score.
	char temp_name[KMAXSIZE];	// Temporary variable to hold user name.
	rnim->m_file_score = 50;	// Initialize score to 50.

	do
	{
		if (!pfin)	// If file was not opened.
		{
			printf("No scores file to read.\n");
			break;
		}

		while(fgets(line, sizeof(line), pfin))	// Read line in text file until EOF.
		{
			sscanf(line, "%d %s", &temp_score, temp_name);	// Save read line into temp variables.
			if (temp_score < rnim->m_file_score)	// If read score is smaller than current best saved score.
			{
				rnim->m_file_score = temp_score;	// Update saved score to new best score.
				sscanf(temp_name, "%s", rnim->m_file_name);	// Update saved user name to new user's name with best score.
			}
		}

		printf("\nCurrently the best score is %d achieved by %s.\n", rnim->m_file_score, rnim->m_file_name);

		fclose(pfin);	// Close the file that was opened.
	} while(0);	// Loop once
}