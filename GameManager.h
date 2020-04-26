#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

namespace GameManager
{
	enum GameState
	{
		MAIN_MENU = 0,
		PLAYING,
		GAME_OVER,
		VICTORY,
	};
	
	extern GameState CurrentGameState;
	
	void Update();
	void StartNewGame();
}

#endif