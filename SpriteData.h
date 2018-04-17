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
	
	extern const unsigned char Walls[][8];
}

#endif