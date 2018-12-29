#ifndef _SPRITE_DATA_H_
#define _SPRITE_DATA_H_

namespace SpriteData
{
	enum WallId
	{
		BLOCK_8_8 = 0,
		BLOCK_16_8_LEFT,
		BLOCK_16_8_RIGHT,
		STATUE_BOTTOM,
		STATUE_TOP,
		NOTHING = 255,
	};
	
	// sprite of the walls
	// the sprite width and height in pixel
	const int LEVEL_SPRITE_WIDTH = 8;
	const int LEVEL_SPRITE_HEIGHT = 8;
	extern const unsigned char Walls[][LEVEL_SPRITE_WIDTH * (LEVEL_SPRITE_HEIGHT / 8)];
	
	// sprite of the main character
	const int RICK_SPRITE_WIDTH = 9;
	const int RICK_SPRITE_HEIGHT = 16;
	extern const unsigned char Rick[][RICK_SPRITE_WIDTH * (RICK_SPRITE_HEIGHT / 8)];
}

#endif