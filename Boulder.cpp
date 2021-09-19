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
	switch (step)
	{
		case UpdateStep::RESPAWN:
			PhysicsFallId = Physics::INVALID_PARABOLIC_ID;
			break;

		case UpdateStep::DRAW_LETHAL:
		{
			// move the boulder
			char movingDirection = IsPropertySet(MIRROR_X) ? -1 : 1;
			bool isFalling = (PhysicsFallId != Physics::INVALID_PARABOLIC_ID);
			if (arduboy.everyXFrames(ANIM_SPEED))
			{
				// check if we need to start or stop to fall
				char hasCollisionUnder = MapManager::IsThereStaticCollisionAt(X+4, Y+12);
				if (!hasCollisionUnder)
				{
					if (!isFalling)
						PhysicsFallId = Physics::StartParabolicTrajectory(X, Y, FALL_INITIAL_VELOCITY_X);
				}
				else if (isFalling)
				{
					Physics::StopParabolicTrajectory(PhysicsFallId);
					PhysicsFallId = Physics::INVALID_PARABOLIC_ID;
				}
				// move if we are not falling
				if (!isFalling)
					X += movingDirection;
			}
			// move the boulder if it is falling
			if (isFalling)
				Physics::UpdateParabolicTrajectory(PhysicsFallId, X, Y, 0);
			// get the coordinate on screen of the boulder
			int xOnScreen = MapManager::GetXOnScreen(X);
			int yOnScreen = MapManager::GetYOnScreen(Y);
			// draw the two halves of it
			arduboy.drawBitmapExtended(xOnScreen, yOnScreen, SpriteData::Boulder, SpriteData::BOULDER_SPRITE_WIDTH, SpriteData::BOULDER_SPRITE_HEIGHT, WHITE, false);
			arduboy.drawBitmapExtended(xOnScreen + SpriteData::BOULDER_SPRITE_WIDTH, yOnScreen, SpriteData::Boulder, SpriteData::BOULDER_SPRITE_WIDTH, SpriteData::BOULDER_SPRITE_HEIGHT, WHITE, true);
			
			// compute the correct animation id
			if (arduboy.everyXFrames(ANIM_ROTATION_SPEED))
				AnimFrameId = (AnimFrameId + 1) % BOULDER_ROLLING_FRAME_COUNT;
			char localAnimFrameId = (movingDirection > 0) ? AnimFrameId : (BOULDER_ROLLING_FRAME_COUNT - AnimFrameId) % BOULDER_ROLLING_FRAME_COUNT;
			// draw the rotating shadow
			char isShadowRight = (localAnimFrameId == 0) || (localAnimFrameId == 3) ? 0 : 1;
			char shadowX = xOnScreen + (2 * !isShadowRight) + (SpriteData::BOULDER_SPRITE_WIDTH * isShadowRight);
			arduboy.drawBitmapExtended(shadowX, yOnScreen + 2, SpriteData::BoulderShadow[localAnimFrameId >> 1], SpriteData::BOULDER_SHADOW_SPRITE_WIDTH, SpriteData::BOULDER_SHADOW_SPRITE_HEIGHT, BLACK, isShadowRight);
			break;
		}
	}
	return false;
}
