#ifndef _MAP_DATA_H_
#define _MAP_DATA_H_

#include "Item.h"

namespace MapManager
{
	// size of the level
	const int LEVEL_SIZE_X = 32;
	const int LEVEL_SIZE_Y = 16;
	
	// all the map sprite ids of the full level
	extern const unsigned char Level[LEVEL_SIZE_Y][LEVEL_SIZE_X];
	
	// all the items in the level
	extern Item * Items[];
	extern const unsigned int ITEM_COUNT;
};

#endif