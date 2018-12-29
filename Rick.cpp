/*
* Rick file handle the main character.
*/

#include "RickArdurous.h"
#include "Rick.h"
#include "SpriteData.h"
#include "Input.h"

namespace Rick
{
	const int ANIM_SPEED = 3;
	
	// state of Rick
	enum AnimState
	{
		IDLE = 0,
		WALK,
		FIRE,
	};
	
	// the current state of Rick
	AnimState State = AnimState::IDLE;
	unsigned char CurrentAnimFrame = 0;
	
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
	// check the input
	if (Input::IsDown(LEFT_BUTTON))
	{
		// reset anim frame to the first frame of the walk, and set the state
		if (Input::IsJustPressed(LEFT_BUTTON))
		{
			CurrentAnimFrame = 0;
			State = AnimState::WALK;
		}
		
		if (arduboy.everyXFrames(ANIM_SPEED))
		{
			x--;
			CurrentAnimFrame = (CurrentAnimFrame + 1) % 4;
		}
	}
	else if (Input::IsDown(RIGHT_BUTTON))
	{
		// reset anim frame to the first frame of the walk, and set the state
		if (Input::IsJustPressed(LEFT_BUTTON))
		{
			CurrentAnimFrame = 0;
			State = AnimState::WALK;
		}
		if (arduboy.everyXFrames(ANIM_SPEED))
		{
			x++;
			CurrentAnimFrame = (CurrentAnimFrame + 1) % 4;
		}
	}
	else
	{
		// reset the state to idle by default
		State = AnimState::IDLE;
		CurrentAnimFrame = 0;
	}
}

void Rick::Draw()
{
	arduboy.drawBitmap(x, y, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, WHITE);
}
