/*
 * Implement the logic and drawing of a dynamite crate
*/

#include "RickArdurous.h"
#include "DynamiteCrate.h"
#include "SpriteData.h"
#include "Rick.h"
#include "MapManager.h"

DynamiteCrate::DynamiteCrate(int startX, int startY) : PickUpItem(startX, startY)
{
};

bool DynamiteCrate::Update(UpdateStep step)
{
	if (GetType() == Item::ItemType::IGNORED_BY_ENEMIES)
	{
		// check if the player pick me up
		CheckIfRickPickMeUp(SpriteData::CRATE_SPRITE_WIDTH, SpriteData::CRATE_SPRITE_HEIGHT);

		// draw the crate
		arduboy.drawBitmap(MapManager::GetXOnScreen(X), MapManager::GetYOnScreen(Y), SpriteData::DynamiteCrate, SpriteData::CRATE_SPRITE_WIDTH, SpriteData::CRATE_SPRITE_HEIGHT, WHITE);
		
		// draw the shiny star
		UpdateShineStar(-2, 9, 1, 6);
	}
	return false;
}

void DynamiteCrate::PickUp()
{
	SetType(Item::ItemType::NO_TYPE);
	Rick::DynamiteCount = Rick::MAX_DYNAMITE_COUNT;
}