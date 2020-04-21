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
#include "Progress.h"
#include <avr/pgmspace.h>

#define ID(id1,id2) ((id1<< 4) | id2)

const unsigned char MapManager::Level[] PROGMEM = {
	ID(2,1),ID(2,0),ID(5,15),ID(4,5),ID(1,2),ID(2,1),ID(2,5),ID(15,15),ID(15,1),
	ID(1,1),ID(1,5),ID(15,6),ID(5,6),ID(1,1),ID(1,5),ID(15,15),ID(15,1),
	ID(2,2),ID(6,15),ID(13,0),ID(15,15),
	ID(1,5),ID(5,15),ID(5,5),ID(15,7),ID(0,15),ID(15,0),
	ID(2,5),ID(15,6),ID(10,10),ID(10,10),ID(10,10),ID(12,15),ID(1,0),ID(15,15),
	ID(1,6),ID(15,4),ID(10,15),ID(7,11),ID(15,15),ID(15,2),
	ID(1,5),ID(15,3),ID(10,15),ID(2,4),ID(3,3),ID(7,15),ID(2,11),ID(15,15),ID(15,2),
	ID(2,5),ID(5,0),ID(5,0),ID(5,6),ID(0,1),ID(2,6),ID(15,2),ID(11,15),ID(1,0),ID(15,15),
	ID(15,14),ID(11,15),ID(1,0),ID(15,15),
	ID(15,14),ID(11,15),ID(1,0),ID(15,15),
	ID(15,15),ID(15,15),ID(15,2),
	ID(15,15),ID(15,15),ID(15,2),
	ID(15,15),ID(15,15),ID(15,2),
	ID(15,15),ID(15,15),ID(15,2),
	ID(15,15),ID(15,15),ID(15,2),
	ID(15,15),ID(15,15),ID(15,2),
};

const unsigned int MapManager::LevelLineIndex[] PROGMEM = {0,9,17,21,27,35,41,50,60,64,68,71,74,77,80,83,};

Spike spike1;
Spike spike2;
Enemy enemy1;
Enemy enemy2;
Enemy enemy3;

void InitScreen0(bool shouldRespawn)
{
	// Add a checkpoint if we need to
	MapManager::MemorizeCheckPoint(40, 30);

	// init all the item of the current puzzle screen
	spike1.Init(34, 16, Item::PropertyFlags::SPECIAL);
	spike2.Init(66, 6, Item::PropertyFlags::NONE);
	enemy1.Init(83, 17, Item::PropertyFlags::SPECIAL_2, shouldRespawn);
	enemy2.Init(70, 34, Item::PropertyFlags::NONE, shouldRespawn);
	enemy3.Init(30, 50, Item::PropertyFlags::SPECIAL, shouldRespawn);
}

void InitScreen1(bool shouldRespawn)
{
	// Add a checkpoint if we need to

	// init all the item of the current puzzle screen
}

// The array that contains all the items
ItemInitFunction MapManager::ItemInitFunctions[] = {
	&InitScreen0, &InitScreen1, 
};

// compute the number of items
const unsigned char MapManager::PUZZLE_SCREEN_COUNT = sizeof(MapManager::ItemInitFunctions) / sizeof(ItemInitFunction);

// this function is to init the progress of the living items in eeprom
void MapManager::InitProgress()
{
	Progress::InitItem(&enemy1, 0);
	Progress::InitItem(&enemy2, 1);
	Progress::InitItem(&enemy3, 2);
}
