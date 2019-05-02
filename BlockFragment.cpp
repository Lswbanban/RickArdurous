/*
 * Implement the logic and drawing of fragment of a Destroyable Blocks, when it is destroyed
*/

#include "RickArdurous.h"
#include "BlockFragment.h"
#include "SpriteData.h"
#include "Physics.h"
#include "MapManager.h"

BlockFragment::BlockFragment() : Item(0, 0, Item::PropertyFlags::NONE)
{
}

void BlockFragment::Spawn(int startX, int startY)
{
	// init the coordinate with the starting positions
	X = startX;
	Y = startY;
	// choose a random velocity
	unsigned char velocityX = random(6, 12);
	if (random(2))
		velocityX = -velocityX;
	// randomize the mirror flag
	if (random(2))
		SetProperty(Item::PropertyFlags::MIRROR_X);
	else
		ClearProperty(Item::PropertyFlags::MIRROR_X);
	// start the trajectory
	StoneFallIndex = Physics::StartParabolicTrajectory(startX, startY, velocityX);
	MapManager::AddItem(this);
}

bool BlockFragment::Update(UpdateStep step)
{
	switch (step)
	{
		case Item::UpdateStep::DRAW_IGNORED_BY_ENEMIES:
		{
			// update the trajectory of the stone
			Physics::UpdateParabolicTrajectory(StoneFallIndex, X, Y);
			
			int xOnScreen = MapManager::GetXOnScreen(X);
			int yOnScreen = MapManager::GetYOnScreen(Y);
			arduboy.drawBitmapExtended(xOnScreen, yOnScreen,
								SpriteData::DestroyableBlockPiece,
								SpriteData::DESTROYABLE_BLOCK_PIECE_SPRITE_WIDTH, SpriteData::DESTROYABLE_BLOCK_PIECE_SPRITE_HEIGHT,
								INVERT, IsPropertySet(Item::PropertyFlags::MIRROR_X));

			// check if I'm still on screen
			if (!MapManager::IsOnScreen(X, Y, SpriteData::DESTROYABLE_BLOCK_PIECE_SPRITE_WIDTH, SpriteData::DESTROYABLE_BLOCK_PIECE_SPRITE_HEIGHT))
			{
				// stop the parabolic trajectory
				Physics::StopParabolicTrajectory(StoneFallIndex);
				// we are now out of the screen we can be removed from the MapManager
				return true;
			}
		}
		break;
	}
	return false;
}
