/*
 * This is a generated file, use the Editor to modify it.
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
	ID(2,1),ID(2,0),ID(5,15),ID(4,5),ID(1,2),ID(2,1),ID(2,5),ID(15,15),ID(15,1),
	ID(1,1),ID(1,5),ID(15,6),ID(5,6),ID(1,1),ID(1,5),ID(15,15),ID(15,1),
	ID(2,2),ID(6,15),ID(13,0),ID(15,15),
	ID(1,5),ID(5,15),ID(13,0),ID(15,15),
	ID(2,5),ID(15,6),ID(10,10),ID(10,10),ID(10,10),ID(12,15),ID(1,0),ID(15,15),
	ID(1,6),ID(15,4),ID(10,15),ID(7,11),ID(15,15),ID(15,2),
	ID(1,5),ID(15,3),ID(10,15),ID(2,4),ID(3,3),ID(7,15),ID(2,11),ID(15,15),ID(15,2),
	ID(2,5),ID(5,0),ID(5,0),ID(5,6),ID(0,1),ID(2,6),ID(15,2),ID(11,15),ID(1,0),ID(15,15),
	ID(15,14),ID(11,15),ID(1,0),ID(15,15),
	ID(15,14),ID(11,15),ID(1,0),ID(15,15),
	ID(15,14),ID(11,15),ID(15,15),ID(2,0),
	ID(15,14),ID(11,15),ID(15,15),ID(2,0),
	ID(15,14),ID(11,15),ID(15,15),ID(2,0),
	ID(0,15),ID(13,11),ID(0,15),ID(15,15),ID(1,0),
	ID(0,15),ID(9,0),ID(15,3),ID(11,0),ID(15,15),ID(15,1),
	ID(0,0),ID(0,0),ID(0,0),ID(0,0),ID(0,0),ID(0,0),ID(0,0),ID(0,0),ID(15,15),ID(15,1),
};

const unsigned int MapManager::LevelLineIndex[] PROGMEM = {0,9,17,21,25,33,39,48,58,62,66,70,74,78,83,89,};

ArrowLauncher en;

void InitScreen0(bool init)
{
	// Add all the items to the manager
	MapManager::MemorizeCheckPoint(73, 34);
	
	// init the item positions
	en.Init(20,50, Item::PropertyFlags::NONE, 80);
}

void InitScreen1(bool init)
{
	// Add all the items to the manager
	
	// init the item positions
	en.Init(80, 114, Item::PropertyFlags::MIRROR_X, 80);
}

// The array that contains all the items
ItemInitFunction MapManager::ItemInitFunctions[] = {
	&InitScreen0, &InitScreen1, 
};

// compute the number of items
const unsigned char MapManager::PUZZLE_SCREEN_COUNT = sizeof(MapManager::ItemInitFunctions) / sizeof(ItemInitFunction);
