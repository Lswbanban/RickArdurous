#ifndef _MAP_DATA_H_
#define _MAP_DATA_H_

// define the type of pointer on member function of Item, for callback purpose
typedef void (*ItemInitFunction)(bool init);

namespace MapManager
{
	// size of the level
	extern const unsigned char LEVEL_WIDTH;
	extern const unsigned char LEVEL_HEIGHT;
	
	// all the map sprite ids of the full level
	extern const unsigned int LevelLineIndex[];
	extern const unsigned char Level[];
	
	// all the function to init the items in the level split per puzzle screen
	extern ItemInitFunction ItemInitFunctions[];
	extern const unsigned char PUZZLE_SCREEN_COUNT;
	
	// init the progress with all the living items
	void InitProgress();
};

#endif