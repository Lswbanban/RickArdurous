/*
* This file handle the player progression in the game, and save it to the flash memory
*/

#include <EEPROM.h>
#include "RickArdurous.h"
#include "Progress.h"
#include "MapManager.h"
#include "MapData.h"

namespace Progress
{
	static constexpr int PROGRESSION_SAVE_ADDRESS = 16;
	
	Item * DeadItems[MapManager::MAX_LIVING_ITEM_COUNT_PER_PUZZLE_SCREEN];
	unsigned char DeadItemsCount = 0;
	
	// private functions
	void AddItemToDeadPool(Item * item);
	void RemoveItemFromDeadPool(unsigned char index);
	void RemoveItemFromDeadPool(Item * item);
}

void Progress::ResetProgress()
{
	DeadItemsCount = 0;
}

bool Progress::IsItemAlive(Item * item)
{
	for (unsigned char i = 0; i < DeadItemsCount; ++i)
		if (DeadItems[i] == item)
			return false;
	return true;
}

void Progress::SetItemAlive(Item * item, bool isAlive)
{
	if (isAlive)
		RemoveItemFromDeadPool(item);
	else
		AddItemToDeadPool(item);
}

void Progress::SaveAndLoadProgress(unsigned char currentScreenIdToSave, unsigned char newScreenIdToLoad)
{
	unsigned char screenByteNumber = currentScreenIdToSave >> 3;
	unsigned char screenBitNumber = currentScreenIdToSave % 8;
	
	// compute how many bytes we need to store one bit for all the puzzle screen
	unsigned char byteCount = MapManager::PUZZLE_SCREEN_COUNT >> 3;
	if ((MapManager::PUZZLE_SCREEN_COUNT % 8) != 0)
		byteCount++;
	
	int eepromAddress = PROGRESSION_SAVE_ADDRESS;
	for (unsigned char i = 0; i < MapManager::MAX_LIVING_ITEM_COUNT_PER_PUZZLE_SCREEN; ++i)
	{
		// save the item eepromAddress
		int itemAddress;
		EEPROM.get(eepromAddress, itemAddress);
		// if the itemAddress is null, that means we reach the end of all saved item in eeprom
		if (itemAddress == 0)
			break;
		// iterate on all the items to check if we found the current item
		for (unsigned char j = 0; j < DeadItemsCount; ++j)
			if ((int)DeadItems[j] == itemAddress)
			{
				// move to the address of the byte saving the alive status of the screen to save
				eepromAddress += 2 + screenByteNumber;
				// read and update the bit for the screen to save
				unsigned char currentByteValue;
				EEPROM.get(eepromAddress, currentByteValue);
				EEPROM.update(eepromAddress, currentByteValue | (1 << screenBitNumber));
				// remove the item from the pool, after updating
				RemoveItemFromDeadPool(j);
				break;
			}
		// compute the begining address for the next item to save
		eepromAddress += 2 + byteCount;
	}
	
	// check if there's remaining item to save
	for (unsigned char j = 0; j < DeadItemsCount; ++j)
	{
		EEPROM.update(eepromAddress, (int)DeadItems[j]);
		EEPROM.update(eepromAddress, 1 << screenBitNumber);
		// compute the begining address for the next item to save
		eepromAddress += 2 + byteCount;
	}
	
	// reset the dead pool after saving all the items
	DeadItemsCount = 0;
	
	// compute the screen byte and bit for the load
	screenByteNumber = newScreenIdToLoad >> 3;
	screenBitNumber = newScreenIdToLoad % 8;

	eepromAddress = PROGRESSION_SAVE_ADDRESS;
	for (unsigned char i = 0; i < MapManager::MAX_LIVING_ITEM_COUNT_PER_PUZZLE_SCREEN; ++i)
	{
		// save the item eepromAddress
		int itemAddress;
		EEPROM.get(eepromAddress, itemAddress);
		// if the itemAddress is null, that means we reach the end of all saved item in eeprom
		if (itemAddress == 0)
			break;
		
		// move to the address of the byte saving the alive status of the screen to save
		eepromAddress += 2 + screenByteNumber;
		// read and update the bit for the screen to save
		unsigned char currentByteValue;
		EEPROM.get(eepromAddress, currentByteValue);

		// if the item is dead for the next screen to load, then add it in the dead pool
		if (currentByteValue & (1 << screenBitNumber))
			AddItemToDeadPool((Item*)itemAddress);
	}
}

void Progress::AddItemToDeadPool(Item * item)
{
	if (DeadItemsCount < MapManager::MAX_LIVING_ITEM_COUNT_PER_PUZZLE_SCREEN)
	{
		// search if the item is not already inside the array
		for (unsigned char i = 0; i < DeadItemsCount; ++i)
			if (DeadItems[i] == item)
				return;
		// add the item to the last position of the array
		DeadItems[DeadItemsCount++] = item;
	}
}

void Progress::RemoveItemFromDeadPool(unsigned char index)
{
	// decrease the item count
	DeadItemsCount--;
	// if the array is not empty, move the last item to the empty place
	DeadItems[index] = DeadItems[DeadItemsCount];
}

void Progress::RemoveItemFromDeadPool(Item * item)
{
	for (unsigned char i = 0; i < DeadItemsCount; ++i)
		if (DeadItems[i] == item)
		{
			RemoveItemFromDeadPool(i);
			// exit the loop when we have found and removed the item
			break;
		}
}

