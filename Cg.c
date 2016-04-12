#include <stdio.h>
#include <stdlib.h>	// Library for rand() and srand().
#include "Cg.h"

// The main interaction function that Game Manager calls.
// ALine count = 6
void GC_conv(GC * rgc)
{
	GC_setup(rgc);	// Function to pick a random card between 1-52.
	GC_hello(rgc);	// Announces the class to the user.
	do
	{
		GC_listen(rgc);	// Asks/gets the user input for card.
		GC_respond(rgc);	// Calculates the positive distance
	} while (0 != GC_endcheck(rgc));	// Exit game if user correctly guesses the secret card.
	GC_cleanup(rgc);	// Performs any needed internal shutdown for the class.
}

// Function to pick a random card between 1-52.
// Touches: m_secret
// ALine count = 2
void GC_setup(GC * rgc)
{
	rgc->m_secret = rand() % 52 + 1;	// Set secret card with value between 1-52.
}

// Announces the class to the user.
// ALine count = 0
void GC_hello(GC * rgc)
{
	printf("\nHello! This is the Guess-a-Card (GC) class.\n");
}

// Asks/gets the user input for card.
// Touches: m_guess
// ALine count = 1
void GC_listen(GC * rgc)
{
	printf("\nGuess a card (e.g. 2C, AS, TD, (T for 10)): ");
	fgets(rgc->m_guess, sizeof(rgc->m_guess), stdin);	// Get user input from stream and save to character array.
}

// Function to calculate the positive distance from user's guess input to the secret card.
// Touches: m_delta, m_secret, m_iguess, m_exit
// ALine count = 6
void GC_respond(GC * rgc)
{
	GC_cvt_card_to_int(rgc);	// Convert user's card suit to an integer value.

	rgc->m_delta = (rgc->m_secret - rgc->m_iguess);	// Calculate distance from secret card.
	if (0 > rgc->m_delta)
	{
		rgc->m_delta *= -1;	// Make delta positive.
	}

	printf("The distance from your card to the secret card is: %d\n", rgc->m_delta);

	if (0 == rgc->m_delta)
	{
		printf("Correct! You found the secret card.\n\n");
		rgc->m_exit = 0;	// If distance is 0/secret card is guessed, set exit-flag to 0.
	}
}

// Checks whether the user is done.
// Touches: m_exit
// Return: Exit-flag in Guess-a-Card int slot.
// ALine count = 1
int GC_endcheck(GC * rgc)
{
	return rgc->m_exit;	// Return the integer from exit-flag slot.
}

// Performs any needed internal shutdown for the class.
// ALine count = 0
void GC_cleanup(GC * rgc)
{
	printf("Thanks for playing.\n");
}

// Converts user's card string to an integer value.
// Touches: m_guess, m_iguess
// ALine count = 10
void GC_cvt_card_to_int(GC * rgc)
{
	if ('\0' != rgc->m_guess[3]) rgc->m_iguess = 0;	// Set guess integer slot to 0 if input is more than 2 characters.
	else if ('2' <= rgc->m_guess[0] && '9' >= rgc->m_guess[0]) rgc->m_iguess = (rgc->m_guess[0] - '0') - 1;	// Integer value of rank subtracted by 1 to reflect the standard card ranking.
	else
	{
		switch(rgc->m_guess[0])	// User rank input set as the expression in the switch statement.
		{
		case 'T':	// For rank 10.
			{
				rgc->m_iguess = 10 - 1;	// Integer value of rank subtracted by 1 to reflect the standard card ranking.
				break;
			}
		case 'J':	// For rank J.
			{
				rgc->m_iguess = 11 - 1;	// Integer value of rank subtracted by 1 to reflect the standard card ranking.
				break;
			}
		case 'Q':	// For rank Q.
			{
				rgc->m_iguess = 12 - 1;	// Integer value of rank subtracted by 1 to reflect the standard card ranking.
				break;
			}
		case 'K':	// For rank K.
			{
				rgc->m_iguess = 13 - 1;	// Integer value of rank subtracted by 1 to reflect the standard card ranking.
				break;
			}
		case 'A':	// For rank A.
			{
				rgc->m_iguess = 14 - 1;	// Integer value of rank subtracted by 1 to reflect the standard card ranking.
				break;
			}
		default:	// For an illegal rank.
			{
				printf("Please input valid Rank (e.g. 2-9, T, J, Q, K, A).\n");
				rgc->m_iguess = 0;	// For all other cases, set guess integer slot to 0.
				break;
			}
		}
	}

	GC_cvt_suit_to_int(rgc);	// Convert user's card suit to an integer value.
}

// Convert user's card suit to an integer value.
// Touches: m_guess, m_iguess
// ALine count = 10
void GC_cvt_suit_to_int(GC * rgc)
{
	if ('\0' != rgc->m_guess[3]) rgc->m_iguess = 0;	// Set guess integer slot to 0 if input is more than 2 characters.
	else if (!('2' <= rgc->m_guess[0] && '9' >= rgc->m_guess[0]) && !('T' == rgc->m_guess[0] || 'J' == rgc->m_guess[0] || 'Q' == rgc->m_guess[0] || 'K' == rgc->m_guess[0] || 'A' == rgc->m_guess[0]))
	{
		rgc->m_iguess = 0;	// Set guess integer slot to 0 if rank input is invalid.
	}
	else
	{
		switch(rgc->m_guess[1])	// User suit input set as the expression in the switch statement.
		{
		case 'C':	// For suit Clubs.
			{
				rgc->m_iguess += 0 * 13;	// Add Club suit value to guess integer slot.
				break;
			}
		case 'D':	// For suit Diamonds.
			{
				rgc->m_iguess += 1 * 13;	// Add Diamond suit value to guess integer slot.
				break;
			}
		case 'H':	// For suit Hearts.
			{
				rgc->m_iguess += 2 * 13;	// Add Heart suit value to guess integer slot.
				break;
			}
		case 'S':	// For suit Spades.
			{
				rgc->m_iguess += 3 * 13;	// Add Spade suit value to guess integer slot.
				break;
			}
		default:	// For an illegal suit.
			{
				printf("Please input valid Suit (e.g. C, D, H, S).\n");
				rgc->m_iguess = 0;	// For all other cases, set guess integer slot to 0.
				break;
			}
		}
	}
}