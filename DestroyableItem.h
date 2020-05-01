#ifndef _DESTROYABLE_ITEM_H_
#define _DESTROYABLE_ITEM_H_

#include "LivingItem.h"

class DestroyableItem : public LivingItem
{
public:
	bool CheckLethalDynamite(unsigned char width);
	
private:
	static constexpr int EXPLOSION_DETECTION_DISTANCE = 5;
};

#endif