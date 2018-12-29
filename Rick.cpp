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
	
	// orientation of Rick
	bool IsLookingLeft = true;
	
	void HandleInput();
	void SetNextAnimFrame(unsigned char startFrameId, unsigned char endFrameId);
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
			CurrentAnimFrame = SpriteData::RickAnimFrameId::WALK_START;
			State = AnimState::WALK;
			IsLookingLeft = true;
		}
		
		if (arduboy.everyXFrames(ANIM_SPEED))
		{
			x--;
			SetNextAnimFrame(SpriteData::RickAnimFrameId::WALK_START, SpriteData::RickAnimFrameId::WALK_END);
		}
	}
	else if (Input::IsDown(RIGHT_BUTTON))
	{
		// reset anim frame to the first frame of the walk, and set the state
		if (Input::IsJustPressed(RIGHT_BUTTON))
		{
			CurrentAnimFrame = SpriteData::RickAnimFrameId::WALK_START;
			State = AnimState::WALK;
			IsLookingLeft = false;
		}
		if (arduboy.everyXFrames(ANIM_SPEED))
		{
			x++;
			SetNextAnimFrame(SpriteData::RickAnimFrameId::WALK_START, SpriteData::RickAnimFrameId::WALK_END);
		}
	}
	else
	{
		// reset the state to idle by default
		State = AnimState::IDLE;
		CurrentAnimFrame = SpriteData::RickAnimFrameId::IDLE;
	}
}

void Rick::SetNextAnimFrame(unsigned char startFrameId, unsigned char endFrameId)
{
	// increase the current frame to the next one
	CurrentAnimFrame++;
	// check if we need to loop the animation
	if (CurrentAnimFrame > endFrameId)
		CurrentAnimFrame = startFrameId;
}

void Rick::Draw()
{
	arduboy.drawBitmapExtended(x, y, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, WHITE, IsLookingLeft);
}
