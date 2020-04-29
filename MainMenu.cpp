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
	// draw an extra line of stones on top of the screen (to fill the gap of the HUD)
	for (unsigned char i = 0; i < 16; ++i)
		arduboy.drawBitmapExtended(i * SpriteData::LEVEL_SPRITE_WIDTH, 0,
				SpriteData::Walls[1 + (i % 2)], SpriteData::LEVEL_SPRITE_WIDTH, SpriteData::LEVEL_SPRITE_HEIGHT, WHITE, (i % 3));

	// draw the title in black over white
	arduboy.fillRect(1, 1, 84, 11, WHITE);
	unsigned char title[] = "Rick Ardurous";
	for (unsigned char i = 0; i < sizeof(title) - 1; ++i)
		arduboy.drawChar(5 + (i*6), 3, title[i], BLACK, WHITE, 1);

	// draw some stalactites
	unsigned char x[] = {24, 45, 75, 93, 97 };
	unsigned char y[] = {17, 15, 15, 21, 20 };
	for (unsigned char i = 0; i < sizeof(x); ++i)
		arduboy.drawBitmapExtended(x[i], y[i], SpriteData::Stalactite, SpriteData::STALACTITE_SPRITE_WIDTH, SpriteData::STALACTITE_SPRITE_HEIGHT, WHITE, false);

	// draw the menu
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
