/*
 * Implement the logic and drawing of lethal spikes
*/

#include "RickArdurous.h"
#include "Statuette.h"
#include "SpriteData.h"

Statuette::Statuette(int startX, int startY) : Item(startX, startY, Item::PropertyFlags::NONE)
{
};

void Statuette::Update()
{
	if (AnimFrameId == -1)
	{
		// check if we need to start a shining star animation
		if (arduboy.everyXFrames(PauseTime))
		{
			// init the shining star animation id
			AnimFrameId = 0;
			
			// draw a random position for the shinning star
			// first choose the vertical position.
			ShineStarShiftY = random(-2,4);
			// If the y position is on top, choose a free x position,
			// otherwise we choose a x position on one of the two side of the statuette
			if (ShineStarShiftY == -2)
			{
				ShineStarShiftX = random(-2,3);
			}
			else
			{
				ShineStarShiftX = random(0,2);
				if (ShineStarShiftX == 0)
					ShineStarShiftX = -3;
				else
					ShineStarShiftX = 3;
			}
			
			// choose a random next pause time
			PauseTime = random(MIN_PAUSE_TIMES, MAX_PAUSE_TIMES);
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
	
	// draw the statuette and the shinning star if any
	arduboy.drawBitmap(X, Y, SpriteData::Statue, SpriteData::STATUE_SPRITE_WIDTH, SpriteData::STATUE_SPRITE_HEIGHT, WHITE);
	if (AnimFrameId > -1)
		arduboy.drawBitmap(X + ShineStarShiftX, Y + ShineStarShiftY, SpriteData::ShineStar[AnimFrameId], SpriteData::SHINE_STAR_SPRITE_WIDTH, SpriteData::SHINE_STAR_SPRITE_HEIGHT, INVERT);
}