/**
* This file store all the sprite data used in the game
*/
#include <avr/pgmspace.h>
#include "SpriteData.h"

namespace SpriteData
{
	const unsigned char Walls[][LEVEL_SPRITE_WIDTH * (LEVEL_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x3e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3e, 0x00, },
		{0x3e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, },
		{0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3e, 0x00, },
		{0xff, 0xb3, 0xb3, 0xff, 0xc1, 0x80, 0x00, 0x00, },
		{0xff, 0x47, 0xfb, 0xff, 0xad, 0xb8, 0x00, 0x00, },
	};
	
	const unsigned char Rick[][RICK_SPRITE_WIDTH * (RICK_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x8, 0x8, 0x7a, 0xfa, 0xfa, 0x6a, 0x3a, 0x38, 0x8, 0x00, 0x00, 0x7, 0x1c, 0x18, 0x1f, 0x16, 0x10, 0x00, },{0x8, 0x8, 0x7a, 0xfa, 0xfa, 0x6a, 0x3a, 0x38, 0x8, 0x00, 0x00, 0x1f, 0x1e, 0x1c, 0xb, 0xe, 0xc, 0x6, },{0x4, 0x4, 0xb5, 0x7d, 0x7d, 0xb5, 0x1d, 0x1c, 0x4, 0x00, 0x8, 0x1d, 0x1f, 0x6, 0xc, 0xf, 0x8, 0x4, },{0x4, 0x4, 0xb5, 0xfd, 0x7d, 0xb5, 0x1d, 0x1c, 0x4, 0xc, 0x1e, 0x7, 0x1c, 0x1e, 0x17, 0x13, 0x00, 0x00, },{0x4, 0x4, 0xbd, 0x7d, 0x7d, 0xb5, 0x1d, 0x1c, 0x4, 0x00, 0x00, 0x3, 0xf, 0xe, 0xc, 0xb, 0x8, 0x00, },{0x4, 0x4, 0xbd, 0x7d, 0x7d, 0x35, 0x9d, 0x9c, 0x4, 0x00, 0x00, 0x3, 0xf, 0xe, 0xe, 0xb, 0x8, 0x00, },{0x8, 0x8, 0x7a, 0xfa, 0xfa, 0x6a, 0x3a, 0x38, 0x8, 0x00, 0x00, 0x7, 0xc, 0x8, 0xf, 0xe, 0x8, 0x00, },{0x4, 0xc, 0x78, 0xfa, 0xf2, 0xd4, 0xe4, 0xe8, 0x40, 0x00, 0x6, 0xf, 0x1, 0x1, 0xe, 0xe, 0x8, 0x00, },
	};
	
	const unsigned char Dynamite[][DYNAMITE_SPRITE_WIDTH * (DYNAMITE_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x00, 0x00, 0x18, 0x4, 0xf4, 0xf8, 0xf0, 0x00, },{0x00, 0x00, 0x8, 0x4, 0xf4, 0xf8, 0xf0, 0x00, },{0x00, 0x00, 0x00, 0x4, 0xf4, 0xf8, 0xf0, 0x00, },{0x00, 0x00, 0x00, 0x00, 0xf4, 0xf8, 0xf0, 0x00, },{0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xf0, 0x00, },{0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0x00, },{0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, },{0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00, },{0x10, 0x24, 0x42, 0x9a, 0x99, 0x42, 0x28, 0x10, },{0x2c, 0x42, 0x11, 0x84, 0xa1, 0x95, 0x42, 0x14, },{0x49, 0x82, 0x00, 0x1, 0x00, 0x80, 0x1, 0x94, },
	};

	const unsigned char Sparks[][SPARKS_SPRITE_WIDTH * (SPARKS_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x00, 0x00, 0x8, 0x10, 0x00, },{0x00, 0x4, 0x10, 0x20, 0x00, },{0x4, 0x20, 0x8, 0x00, 0x80, },{0x40, 0x00, 0x10, 0x4, 0x00, },{0x00, 0x00, 0x40, 0x00, 0x2, },
	};

	
	const unsigned char SpikeHorizontal[][SPIKE_HORIZONTAL_SPRITE_WIDTH * (SPIKE_HORIZONTAL_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0xc0, 0xf0, 0xc0, },{0xc0, 0xe0, 0xc0, },{0x80, 0xd0, 0xc0, },{0x40, 0xb0, 0xc0, },{0xc0, 0x70, 0x80, },{0xc0, 0xf0, 0x40, },
	};

	const unsigned char SpikeVertical[][SPIKE_VERTICAL_SPRITE_WIDTH * (SPIKE_VERTICAL_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x10, 0x10, 0x38, 0x38, },{0x00, 0x10, 0x38, 0x38, },{0x10, 0x00, 0x30, 0x38, },{0x10, 0x10, 0x28, 0x30, },{0x10, 0x10, 0x18, 0x28, },{0x10, 0x10, 0x38, 0x18, },
	};
	
	const unsigned char ShineStar[][SHINE_STAR_SPRITE_WIDTH * (SHINE_STAR_SPRITE_HEIGHT / 8)] PROGMEM = {
		{0x00, 0x00, 0x4, 0x00, 0x00, },{0x00, 0x4, 0xa, 0x4, 0x00, },{0x4, 0x4, 0x1b, 0x4, 0x4, },{0x4, 0x00, 0x11, 0x00, 0x4, },
	};
	
	const unsigned char Statue[] PROGMEM = { 0x7c, 0xea, 0xee, 0xea, 0x7c, };
}