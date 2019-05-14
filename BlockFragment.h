#ifndef _BLOCK_FRAGMENT_H_
#define _BLOCK_FRAGMENT_H_

#include "Item.h"

class BlockFragment : public Item
{
public:
	BlockFragment();
	virtual bool Update(UpdateStep step);
	
	void Spawn(int startX, int startY, int id);
	
private:
	unsigned char StoneFallIndex;
};

#endif