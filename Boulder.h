#ifndef _BOULDER_H_
#define _BOULDER_H_

#include "Item.h"

class Boulder : public Item
{
public:
	virtual bool Update(UpdateStep step);

private:
	static constexpr int ANIM_SPEED = 3;
	static constexpr int ANIM_ROTATION_SPEED = 8;
	static constexpr int BOULDER_ROLLING_FRAME_COUNT = 4;
	unsigned char AnimFrameId = 0;
	unsigned char PhysicsFallId;
};

#endif