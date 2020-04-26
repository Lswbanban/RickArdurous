/**
* The Game Manager handle the whole game state (menu, game playing, game over, etc...)
*/

#include "RickArdurous.h"
#include "GameManager.h"
#include "MapManager.h"
#include "HUD.h"
#include "MainMenu.h"
#include "Rick.h"

GameManager::GameState GameManager::CurrentGameState = GameManager::GameState::MAIN_MENU;

void GameManager::Update()
{
	switch (CurrentGameState)
	{
		case GameState::MAIN_MENU:
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
	MapManager::Reset();
	
	// switch the current game state
	CurrentGameState = GameState::PLAYING;
}