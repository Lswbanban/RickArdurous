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

#define ID(id1,id2) ((id1<< 4) | id2)

const unsigned char MapManager::Level[] PROGMEM = {
	ID(SpriteData::BLOCK_8_8, SpriteData::NOTHING), ID(11, SpriteData::BLOCK_8_8), ID(SpriteData::BLOCK_8_8_SPLIT, 2), ID(1, SpriteData::BLOCK_8_8), ID(SpriteData::NOTHING, 14), ID(SpriteData::BLOCK_8_8, 0),
	ID(SpriteData::BLOCK_8_8_SPLIT, SpriteData::NOTHING), ID(11, 2), ID(1, SpriteData::BLOCK_8_8), ID(SpriteData::BLOCK_8_8_SPLIT, SpriteData::BLOCK_8_8), ID(SpriteData::NOTHING, 14), ID(SpriteData::BLOCK_8_8, 0),
	ID(SpriteData::BLOCK_8_8, 2), ID(1, SpriteData::PLATFORM), ID(SpriteData::PLATFORM_WITH_LADDER, SpriteData::PLATFORM), ID(SpriteData::NOTHING, 7), ID(SpriteData::BLOCK_8_8_SPLIT, 2), ID(1, 0), ID(SpriteData::NOTHING, 14), ID(SpriteData::BLOCK_8_8,0),
	ID(SpriteData::BLOCK_8_8, SpriteData::NOTHING), ID(3, SpriteData::LADDER), ID(SpriteData::NOTHING, 8), ID(2, 1), ID(SpriteData::BLOCK_8_8_SPLIT, 0), ID(SpriteData::NOTHING,14), ID(SpriteData::BLOCK_8_8, 0),
	ID(SpriteData::BLOCK_8_8_SPLIT, SpriteData::NOTHING), ID(3, SpriteData::LADDER), ID(SpriteData::PLATFORM, SpriteData::PLATFORM), ID(SpriteData::NOTHING, 3), ID(SpriteData::PLATFORM, SpriteData::PLATFORM), ID(SpriteData::PLATFORM, SpriteData::NOTHING), ID(3, 0), ID(SpriteData::NOTHING, 14), ID(0,0),
	ID(2, SpriteData::NOTHING), ID(2, SpriteData::PLATFORM), ID(SpriteData::PLATFORM_WITH_LADDER, SpriteData::PLATFORM), ID(SpriteData::NOTHING, 1), ID(SpriteData::SMALL_STATUE, SpriteData::NOTHING), ID(15, SpriteData::NOTHING), ID(8, SpriteData::BLOCK_8_8),
	ID(SpriteData::BLOCK_8_8_SPLIT, SpriteData::LADDER), ID(SpriteData::NOTHING, 2), ID(SpriteData::LADDER, SpriteData::NOTHING), ID(7, SpriteData::DESTROYABLE_BLOCK), ID(SpriteData::DESTROYABLE_BLOCK, SpriteData::NOTHING), ID(15, SpriteData::NOTHING), ID(3, 0),
	ID(SpriteData::BLOCK_8_8_SPLIT, SpriteData::LADDER), ID(SpriteData::PLATFORM, SpriteData::BLOCK_16_8_RIGHT), ID(SpriteData::BLOCK_8_8_SPLIT, SpriteData::BLOCK_16_8_RIGHT), ID(SpriteData::NOTHING, 2), ID(SpriteData::BLOCK_8_8_SPLIT, SpriteData::BLOCK_16_8_RIGHT), ID(SpriteData::BLOCK_8_8_SPLIT, SpriteData::BLOCK_16_8_RIGHT), ID(SpriteData::BLOCK_8_8_SPLIT, SpriteData::BLOCK_16_8_RIGHT), ID(SpriteData::BLOCK_8_8_SPLIT, SpriteData::BLOCK_16_8_RIGHT), ID(7, 0), ID(6, 0), ID(0, SpriteData::NOTHING), ID(1, 0), ID(0, 0), ID(0, SpriteData::NOTHING), ID(5, 0),
	/*{ 0, SpriteData::LADDER, 255, 255, 255, 6, 255, 255, 7, 1, 2, 1, 2, 2, 1, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 0,},
	{ 0, SpriteData::LADDER, 255, 255, 255, 6, 255, 255, 6, 1, 1, 2, 2, 2, 1, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, SpriteData::PLATFORM, SpriteData::PLATFORM_WITH_LADDER, SpriteData::PLATFORM, 0,},
	{ 0, SpriteData::LADDER, 255, 255, 255, 7, 255, 255, 6, 2, 2, 1, 2, 1, 1, 0, 0, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 255, SpriteData::LADDER, 255, 0,},
	{ 0, SpriteData::LADDER, 255, SpriteData::LADDER, 255, 255, 255, 255, 0, 6, 7, 6, 0, 6, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, SpriteData::LADDER, 255, 0,},
	{ 0, 0, 0, SpriteData::LADDER, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 3, SpriteData::STAIR, 255, 255, 255, 255, 255, 255, SpriteData::STAIR, 3, 255, 255, SpriteData::LADDER, 255, 0,},
	{ 0, 255, 255, SpriteData::LADDER, 255, SpriteData::BIG_STATUE_TOP, SpriteData::BIG_STATUE_TOP, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 1, 2, SpriteData::STAIR, 255, 255, 255, 255, SpriteData::STAIR, 1, 2, 255, 255, 255, 255, 0,},
	{ 0, 255, 255, 255, 255, SpriteData::BIG_STATUE_BOTTOM, SpriteData::BIG_STATUE_BOTTOM, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},*/
};

const unsigned int MapManager::LevelSize = sizeof(MapManager::Level);

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
