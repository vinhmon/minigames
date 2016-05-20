#ifndef _ROOM_H_
#define _ROOM_H_

#define KMAXTITLE		50	// Maximum length for room title.
#define KMAXDESC		200	// Maximum length for room description.
#define KEXITS			10	// 10 exit directions.

typedef struct tRoom * pRoom;	// Pointer to tRoom struct.

// Structure/Pseudo-Class for Room.
typedef struct tRoom
{
	char m_title[KMAXTITLE];	// Character array for room title.
	char m_desc[KMAXDESC];	// Character array for room description.
	int m_exits[KEXITS];	// Integer array for exit direction to other rooms.
} Room;	// Define Room for Room structure (tRoom).

// Function prototypes for Room.
void Room_print_room(pRoom);	// Print room description.
void Room_set_room_exits(pRoom, int);	// Randomly set 2-8 exit directions to other rooms.
void Room_print_options(pRoom);	// Print the available exit options for the room.
void Room_print_directions(int);	// Print the direction names.

#endif