/*
 * Implement the logic and drawing of lethal spikes
*/

#include "RickArdurous.h"
#include "Spike.h"
#include "SpriteData.h"

Spike::Spike(int startX, int startY, unsigned char flag) : Item(startX, startY, flag | Item::PropertyFlags::LETHAL)
{
}

bool Spike::Update()
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
	
	if (IsPropertySet(PropertyFlags::HORIZONTAL_SPIKE))
	{
		arduboy.drawBitmapExtended(X, Y, SpriteData::SpikeHorizontal[AnimFrameId], SpriteData::SPIKE_HORIZONTAL_SPRITE_WIDTH, SpriteData::SPIKE_HORIZONTAL_SPRITE_HEIGHT, WHITE, IsPropertySet(PropertyFlags::MIRROR_X));
	}
	else
	{
		arduboy.drawBitmapExtended(X, Y, SpriteData::SpikeVertical[AnimFrameId], SpriteData::SPIKE_VERTICAL_SPRITE_WIDTH, SpriteData::SPIKE_VERTICAL_SPRITE_HEIGHT, WHITE, IsPropertySet(PropertyFlags::MIRROR_X));
	}
	
	return false;
}