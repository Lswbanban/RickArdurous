/**
* The Map Manager handle the drawing of the map
*/
#include "RickArdurous.h"
#include "MapManager.h"
#include "SpriteData.h"

#include <avr/pgmspace.h>

const unsigned char level[][32] PROGMEM = {
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ SpriteData::STATUE_TOP, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ SpriteData::STATUE_BOTTOM, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, 255, 255, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ 0, 255, 255, 255, 255, 0, 255, 255, 0, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ 0, 255, 255, 255, 255, 0, 255, 255, 0, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ 0, 255, 255, 255, 255, 0, 255, 255, 0, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ 0, 255, 255, 255, 255, 0, 255, 255, 0, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
};

namespace MapManager
{
	// the vertical shift value in pixel that should be aplied to the camera when drawing the level
	const int CAMERA_VERTICAL_SHIFT = 2;
	const int NB_HORIZONTAL_SPRITE_PER_SCREEN = 16;
	const int NB_VERTICAL_SPRITE_PER_SCREEN = 9;
	
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
	
	void AnimateCameraTransition();
	int GetCameraSpeed(int step, int subStep);
	void Draw();
}

void MapManager::Update()
{
	// debug code
	if (arduboy.pressed(DOWN_BUTTON))
		TargetCameraY = 8;
	if (arduboy.pressed(UP_BUTTON))
		TargetCameraY = 0;
	/*if (arduboy.pressed(LEFT_BUTTON))
		TargetCameraX = 0;
	if (arduboy.pressed(RIGHT_BUTTON))
		TargetCameraX = 16;
	*/
	
	AnimateCameraTransition();
	Draw();
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

// this function check if there's difference between the current position of the camera
// and the target position, and animate the camera position to reach the target
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

// This function draw the map based on the current position of the camera.
void MapManager::Draw()
{
	for (int y = StartDrawSpriteY; y < NB_VERTICAL_SPRITE_PER_SCREEN; ++y)
		for (int x = StartDrawSpriteX; x < NB_HORIZONTAL_SPRITE_PER_SCREEN + EndDrawSpriteX; ++x)
		{
			unsigned char spriteId = pgm_read_byte(&(level[y + CameraY][x + CameraX]));
			if (spriteId != SpriteData::NOTHING)
				arduboy.drawBitmap(SpriteData::LEVEL_SPRITE_WIDTH * x - CameraTransitionX,
					(SpriteData::LEVEL_SPRITE_HEIGHT * y) - CAMERA_VERTICAL_SHIFT - CameraTransitionY,
					SpriteData::Walls[spriteId],
					SpriteData::LEVEL_SPRITE_WIDTH, SpriteData::LEVEL_SPRITE_HEIGHT, WHITE);
		}
}