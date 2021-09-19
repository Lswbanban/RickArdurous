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
	ID(3,2),ID(1,2),ID(1,3),ID(1,3),ID(1,2),ID(1,2),ID(3,1),ID(2,2),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),ID(5,5),
	ID(1,1),ID(0,0),ID(15,1),ID(11,0),ID(11,0),ID(0,15),ID(1,11),ID(0,11),ID(0,1),ID(5,15),ID(14,5),
	ID(2,0),ID(15,13),ID(0,5),ID(15,14),ID(5,0),
	ID(0,15),ID(15,5),ID(15,14),ID(5,0),
	ID(15,15),ID(15,1),ID(5,15),ID(11,13),ID(15,2),ID(5,0),
	ID(15,14),ID(7,3),ID(5,15),ID(11,13),ID(15,2),ID(5,0),
	ID(15,12),ID(7,2),ID(1,2),ID(5,15),ID(11,13),ID(15,2),ID(5,0),
	ID(5,5),ID(4,15),ID(13,5),ID(15,11),ID(13,15),ID(2,5),
	ID(4,5),ID(1,2),ID(1,2),ID(1,0),ID(0,0),ID(5,5),ID(5,5),ID(5,5),ID(1,1),ID(4,4),ID(15,8),ID(13,15),ID(2,5),
	ID(6,2),ID(1,0),ID(15,1),ID(0,15),ID(11,0),ID(5,1),ID(15,8),ID(13,15),ID(2,5),
	ID(5,0),ID(15,15),ID(15,11),ID(13,15),ID(2,5),
	ID(5,15),ID(11,12),ID(14,12),ID(12,12),ID(12,15),ID(1,3),ID(15,8),ID(13,15),ID(2,5),
	ID(8,15),ID(12,13),ID(15,2),ID(1,15),ID(1,7),ID(1,15),ID(8,13),ID(15,2),ID(5,0),
	ID(6,15),ID(4,9),ID(9,15),ID(6,13),ID(15,2),ID(1,15),ID(11,13),ID(15,2),ID(5,0),
	ID(5,15),ID(4,10),ID(10,15),ID(6,13),ID(15,2),ID(2,7),ID(15,10),ID(13,15),ID(2,5),
	ID(5,5),ID(6,5),ID(5,6),ID(5,5),ID(6,5),ID(5,5),ID(5,5),ID(5,5),ID(2,2),ID(3,3),ID(3,3),ID(3,3),ID(5,5),ID(5,5),ID(5,5),ID(5,5),
};

const unsigned int MapManager::LevelLineIndex[] PROGMEM = {0,16,27,32,36,42,48,55,61,74,83,88,97,106,115,124,140,};

Graal graal1;
Enemy enemy1;
Stalagmite stalagmite1;
Stalagmite stalagmite2;
Stalactite stalactite1;
ArrowLauncher arrowLauncher1;
DestroyableBlock destBlock1;
Boulder boulder1;

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
	MapManager::MemorizeCheckPoint(13, 106);

	// init all the item of the current puzzle screen
	stalagmite1.Init(49, 96, Item::PropertyFlags::NONE, shouldRespawn);
	destBlock1.Init(72, 112, Item::PropertyFlags::NONE, shouldRespawn);
	enemy1.Init(89, 106, Item::PropertyFlags::NONE, shouldRespawn);
	stalactite1.Init(74, 70, Item::PropertyFlags::NONE, shouldRespawn);
	boulder1.Init(10, 90, Item::PropertyFlags::NONE);
	//boulder1.Init(70, 90, Item::PropertyFlags::MIRROR_X);
}

void InitScreen2(bool shouldRespawn)
{
	// Add a checkpoint if we need to

	// init all the item of the current puzzle screen
	destBlock1.Init(145, 80, Item::PropertyFlags::NONE, shouldRespawn);
	arrowLauncher1.Init(191, 104, Item::PropertyFlags::MIRROR_X, 80);
}

void InitScreen3(bool shouldRespawn)
{
	// Add a checkpoint if we need to

	// init all the item of the current puzzle screen
	graal1.Init(224, 23, Item::PropertyFlags::NONE, shouldRespawn);
}

// The array that contains all the items
ItemInitFunction MapManager::ItemInitFunctions[] = {
	&InitScreen0, &InitScreen1, &InitScreen2, &InitScreen3, 
};


// this function is to save and load the living status of the items
void MapManager::SaveAndLoadAliveStatusForAllItems(unsigned char currentScreenIdToSave, unsigned char newScreenIdToLoad)
{
	graal1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	enemy1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	stalagmite1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	stalagmite2.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	stalactite1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	destBlock1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
}
