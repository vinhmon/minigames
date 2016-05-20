#include <stdio.h>
#include <stdlib.h>	// Library for rand() and srand().
#include "Room.h"

// Print room description.
// Touches: m_desc
// Aline count = 0
void Room_print_room(Room * rrm)
{
	printf("\nYou are in %s\n", rrm->m_desc);
}

// Randomly set 2-8 exit directions to other rooms.
// Touches: m_room_cnt, m_exits
// Aline count = 6
void Room_set_room_exits(Room * rrm, int room_cnt)
{
	int i, j;
	int exit_cnt;	// Counter to make sure that there are at least 2 exits and at most 8 exits.
	
	for (i = 0; i < KEXITS; i++)
	{
		rrm->m_exits[i] = 0;	// Initialize m_exit array values to 0.
	}

	exit_cnt = rand() % 7 + 2;	// Select random number of exits between 2-8 for room.

	for (j = 0; j < exit_cnt; j++)	// Loop through randomly selected exit count.
	{
		int random_dir = rand() % KEXITS;	// Randomly select an exit direction.
		rrm->m_exits[random_dir] = rand() % room_cnt + 1;	// Set the exit to connect to a random room.
	}
}

// Print the available exit options for the room.
// Touches: m_exits
// Aline count = 3
void Room_print_options(Room * rrm)
{
	int i;
	printf("The available exits are: ");

	for (i = 0; i < KEXITS; i++)
	{
		if (0 != rrm->m_exits[i])	// Print only the exits that lead to another room.
		{
			Room_print_directions(i);	// Call function to print direction names.
		}
	}
}

// Print the direction names.
// Aline count = 10
void Room_print_directions(int dir_index)
{
	switch(dir_index)	// Direction index set as the expression in the switch statement.
		{
		case 0:	// For index 0.
			{
				printf("\n(%d) north", dir_index);
				break;
			}
		case 1:	// For index 1.
			{
				printf("\n(%d) northeast", dir_index);
				break;
			}
		case 2:	// For index 2.
			{
				printf("\n(%d) east", dir_index);
				break;
			}
		case 3:	// For index 3.
			{
				printf("\n(%d) southeast", dir_index);
				break;
			}
		case 4:	// For index 4.
			{
				printf("\n(%d) south", dir_index);
				break;
			}
		case 5:	// For index 5.
			{
				printf("\n(%d) southwest", dir_index);
				break;
			}
		case 6:	// For index 6.
			{
				printf("\n(%d) west", dir_index);
				break;
			}
		case 7:	// For index 7.
			{
				printf("\n(%d) northwest", dir_index);
				break;
			}
		case 8:	// For index 8.
			{
				printf("\n(%d) upwards by a rope ladder", dir_index);
				break;
			}
		case 9:	// For index 9.
			{
				printf("\n(%d) downwards by a sliding chute", dir_index);
				break;
			}
		default:
			{
				break;
			}
		}
}