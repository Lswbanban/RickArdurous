/**
* The Game Manager handle the whole game state (menu, game playing, game over, etc...)
*/

#include "RickArdurous.h"
#include "GameManager.h"
#include "MapManager.h"
#include "MapData.h"
#include "HUD.h"
#include "MainMenu.h"

GameManager::GameState GameManager::CurrentGameState = GameManager::GameState::MAIN_MENU;

void GameManager::Update()
{
	switch (CurrentGameState)
	{
		case GameState::MAIN_MENU:
			MainMenu::Update();
			break;
			
		case GameState::PLAYING:
			// update the managers
			MapManager::Update();
			// update the HUD
			HUD::Update();
			break;
	}
}

void GameManager::StartNewGame()
{
	// call init function of some managers
	MapManager::InitProgress(); // call this before the Init of the MapManager
	MapManager::Init(true);
	
	// switch the current game state
	CurrentGameState = GameState::PLAYING;
}