/*
* Rick file handle the main character.
*/

#include "RickArdurous.h"
#include "Rick.h"
#include "SpriteData.h"
#include "Input.h"
#include "Dynamite.h"
#include "ArrowBullet.h"
#include "MapData.h"
#include "PickUpItem.h"
#include "MapManager.h"

namespace Rick
{
	const int WALK_ANIM_SPEED = 3;
	const int NO_HORIZONTAL_MOVE_AIR_CONTROL_ANIM_SPEED = 1;
	const int MIN_AIR_CONTROL_ANIM_SPEED = 3;
	const int MAX_AIR_CONTROL_ANIM_SPEED = 8;
	const char JUMP_AND_FALL_VERTICAL_MOVE[] 		= { 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1 };
	const char JUMP_AND_FALL_VERTICAL_ANIM_SPEED[]	= { 1, 1, 1, 1, 1, 2, 2, 3, 3, 4, 5, 6 };
	const int JUMP_AND_FALL_VERTICAL_ANIM_SPEED_COUNT = sizeof(JUMP_AND_FALL_VERTICAL_ANIM_SPEED);
	const int FALL_VERTICAL_MIN_INDEX = 3; // this variable is used to limite the falling speed on a very long fall
	const int FIRE_ANIM_SPEED = 3;
	const int CROUCH_STAND_ANIM_SPEED = 3;
	const int CRAWL_ANIM_SPEED = 3;
	const int CLIMB_LADDER_ANIM_SPEED = 3;
	const int DEATH_ANIM_SPEED = 4;
	const int WIDTH_DIFF_BETWEEN_CRAWL_AND_STAND = SpriteData::RICK_CRAWL_SPRITE_WIDTH - SpriteData::RICK_SPRITE_WIDTH;
	const int DEATH_MOVING_SPEED = 16;
	const int DEATH_VELOCITY_X = 9;
	const int DEATH_VELOCITY_Y = -30;
	const int HALF_GRAVITY = 1;
	// The standing sprite are stored on 2 bytes vertically, whereas the crawl sprite only use one.
	// When switching from stand to crawl state, we don't change the Y, but just draw the sprite lower
	// Thia constant value, store the difference between those two sprites visually speaking
	const int VISUAL_HEIGHT_DIFF_BETWEEN_STAND_AND_CRAWL = 5;
	// The distance from the left edge of the sprite, from which we check the collision under the feet
	const int LEFT_X_SHIFT_FOR_COLLISION_UNDER_FEET = 2;
	const int RIGHT_X_SHIFT_FOR_COLLISION_UNDER_FEET_STAND = 6;
	const int RIGHT_X_SHIFT_FOR_COLLISION_UNDER_FEET_CRAWL = 9;
	
	// state of Rick
	enum AnimState
	{
		IDLE = 0,
		WALK,
		JUMP,
		FALL,
		FIRE,
		CROUCH_DOWN,
		STAND_UP,
		CRAWL,
		CLIMB_LADDER,
		DEATH,
	};
	
	// the current state of Rick
	AnimState State = AnimState::IDLE;
	unsigned char CurrentAnimFrame = 0;
	char CurrentAnimDirection = 1;
	bool IsAlive() { return State != AnimState::DEATH;}
	
	// position of Rick
	int X = 14;
	int Y = 4;
	int GetX() { return X; }
	int GetY() { return Y; }
	int GetCenterX() { return X + 4; }
	int GetCenterY() { return Y + 10; }
	
	// orientation of Rick
	bool IsLookingLeft = true;

	// variable for different states
	unsigned char StateFrameCounter = 0; // a generic frame counter that can be used by different states
	
	// variable for the jump state
	unsigned char JumpAndFallAnimSpeedIndex = 0;
	unsigned char AirControlAnimSpeed = NO_HORIZONTAL_MOVE_AIR_CONTROL_ANIM_SPEED;
	unsigned char AirControlFrameCount = 0;
	
	// variable for crawl state
	bool IsThereAnyCeilingAboveHead = false;
	bool ShouldWePlaceADynamite = false;
	
	// variable for the climb ladder state
	bool IsInFrontOfLadder = false;
	bool IsAboveLadder = false;
	
	// variable for death state
	int DeathStartX = 0;
	int DeathStartY = 0;
	
	// Inventory
	char LifeCount = MAX_LIFE_COUNT;
	char StatuetteCount = 0;
	char BulletCount = MAX_BULLET_COUNT;
	char DynamiteCount = MAX_DYNAMITE_COUNT;
	
	// all the dynamite instances
	Dynamite AllDynamites[MAX_DYNAMITE_COUNT];
	// all the bullet instances
	ArrowBullet AllBullets[MAX_BULLET_COUNT];
	
	void Respawn();
	void InitIdle();
	void InitFall();
	void InitCrouch();
	void InitCrawl();
	void InitStandUp();
	void InitClimbLadder();
	void InitDeath();
	bool IsDynamitePlacementRequested();
	void PlaceDynamite();
	void HandleInput();
	void SetNextAnimFrame(unsigned char startFrameId, unsigned char endFrameId, bool isLooping);
	void UpdateAirControl(bool towardLeftDirection);
	bool IsThereAnyGroundOrCeilingCollisionAt(int y);
	bool IsThereAnyCeilingAboveCrawl();
	bool IsOnScreen();
	unsigned int Draw(unsigned char color);
}

int Rick::GetLeftForScreenTransition()
{
	// remove 2, one for being the first pixel of the next screen,
	// and one because the last pixel of decor sprite is black,
	// therefore no collision would be detected during the first frame of the transition
	if (State == AnimState::CRAWL)
		return X + (LEFT_X_SHIFT_FOR_COLLISION_UNDER_FEET + 2);
	else
		return X + LEFT_X_SHIFT_FOR_COLLISION_UNDER_FEET;
}

int Rick::GetRightForScreenTransition()
{
	if (State == AnimState::CRAWL)
		return X + (RIGHT_X_SHIFT_FOR_COLLISION_UNDER_FEET_CRAWL - 1);
	else
		return X + RIGHT_X_SHIFT_FOR_COLLISION_UNDER_FEET_STAND;
}

int Rick::GetTopForScreenTransition()
{
	if (State == AnimState::CRAWL)
		return Y + (VISUAL_HEIGHT_DIFF_BETWEEN_STAND_AND_CRAWL + 2);
	else
		return Y + 2;
}

int Rick::GetBottomForScreenTransition()
{
	return Y + 10;
}

unsigned char Rick::GetFeetYOnScreen()
{
	int feetOnScreen = MapManager::GetYOnScreen(Y) + 12;
	if (State == AnimState::FALL)
		feetOnScreen -= JUMP_AND_FALL_VERTICAL_MOVE[JumpAndFallAnimSpeedIndex] + 1;
	if (feetOnScreen >= HEIGHT)
		feetOnScreen = HEIGHT-1;
	return feetOnScreen;
}

void Rick::Respawn()
{
	// temp code, just teleport to hard coded location
	X = 15;
	Y = 8;
	// start in idle state
	InitIdle();
}

void Rick::InitIdle()
{
	State = AnimState::IDLE;
	CurrentAnimFrame = SpriteData::RickAnimFrameId::IDLE;
	CurrentAnimDirection = 1;
	AirControlAnimSpeed = NO_HORIZONTAL_MOVE_AIR_CONTROL_ANIM_SPEED;
}

void Rick::InitFall()
{
	// special case for when I fall from the crawl state and there's ceiling above,
	// then we should teleport Rick below to avoid his head to collide in the ceiling
	if ((State == AnimState::CRAWL) && IsThereAnyCeilingAboveHead)
		Y += VISUAL_HEIGHT_DIFF_BETWEEN_STAND_AND_CRAWL;
	// then change the state and the other parameters
	State = AnimState::FALL;
	CurrentAnimFrame = SpriteData::RickAnimFrameId::JUMP;
	CurrentAnimDirection = 1;
	StateFrameCounter = 0;
	JumpAndFallAnimSpeedIndex = JUMP_AND_FALL_VERTICAL_ANIM_SPEED_COUNT - 1;
	AirControlFrameCount = 0;
}

void Rick::InitCrouch()
{
	State = AnimState::CROUCH_DOWN;
	CurrentAnimFrame = SpriteData::RickAnimFrameId::CROUCH_START;
	CurrentAnimDirection = 1;
}

void Rick::InitCrawl()
{
	// if the down button is still pressed, go to crawl state
	State = AnimState::CRAWL;
	CurrentAnimFrame = SpriteData::RickAnimFrameId::CRAWL_START;
	CurrentAnimDirection = 1;
	// if the rick is looking right, move x 3 pixel to the left for keeping the hat aligned with the idle animation
	if (!IsLookingLeft)
		X -= WIDTH_DIFF_BETWEEN_CRAWL_AND_STAND;
}

void Rick::InitStandUp()
{
	State = AnimState::STAND_UP;
	CurrentAnimFrame = SpriteData::RickAnimFrameId::STAND_UP_START;
	CurrentAnimDirection = -1;
	// if the rick is looking right, move x 3 pixel to the right for keeping the hat aligned with the idle animation
	if (!IsLookingLeft)
		X += WIDTH_DIFF_BETWEEN_CRAWL_AND_STAND;
}

void Rick::InitClimbLadder()
{
	State = AnimState::CLIMB_LADDER;
	CurrentAnimFrame = SpriteData::RickAnimFrameId::CLIMB_START;
	CurrentAnimDirection = 1;
	AirControlAnimSpeed = NO_HORIZONTAL_MOVE_AIR_CONTROL_ANIM_SPEED;
}

void Rick::InitDeath()
{
	State = AnimState::DEATH;
	CurrentAnimFrame = SpriteData::RickAnimFrameId::DEATH_START;
	CurrentAnimDirection = -1;
	DeathStartX = X;
	DeathStartY = Y;
	StateFrameCounter = 0;
	// decrease the life counter
	if (LifeCount > 0)
		LifeCount--;
}

bool Rick::IsDynamitePlacementRequested()
{
	if ((Input::IsJustPressed(A_BUTTON)) && (DynamiteCount > 0))
		for (int i = DynamiteCount-1; i >= 0; --i)
			if (!AllDynamites[i].IsPropertySet(Item::PropertyFlags::ALIVE))
				return true;
	return false;
}

void Rick::PlaceDynamite()
{
	// find an available dynamite and light it up
	for (int i = DynamiteCount-1; i >= 0; --i)
		if (!AllDynamites[i].IsPropertySet(Item::PropertyFlags::ALIVE))
		{
			AllDynamites[i].LightUp(X, Y + 5);
			DynamiteCount--;
			break;
		}
	// reset the dynamite placement flag 
	ShouldWePlaceADynamite = false;
}

void Rick::UpdateInput()
{
	// handle the input differently according to the current state
	if ((State == AnimState::JUMP) || (State == AnimState::FALL))
	{
		// increase the frame counter for the jump, and switch to the next frame when needed
		StateFrameCounter++;
		if (StateFrameCounter >= JUMP_AND_FALL_VERTICAL_ANIM_SPEED[JumpAndFallAnimSpeedIndex])
		{
			StateFrameCounter = 0;
			if (State == AnimState::JUMP)
			{
				// move up
				Y -= JUMP_AND_FALL_VERTICAL_MOVE[JumpAndFallAnimSpeedIndex];
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
				Y += JUMP_AND_FALL_VERTICAL_MOVE[JumpAndFallAnimSpeedIndex];
				// decrease the jump counter
				if (JumpAndFallAnimSpeedIndex > FALL_VERTICAL_MIN_INDEX)
					JumpAndFallAnimSpeedIndex--;
			}
		}
		
		// move left or right while jumping or falling
		AirControlFrameCount++;
		if (AirControlFrameCount >= AirControlAnimSpeed)
		{
			AirControlFrameCount = 0;
			// In jump or Fall state, we can do air control
			if (Input::IsDown(LEFT_BUTTON))
				UpdateAirControl(true);
			else if (Input::IsDown(RIGHT_BUTTON))
				UpdateAirControl(false);
			
			// move the X according to the orientation Rick, and if he didn't jump vertically
			if (AirControlAnimSpeed != NO_HORIZONTAL_MOVE_AIR_CONTROL_ANIM_SPEED)
			{
				if (IsLookingLeft)
					X--;
				else
					X++;
			}
		}
		
		// grab the ladder if we are in front of it
		if (IsInFrontOfLadder)
			InitClimbLadder();
	}
	else if (State == AnimState::FIRE)
	{
		// change the anim frame id if it is the time to
		if (arduboy.everyXFrames(FIRE_ANIM_SPEED))
			CurrentAnimFrame += CurrentAnimDirection;
		
		// check if we reach the end of the animation
		if (CurrentAnimFrame > SpriteData::RickAnimFrameId::FIRE_END)
		{
			// reset the anim frame to a correct value and reverse the anim direction
			CurrentAnimFrame = SpriteData::RickAnimFrameId::FIRE_END;
			CurrentAnimDirection = -1;
			
			// fire the bullet
			for (int i = BulletCount-1; i >= 0; --i)
				if (!AllBullets[i].IsPropertySet(Item::PropertyFlags::ALIVE))
				{
					AllBullets[i].Fire(IsLookingLeft ? X : X + SpriteData::RICK_SPRITE_WIDTH, Y + 8, IsLookingLeft);
					BulletCount--;
					break;
				}
		}
		// check if we finished the ping pong loop
		else if (CurrentAnimFrame < SpriteData::RickAnimFrameId::FIRE_START)
		{
			// go back to idle
			InitIdle();
		}
	}
	else if (State == AnimState::CROUCH_DOWN)
	{
		// check if the player wants to place a dynamite
		if (!ShouldWePlaceADynamite)
			ShouldWePlaceADynamite = IsDynamitePlacementRequested();
		
		// change the anim frame id if it is the time to
		if (arduboy.everyXFrames(CROUCH_STAND_ANIM_SPEED))
			CurrentAnimFrame += CurrentAnimDirection;
		
		// check if we reach the end of the animation
		if (CurrentAnimFrame > SpriteData::RickAnimFrameId::CROUCH_END)
		{
			// now we can place the dynamite, because we reach the end of the animation
			if (ShouldWePlaceADynamite)
				PlaceDynamite();

			// check if the down button is still pressed or not
			if (Input::IsDown(DOWN_BUTTON))
			{
				InitCrawl();
			}
			else
			{
				// the player release the down button, so we need to stand up
				// reset the anim frame to a correct value and reverse the anim direction
				InitStandUp();
			}
		}
	}
	else if (State == AnimState::STAND_UP)
	{
		// change the anim frame id if it is the time to
		if (arduboy.everyXFrames(CROUCH_STAND_ANIM_SPEED))
			CurrentAnimFrame += CurrentAnimDirection;

		// check if we finished the ping pon+g loop
		if (CurrentAnimFrame < SpriteData::RickAnimFrameId::STAND_UP_END)
		{
			// go back to idle
			InitIdle();
		}
	}
	else if (State == AnimState::CRAWL)
	{
		// light up the dynamite if the playe press A
		if (IsDynamitePlacementRequested())
			PlaceDynamite();
		
		// if player release the down button and there's no ceiling above, then the main character goes up
		if (!Input::IsDown(DOWN_BUTTON) && !IsThereAnyCeilingAboveHead)
		{
			InitStandUp();
			return;
		}
		
		// handle the crawling on left and right
		if (Input::IsDown(LEFT_BUTTON))
		{
			IsLookingLeft = true;
			// check if we should move to the next frame
			if (arduboy.everyXFrames(CRAWL_ANIM_SPEED))
			{
				X--;
				SetNextAnimFrame(SpriteData::RickAnimFrameId::CRAWL_START, SpriteData::RickAnimFrameId::CRAWL_END, true);
			}
		}
		else if (Input::IsDown(RIGHT_BUTTON))
		{
			IsLookingLeft = false;
			// check if we should move to the next frame
			if (arduboy.everyXFrames(CRAWL_ANIM_SPEED))
			{
				X++;
				SetNextAnimFrame(SpriteData::RickAnimFrameId::CRAWL_START, SpriteData::RickAnimFrameId::CRAWL_END, true);
			}
		}
	}
	else if (State == AnimState::CLIMB_LADDER)
	{
		if (arduboy.everyXFrames(CLIMB_LADDER_ANIM_SPEED))
		{
			bool isMoving = false;
			if (Input::IsDown(UP_BUTTON))
			{
				isMoving = true;
				Y--;
			}
			else if (Input::IsDown(DOWN_BUTTON))
			{
				isMoving = true;
				Y++;
			}
			else if (Input::IsDown(LEFT_BUTTON))
			{
				isMoving = true;
				X--;
			}
			else if (Input::IsDown(RIGHT_BUTTON))
			{
				isMoving = true;
				X++;
			}
		
			// update the animation if moving
			if (isMoving)
				SetNextAnimFrame(SpriteData::RickAnimFrameId::CLIMB_START, SpriteData::RickAnimFrameId::CLIMB_END, false);
		}
	}
	else if (State == AnimState::DEATH)
	{
		if (arduboy.everyXFrames(DEATH_ANIM_SPEED))
		{
			// reverse direction if we reach the end of the loop
			if ((CurrentAnimFrame == SpriteData::RickAnimFrameId::DEATH_START) ||
				(CurrentAnimFrame == SpriteData::RickAnimFrameId::DEATH_END))
				CurrentAnimDirection = -CurrentAnimDirection;
			// increase the anim frame
			CurrentAnimFrame += CurrentAnimDirection;
		}
		
		// increase the death timer
		StateFrameCounter++;
		
		// compute the horizontal velocity
		char velocity_X = IsLookingLeft ? DEATH_VELOCITY_X : -DEATH_VELOCITY_X;
		
		// move the main character according to a projectile trajectory
		X = DeathStartX + (velocity_X * StateFrameCounter) / DEATH_MOVING_SPEED;
		Y = DeathStartY + ((DEATH_VELOCITY_Y * StateFrameCounter) + (HALF_GRAVITY * StateFrameCounter * StateFrameCounter)) / DEATH_MOVING_SPEED;
		
		// check if the X and Y are outside of the screen
		if (!IsOnScreen())
			Respawn();
	}
	else
	{
		// check if we start a the jump
		if (Input::IsJustPressed(B_BUTTON))
		{
			State = AnimState::JUMP;
			CurrentAnimFrame = SpriteData::RickAnimFrameId::JUMP;
			StateFrameCounter = 0;
			JumpAndFallAnimSpeedIndex = 0;
			AirControlFrameCount = 0;
		}
		else if (Input::IsDown(DOWN_BUTTON))
		{
			if ((IsInFrontOfLadder || IsAboveLadder) && Input::IsJustPressed(DOWN_BUTTON))
				InitClimbLadder();
			else
				InitCrouch();
		}
		else if (Input::IsDown(UP_BUTTON) && IsInFrontOfLadder)
		{
			InitClimbLadder();
		}
		else if (Input::IsDown(LEFT_BUTTON))
		{
			IsLookingLeft = true;
			AirControlAnimSpeed = MIN_AIR_CONTROL_ANIM_SPEED;

			// reset anim frame to the first frame of the walk, and set the state
			if (Input::IsJustPressed(LEFT_BUTTON))
			{
				CurrentAnimFrame = SpriteData::RickAnimFrameId::WALK_START;
				State = AnimState::WALK;
			}
			
			if (arduboy.everyXFrames(WALK_ANIM_SPEED))
			{
				X--;
				SetNextAnimFrame(SpriteData::RickAnimFrameId::WALK_START, SpriteData::RickAnimFrameId::WALK_END, true);
			}
		}
		else if (Input::IsDown(RIGHT_BUTTON))
		{
			IsLookingLeft = false;
			AirControlAnimSpeed = MIN_AIR_CONTROL_ANIM_SPEED;
			
			// reset anim frame to the first frame of the walk, and set the state
			if (Input::IsJustPressed(RIGHT_BUTTON))
			{
				CurrentAnimFrame = SpriteData::RickAnimFrameId::WALK_START;
				State = AnimState::WALK;
			}
			if (arduboy.everyXFrames(WALK_ANIM_SPEED))
			{
				X++;
				SetNextAnimFrame(SpriteData::RickAnimFrameId::WALK_START, SpriteData::RickAnimFrameId::WALK_END, true);
			}
		}
		else
		{
			// reset the state to idle by default
			InitIdle();
		}
		
		// fire when pressing the correct button
		if ((Input::IsJustPressed(A_BUTTON)) && (BulletCount > 0))
		{
			for (int i = BulletCount-1; i >= 0; --i)
				if (!AllBullets[i].IsPropertySet(Item::PropertyFlags::ALIVE))
				{
					CurrentAnimFrame = SpriteData::RickAnimFrameId::FIRE_START;
					CurrentAnimDirection = 1;
					State = AnimState::FIRE;
					break;
				}
		}
	}
}

void Rick::SetNextAnimFrame(unsigned char startFrameId, unsigned char endFrameId, bool isLooping)
{
	// increase the current frame to the next one
	CurrentAnimFrame += CurrentAnimDirection;
	// check if we need to loop the animation
	if (CurrentAnimFrame > endFrameId)
	{
		if (isLooping)
			CurrentAnimFrame = startFrameId;
		else
		{
			CurrentAnimFrame = endFrameId -1;
			CurrentAnimDirection = -1;
		}
	}
	else if (CurrentAnimFrame < startFrameId)
	{
		CurrentAnimFrame = startFrameId + 1;
		CurrentAnimDirection = 1;
	}
}

void Rick::UpdateAirControl(bool towardLeftDirection)
{
	// first check if we jump without any horizontal movement (just vertically)
	if (AirControlAnimSpeed == NO_HORIZONTAL_MOVE_AIR_CONTROL_ANIM_SPEED)
	{
		// the horizontal speed was null, so set the looking orientation and set the anim speed to max
		IsLookingLeft = towardLeftDirection;
		AirControlAnimSpeed = MAX_AIR_CONTROL_ANIM_SPEED;
	}
	else if (IsLookingLeft == towardLeftDirection)
	{
		if (AirControlAnimSpeed > MIN_AIR_CONTROL_ANIM_SPEED)
			AirControlAnimSpeed--;
	}
	else
	{
		if (AirControlAnimSpeed < MAX_AIR_CONTROL_ANIM_SPEED)
			AirControlAnimSpeed++;
		if (AirControlAnimSpeed == MAX_AIR_CONTROL_ANIM_SPEED)
			IsLookingLeft = towardLeftDirection;
	}
}

/**
 * Tell if there is any horizontal collision (i.e. ground or ceiling) at the specified world vertical coordinate.
 * This function will test two pixels on the left and the right of the current sprite position, a little inside the sprite.
 * If the specified y coordinate is outside the screen, then this function will ask the MapManager to check if there is
 * a sprite at that place in the level, to still have accurate collision event if the ground or ceiling is outside the
 * the screen.
 */
bool Rick::IsThereAnyGroundOrCeilingCollisionAt(int yWorld)
{
	// compute the world coord that we will check for left and right sensor
	int leftWorld = X + LEFT_X_SHIFT_FOR_COLLISION_UNDER_FEET;
	int rightWorld;
	if (State == AnimState::CRAWL)
		rightWorld = X + RIGHT_X_SHIFT_FOR_COLLISION_UNDER_FEET_CRAWL;
	else
		rightWorld = X + RIGHT_X_SHIFT_FOR_COLLISION_UNDER_FEET_STAND;
	// ask the MapManager to check for the collisions
	return MapManager::IsThereAnyHorizontalCollisionAt(leftWorld, rightWorld, yWorld);
}

bool Rick::IsThereAnyCeilingAboveCrawl()
{
	int xOnScreen = MapManager::GetXOnScreen(X);
	if (!IsLookingLeft)
		xOnScreen += WIDTH_DIFF_BETWEEN_CRAWL_AND_STAND;
	int yOnScreen = MapManager::GetYOnScreen(Y);
	if ((xOnScreen < 0) || (xOnScreen >= WIDTH) || (yOnScreen < 0) || (yOnScreen >= HEIGHT))
		return false;
	return arduboy.CheckWhitePixelsInRow(xOnScreen, yOnScreen >> 3, SpriteData::RICK_SPRITE_WIDTH) != 0;
}

bool Rick::IsOnScreen()
{
	char spriteWidth = SpriteData::RICK_SPRITE_WIDTH;
	char spriteHeight = SpriteData::RICK_SPRITE_HEIGHT;
	if (State == AnimState::CRAWL)
	{
		spriteWidth = SpriteData::RICK_CRAWL_SPRITE_WIDTH;
		spriteHeight = SpriteData::RICK_CRAWL_SPRITE_HEIGHT;
	}
	// translate global coord to coord local to the screen
	int xOnScreen = MapManager::GetXOnScreen(X);
	int yOnScreen = MapManager::GetYOnScreen(Y);
	// check that the part of the main character (including the sprite width and height) is inside the screen dimension
	return (xOnScreen + spriteWidth >= 0) && (xOnScreen < WIDTH) && (yOnScreen + spriteHeight >= 0) && (yOnScreen < HEIGHT);
}

/**
 * Check if Rick is colliding with a static wall, floor, and ceiling and prevent him to move.
 */
void Rick::CheckStaticCollision()
{
	// early exit when the main character is dead, we don't need to check the static collision
	if (State == AnimState::DEATH)
		return;
	
	// if we jump, check the ceiling, otherwise, check the floor
	if (State == AnimState::JUMP)
	{
		int yAboveHead = Y - 1;
		if (IsThereAnyGroundOrCeilingCollisionAt(yAboveHead))
		{
			// cancel the jump state and enter directly into the fall state, because Rick as collided with the ceilling
			InitFall();
			
			// move down Rick, until it is outside the collision, this can happen if Rick entered deeply in the collision
			while (IsThereAnyGroundOrCeilingCollisionAt(++yAboveHead))
				Y++;
		}
	}
	else
	{
		// first check the floor collisions
		int yUnderFeet = Y + 13;
		if (IsThereAnyGroundOrCeilingCollisionAt(yUnderFeet))
		{
			// We found a collision under the feet, so if we are falling, stop falling
			if ((State == AnimState::FALL) || 
				((State == AnimState::CLIMB_LADDER) &&
					((!Input::IsDown(DOWN_BUTTON) && !IsInFrontOfLadder) ||
					 (Input::IsDown(DOWN_BUTTON) && !IsAboveLadder))))
				InitIdle();
			
			// move up if Rick entered deeply in the ground (this can happen if Rick moves more than 1 pixel per frame)
			while (IsThereAnyGroundOrCeilingCollisionAt(--yUnderFeet))
				Y--;
		}
		else if ((State != AnimState::FALL) && !IsInFrontOfLadder) // There's no collision under the feet, and not jumping, then we fall
		{
			InitFall();
		}
	}
	
	// draw rick sprite to check the wall collisions
	unsigned int wallCollision = Draw(TRANSPARENT);
	if (wallCollision)
	{
		// cancel any speed in the air if colliding with a wall
		AirControlAnimSpeed = NO_HORIZONTAL_MOVE_AIR_CONTROL_ANIM_SPEED;
		// declare a variable to know in which direction we should push the main character to exit the collision
		bool pushToRight = IsLookingLeft;
		// if this is the left part of the sprite that has collision then we should push in the same direction as his look
		if ((wallCollision & 0x07) != 0)
			pushToRight = !IsLookingLeft;
		// push rick in the right direction
		if (pushToRight)
			X++;
		else
			X--;
	}
	
	// check above the head in craw state
	if (State == AnimState::CRAWL)
		IsThereAnyCeilingAboveHead = IsThereAnyCeilingAboveCrawl();
	
	// Now check the collision with the ladder (only use the map level for that, because we don't need a pixel precision)
	// get the x coord on scren of the middle of the character
	int middleWorldX = X + 4;
	// check if we are in front of a ladder
	IsInFrontOfLadder = MapManager::IsThereLadderAt(middleWorldX, Y + 5) ||
						MapManager::IsThereLadderAt(middleWorldX, Y + 12);
	// check if there's a ladder under the platform
	IsAboveLadder = MapManager::IsThereLadderAt(middleWorldX, Y + 13);
}

/**
 * Chekc if Rick collides with any pixel that will kill him.
 */
void Rick::CheckLethalCollision()
{
	if ((State != AnimState::DEATH) && Draw(BLACK))
		InitDeath();
}

unsigned int Rick::Draw()
{
	// for the death animation, draw the main character in invert color
	return Draw((State == AnimState::DEATH) ? INVERT : WHITE);
}

unsigned int Rick::Draw(unsigned char color)
{
	int xOnScreen = MapManager::GetXOnScreen(X);
	int yOnScreen = MapManager::GetYOnScreen(Y);
	if (State == AnimState::CRAWL)
		return arduboy.drawBitmapExtended(xOnScreen, yOnScreen + VISUAL_HEIGHT_DIFF_BETWEEN_STAND_AND_CRAWL, SpriteData::RickCrawl[CurrentAnimFrame], SpriteData::RICK_CRAWL_SPRITE_WIDTH, SpriteData::RICK_CRAWL_SPRITE_HEIGHT, color, IsLookingLeft);
	else
		return arduboy.drawBitmapExtended(xOnScreen, yOnScreen, SpriteData::Rick[CurrentAnimFrame], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, color, IsLookingLeft);
}
