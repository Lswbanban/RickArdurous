#ifndef _STALAGMITE_H_
#define _STALAGMITE_H_

#include "DestroyableItem.h"

class Stalagmite : public DestroyableItem
{
public:
	Stalagmite(int startX, int startY, unsigned char flags);
	virtual bool Update(UpdateStep step);
private:
	static constexpr int SPARKS_ANIM_SPEED = 3;

	unsigned char SparksAnimFrameId = 0;
	
	void Draw();
};

#endif