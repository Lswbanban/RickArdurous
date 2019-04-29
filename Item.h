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
		// specific flag let to the derivated class for handling what they want
		SPECIAL = 1 << 7,
	};
	
	enum UpdateStep
	{
		DRAW_LETHAL = 0,
		CHECK_LETHAL,
		ERASE_BULLET,
		DRAW_ENEMIES,
		CHECK_STATIC_COLLISION,
		DRAW_IGNORED_BY_ENEMIES,
	};
	
	Item(int startX, int startY, unsigned char flag);
	virtual bool Update(UpdateStep step) = 0;
	
	void SetProperty(unsigned char flag) { Property |= flag; }
	void ClearProperty(unsigned char flag) { Property &= ~flag; }
	void InverseProperty(unsigned char flag) { Property = (Property & ~flag) | (~Property & flag); }
	bool IsPropertySet(unsigned char flag) { return (Property & flag) != 0; }

protected:
	int X;
	int Y;
	unsigned char Property = 0;
};

#endif