#ifndef _MAP_DATA_H_
#define _MAP_DATA_H_

#include "Item.h"

namespace MapManager
{
	// all the map sprite ids of the full level
	extern const unsigned char Level[][32];
	
	// all the items in the level
	extern Item * Items[];
	extern const unsigned int ITEM_COUNT;
};

#endif