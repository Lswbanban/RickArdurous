/*
 * This file implement the base class for all the pickup items
*/

#include "RickArdurous.h"
#include "SpriteData.h"
#include "PickUpItem.h"
#include "MapManager.h"

/**
 * Update and Draw a shiny star around the sprite of this Pickup Item according to the specified 
 * min and max values.
 * @param minX the included left border where the star can shine
 * @param maxX the excluded right border where the star can shine
 * @param minY the included top border where the star can shine
 * @param maxY the excluded bottom border where the star can shine 
 */
void PickUpItem::UpdateShineStar(char minX, char maxX, char minY, char maxY)
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
			ShineStarShiftY = random(minY, maxY);
			// If the y position is on top, choose a free x position,
			// otherwise we choose a x position on one of the two side of the statuette
			if (ShineStarShiftY == minY)
			{
				ShineStarShiftX = random(minX, maxX);
			}
			else
			{
				ShineStarShiftX = random(0,2);
				if (ShineStarShiftX == 0)
					ShineStarShiftX = minX - 1;
				else
					ShineStarShiftX = maxX;
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
	
	//draw the star if needed
	if (AnimFrameId > -1)
		arduboy.drawBitmap(MapManager::GetXOnScreen(X + ShineStarShiftX),
							MapManager::GetYOnScreen(Y + ShineStarShiftY),
							SpriteData::ShineStar[AnimFrameId],
							SpriteData::SHINE_STAR_SPRITE_WIDTH,
							SpriteData::SHINE_STAR_SPRITE_HEIGHT,
							INVERT);
}