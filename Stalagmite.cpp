/*
 * Implement the logic of the Stalagmite
*/

#include "RickArdurous.h"
#include "Stalagmite.h"
#include "MapManager.h"
#include "SpriteData.h"

Stalagmite::Stalagmite(unsigned char flags) : DestroyableItem(flags | Item::PropertyFlags::ALIVE)
{
}

bool Stalagmite::Update(UpdateStep step)
{
	switch (step)
	{
		case Item::UpdateStep::DRAW_LETHAL:
		{
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
				Draw();
			break;
		}
		
		case Item::UpdateStep::CHECK_LETHAL:
		{
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				// spawn sparks if the dynamite kill me
				if (CheckLethalDynamite(SpriteData::STALAGMITE_SPRITE_WIDTH << 1))
					ClearProperty(Item::PropertyFlags::ALIVE);
			}
			break;
		}
		
		case Item::UpdateStep::DRAW_IGNORED_BY_ENEMIES:
		{
			if (!IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				// increase the sparks frame counter
				if (arduboy.everyXFrames(SPARKS_ANIM_SPEED))
					SparksAnimFrameId++;

				// remove from update once the sparks anim is finished
				if (SparksAnimFrameId >= SpriteData::SPARKS_SPRITE_FRAME_COUNT)
					return true;
				
				// draw the Stalactite
				if (SparksAnimFrameId < 2)
					Draw();
				
				// draw the sparks
				for (int i = 0; i < 3; ++i)
					arduboy.drawBitmapExtended(MapManager::GetXOnScreen(X + (i*3) -1),
						MapManager::GetYOnScreen(Y + 1),
						SpriteData::Sparks[(SparksAnimFrameId + i) % SpriteData::SPARKS_SPRITE_FRAME_COUNT],
						SpriteData::SPARKS_SPRITE_WIDTH,
						SpriteData::SPARKS_SPRITE_HEIGHT,
						INVERT, false);
			}
			break;
		}

		case Item::UpdateStep::RESPAWN:
		{
			SparksAnimFrameId = 0;
			SetProperty(Item::PropertyFlags::ALIVE);
			break;
		}
	}
	return false;
}

void Stalagmite::Draw()
{
	for (int i = 0; i < 2; ++i)
	arduboy.drawBitmapExtended(
		MapManager::GetXOnScreen(X + (i * (SpriteData::STALAGMITE_SPRITE_WIDTH + 1))),
		MapManager::GetYOnScreen(Y),
		SpriteData::Stalagmite,
		SpriteData::STALAGMITE_SPRITE_WIDTH, SpriteData::STALAGMITE_SPRITE_HEIGHT,
		WHITE, i);
}
