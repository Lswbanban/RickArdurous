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
#include "Graal.h"
#include "BulletCrate.h"
#include "Enemy.h"
#include "DestroyableBlock.h"
#include "Stalactite.h"
#include "Stalagmite.h"
#include "Boulder.h"
#include <avr/pgmspace.h>

#define ID(id1,id2) ((id1<< 4) | id2)

const unsigned char MapManager::Level[] PROGMEM = {
	ID(3,2),ID(1,2),ID(1,3),ID(1,3),ID(1,2),ID(1,2),ID(3,1),ID(2,2),ID(15,15),ID(15,1),
	ID(1,1),ID(0,0),ID(15,1),ID(11,11),ID(11,0),ID(11,15),ID(1,11),ID(0,11),ID(0,1),ID(15,15),ID(15,1),
	ID(2,0),ID(15,13),ID(0,15),ID(15,15),ID(1,0),
	ID(0,15),ID(15,15),ID(15,15),ID(1,0),
	ID(15,15),ID(15,15),ID(15,2),
	ID(15,14),ID(7,3),ID(15,15),ID(15,1),
	ID(15,12),ID(7,2),ID(1,2),ID(15,15),ID(15,1),
	ID(5,5),ID(4,15),ID(15,15),ID(14,0),
	ID(1,0),ID(11,11),ID(11,11),ID(11,11),ID(11,11),ID(11,11),ID(11,2),ID(1,1),ID(1,2),ID(1,1),ID(1,2),ID(1,1),ID(1,1),ID(2,1),ID(1,1),ID(1,1),
	ID(8,15),ID(12,1),ID(0,0),ID(0,2),ID(1,2),ID(1,11),ID(15,3),ID(11,0),ID(11,15),ID(2,0),ID(1,0),
	ID(8,15),ID(2,11),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(3,0),ID(15,4),ID(0,2),ID(0,15),ID(10,8),
	ID(8,15),ID(4,11),ID(11,11),ID(0,1),ID(2,0),ID(11,15),ID(15,15),ID(1,7),ID(3,1),
	ID(1,7),ID(15,7),ID(0,11),ID(15,4),ID(7,3),ID(3,3),ID(3,7),ID(15,10),ID(1,0),
	ID(1,1),ID(3,3),ID(3,0),ID(11,15),ID(8,8),ID(1,2),ID(2,1),ID(3,3),ID(7,15),ID(2,7),ID(3,7),ID(15,3),ID(8,0),
	ID(1,2),ID(1,2),ID(8,15),ID(10,8),ID(2,1),ID(1,2),ID(2,1),ID(8,15),ID(2,8),ID(2,1),ID(7,15),ID(2,2),
	ID(2,1),ID(1,1),ID(2,2),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(3,1),ID(2,2),ID(1,2),ID(1,2),ID(1,1),ID(1,1),ID(1,2),ID(8,15),ID(2,8),
	ID(2,2),ID(2,0),ID(11,11),ID(0,2),ID(1,1),ID(1,1),ID(1,0),ID(11,11),ID(11,11),ID(11,11),ID(11,11),ID(11,11),ID(0,11),ID(0,11),ID(11,15),ID(2,1),
	ID(1,0),ID(11,15),ID(5,11),ID(4,6),ID(11,15),ID(15,15),ID(4,8),
	ID(2,15),ID(14,7),ID(1,12),ID(12,14),ID(12,12),ID(12,12),ID(15,1),ID(2,1),ID(15,2),ID(7,3),ID(1,0),
	ID(1,15),ID(2,7),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(3,6),ID(4,5),ID(1,15),ID(2,13),ID(15,5),ID(1,1),ID(15,2),ID(1,1),ID(1,0),
	ID(5,15),ID(2,0),ID(1,2),ID(0,11),ID(11,15),ID(1,11),ID(11,0),ID(1,6),ID(5,1),ID(15,2),ID(13,15),ID(5,2),ID(1,15),ID(2,1),ID(2,1),
	ID(6,15),ID(3,11),ID(15,8),ID(11,11),ID(1,1),ID(15,2),ID(13,15),ID(3,7),ID(3,2),ID(1,15),ID(2,1),ID(1,2),
	ID(1,7),ID(15,13),ID(2,1),ID(7,15),ID(1,13),ID(15,9),ID(2,1),ID(1,0),
	ID(2,2),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(3,7),ID(15,2),ID(7,1),ID(1,1),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(1,1),ID(1,1),
	ID(1,11),ID(11,11),ID(11,11),ID(11,11),ID(11,11),ID(11,11),ID(15,2),ID(4,5),ID(1,11),ID(11,0),ID(5,4),ID(5,0),ID(11,11),ID(11,11),ID(11,11),ID(11,0),
	ID(6,15),ID(11,14),ID(12,5),ID(6,1),ID(15,5),ID(6,15),ID(9,0),
	ID(5,15),ID(2,12),ID(12,12),ID(12,5),ID(15,4),ID(13,9),ID(9,5),ID(1,3),ID(14,2),ID(5,6),ID(5,15),ID(9,0),
	ID(5,6),ID(15,5),ID(6,15),ID(4,13),ID(10,10),ID(6,1),ID(1,13),ID(1,1),ID(4,5),ID(12,14),ID(12,12),ID(12,12),ID(12,12),ID(5,0),
	ID(4,5),ID(15,5),ID(4,12),ID(12,12),ID(12,12),ID(0,5),ID(5,0),ID(15,2),ID(11,0),ID(1,5),ID(15,1),ID(13,15),ID(6,1),
	ID(6,9),ID(9,12),ID(12,14),ID(12,11),ID(15,7),ID(6,15),ID(5,0),ID(6,4),ID(5,3),ID(7,15),ID(4,1),
	ID(5,10),ID(10,15),ID(2,13),ID(15,12),ID(5,15),ID(10,7),ID(3,1),
	ID(4,5),ID(6,5),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(3,6),ID(4,5),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(1,1),
};

const unsigned int MapManager::LevelLineIndex[] PROGMEM = {0,10,21,26,30,33,37,42,46,62,73,84,93,102,115,127,143,159,166,177,192,207,219,227,243,259,266,278,292,305,316,323,339,};

Statuette statuette1;
Graal graal1;
Enemy enemy1;
Enemy enemy2;
Stalagmite stalagmite1;
Stalagmite stalagmite2;
Stalactite stalactite1;
DestroyableBlock destBlock1;

void InitScreen0(bool shouldRespawn)
{
	// Add a checkpoint if we need to

	// init all the item of the current puzzle screen
	stalagmite1.Init(13, 48, Item::PropertyFlags::NONE, shouldRespawn);
	stalagmite2.Init(117, 32, Item::PropertyFlags::NONE, shouldRespawn);
}

void InitScreen1(bool shouldRespawn)
{
	// Add a checkpoint if we need to
	MapManager::MemorizeCheckPoint(64, 67);

	// init all the item of the current puzzle screen
}

void InitScreen2(bool shouldRespawn)
{
	// Add a checkpoint if we need to

	// init all the item of the current puzzle screen
}

void InitScreen3(bool shouldRespawn)
{
	// Add a checkpoint if we need to

	// init all the item of the current puzzle screen
}

void InitScreen4(bool shouldRespawn)
{
	// Add a checkpoint if we need to

	// init all the item of the current puzzle screen
}

void InitScreen5(bool shouldRespawn)
{
	// Add a checkpoint if we need to

	// init all the item of the current puzzle screen
}

void InitScreen6(bool shouldRespawn)
{
	// Add a checkpoint if we need to
	MapManager::MemorizeCheckPoint(131, 234);

	// init all the item of the current puzzle screen
	statuette1.Init(166, 200, Item::PropertyFlags::NONE, shouldRespawn);
	graal1.Init(250, 207, Item::PropertyFlags::NONE, shouldRespawn);
	enemy1.Init(207, 202, Item::PropertyFlags::SPECIAL_2, shouldRespawn);
	destBlock1.Init(184, 240, Item::PropertyFlags::NONE, shouldRespawn);
	stalactite1.Init(237, 195, Item::PropertyFlags::NONE, shouldRespawn);
	enemy2.Init(213, 244, Item::PropertyFlags::SPECIAL, shouldRespawn);
}

// The array that contains all the items
ItemInitFunction MapManager::ItemInitFunctions[] = {
	&InitScreen0, &InitScreen1, &InitScreen2, &InitScreen3, &InitScreen4, &InitScreen5, &InitScreen6, 
};


// this function is to save and load the living status of the items
void MapManager::SaveAndLoadAliveStatusForAllItems(unsigned char currentScreenIdToSave, unsigned char newScreenIdToLoad)
{
	statuette1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	graal1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	enemy1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	enemy2.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	stalagmite1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	stalagmite2.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	stalactite1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	destBlock1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
}
