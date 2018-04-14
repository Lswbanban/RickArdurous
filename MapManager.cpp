/**
* The Map Manager handle the drawing of the map
*/
#include "RickArdurous.h"
#include "MapManager.h"
#include "SpriteData.h"

void MapManager::Update()
{
	for (int i = 0; i < 10; ++i)
		arduboy.drawBitmap(8*i, 10, SpriteData::Walls[0], 8, 8, WHITE);
	
}