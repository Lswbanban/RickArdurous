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
	
	enum RickAnimFrameId
	{
		IDLE = 0,
		WALK_START = 0,
		WALK_END = 3,
		FIRE_START,
		FIRE_END,
		POSE_DYNAMITE_START,
		POSE_DYNAMITE_END,
	};
	
	// sprite of the main character
	const int RICK_SPRITE_WIDTH = 9;
	const int RICK_SPRITE_HEIGHT = 16;
	extern const unsigned char Rick[][RICK_SPRITE_WIDTH * (RICK_SPRITE_HEIGHT / 8)];
	
	// animation for the dynamite, with the fuse and the explosion
	const int DYNAMITE_SPRITE_WIDTH = 8;
	const int DYNAMITE_SPRITE_HEIGHT = 8;
	extern const unsigned char Dynamite[][DYNAMITE_SPRITE_WIDTH * (DYNAMITE_SPRITE_HEIGHT / 8)];

	// animation for the sparks when the fuse of the dynamite is consuming. This anim should be drawn in inverted color.
	const int SPARKS_SPRITE_WIDTH = 5;
	const int SPARKS_SPRITE_HEIGHT = 8;
	extern const unsigned char Sparks[][SPARKS_SPRITE_WIDTH * (SPARKS_SPRITE_HEIGHT / 8)];

	// animation for the shiny horizontal spikes
	const int SPIKE_SPRITE_FRAME_COUNT = 6;
	const int SPIKE_HORIZONTAL_SPRITE_WIDTH = 3;
	const int SPIKE_HORIZONTAL_SPRITE_HEIGHT = 8;
	extern const unsigned char SpikeHorizontal[][SPIKE_HORIZONTAL_SPRITE_WIDTH * (SPIKE_HORIZONTAL_SPRITE_HEIGHT / 8)];

	// animation for the shiny vertical spikes
	const int SPIKE_VERTICAL_SPRITE_WIDTH = 4;
	const int SPIKE_VERTICAL_SPRITE_HEIGHT = 8;
	extern const unsigned char SpikeVertical[][SPIKE_VERTICAL_SPRITE_WIDTH * (SPIKE_VERTICAL_SPRITE_HEIGHT / 8)];

	// animation of a shiny star sparks that should be drawn on top of the gold statue. This anim should be drawn in inverted color.
	const int SHINE_STAR_SPRITE_WIDTH = 5;
	const int SHINE_STAR_SPRITE_HEIGHT = 8;
	extern const unsigned char ShineStar[][SHINE_STAR_SPRITE_WIDTH * (SHINE_STAR_SPRITE_HEIGHT / 8)];
	
	// statue sprite
	const int STATUE_SPRITE_WIDTH = 5;
	const int STATUE_SPRITE_HEIGHT = 8;
	extern const unsigned char Statue[];
}

#endif