#ifndef _MH_H_
#define _MH_H_

#define KMAXROOMS		100	// Maximum number of rooms.

#include "Room.h"

// Structure/Pseudo-Class for Mystery House.
typedef struct tMh
{
	pRoom m_rooms[KMAXROOMS];	// pRoom array of rooms.
	int m_room_cnt;	// Number of rooms in the house.
	int m_current_room;	// Integer to keep track of current room in the house.
	int m_outside;	// Room that leads to the outside.
	char m_choice[5];	// User's direction choice.
	int m_qdone;	// Slot for exit-game flag.
	int m_z1, m_z2, m_z3;	// Intergers that keep track of zombie locations in the house.
} MH;	// Define MH for Mystery House structure (tMh).

// Function prototypes for Mystery House.
void MH_conv(MH *);	// The main user interaction function (conversation).
void MH_setup(MH *);	// Performs any needed internal setup for class.
void MH_hello(MH *);	// Announces the class to the user.
void MH_listen(MH *);	// Asks/gets the user input.
void MH_respond(MH *);	// Does the needed processing for user input.
int MH_endcheck(MH *);	// Checks whether the user is done.
void MH_cleanup(MH *);	// Performs any needed internal shutdown for the class.

void MH_read_room(MH *);	// Malloc room from title and description read from text file.
int MH_is_valid_choice(MH *);	// Checks if user input is valid.
void MH_set_zombies(MH *, int *);	// Randomly place zombies into rooms.
void MH_detect_outside(MH *);	// Check if outside room is nearby.
void MH_detect_zombies(MH *, int *);	// Check if a zombie is nearby.

#endif