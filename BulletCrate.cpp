/*
 * Implement the logic and drawing of a bullet crate
*/

#include "RickArdurous.h"
#include "BulletCrate.h"
#include "SpriteData.h"
#include "Rick.h"

BulletCrate::BulletCrate(int startX, int startY) : PickUpItem(startX, startY, Item::PropertyFlags::IGNORED_BY_ENEMIES)
{
};

bool BulletCrate::Update(UpdateStep step)
{
	if (IsPropertySet(Item::PropertyFlags::IGNORED_BY_ENEMIES))
	{
		// draw the crate
		arduboy.drawBitmap(X, Y, SpriteData::BulletCrate, SpriteData::CRATE_SPRITE_WIDTH, SpriteData::CRATE_SPRITE_HEIGHT, WHITE);

		// ask the main character to check collision with me
		Rick::CheckCollisionWithPickUp(this);

		// draw the shiny star
		UpdateShineStar(-2, 9, 1, 6);
	}
	return false;
}

void BulletCrate::PickUp()
{
	ClearProperty(Item::PropertyFlags::IGNORED_BY_ENEMIES);
	Rick::BulletCount = Rick::MAX_BULLET_COUNT;
}