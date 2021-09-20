#ifndef _ITEM_H_
#define _ITEM_H_

class Item
{
public:
	enum PropertyFlags
	{
		NONE = 0,
		// this flag is necessary for the MapManager
		DESTROYABLE_BLOCK = 1 << 0,
		TRAP_TRIGERER  = 1 << 1,
		// these are other properties
		IS_VISIBLE = 1 << 3,
		MIRROR_X = 1 << 4,
		ALIVE = 1 << 5,
		// specific flag let to the derivated class for handling what they want
		SPECIAL = 1 << 6,
		SPECIAL_2 = 1 << 7,
	};
	
	enum UpdateStep
	{
		DRAW_LETHAL_BESIDE = 0,
		CHECK_LETHAL_BESIDE,
		DRAW_LETHAL,
		CHECK_LETHAL,
		ERASE_BULLET,
		DRAW_ENEMIES,
		DRAW_STATIC_COLLISION,
		CHECK_STATIC_COLLISION,
		DRAW_IGNORED_BY_ENEMIES,
		RESPAWN,
	};
	
	void Init(int startX, int startY, unsigned char flags);
	virtual bool Update(UpdateStep step) = 0;
	
	void SetProperty(unsigned char flag) { Property |= flag; }
	void ClearProperty(unsigned char flag) { Property &= ~flag; }
	void InverseProperty(unsigned char flag) { Property = (Property & ~flag) | (~Property & flag); }
	bool IsPropertySet(unsigned char flag) { return (Property & flag) == flag; }

	int GetX() { return X; }
	int GetY() { return Y; }

protected:
	int X;
	int Y;
	unsigned char Property = 0;
	
	void CommonInit(int startX, int startY, unsigned char flags);
};

#endif