#ifndef _DESTROYABLE_ITEM_H_
#define _DESTROYABLE_ITEM_H_

#include "Item.h"

class DestroyableItem : public Item
{
public:
	DestroyableItem(unsigned char flags);
	bool CheckLethalDynamite(unsigned char width);
	
private:
	static constexpr int EXPLOSION_DETECTION_DISTANCE = 5;
};

#endif