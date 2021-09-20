/*
 * Implement the logic and drawing of lethal spikes
*/

#include "RickArdurous.h"
#include "Boulder.h"
#include "SpriteData.h"
#include "MapManager.h"
#include "Physics.h"

bool Boulder::Update(UpdateStep step)
{
	bool isBoulderRolling = !IsPropertySet(SPECIAL);
	
	switch (step)
	{
		case UpdateStep::RESPAWN:
			PhysicsFallId = Physics::INVALID_PARABOLIC_ID;
			ClearProperty(SPECIAL);
			break;

		case UpdateStep::CHECK_STATIC_COLLISION:
		{
			// move the boulder
			char movingDirection = IsPropertySet(MIRROR_X) ? -1 : 1;
			bool isFalling = (PhysicsFallId != Physics::INVALID_PARABOLIC_ID);
			// check if we need to start or stop to fall
			bool hasCollisionUnder = MapManager::IsThereAnyHorizontalCollisionAt(X+4, Y+12, 4);
			if (!hasCollisionUnder)
			{
				if (isFalling)
					Physics::UpdateParabolicTrajectory(PhysicsFallId, X, Y, 0);
				else
					PhysicsFallId = Physics::StartParabolicTrajectory(X, Y, movingDirection * FALL_INITIAL_VELOCITY_X);
			}
			else if (isFalling)
			{
				Physics::StopParabolicTrajectory(PhysicsFallId);
				PhysicsFallId = Physics::INVALID_PARABOLIC_ID;
				// move the boulder up outside the ground collision
				//while (MapManager::IsThereAnyHorizontalCollisionAt(X+4, Y+11, 4))
				//	Y--;
			}
			else if (arduboy.everyXFrames(ANIM_SPEED) && isBoulderRolling)
			{
				// move if we are not falling
				X += movingDirection;
				// check if I bump in a wall
				char wallCheckX = (movingDirection > 0) ? X + SpriteData::BOULDER_SPRITE_WIDTH * 2 : X;
				if (MapManager::IsThereStaticCollisionAt(wallCheckX, Y) ||
					MapManager::IsThereStaticCollisionAt(wallCheckX, Y+8))
					{
						SetProperty(SPECIAL);
						X -= movingDirection;
					}
			}
			break;
		}
		case UpdateStep::DRAW_LETHAL_BESIDE:
		{
			if (isBoulderRolling)
				Draw();
			break;
		}

		case UpdateStep::DRAW_STATIC_COLLISION:
		{
			if (!isBoulderRolling)
				Draw();
			break;
		}
	}
	return false;
}

void Boulder::Draw()
{
	// get the coordinate on screen of the boulder
	int xOnScreen = MapManager::GetXOnScreen(X);
	int yOnScreen = MapManager::GetYOnScreen(Y);
	// draw the two halves of it
	arduboy.drawBitmapExtended(xOnScreen, yOnScreen, SpriteData::Boulder, SpriteData::BOULDER_SPRITE_WIDTH, SpriteData::BOULDER_SPRITE_HEIGHT, WHITE, false);
	arduboy.drawBitmapExtended(xOnScreen + SpriteData::BOULDER_SPRITE_WIDTH, yOnScreen, SpriteData::Boulder, SpriteData::BOULDER_SPRITE_WIDTH, SpriteData::BOULDER_SPRITE_HEIGHT, WHITE, true);
	
	// get the moving direction
	char movingDirection = IsPropertySet(MIRROR_X) ? -1 : 1;
	bool isBoulderRolling = !IsPropertySet(SPECIAL);
	// compute the correct animation id
	if (arduboy.everyXFrames(ANIM_ROTATION_SPEED) && isBoulderRolling)
		AnimFrameId = (AnimFrameId + 1) % BOULDER_ROLLING_FRAME_COUNT;
	char localAnimFrameId = (movingDirection > 0) ? AnimFrameId : (BOULDER_ROLLING_FRAME_COUNT - AnimFrameId) % BOULDER_ROLLING_FRAME_COUNT;
	// draw the rotating shadow
	char isShadowRight = (localAnimFrameId == 0) || (localAnimFrameId == 3) ? 0 : 1;
	char shadowX = xOnScreen + (2 * !isShadowRight) + (SpriteData::BOULDER_SPRITE_WIDTH * isShadowRight);
	arduboy.drawBitmapExtended(shadowX, yOnScreen + 2, SpriteData::BoulderShadow[localAnimFrameId >> 1], SpriteData::BOULDER_SHADOW_SPRITE_WIDTH, SpriteData::BOULDER_SHADOW_SPRITE_HEIGHT, BLACK, isShadowRight);
}