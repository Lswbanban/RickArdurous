#ifndef _STALAGMITE_H_
#define _STALAGMITE_H_

#include "DestroyableItem.h"

class Stalagmite : public DestroyableItem
{
public:
	virtual bool Update(UpdateStep step);

private:
	static constexpr int DROP_PERIOD = 150;
	static constexpr int SPARKS_ANIM_SPEED = 3;

	union
	{
		unsigned char DropY;
		unsigned char SparksAnimFrameId;
	};
	
	unsigned char DropX;
	
	void Draw();
	void InitDrop();
};

#endif