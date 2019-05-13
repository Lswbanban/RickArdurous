#ifndef _PICKUP_ITEM_H_
#define _PICKUP_ITEM_H_

#include "Item.h"

class PickUpItem : public Item
{
public:
	PickUpItem() : Item(PropertyFlags::ALIVE) {}

protected:
	void UpdateShineStar(char minX, char maxX, char minY, char maxY);
	bool DoesRickPickMeUp(unsigned char width, unsigned char height);
	
private:
	static constexpr int ANIM_SPEED = 2;
	static constexpr int MIN_PAUSE_TIMES = 10;
	static constexpr int MAX_PAUSE_TIMES = 150;
	
	// the current time to wait before playing the next shining star
	char PauseTime = 0;
	
	// current frame id and direction of the shinning star
	char AnimFrameId = -1;
	char AnimDirection = 1;
	
	// the position shift for the shine star, relative to the statuette
	char ShineStarShiftX = 0;
	char ShineStarShiftY = 0;
};

#endif