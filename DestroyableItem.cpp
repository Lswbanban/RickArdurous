/*
 * Implement the logic the base class of Destroyable items
*/

#include "RickArdurous.h"
#include "DestroyableItem.h"
#include "MapManager.h"

DestroyableItem::DestroyableItem(unsigned char flags) : Item(flags)
{
}

bool DestroyableItem::CheckLethalDynamite(unsigned char width)
{
	// get my y coordinate on screen
	int yOnScreen = MapManager::GetYOnScreen(Y);
	// check if I'm on screen
	if ((yOnScreen >= 0) && (yOnScreen < HEIGHT))
	{
		// get my x coordinate on screen
		int xOnScreen = MapManager::GetXOnScreen(X);
		
		// iterate on a certain distance
		for (int i = 1; i <= EXPLOSION_DETECTION_DISTANCE; ++i)
		{
			// check on the left
			int xLeft = xOnScreen - i;
			if ((xLeft >= 0) && (xLeft < WIDTH) && (arduboy.getPixel(xLeft, yOnScreen) == WHITE))
				return true;
			// check on the right
			int xRight = xOnScreen + width + i;
			if ((xRight >= 0) && (xRight < WIDTH) && (arduboy.getPixel(xRight, yOnScreen) == WHITE))
				return true;
		}
	}
	// by default no collision detected
	return false;
}