/**
* This file store all the sprite data used in the game
*/
#include <avr/pgmspace.h>
#include "SpriteData.h"

namespace SpriteData
{
	const unsigned char Walls[][8] PROGMEM = {
		{0x3e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3e, 0x00, }, 
	};

}