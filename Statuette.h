#ifndef _STATUETTE_H_
#define _STATUETTE_H_

#include "Item.h"

class Statuette : public Item
{
public:
	Statuette(int startX, int startY);
	virtual void Update();

private:
	const int ANIM_SPEED = 2;
	const int MIN_PAUSE_TIMES = 10;
	const int MAX_PAUSE_TIMES = 150;
	
	// the current time to wait before playing the next shining star
	char PauseTime = 0;
	
	// current frame id and direction of the shinning star
	char AnimFrameId = -1;
	char AnimDirection = 1;
	
	// the position shift for the shine star, relative to the statuette
	char ShineStarShiftX = 0;
	char ShineStarShiftY = 0;
};

#endif