#ifndef _DYNAMITE_H_
#define _DYNAMITE_H_

#include "Item.h"

class Dynamite : public Item
{
public:
	Dynamite();
	Dynamite(int startX, int startY);
	virtual bool Update();
	void LightUp(int x, int y);

private:
	const int DYNAMITE_ANIM_SPEED = 20;
	const int EXPLOSION_ANIM_SPEED = 6;
	const int SPARKS_ANIM_SPEED = 5;
	char DynamiteAnimFrameId = -1;
	char SparksAnimFrameId = -1;
};

#endif