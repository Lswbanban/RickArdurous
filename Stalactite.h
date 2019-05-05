#ifndef _STALACTITE_H_
#define _STALACTITE_H_

#include "Item.h"

class Stalactite : public Item
{
public:
	Stalactite(int startX, int startY, unsigned char flags);
	virtual bool Update(UpdateStep step);

protected:
	static constexpr int SHAKING_SPEED = 120;
	static constexpr int SPARKS_ANIM_SPEED = 3;
	
	unsigned char SparksAnimFrameId;
	unsigned char FallAnimSpeedIndex;

	static void CheckTrigererCallback(Item * me, Item * trigerer);
	void CheckTrigerer(bool isAlive, int trigererX, int trigererY);
	void Draw(int shakeX);
};

#endif