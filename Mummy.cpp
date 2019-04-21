/*
 * Implement the logic and drawing of the mummy ennemies
*/

#include "RickArdurous.h"
#include "Mummy.h"
#include "SpriteData.h"
#include "Rick.h"
#include "MapManager.h"

const char WALK_ANIM_SPEED[] = { 8, 12, 6, 8 };

Mummy::Mummy(int startX, int startY) : Item(startX, startY, Item::PropertyFlags::ENEMIES | Item::PropertyFlags::STATIC_COLLISION_NEEDED)
{
	AnimFrameId = 0;
	AnimFrameCount = 0;
	SetProperty(PropertyFlags::MIRROR_X);
};

bool Mummy::Update(UpdateStep step)
{
	switch (step)
	{
		case Item::UpdateStep::DRAW_ENEMIES:
		{
			switch (AnimState)
			{
				case State::WALK:
					UpdateWalk();
					break;
				case State::FALL:
					UpdateFall();
					break;
			}
			
			// draw the statuette and check the collision with eventual lethal stuff
			int collision = Draw(WHITE);
									
			// if we have a collision, that means we hit a lethal pixel
			if (collision != 0)
			{
				ClearProperty(Item::PropertyFlags::ALIVE);
				MapManager::RemoveItem(this);
				return true;
			}
			break;
		}
		case Item::UpdateStep::CHECK_STATIC_COLLISION:
		{
			// check the ground collision
			int yUnderFeet = Y + 13;
			if (!MapManager::IsThereAnyHorizontalCollisionAt(X+1, X+7, yUnderFeet))
				AnimState = State::FALL;
			else
				AnimState = State::WALK;
			
			// check the wall collision
			bool isWalkingLeft = IsPropertySet(PropertyFlags::MIRROR_X);
			int wallX = isWalkingLeft ? X - 1 : X + SpriteData::MUMMY_SPRITE_WIDTH;
			int wallYOnScreen = MapManager::GetYOnScreen(Y);
			if (CheckPixelColumn(MapManager::GetXOnScreen(wallX), wallYOnScreen, wallYOnScreen + 12))
			{
				if (isWalkingLeft)
					ClearProperty(PropertyFlags::MIRROR_X);
				else
					SetProperty(PropertyFlags::MIRROR_X);
			}
			break;
		}
	}
	return false;
}

/**
 * Check a column of pixels at the specified x position (in screen coord) and from startY to endY (in screen coord)
 * This function will check if the specified coordinates are on screen and return false if not.
 * This function return true for the first white pixel encountered.
 */
bool Mummy::CheckPixelColumn(int xOnScreen, int startYOnScreen, int endYOnScreen)
{
	if ((xOnScreen >= 0) && (xOnScreen < WIDTH))
		for (int yOnScreen = startYOnScreen; yOnScreen <= endYOnScreen; yOnScreen++)
			if ((yOnScreen >= 0) && (yOnScreen < HEIGHT) && (arduboy.getPixel(xOnScreen, yOnScreen) == WHITE))
				return true;
	return false;
}

void Mummy::UpdateWalk()
{
	// update the animation
	AnimFrameCount++;
	if (AnimFrameCount == WALK_ANIM_SPEED[AnimFrameId])
	{
		// move the X depending on the direction
		if (IsPropertySet(PropertyFlags::MIRROR_X))
			X--;
		else
			X++;
		// go to the next frame id
		AnimFrameId++;
		AnimFrameCount = 0;
		if (AnimFrameId == 4)
			AnimFrameId = 0;
	}
}

void Mummy::UpdateFall()
{
	Y++;
}

int Mummy::Draw(unsigned char color)
{
	return arduboy.drawBitmapExtended(MapManager::GetXOnScreen(X),
									MapManager::GetYOnScreen(Y),
									SpriteData::Mummy[AnimFrameId],
									SpriteData::MUMMY_SPRITE_WIDTH, SpriteData::MUMMY_SPRITE_HEIGHT,
									color, IsPropertySet(PropertyFlags::MIRROR_X));
}