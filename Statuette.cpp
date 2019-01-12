/*
 * Implement the logic and drawing of the statuette bonus
*/

#include "RickArdurous.h"
#include "Statuette.h"
#include "SpriteData.h"
#include "Rick.h"

Statuette::Statuette(int startX, int startY) : PickUpItem(startX, startY, Item::PropertyFlags::IGNORED_BY_ENEMIES)
{
};

bool Statuette::Update(UpdateStep step)
{
	if (IsPropertySet(Item::PropertyFlags::IGNORED_BY_ENEMIES))
	{
		// draw the statuette
		arduboy.drawBitmap(X, Y, SpriteData::Statue, SpriteData::STATUE_SPRITE_WIDTH, SpriteData::STATUE_SPRITE_HEIGHT, WHITE);
		
		// ask the main character to check collision with me
		Rick::CheckCollisionWithPickUp(this);

		// draw the shiny star
		UpdateShineStar(-2, 3, -2, 4);
	}
	return false;
}

void Statuette::PickUp()
{
	ClearProperty(Item::PropertyFlags::IGNORED_BY_ENEMIES);
	Rick::StatuetteCount++;
}