/*
 * Implement the logic and drawing of Destroyable Blocks
*/

#include "RickArdurous.h"
#include "DestroyableBlock.h"
#include "SpriteData.h"
#include "BlockFragment.h"
#include "MapManager.h"

BlockFragment * DestroyableBlock::Fragments[FRAGMENT_COUNT];

DestroyableBlock::DestroyableBlock()
{
	SetProperty(Item::PropertyFlags::DESTROYABLE_BLOCK | Item::PropertyFlags::ALIVE);
}

void DestroyableBlock::StaticInit()
{
	for (unsigned char i = 0; i < FRAGMENT_COUNT; ++i)
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
				// spawn block fragment and remove myself from the manager
				if (CheckLethalDynamite(SpriteData::LEVEL_SPRITE_WIDTH << 1))
				{
					InitDeath();
					return true;
				}
			}
			break;
		}

		case UpdateStep::DRAW_STATIC_COLLISION:
		{
			// if we are updated, that means we are alive, so no need to check the property flag
			arduboy.drawBitmapExtended(MapManager::GetXOnScreen(X), MapManager::GetYOnScreen(Y), SpriteData::DestroyableBlock, SpriteData::DESTROYABLE_BLOCK_SPRITE_WIDTH, SpriteData::DESTROYABLE_BLOCK_SPRITE_HEIGHT, WHITE, false);
		}
		break;

		case Item::UpdateStep::RESPAWN:
		{
			SetProperty(Item::PropertyFlags::ALIVE);
			break;
		}
	}
	return false;
}

void DestroyableBlock::InitDeath()
{
	ClearProperty(Item::PropertyFlags::ALIVE);
	for (unsigned char i = 0; i < FRAGMENT_COUNT; ++i)
		Fragments[i]->Spawn(X + (i*6), Y, i);
}

bool DestroyableBlock::IsLocatedAt(unsigned char mapX, unsigned char mapY)
{
	return (mapY == (Y >> 3)) && ((mapX == (X >> 3)) || (mapX == ((X + SpriteData::LEVEL_SPRITE_WIDTH) >> 3)));
}
