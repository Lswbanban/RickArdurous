/*
* Rick file handle the main character.
*/

#include "RickArdurous.h"
#include "Rick.h"
#include "SpriteData.h"

namespace Rick
{
	// position of Rick
	int x = 0;
	int y = 20;
	
	void HandleInput();
	void Draw();
}

void Rick::Update()
{
	HandleInput();
	Draw();
}

void Rick::HandleInput()
{
	if (arduboy.pressed(LEFT_BUTTON))
		x--;
	if (arduboy.pressed(RIGHT_BUTTON))
		x++;
}

void Rick::Draw()
{
	arduboy.drawBitmap(x/3, y, SpriteData::Rick[(x/3)%4], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, WHITE);
}
