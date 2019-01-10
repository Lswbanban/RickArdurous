/*
 * Implement the logic and drawing of the bullet
*/

#include "RickArdurous.h"
#include "Bullet.h"
#include "MapManager.h"

Bullet::Bullet() : Item(0, 0, Item::PropertyFlags::STATIC_COLLISION_NEEDED)
{
}

Bullet::Bullet(int startX, int startY) : Item(startX, startY, Item::PropertyFlags::STATIC_COLLISION_NEEDED)
{
}

void Bullet::Fire(int x, int y, bool isMovingToLeft)
{
	X = x;
	Y = y;
	SetProperty(Item::PropertyFlags::ALIVE | Item::PropertyFlags::LETHAL);
	if (isMovingToLeft)
		SetProperty(Item::PropertyFlags::MIRROR_X);
	// add myself to the map manager in order to be updated
	MapManager::AddItem(this);
}

void Bullet::Update()
{
	// check if the bullet is alive
	if (IsPropertySet(Item::PropertyFlags::ALIVE))
	{
		// move the bullet
		if (IsPropertySet(Item::PropertyFlags::MIRROR_X))
			X -= BULLET_SPEED;
		else
			X += BULLET_SPEED;
		
		// draw the bullet
		arduboy.drawFastHLine(X, Y, BULLET_WIDTH, WHITE);
	}
}

void Bullet::CheckStaticCollision()
{
	if ((X < 0) || (X > WIDTH))
	{
		ClearProperty(Item::PropertyFlags::ALIVE | Item::PropertyFlags::LETHAL);
		MapManager::RemoveItem(this);
	}
}
