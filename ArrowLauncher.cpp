/*
 * This class will launch arrows when the player move in front of it
 */

#include "RickArdurous.h"
#include "ArrowLauncher.h"
#include "Rick.h"

ArrowLauncher::ArrowLauncher(int startX, int startY, unsigned char flag) : Item(startX, startY, flag | Item::PropertyFlags::LETHAL)
{
	// instantiate my arrow
	Arrow = new ArrowBullet(true);
}

bool ArrowLauncher::Update(UpdateStep step)
{
	if (LastLaunchTime == CAN_LAUNCH_ARROW)
	{
		int rickY = Rick::GetY();
		if ((Y > rickY) && (Y < rickY + 13))
		{
			Arrow->Fire(X, Y, IsPropertySet(Item::PropertyFlags::MIRROR_X));
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
