/*
 * Implement the logic and drawing of Destroyable Blocks
*/

#include "RickArdurous.h"
#include "DestroyableBlock.h"
#include "SpriteData.h"
#include "MapManager.h"

DestroyableBlock::DestroyableBlock(int startX, int startY, unsigned char flags) : Item(startX, startY, flags | Item::PropertyFlags::DESTROYABLE_BLOCK | Item::PropertyFlags::ALIVE)
{
}

bool DestroyableBlock::Update(UpdateStep step)
{
	switch (step)
	{
		case Item::UpdateStep::CHECK_LETHAL:
		{
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				// get my coordinate on screen
				int xOnScreen = MapManager::GetXOnScreen(X);
				int yOnScreen = MapManager::GetYOnScreen(Y);
				// check on the left
				for (int i = 1; i <= EXPLOSION_DETECTION_DISTANCE; ++i)
					if (arduboy.getPixel(xOnScreen - i, yOnScreen) == WHITE)
						InitDeath();
				// check on the right
				xOnScreen += SpriteData::LEVEL_SPRITE_WIDTH << 1;
				for (int i = 1; i <= EXPLOSION_DETECTION_DISTANCE; ++i)
					if (arduboy.getPixel(xOnScreen + i, yOnScreen) == WHITE)
						InitDeath();
			}
			break;
		}
	}
	return false;
}

void DestroyableBlock::InitDeath()
{
	ClearProperty(Item::PropertyFlags::ALIVE);
}

bool DestroyableBlock::IsLocatedAt(unsigned char mapX, unsigned char mapY, unsigned char spriteId)
{
	if (mapY == (Y >> 3))
	{
		int x = (spriteId == SpriteData::WallId::DESTROYABLE_BLOCK_RIGHT) ? X + SpriteData::LEVEL_SPRITE_WIDTH : X;
		return (mapX == (x >> 3));
	}
	return false;
}

bool DestroyableBlock::IsAlive()
{
	return IsPropertySet(Item::PropertyFlags::ALIVE);
}
