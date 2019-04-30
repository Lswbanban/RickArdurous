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

Enemy::Enemy(int startX, int startY, unsigned char flag) : Item(startX, startY, flag | Item::PropertyFlags::ENEMIES | Item::PropertyFlags::STATIC_COLLISION_NEEDED)
{
	InitWalk();
};

bool Enemy::Update(UpdateStep step)
{
	switch (step)
	{
		case Item::UpdateStep::CHECK_LETHAL:
		{
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
					UpdateWait();
					break;
				case State::FALL:
					UpdateFall();
					break;
			}
			
			// draw the enemy in white
			Draw(WHITE);
			break;
		}
		
		case Item::UpdateStep::DRAW_IGNORED_BY_ENEMIES:
		{
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
	return Y + 14;
}

unsigned char Enemy::GetWidth()
{
	return IsPropertySet(PropertyFlags::SPECIAL) ? SpriteData::SKELETON_SPRITE_WIDTH : SpriteData::MUMMY_SPRITE_WIDTH;
}

unsigned char Enemy::GetHeight()
{
	return SpriteData::SKELETON_SPRITE_HEIGHT;
}

void Enemy::MoveAccordingToOrientation()
{
	// move the X depending on the direction
	if (IsPropertySet(PropertyFlags::MIRROR_X))
		X--;
	else
		X++;
}

bool Enemy::IsThereWallCollisionOrGap()
{
	bool isSkeleton = IsPropertySet(PropertyFlags::SPECIAL);
	int wallX = IsPropertySet(PropertyFlags::MIRROR_X) ? X - WALL_COLLISION_DETECTION_DISTANCE : X + GetWidth() + WALL_COLLISION_DETECTION_DISTANCE;
	return (MapManager::IsThereStaticCollisionAt(wallX, Y) || 
		MapManager::IsThereStaticCollisionAt(wallX, Y + SpriteData::LEVEL_SPRITE_HEIGHT) ||
		(!isSkeleton && !MapManager::IsThereStaticCollisionAt(wallX, Y + (SpriteData::LEVEL_SPRITE_HEIGHT << 1))));
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
		if ((!isRickOnMyLeft && !isRickOnMyRight) || IsThereWallCollisionOrGap())
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
	if (IsPropertySet(PropertyFlags::SPECIAL))
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
	// the walk will have different logic for Skeleton or other type
	bool isSkeleton = IsPropertySet(PropertyFlags::SPECIAL);
	
	// get the anim speed
	unsigned char walkAnimSpeed = isSkeleton ? SKELETON_WALK_ANIM_SPEED : WALK_AND_WAIT_ANIM_SPEED[AnimFrameId];
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
		if (isSkeleton)
			UpdateSkeletonBehavior();
		else if (IsThereWallCollisionOrGap())
			InitHalfTurn();
	}
}

void Enemy::UpdateHalfTurn()
{
	// get the anim speed
	unsigned char halfTurnAnimSpeed = IsPropertySet(PropertyFlags::SPECIAL) ? SKELETON_HALF_TURN_ANIM_SPEED : MUMMY_HALF_TURN_ANIM_SPEED;
	if (AnimFrameCount == halfTurnAnimSpeed)
		InitWalk();
}

void Enemy::UpdateWait()
{
	// check if we need to change the frame id
	if (AnimFrameCount == WALK_AND_WAIT_ANIM_SPEED[AnimFrameId - SpriteData::EnemyAnimFrameId::ENEMY_WAIT_START])
	{
		// reset the frame counter
		AnimFrameCount = 0;
		// change the anim id (only two ids in wait, but will make 3 frame with the mirror)
		if (AnimFrameId == SpriteData::EnemyAnimFrameId::ENEMY_WAIT_END)
			AnimFrameId = SpriteData::EnemyAnimFrameId::ENEMY_WAIT_START;
		else
			AnimFrameId++;
		
		// check if we need to stop waiting and go back to walk
		if (IsPropertySet(PropertyFlags::SPECIAL))
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
	if (IsPropertySet(PropertyFlags::SPECIAL))
		return arduboy.drawBitmapExtended(xOnScreen, yOnScreen,
									SpriteData::Skeleton[AnimFrameId],
									SpriteData::SKELETON_SPRITE_WIDTH, SpriteData::SKELETON_SPRITE_HEIGHT,
									color, isMirror);
	else
		return arduboy.drawBitmapExtended(xOnScreen, yOnScreen,
									SpriteData::Mummy[AnimFrameId],
									SpriteData::MUMMY_SPRITE_WIDTH, SpriteData::MUMMY_SPRITE_HEIGHT,
									color, isMirror);
}