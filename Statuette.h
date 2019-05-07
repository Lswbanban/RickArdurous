#ifndef _STATUETTE_H_
#define _STATUETTE_H_

#include "PickUpItem.h"

class Statuette : public PickUpItem
{
public:
	Statuette();
	virtual bool Update(UpdateStep step);
};

#endif