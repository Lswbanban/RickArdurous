/**
* The Map Manager handle the drawing of the map
*/
#include "RickArdurous.h"
#include "MapManager.h"
#include "SpriteData.h"

#include <avr/pgmspace.h>

const unsigned char level[][16] PROGMEM = {
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
	{ SpriteData::STATUE_TOP, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
	{ SpriteData::STATUE_BOTTOM, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, },
	{ SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, 255, 255, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, },
	{ 0, 255, 255, 255, 255, 0, 255, 255, 0, 255, 255, 255, 255, 255, 255, 0, },
	{ 0, 255, 255, 255, 255, 0, 255, 255, 0, 255, 255, 255, 255, 255, 255, 0, },
	{ 0, 255, 255, 255, 255, 0, 255, 255, 0, 255, 255, 255, 255, 255, 255, 0, },
	{ 0, 255, 255, 255, 255, 0, 255, 255, 0, 255, 255, 255, 255, 255, 255, 0, },
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, },
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, },
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, },
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, },
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, },
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, },
};

namespace MapManager
{
	// the vertical shift value in pixel that should be aplied to the camera when drawing the level
	const int CAMERA_VERTICAL_SHIFT = 2;
	const int NB_HORIZONTAL_SPRITE_PER_SCREEN = 16;
	const int NB_VERTICAL_SPRITE_PER_SCREEN = 9;
	
	// the sprite width and height in pixel
	const int LEVEL_SPRITE_WIDTH = 8;
	const int LEVEL_SPRITE_HEIGHT = 8;
	
	// The current camera coordinate reference the top left corner of the screen portion of the level, in the big level array.
	int CameraX = 0;
	int CameraY = 0;
	
	// The target camera coordinates
	int TargetCameraX = 0;
	int TargetCameraY = 0;
	
	// This variable is used to store a temporary shift of the camera during a transition animation
	char CameraTransition = 0;
	
	void AnimateCameraTransition();
	void Draw();
}

void MapManager::Update()
{
	// debug code
	if (arduboy.pressed(DOWN_BUTTON))
		TargetCameraY = 8;
	if (arduboy.pressed(UP_BUTTON))
		TargetCameraY = 0;
	
	AnimateCameraTransition();
	Draw();
}

// this function check if there's difference between the current position of the camera
// and the target position, and animate the camera position to reach the target
void MapManager::AnimateCameraTransition()
{
	int xDiff = TargetCameraX - CameraX;
	int yDiff = TargetCameraY - CameraY;
	if (xDiff > 0)
	{
		CameraTransition++;
		if (CameraTransition == LEVEL_SPRITE_WIDTH)
		{
			CameraTransition = 0;
			CameraX++;
		}
	}
	else if (xDiff < 0)
	{
		CameraTransition--;
		if (CameraTransition == -LEVEL_SPRITE_WIDTH)
		{
			CameraTransition = 0;
			CameraX--;
		}
	}
	else if (yDiff > 0)
	{
		CameraTransition++;
		if (CameraTransition == LEVEL_SPRITE_HEIGHT)
		{
			CameraTransition = 0;
			CameraY++;
		}
	}
	else if (yDiff < 0)
	{
		CameraTransition--;
		if (CameraTransition == -LEVEL_SPRITE_HEIGHT)
		{
			CameraTransition = 0;
			CameraY--;
		}
	}
}

// This function draw the map based on the current position of the camera.
void MapManager::Draw()
{
	for (int y = 0; y < NB_VERTICAL_SPRITE_PER_SCREEN; ++y)
		for (int x = 0; x < NB_HORIZONTAL_SPRITE_PER_SCREEN; ++x)
		{
			unsigned char spriteId = pgm_read_byte(&(level[y + CameraY][x + CameraX]));
			if (spriteId != SpriteData::NOTHING)
				arduboy.drawBitmap(LEVEL_SPRITE_WIDTH * x,
					(LEVEL_SPRITE_HEIGHT * y) - CAMERA_VERTICAL_SHIFT,
					SpriteData::Walls[spriteId],
					LEVEL_SPRITE_WIDTH, LEVEL_SPRITE_HEIGHT, WHITE);
		}
}