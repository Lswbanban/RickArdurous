/*
 * This file contains all the level data.
*/

#include "MapData.h"
#include "SpriteData.h"
#include "Spike.h"
#include "Statuette.h"
#include "Dynamite.h"
#include "DynamiteCrate.h"
#include "BulletCrate.h"
#include <avr/pgmspace.h>

const unsigned char MapManager::Level[][32] PROGMEM = {
	{ 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 1, 2, 3, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ 1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 2, 3, 0, 1, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ 0, 2, 3, 29, 30, 29, 255, 255, 255, 255, 255, 255, 255, 1, 2, 3, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ 0, 255, 255, 255, 31, 29, 29, 255, 255, 255, 255, 255, 255, 2, 3, 1, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ 1, 255, 255, 255, 31, 255, 255, 255, 255, 255, 29, 29, 29, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ 2, SpriteData::STATUE_TOP, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 1, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ SpriteData::BLOCK_8_8_SPLIT, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, 0, 0, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_16_8_LEFT, SpriteData::BLOCK_16_8_RIGHT, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
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

// below is the instances of all the Items
Spike	sp1(120,30, Item::PropertyFlags::SPECIAL | Item::PropertyFlags::MIRROR_X);
Spike	sp2(110,30, Item::PropertyFlags::MIRROR_X);
Spike	sp3(100,30, Item::PropertyFlags::NONE);
Statuette	st(40,25);
DynamiteCrate	dc(60, 50);
BulletCrate		bc(80, 25);

// The array that contains all the items
Item * MapManager::Items[] = {
	&sp1, &sp2, &sp3, &st, &dc, &bc,
	};

// compute the number of items
const unsigned int MapManager::ITEM_COUNT = sizeof(MapManager::Items) >> 1;
