/**
* This file store all the sprite data used in the game
*/
#include <avr/pgmspace.h>
#include "SpriteData.h"

namespace SpriteData
{
	const unsigned char Walls[][LEVEL_SPRITE_WIDTH * (LEVEL_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x7f, 0x7b, 0x7f, 0x6f, 0x7f, 0x7d, 0x7f, 0x7f, },{0xc6, 0x53, 0x99, 0x3c, 0x2e, 0x24, 0x99, 0xc2, },{0xc7, 0x53, 0x9b, 0x3b, 0x6b, 0x2b, 0x93, 0xc7, },{0xc7, 0x53, 0x9b, 0x2b, 0x73, 0x7, 0xf, 0xe, },{0xe, 0xf, 0x7, 0x73, 0x2b, 0x9b, 0x53, 0xc7, },{0x7f, 0x5f, 0x7b, 0x7f, 0x7f, 0x6f, 0x7f, 0x00, },{0x77, 0x77, 0x75, 0x77, 0x57, 0x77, 0x77, 0x00, },{0x7e, 0xf3, 0xab, 0xbf, 0xaf, 0xb3, 0xfb, 0x7e, },{0x77, 0x6d, 0x6f, 0x57, 0x5b, 0x3d, 0x7d, 0x6e, },{0x7f, 0x6b, 0x6f, 0x5c, 0x2b, 0x77, 0x77, 0x00, },{0xfe, 0x85, 0x35, 0x4f, 0x4d, 0x35, 0x87, 0xfd, },{0x7f, 0xff, 0xe7, 0xc3, 0xcf, 0xc3, 0xa2, 0x67, },{0x3, 0x1, 0x3, 0x3, 0x3, 0x1, 0x3, 0x3, },{0xff, 0x11, 0x11, 0x11, 0x11, 0x11, 0xff, 0x00, },{0xff, 0x11, 0x13, 0x13, 0x13, 0x11, 0xff, 0x3, },{0xff, 0xb6, 0xbe, 0x18, 0x00, 0x00, 0x00, 0x00, },
	};
	
	const unsigned char Rick[][RICK_SPRITE_WIDTH * (RICK_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x8, 0x8, 0x7a, 0xfa, 0xfa, 0x6a, 0x3a, 0x38, 0x8, 0x00, 0x00, 0x7, 0x1c, 0x18, 0x1f, 0x16, 0x10, 0x00, },{0x8, 0x8, 0x7a, 0xfa, 0xfa, 0x6a, 0x3a, 0x38, 0x8, 0x00, 0x00, 0x1f, 0x1e, 0x1c, 0xb, 0xe, 0xc, 0x6, },{0x4, 0x4, 0xb5, 0x7d, 0x7d, 0xb5, 0x1d, 0x1c, 0x4, 0x00, 0x8, 0x1d, 0x1f, 0x6, 0xc, 0xf, 0x8, 0x4, },{0x4, 0x4, 0xb5, 0xfd, 0x7d, 0xb5, 0x1d, 0x1c, 0x4, 0xc, 0x1e, 0x7, 0x1c, 0x1e, 0x17, 0x13, 0x00, 0x00, },{0x8, 0x8, 0x7a, 0xfa, 0xfa, 0x6a, 0x3a, 0x38, 0x8, 0x00, 0x00, 0x7, 0x1e, 0x1c, 0x19, 0x16, 0x10, 0x00, },{0x8, 0x8, 0x7a, 0xfa, 0xfa, 0x6a, 0x3a, 0x38, 0x8, 0x00, 0x00, 0x7, 0x1e, 0x1c, 0x1c, 0x17, 0x11, 0x00, },{0x10, 0x10, 0xf4, 0xf4, 0xf4, 0xd4, 0x74, 0x70, 0x10, 0x00, 0x00, 0xe, 0x19, 0x11, 0x1e, 0x1c, 0x10, 0x00, },{0x8, 0x18, 0xf0, 0xf4, 0xe4, 0xa8, 0xc8, 0xd0, 0x80, 0x00, 0xc, 0x1e, 0x3, 0x3, 0x1d, 0x1d, 0x11, 0x00, },{0x4, 0x4, 0xbd, 0x7d, 0x7d, 0xb5, 0x1d, 0x1c, 0x4, 0x4, 0xf, 0x1c, 0x16, 0x3, 0x7, 0xe, 0xc, 0x6, },{0x3c, 0x42, 0x99, 0xbd, 0xbd, 0xbd, 0x99, 0x42, 0xbc, 0x4, 0x6, 0xe, 0xf, 0x7, 0x1f, 0x1e, 0x3, 0x1, },{0x3c, 0x42, 0x99, 0xbd, 0xbd, 0xbd, 0x99, 0x42, 0x3c, 0x3, 0x3, 0x1d, 0x1f, 0x7, 0x1f, 0x1d, 0x3, 0x3, },{0xbc, 0x42, 0x99, 0xbd, 0xbd, 0xbd, 0x99, 0x42, 0x3c, 0x1, 0x3, 0x1e, 0x1f, 0x7, 0xf, 0xe, 0x6, 0x4, },{0xc8, 0x88, 0x7a, 0xaa, 0xba, 0xaa, 0x7a, 0x88, 0xc8, 0x00, 0x1, 0x17, 0x1f, 0xa, 0x1f, 0x17, 0x1, 0x00, },{0x8, 0x8, 0x7a, 0xaa, 0xba, 0xaa, 0x7a, 0x8, 0x8, 0x1, 0x3, 0x17, 0x1f, 0xa, 0x1f, 0x17, 0x3, 0x1, },{0x8, 0x8, 0x7a, 0xaa, 0xba, 0xaa, 0x7a, 0x8, 0x8, 0x6, 0x3, 0x17, 0x1f, 0xa, 0x1f, 0x17, 0x3, 0x6, },
	};

	const unsigned char RickCrawl[][RICK_CRAWL_SPRITE_WIDTH * (RICK_CRAWL_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x00, 0xc0, 0xe0, 0xe4, 0xf4, 0x9d, 0x3d, 0x7d, 0xf5, 0x9d, 0x9c, 0x4, },{0x80, 0xc0, 0xe0, 0xe4, 0xf4, 0x1d, 0x7d, 0xfd, 0xf5, 0x9d, 0x1c, 0x4, },{0xc0, 0xc0, 0xe0, 0xe4, 0xb4, 0x1d, 0xdd, 0xfd, 0xb5, 0x1d, 0x1c, 0x4, },
	};
	
	const unsigned char Dynamite[][DYNAMITE_SPRITE_WIDTH * (DYNAMITE_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x00, 0x00, 0x18, 0x4, 0xf4, 0xf8, 0xf0, 0x00, },{0x00, 0x00, 0x8, 0x4, 0xf4, 0xf8, 0xf0, 0x00, },{0x00, 0x00, 0x00, 0x4, 0xf4, 0xf8, 0xf0, 0x00, },{0x00, 0x00, 0x00, 0x00, 0xf4, 0xf8, 0xf0, 0x00, },{0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xf0, 0x00, },{0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0x00, },{0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, },{0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00, },{0x10, 0x24, 0x42, 0x9a, 0x99, 0x42, 0x28, 0x10, },{0x2c, 0x42, 0x11, 0x84, 0xa1, 0x95, 0x42, 0x14, },{0x49, 0x82, 0x00, 0x1, 0x00, 0x80, 0x1, 0x94, },
	};

	const unsigned char Sparks[][SPARKS_SPRITE_WIDTH * (SPARKS_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x00, 0x00, 0x8, 0x10, 0x00, },{0x00, 0x4, 0x10, 0x20, 0x00, },{0x4, 0x00, 0x00, 0x8, 0x40, },{0x00, 0x10, 0x00, 0x00, 0x4, },{0x20, 0x00, 0x00, 0x00, 0x00, },
	};

	
	const unsigned char SpikeHorizontal[][SPIKE_HORIZONTAL_SPRITE_WIDTH * (SPIKE_HORIZONTAL_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0xc0, 0xf0, 0xc0, },{0xc0, 0xe0, 0xc0, },{0x80, 0xd0, 0xc0, },{0x40, 0xb0, 0xc0, },{0xc0, 0x70, 0x80, },{0xc0, 0xf0, 0x40, },
	};

	const unsigned char SpikeVertical[][SPIKE_VERTICAL_SPRITE_WIDTH * (SPIKE_VERTICAL_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x10, 0x10, 0x38, 0x38, },{0x00, 0x10, 0x38, 0x38, },{0x10, 0x00, 0x30, 0x38, },{0x10, 0x10, 0x28, 0x30, },{0x10, 0x10, 0x18, 0x28, },{0x10, 0x10, 0x38, 0x18, },
	};
	
	const unsigned char ShineStar[][SHINE_STAR_SPRITE_WIDTH * (SHINE_STAR_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x00, 0x00, 0x4, 0x00, 0x00, },{0x00, 0x4, 0xe, 0x4, 0x00, },{0x4, 0x4, 0x1f, 0x4, 0x4, },{0x4, 0x4, 0x1f, 0x4, 0x4, },
	};
	
	const unsigned char ArrowLauncherFace[] PROGMEM = {0xff, 0xb6, 0xbe, 0x18, };
	
	const unsigned char Statuette[] PROGMEM = { 0x7c, 0xea, 0xee, 0xea, 0x7c, };
	
	const unsigned char BulletCrate[] PROGMEM = { 0xa8, 0xfc, 0x8a, 0xaf, 0xa9, 0xaf, 0xaa, 0xae, 0x8a, 0xfc, 0xa8,  };
	const unsigned char DynamiteCrate[] PROGMEM = { 0xaa, 0xf9, 0x8d, 0xae, 0xac, 0xa8, 0xac, 0xae, 0x8d, 0xf9, 0xa8, };
	
	const unsigned char Mummy[][MUMMY_SPRITE_WIDTH * (MUMMY_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x10, 0x54, 0x54, 0x7c, 0xfc, 0xf4, 0x5c, 0x18, 0x00, 0x00, 0x9, 0xa, 0xa, 0x3f, 0x3f, 0x21, 0x1, 0x3, },{0x48, 0x24, 0xaa, 0xbe, 0xfe, 0xea, 0xae, 0x8c, 0x80, 0x8, 0x5, 0x34, 0x3e, 0x3e, 0x27, 0x00, 0x00, 0x1, },{0x28, 0x28, 0x52, 0x5a, 0xbc, 0xf4, 0x5c, 0x18, 0x00, 0x2, 0x5, 0x1d, 0x3a, 0xd, 0x3f, 0x39, 0x21, 0x1, },{0x50, 0x94, 0xa4, 0xb8, 0xf8, 0xe8, 0xf8, 0x30, 0x00, 0x8, 0x12, 0xa, 0x2e, 0x3d, 0x3f, 0x1a, 0x2, 0x2, },{0x00, 0x38, 0x74, 0xdc, 0xdc, 0x74, 0x6c, 0x94, 0x20, 0x00, 0x3, 0x27, 0x3d, 0x3b, 0x2d, 0xa, 0x12, 0x4, },
	};
	
	const unsigned char Skeleton[][SKELETON_SPRITE_WIDTH * (SKELETON_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x18, 0x3c, 0xfc, 0x74, 0x58, 0x00, 0x00, 0x7, 0x3c, 0x23, 0x00, 0x00, },{0x18, 0x3c, 0xfc, 0x74, 0x58, 0x00, 0x00, 0x37, 0x2c, 0xb, 0x12, 0x8, },{0xc, 0x9e, 0x7e, 0xba, 0x2c, 0x00, 0x10, 0x29, 0x6, 0x1d, 0x11, 0x00, },{0xc, 0x9e, 0x7e, 0xba, 0x2c, 0x00, 0x8, 0x15, 0x6, 0x39, 0x22, 0x00, },{0x98, 0x74, 0xac, 0x74, 0x98, 0x00, 0x23, 0x3d, 0x7, 0x3d, 0x00, 0x3, },{0x18, 0x74, 0xac, 0x74, 0x18, 0x00, 0x26, 0x3d, 0x7, 0x3d, 0x26, 0x00, },{0x30, 0xe8, 0x58, 0xe8, 0x30, 0x00, 0x2c, 0x3a, 0xf, 0x3a, 0x2c, 0x00, },{0x46, 0x5d, 0xeb, 0x5d, 0x46, 0x00, 0x8, 0x6, 0x1, 0x6, 0x8, 0x00, },{0x98, 0x34, 0x2c, 0x34, 0x98, 0x00, 0x21, 0x3a, 0xf, 0x3a, 0x21, 0x00, },{0x18, 0x3c, 0xfc, 0x74, 0x58, 0x00, 0x10, 0x2b, 0x4, 0xb, 0x11, 0x9, },
	};
	
	const unsigned char Scorpion[][SCORPION_SPRITE_WIDTH * (SCORPION_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x7, 0xd, 0x4, 0xe, 0x6, 0xc, 0xe, 0xa, },{0xf, 0x5, 0xc, 0xe, 0x6, 0xc, 0xe, 0xa, },{0x7, 0xd, 0xc, 0x6, 0xe, 0xc, 0xc, 0xa, },{0xf, 0xd, 0x4, 0xe, 0x6, 0xc, 0xc, 0xc, },{0x00, 0x7, 0xd, 0xe, 0x6, 0xc, 0xc, 0x00, },{0x6, 0xd, 0x4, 0xe, 0x6, 0xc, 0xe, 0x9, },{0x2, 0xf, 0x5, 0xc, 0x6, 0xe, 0x7, 0x5, },{0x2, 0xf, 0x5, 0xd, 0x4, 0xe, 0x6, 0x6, },{0x6, 0xf, 0x5, 0xc, 0x6, 0xe, 0x6, 0xa, },
	};
	
	const unsigned char BlockFragment[] PROGMEM = {0x1c, 0x36, 0x6e, 0x7c, 0x1c, };
	
	const unsigned char Stalactite[] PROGMEM = {0xf, 0xff, 0x1f, };
	
	const unsigned char Stalagmite[] PROGMEM = {0xf0, 0xff, 0xf8, };
	
	const unsigned char HUDHeart[] PROGMEM = { 0x6, 0xf, 0x1e, 0xf, 0x6, };
	const unsigned char HUDStatuette[] PROGMEM = { 0xe, 0x1d, 0x17, 0x1d, 0xe, };
	const unsigned char HUDDynamite[] PROGMEM = { 0x1c, 0x1e, 0x1d, 0x1, 0x2, };
	const unsigned char HUDBullet[] PROGMEM = { 0x1c, 0x1e, 0x7, 0x5, 0x3, 0x1, 0x1, };
	const unsigned char HUDSlash[] PROGMEM = { 0x18, 0xe, 0x3, };
	
	const unsigned char Numbers[][NUMBERS_SPRITE_WIDTH * (NUMBERS_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0xe, 0x11, 0x11, 0xe, },{0x00, 0x12, 0x1f, 0x10, },{0x19, 0x15, 0x15, 0x12, },{0x11, 0x15, 0x15, 0xa, },{0xc, 0xa, 0x1f, 0x8, },{0x17, 0x15, 0x15, 0x9, },{0xe, 0x15, 0x15, 0x9, },{0x1, 0x19, 0x5, 0x3, },{0xa, 0x15, 0x15, 0xa, },{0x12, 0x15, 0x15, 0xe, },
	};
}