/*
 * Implement the logic and drawing of Stalactite
*/

#include "RickArdurous.h"
#include "Stalactite.h"
#include "SpriteData.h"
#include "MapManager.h"
#include "Rick.h"

Stalactite::Stalactite(int startX, int startY, unsigned char flags) : Item(startX, startY, flags | Item::PropertyFlags::ALIVE)
{
}

bool Stalactite::Update(UpdateStep step)
{
	switch (step)
	{
		case Item::UpdateStep::DRAW_LETHAL:
		{
			if (AnimState == State::WAIT)
			{
				// check if the main character is triggering me
				CheckTrigerer(Rick::IsAlive(), Rick::GetX(), Rick::GetY());
				// check if the other trap trigerer is triggering me
				MapManager::CallMeBackForEachTrapTriggerer(this, &CheckTrigererCallback);
			}
			else if (AnimState == State::FALL)
			{
				// make the stalactite fall
				Y++;
				if (MapManager::IsThereStaticCollisionAt(X, Y + SpriteData::STALACTITE_SPRITE_HEIGHT))
				{
					AnimState = State::DEAD;
				}
			}

			// draw the stalactite
			arduboy.drawBitmapExtended(MapManager::GetXOnScreen(X), MapManager::GetYOnScreen(Y),
									SpriteData::Stalactite,
									SpriteData::STALACTITE_SPRITE_WIDTH, SpriteData::STALACTITE_SPRITE_HEIGHT,
									WHITE, IsPropertySet(PropertyFlags::MIRROR_X));

			break;
		}
		case Item::UpdateStep::RESPAWN:
		{
			Y = 10; // DEBUG CODE
			AnimState = State::WAIT;
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
	if ((AnimState == State::WAIT) && isAlive && (Y < trigererY) && 
		(X < trigererX + SpriteData::RICK_SPRITE_WIDTH) && 
		(X + (SpriteData::STALACTITE_SPRITE_WIDTH * 3) > trigererX))
	{
		AnimState = State::FALL;
	}
}