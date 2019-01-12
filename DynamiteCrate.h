#ifndef _DYNAMITE_CRATE_H_
#define _DYNAMITE_CRATE_H_

#include "PickUpItem.h"

class DynamiteCrate : public PickUpItem
{
public:
	DynamiteCrate(int startX, int startY);
	virtual bool Update(UpdateStep step);
	virtual void PickUp();
};

#endif