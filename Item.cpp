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
	// if we are not forced to respaw, ask our alive status to the progress
	if (!shouldRespawn)
		shouldRespawn = Progress::IsItemAlive(this);
	// set the alive flag
	if (shouldRespawn)
	{
		// set the alive flag in the flags variable
		flags |= Item::PropertyFlags::ALIVE;
		// warn also the progress, because the general init function will override the property flag and not call the SetProperty() function
		Progress::SetItemAlive(this, true);
		// add the item to the manager
		MapManager::AddItem(this);
		// and call the common init function
		CommonInit(startX, startY, flags);
	}
	else
	{
		// warn the progress, because the general init function will override the property flag and not call the ClearProperty() function
		Progress::SetItemAlive(this, false);
		// remove the item from the manager
		MapManager::RemoveItem(this);
	}
};
