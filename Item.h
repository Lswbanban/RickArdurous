#ifndef _ITEM_H_
#define _ITEM_H_

class Item
{
public:
	enum PropertyFlags
	{
		NONE = 0,
		LETHAL = 1,
		PICKUP = 1 << 1,
		MIRROR_X = 1 << 2,
		ALIVE = 1 << 3,
		// specific flag for the spikes
		HORIZONTAL_SPIKE = 1 << 7,
	};
	
	Item(int startX, int startY, unsigned char flag);
	virtual void Update() = 0;
	
	bool SetProperty(unsigned char flag) { Property |= flag; }
	bool ClearProperty(unsigned char flag) { Property &= ~flag; }
	bool IsPropertySet(unsigned char flag) { return (Property & flag) != 0; }

protected:
	unsigned char Property = 0;
	int X;
	int Y;
};

#endif