#ifndef _ITEM_H_
#define _ITEM_H_

class Item
{
public:
	enum PropertyFlags
	{
		NONE = 0,
		// these flags will impact the update step
		LETHAL = 1,
		ENEMIES = 1 << 1,
		BULLET = 1 << 2,
		STATIC_COLLISION_NEEDED = 1 << 3,
		IGNORED_BY_ENEMIES = 1 << 4,
		// these are other properties
		MIRROR_X = 1 << 5,
		ALIVE = 1 << 6,
		// specific flag for the spikes
		HORIZONTAL_SPIKE = 1 << 7,
	};
	
	enum UpdateStep
	{
		DRAW_LETHAL = 0,
		DRAW_DANGEROUS,
		ERASE_BULLET,
		CHECK_STATIC_COLLISION,
		DRAW_IGNORED_BY_ENEMIES,
	};
	
	Item(int startX, int startY, unsigned char flag);
	virtual bool Update(UpdateStep step) = 0;
	
	bool SetProperty(unsigned char flag) { Property |= flag; }
	bool ClearProperty(unsigned char flag) { Property &= ~flag; }
	bool IsPropertySet(unsigned char flag) { return (Property & flag) != 0; }

protected:
	unsigned char Property = 0;
	int X;
	int Y;
};

#endif