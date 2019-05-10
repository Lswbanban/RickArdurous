#ifndef _MAP_MANAGER_H_
#define _MAP_MANAGER_H_

class Item;

// define the type of pointer on member function of Item, for callback purpose
typedef void (*ItemCallback)(Item* caller, Item* trigerer);

namespace MapManager
{
	void Init(bool shouldRespawn);
	void Update();
	
	// function to add or remove the items currently updated
	void AddItem(Item * item);
	void RemoveItem(Item * item);
	
	// function to get local coordinates
	int GetXOnScreen(int worldX);
	int GetYOnScreen(int worldY);
	bool IsOnScreen(int x, int y, unsigned char spriteWidth, unsigned char spriteHeight);
	
	// Check if there's a solid sprite (static collision) or ladder at the specified world coodinates
	bool IsThereStaticCollisionAt(int xWorld, int yWorld);
	bool IsThereAnyHorizontalCollisionAt(int leftWorld, int rightWorld, int yWorld);
	bool IsThereLadderAt(int xWorld, int yWorld);
	
	// function to iterate on items
	void CallMeBackForEachTrapTriggerer(Item* caller, ItemCallback callback);
	
	// checkpoint functions
	void MemorizeCheckPoint(int rickX, int rickY);
	void RestartToLastCheckpoint();
}

#endif