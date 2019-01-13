#ifndef _ARROW_LAUNCHER_H_
#define _ARROW_LAUNCHER_H_

#include "ArrowBullet.h"

class ArrowLauncher : public Item
{
public:
	ArrowLauncher(int startX, int startY, unsigned char detectionWidth, unsigned char flag);
	virtual bool Update(UpdateStep step);

private:
	const int LAUNCH_PERIOD = 180;
	const int CAN_LAUNCH_ARROW = 255;
	
	ArrowBullet * Arrow;
	unsigned char LastLaunchTime = CAN_LAUNCH_ARROW;
	unsigned char DetectionWidth;
};

#endif