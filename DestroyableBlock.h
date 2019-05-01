#ifndef _DESTROYABLE_BLOCK_H_
#define _DESTROYABLE_BLOCK_H_

#include "Item.h"

class DestroyableBlock : public Item
{
public:
	DestroyableBlock(int startX, int startY, unsigned char flag);
	virtual bool Update(UpdateStep step);

	bool IsLocatedAt(unsigned char mapX, unsigned char mapY, unsigned char spriteId);
	bool IsAlive();
private:
	static constexpr int EXPLOSION_DETECTION_DISTANCE = 5;
	
	void InitDeath();
};

#endif