#ifndef _SPIKE_H_
#define _SPIKE_H_

#include "Item.h"

class Spike : public Item
{
public:
	Spike(int startX, int startY, unsigned char flag);
	virtual bool Update(UpdateStep step);

private:
	const int ANIM_SPEED = 4;
	const int PAUSE_TIME = 90;
	unsigned char AnimFrameId = 0;
};

#endif