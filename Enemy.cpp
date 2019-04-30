/*
 * Implement the logic and drawing of the Enemies
*/

#include "RickArdurous.h"
#include "Enemy.h"
#include "SpriteData.h"
#include "Rick.h"
#include "MapManager.h"
#include "Physics.h"

const char WALK_AND_WAIT_ANIM_SPEED[] = { 8, 13, 6, 8 };

Enemy::Enemy(int startX, int startY, unsigned char flag, bool isSkeleton) : Item(startX, startY, flag | Item::PropertyFlags::ENEMIES | Item::PropertyFlags::STATIC_COLLISION_NEEDED)
{
	IsSkeleton = isSkeleton;
	InitWalk();
};

bool Enemy::Update(UpdateStep step)
{
	switch (step)
	{
		case Item::UpdateStep::CHECK_LETHAL:
		{
			// first update the logic of the AI to determine its state and animation,
			// so that we draw the same frame in black and white
			// update the frame counter (need to be done in any state)
			AnimFrameCount++;
			// then call the corect update according to the current state
			switch (AnimState)
			{
				case State::WALK:
					UpdateWalk();
					break;
				case State::HALF_TURN:
					UpdateHalfTurn();
					break;
				case State::WAIT:
				case State::WAIT_AGAIN:
					UpdateWait();
					break;
				case State::FALL:
					UpdateFall();
					break;
			}
			
			// if we have a collision, that means we hit a lethal pixel
			// Draw in black to delete the bullet in case we are hit by a bullet
			int collision = Draw(BLACK);
			if (collision != 0)
			{
				// compute the horizontal velocity for the death trajectory
				bool isCollisionOnLeftHalfOfSprite = collision < (1 << (GetWidth() >> 1));
				char velocityX = (IsPropertySet(PropertyFlags::MIRROR_X) != isCollisionOnLeftHalfOfSprite) ? DEATH_VELOCITY_X : -DEATH_VELOCITY_X;
				FallAnimSpeedIndex = Physics::StartParabolicTrajectory(X, Y, velocityX);
				AnimState = State::DEATH;
				ClearProperty(Item::PropertyFlags::STATIC_COLLISION_NEEDED | Item::PropertyFlags::ENEMIES);
				SetProperty(Item::PropertyFlags::IGNORED_BY_ENEMIES);
			}
			break;
		}
		
		case Item::UpdateStep::DRAW_ENEMIES:
		{
			// draw the enemy in white
			Draw(WHITE);
			break;
		}
		
		case Item::UpdateStep::DRAW_IGNORED_BY_ENEMIES:
		{
			// special case, the Enemy is in that update step only when he is dead
			Draw(INVERT);
			return UpdateDeath();
		}
		
		case Item::UpdateStep::CHECK_STATIC_COLLISION:
		{
			// check the ground collision
			int yUnderFeet = GetYUnderFeet();
			if (!IsThereAnyGroundCollisionAt(yUnderFeet))
			{
				// check if we are already falling or not
				if (AnimState == State::FALL)
				{
					// If we are falling, check the ground several pixel below, depending on my current
					// fall speed, to see if I will touch the ground during next frame.
					// If yes, reduce my falling speed to avoid penetrating in the ground during next frame
					for (int i = Physics::JUMP_AND_FALL_VERTICAL_MOVE[FallAnimSpeedIndex]; i > 1; i--)
						if (IsThereAnyGroundCollisionAt(yUnderFeet + i))
							while (Physics::JUMP_AND_FALL_VERTICAL_MOVE[FallAnimSpeedIndex] > 
									Physics::JUMP_AND_FALL_VERTICAL_MOVE[FallAnimSpeedIndex + 1] )
								FallAnimSpeedIndex++;
				}
				else
				{
					// if we are not falling init the fall
					InitFall();
				}
			}
			else
			{
				// there is ground, check if I was falling
				if (AnimState == State::FALL)
					InitWalk();
			}
			break;
		}
		case Item::UpdateStep::RESPAWN:
		{
			SetProperty(Item::PropertyFlags::STATIC_COLLISION_NEEDED | Item::PropertyFlags::ENEMIES);
			ClearProperty(Item::PropertyFlags::IGNORED_BY_ENEMIES);
			InitWalk();
			break;
		}
	}
	return false;
}

int Enemy::GetYUnderFeet()
{
	return IsScorpion() ? Y + 6 : Y + 14;
}

unsigned char Enemy::GetWidth()
{
	return IsSkeleton ? SpriteData::SKELETON_SPRITE_WIDTH : 
			(IsScorpion() ? SpriteData::SCORPION_SPRITE_WIDTH : SpriteData::MUMMY_SPRITE_WIDTH);
}

unsigned char Enemy::GetHeight()
{
	return IsScorpion() ? 6 : 12;
}

void Enemy::MoveAccordingToOrientation()
{
	// move the X depending on the direction
	if (IsPropertySet(PropertyFlags::MIRROR_X))
		X--;
	else
		X++;
}

bool Enemy::IsThereWallCollisionOrGap(bool shouldCheckGap)
{
	int wallX = IsPropertySet(PropertyFlags::MIRROR_X) ? X - WALL_COLLISION_DETECTION_DISTANCE : X + GetWidth() + WALL_COLLISION_DETECTION_DISTANCE;
	unsigned char gapHeightShift = IsScorpion() ? 0 : 1;
	return (MapManager::IsThereStaticCollisionAt(wallX, Y) || 
		(!IsScorpion() && MapManager::IsThereStaticCollisionAt(wallX, Y + SpriteData::LEVEL_SPRITE_HEIGHT)) ||
		(shouldCheckGap && !MapManager::IsThereStaticCollisionAt(wallX, Y + (SpriteData::LEVEL_SPRITE_HEIGHT << gapHeightShift))));
}

bool Enemy::IsThereAnyGroundCollisionAt(int yWorld)
{
	// compute the world coord that we will check for left and right sensor
	int leftWorldX = X + 1;
	int rightWorldX = X + GetWidth() - 2;
	// ask the MapManager to check for the collisions
	return MapManager::IsThereAnyHorizontalCollisionAt(leftWorldX, rightWorldX, yWorld);
}

void Enemy::UpdateSkeletonBehavior()
{
	int rickX = Rick::GetCenterX();
	int myCenterX = X + (SpriteData::SKELETON_SPRITE_WIDTH >> 1);
	bool isRickOnMyLeft = rickX < (myCenterX - SKELETON_SENSOR);
	bool isRickOnMyRight = rickX > (myCenterX + SKELETON_SENSOR);
	bool amILookingLeft = IsPropertySet(MIRROR_X);
	if ((isRickOnMyRight && amILookingLeft) || (isRickOnMyLeft && !amILookingLeft))
	{
		InitHalfTurn();
	}
	else 
	{
		// check if rick is aligned with me, or if I'm blocked by collision
		if ((!isRickOnMyLeft && !isRickOnMyRight) || IsThereWallCollisionOrGap(false))
		{
			if (AnimState != State::WAIT)
				InitWait();
		}
		else
		{
			if (AnimState != State::WALK)
				InitWalk();
		}
	}
}

void Enemy::InitFall()
{
	AnimState = State::FALL;
	FallAnimSpeedIndex = Physics::JUMP_AND_FALL_VERTICAL_ANIM_SPEED_COUNT - 1;
	AnimFrameCount = 0;
	if (IsSkeleton)
		AnimFrameId = SpriteData::EnemyAnimFrameId::ENEMY_FALL;
}

void Enemy::InitWait()
{
	AnimState = WAIT;
	AnimFrameId = SpriteData::EnemyAnimFrameId::ENEMY_WAIT_START;
	AnimFrameCount = 0;
}

void Enemy::InitWalk()
{
	AnimState = State::WALK;
	AnimFrameId = SpriteData::EnemyAnimFrameId::ENEMY_WALK_START;
	AnimFrameCount = 0;
}

void Enemy::InitHalfTurn()
{
	// reverse the walking direction imediately for the next frame to test the collision at the right place
	InverseProperty(PropertyFlags::MIRROR_X);
	// init the half turn state
	AnimState = State::HALF_TURN;
	AnimFrameId = SpriteData::EnemyAnimFrameId::ENEMY_HALF_TURN;
	AnimFrameCount = 0;
}

void Enemy::UpdateWalk()
{
	// get the anim speed
	unsigned char walkAnimSpeed = IsSkeleton ? SKELETON_WALK_ANIM_SPEED : 
				(IsScorpion() ? SCORPION_WALK_ANIM_SPEED : WALK_AND_WAIT_ANIM_SPEED[AnimFrameId]);
	// check if it is the time to change the anim frame
	if (AnimFrameCount == walkAnimSpeed)
	{
		// reset the frame counter
		AnimFrameCount = 0;
		// go to the next frame id
		if (AnimFrameId == SpriteData::EnemyAnimFrameId::ENEMY_WALK_END)
			AnimFrameId = SpriteData::EnemyAnimFrameId::ENEMY_WALK_START;
		else
			AnimFrameId++;

		// move the X according to the orientation for a ping pong trajectory
		MoveAccordingToOrientation();
	
		// Update the special behavior of the skeleton or by default make half turn
		if (IsSkeleton)
		{
			UpdateSkeletonBehavior();
		}
		else if (IsThereWallCollisionOrGap(true))
		{
			if (IsScorpion())
				InitWait();
			else
				InitHalfTurn();
		}
	}
}

void Enemy::UpdateHalfTurn()
{
	// get the anim speed
	unsigned char halfTurnAnimSpeed = IsSkeleton ? SKELETON_HALF_TURN_ANIM_SPEED : MUMMY_HALF_TURN_ANIM_SPEED;
	if (AnimFrameCount == halfTurnAnimSpeed)
		InitWalk();
}

void Enemy::UpdateWait()
{
	// get the wait anim speed
	unsigned char waitAnimSpeed = IsScorpion() ? SCORPION_WAIT_ANIM_SPEED : WALK_AND_WAIT_ANIM_SPEED[AnimFrameId - SpriteData::EnemyAnimFrameId::ENEMY_WAIT_START];
	// check if we need to change the frame id
	if (AnimFrameCount == waitAnimSpeed)
	{
		// reset the frame counter
		AnimFrameCount = 0;
		// change the anim id (only two ids in wait, but will make 3 frame with the mirror)
		if (AnimFrameId == SpriteData::EnemyAnimFrameId::ENEMY_WAIT_END)
		{
			AnimFrameId = SpriteData::EnemyAnimFrameId::ENEMY_WAIT_START;
			if (IsScorpion())
			{
				if (AnimState == State::WAIT)
					AnimState = State::WAIT_AGAIN;
				else
					InitHalfTurn();
			}
		}
		else
			AnimFrameId++;
		
		// check if we need to stop waiting and go back to walk
		if (IsSkeleton)
			UpdateSkeletonBehavior();
	}
}

void Enemy::UpdateFall()
{
	if (AnimFrameCount >= Physics::JUMP_AND_FALL_VERTICAL_ANIM_SPEED[FallAnimSpeedIndex])
	{
		// reset the frame counter
		AnimFrameCount = 0;
		// in fall state, move down
		Y += Physics::JUMP_AND_FALL_VERTICAL_MOVE[FallAnimSpeedIndex];
		// move a little bit on X during the first frame of the animation
		if (FallAnimSpeedIndex >= Physics::JUMP_AND_FALL_VERTICAL_ANIM_SPEED_COUNT - WALL_COLLISION_DETECTION_DISTANCE - 1)
			MoveAccordingToOrientation();
		// decrease the jump counter
		if (FallAnimSpeedIndex > Physics::FALL_VERTICAL_MIN_INDEX)
			FallAnimSpeedIndex--;
	}
}

bool Enemy::UpdateDeath()
{
	// update the trajectory
	Physics::UpdateParabolicTrajectory(FallAnimSpeedIndex, X, Y);
	
	// check if I'm still on screen
	if (!MapManager::IsOnScreen(X, Y, GetWidth(), GetHeight()))
	{
		// stop the parabolic trajectory
		Physics::StopParabolicTrajectory(FallAnimSpeedIndex);
		// clear alive property
		ClearProperty(Item::PropertyFlags::ALIVE);
		MapManager::RemoveItem(this);
		return true;
	}
	
	return false;
}

int Enemy::Draw(unsigned char color)
{
	int xOnScreen = MapManager::GetXOnScreen(X);
	int yOnScreen = MapManager::GetYOnScreen(Y);
	bool isMirror = IsPropertySet(PropertyFlags::MIRROR_X);
	if (IsSkeleton)
		return arduboy.drawBitmapExtended(xOnScreen, yOnScreen,
									SpriteData::Skeleton[AnimFrameId],
									SpriteData::SKELETON_SPRITE_WIDTH, SpriteData::SKELETON_SPRITE_HEIGHT,
									color, isMirror);
	else if (IsScorpion())
		return arduboy.drawBitmapExtended(xOnScreen, yOnScreen,
									SpriteData::Scorpion[AnimFrameId],
									SpriteData::SCORPION_SPRITE_WIDTH, SpriteData::SCORPION_SPRITE_HEIGHT,
									color, isMirror);
	else
		return arduboy.drawBitmapExtended(xOnScreen, yOnScreen,
									SpriteData::Mummy[AnimFrameId],
									SpriteData::MUMMY_SPRITE_WIDTH, SpriteData::MUMMY_SPRITE_HEIGHT,
									color, isMirror);
}