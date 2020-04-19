/*
* This file handle the player progression in the game, and save it to the flash memory
*/

#include <EEPROM.h>
#include "RickArdurous.h"
#include "Progress.h"
#include "MapManager.h"
#include "MapData.h"
#include "Item.h"

namespace Progress
{
	static constexpr int PROGRESSION_SAVE_ADDRESS = 16;
	// the size of char used to save the progress is 2 bytes for the item adress + one byte for every 8 puzzle screen
	const unsigned char ITEM_PROGRESS_SAVE_SIZE = (MapManager::PUZZLE_SCREEN_COUNT >> 3) + 3;

	// a variable to memorize how many living items have been initialized and saved in the eeprom
	unsigned char LivingItemsCount = 0;
	
	// private functions
	void UpdateBit(int eepromAddress, char bit, bool shouldSet);
	bool GetBit(int eepromAddress, char bit);
}

void Progress::ResetProgress()
{
}

void Progress::InitItem(Item * item, unsigned char index)
{
	int eepromAddress = PROGRESSION_SAVE_ADDRESS + (ITEM_PROGRESS_SAVE_SIZE * index);
	EEPROM.put(eepromAddress, (unsigned int)item);
	eepromAddress += 2;
	for (unsigned char i = 0; i < ITEM_PROGRESS_SAVE_SIZE - 2; ++i)
		EEPROM.update(eepromAddress++, (unsigned char)0);
	// save the index in the count, assuming the function will be called in order (last index called last)
	LivingItemsCount = index + 1;
}

void Progress::UpdateBit(int eepromAddress, char bit, bool shouldSet)
{
	// read and update the bit for the screen to save
	unsigned char currentByteValue = EEPROM.read(eepromAddress);
	// change the bit for the current screen to save, according to the specified parameter
	if (shouldSet)
		currentByteValue |= (1 << bit);
	else
		currentByteValue &= ~(1 << bit);
	// and update the byte in the eeprom
	EEPROM.update(eepromAddress, currentByteValue);
}

bool Progress::GetBit(int eepromAddress, char bit)
{
	// read and update the bit for the screen to save
	unsigned char currentByteValue = EEPROM.read(eepromAddress);
	return (currentByteValue & (1 << bit));
}

void Progress::SaveAndLoadProgress(unsigned char currentScreenIdToSave, unsigned char newScreenIdToLoad)
{
	// compute the screen byte and bit for the save and load
	unsigned char screenToSaveByteNumber = 2 + (currentScreenIdToSave >> 3);
	unsigned char screenToSaveBitNumber = currentScreenIdToSave % 8;
	unsigned char screenToLoadByteNumber = 2 + (newScreenIdToLoad >> 3);
	unsigned char screenToLoadBitNumber = newScreenIdToLoad % 8;
	
	// reset the eeprom address at the begining of the progress save
	int eepromAddress = PROGRESSION_SAVE_ADDRESS;
	for (unsigned char i = 0; i < LivingItemsCount; ++i)
	{
		// get the item address
		unsigned int itemAddress;
		EEPROM.get(eepromAddress, itemAddress);
		// first update the bit in the eeprom, according to the current alive status of the item
		UpdateBit(eepromAddress + screenToSaveByteNumber, screenToSaveBitNumber, ((Item*)itemAddress)->IsPropertySet(Item::PropertyFlags::ALIVE));
		// now update the alive status of the current item according to the current bit set in the eeprom
		if (GetBit(eepromAddress + screenToLoadByteNumber, screenToLoadBitNumber))
			((Item*)itemAddress)->SetProperty(Item::PropertyFlags::ALIVE);
		else
			((Item*)itemAddress)->ClearProperty(Item::PropertyFlags::ALIVE);
		// compute the begining address for the next item to read from eeprom
		eepromAddress += ITEM_PROGRESS_SAVE_SIZE;
	}
}
