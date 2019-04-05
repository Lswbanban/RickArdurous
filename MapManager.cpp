/**
* The Map Manager handle the drawing of the map
*/
#include "RickArdurous.h"
#include "MapManager.h"
#include "MapData.h"
#include "SpriteData.h"
#include "Rick.h"
#include "PickUpItem.h"
#include <avr/pgmspace.h>
#include "Input.h"

namespace MapManager
{
	// the vertical shift value in pixel that should be aplied to the camera when drawing the level
	const int CAMERA_VERTICAL_SHIFT = 6;
	const int NB_HORIZONTAL_SPRITE_PER_SCREEN = 16;
	const int NB_VERTICAL_SPRITE_PER_SCREEN = 8;
	
	// The current camera coordinate reference the top left corner of the screen portion of the level, in the big level array.
	int CameraX = 0;
	int CameraY = 0;
	
	// The target camera coordinates
	int TargetCameraX = 0;
	int TargetCameraY = 0;
	
	// This variable is used to store a temporary shift of the camera during a transition animation
	char CameraTransitionX = 0;
	char StartDrawSpriteX = 0;
	char EndDrawSpriteX = 0;
	char CameraTransitionY = 0;
	char StartDrawSpriteY = 0;
	
	// the items to currently update
	static const unsigned int MAX_UPDATABLE_ITEM_COUNT = 100;
	Item * ItemsToUpdate[MAX_UPDATABLE_ITEM_COUNT];
	unsigned char ItemsToUpdateCount = 0;
	
	// debug draw state
	unsigned char DebugDrawStep = 255;
	
	void UpdateItems(Item::UpdateStep updateStep, Item::PropertyFlags itemPropertyFlags);
	void AnimateCameraTransition();
	int GetCameraSpeed(int step, int subStep);
	void Draw(unsigned char minSpriteIndex, unsigned char maxSpriteIndex, unsigned char rickFeetOnScreen);
	
	int GetCameraTransitionMoveY() { return CameraTransitionY; }
}

void MapManager::AddItem(Item * item)
{
	if (ItemsToUpdateCount < MAX_UPDATABLE_ITEM_COUNT)
		ItemsToUpdate[ItemsToUpdateCount++] = item;
}

void MapManager::RemoveItem(Item * item)
{
	for (int i = 0; i < ItemsToUpdateCount; ++i)
		if (ItemsToUpdate[i] == item)
		{
			// decrease the item count
			ItemsToUpdateCount--;
			// if the array is not empty, move the last item to the empty place
			ItemsToUpdate[i] = ItemsToUpdate[ItemsToUpdateCount];
			// exit the loop when we have found and removed the item
			break;
		}
}

#include "BulletCrate.h"
#include "ArrowLauncher.h"
BulletCrate	dc2(60, 50);
ArrowLauncher al(9, 52, 52, 0 /*Item::PropertyFlags::MIRROR_X*/);

void MapManager::Init()
{
	MapManager::AddItem(&dc2);
	//MapManager::AddItem(&al);
}

void MapManager::UpdateItems(Item::UpdateStep updateStep, Item::PropertyFlags itemPropertyFlags)
{
	// debug early exit
	if (updateStep > DebugDrawStep)
		return;
	
	for (int i = 0; i < ItemsToUpdateCount; i++)
		if (ItemsToUpdate[i]->IsPropertySet(itemPropertyFlags))
			if (ItemsToUpdate[i]->Update(updateStep))
				i--;
}

void MapManager::Update()
{
	// debug code
	if (Input::IsDown(B_BUTTON) && Input::IsJustPressed(UP_BUTTON))
		DebugDrawStep++;
	if (Input::IsDown(B_BUTTON) && Input::IsJustPressed(DOWN_BUTTON))
		DebugDrawStep--;
	
	// update the input of the main character
	Rick::UpdateInput();
	
	// update the lethal entities
	MapManager::UpdateItems(Item::UpdateStep::DRAW_LETHAL, Item::PropertyFlags::LETHAL);
	
	// check the lethal collision after drawing the lethal items
	Rick::CheckLethalCollision();
	
	// call the function to check the static collision for the items that need it
	MapManager::UpdateItems(Item::UpdateStep::ERASE_BULLET, Item::PropertyFlags::BULLET);

	// get the position of the feet of rick in screen coordinate
	unsigned char rickFeetOnScreen = Rick::GetFeetYOnScreen();
	
	// animate the camera and draw the static collision
	AnimateCameraTransition();
	Draw(SpriteData::BLOCK_8_8, SpriteData::PLATFORM, rickFeetOnScreen);

	// check the collision with the walls, floor and ceilling after the map has been drawn
	Rick::CheckStaticCollision();

	// draw the ladders after checking the collision
	Draw(SpriteData::LADDER, SpriteData::LADDER, rickFeetOnScreen);

	// check the collision with the walls, floor and ceilling after the map has been drawn
	Rick::CheckLadderCollision();
	
	// draw the platforms after checking the collision
	Draw(SpriteData::PLATFORM, SpriteData::PLATFORM, rickFeetOnScreen);
	
	// call the function to check the static collision for the items that need it
	MapManager::UpdateItems(Item::UpdateStep::CHECK_STATIC_COLLISION, Item::PropertyFlags::STATIC_COLLISION_NEEDED);

	// draw the pickup items or all the items ignores by the ennemies like a burning dynamite
	MapManager::UpdateItems(Item::UpdateStep::DRAW_IGNORED_BY_ENEMIES, Item::PropertyFlags::IGNORED_BY_ENEMIES);

	// update the main character
	Rick::Draw();
	
	// Check if we should start a camera transition (if the main character exit the screen)
	// because NB_VERTICAL_SPRITE_PER_SCREEN=8 then the masking if equivalent to the computation
	int screenPuzzleY = CameraY & 0xFFF8; // i.e. (CameraY / NB_VERTICAL_SPRITE_PER_SCREEN) * NB_VERTICAL_SPRITE_PER_SCREEN
	if (Rick::GetBottom() < (screenPuzzleY * SpriteData::LEVEL_SPRITE_HEIGHT))
	{
		TargetCameraY = screenPuzzleY - NB_VERTICAL_SPRITE_PER_SCREEN;
	}
	else
	{
		int nextScreenPuzzleY = screenPuzzleY + NB_VERTICAL_SPRITE_PER_SCREEN;
		if (Rick::GetTop() >= (nextScreenPuzzleY * SpriteData::LEVEL_SPRITE_HEIGHT))
		{
			TargetCameraY = nextScreenPuzzleY;
		}
		else
		{
			int screenPuzzleX = CameraX & 0xFFF0; // i.e. (CameraX / NB_HORIZONTAL_SPRITE_PER_SCREEN) * NB_HORIZONTAL_SPRITE_PER_SCREEN
			if (Rick::GetRight() < (screenPuzzleX * SpriteData::LEVEL_SPRITE_WIDTH))
			{
				TargetCameraX = screenPuzzleX - NB_HORIZONTAL_SPRITE_PER_SCREEN;
			}
			else
			{
				int nextScreenPuzzleX = screenPuzzleX + NB_HORIZONTAL_SPRITE_PER_SCREEN;
				if (Rick::GetLeft() >= (nextScreenPuzzleX * SpriteData::LEVEL_SPRITE_WIDTH))
				{
					TargetCameraX = nextScreenPuzzleX;
				}
			}
		}
	}
}

int MapManager::GetXOnScreen(int worldX)
{
	return worldX - (CameraX * SpriteData::LEVEL_SPRITE_WIDTH) - CameraTransitionX;
}

int MapManager::GetYOnScreen(int worldY)
{
	return worldY - (CameraY * SpriteData::LEVEL_SPRITE_HEIGHT) - CameraTransitionY;
}

/**
 * @param step the current step in the scrolling between 0 and 8
 * @param subStep the current subStep bewteen 0 and 7
 */
int MapManager::GetCameraSpeed(int step, int subStep)
{
	// check if we need to move every frame or not
	if (step > 1)
	{
		if (step > 8)
			step = 8;
		// this array return the number of pixel the camera should move this frame
		char speed[] = { 1, 1, 1, 2, 2, 3, 4, 4, 4 };
		return speed[step];
	}
	else
	{
		// use an array to declare the number of frame to wait
		char frame[] = { 1, 2, 3, 4 };
		// check if we need to wait or if we can advance the camera transition
		if (arduboy.everyXFrames(frame[subStep >> 1]))
			return 1;
		else
			return 0;
	}
}

/**
 * this function check if there's difference between the current position of the camera
 * and the target position, and animate the camera position to reach the target
 */
void MapManager::AnimateCameraTransition()
{
	int xDiff = TargetCameraX - CameraX;
	if (xDiff > 0)
	{
		CameraTransitionX += GetCameraSpeed(xDiff, CameraTransitionX);
		StartDrawSpriteX = 0;
		EndDrawSpriteX = 1;
		if (CameraTransitionX >= SpriteData::LEVEL_SPRITE_WIDTH)
		{
			CameraTransitionX -= SpriteData::LEVEL_SPRITE_WIDTH;
			CameraX++;
		}
	}
	else if (xDiff < 0)
	{
		CameraTransitionX -= GetCameraSpeed(-xDiff, -CameraTransitionX);
		StartDrawSpriteX = -1;
		EndDrawSpriteX = 0;
		if (CameraTransitionX <= -SpriteData::LEVEL_SPRITE_WIDTH)
		{
			CameraTransitionX += SpriteData::LEVEL_SPRITE_WIDTH;
			CameraX--;
		}
	}
	else
	{
		StartDrawSpriteX = 0;
		EndDrawSpriteX = 0;
	}
	
	int yDiff = TargetCameraY - CameraY;
	if (yDiff > 0)
	{
		CameraTransitionY += GetCameraSpeed(yDiff, CameraTransitionY);
		StartDrawSpriteY = 0;
		if (CameraTransitionY >= SpriteData::LEVEL_SPRITE_HEIGHT)
		{
			CameraTransitionY -= SpriteData::LEVEL_SPRITE_HEIGHT;
			CameraY++;
		}
	}
	else if (yDiff < 0)
	{
		CameraTransitionY -= GetCameraSpeed(-yDiff, -CameraTransitionY);
		StartDrawSpriteY = -1;
		if (CameraTransitionY <= -SpriteData::LEVEL_SPRITE_HEIGHT)
		{
			CameraTransitionY += SpriteData::LEVEL_SPRITE_HEIGHT;
			CameraY--;
		}
	}
	else
	{
		StartDrawSpriteY = 0;
	}
}

/**
 * This function draw the map based on the current position of the camera.
 */
void MapManager::Draw(unsigned char minSpriteIndex, unsigned char maxSpriteIndex, unsigned char rickFeetOnScreen)
{
	for (int y = StartDrawSpriteY; y < NB_VERTICAL_SPRITE_PER_SCREEN; ++y)
	{
		// compute the sprite y coordinate
		int spriteY = (SpriteData::LEVEL_SPRITE_HEIGHT * y) + CAMERA_VERTICAL_SHIFT - CameraTransitionY;
		// determines if we need to draw the platforms.
		// If we are not specifically drawing the platforms (the min sprite index is not platforms),
		// then we should only draw the platforms below the feet
		// Otherwise, if we are in the drawing platform step, we only draw those above the feet,
		// since the below ones as already been drawn
		bool shouldDrawPlatforms = ((minSpriteIndex == SpriteData::BLOCK_8_8) && (spriteY > rickFeetOnScreen)) ||
									((minSpriteIndex == SpriteData::PLATFORM) && (spriteY <= rickFeetOnScreen));
		for (int x = StartDrawSpriteX; x < NB_HORIZONTAL_SPRITE_PER_SCREEN + EndDrawSpriteX; ++x)
		{
			unsigned char spriteId = pgm_read_byte(&(Level[y + CameraY][x + CameraX]));
			// special case for the mix of ladder and platform, draw either a platform or a ladder depending on the drawing state
			if (spriteId == SpriteData::PLATFORM_WITH_LADDER)
			{
				if (minSpriteIndex == SpriteData::LADDER)
					spriteId = SpriteData::LADDER;
				else
					spriteId = SpriteData::PLATFORM;
			}
			// draw the sprite if we need to
			if ((spriteId >= minSpriteIndex) && (spriteId <= maxSpriteIndex) &&
				((spriteId != SpriteData::PLATFORM) || shouldDrawPlatforms))
				arduboy.drawBitmap(SpriteData::LEVEL_SPRITE_WIDTH * x - CameraTransitionX,
					spriteY,
					SpriteData::Walls[spriteId],
					SpriteData::LEVEL_SPRITE_WIDTH, SpriteData::LEVEL_SPRITE_HEIGHT, WHITE);
		}
	}
}
