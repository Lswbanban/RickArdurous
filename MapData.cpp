/*
 * This file contains all the level data.
*/

#include "MapData.h"
#include "SpriteData.h"
#include "MapManager.h"
#include "ArrowLauncher.h"
#include "Spike.h"
#include "Statuette.h"
#include "Dynamite.h"
#include "DynamiteCrate.h"
#include "BulletCrate.h"
#include "Enemy.h"
#include "DestroyableBlock.h"
#include "Stalactite.h"
#include "Stalagmite.h"
#include <avr/pgmspace.h>


const unsigned char MapManager::Level[LEVEL_SIZE_Y][LEVEL_SIZE_X] PROGMEM = {
	{ SpriteData::BLOCK_8_8, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, SpriteData::BLOCK_8_8, SpriteData::BLOCK_8_8_SPLIT, 2, 1, SpriteData::BLOCK_8_8, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, SpriteData::BLOCK_8_8,},
	{ SpriteData::BLOCK_8_8_SPLIT, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 2, 1, SpriteData::BLOCK_8_8, SpriteData::BLOCK_8_8_SPLIT, SpriteData::BLOCK_8_8, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, SpriteData::BLOCK_8_8,},
	{ SpriteData::BLOCK_8_8, 2, 1, SpriteData::PLATFORM, SpriteData::PLATFORM_WITH_LADDER, SpriteData::PLATFORM, 255, 255, 255, 255, 255, 255, 255, SpriteData::BLOCK_8_8_SPLIT, 2, 1, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, SpriteData::BLOCK_8_8,},
	{ SpriteData::BLOCK_8_8, 255, 255, 255, SpriteData::LADDER, 255, 255, 255, 255, 255, 255, 255, 255, 2, 1, SpriteData::BLOCK_8_8_SPLIT, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, SpriteData::BLOCK_8_8,},
	{ SpriteData::BLOCK_8_8_SPLIT, 255, 255, 255, SpriteData::LADDER, SpriteData::PLATFORM, SpriteData::PLATFORM, 255, 255, 255, SpriteData::PLATFORM, SpriteData::PLATFORM, SpriteData::PLATFORM, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ 2, 255, 255, SpriteData::PLATFORM, SpriteData::PLATFORM_WITH_LADDER, SpriteData::PLATFORM, 255, SpriteData::SMALL_STATUE, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, SpriteData::BLOCK_8_8,},
	{ SpriteData::BLOCK_8_8_SPLIT, SpriteData::LADDER, 255, 255, SpriteData::LADDER, 255, 255, 255, 255, 255, 255, 255, SpriteData::DESTROYABLE_BLOCK, SpriteData::DESTROYABLE_BLOCK, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,},
	{ SpriteData::BLOCK_8_8_SPLIT, SpriteData::LADDER, SpriteData::PLATFORM, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_8_8_SPLIT, SpriteData::BLOCK_16_8_RIGHT, 255, 255, SpriteData::BLOCK_8_8_SPLIT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_8_8_SPLIT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_8_8_SPLIT, SpriteData::BLOCK_16_8_RIGHT, SpriteData::BLOCK_8_8_SPLIT, SpriteData::BLOCK_16_8_RIGHT, 7, 0, 6, 0, 0, 255, 0, 0, 0, 0, 255, 255, 255, 255, 255, 0,},
	{ 0, SpriteData::LADDER, 255, 255, 255, 6, 255, 255, 7, 1, 2, 1, 2, 2, 1, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 0,},
	{ 0, SpriteData::LADDER, 255, 255, 255, 6, 255, 255, 6, 1, 1, 2, 2, 2, 1, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, SpriteData::PLATFORM, SpriteData::PLATFORM_WITH_LADDER, SpriteData::PLATFORM, 0,},
	{ 0, SpriteData::LADDER, 255, 255, 255, 7, 255, 255, 6, 2, 2, 1, 2, 1, 1, 0, 0, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 255, SpriteData::LADDER, 255, 0,},
	{ 0, SpriteData::LADDER, 255, SpriteData::LADDER, 255, 255, 255, 255, 0, 6, 7, 6, 0, 6, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, SpriteData::LADDER, 255, 0,},
	{ 0, 0, 0, SpriteData::LADDER, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 3, SpriteData::STAIR, 255, 255, 255, 255, 255, 255, SpriteData::STAIR, 3, 255, 255, SpriteData::LADDER, 255, 0,},
	{ 0, 255, 255, SpriteData::LADDER, 255, SpriteData::BIG_STATUE_TOP, SpriteData::BIG_STATUE_TOP, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 1, 2, SpriteData::STAIR, 255, 255, 255, 255, SpriteData::STAIR, 1, 2, 255, 255, 255, 255, 0,},
	{ 0, 255, 255, 255, 255, SpriteData::BIG_STATUE_BOTTOM, SpriteData::BIG_STATUE_BOTTOM, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
};

// below is the instances of all the Items
Enemy		mum(Item::PropertyFlags::NONE);
Enemy		skl(Item::PropertyFlags::SPECIAL_2 | Item::PropertyFlags::MIRROR_X);
Enemy		scor(Item::PropertyFlags::SPECIAL);
DestroyableBlock		block(Item::PropertyFlags::NONE);
Stalactite		sta(Item::PropertyFlags::NONE);
Stalagmite		mite(Item::PropertyFlags::NONE);
ArrowLauncher al(80, Item::PropertyFlags::NONE);
ArrowLauncher al2(80, Item::PropertyFlags::MIRROR_X);

void InitScreen0(bool init)
{
	MapManager::MemorizeCheckPoint(15, 2);
	MapManager::AddItem(&mum);
	//MapManager::AddItem(&skl);
	//MapManager::AddItem(&scor);
	MapManager::AddItem(&block);
	//MapManager::AddItem(&sta);
	//MapManager::AddItem(&mite);
	//MapManager::AddItem(&al);
	//MapManager::AddItem(&al2);
	
	if (init)
	{
		mum.Init(80, 40);
		skl.Init(85, 15);
		scor.Init(85, 15);
		block.Init(96, 48);
		sta.Init(75, 10);
		mite.Init(85, 48);
		//al.Init(9, 36);
		//al2.Init(80, 30);
	}
}

Spike	sp1(Item::PropertyFlags::SPECIAL | Item::PropertyFlags::MIRROR_X);
Spike	sp2(Item::PropertyFlags::MIRROR_X);
Spike	sp3(Item::PropertyFlags::NONE);
Statuette	st0;

void InitScreen1(bool init)
{
	MapManager::AddItem(&sp1);
	MapManager::AddItem(&sp2);
	MapManager::AddItem(&sp3);
	MapManager::AddItem(&st0);

	// init of the reusable items
	sp1.Init(80,94);
	sp2.Init(100,94);
	sp3.Init(116,105);
	
	// init of the killable items
	if (init)
	{
		st0.Init(20, 110);
	}
}

void InitScreen2(bool init)
{
	MapManager::MemorizeCheckPoint(180, 100);
	MapManager::AddItem(&sp1);
	MapManager::AddItem(&sp2);

	sp1.Init(200,100);
	sp2.Init(220,100);
	
	// init of the killable items
	//if (init)
	//{
	//}
}

Statuette	st;
DynamiteCrate	dc;
BulletCrate		bc;

void InitScreen3(bool init)
{
	MapManager::AddItem(&st);
	MapManager::AddItem(&dc);
	MapManager::AddItem(&bc);
	
	if (init)
	{
		st.Init(160, 40);
		dc.Init(140, 42);
		bc.Init(200, 42);
	}
}


// The array that contains all the items
ItemInitFunction MapManager::ItemInitFunctions[] = {
	&InitScreen0, &InitScreen1, &InitScreen2, &InitScreen3,
	};

// compute the number of items
const unsigned char MapManager::PUZZLE_SCREEN_COUNT = sizeof(MapManager::ItemInitFunctions) / sizeof(ItemInitFunction);
