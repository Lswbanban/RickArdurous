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
#include <avr/pgmspace.h>

#define ID(id1,id2) ((id1<< 4) | id2)

const unsigned char MapManager::Level[] PROGMEM = {
	ID(3,2),ID(1,2),ID(1,3),ID(1,3),ID(1,2),ID(1,2),ID(3,1),ID(2,2),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),
	ID(1,1),ID(0,0),ID(15,1),ID(11,0),ID(11,0),ID(0,15),ID(1,11),ID(0,11),ID(0,1),ID(5,15),ID(14,5),
	ID(2,0),ID(15,13),ID(0,5),ID(15,14),ID(5,0),
	ID(0,15),ID(15,5),ID(15,14),ID(5,0),
	ID(15,15),ID(15,1),ID(5,15),ID(14,5),
	ID(15,14),ID(7,3),ID(5,15),ID(14,5),
	ID(15,12),ID(7,2),ID(1,2),ID(5,15),ID(14,5),
	ID(5,5),ID(4,15),ID(15,15),ID(14,0),
	ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(1,15),ID(14,5),
	ID(5,15),ID(15,0),ID(15,14),ID(5,0),
	ID(5,15),ID(13,12),ID(15,15),ID(15,1),ID(5,0),
	ID(5,15),ID(4,5),ID(5,13),ID(11,11),ID(15,4),ID(12,15),ID(15,15),ID(1,5),
	ID(5,15),ID(6,12),ID(15,6),ID(12,15),ID(4,7),ID(3,7),ID(15,9),ID(5,0),
	ID(6,15),ID(6,12),ID(15,6),ID(12,15),ID(3,7),ID(1,2),ID(1,7),ID(15,8),ID(5,0),
	ID(5,15),ID(6,12),ID(15,6),ID(12,15),ID(2,7),ID(1,2),ID(2,1),ID(1,7),ID(15,7),ID(5,0),
	ID(5,5),ID(6,5),ID(5,6),ID(5,5),ID(6,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),
};

const unsigned int MapManager::LevelLineIndex[] PROGMEM = {0,16,27,32,36,40,44,49,53,63,67,72,80,88,97,107,123,};

DynamiteCrate dynamiteCrate1;
Graal graal1;
Enemy enemy1;
Stalagmite stalagmite1;
Stalagmite stalagmite2;
ArrowLauncher arrowLauncher1;
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
	MapManager::MemorizeCheckPoint(40, 106);

	// init all the item of the current puzzle screen
	stalagmite1.Init(105, 113, Item::PropertyFlags::NONE, shouldRespawn);
	enemy1.Init(48, 85, Item::PropertyFlags::SPECIAL, shouldRespawn);
	arrowLauncher1.Init(8, 98, Item::PropertyFlags::NONE, 80);
	dynamiteCrate1.Init(14, 112, Item::PropertyFlags::NONE, shouldRespawn);
	destBlock1.Init(81, 113, Item::PropertyFlags::NONE, shouldRespawn);
}

void InitScreen2(bool shouldRespawn)
{
	// Add a checkpoint if we need to

	// init all the item of the current puzzle screen
	graal1.Init(227, 113, Item::PropertyFlags::NONE, shouldRespawn);
	destBlock1.Init(159, 89, Item::PropertyFlags::NONE, shouldRespawn);
}

// The array that contains all the items
ItemInitFunction MapManager::ItemInitFunctions[] = {
	&InitScreen0, &InitScreen1, &InitScreen2, 
};


// this function is to save and load the living status of the items
void MapManager::SaveAndLoadAliveStatusForAllItems(unsigned char currentScreenIdToSave, unsigned char newScreenIdToLoad)
{
	dynamiteCrate1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	graal1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	enemy1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	stalagmite1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	stalagmite2.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	destBlock1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
}
