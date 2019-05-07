/*
 * This file implement the base class for all the items present in the level
*/

#include "RickArdurous.h"
#include "Item.h"

Item::Item(unsigned char flags)
{
	Property = flags;
}

void Item::Init(int startX, int startY)
{
	X = startX;
	Y = startY;
}
