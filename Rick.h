#ifndef _RICK_H_
#define _RICK_H_

class PickUpItem;

namespace Rick
{
	const char MAX_LIFE_COUNT = 6;
	const char MAX_STATUETTE_COUNT = 20;
	const char MAX_BULLET_COUNT = 5;
	const char MAX_DYNAMITE_COUNT = 5;
	
	void UpdateInput();
	void CheckLethalCollision();
	void CheckCollisionWithPickUp(PickUpItem * item);
	void CheckStaticCollision();
	unsigned int Draw();
	bool IsAlive();
	
	int GetX();
	int GetY();
	
	// Rick Inventory
	extern char LifeCount;
	extern char StatuetteCount;
	extern char BulletCount;
	extern char DynamiteCount;
}

#endif