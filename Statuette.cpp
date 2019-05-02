/*
 * Implement the logic and drawing of the statuette bonus
*/

#include "RickArdurous.h"
#include "Statuette.h"
#include "SpriteData.h"
#include "Rick.h"
#include "MapManager.h"

Statuette::Statuette(int startX, int startY) : PickUpItem(startX, startY)
{
};

bool Statuette::Update(UpdateStep step)
{
	switch (step)
	{
		case UpdateStep::DRAW_IGNORED_BY_ENEMIES:
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				// check if the player pick me up
				if (DoesRickPickMeUp(SpriteData::STATUE_SPRITE_WIDTH, SpriteData::STATUE_SPRITE_HEIGHT))
				{
					ClearProperty(Item::PropertyFlags::ALIVE);
					Rick::StatuetteCount++;
				}
				
				// draw the statuette
				arduboy.drawBitmap(MapManager::GetXOnScreen(X), MapManager::GetYOnScreen(Y), SpriteData::Statue, SpriteData::STATUE_SPRITE_WIDTH, SpriteData::STATUE_SPRITE_HEIGHT, WHITE);
				
				// draw the shiny star
				UpdateShineStar(-2, 3, -2, 4);
			}
			break;
	}
	return false;
}
