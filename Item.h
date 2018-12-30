#ifndef _ITEM_H_
#define _ITEM_H_

class Item
{
public:
	Item(int startX, int startY);
	virtual void Update() = 0;

protected:
	int X;
	int Y;
};

#endif