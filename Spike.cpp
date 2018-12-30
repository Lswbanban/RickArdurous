/*
 * Implement the logic and drawing of lethal spikes
*/

#include "RickArdurous.h"
#include "Spike.h"
#include "SpriteData.h"

Spike::Spike(int startX, int startY, VisualType type) : Item(startX, startY)
{
	Type = type;
};

void Spike::Update()
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
	
	switch (Type)
	{
		case VisualType::HORIZONTAL:
			arduboy.drawBitmap(X, Y, SpriteData::SpikeHorizontal[AnimFrameId], SpriteData::SPIKE_HORIZONTAL_SPRITE_WIDTH, SpriteData::SPIKE_HORIZONTAL_SPRITE_HEIGHT, WHITE);
			break;
		case VisualType::VERTICAL_RIGHT:
			arduboy.drawBitmap(X, Y, SpriteData::SpikeVertical[AnimFrameId], SpriteData::SPIKE_VERTICAL_SPRITE_WIDTH, SpriteData::SPIKE_VERTICAL_SPRITE_HEIGHT, WHITE);
			break;
		case VisualType::VERTICAL_LEFT:
			arduboy.drawBitmapExtended(X, Y, SpriteData::SpikeVertical[AnimFrameId], SpriteData::SPIKE_VERTICAL_SPRITE_WIDTH, SpriteData::SPIKE_VERTICAL_SPRITE_HEIGHT, WHITE, true);
			break;
	}
}