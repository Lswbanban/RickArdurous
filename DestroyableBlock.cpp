/*
 * Implement the logic and drawing of Destroyable Blocks
*/

#include "RickArdurous.h"
#include "DestroyableBlock.h"
#include "SpriteData.h"
#include "MapManager.h"

DestroyableBlock::DestroyableBlock(int startX, int startY, unsigned char flag) : Item(startX, startY, flag | Item::PropertyFlags::ALIVE)
{
}

bool DestroyableBlock::Update(UpdateStep step)
{
	switch (step)
	{
		case Item::UpdateStep::CHECK_LETHAL:
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
	int x = X;
	if (spriteId == SpriteData::WallId::DESTROYABLE_BLOCK_RIGHT)
		x += SpriteData::LEVEL_SPRITE_WIDTH;
	return (mapX == (x >> 3)) && (mapY == (Y >> 3));
}

bool DestroyableBlock::IsAlive()
{
	return IsPropertySet(Item::PropertyFlags::ALIVE);
}
