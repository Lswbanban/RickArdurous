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
	const int AIR_CONTROL_ANIM_SPEED = 6;
	const char JUMP_AND_FALL_VERTICAL_ANIM_SPEED[] = { 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5, 6 };
	const int JUMP_AND_FALL_VERTICAL_ANIM_SPEED_COUNT = sizeof(JUMP_AND_FALL_VERTICAL_ANIM_SPEED);
	
	// state of Rick
	enum AnimState
	{
		IDLE = 0,
		WALK,
		JUMP,
		FALL,
		FIRE,
	};
	
	// the current state of Rick
	AnimState State = AnimState::IDLE;
	unsigned char CurrentAnimFrame = 0;
	
	// position of Rick
	int X = 15;
	int Y = 22;
	
	// orientation of Rick
	bool IsLookingLeft = true;
	
	// variable for the jump state
	unsigned char JumpAndFallFrameCount = 0;
	unsigned char JumpAndFallAnimSpeedIndex = 0;
	char AirSpeedX = 0;
	
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
	if ((State == AnimState::JUMP) || (State == AnimState::FALL))
	{
		// increase the frame counter for the jump, and switch to the next frame when needed
		JumpAndFallFrameCount++;
		if (JumpAndFallFrameCount >= JUMP_AND_FALL_VERTICAL_ANIM_SPEED[JumpAndFallAnimSpeedIndex])
		{
			JumpAndFallFrameCount = 0;
			if (State == AnimState::JUMP)
			{
				// move up
				Y--;
				// increase the jump frame counter and check if we need to change state to fall
				JumpAndFallAnimSpeedIndex++;
				if (JumpAndFallAnimSpeedIndex >= JUMP_AND_FALL_VERTICAL_ANIM_SPEED_COUNT)
				{
					State = AnimState::FALL;
					JumpAndFallAnimSpeedIndex--;
				}
			}
			else
			{
				// in fall state, move down
				Y++;
				// decrease the jump counter
				if (JumpAndFallAnimSpeedIndex > 0)
					JumpAndFallAnimSpeedIndex--;
			}
		}
		
		// move left or right while jumping or falling
		if (arduboy.everyXFrames(AIR_CONTROL_ANIM_SPEED))
		{
			// In jump or Fall state, we can do air control
			if (Input::IsDown(LEFT_BUTTON))
				AirSpeedX = -1;
			else if (Input::IsDown(RIGHT_BUTTON))
				AirSpeedX = 1;
			
			// move the X according to the air speed
			X += AirSpeedX;
		}
	}
	else
	{
		// check if we start a the jump
		if (Input::IsJustPressed(B_BUTTON))
		{
			State = AnimState::JUMP;
			CurrentAnimFrame = SpriteData::RickAnimFrameId::IDLE;
			JumpAndFallFrameCount = 0;
			JumpAndFallAnimSpeedIndex = 0;
		}
		else if (Input::IsDown(LEFT_BUTTON))
		{
			// reset anim frame to the first frame of the walk, and set the state
			if (Input::IsJustPressed(LEFT_BUTTON))
			{
				CurrentAnimFrame = SpriteData::RickAnimFrameId::WALK_START;
				State = AnimState::WALK;
				IsLookingLeft = true;
				AirSpeedX = -1;
			}
			
			if (arduboy.everyXFrames(WALK_ANIM_SPEED))
			{
				X--;
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
				AirSpeedX = 1;
			}
			if (arduboy.everyXFrames(WALK_ANIM_SPEED))
			{
				X++;
				SetNextAnimFrame(SpriteData::RickAnimFrameId::WALK_START, SpriteData::RickAnimFrameId::WALK_END);
			}
		}
		else
		{
			// reset the state to idle by default
			State = AnimState::IDLE;
			CurrentAnimFrame = SpriteData::RickAnimFrameId::IDLE;
			AirSpeedX = 0;
		}
		
		//debug test code to place a dynamite
		if (Input::IsJustPressed(A_BUTTON))
			((Dynamite*)(MapManager::Items[4]))->LightUp(X,Y);
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
	int yUnderFeet = Y + 13;
	if ((yUnderFeet < 64) && ((arduboy.getPixel(X + 2, yUnderFeet) == WHITE) || (arduboy.getPixel(X + 6, yUnderFeet) == WHITE)))
	{
		// We found a collision under the feet, so if we are falling, stop falling
		if (State == AnimState::FALL)
			State = AnimState::IDLE;
	}
	else
	{
		// There's no collision under the feet, and not jumping, then we fall
		if ((State != AnimState::JUMP) && (State != AnimState::FALL))
		{
			State = AnimState::FALL;
			JumpAndFallFrameCount = 0;
			JumpAndFallAnimSpeedIndex = JUMP_AND_FALL_VERTICAL_ANIM_SPEED_COUNT - 1;
		}
	}
	
	// draw rick sprite to check the wall collisions
	bool wallCollision = arduboy.drawBitmapExtended(X, Y, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, TRANSPARENT, IsLookingLeft);
	
	if (wallCollision)
	{
		AirSpeedX = 0;
		if (IsLookingLeft)
			X++;
		else
			X--;
	}
}

/**
 * Chekc if Rick collides with any pixel that will kill him.
 */
void Rick::CheckLethalCollision()
{
	bool collisionDetected = arduboy.drawBitmapExtended(X, Y, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, BLACK, IsLookingLeft);
	
	if (collisionDetected)
	{
		if (LifeCount > 0)
			LifeCount--;
		X = 15;
	}
}

/**
 * Check if Rick collides with any pixel from the frame buffer, and if yes, assume those pixels
 * belongs to the specified Pickup item, and then pick up that specified item.
 * @return if true, that means, you can continue to check collision, otherwise that means Rick already pickup an item this frame.
 */
void Rick::CheckCollisionWithPickUp(PickUpItem * item)
{
	if (arduboy.drawBitmapExtended(X, Y, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, BLACK, IsLookingLeft))
		item->PickUp();
}

void Rick::Draw()
{
	arduboy.drawBitmapExtended(X, Y, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, WHITE, IsLookingLeft);
}
