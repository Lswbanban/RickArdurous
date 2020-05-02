/*
 * This class will launch arrows when the player move in front of it
 */

#include "RickArdurous.h"
#include "ArrowLauncher.h"
#include "Rick.h"
#include "SpriteData.h"
#include "MapManager.h"
#include "FXManager.h"

ArrowLauncher::ArrowLauncher()
: Arrow(true)
{
}

void ArrowLauncher::Init(int startX, int startY, unsigned char flags, unsigned char detectionWidth)
{
	// set my detection
	DetectionWidth = detectionWidth;
	// and call the item init
	Item::Init(startX, startY, flags);
}

bool ArrowLauncher::Update(UpdateStep step)
{
	switch (step)
	{
		case UpdateStep::DRAW_LETHAL:
			if (LastLaunchTime == CAN_LAUNCH_ARROW)
			{
				// check if the main character is triggering me
				CheckTrigerer(Rick::IsAlive(), Rick::GetX(), Rick::GetY());
				// check if the other trap trigerer is triggering me
				MapManager::CallMeBackForEachTrapTriggerer(this, &CheckTrigererCallback);
			}
			else
			{
				LastLaunchTime++;
				if (LastLaunchTime >= LAUNCH_PERIOD)
					LastLaunchTime = CAN_LAUNCH_ARROW;
			}
			break;
		
		case UpdateStep::DRAW_STATIC_COLLISION:
			{
				bool isShootingTowardLeft = IsPropertySet(Item::PropertyFlags::MIRROR_X);
				int drawX = isShootingTowardLeft ? X - 3: X - 1;
				// draw the statue that launch the arrow
				arduboy.drawBitmapExtended(MapManager::GetXOnScreen(drawX), MapManager::GetYOnScreen(Y - 6), SpriteData::ArrowLauncherFace, SpriteData::ARROW_LAUNCHER_FACE_SPRITE_WIDTH, SpriteData::ARROW_LAUNCHER_FACE_SPRITE_HEIGHT, WHITE, isShootingTowardLeft);
			}
			break;
			
		case UpdateStep::RESPAWN:
			LastLaunchTime = CAN_LAUNCH_ARROW;
			Arrow.KillBulletWithoutSparks();
			break;
	}
	return false;
}

void ArrowLauncher::CheckTrigererCallback(Item * me, Item * trigerer)
{
	((ArrowLauncher *)me)->CheckTrigerer(trigerer->IsPropertySet(Item::PropertyFlags::ALIVE), trigerer->GetX(), trigerer->GetY());
}

void ArrowLauncher::CheckTrigerer(bool isAlive, int trigererX, int trigererY)
{
	if (LastLaunchTime == CAN_LAUNCH_ARROW)
	{
		int minX;
		int maxX;
		bool isShootingTowardLeft = IsPropertySet(Item::PropertyFlags::MIRROR_X);
		if (isShootingTowardLeft)
		{
			minX = X - DetectionWidth;
			maxX = X;
		}
		else
		{
			minX = X;
			maxX = X + DetectionWidth;
		}

		// check if the main character is inside the detection range
		if (isAlive && (Y > trigererY) && (Y < trigererY + 13) && (minX < trigererX + SpriteData::RICK_SPRITE_WIDTH) && (maxX > trigererX))
		{
			Arrow.Fire(X, Y, isShootingTowardLeft);
			FXManager::StartFXCommand(FXManager::BufferId::GAME, {1, 0, 0, 4, 0, 52, 0, 1});
			LastLaunchTime = 0;
		}
	}
}