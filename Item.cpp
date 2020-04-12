/*
 * This file implement the base class for all the items present in the level
*/

#include "RickArdurous.h"
#include "Item.h"

void Item::Init(int startX, int startY, unsigned char flags)
{
	X = startX;
	Y = startY;
	Property = flags;
	// call the update virtual function with the Respawn step, for specific data init
	Update(Item::UpdateStep::RESPAWN);
}
