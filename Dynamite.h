#ifndef _DYNAMITE_H_
#define _DYNAMITE_H_

#include "Item.h"

class Dynamite : public Item
{
public:
	Dynamite();
	Dynamite(int startX, int startY);
	virtual bool Update(UpdateStep step);
	void LightUp(int x, int y);

private:
	static constexpr int DYNAMITE_ANIM_SPEED = 20;
	static constexpr int EXPLOSION_ANIM_SPEED = 6;
	static constexpr int SPARKS_ANIM_SPEED = 5;
	char DynamiteAnimFrameId = -1;
	char SparksAnimFrameId = -1;
	
	void Draw();
};

#endif