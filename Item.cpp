/*
 * This file implement the base class for all the items present in the level
*/

#include "RickArdurous.h"
#include "Item.h"
#include "Progress.h"
#include "MapManager.h"

void Item::CommonInit(int startX, int startY, unsigned char flags)
{
	X = startX;
	Y = startY;
	// override the property flag to reset totally the property as the specified flag
	Property = flags;
	// call the update virtual function with the Respawn step, for specific data init
	Update(Item::UpdateStep::RESPAWN);
}

void Item::Init(int startX, int startY, unsigned char flags)
{
	// for items that can never die, add it to the manager anyway
	MapManager::AddItem(this);
	// and call the common init function
	CommonInit(startX, startY, flags);
}

void Item::Init(int startX, int startY, unsigned char flags, bool shouldRespawn)
{
	// if we are not forced to respaw, check our alive status that as been correctly set by the progress
	if (!shouldRespawn)
		shouldRespawn = IsPropertySet(Item::PropertyFlags::ALIVE);
	// set the alive flag if we should respawn
	if (shouldRespawn)
	{
		// set the alive flag in the flags variable
		flags |= Item::PropertyFlags::ALIVE;
		// add the item to the manager
		MapManager::AddItem(this);
		// and call the common init function
		CommonInit(startX, startY, flags);
	}
	else
	{
		// remove the item from the manager
		MapManager::RemoveItem(this);
	}
};
