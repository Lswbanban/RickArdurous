/*
* Rick file handle the main character.
*/

#include "RickArdurous.h"
#include "Rick.h"
#include "SpriteData.h"
#include "Input.h"
#include "Dynamite.h"
#include "MapData.h"
#include "PickUpItem.h"

namespace Rick
{
	const int WALK_ANIM_SPEED = 3;
	const int JUMP_ANIM_SPEED = 3;
	const int MAX_JUMP_UP_FRAME_COUNT = 5;
	
	// state of Rick
	enum AnimState
	{
		IDLE = 0,
		WALK,
		JUMP,
		FIRE,
	};
	
	// the current state of Rick
	AnimState State = AnimState::IDLE;
	unsigned char CurrentAnimFrame = 0;
	
	// position of Rick
	int x = 15;
	int y = 22;
	
	// orientation of Rick
	bool IsLookingLeft = true;
	
	// variable for the jump state
	unsigned char JumpUpFrameCount = 0;
	char JumpAirSpeedX = 0;
	
	// Inventory
	char LifeCount = MAX_LIFE_COUNT;
	char StatuetteCount = 0;
	char BulletCount = MAX_BULLET_COUNT;
	char DynamiteCount = MAX_DYNAMITE_COUNT;
	
	void HandleInput();
	void SetNextAnimFrame(unsigned char startFrameId, unsigned char endFrameId);
}

void Rick::Update()
{
	HandleInput();
}

void Rick::HandleInput()
{
	// handle the input differently according to the current state
	if (State == AnimState::JUMP)
	{
		if (arduboy.everyXFrames(JUMP_ANIM_SPEED))
		{
			// increase the jump frame counter
			JumpUpFrameCount++;
			
			// move up or down, depending on the phase of the jump
			if (JumpUpFrameCount < MAX_JUMP_UP_FRAME_COUNT)
				y--;
			else
				y++;
			
			// do air control
			if (Input::IsDown(LEFT_BUTTON))
				JumpAirSpeedX = -1;
			else if (Input::IsDown(RIGHT_BUTTON))
				JumpAirSpeedX = 1;
			
			// move the x according to the air speed
			x += JumpAirSpeedX;
		}
	}
	else
	{
		// check if we start a the jump
		if (Input::IsJustPressed(B_BUTTON))
		{
			State = AnimState::JUMP;
			CurrentAnimFrame = SpriteData::RickAnimFrameId::IDLE;
			JumpUpFrameCount = 0;
		}
		else if (Input::IsDown(LEFT_BUTTON))
		{
			// reset anim frame to the first frame of the walk, and set the state
			if (Input::IsJustPressed(LEFT_BUTTON))
			{
				CurrentAnimFrame = SpriteData::RickAnimFrameId::WALK_START;
				State = AnimState::WALK;
				IsLookingLeft = true;
				JumpAirSpeedX = -1;
			}
			
			if (arduboy.everyXFrames(WALK_ANIM_SPEED))
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
				JumpAirSpeedX = 1;
			}
			if (arduboy.everyXFrames(WALK_ANIM_SPEED))
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
			JumpAirSpeedX = 0;
		}
		
		//debug test code to place a dynamite
		if (Input::IsJustPressed(A_BUTTON))
			((Dynamite*)(MapManager::Items[4]))->LightUp(x,y);
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

/**
 * Check if Rick is colliding with a static wall, floor, and ceiling and prevent him to move.
 */
void Rick::CheckStaticCollision()
{
	// first check the floor collisions
	if ((arduboy.getPixel(x+2, y+13) == WHITE) || (arduboy.getPixel(x+9, y+13) == WHITE))
	{
		y--;
		if (State == AnimState::JUMP)
			State = AnimState::IDLE;
	}
	
	// draw rick sprite to check the wall collisions
	bool wallCollision = arduboy.drawBitmapExtended(x, y, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, TRANSPARENT, IsLookingLeft);
	
	if (wallCollision)
	{
		JumpAirSpeedX = 0;
		if (IsLookingLeft)
			x++;
		else
			x--;
	}
}

/**
 * Chekc if Rick collides with any pixel that will kill him.
 */
void Rick::CheckLethalCollision()
{
	bool collisionDetected = arduboy.drawBitmapExtended(x, y, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, BLACK, IsLookingLeft);
	
	if (collisionDetected)
	{
		if (LifeCount > 0)
			LifeCount--;
		x = 15;
	}
}

/**
 * Check if Rick collides with any pixel from the frame buffer, and if yes, assume those pixels
 * belongs to the specified Pickup item, and then pick up that specified item.
 * @return if true, that means, you can continue to check collision, otherwise that means Rick already pickup an item this frame.
 */
void Rick::CheckCollisionWithPickUp(PickUpItem * item)
{
	if (arduboy.drawBitmapExtended(x, y, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, BLACK, IsLookingLeft))
		item->PickUp();
}

void Rick::Draw()
{
	arduboy.drawBitmapExtended(x, y, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, WHITE, IsLookingLeft);
}
