#ifndef _ARROW_BULLET_H_
#define _ARROW_BULLET_H_

#include "Item.h"

class ArrowBullet : public Item
{
public:
	ArrowBullet();
	ArrowBullet(bool isArrow);
	virtual bool Update(UpdateStep step);
	void Fire(int x, int y, bool isMovingToLeft);

private:
	const int BULLET_SPEED = 4;
	const int BULLET_WIDTH = 3;
	const int ARROW_SPEED = 2;
	const int ARROW_WIDTH = 8;
	const int SPARKS_ANIM_SPEED = 3;
	const int NO_PIXEL_FOUND = 1000; // special return value for SearchForPixelColorAlongBulletRay() when no color is found
	
	union
	{
		char CurrentBulletSpeed; // the current speed (which could be null on the first frame)
		char SparksAnimFrameId; // the frame id to play sparks when the bullet hit the wall
	};
	
	unsigned char GetWidth();
	int GetBulletRayCastStartX();
	void DrawBulletRay(unsigned char color);
	int SearchForPixelColorAlongBulletRay(unsigned int color);
	void KillBulletWithoutSparks();
};

#endif