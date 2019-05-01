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
		case Item::UpdateStep::DRAW_DECOR_BLOCK:
		{
			break;
		}
	}

	return false;
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
