#ifndef _GC_H_
#define _GC_H_

// Structure/Pseudo-Class for Guess-a-Card.
typedef struct tGc
{
	int m_exit;	// Slot for exit-game flag.
	char m_guess[10];	// Character array to to hold user's 2 character guess input.
	int m_iguess;	// Integer value for user's guess input.
	int m_secret;	// Random secret card value generated by the program.
	int m_delta;	// Positive distance from user's guess input to the secret card.
} GC;	// Define GC for Guess-a-Card structure (tGc).

// Function prototypes for Guess-a-Card.
void GC_conv(GC *);	// The main interaction function that Game Manager calls.
void GC_setup(GC *);	// Function to pick a random card between 1-52.
void GC_hello(GC *);	// Announces the class to the user.
void GC_listen(GC *);	// Asks/gets the user input for card.
void GC_respond(GC *);	// Function to calculate the positive distance from user's guess input to the secret card.
int GC_endcheck(GC *);	// Checks whether the user is done.
void GC_cleanup(GC *);	// Performs any needed internal shutdown for the class.
void GC_cvt_card_to_int(GC *);	// Converts user's card string to an integer value.
void GC_cvt_suit_to_int(GC *);	// Converts user's card suit to an integer value.

#endif