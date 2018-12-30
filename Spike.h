#ifndef _SPIKE_H_
#define _SPIKE_H_

#include "Item.h"

class Spike : public Item
{
public:
	enum VisualType
	{
		HORIZONTAL = 0,
		VERTICAL_LEFT,
		VERTICAL_RIGHT,
	};
	
	Spike(int startX, int startY, VisualType type);
	virtual void Update();

private:
	const int ANIM_SPEED = 4;
	const int PAUSE_TIME = 90;
	unsigned char AnimFrameId = 0;
	VisualType Type = HORIZONTAL;
};

#endif