/*
 * This class will launch arrows when the player move in front of it
 */

#include "RickArdurous.h"
#include "ArrowLauncher.h"
#include "Rick.h"
#include "SpriteData.h"

ArrowLauncher::ArrowLauncher(int startX, int startY, unsigned char detectionWidth, unsigned char flag) : Item(startX, startY, flag | Item::PropertyFlags::LETHAL)
{
	DetectionWidth = detectionWidth;
	// instantiate my arrow
	Arrow = new ArrowBullet(true);
}

bool ArrowLauncher::Update(UpdateStep step)
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
		// get the position of the main character
		int rickX = Rick::GetX();
		int rickY = Rick::GetY();
		// check if the main character is inside the detection range
		if (Rick::IsAlive() && (Y > rickY) && (Y < rickY + 13) && (minX < rickX + SpriteData::RICK_SPRITE_WIDTH) && (maxX > rickX))
		{
			Arrow->Fire(X, Y, isShootingTowardLeft);
			LastLaunchTime = 0;
		}
	}
	else
	{
		LastLaunchTime++;
		if (LastLaunchTime >= LAUNCH_PERIOD)
			LastLaunchTime = CAN_LAUNCH_ARROW;
	}
	
	return false;
}
