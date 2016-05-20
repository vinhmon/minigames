#include <stdio.h>
#include <stdlib.h>	// Library for malloc, rand(), and srand().
#include <assert.h>	// Library for assert.
#include "Mh.h"

// The main interaction function that Mystery House calls.
// ALine count = 6
void MH_conv(MH * rmh)
{
	MH_setup(rmh);	// Performs any needed internal setup for class.
	MH_hello(rmh);	// Announces the class to the user.
	do
	{
		MH_listen(rmh);	// Asks/gets the user input for direction.
		MH_respond(rmh);	// Moves the user to the next room.
	} while (0 != MH_endcheck(rmh));	// Exit game if user finds the outside or get killed by zombie.
	MH_cleanup(rmh);	// Performs any needed internal shutdown for the class.
}

// Performs any needed internal setup for class.
// Touches: m_room_cnt, m_rooms, m_outside, m_current_room
// ALine count = 9
void MH_setup(MH * rmh)
{
	int i;

	printf("Reading rooms from text file.\n");
	MH_read_room(rmh);	// Call function to read in rooms from text file.

	for (i = 0; i < rmh->m_room_cnt; i++)	// Loop through all the rooms.
	{
		Room_set_room_exits(rmh->m_rooms[i], rmh->m_room_cnt);	// Call function to set exit directions for each room.
	}

	rmh->m_outside = rand() % rmh->m_room_cnt;	// Set random room that leads to outside.

	do
	{
		rmh->m_current_room = rand() % rmh->m_room_cnt;	// Place the player into a random room.
	} while (rmh->m_current_room == rmh->m_outside);	// Loop until random room is not outside room.

	MH_set_zombies(rmh, &rmh->m_z1);	// Place zombie 1 into random room.
	MH_set_zombies(rmh, &rmh->m_z2);	// Place zombie 2 into random room.
	MH_set_zombies(rmh, &rmh->m_z3);	// Place zombie 3 into random room.
}

// Announces the class to the user.
// Aline count = 0
void MH_hello(MH * rmh)
{
	printf("\nHello! This is the Mystery House (MH) class.\n\n");
}

// Asks/gets the user input.
// Touches: m_current_room, m_outside, m_rooms, m_z1, m_z2, m_z3, m_choice
// ALine count = 9
void MH_listen(MH * rmh)
{
	int temp1 = rmh->m_current_room;	// Set temp variable to current room.
	int temp2 = rmh->m_outside;	// Set temp variable to outside room.

	temp1++, temp2++;	// Increment variables in order to output correct room numbers.

	Room_print_room(rmh->m_rooms[rmh->m_current_room]);	// Call function to print room description.

	MH_detect_outside(rmh);	// Call function to check if outside room is nearby.
	MH_detect_zombies(rmh, &rmh->m_z1);	// Call function to check if zombie 1 is nearby.
	MH_detect_zombies(rmh, &rmh->m_z2);	// Call function to check if zombie 2 is nearby.
	MH_detect_zombies(rmh, &rmh->m_z3);	// Call function to check if zombie 3 is nearby.

	Room_print_options(rmh->m_rooms[rmh->m_current_room]);	// Call function to print direction options for current room.

	do
	{
		printf("\nWhat next?> ");
		fgets(rmh->m_choice, sizeof(rmh->m_choice), stdin);	// Get user input from stream and save to character array.
	} while (0 == MH_is_valid_choice(rmh));	// Loop until user inputs a valid direction.
}

// Does the needed processing for user input.
// Touches: m_current_room, m_rooms, m_exits, m_choice, m_z1, m_z2, m_z3, m_qdone, m_outside
// ALine count = 9
void MH_respond(MH * rmh)
{
	rmh->m_current_room = rmh->m_rooms[rmh->m_current_room]->m_exits[rmh->m_choice[0] - '0'];	// Move the player to through the selected exit direction.
	rmh->m_current_room--;	// Decrement current room in order to match correct room index.


	if (rmh->m_current_room == rmh->m_z1 || rmh->m_current_room == rmh->m_z2 || rmh->m_current_room == rmh->m_z3)	// If player enters room containing a zombie.
	{
		printf("You lose, Zombie encountered.\n");
		rmh->m_qdone = 0;	// Set exit-flag to 0.
	}

	if (rmh->m_current_room == rmh->m_outside)	// If player enters room containing the exit to outside.
	{
		printf("Congratulations, you have found the room with the exit to outside!\n");
		rmh->m_qdone = 0;	// Set exit-flag to 0.
	}

	MH_set_zombies(rmh, &rmh->m_z1);	// Move zombie 1 into random room.
	MH_set_zombies(rmh, &rmh->m_z2);	// Move zombie 2 into random room.
	MH_set_zombies(rmh, &rmh->m_z3);	// Move zombie 3 into random room.
}

// Checks whether the user is done.
// Touches: m_qdone
// Return: Exit-flag in Mystery House int slot.
// ALine count = 1
int MH_endcheck(MH * rmh)
{
	return rmh->m_qdone;	// Return exit-flag.
}

// Performs any needed internal shutdown for the class.
// Touches: m_room_cnt, m_rooms
// ALine count = 2
void MH_cleanup(MH * rmh)
{
	int i;

	for (i = 0; i < rmh->m_room_cnt; i++)	// Loop through all the rooms.
	{
		free(rmh->m_rooms[i]);	// Release malloc'd room pointers.
		rmh->m_rooms[i] = 0;
	}
}

// Malloc room from title and description read from text file.
// Touches: m_room_cnt, m_title, m_desc, m_rooms
// Aline count = 13
void MH_read_room(MH * rmh)
{
	int i;
	char line[KMAXDESC];	// Character array to store line from text file.
	FILE * pfin  = fopen("house.txt", "r");	// Open text file for reading.

	do
	{
		if (!pfin)	// If file was not opened.
		{
			printf("Unable to open house text file for read.\n");
			break;
		}

		fgets(line, sizeof(line), pfin);	// Read first line containing count in text file.
		sscanf(line, "Count: %d", &rmh->m_room_cnt);	// Save read line into count int slot.

		for (i = 0; i < rmh->m_room_cnt; i++)	// Read line in text file until room count.
		{
			pRoom px = (Room *) malloc(sizeof(Room));	// Allocate heap space for room.
			assert(px);	// Assertion failure if unable to malloc.

			fgets(line, sizeof(line), pfin);	// Read line containing room title in text file.
			sscanf(line, "Room: %s", px->m_title);	// Save read line into title slot.

			fgets(line, sizeof(line), pfin);	// Read line containing room description in text file.
			sscanf(line, "%[^\n]s", px->m_desc);	// Save read line into description slot.

			rmh->m_rooms[i] = px;	// Add malloc'd room to pRoom array.
		}
		fclose(pfin);	// Close the file that was opened.
	} while(0);	// Loop once.
}

// Checks if user input is valid.
// Touches: m_rooms, m_current_room, m_exits, m_choice
// Aline count = 5
int MH_is_valid_choice(MH * rmh)
{
	int i;

	for (i = 0; i < KEXITS; i++)	// Loop through all exits in current room.
	{
		if (0 != rmh->m_rooms[rmh->m_current_room]->m_exits[i])	// If the exit leads to another room.
		{
			if (i == (rmh->m_choice[0] - '0'))	// If the user selected this exit option.
			{
				return 1;	// Return 1
			}
		}
	}

	printf("Please select a valid direction.\n");

	return 0;	// If the user did not select a valid exit option, return 0.
}

// Randomly place zombies into rooms.
// Touches: m_room_cnt, m_z1, m_z2, m_z3, m_outside, m_current_room
// Aline count = 2
void MH_set_zombies(MH * rmh, int * zombie)
{
	do
	{
		(*zombie) = rand() % rmh->m_room_cnt;	// Select a random room for the zombie.
	} while (*zombie == rmh->m_outside || *zombie == rmh->m_current_room);	// Loop until zombie is not in player's room or outside room.
}

// Check if outside room is nearby.
// Touches: m_outside, m_rooms, m_current_room, m_exits
// Aline count = 4
void MH_detect_outside(MH * rmh)
{
	int j;
	int temp = rmh->m_outside;	// Set temp variable to outside room.

	temp++;	// Increment variable in order to compare correct room.

	for (j = 0; j < KEXITS; j++)	// Loop through all the rooms.
	{
		if (temp == rmh->m_rooms[rmh->m_current_room]->m_exits[j])	// If exit to outside room is nearby ouput notification.
		{
			printf(" [You hear birds chirping.]\n");
			break;
		}
	}
}

// Check if a zombie is nearby.
// Touches: m_z1, m_z2, m_z3
// Aline count = 4
void MH_detect_zombies(MH * rmh, int * zombie)
{
	int j;
	int temp = *zombie;	// Set temp variable to zombie.

	temp++;	// Increment variable in order to compare correct room.

	for (j = 0; j < KEXITS; j++)	// Loop through all the rooms.
	{
		if (temp == rmh->m_rooms[rmh->m_current_room]->m_exits[j])// If exit to zombie room is nearby ouput notification.
		{
			printf(" [You hear a shuffling sound.]\n");
			break;
		}
	}
}