/*
 * Implement the logic of the Stalagmite
*/

#include "RickArdurous.h"
#include "Stalagmite.h"
#include "MapManager.h"
#include "SpriteData.h"

Stalagmite::Stalagmite(int startX, int startY, unsigned char flags) : DestroyableItem(startX, startY, flags | Item::PropertyFlags::ALIVE)
{
}

bool Stalagmite::Update(UpdateStep step)
{
	switch (step)
	{
		case Item::UpdateStep::DRAW_LETHAL:
		{
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				for (int i = 0; i < 2; ++i)
					arduboy.drawBitmapExtended(
						MapManager::GetXOnScreen(X + (i * (SpriteData::STALAGMITE_SPRITE_WIDTH + 1))),
						MapManager::GetYOnScreen(Y),
						SpriteData::Stalagmite,
						SpriteData::STALAGMITE_SPRITE_WIDTH, SpriteData::STALAGMITE_SPRITE_HEIGHT,
						WHITE, i);
			}
			break;
		}
		case Item::UpdateStep::CHECK_LETHAL:
		{
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				// spawn sparks if the dynamite kill me
				if (CheckLethalDynamite(SpriteData::STALAGMITE_SPRITE_WIDTH << 1))
				{
					ClearProperty(Item::PropertyFlags::ALIVE);
					return true;
				}
			}
			break;
		}
		case Item::UpdateStep::RESPAWN:
		{
			SetProperty(Item::PropertyFlags::ALIVE);
			break;
		}
	}
	return false;
}
