/*
* This file handle the player progression in the game, and save it to the flash memory
*/

#include "RickArdurous.h"
#include "Progress.h"
#include "MapManager.h"

namespace Progress
{
	bool mIsAlive[2];
}

void Progress::ResetProgress()
{
	mIsAlive[0] = true;
	mIsAlive[1] = true;
}

bool Progress::IsItemAlive(Item * item)
{
	unsigned char id = MapManager::GetCurrentPuzzleScreenId();
	return mIsAlive[id];
}

void Progress::SetItemAlive(Item * item, bool isAlive)
{
	unsigned char id = MapManager::GetCurrentPuzzleScreenId();
	
	mIsAlive[id] = isAlive;
}
