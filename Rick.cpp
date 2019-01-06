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
	int x = 15;
	int y = 22;
	
	// orientation of Rick
	bool IsLookingLeft = true;
	
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
	
	//debug test code to place a dynamite
	if (Input::IsJustPressed(A_BUTTON))
		((Dynamite*)(MapManager::Items[4]))->LightUp(x,y);
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
	// draw the collision sprite on the side where Rick is moving
	bool collision = arduboy.drawBitmapExtended(x, y, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, TRANSPARENT, IsLookingLeft);
	
	if (collision)
	{
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
bool Rick::CheckCollisionWithPickUp(PickUpItem * item)
{
	bool collisionDetected = arduboy.drawBitmapExtended(x, y, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, BLACK, IsLookingLeft);
	
	if (collisionDetected)
		item->PickUp();
	
	return !collisionDetected;
}

void Rick::Draw()
{
	arduboy.drawBitmapExtended(x, y, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, WHITE, IsLookingLeft);
}
