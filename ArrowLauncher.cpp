/*
 * This class will launch arrows when the player move in front of it
 */

#include "RickArdurous.h"
#include "ArrowLauncher.h"
#include "Rick.h"
#include "SpriteData.h"
#include "MapManager.h"

ArrowLauncher::ArrowLauncher(unsigned char detectionWidth, unsigned char flags) : Item(flags)
{
	DetectionWidth = detectionWidth;
	// instantiate my arrow
	Arrow = new ArrowBullet(true);
}

bool ArrowLauncher::Update(UpdateStep step)
{
	if (step == UpdateStep::DRAW_LETHAL)
	{
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
			Arrow->Fire(X, Y, isShootingTowardLeft);
			LastLaunchTime = 0;
		}
	}
}