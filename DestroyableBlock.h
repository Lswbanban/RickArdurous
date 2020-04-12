#ifndef _DESTROYABLE_BLOCK_H_
#define _DESTROYABLE_BLOCK_H_

#include "DestroyableItem.h"
class BlockFragment;

class DestroyableBlock : public DestroyableItem
{
public:
	DestroyableBlock();
	virtual bool Update(UpdateStep step);

	bool IsLocatedAt(unsigned char mapX, unsigned char mapY);
	bool IsAlive() { return IsPropertySet(Item::PropertyFlags::ALIVE); }
	
	static void StaticInit();

private:
	static constexpr int FRAGMENT_COUNT = 3;
	
	static BlockFragment * Fragments[FRAGMENT_COUNT];
	
	void InitDeath();
};

#endif