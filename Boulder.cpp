/*
 * Implement the logic and drawing of lethal spikes
*/

#include "RickArdurous.h"
#include "Boulder.h"
#include "SpriteData.h"
#include "MapManager.h"

bool Boulder::Update(UpdateStep step)
{
	if (step == UpdateStep::DRAW_LETHAL)
	{
		char movingDirection = IsPropertySet(MIRROR_X) ? -1 : 1;
		if (arduboy.everyXFrames(ANIM_SPEED))
			X += movingDirection;
		if (arduboy.everyXFrames(ANIM_ROTATION_SPEED))
		{
			AnimFrameId++;
			if (movingDirection < 0)
				AnimFrameId = (BOULDER_ROLLING_FRAME_COUNT - AnimFrameId);
			AnimFrameId %= BOULDER_ROLLING_FRAME_COUNT;
		}
		// get the coordinate on screen of the boulder
		int xOnScreen = MapManager::GetXOnScreen(X);
		int yOnScreen = MapManager::GetYOnScreen(Y);
		// draw the two halves of it
		arduboy.drawBitmapExtended(xOnScreen, yOnScreen, SpriteData::Boulder, SpriteData::BOULDER_SPRITE_WIDTH, SpriteData::BOULDER_SPRITE_HEIGHT, WHITE, false);
		arduboy.drawBitmapExtended(xOnScreen + SpriteData::BOULDER_SPRITE_WIDTH, yOnScreen, SpriteData::Boulder, SpriteData::BOULDER_SPRITE_WIDTH, SpriteData::BOULDER_SPRITE_HEIGHT, WHITE, true);
		// draw the rotating shadow
		char isShadowRight = (AnimFrameId == 0) || (AnimFrameId == 3) ? 0 : 1;
		char shadowX = xOnScreen + (2 * !isShadowRight) + (SpriteData::BOULDER_SPRITE_WIDTH * isShadowRight);
		arduboy.drawBitmapExtended(shadowX, yOnScreen + 2, SpriteData::BoulderShadow[AnimFrameId >> 1], SpriteData::BOULDER_SHADOW_SPRITE_WIDTH, SpriteData::BOULDER_SHADOW_SPRITE_HEIGHT, BLACK, isShadowRight);
	}
	return false;
}
