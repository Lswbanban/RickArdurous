/*
 * Implement the logic and drawing of the Bullet fired by Rick or an Arrow thrown by the Arrow Launcher
*/

#include "RickArdurous.h"
#include "ArrowBullet.h"
#include "MapManager.h"
#include "SpriteData.h"

ArrowBullet::ArrowBullet() : Item(0, 0, Item::PropertyFlags::NONE)
{
}

ArrowBullet::ArrowBullet(bool isArrow) : Item(0, 0, (isArrow ? PropertyFlags::SPECIAL : 0))
{
}

/**
 * Make this bullet alive, and start moving from the specified position in the specified direction
 * @param the x position, of the muzzle of the gun, not including the pixel of the gun (it should be the free pixel just after the gun)
 * @param the y position of the muzzle of the gun
 * @param isMovingToLeft if true, then the bullet will move to the left of the screen, otherwise to the right.
 */
void ArrowBullet::Fire(int x, int y, bool isMovingToLeft)
{
	// make the bullet alive
	SetProperty(Item::PropertyFlags::ALIVE);
	// set the starting position and orienatation
	if (isMovingToLeft)
	{
		SetProperty(Item::PropertyFlags::MIRROR_X);
		X = x - GetWidth();
	}
	else
	{
		X = x;
	}
	Y = y;
	// for the first frame we set the bullet speed to zero
	CurrentBulletSpeed = 0;
	// add myself to the map manager in order to be updated
	MapManager::AddItem(this);
}

unsigned char ArrowBullet::GetWidth()
{
	return IsPropertySet(Item::PropertyFlags::SPECIAL) ? ARROW_WIDTH : BULLET_WIDTH;
}

/**
 * Return the start x position of the bullet in world coordinates
 */
int ArrowBullet::GetBulletRayCastStartX()
{
	if (IsPropertySet(Item::PropertyFlags::MIRROR_X))
		return X - CurrentBulletSpeed;
	else
		return X;
}

/**
 * Draw a full ray of the bullet with the specified color.
 * The ray length equals to the bullet length + the speed of the bullet.
 */
void ArrowBullet::DrawBulletRay(unsigned char color)
{
	// draw the line of the ray cast
	arduboy.drawFastHLine(MapManager::GetXOnScreen(GetBulletRayCastStartX()),
							MapManager::GetYOnScreen(Y), CurrentBulletSpeed + GetWidth(), color);
}

/**
 * Search for a pixel of the specified color along the bullet ray cast.
 * If that pixel of that color is found, return the world position of that pixel,
 * otherwise return the specific value NO_PIXEL_FOUND (60000)
 */
int ArrowBullet::SearchForPixelColorAlongBulletRay(unsigned int color)
{
	// get the ray cast positions
	int worldStartX = GetBulletRayCastStartX();
	int startXOnScreen = MapManager::GetXOnScreen(worldStartX);
	int yOnScreen = MapManager::GetYOnScreen(Y);
	// iterate on the frame buffer to check if any pixel is set
	for (int i = 0; i < CurrentBulletSpeed + GetWidth(); ++i)
		if (arduboy.getPixel(startXOnScreen + i, yOnScreen) == color)
				return (worldStartX + i - (SpriteData::SPARKS_SPRITE_WIDTH >> 1));
	// no collision found
	return NO_PIXEL_FOUND;
}

void ArrowBullet::KillBulletWithoutSparks()
{
	ClearProperty(Item::PropertyFlags::ALIVE);
}

bool ArrowBullet::Update(UpdateStep step)
{
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
			{
				// before erasing first check if some pixels of the ray cast has been erased (which means the bullet has hit something)
				bool shouldKillBullet = (SearchForPixelColorAlongBulletRay(BLACK) != NO_PIXEL_FOUND);
				if (shouldKillBullet)
					KillBulletWithoutSparks();
				// now erase the bullet ray
				DrawBulletRay(BLACK);
				// return the value depending if the bullet was killed
				return shouldKillBullet;
			}
			break;
			
		case UpdateStep::CHECK_STATIC_COLLISION:
		{
			// draw the bullet or the sparks depending if the bullet is alive or not
			if (IsPropertySet(Item::PropertyFlags::ALIVE))
			{
				// first check the collition and get the impact position if any
				int impactPosition = SearchForPixelColorAlongBulletRay(WHITE);
				
				// move the bullet X according to its direction
				if (IsPropertySet(Item::PropertyFlags::MIRROR_X))
					X -= CurrentBulletSpeed;
				else
					X += CurrentBulletSpeed;
				
				// from the second frame set the current bullet speed to its nominal value
				CurrentBulletSpeed = IsPropertySet(Item::PropertyFlags::SPECIAL) ? ARROW_SPEED : BULLET_SPEED;
				
				// draw the bullet
				int xOnScreen = MapManager::GetXOnScreen(X);
				arduboy.drawFastHLine(xOnScreen, MapManager::GetYOnScreen(Y), GetWidth(), WHITE);
				
				// check if the bullet collided on the static collision along its movement, if yes prepare the sparks fx for the next frame
				if (impactPosition != NO_PIXEL_FOUND)
				{
					// the bullet hit the wall, so kill it
					ClearProperty(Item::PropertyFlags::ALIVE);
					// init the postion for the sparks sprite, and reset the sparks animation frame id
					X = impactPosition;
					Y -= (SpriteData::SPARKS_SPRITE_HEIGHT >> 1);
					SparksAnimFrameId = 0;
				}
				else if ((xOnScreen < 0) || (xOnScreen >= WIDTH))
				{
					// if the bullet is outside the screen, kill it immediately without playing sparks
					KillBulletWithoutSparks();
					return true;
				}
			}
			else
			{
				if (SparksAnimFrameId < SpriteData::SPARKS_SPRITE_FRAME_COUNT)
				{
					// draw the sparks
					arduboy.drawBitmap(MapManager::GetXOnScreen(X), MapManager::GetYOnScreen(Y), SpriteData::Sparks[SparksAnimFrameId], SpriteData::SPARKS_SPRITE_WIDTH, SpriteData::SPARKS_SPRITE_HEIGHT, INVERT);
					// increase the frame id of the sparks
					if (arduboy.everyXFrames(SPARKS_ANIM_SPEED))
						SparksAnimFrameId++;
				}
				else
				{
					// we reach the end of the sparks animation, so return true to be removed from the manager
					return true;
				}
			}
			break;
		}
	}
	// return false by default
	return false;
}
