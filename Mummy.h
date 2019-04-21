#ifndef _MUMMY_H_
#define _MUMMY_H_

#include "Item.h"

class Mummy : public Item
{
public:
	Mummy(int startX, int startY);
	virtual bool Update(UpdateStep step);
	
private:
	enum State
	{
		WALK = 0,
		FALL,
		DIE,
	};
	
	unsigned char AnimFrameId : 4;
	unsigned char AnimFrameCount : 4;
	unsigned char AnimState = 0;
	
	bool CheckPixelColumn(int x, int startY, int endX);
	void UpdateWalk();
	void UpdateFall();
	int Draw(unsigned char color);
};

#endif