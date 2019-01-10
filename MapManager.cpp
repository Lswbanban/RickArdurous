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
	
	void AnimateCameraTransition();
	int GetCameraSpeed(int step, int subStep);
	void Draw();
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

void MapManager::Update()
{
	// debug code
	//if (arduboy.pressed(DOWN_BUTTON))
	//	TargetCameraY = 8;
	//if (arduboy.pressed(UP_BUTTON))
	//	TargetCameraY = 0;
	
	// update the main character
	Rick::Update();

	
	// first draw the lethal items
	for (int i = 0; i < ItemsToUpdateCount; i++)
		if (ItemsToUpdate[i]->IsPropertySet(Item::PropertyFlags::LETHAL))
			if (ItemsToUpdate[i]->Update())
				i--;
	
	// check the lethal collision after drawing the lethal items
	Rick::CheckLethalCollision();
	
	// first draw the bonus items
	for (int i = 0; i < ItemsToUpdateCount; i++)
		if (ItemsToUpdate[i]->IsPropertySet(Item::PropertyFlags::PICKUP))
		{
			if (ItemsToUpdate[i]->Update())
				i--;
			Rick::CheckCollisionWithPickUp((PickUpItem*)(ItemsToUpdate[i]));
		}
	
	AnimateCameraTransition();
	Draw();
	
	// call the function to check the static collision for the items that need it
	for (int i = 0; i < ItemsToUpdateCount; i++)
		if (ItemsToUpdate[i]->IsPropertySet(Item::PropertyFlags::STATIC_COLLISION_NEEDED))
			if (ItemsToUpdate[i]->CheckStaticCollision())
				i--;

	// check the collision with the walls, floor and ceilling after the map has been drawn
	Rick::CheckStaticCollision();

	// update the main character
	Rick::Draw();
	
		// draw the non lethal items
	for (int i = 0; i < ItemsToUpdateCount; i++)
		if (!ItemsToUpdate[i]->IsPropertySet(Item::PropertyFlags::LETHAL | Item::PropertyFlags::PICKUP))
			if(ItemsToUpdate[i]->Update())
				i--;
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
		char speed[] = { 1, 1, 1, 2, 2, 3, 4, 4 };
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
void MapManager::Draw()
{
	for (int y = StartDrawSpriteY; y < NB_VERTICAL_SPRITE_PER_SCREEN; ++y)
		for (int x = StartDrawSpriteX; x < NB_HORIZONTAL_SPRITE_PER_SCREEN + EndDrawSpriteX; ++x)
		{
			unsigned char spriteId = pgm_read_byte(&(Level[y + CameraY][x + CameraX]));
			if (spriteId != SpriteData::NOTHING)
				arduboy.drawBitmap(SpriteData::LEVEL_SPRITE_WIDTH * x - CameraTransitionX,
					(SpriteData::LEVEL_SPRITE_HEIGHT * y) + CAMERA_VERTICAL_SHIFT - CameraTransitionY,
					SpriteData::Walls[spriteId],
					SpriteData::LEVEL_SPRITE_WIDTH, SpriteData::LEVEL_SPRITE_HEIGHT, WHITE);
		}
}
