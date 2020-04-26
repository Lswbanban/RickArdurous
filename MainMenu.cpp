/**
* The Main menu display the menu to start the game or change options
*/

#include "RickArdurous.h"
#include "MainMenu.h"
#include "GameManager.h"

void MainMenu::Update()
{
	GameManager::StartNewGame();
}
