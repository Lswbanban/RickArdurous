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

/**
 * Make this bullet alive, and start moving from the specified position in the specified direction
 * @param the x position, of the muzzle of the gun, not including the pixel of the gun (it should be the free pixel just after the gun)
 * @param the y position of the muzzle of the gun
 * @param isMovingToLeft if true, then the bullet will move to the left of the screen, otherwise to the right.
 */
void Bullet::Fire(int x, int y, bool isMovingToLeft)
{
	// make the bullet alive and lethal
	SetProperty(Item::PropertyFlags::ALIVE | Item::PropertyFlags::LETHAL);
	// set the starting position and orienatation
	if (isMovingToLeft)
	{
		SetProperty(Item::PropertyFlags::MIRROR_X);
		X = x - BULLET_WIDTH;
	}
	else
	{
		X = x;
	}
	Y = y;
	// add myself to the map manager in order to be updated
	MapManager::AddItem(this);
}

unsigned char Bullet::GetBulletRayCastStartX()
{
	if (IsPropertySet(Item::PropertyFlags::MIRROR_X))
		return X - BULLET_SPEED;
	else
		return X;
}

void Bullet::DrawBulletRay(unsigned char color)
{
	// draw the line of the ray cast
	arduboy.drawFastHLine(GetBulletRayCastStartX(), Y, BULLET_RAY_CAST_LENGTH, color);
}

bool Bullet::ImpactBulletFound()
{
	// get the ray cast positions
	unsigned char startX = GetBulletRayCastStartX();
	// iterate on the frame buffer to chack if any pixel is set
	for (int i = 0; i < BULLET_RAY_CAST_LENGTH; ++i)
		if (arduboy.getPixel(startX + i, Y) == WHITE)
			{
				// prepare the X and Y position for the sparks animation
				X = startX + i - (SpriteData::SPARKS_SPRITE_WIDTH >> 1);
				Y -= (SpriteData::SPARKS_SPRITE_HEIGHT >> 1);
				return true;
			}
	// no collision found
	return false;
}

bool Bullet::Update(UpdateStep step)
{
	// declare a flag to know when the bullet was removed
	bool wasBulletRemovedThatFrame = false;
	
	switch (step)
	{
		case UpdateStep::DRAW_LETHAL:
			// draw a line along the whole move of the bullet
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
				DrawBulletRay(WHITE);
			break;

		case UpdateStep::ERASE_BULLET:
			// erase the line along the whole move of the bullet
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
				DrawBulletRay(BLACK);
			break;
			
		case UpdateStep::CHECK_STATIC_COLLISION:
		{
			// draw the bullet or the sparks depending if the bullet is alive or not
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				// check if the bullet collided on the static collision along its movement
				if (!ImpactBulletFound())
				{
					// no collision found, so move the bullet according to its direction
					if (IsPropertySet(Item::PropertyFlags::MIRROR_X))
						X -= BULLET_SPEED;
					else
						X += BULLET_SPEED;
				
					// draw the bullet
					arduboy.drawFastHLine(X, Y, BULLET_WIDTH, WHITE);
					
					// if the bullet is outside the screen, kill it immediately without playing sparks
					if ((X < 0) || (X >= WIDTH))
					{
						ClearProperty(Item::PropertyFlags::ALIVE | Item::PropertyFlags::LETHAL);
						MapManager::RemoveItem(this);
						wasBulletRemovedThatFrame = true;
					}
				}
				else
				{
					// the bullet hit the wall, so kill it, and reset the sparks animation frame id
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
					// we reach the end of the sparks animation, so remove this bullet from the manager
					MapManager::RemoveItem(this);
					wasBulletRemovedThatFrame = true;
				}
			}
			break;
		}
	}
	// return the result
	return wasBulletRemovedThatFrame;
}
