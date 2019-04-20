/*
 * Implement the logic and drawing of the mummy ennemies
*/

#include "RickArdurous.h"
#include "Mummy.h"
#include "SpriteData.h"
#include "Rick.h"
#include "MapManager.h"

Mummy::Mummy(int startX, int startY) : Item(startX, startY, Item::PropertyFlags::ENEMIES | Item::PropertyFlags::STATIC_COLLISION_NEEDED)
{
};

bool Mummy::Update(UpdateStep step)
{
	switch (step)
	{
		case Item::UpdateStep::DRAW_ENEMIES:
		{
			// draw the statuette
			arduboy.drawBitmap(MapManager::GetXOnScreen(X), MapManager::GetYOnScreen(Y), SpriteData::Mummy[0], SpriteData::MUMMY_SPRITE_WIDTH, SpriteData::MUMMY_SPRITE_HEIGHT, WHITE);
			break;
		}
		case Item::UpdateStep::CHECK_STATIC_COLLISION:
		{
			int yUnderFeet = Y + 12;
			if (!MapManager::IsThereAnyHorizontalCollisionAt(X+1, X+7, yUnderFeet))
				Y++;
			break;
		}
	}
	return false;
}