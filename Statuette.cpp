/*
 * Implement the logic and drawing of the statuette bonus
*/

#include "RickArdurous.h"
#include "Statuette.h"
#include "SpriteData.h"
#include "Rick.h"
#include "MapManager.h"

Statuette::Statuette(int startX, int startY) : PickUpItem(startX, startY, Item::PropertyFlags::IGNORED_BY_ENEMIES)
{
};

bool Statuette::Update(UpdateStep step)
{
	if (IsPropertySet(Item::PropertyFlags::IGNORED_BY_ENEMIES))
	{
		// check if the player pick me up
		CheckIfRickPickMeUp(SpriteData::STATUE_SPRITE_WIDTH, SpriteData::STATUE_SPRITE_HEIGHT);
		
		// draw the statuette
		arduboy.drawBitmap(MapManager::GetXOnScreen(X), MapManager::GetYOnScreen(Y), SpriteData::Statue, SpriteData::STATUE_SPRITE_WIDTH, SpriteData::STATUE_SPRITE_HEIGHT, WHITE);
		
		// draw the shiny star
		UpdateShineStar(-2, 3, -2, 4);
	}
	return false;
}

void Statuette::PickUp()
{
	ClearProperty(Item::PropertyFlags::IGNORED_BY_ENEMIES);
	Rick::StatuetteCount++;
}