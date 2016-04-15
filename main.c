#include <stdio.h>
#include "Gm.h"

// Main program.
// Creates Game Manager object and calls GM_conv(GM *) with a pointer to Game Manager structure.
// Aline count = 3
int main()
{
	GM gmx;	// Creates a Game Manager object.
	GM_conv(&gmx);	// Address of object gmx passed to Game Manager conversation function.

	return 0;
}