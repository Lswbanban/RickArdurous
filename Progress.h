#ifndef _PROGRESS_H_
#define _PROGRESS_H_

class Item;

namespace Progress
{
	void ResetProgress();
	bool IsItemAlive(Item * item);
	void SetItemAlive(Item * item, bool isAlive);
}

#endif