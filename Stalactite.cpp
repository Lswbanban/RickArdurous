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
			// check if the main character is triggering me
			//CheckTrigerer(Rick::IsAlive(), Rick::GetX(), Rick::GetY());
			// check if the other trap trigerer is triggering me
			//MapManager::CallMeBackForEachTrapTriggerer(this, &CheckTrigererCallback);
			// draw the stalactite
			arduboy.drawBitmapExtended(MapManager::GetXOnScreen(X), MapManager::GetYOnScreen(Y),
									SpriteData::Stalactite,
									SpriteData::STALACTITE_SPRITE_WIDTH, SpriteData::STALACTITE_SPRITE_HEIGHT,
									WHITE, IsPropertySet(PropertyFlags::MIRROR_X));
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
	if (AnimState == State::WAIT)
	{
		// check if the main character is inside the detection range
		if (isAlive && (Y < trigererY) && (X < trigererX + SpriteData::RICK_SPRITE_WIDTH) && (X > trigererX))
		{
			AnimState = State::FALL;
		}
	}
}