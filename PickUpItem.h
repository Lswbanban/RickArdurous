#ifndef _PICKUP_H_
#define _PICKUP_H_

#include "Item.h"

class PickUpItem : public Item
{
public:
	PickUpItem(int startX, int startY, unsigned char flag) : Item(startX, startY, flag) {}
	virtual void PickUp() = 0;
};

#endif