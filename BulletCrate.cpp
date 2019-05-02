/*
 * Implement the logic and drawing of a bullet crate
*/

#include "RickArdurous.h"
#include "BulletCrate.h"
#include "SpriteData.h"
#include "Rick.h"
#include "MapManager.h"

BulletCrate::BulletCrate(int startX, int startY) : PickUpItem(startX, startY)
{
};

bool BulletCrate::Update(UpdateStep step)
{
	if (GetType() == Item::ItemType::IGNORED_BY_ENEMIES)
	{
		// check if the player pick me up
		CheckIfRickPickMeUp(SpriteData::CRATE_SPRITE_WIDTH, SpriteData::CRATE_SPRITE_HEIGHT);

		// draw the crate
		arduboy.drawBitmap(MapManager::GetXOnScreen(X), MapManager::GetYOnScreen(Y), SpriteData::BulletCrate, SpriteData::CRATE_SPRITE_WIDTH, SpriteData::CRATE_SPRITE_HEIGHT, WHITE);

		// draw the shiny star
		UpdateShineStar(-2, 9, 1, 6);
	}
	return false;
}

void BulletCrate::PickUp()
{
	SetType(Item::ItemType::NO_TYPE);
	Rick::BulletCount = Rick::MAX_BULLET_COUNT;
}