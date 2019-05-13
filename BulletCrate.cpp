/*
 * Implement the logic and drawing of a bullet crate
*/

#include "RickArdurous.h"
#include "BulletCrate.h"
#include "SpriteData.h"
#include "Rick.h"
#include "MapManager.h"

BulletCrate::BulletCrate() : PickUpItem()
{
};

bool BulletCrate::Update(UpdateStep step)
{
	switch (step)
	{
		case UpdateStep::DRAW_IGNORED_BY_ENEMIES:
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				// check if the player pick me up
				if (DoesRickPickMeUp(SpriteData::CRATE_SPRITE_WIDTH, SpriteData::CRATE_SPRITE_HEIGHT))
				{
					ClearProperty(Item::PropertyFlags::ALIVE);
					Rick::BulletCount = Rick::MAX_BULLET_COUNT;
					return true;
				}
				
				// draw the crate
				arduboy.drawBitmap(MapManager::GetXOnScreen(X), MapManager::GetYOnScreen(Y), SpriteData::BulletCrate, SpriteData::CRATE_SPRITE_WIDTH, SpriteData::CRATE_SPRITE_HEIGHT, WHITE);

				// draw the shiny star
				UpdateShineStar(-2, 9, 1, 6);
			}
			break;
			
		case UpdateStep::RESPAWN:
			SetProperty(Item::PropertyFlags::ALIVE);
			break;
	}
	return false;
}