#ifndef _ITEM_H_
#define _ITEM_H_

class Item
{
public:
	enum ItemType
	{
		NO_TYPE = 0,
		LETHAL, // spikes, stalactite, dynamite
		ENEMIES,
		BULLET,
		DESTROYABLE_BLOCK,
		IGNORED_BY_ENEMIES,
	};
	
	enum PropertyFlags
	{
		NONE = 0,
		// the first 3 bits are reserved for the Type
		// this flags will impact the update step
		STATIC_COLLISION_NEEDED = 1 << 4,
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
		RESPAWN,
	};
	
	Item(int startX, int startY, unsigned char itemType, unsigned char flags);
	virtual bool Update(UpdateStep step) = 0;
	
	unsigned char GetType() { return (TypeAndProperty & 0x07); }
	void SetType(unsigned char itemType) { TypeAndProperty = (TypeAndProperty & 0xF8) | itemType; }
	void SetProperty(unsigned char flag) { TypeAndProperty |= flag; }
	void ClearProperty(unsigned char flag) { TypeAndProperty &= ~flag; }
	void InverseProperty(unsigned char flag) { TypeAndProperty = (TypeAndProperty & ~flag) | (~TypeAndProperty & flag); }
	bool IsPropertySet(unsigned char flag) { return (TypeAndProperty & flag) != 0; }

protected:
	int X;
	int Y;
	unsigned char TypeAndProperty = 0;
};

#endif