/*
 * Implement the logic and drawing of Destroyable Blocks
*/

#include "RickArdurous.h"
#include "DestroyableBlock.h"
#include "SpriteData.h"
#include "BlockFragment.h"

BlockFragment * DestroyableBlock::Fragments[FRAGMENT_COUNT];

DestroyableBlock::DestroyableBlock(unsigned char flags) : DestroyableItem(flags | Item::PropertyFlags::DESTROYABLE_BLOCK | Item::PropertyFlags::ALIVE)
{
}

void DestroyableBlock::StaticInit()
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
				// spawn block fragment and remove myself from the manager
				if (CheckLethalDynamite(SpriteData::LEVEL_SPRITE_WIDTH << 1))
				{
					InitDeath();
					return true;
				}
			}
			break;
		}
		case Item::UpdateStep::RESPAWN:
		{
			SetProperty(Item::PropertyFlags::ALIVE);
			// kill all the fragments
			for (int i = 0; i < FRAGMENT_COUNT; ++i)
				Fragments[i]->Kill();
			break;
		}
	}
	return false;
}

void DestroyableBlock::InitDeath()
{
	ClearProperty(Item::PropertyFlags::ALIVE);
	for (int i = 0; i < FRAGMENT_COUNT; ++i)
		Fragments[i]->Spawn(X + (i*6), Y, i);
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
