/*
 * Implement the logic and drawing of the Enemies
*/

#include "RickArdurous.h"
#include "Enemy.h"
#include "SpriteData.h"
#include "Rick.h"
#include "MapManager.h"

const char WALK_AND_WAIT_ANIM_SPEED[] = { 8, 13, 6, 8 };

Enemy::Enemy(int startX, int startY, unsigned char flag) : Item(startX, startY, flag | Item::PropertyFlags::ENEMIES | Item::PropertyFlags::STATIC_COLLISION_NEEDED)
{
	InitWalk();
};

bool Enemy::Update(UpdateStep step)
{
	switch (step)
	{
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
			
			// draw the statuette and check the collision with eventual lethal stuff
			int collision = Draw();
			
			// if we have a collision, that means we hit a lethal pixel
			if (collision != 0)
			{
				ClearProperty(Item::PropertyFlags::ALIVE);
				MapManager::RemoveItem(this);
				return true;
			}
			break;
		}
		case Item::UpdateStep::CHECK_STATIC_COLLISION:
		{
			// check the ground collision
			int yUnderFeet = Y + 14;
			unsigned char width = IsPropertySet(PropertyFlags::SPECIAL) ? SpriteData::SKELETON_SPRITE_WIDTH : SpriteData::MUMMY_SPRITE_WIDTH;
			if (!MapManager::IsThereAnyHorizontalCollisionAt(X+1, X+width-2, yUnderFeet))
			{
				AnimState = State::FALL;
			}
			else
			{
				// there is ground, check if I was falling
				if (AnimState == State::FALL)
				{
					InitWalk();
				}
				else
				{
					// compute the world coordinate of the map level block to test
					int wallX = IsPropertySet(PropertyFlags::MIRROR_X) ? X - WALL_COLLISION_DETECTION_DISTANCE : X + width + WALL_COLLISION_DETECTION_DISTANCE;
					if (MapManager::IsThereStaticCollisionAt(wallX, Y) || 
						MapManager::IsThereStaticCollisionAt(wallX, Y + SpriteData::LEVEL_SPRITE_HEIGHT) ||
						!MapManager::IsThereStaticCollisionAt(wallX, Y + (SpriteData::LEVEL_SPRITE_HEIGHT << 1)))
					{
						// reverse the walking direction imediately for the next frame to test the collision at the right place
						InverseProperty(PropertyFlags::MIRROR_X);
						// init the half turn state
						AnimState = State::HALF_TURN;
						AnimFrameId = SpriteData::EnemyAnimFrameId::ENEMY_HALF_TURN;
						AnimFrameCount = 0;
					}
				}
			}
			break;
		}
	}
	return false;
}

void Enemy::InitWalk()
{
	AnimState = State::WALK;
	AnimFrameId = SpriteData::EnemyAnimFrameId::ENEMY_WALK_START;
	AnimFrameCount = 0;
}

void Enemy::UpdateWalk()
{
	// get the anim speed
	unsigned char walkAnimSpeed = IsPropertySet(PropertyFlags::SPECIAL) ? SKELETON_WALK_ANIM_SPEED : WALK_AND_WAIT_ANIM_SPEED[AnimFrameId];
	// check if it is the time to change the anim frame
	if (AnimFrameCount == walkAnimSpeed)
	{
		// move the X depending on the direction
		if (IsPropertySet(PropertyFlags::MIRROR_X))
			X--;
		else
			X++;
		// reset the frame counter
		AnimFrameCount = 0;
		// go to the next frame id
		if (AnimFrameId == SpriteData::EnemyAnimFrameId::ENEMY_WALK_END)
			AnimFrameId = SpriteData::EnemyAnimFrameId::ENEMY_WALK_START;
		else
			AnimFrameId++;
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
	}
}

void Enemy::UpdateFall()
{
	Y++;
}

int Enemy::Draw()
{
	int xOnScreen = MapManager::GetXOnScreen(X);
	int yOnScreen = MapManager::GetYOnScreen(Y);
	bool isMirror = IsPropertySet(PropertyFlags::MIRROR_X);
	if (IsPropertySet(PropertyFlags::SPECIAL))
		return arduboy.drawBitmapExtended(xOnScreen, yOnScreen,
									SpriteData::Skeleton[AnimFrameId],
									SpriteData::SKELETON_SPRITE_WIDTH, SpriteData::SKELETON_SPRITE_HEIGHT,
									WHITE, isMirror);
	else
		return arduboy.drawBitmapExtended(xOnScreen, yOnScreen,
									SpriteData::Mummy[AnimFrameId],
									SpriteData::MUMMY_SPRITE_WIDTH, SpriteData::MUMMY_SPRITE_HEIGHT,
									WHITE, isMirror);
}