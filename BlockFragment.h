#ifndef _BLOCK_FRAGMENT_H_
#define _BLOCK_FRAGMENT_H_

#include "Item.h"
#include "Physics.h"

class BlockFragment : public Item
{
public:
	BlockFragment();
	virtual bool Update(UpdateStep step);
	
	void Spawn(int startX, int startY, int id);
	void Kill();
	
private:
	unsigned char StoneFallIndex = Physics::INVALID_FALL_ID;
};

#endif