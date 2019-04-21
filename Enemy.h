#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Item.h"

class Enemy : public Item
{
public:
	Enemy(int startX, int startY, unsigned char flag);
	virtual bool Update(UpdateStep step);
	
private:
	const int WALL_COLLISION_DETECTION_DISTANCE = 1;
	const int MUMMY_HALF_TURN_ANIM_SPEED = 10;
	const int SKELETON_HALF_TURN_ANIM_SPEED = 5;
	const int SKELETON_WALK_ANIM_SPEED = 3;

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
	int Draw();
};

#endif