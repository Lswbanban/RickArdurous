#ifndef _STALACTITE_H_
#define _STALACTITE_H_

#include "Item.h"

class Stalactite : public Item
{
public:
	Stalactite(int startX, int startY, unsigned char flags);
	virtual bool Update(UpdateStep step);

protected:
	enum State
	{
		WAIT = 0,
		FALL,
		DEAD,
	};
	
	unsigned char AnimState = 0;
	
	static void CheckTrigererCallback(Item * me, Item * trigerer);
	void CheckTrigerer(bool isAlive, int trigererX, int trigererY);
};

#endif