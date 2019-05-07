/*
 * Implement the logic the base class of Destroyable items
*/

#include "RickArdurous.h"
#include "DestroyableItem.h"
#include "MapManager.h"

DestroyableItem::DestroyableItem(unsigned char flags) : Item(flags)
{
}

bool DestroyableItem::CheckLethalDynamite(int width)
{
	// get my coordinate on screen
	int xOnScreen = MapManager::GetXOnScreen(X);
	int yOnScreen = MapManager::GetYOnScreen(Y);
	
	// check on the left
	for (int i = 1; i <= EXPLOSION_DETECTION_DISTANCE; ++i)
		if (arduboy.getPixel(xOnScreen - i, yOnScreen) == WHITE)
			return true;
	
	// check on the right
	xOnScreen += width;
	for (int i = 1; i <= EXPLOSION_DETECTION_DISTANCE; ++i)
		if (arduboy.getPixel(xOnScreen + i, yOnScreen) == WHITE)
			return true;
	
	// by default no collision detected
	return false;
}