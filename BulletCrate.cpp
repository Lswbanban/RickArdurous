/*
 * Implement the logic and drawing of a bullet crate
*/

#include "RickArdurous.h"
#include "BulletCrate.h"
#include "SpriteData.h"
#include "Rick.h"

BulletCrate::BulletCrate(int startX, int startY) : PickUpItem(startX, startY, Item::PropertyFlags::PICKUP)
{
};

bool BulletCrate::Update()
{
	if (IsPropertySet(Item::PropertyFlags::PICKUP))
	{
		// draw the crate
		arduboy.drawBitmap(X, Y, SpriteData::BulletCrate, SpriteData::CRATE_SPRITE_WIDTH, SpriteData::CRATE_SPRITE_HEIGHT, WHITE);
		// draw the shiny star
		UpdateShineStar(-2, 9, 1, 6);
	}
	return false;
}

void BulletCrate::PickUp()
{
	ClearProperty(Item::PropertyFlags::PICKUP);
	Rick::BulletCount = Rick::MAX_BULLET_COUNT;
}