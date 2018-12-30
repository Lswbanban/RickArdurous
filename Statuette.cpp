/*
 * Implement the logic and drawing of lethal spikes
*/

#include "RickArdurous.h"
#include "Statuette.h"
#include "SpriteData.h"

Statuette::Statuette(int startX, int startY) : Item(startX, startY)
{
};

void Statuette::Update()
{
	if (AnimFrameId == -1)
	{
		// check if we need to start a shining star animation
		if (arduboy.everyXFrames(PAUSE_TIME))
		{
			AnimFrameId = 0;
			ShineStarShiftX = random(-2,3);
			ShineStarShiftY = random(-1,3);
		}
	}
	else
	{
		if (arduboy.everyXFrames(ANIM_SPEED))
		{
			AnimFrameId += AnimDirection;
			if ((AnimFrameId == -1) || (AnimFrameId == SpriteData::SHINE_STAR_SPRITE_FRAME_COUNT - 1))
				AnimDirection = -AnimDirection;
		}
	}
	
	arduboy.drawBitmap(X, Y, SpriteData::Statue, SpriteData::STATUE_SPRITE_WIDTH, SpriteData::STATUE_SPRITE_HEIGHT, WHITE);
	if (AnimFrameId > -1)
		arduboy.drawBitmap(X + ShineStarShiftX, Y + ShineStarShiftY, SpriteData::ShineStar[AnimFrameId], SpriteData::SHINE_STAR_SPRITE_WIDTH, SpriteData::SHINE_STAR_SPRITE_HEIGHT, INVERT);
}