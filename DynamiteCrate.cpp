/*
 * Implement the logic and drawing of a dynamite crate
*/

#include "RickArdurous.h"
#include "DynamiteCrate.h"
#include "SpriteData.h"
#include "Rick.h"
#include "MapManager.h"

DynamiteCrate::DynamiteCrate(int startX, int startY) : PickUpItem(startX, startY, Item::PropertyFlags::IGNORED_BY_ENEMIES)
{
};

bool DynamiteCrate::Update(UpdateStep step)
{
	if (IsPropertySet(Item::PropertyFlags::IGNORED_BY_ENEMIES))
	{
		// draw the crate
		arduboy.drawBitmap(MapManager::GetXOnScreen(X), MapManager::GetYOnScreen(Y), SpriteData::DynamiteCrate, SpriteData::CRATE_SPRITE_WIDTH, SpriteData::CRATE_SPRITE_HEIGHT, WHITE);
		
		// ask the main character to check collision with me
		Rick::CheckCollisionWithPickUp(this);

		// draw the shiny star
		UpdateShineStar(-2, 9, 1, 6);
	}
	return false;
}

void DynamiteCrate::PickUp()
{
	ClearProperty(Item::PropertyFlags::IGNORED_BY_ENEMIES);
	Rick::DynamiteCount = Rick::MAX_DYNAMITE_COUNT;
}