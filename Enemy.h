#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Item.h"

class Enemy : public Item
{
public:
	Enemy(int startX, int startY, unsigned char flag);
	virtual bool Update(UpdateStep step);
	
private:
	static constexpr int WALL_COLLISION_DETECTION_DISTANCE = 1;
	static constexpr int MUMMY_HALF_TURN_ANIM_SPEED = 14;
	static constexpr int SKELETON_HALF_TURN_ANIM_SPEED = 5;
	static constexpr int SKELETON_WALK_ANIM_SPEED = 3;

	enum State
	{
		WALK = 0,
		HALF_TURN,
		WAIT,
		FALL,
		DIE,
	};
	
	unsigned char AnimFrameId : 4;
	unsigned char AnimFrameCount : 4;
	unsigned char AnimState : 4;
	unsigned char FallAnimSpeedIndex :4;
	
	int GetYUnderFeet();
	unsigned char GetWidth();
	bool IsThereAnyGroundCollisionAt(int yWorld);
	
	void InitWalk();
	void UpdateWalk();
	void UpdateHalfTurn();
	void UpdateWait();
	void UpdateFall();
	int Draw();
};

#endif