/**
* The Main menu display the menu to start the game or change options
*/

#include "RickArdurous.h"
#include "MainMenu.h"
#include "GameManager.h"
#include "Input.h"
namespace MainMenu
{
	static constexpr int LAST_MENU_OPTION = 1;
	static constexpr int MENU_X = 20;
	
	unsigned char SelectedOption = 0;
	
	void Draw();
}

void MainMenu::Update()
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
	Draw();
}

void MainMenu::Draw()
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
