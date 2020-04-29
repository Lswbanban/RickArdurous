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
#include "Rick.h"

namespace MainMenu
{
	static constexpr int LAST_MENU_OPTION = 1;
	static constexpr int MENU_X = 46;
	static constexpr int GAME_OVER_ANIM_SPEED = 4;
	
	unsigned char SelectedOption = 0;
	
	// variable for game over animation
	char SpriteY;
	unsigned char GameOverAnimId = SpriteData::RickAnimFrameId::DEATH_START;
	char GameOverAnimDirection = -1;
	
	void DrawMainMenu();
	void DrawStatuetteCount();
	void DrawVictory();
	void DrawGameOver();
	void InitGameOver();
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
				InitGameOver();
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
		GameManager::GoToMainMenu();
	
	if (isVictory)
		DrawVictory();
	else
		DrawGameOver();
	
}

void MainMenu::DrawMainMenu()
{
	// draw the title in a frame
/*	arduboy.fillRect(0, 0, WIDTH, 10, WHITE);
	arduboy.fillRect(0, 0, 3, 15, WHITE);
	
//	unsigned char title[] = "Rick Ardurous";
//	for (unsigned char i = 0; i < sizeof(title); ++i)
//		arduboy.drawChar(50 + (i*6), 1, title[i], BLACK, WHITE, 1);

	
	unsigned char title[] = "Rick";
	for (unsigned char i = 0; i < sizeof(title)-1; ++i)
		arduboy.drawChar(3 + (i*12), 1, title[i], BLACK, WHITE, 2);
	unsigned char title2[] = "Ardurous - -";
	for (unsigned char i = 0; i < sizeof(title2)-1; ++i)
		arduboy.drawChar(55 + (i*6), 1, title2[i], BLACK, WHITE, 1);
*/

	arduboy.fillRect(0, 0, WIDTH, 2, WHITE);
	arduboy.setCursor(13, 3);
	arduboy.print("* Rick Ardurous *");
	arduboy.fillRect(0, 12, WIDTH, 2, WHITE);
	
	// draw some stalactite
	arduboy.drawBitmapExtended(24, 17, SpriteData::Stalactite, SpriteData::STALACTITE_SPRITE_WIDTH, SpriteData::STALACTITE_SPRITE_HEIGHT, WHITE, false);
	arduboy.drawBitmapExtended(45, 15, SpriteData::Stalactite, SpriteData::STALACTITE_SPRITE_WIDTH, SpriteData::STALACTITE_SPRITE_HEIGHT, WHITE, false);
	arduboy.drawBitmapExtended(75, 15, SpriteData::Stalactite, SpriteData::STALACTITE_SPRITE_WIDTH, SpriteData::STALACTITE_SPRITE_HEIGHT, WHITE, true);
	arduboy.drawBitmapExtended(93, 21, SpriteData::Stalactite, SpriteData::STALACTITE_SPRITE_WIDTH, SpriteData::STALACTITE_SPRITE_HEIGHT, WHITE, false);
	arduboy.drawBitmapExtended(97, 20, SpriteData::Stalactite, SpriteData::STALACTITE_SPRITE_WIDTH, SpriteData::STALACTITE_SPRITE_HEIGHT, WHITE, true);
	
	unsigned char menuY[] = { 34, 45 };
	arduboy.setCursor(MENU_X, menuY[0]);
	arduboy.print("Play");
	arduboy.setCursor(MENU_X, menuY[1]);
	arduboy.print("Music");
	
	// draw the selected indicator
	arduboy.setCursor(MENU_X - 8, menuY[SelectedOption]);
	arduboy.print('>');
}

void MainMenu::DrawStatuetteCount()
{
	arduboy.print(Rick::StatuetteCount, DEC);
	arduboy.drawBitmapExtended(arduboy.GetCursorX() + 2, arduboy.GetCursorY() -1, SpriteData::Statuette, SpriteData::STATUETTE_SPRITE_WIDTH, SpriteData::STATUETTE_SPRITE_HEIGHT, WHITE, false);
	arduboy.setCursor(arduboy.GetCursorX() + (8 + SpriteData::STATUETTE_SPRITE_WIDTH), arduboy.GetCursorY());
}

void MainMenu::DrawVictory()
{
	// draw the graal!
	arduboy.drawBitmapExtended(61, 8, SpriteData::Graal, SpriteData::GRAAL_SPRITE_WIDTH, SpriteData::GRAAL_SPRITE_HEIGHT, WHITE, false);
	graal1.UpdateShineStar(61, 8, -2, 3, -2, 4);

	// draw the message
	arduboy.setCursor(21, 26);
	arduboy.print("Congratulation!");
	arduboy.setCursor(7, 46);
	arduboy.print("You found the Graal");
	arduboy.setCursor(43, 56);
	arduboy.print("and ");
	DrawStatuetteCount();
}

void MainMenu::InitGameOver()
{
	SpriteY = 63;
	GameOverAnimId = SpriteData::RickAnimFrameId::DEATH_START;
	GameOverAnimDirection = -1;
}

void MainMenu::DrawGameOver()
{
	// updat the animation of Rick sprite
	if (arduboy.everyXFrames(GAME_OVER_ANIM_SPEED))
	{
		// reverse direction if we reach the end of the loop
		if ((GameOverAnimId == SpriteData::RickAnimFrameId::DEATH_START) ||
			(GameOverAnimId == SpriteData::RickAnimFrameId::DEATH_END))
			GameOverAnimDirection = -GameOverAnimDirection;
		// increase the anim frame
		GameOverAnimId += GameOverAnimDirection;
		// decrease altitude
		SpriteY--;
	}
	// draw rick sprite
	arduboy.drawBitmapExtended(GameOverAnimId - SpriteData::RickAnimFrameId::DEATH_START, SpriteY, SpriteData::Rick[GameOverAnimId], SpriteData::RICK_SPRITE_WIDTH, SpriteData::RICK_SPRITE_HEIGHT, WHITE, false);

	arduboy.setCursor(16, 8);
	arduboy.print("Game Over...");
	arduboy.setCursor(16, 26);
	arduboy.print("You died before");
	arduboy.setCursor(16, 36);
	arduboy.print("reaching the Graal");
	arduboy.setCursor(16, 54);
	DrawStatuetteCount();
	arduboy.print("collected");
}
