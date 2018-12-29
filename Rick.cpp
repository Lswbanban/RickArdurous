/*
* Rick file handle the main character.
*/

#include "RickArdurous.h"
#include "Rick.h"
#include "SpriteData.h"

namespace Rick
{
	// state of Rick
	enum AnimState
	{
		IDLE = 0,
		WALK,
		FIRE,
	};
	
	// the current state of Rick
	AnimState State = AnimState::IDLE;
	
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
	// reset the state to idle by default
	State = AnimState::IDLE;

	// check the input
	if (arduboy.pressed(LEFT_BUTTON))
	{
		State = AnimState::WALK;
		x--;
	}
	if (arduboy.pressed(RIGHT_BUTTON))
	{
		State = AnimState::WALK;
		x++;
	}
}

void Rick::Draw()
{
	int frameId = 0;
	if (State == AnimState::WALK)
		frameId = (x/3) % 4;
	
	arduboy.drawBitmap(x/3, y, SpriteData::Rick[frameId], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, WHITE);
}
