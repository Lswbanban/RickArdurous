/*
 * Implement the logic and drawing of lethal spikes
*/

#include "RickArdurous.h"
#include "Spike.h"
#include "SpriteData.h"
#include "MapManager.h"

Spike::Spike(unsigned char flags) : Item(flags)
{
}

bool Spike::Update(UpdateStep step)
{
	if (step == UpdateStep::DRAW_LETHAL)
	{
		if (AnimFrameId == 0)
		{
			if (arduboy.everyXFrames(PAUSE_TIME))
				AnimFrameId = 1;
		}
		else
		{
			if (arduboy.everyXFrames(ANIM_SPEED))
				AnimFrameId = (AnimFrameId + 1) % SpriteData::SPIKE_SPRITE_FRAME_COUNT;
		}
		
		// special spikes are horizontal
		int xOnScreen = MapManager::GetXOnScreen(X);
		int yOnScreen = MapManager::GetYOnScreen(Y);
		if (IsPropertySet(PropertyFlags::SPECIAL))
		{
			arduboy.drawBitmapExtended(xOnScreen, yOnScreen, SpriteData::SpikeHorizontal[AnimFrameId], SpriteData::SPIKE_HORIZONTAL_SPRITE_WIDTH, SpriteData::SPIKE_HORIZONTAL_SPRITE_HEIGHT, WHITE, IsPropertySet(PropertyFlags::MIRROR_X));
		}
		else
		{
			arduboy.drawBitmapExtended(xOnScreen, yOnScreen, SpriteData::SpikeVertical[AnimFrameId], SpriteData::SPIKE_VERTICAL_SPRITE_WIDTH, SpriteData::SPIKE_VERTICAL_SPRITE_HEIGHT, WHITE, IsPropertySet(PropertyFlags::MIRROR_X));
		}
	}
	return false;
}