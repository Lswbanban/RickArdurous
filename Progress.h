#ifndef _PROGRESS_H_
#define _PROGRESS_H_

class Item;

namespace Progress
{
	void InitItem(Item * item, unsigned char index);
	void ResetProgress();
	void SaveAndLoadProgress(unsigned char currentScreenIdToSave, unsigned char newScreenIdToLoad);
}

#endif