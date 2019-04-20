/*
 * Implement the logic and drawing of the mummy ennemies
*/

#include "RickArdurous.h"
#include "Mummy.h"
#include "SpriteData.h"
#include "Rick.h"
#include "MapManager.h"

const char WALK_ANIM_SPEED[] = { 8, 12, 4, 6 };

Mummy::Mummy(int startX, int startY) : Item(startX, startY, Item::PropertyFlags::ENEMIES | Item::PropertyFlags::STATIC_COLLISION_NEEDED)
{
	AnimFrameId = 0;
	AnimFrameCount = 0;
};

bool Mummy::Update(UpdateStep step)
{
	switch (step)
	{
		case Item::UpdateStep::DRAW_ENEMIES:
		{
			// update the animation
			AnimFrameCount++;
			if (AnimFrameCount == WALK_ANIM_SPEED[AnimFrameId])
			{
				X++;
				AnimFrameId++;
				AnimFrameCount = 0;
				if (AnimFrameId == 4)
					AnimFrameId = 0;
			}
			
			// draw the statuette and check the collision with eventual lethal stuff
			int collision = arduboy.drawBitmapExtended(MapManager::GetXOnScreen(X),
									MapManager::GetYOnScreen(Y),
									SpriteData::Mummy[AnimFrameId],
									SpriteData::MUMMY_SPRITE_WIDTH, SpriteData::MUMMY_SPRITE_HEIGHT,
									WHITE, false);
			if (collision != 0)
			{
				ClearProperty(Item::PropertyFlags::ALIVE);
				MapManager::RemoveItem(this);
				return true;
			}
			break;
		}
		case Item::UpdateStep::CHECK_STATIC_COLLISION:
		{
			int yUnderFeet = Y + 13;
			if (!MapManager::IsThereAnyHorizontalCollisionAt(X+1, X+7, yUnderFeet))
				Y++;
			break;
		}
	}
	return false;
}