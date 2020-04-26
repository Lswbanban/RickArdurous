/**
* Rick Ardurous is a freeware Game for Arduboy platform written by Alban Nanty
*/

#include "RickArdurous.h"
#include "Input.h"
#include "GameManager.h"
#include "MapData.h"

// instance of the arduboy class
CustomArduboy arduboy;

void setup()
{
	// init the debug serial communication
//	Serial.begin(9600);
//	while(!Serial);
  
	arduboy.beginNoLogo();
//	arduboy.begin();
	arduboy.clear();
	
	// init the random generator
	arduboy.initRandomSeed();
	
	// init the progress
	MapManager::InitProgress(); // call this before the Init of the MapManager
	
	// go to main menu
	GameManager::GoToMainMenu();
}

void loop()
{
	// early exit if the frame is not ready
	if (!arduboy.nextFrame())
		return;

	// clear the screen
	arduboy.clear();

	// update the input
	Input::Update();
	
	// update the game state
	GameManager::Update();
	
	// draw the frame buffer
	arduboy.display();
}
