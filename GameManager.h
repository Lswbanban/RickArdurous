#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

namespace GameManager
{
	enum GameStateEnum
	{
		MAIN_MENU = 0,
		PLAYING,
		GAME_OVER,
		VICTORY,
		HELP_SCREEN,
	};
	typedef unsigned char GameState;
	
	extern GameState CurrentGameState;
	
	void Update();
	void StartNewGame();
	void GoToMainMenu();
}

#endif