/**
* The Main menu display the menu to start the game or change options
*/

#include "RickArdurous.h"
#include "MainMenu.h"
#include "GameManager.h"
#include "Input.h"
#include "MapData.h"
#include "SpriteData.h"
#include "Graal.h"

namespace MainMenu
{
	static constexpr int LAST_MENU_OPTION = 1;
	static constexpr int MENU_X = 20;
	
	unsigned char SelectedOption = 0;
	
	void DrawMainMenu();
	void DrawVictory();
	void DrawGameOver();
}

void MainMenu::UpdateMainMenu()
{
	// check the input
	if (Input::IsJustPressed(DOWN_BUTTON) && (SelectedOption < LAST_MENU_OPTION))
		SelectedOption++;
	else if (Input::IsJustPressed(UP_BUTTON) && (SelectedOption > 0))
		SelectedOption--;
	else if (Input::IsJustPressed(A_BUTTON) || Input::IsJustPressed(B_BUTTON))
	{
		switch (SelectedOption)
		{
			case 0:
				GameManager::StartNewGame();
				break;
			case 1:
				break;
		}
	}
	
	// draw the menu
	DrawMainMenu();
}

void MainMenu::UpdateGameOver(bool isVictory)
{
	// wait for user to press a button
	if (Input::IsJustPressed(A_BUTTON) || Input::IsJustPressed(B_BUTTON))
		GameManager::CurrentGameState = GameManager::GameState::MAIN_MENU;
	
	if (isVictory)
		DrawVictory();
	else
		DrawGameOver();
	
}

void MainMenu::DrawMainMenu()
{
	unsigned char menuY[] = { 10, 20 };
	arduboy.setCursor(MENU_X, menuY[0]);
	arduboy.print("Play");
	arduboy.setCursor(MENU_X, menuY[1]);
	arduboy.print("Music");
	
	// draw the selected indicator
	arduboy.setCursor(MENU_X - 8, menuY[SelectedOption]);
	arduboy.print('>');
}

void MainMenu::DrawVictory()
{
	// draw the graal!
	arduboy.drawBitmapExtended(61, 10, SpriteData::Graal, SpriteData::GRAAL_SPRITE_WIDTH, SpriteData::GRAAL_SPRITE_HEIGHT, WHITE, false);
	graal1.UpdateShineStar(61, 10, -2, 3, -2, 4);

	// draw the message
	arduboy.setCursor(19, 30);
	arduboy.print("Congratulation!");
	arduboy.setCursor(4, 44);
	arduboy.print("You found the Graal.");
}

void MainMenu::DrawGameOver()
{
	arduboy.setCursor(20, 40);
	arduboy.print("Game Over...");
}
