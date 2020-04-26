/*
 * Implement the logic and drawing of the final graal item that the player has to collect to win the game
*/

#include "RickArdurous.h"
#include "Graal.h"
#include "SpriteData.h"
#include "GameManager.h"

bool Graal::Update(UpdateStep step)
{
	if (PickupUpdate(step, SpriteData::Statuette, SpriteData::STATUETTE_SPRITE_WIDTH, SpriteData::STATUETTE_SPRITE_HEIGHT, false))
	{
		GameManager::CurrentGameState = GameManager::GameState::VICTORY;
		return true;
	}
	return false;
}
