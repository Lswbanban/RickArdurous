/*
 * Implement the logic and drawing of the dynamite
*/

#include "RickArdurous.h"
#include "Dynamite.h"
#include "SpriteData.h"

Dynamite::Dynamite() : Item(0, 0, Item::PropertyFlags::NONE)
{
};

Dynamite::Dynamite(int startX, int startY) : Item(startX, startY, Item::PropertyFlags::NONE)
{
};

void Dynamite::Update()
{
	// check if the dynamite is alive
	if (DynamiteAnimFrameId > -1)
	{
		// check if we are in the consume fuse part, or the explosion part of the anim
		if (DynamiteAnimFrameId < 6)
		{
			// We are in fuse consume part, increase the dynamite frame id for consuming the fuse
			if (arduboy.everyXFrames(DYNAMITE_ANIM_SPEED))
				DynamiteAnimFrameId++;
			// increase the sparks frame id
			if (arduboy.everyXFrames(SPARKS_ANIM_SPEED))
				SparksAnimFrameId = (SparksAnimFrameId + 1) % SpriteData::SPARKS_SPRITE_FRAME_COUNT;
		}
		else
		{
			// set the lethal flag when the dynamite explode
			SetProperty(Item::PropertyFlags::LETHAL);
			// we are in explosion part, so stop the sparks
			SparksAnimFrameId = -1;
			// increase the dynamite frame id, at different speed depending if it is the fuse consuming part or the explosion
			if (arduboy.everyXFrames(EXPLOSION_ANIM_SPEED))
				DynamiteAnimFrameId++;
			// if we reach the end of the dynamite explosion, disable the dynamite
			if (DynamiteAnimFrameId == SpriteData::DYNAMITE_SPRITE_FRAME_COUNT)
				DynamiteAnimFrameId = -1;
		}
	}
	
	// draw the dynamite or explosion
	if (DynamiteAnimFrameId > -1)
		arduboy.drawBitmap(X, Y, SpriteData::Dynamite[DynamiteAnimFrameId], SpriteData::DYNAMITE_SPRITE_WIDTH, SpriteData::DYNAMITE_SPRITE_HEIGHT, WHITE);
	// draw the sparks if any
	if (SparksAnimFrameId > -1)
		arduboy.drawBitmap(X + (DynamiteAnimFrameId>>1), Y, SpriteData::Sparks[SparksAnimFrameId], SpriteData::SPARKS_SPRITE_WIDTH, SpriteData::SPARKS_SPRITE_HEIGHT, INVERT);
}