#ifndef _DESTROYABLE_BLOCK_H_
#define _DESTROYABLE_BLOCK_H_

#include "Item.h"
class BlockFragment;

class DestroyableBlock : public Item
{
public:
	DestroyableBlock(int startX, int startY, unsigned char flags);
	virtual bool Update(UpdateStep step);

	bool IsLocatedAt(unsigned char mapX, unsigned char mapY, unsigned char spriteId);
	bool IsAlive();
	
	static void Init();

private:
	static constexpr int EXPLOSION_DETECTION_DISTANCE = 5;
	static constexpr int FRAGMENT_COUNT = 3;
	
	static BlockFragment * Fragments[FRAGMENT_COUNT];
	
	void InitDeath();
};

#endif