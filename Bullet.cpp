/*
 * Implement the logic and drawing of the bullet
*/

#include "RickArdurous.h"
#include "Bullet.h"
#include "MapManager.h"
#include "SpriteData.h"

Bullet::Bullet() : Item(0, 0, Item::PropertyFlags::BULLET | Item::PropertyFlags::STATIC_COLLISION_NEEDED)
{
}

Bullet::Bullet(int startX, int startY) : Item(startX, startY, Item::PropertyFlags::BULLET | Item::PropertyFlags::STATIC_COLLISION_NEEDED)
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

void Bullet::GetStartAndEndX(unsigned char &startX, unsigned char &endX)
{
	if (IsPropertySet(Item::PropertyFlags::MIRROR_X))
	{
		startX = X - BULLET_SPEED;
		endX = X + BULLET_WIDTH;
	}
	else
	{
		startX = X;
		endX = X + BULLET_SPEED + BULLET_WIDTH;
	}
}

void Bullet::DrawBulletRay(unsigned char color)
{
	// get the ray cast positions
	unsigned char startX;
	unsigned char endX;
	GetStartAndEndX(startX, endX);
	// draw the line of the ray cast
	arduboy.drawFastHLine(startX, Y, endX, color);
}

bool Bullet::ImpactBulletFound()
{
	// get the ray cast positions
	unsigned char startX;
	unsigned char endX;
	GetStartAndEndX(startX, endX);
	// iterate on the frame buffer to chack if any pixel is set
	for (int i = startX; i <= endX; ++i)
		if (arduboy.getPixel(i, Y) == WHITE)
			{
				X = i - (SpriteData::SPARKS_SPRITE_WIDTH >> 1);
				Y -= (SpriteData::SPARKS_SPRITE_HEIGHT >> 1);
				return true;
			}
	// no collision found
	return false;
}

bool Bullet::Update(UpdateStep step)
{
	switch (step)
	{
		case UpdateStep::DRAW_LETHAL:
			// check if the bullet is alive
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				// draw a line along the whole move of the bullet
				DrawBulletRay(WHITE);
			}
			return false;

		case UpdateStep::ERASE_BULLET:
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				// erase the line along the whole move of the bullet
				DrawBulletRay(BLACK);
			}
			return false;
			
		case UpdateStep::CHECK_STATIC_COLLISION:
		{
			// declare a flag to know when the bullet was removed
			bool wasBulletRemovedThatFrame = false;
			// draw the bullet or the sparks depending if the bullet is alive or not
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				// check if the bullet collided on the static collision along its movement
				// and move the bullet according to its direction
				if (!ImpactBulletFound())
				{
					if (IsPropertySet(Item::PropertyFlags::MIRROR_X))
						X -= BULLET_SPEED;
					else
						X += BULLET_SPEED;
				
					// draw the bullet
					arduboy.drawFastHLine(X, Y, BULLET_WIDTH, WHITE);
				}
				else
				{
					//if ((X < 0) || (X > WIDTH))
					ClearProperty(Item::PropertyFlags::ALIVE | Item::PropertyFlags::LETHAL);
					SparksAnimFrameId = 0;
				}
			}
			else
			{
				if (SparksAnimFrameId < SpriteData::SPARKS_SPRITE_FRAME_COUNT)
				{
					// draw the sparks
					arduboy.drawBitmap(X, Y, SpriteData::Sparks[SparksAnimFrameId], SpriteData::SPARKS_SPRITE_WIDTH, SpriteData::SPARKS_SPRITE_HEIGHT, INVERT);
					// increase the frame id of the sparks
					if (arduboy.everyXFrames(SPARKS_ANIM_SPEED))
						SparksAnimFrameId++;
				}
				else
				{
					MapManager::RemoveItem(this);
					wasBulletRemovedThatFrame = true;
				}
			}
			
			return wasBulletRemovedThatFrame;
		}
	}
}
