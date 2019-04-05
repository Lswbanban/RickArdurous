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
	void CheckLadderCollision();
	unsigned char GetFeetYOnScreen();
	unsigned int Draw();
	bool IsAlive();
	
	// function to get the coordinate of the sprite of the main character
	int GetX();
	int GetY();
	// function to get the coordinate when the screen should do a transition
	int GetLeftForScreenTransition();
	int GetRightForScreenTransition();
	int GetTopForScreenTransition();
	int GetBottomForScreenTransition();
	
	// Rick Inventory
	extern char LifeCount;
	extern char StatuetteCount;
	extern char BulletCount;
	extern char DynamiteCount;
}

#endif