#ifndef _MAP_DATA_H_
#define _MAP_DATA_H_

// define the type of pointer on member function of Item, for callback purpose
typedef void (*ItemInitFunction)(bool init);

namespace MapManager
{
	// size of the level
	static constexpr int LEVEL_SIZE_X = 32;
	static constexpr int LEVEL_SIZE_Y = 16;
	
	// all the map sprite ids of the full level
	extern const unsigned char Level[LEVEL_SIZE_Y][LEVEL_SIZE_X];
	
	// all the function to init the items in the level split per puzzle screen
	extern ItemInitFunction ItemInitFunctions[];
	extern const unsigned char PUZZLE_SCREEN_COUNT;
};

#endif