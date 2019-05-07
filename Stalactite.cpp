/*
 * Implement the logic and drawing of Stalactite
*/

#include "RickArdurous.h"
#include "Stalactite.h"
#include "SpriteData.h"
#include "MapManager.h"
#include "Rick.h"
#include "Physics.h"

Stalactite::Stalactite(unsigned char flags) : Item(flags | Item::PropertyFlags::ALIVE)
{
}

bool Stalactite::Update(UpdateStep step)
{
	switch (step)
	{
		case Item::UpdateStep::DRAW_LETHAL:
		{
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				int shakeX = 0;
				// use the special flag as an anim state: if special is set then the stalactite is falling,
				// otherwise it is waiting
				if (!IsPropertySet(Item::PropertyFlags::SPECIAL))
				{
					// check if the main character is triggering me
					CheckTrigerer(Rick::IsAlive(), Rick::GetX(), Rick::GetY());
					// check if the other trap trigerer is triggering me
					MapManager::CallMeBackForEachTrapTriggerer(this, &CheckTrigererCallback);

					// compute a shaking x variation
					char shakingMove[] = {1, -1, 0, 2, 0, -2, 1, -1};
					for (int i = 0; i < sizeof(shakingMove); ++i)
						if (arduboy.everyXFrames(SHAKING_SPEED + i))
						{
							shakeX = shakingMove[i];
							break;
						}
				}
				else
				{
					// make the stalactite fall
					Physics::UpdateFall(FallAnimSpeedIndex, Y);
					if (MapManager::IsThereStaticCollisionAt(X, Y + SpriteData::STALACTITE_SPRITE_HEIGHT))
						ClearProperty(Item::PropertyFlags::ALIVE);
				}
				// draw the stalactite
				Draw(shakeX);
			}
			break;
		}
		
		case Item::UpdateStep::DRAW_IGNORED_BY_ENEMIES:
		{
			if (!IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				// increase the sparks frame counter
				if (arduboy.everyXFrames(SPARKS_ANIM_SPEED))
				{
					Y++;
					SparksAnimFrameId++;
				}

				// remove from update once the sparks anim is finished
				if (SparksAnimFrameId == SpriteData::SPARKS_SPRITE_FRAME_COUNT)
					return true;
				
				// draw the Stalactite
				if (SparksAnimFrameId < 3)
					Draw(0);
				
				// draw the sparks
				for (int i = 0; i < 2; ++i)
					arduboy.drawBitmap(MapManager::GetXOnScreen(X + (i*4)),
						MapManager::GetYOnScreen(Y + 2 - SparksAnimFrameId),
						SpriteData::Sparks[SparksAnimFrameId],
						SpriteData::SPARKS_SPRITE_WIDTH,
						SpriteData::SPARKS_SPRITE_HEIGHT,
						INVERT);
			}
			break;
		}
		
		case Item::UpdateStep::RESPAWN:
		{
			Y = 10; // DEBUG CODE
			ClearProperty(Item::PropertyFlags::SPECIAL);
			SetProperty(Item::PropertyFlags::ALIVE);
			Physics::StopFall(FallAnimSpeedIndex);
			FallAnimSpeedIndex = 0;
			SparksAnimFrameId = 0;
			break;
		}
	}
	return false;
}

void Stalactite::CheckTrigererCallback(Item * me, Item * trigerer)
{
	((Stalactite *)me)->CheckTrigerer(trigerer->IsPropertySet(Item::PropertyFlags::ALIVE), trigerer->GetX(), trigerer->GetY());
}

void Stalactite::CheckTrigerer(bool isAlive, int trigererX, int trigererY)
{
	// check if the trigerer is alive and inside the detection range,
	// and that the stalactite is not alreay falling
	if (isAlive && (Y < trigererY) && 
		(X < trigererX + SpriteData::RICK_SPRITE_WIDTH) && 
		(X + (SpriteData::STALACTITE_SPRITE_WIDTH * 3) > trigererX))
	{
		SetProperty(Item::PropertyFlags::SPECIAL);
		FallAnimSpeedIndex = Physics::StartFall();
	}
}

void Stalactite::Draw(int shakeX)
{
	for (int i = 0; i < 2; ++i)
		arduboy.drawBitmapExtended(
					MapManager::GetXOnScreen(X + (i * (SpriteData::STALACTITE_SPRITE_WIDTH + 1)) + shakeX),
					MapManager::GetYOnScreen(Y + i),
					SpriteData::Stalactite,
					SpriteData::STALACTITE_SPRITE_WIDTH, SpriteData::STALACTITE_SPRITE_HEIGHT,
					WHITE, i);
}
