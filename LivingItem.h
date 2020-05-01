#ifndef _LIVING_ITEM_H_
#define _LIVING_ITEM_H_

#include "Item.h"

class LivingItem: public Item
{
public:
	static constexpr int PUZZLE_SCREEN_BYTE_COUNT = 2; // TODO Move to MapData and make it equals to (PUZZLE_SCREEN_COUNT >> 3) + 1;
	
	void Init(int startX, int startY, unsigned char flags, bool shouldRespawn);
	void SaveAndLoadAliveStatus(unsigned char currentScreenIdToSave, unsigned char newScreenIdToLoad);

private:
	unsigned char AlivePerPuzzleScreen[PUZZLE_SCREEN_BYTE_COUNT];
};

#endif