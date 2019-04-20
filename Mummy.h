#ifndef _MUMMY_H_
#define _MUMMY_H_

#include "Item.h"

class Mummy : public Item
{
public:
	Mummy(int startX, int startY);
	virtual bool Update(UpdateStep step);
	
private:
	unsigned char AnimFrameId : 3;
	unsigned char AnimFrameCount : 5;
};

#endif