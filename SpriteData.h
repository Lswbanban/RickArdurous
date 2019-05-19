#ifndef _SPRITE_DATA_H_
#define _SPRITE_DATA_H_

namespace SpriteData
{
	enum WallId
	{
		BLOCK_16_8_RIGHT = 0,
		ROCK,
		ROCK_2,
		ROCK_GROUND,
		STAIR,
		BLOCK_8_8,
		BLOCK_8_8_SPLIT,
		SMALL_STATUE,
		BIG_STATUE_TOP,
		BIG_STATUE_BOTTOM,
		PLATFORM,
		LADDER,
		PLATFORM_WITH_LADDER,
		ARROW_LAUNCHER,
		DESTROYABLE_BLOCK,
		NOTHING = 255, // todo replace when optimizing the map
	};
	
	// sprite of the walls
	// the sprite width and height in pixel
	const int LEVEL_SPRITE_WIDTH = 8;
	const int LEVEL_SPRITE_HEIGHT = 8;
	extern const unsigned char Walls[][LEVEL_SPRITE_WIDTH * (LEVEL_SPRITE_HEIGHT / 8)];
	
	// destroyable Blocks
	const int DESTROYABLE_BLOCK_SPRITE_WIDTH = 15;
	const int DESTROYABLE_BLOCK_SPRITE_HEIGHT = 8;
	extern const unsigned char DestroyableBlock[];
	
	enum RickAnimFrameId
	{
		IDLE = 0,
		WALK_START = 0,
		WALK_END = 3,
		FIRE_START = 4,
		FIRE_END = 5,
		CROUCH_START = 6,
		CROUCH_END = 7,
		STAND_UP_START = 7,
		STAND_UP_END = 6,
		JUMP = 8,
		CLIMB_START = 9,
		CLIMB_END = 11,
		DEATH_START = 12,
		DEATH_END = 14,
		// restart the index because these index are for the RickCrawl array
		CRAWL_START = 0,
		CRAWL_END = 2,
	};
	
	// sprite of the main character
	const int RICK_SPRITE_WIDTH = 9;
	const int RICK_SPRITE_HEIGHT = 16;
	extern const unsigned char Rick[][RICK_SPRITE_WIDTH * (RICK_SPRITE_HEIGHT / 8)];
	const int RICK_CRAWL_SPRITE_WIDTH = 12;
	const int RICK_CRAWL_SPRITE_HEIGHT = 8;
	extern const unsigned char RickCrawl[][RICK_CRAWL_SPRITE_WIDTH * (RICK_CRAWL_SPRITE_HEIGHT / 8)];
	
	// animation for the dynamite, with the fuse and the explosion
	const int DYNAMITE_SPRITE_FRAME_COUNT = 11;
	const int DYNAMITE_SPRITE_WIDTH = 8;
	const int DYNAMITE_SPRITE_HEIGHT = 8;
	extern const unsigned char Dynamite[][DYNAMITE_SPRITE_WIDTH * (DYNAMITE_SPRITE_HEIGHT / 8)];

	// animation for the sparks when the fuse of the dynamite is consuming. This anim should be drawn in inverted color.
	const int SPARKS_SPRITE_FRAME_COUNT = 5;
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
	const int SHINE_STAR_SPRITE_FRAME_COUNT = 4;
	const int SHINE_STAR_SPRITE_WIDTH = 5;
	const int SHINE_STAR_SPRITE_HEIGHT = 8;
	extern const unsigned char ShineStar[][SHINE_STAR_SPRITE_WIDTH * (SHINE_STAR_SPRITE_HEIGHT / 8)];
	
	// arrow launcher
	const int ARROW_LAUNCHER_FACE_SPRITE_WIDTH = 4;
	const int ARROW_LAUNCHER_FACE_SPRITE_HEIGHT = 8;
	extern const unsigned char ArrowLauncherFace[];
	
	// statue sprite
	const int STATUETTE_SPRITE_WIDTH = 5;
	const int STATUETTE_SPRITE_HEIGHT = 8;
	extern const unsigned char Statuette[];
	
	// dynamite and bullet bonus sprite
	const int CRATE_SPRITE_WIDTH = 11;
	const int CRATE_SPRITE_HEIGHT = 8;
	extern const unsigned char BulletCrate[];
	extern const unsigned char DynamiteCrate[];
	
	// Mummies
	enum EnemyAnimFrameId
	{
		ENEMY_WALK_START = 0,
		ENEMY_WALK_END = 3,
		ENEMY_HALF_TURN,
		ENEMY_WAIT_START,
		ENEMY_WAIT_END = 8,
		ENEMY_FALL,
	};
	const int MUMMY_SPRITE_WIDTH = 9;
	const int MUMMY_SPRITE_HEIGHT = 16;
	extern const unsigned char Mummy[][MUMMY_SPRITE_WIDTH * (MUMMY_SPRITE_HEIGHT / 8)];

	// Skeletons
	const int SKELETON_SPRITE_WIDTH = 6;
	const int SKELETON_SPRITE_HEIGHT = 16;
	extern const unsigned char Skeleton[][SKELETON_SPRITE_WIDTH * (SKELETON_SPRITE_HEIGHT / 8)];

	// Scorpions
	const int SCORPION_SPRITE_WIDTH = 8;
	const int SCORPION_SPRITE_HEIGHT = 8;
	extern const unsigned char Scorpion[][SCORPION_SPRITE_WIDTH * (SCORPION_SPRITE_HEIGHT / 8)];

	// Destroyable block fragment sprite
	const int BLOCK_FRAGMENT_SPRITE_WIDTH = 5;
	const int BLOCK_FRAGMENT_SPRITE_HEIGHT = 8;
	extern const unsigned char BlockFragment[];

	// Stalactite and Stalagmite
	const int STALACTITE_SPRITE_WIDTH = 3;
	const int STALACTITE_SPRITE_HEIGHT = 8;
	extern const unsigned char Stalactite[];
	const int STALAGMITE_SPRITE_WIDTH = 3;
	const int STALAGMITE_SPRITE_HEIGHT = 8;
	extern const unsigned char Stalagmite[];

	// HUD elements
	const int HUD_SPRITE_WIDTH = 5;
	const int HUD_BULLET_SPRITE_WIDTH = 7;
	const int HUD_SPRITE_HEIGHT = 8;
	extern const unsigned char HUDHeart[];
	extern const unsigned char HUDStatuette[];
	extern const unsigned char HUDDynamite[];
	extern const unsigned char HUDBullet[];

	const int HUD_SLASH_SPRITE_WIDTH = 3;
	extern const unsigned char HUDSlash[];

	// tiny numbers for HUD
	const int NUMBERS_SPRITE_WIDTH = 4;
	const int NUMBERS_SPRITE_HEIGHT = 8;
	extern const unsigned char Numbers[][NUMBERS_SPRITE_WIDTH * (NUMBERS_SPRITE_HEIGHT / 8)];
}

#endif