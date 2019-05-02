/*
 * Implement the logic and drawing of the dynamite
*/

#include "RickArdurous.h"
#include "Dynamite.h"
#include "SpriteData.h"
#include "MapManager.h"

Dynamite::Dynamite() : Item(0, 0, Item::ItemType::IGNORED_BY_ENEMIES, Item::PropertyFlags::NONE)
{
};

Dynamite::Dynamite(int startX, int startY) : Item(startX, startY, Item::ItemType::IGNORED_BY_ENEMIES, Item::PropertyFlags::NONE)
{
};

void Dynamite::LightUp(int x, int y)
{
	X = x;
	Y = y;
	DynamiteAnimFrameId = 0;
	SparksAnimFrameId = 0;
	SetType(Item::ItemType::IGNORED_BY_ENEMIES);
	SetProperty(Item::PropertyFlags::ALIVE);
	// add myself to the map manager in order to be updated
	MapManager::AddItem(this);
}

bool Dynamite::Update(UpdateStep step)
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
			SetType(Item::ItemType::LETHAL);
			// we are in explosion part, so stop the sparks
			SparksAnimFrameId = -1;
			// increase the dynamite frame id, at different speed depending if it is the fuse consuming part or the explosion
			if (arduboy.everyXFrames(EXPLOSION_ANIM_SPEED))
				DynamiteAnimFrameId++;
			// if we reach the end of the dynamite explosion, disable the dynamite
			if (DynamiteAnimFrameId == SpriteData::DYNAMITE_SPRITE_FRAME_COUNT)
			{
				DynamiteAnimFrameId = -1;
				ClearProperty(Item::PropertyFlags::ALIVE);
				MapManager::RemoveItem(this);
			}
		}
	}
	
	// draw the dynamite or explosion
	int yOnScreen = MapManager::GetYOnScreen(Y);
	if (DynamiteAnimFrameId > -1)
		arduboy.drawBitmap(MapManager::GetXOnScreen(X), yOnScreen, SpriteData::Dynamite[DynamiteAnimFrameId], SpriteData::DYNAMITE_SPRITE_WIDTH, SpriteData::DYNAMITE_SPRITE_HEIGHT, WHITE);
	// draw the sparks if any
	if (SparksAnimFrameId > -1)
		arduboy.drawBitmap(MapManager::GetXOnScreen(X + (DynamiteAnimFrameId>>1)), yOnScreen, SpriteData::Sparks[SparksAnimFrameId], SpriteData::SPARKS_SPRITE_WIDTH, SpriteData::SPARKS_SPRITE_HEIGHT, INVERT);
	
	return !IsPropertySet(Item::PropertyFlags::ALIVE);
}