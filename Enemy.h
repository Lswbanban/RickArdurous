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
	static constexpr int DEATH_VELOCITY_X = 9;
	static constexpr int SKELETON_SENSOR = 5;

	enum State
	{
		WALK = 0,
		HALF_TURN,
		WAIT,
		FALL,
		DEATH,
	};
	
	unsigned char AnimFrameId : 4;
	unsigned char AnimFrameCount : 4;
	unsigned char AnimState : 4;
	unsigned char FallAnimSpeedIndex :4;
	
	int GetYUnderFeet();
	unsigned char GetWidth();
	unsigned char GetHeight();
	bool IsThereAnyGroundCollisionAt(int yWorld);
	void MoveAccordingToOrientation();
	bool IsRickAlignedWithMe();
	
	void InitWalk();
	void InitFall();
	void InitHalfTurn();
	void UpdateWalk();
	void UpdateHalfTurn();
	void UpdateWait();
	void UpdateFall();
	bool UpdateDeath();
	int Draw(unsigned char color);
};

#endif