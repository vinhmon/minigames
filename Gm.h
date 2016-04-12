#ifndef _GM_H_
#define _GM_H_

// Structure/Pseudo-Class for Game Manager.
typedef struct tGM
{
	int m_data;	// User choice saved to GM int slot.
} GM;	// Define GM for Game Manager structure (tGM).

// Function prototypes for Game Manager.
void GM_conv(GM *);	// The main user interaction function (conversation).
void GM_setup(GM *);	// Performs any needed internal setup for class.
void GM_hello(GM *);	// Announces the class to the user.
void GM_listen(GM *);	// Asks/gets the user input.
void GM_respond(GM *);	// Does the needed processing for user input.
int GM_endcheck(GM *);	// Checks whether the user is done.
void GM_cleanup(GM *);	// Performs any needed internal shutdown for the class.
void GM_printmenu(GM *);	// Outputs text menu containing game options and the quit option.

#endif