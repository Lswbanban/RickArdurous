#ifndef _BULLET_CRATE_H_
#define _BULLET_CRATE_H_

#include "PickUpItem.h"

class BulletCrate : public PickUpItem
{
public:
	BulletCrate(int startX, int startY);
	virtual void Update();
	virtual void PickUp();
};

#endif