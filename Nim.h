#ifndef _NIM_H_
#define _NIM_H_

#define KMAXSIZE		15	// Maximum string length for file read/write.
#define KMAXROWS		5	// Maximum number of rows.

// Structure/Pseudo-Class for Nim.
typedef struct tNim
{
	int m_rowcnt;	// Number of rows that Nim selected.
	int m_rows[KMAXROWS];	// Data structure array of ints to represent board.
	int m_row_select;	// User/brain selection of row.
	int m_pebble_select;	// User/brain selection of pebbles.
	int m_pebble_sum;	// The calculated sum of all pebbles on the board.
	int m_exit;	// Slot for exit-game flag.
	int m_record;	// Odd integer records user as playing, even integer records brain as playing.
	char m_user_name[KMAXSIZE];	// Array to hold user's name for file writing.
	char m_file_name[KMAXSIZE];	// Array to hold user's name with best score.
	int m_file_score;	// The best integer score from text file.
} NIM;	// Define NIM for Nim structure (tNim).

// Function prototypes for Nim.
void NIM_conv(NIM *);	// The main user interaction function (conversation).
void NIM_setup(NIM *);	// Performs any needed internal setup for class.
void NIM_hello(NIM *);	// Announces the class to the user and rules of the game.
void NIM_listen(NIM *);	// Asks/gets the user/brain input.
void NIM_respond(NIM *);	// Does the needed processing for user/brain input.
int NIM_endcheck(NIM *);	// Checks whether the user is done.
void NIM_cleanup(NIM *);	// Performs any needed internal shutdown for the class.
void NIM_print_board(NIM *);	// Displays the updated board.
int NIM_is_valid_move(NIM *);	// Checks to see if user/brain selected row and pebble count is valid.
void NIM_brain_moves(NIM *);	// Brain selects random row and random pebble count.
void NIM_calc_sum(NIM *);	// Calculates the total sum of pebbles remaining on the board.
void NIM_write_score(NIM *);	// Write the user's score and name to text file.
void NIM_read_score(NIM *);	// Read text file and save the user's name with best score.

#endif