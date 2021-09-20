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
	ID(3,2),ID(1,2),ID(1,3),ID(1,3),ID(1,2),ID(1,2),ID(3,1),ID(2,2),ID(15,15),ID(15,1),
	ID(1,1),ID(0,0),ID(15,1),ID(11,11),ID(11,0),ID(11,15),ID(1,11),ID(0,11),ID(0,1),ID(15,15),ID(15,1),
	ID(2,0),ID(15,13),ID(0,15),ID(15,15),ID(1,0),
	ID(0,15),ID(15,15),ID(15,15),ID(1,0),
	ID(15,15),ID(15,15),ID(15,2),
	ID(15,14),ID(7,3),ID(15,15),ID(15,1),
	ID(15,12),ID(7,2),ID(1,2),ID(15,15),ID(15,1),
	ID(5,5),ID(4,15),ID(15,15),ID(14,0),
	ID(1,0),ID(11,11),ID(11,11),ID(11,11),ID(11,11),ID(11,11),ID(11,11),ID(11,1),ID(1,2),ID(1,1),ID(1,2),ID(1,1),ID(1,1),ID(2,1),ID(1,1),ID(1,1),
	ID(2,15),ID(14,1),ID(0,0),ID(1,2),ID(0,11),ID(15,3),ID(11,0),ID(11,15),ID(2,0),ID(1,0),
	ID(1,15),ID(2,7),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(3,0),ID(11,11),ID(15,2),ID(6,5),ID(15,11),ID(2,0),
	ID(1,15),ID(8,0),ID(2,1),ID(0,15),ID(15,15),ID(1,7),ID(3,1),
	ID(1,7),ID(15,8),ID(0,0),ID(15,3),ID(3,3),ID(3,3),ID(3,7),ID(15,10),ID(1,0),
	ID(1,1),ID(3,3),ID(3,3),ID(7,15),ID(8,1),ID(1,2),ID(2,1),ID(3,3),ID(7,15),ID(2,7),ID(3,7),ID(15,3),ID(1,0),
	ID(1,2),ID(1,2),ID(1,1),ID(15,8),ID(3,2),ID(2,1),ID(1,2),ID(2,1),ID(1,15),ID(2,1),ID(2,1),ID(7,15),ID(2,2),
	ID(2,1),ID(1,1),ID(2,1),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(3,1),ID(2,2),ID(1,2),ID(1,2),ID(1,1),ID(1,1),ID(1,2),ID(1,15),ID(2,1),
	ID(15,15),ID(15,1),ID(11,11),ID(11,11),ID(11,11),ID(11,11),ID(0,11),ID(0,11),ID(11,15),ID(2,1),
	ID(15,15),ID(15,15),ID(15,1),ID(1,0),
	ID(15,15),ID(15,1),ID(1,12),ID(12,14),ID(12,12),ID(12,12),ID(15,1),ID(2,2),ID(15,2),ID(7,3),ID(1,0),
	ID(15,15),ID(15,1),ID(1,15),ID(2,13),ID(15,5),ID(1,2),ID(15,2),ID(1,1),ID(1,0),
	ID(15,15),ID(15,1),ID(1,15),ID(2,13),ID(15,5),ID(2,2),ID(15,2),ID(1,1),ID(1,0),
	ID(15,15),ID(15,1),ID(1,15),ID(2,13),ID(15,3),ID(7,3),ID(2,1),ID(15,2),ID(1,1),ID(1,0),
	ID(15,15),ID(15,1),ID(1,7),ID(15,1),ID(13,15),ID(9,1),ID(1,1),
	ID(15,15),ID(15,1),ID(1,1),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(3,3),ID(1,1),ID(1,1),
};

const unsigned int MapManager::LevelLineIndex[] PROGMEM = {0,10,21,26,30,33,37,42,46,62,72,84,91,100,113,126,142,152,156,167,176,185,195,202,212,};

Statuette statuette1;
Graal graal1;
Spike spike1;
Spike spike2;
Spike spike3;
Spike spike4;
Spike spike5;
Spike spike6;
Enemy enemy1;
Stalagmite stalagmite1;
Stalagmite stalagmite2;

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
	MapManager::MemorizeCheckPoint(69, 67);

	// init all the item of the current puzzle screen
}

void InitScreen2(bool shouldRespawn)
{
	// Add a checkpoint if we need to
	MapManager::MemorizeCheckPoint(132, 83);

	// init all the item of the current puzzle screen
	stalagmite1.Init(193, 112, Item::PropertyFlags::NONE, shouldRespawn);
	stalagmite2.Init(185, 112, Item::PropertyFlags::NONE, shouldRespawn);
	statuette1.Init(235, 80, Item::PropertyFlags::NONE, shouldRespawn);
}

void InitScreen3(bool shouldRespawn)
{
	// Add a checkpoint if we need to
	MapManager::MemorizeCheckPoint(236, 131);

	// init all the item of the current puzzle screen
	statuette1.Init(190, 160, Item::PropertyFlags::NONE, shouldRespawn);
	graal1.Init(139, 135, Item::PropertyFlags::NONE, shouldRespawn);
	spike1.Init(216, 165, Item::PropertyFlags::MIRROR_X);
	spike2.Init(216, 169, Item::PropertyFlags::MIRROR_X);
	spike3.Init(196, 159, Item::PropertyFlags::NONE);
	spike4.Init(196, 153, Item::PropertyFlags::NONE);
	spike5.Init(211, 136, Item::PropertyFlags::SPECIAL);
	spike6.Init(206, 136, Item::PropertyFlags::SPECIAL);
	enemy1.Init(161, 130, Item::PropertyFlags::SPECIAL_2, shouldRespawn);
}

// The array that contains all the items
ItemInitFunction MapManager::ItemInitFunctions[] = {
	&InitScreen0, &InitScreen1, &InitScreen2, &InitScreen3, 
};


// this function is to save and load the living status of the items
void MapManager::SaveAndLoadAliveStatusForAllItems(unsigned char currentScreenIdToSave, unsigned char newScreenIdToLoad)
{
	statuette1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	graal1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	enemy1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	stalagmite1.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
	stalagmite2.SaveAndLoadAliveStatus(currentScreenIdToSave, newScreenIdToLoad);
}
