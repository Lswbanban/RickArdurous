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
	ID(1,5),ID(5,15),ID(13,0),ID(15,15),
	ID(2,5),ID(15,6),ID(10,10),ID(10,10),ID(10,10),ID(12,15),ID(1,0),ID(15,15),
	ID(1,6),ID(15,4),ID(10,15),ID(7,11),ID(15,15),ID(15,2),
	ID(1,5),ID(15,3),ID(10,15),ID(2,4),ID(3,3),ID(7,15),ID(2,11),ID(15,15),ID(15,2),
	ID(2,5),ID(5,0),ID(5,0),ID(5,6),ID(0,1),ID(2,6),ID(15,2),ID(11,15),ID(1,0),ID(15,15),
	ID(15,14),ID(11,15),ID(1,0),ID(15,15),
	ID(15,14),ID(11,15),ID(1,0),ID(15,15),
	ID(15,14),ID(11,15),ID(15,15),ID(2,0),
	ID(5,15),ID(4,5),ID(5,12),ID(15,6),ID(11,15),ID(15,15),ID(2,0),
	ID(5,15),ID(6,11),ID(15,6),ID(11,15),ID(3,4),ID(3,4),ID(15,11),
	ID(6,13),ID(15,5),ID(11,15),ID(6,11),ID(15,2),ID(4,2),ID(1,2),ID(15,11),
	ID(5,15),ID(6,11),ID(15,6),ID(11,15),ID(1,4),ID(1,1),ID(2,2),ID(15,11),
	ID(5,5),ID(6,5),ID(5,6),ID(5,5),ID(6,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,15),ID(11,0),
};

const unsigned int MapManager::LevelLineIndex[] PROGMEM = {0,9,17,21,25,33,39,48,58,62,66,70,77,84,92,100,112,};

const unsigned char MapManager::LEVEL_WIDTH = 32;
const unsigned char MapManager::LEVEL_HEIGHT = 16;
Enemy enemy1;

void InitScreen0(bool shouldRespawn)
{
	// Add a checkpoint if we need to
	MapManager::MemorizeCheckPoint(74, 35);

	// init all the item of the current puzzle screen
}

void InitScreen1(bool shouldRespawn)
{
	// Add a checkpoint if we need to

	// init all the item of the current puzzle screen
	enemy1.Init(41, 84, Item::PropertyFlags::SPECIAL, shouldRespawn);
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
}
