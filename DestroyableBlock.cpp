/*
 * Implement the logic and drawing of Destroyable Blocks
*/

#include "RickArdurous.h"
#include "DestroyableBlock.h"
#include "SpriteData.h"
#include "MapManager.h"
#include "BlockFragment.h"

BlockFragment * DestroyableBlock::Fragments[FRAGMENT_COUNT];

DestroyableBlock::DestroyableBlock(int startX, int startY, unsigned char flags) : Item(startX, startY, flags | Item::PropertyFlags::DESTROYABLE_BLOCK | Item::PropertyFlags::ALIVE)
{
}

void DestroyableBlock::Init()
{
	for (int i = 0; i < FRAGMENT_COUNT; ++i)
		Fragments[i] = new BlockFragment();
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
				bool isDead = false;
				for (int i = 1; i <= EXPLOSION_DETECTION_DISTANCE; ++i)
					if (arduboy.getPixel(xOnScreen - i, yOnScreen) == WHITE)
						isDead = true;
				
				// check on the right
				xOnScreen += SpriteData::LEVEL_SPRITE_WIDTH << 1;
				for (int i = 1; i <= EXPLOSION_DETECTION_DISTANCE; ++i)
					if (arduboy.getPixel(xOnScreen + i, yOnScreen) == WHITE)
						isDead = true;
					
				// spawn block fragment and remove myself from the manager
				if (isDead)
				{
					InitDeath();
					return true;
				}
			}
			break;
		}
	}
	return false;
}

void DestroyableBlock::InitDeath()
{
	ClearProperty(Item::PropertyFlags::ALIVE);
	for (int i = 0; i < FRAGMENT_COUNT; ++i)
		Fragments[i]->Spawn(X, Y);
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
