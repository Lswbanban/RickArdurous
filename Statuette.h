#ifndef _STATUETTE_H_
#define _STATUETTE_H_

#include "Item.h"

class Statuette : public Item
{
public:
	Statuette(int startX, int startY);
	virtual void Update();

private:
	const int ANIM_SPEED = 3;
	const int PAUSE_TIME = 60;
	char AnimFrameId = -1;
	char AnimDirection = 1;
	// the position shift for the shine star, relative to the statuette
	char ShineStarShiftX = 0;
	char ShineStarShiftY = 0;
};

#endif