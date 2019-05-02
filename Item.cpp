/*
 * This file implement the base class for all the items present in the level
*/

#include "RickArdurous.h"
#include "Item.h"

Item::Item(int startX, int startY, unsigned char flags)
{
	X = startX;
	Y = startY;
	Property = flags;
}