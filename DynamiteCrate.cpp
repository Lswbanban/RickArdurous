/*
 * Implement the logic and drawing of a dynamite crate
*/

#include "RickArdurous.h"
#include "DynamiteCrate.h"
#include "SpriteData.h"

DynamiteCrate::DynamiteCrate(int startX, int startY) : PickUpItem(startX, startY, Item::PropertyFlags::PICKUP)
{
};

void DynamiteCrate::Update()
{
	// draw the crate
	if (IsPropertySet(Item::PropertyFlags::PICKUP))
		arduboy.drawBitmap(X, Y, SpriteData::DynamiteCrate, SpriteData::CRATE_SPRITE_WIDTH, SpriteData::CRATE_SPRITE_HEIGHT, WHITE);
}

void DynamiteCrate::PickUp()
{
	ClearProperty(Item::PropertyFlags::PICKUP);
}