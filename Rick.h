#ifndef _RICK_H_
#define _RICK_H_

class PickUpItem;

namespace Rick
{
	void Update();
	bool CheckCollisionWithPickUp(PickUpItem * item);
	void Draw();
}

#endif