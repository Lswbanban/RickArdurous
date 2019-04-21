#ifndef _MUMMY_H_
#define _MUMMY_H_

#include "Item.h"

class Mummy : public Item
{
public:
	Mummy(int startX, int startY);
	virtual bool Update(UpdateStep step);
	
private:
	const int WALL_COLLISION_DETECTION_DISTANCE = 2;
	const int HALF_TURN_ANIM_SPEED = 10;
	
	enum State
	{
		WALK = 0,
		HALF_TURN,
		FALL,
		DIE,
	};
	
	unsigned char AnimFrameId : 4;
	unsigned char AnimFrameCount : 4;
	unsigned char AnimState = 0;
	
	void InitWalk();
	void UpdateWalk();
	void UpdateHalfTurn();
	void UpdateFall();
	int Draw(unsigned char color);
};

#endif