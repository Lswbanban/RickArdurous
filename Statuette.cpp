/*
 * Implement the logic and drawing of the statuette bonus
*/

#include "RickArdurous.h"
#include "Statuette.h"
#include "SpriteData.h"

Statuette::Statuette(int startX, int startY) : PickUpItem(startX, startY, Item::PropertyFlags::PICKUP)
{
};

void Statuette::Update()
{
	if (IsPropertySet(Item::PropertyFlags::PICKUP))
	{
		
		// draw the statuette
		arduboy.drawBitmap(X, Y, SpriteData::Statue, SpriteData::STATUE_SPRITE_WIDTH, SpriteData::STATUE_SPRITE_HEIGHT, WHITE);
		// draw the shiny star
		UpdateShineStar(-2, 3, -2, 4);
	}
}

void Statuette::PickUp()
{
	ClearProperty(Item::PropertyFlags::PICKUP);
}