/**
* Rick Ardurous is a freeware Game for Arduboy platform written by Alban Nanty
*/

#include "RickArdurous.h"
#include "MapManager.h"

// instance of the arduboy class
Arduboy arduboy;

void setup()
{
	// init the debug serial communication
//	Serial.begin(9600);
//	while(!Serial);
  
	arduboy.beginNoLogo();
//	arduboy.begin();
	arduboy.clear();
}

void loop()
{
	// early exit if the frame is not ready
	if (!arduboy.nextFrame())
		return;

	// clear the screen
	arduboy.clear();

	// update the managers
	MapManager::Update();

	// draw the frame buffer
	arduboy.display();
}
