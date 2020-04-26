/**
* The Game Manager handle the whole game state (menu, game playing, game over, etc...)
*/

#include "RickArdurous.h"
#include "GameManager.h"
#include "MapManager.h"
#include "HUD.h"
#include "MainMenu.h"
#include "Rick.h"

GameManager::GameState GameManager::CurrentGameState;

void GameManager::Update()
{
	switch (CurrentGameState)
	{
		case GameState::MAIN_MENU:
			MapManager::Update();
			MainMenu::UpdateMainMenu();
			break;
			
		case GameState::PLAYING:
			// update the managers
			MapManager::Update();
			// update the HUD
			HUD::Update();
			break;
			
		case GameState::GAME_OVER:
			MainMenu::UpdateGameOver(false);
			break;

		case GameState::VICTORY:
			MainMenu::UpdateGameOver(true);
			break;
	}
}

void GameManager::StartNewGame()
{
	// reset the life count and inventory of Rick
	Rick::Reset();
	
	// call init function of some managers
	MapManager::Reset(1, 0, 8);
	
	// switch the current game state
	CurrentGameState = GameState::PLAYING;
}

void GameManager::GoToMainMenu()
{
	// init the Map Manager with the first screen
	MapManager::Reset(0, 0, 0);
	
	// switch the current game state
	CurrentGameState = GameState::MAIN_MENU;
}