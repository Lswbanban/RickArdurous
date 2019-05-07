/**
* The Map Manager handle the drawing of the map
*/
#include "RickArdurous.h"
#include "MapManager.h"
#include "MapData.h"
#include "SpriteData.h"
#include "Rick.h"
#include "PickUpItem.h"
#include "DestroyableBlock.h"
#include <avr/pgmspace.h>
#include "Input.h"

namespace MapManager
{
	// the vertical shift value in pixel that should be aplied to the camera when drawing the level
	const int CAMERA_VERTICAL_SHIFT = 6;
	const int NB_HORIZONTAL_SPRITE_PER_SCREEN = 16;
	const int NB_VERTICAL_SPRITE_PER_SCREEN = 8;
	
	// The current camera coordinate reference the top left corner of the screen portion of the level, in the big level array.
	int CameraX = 0;
	int CameraY = 0;
	
	// The target camera coordinates
	int TargetCameraX = 0;
	int TargetCameraY = 0;
	
	// This variable is used to store a temporary shift of the camera during a transition animation
	char CameraTransitionX = 0;
	char StartDrawSpriteX = 0;
	char EndDrawSpriteX = 0;
	char CameraTransitionY = 0;
	char StartDrawSpriteY = 0;
	
	// the items to currently update
	static const unsigned int MAX_UPDATABLE_ITEM_COUNT = 100;
	Item * ItemsToUpdate[MAX_UPDATABLE_ITEM_COUNT];
	unsigned char ItemsToUpdateCount = 0;
	
	// debug draw state
	unsigned char DebugDrawStep = 255;
	
	void RemoveItem(int index);
	void UpdateItems(Item::UpdateStep updateStep);
	void Respawn();
	void AnimateCameraTransition();
	int GetCameraSpeed(int step, int subStep);
	void Draw(unsigned char minSpriteIndex, unsigned char maxSpriteIndex, unsigned char rickFeetOnScreen);
	unsigned char GetLevelSpriteAt(int xWorld, int yWorld);
	bool IsDestroyableBlockAlive(unsigned char spriteLevelX, unsigned char spriteLevelY, unsigned char spriteId);
}

void MapManager::AddItem(Item * item)
{
	if (ItemsToUpdateCount < MAX_UPDATABLE_ITEM_COUNT)
		ItemsToUpdate[ItemsToUpdateCount++] = item;
}

void MapManager::RemoveItem(Item * item)
{
	for (int i = 0; i < ItemsToUpdateCount; ++i)
		if (ItemsToUpdate[i] == item)
		{
			// remove the item found
			RemoveItem(i);
			// exit the loop when we have found and removed the item
			break;
		}
}

void MapManager::CallMeBackForEachTrapTriggerer(Item* caller, ItemCallback callback)
{
	for (int i = 0; i < ItemsToUpdateCount; i++)
		if (ItemsToUpdate[i]->IsPropertySet(Item::PropertyFlags::TRAP_TRIGERER))
			(*callback)(caller, ItemsToUpdate[i]);
}

void MapManager::RemoveItem(int index)
{
	// decrease the item count
	ItemsToUpdateCount--;
	// if the array is not empty, move the last item to the empty place
	ItemsToUpdate[index] = ItemsToUpdate[ItemsToUpdateCount];
}

void MapManager::Init(bool shouldRespawn)
{
	(*MapManager::ItemInitFunctions[0])(shouldRespawn);
}

void MapManager::UpdateItems(Item::UpdateStep updateStep)
{
	// debug early exit
	if (updateStep > DebugDrawStep)
		return;
	
	// iterate on all the items, and if one return true, we remove it from the update array
	for (int i = 0; i < ItemsToUpdateCount; i++)
		if (ItemsToUpdate[i]->Update(updateStep))
		{
			RemoveItem(i);
			i--;
		}
}

void MapManager::Respawn()
{
	// debug code for now, reinit the item count, and readd every thing
	ItemsToUpdateCount = 0;
	Init(true);
}

void MapManager::Update()
{
	// debug code
	if (Input::IsDown(B_BUTTON) && Input::IsJustPressed(UP_BUTTON))
		DebugDrawStep++;
	if (Input::IsDown(B_BUTTON) && Input::IsJustPressed(DOWN_BUTTON))
		DebugDrawStep--;
	if (Input::IsDown(B_BUTTON) && Input::IsJustPressed(LEFT_BUTTON))
		Respawn();
	
	
	// update the input of the main character
	Rick::UpdateInput();
	
	// update the lethal entities
	MapManager::UpdateItems(Item::UpdateStep::DRAW_LETHAL);

	// Check the lethal collision for Rick after drawing the lethal items
	Rick::CheckLethalCollision();
	
	// Check lethal collision also for the ennemies (they should draw in black to erase the bullets) or destroyable blocks
	MapManager::UpdateItems(Item::UpdateStep::CHECK_LETHAL);

	// erase the bullet to avoid the bullet to be considered as static collision
	// also this will kill the bullet that hit Rick or an Enemy
	MapManager::UpdateItems(Item::UpdateStep::ERASE_BULLET);

	// Draw the ennemies
	MapManager::UpdateItems(Item::UpdateStep::DRAW_ENEMIES);

	// Check again the lethal collision for Rick because enemies are lethal to the player
	Rick::CheckLethalCollision();

	// get the position of the feet of rick in screen coordinate
	unsigned char rickFeetOnScreen = Rick::GetFeetYOnScreen();
	
	// Draw the static collision of the map
	Draw(SpriteData::BLOCK_8_8, SpriteData::PLATFORM, rickFeetOnScreen);

	// check the collision with the walls, floor and ceilling after the map has been drawn
	Rick::CheckStaticCollision();

	// draw the platforms above the player after checking the collision of the player
	Draw(SpriteData::PLATFORM, SpriteData::PLATFORM, rickFeetOnScreen);

	// call the function to check the static collision for the items that need it, including the Enemies
	MapManager::UpdateItems(Item::UpdateStep::CHECK_STATIC_COLLISION);

	// draw the pickup items or all the items ignores by the ennemies like a burning dynamite
	MapManager::UpdateItems(Item::UpdateStep::DRAW_IGNORED_BY_ENEMIES);

	// draw the ladders after checking the collision
	Draw(SpriteData::LADDER, SpriteData::LADDER, rickFeetOnScreen);

	// update the main character
	Rick::Draw();
	
	// animate the camera (in case the target as changed).
	// Should be done before or after all the drawing to have a consistent conversion from world coord to screen coord
	AnimateCameraTransition();
}

int MapManager::GetXOnScreen(int worldX)
{
	return worldX - (CameraX * SpriteData::LEVEL_SPRITE_WIDTH) - CameraTransitionX;
}

int MapManager::GetYOnScreen(int worldY)
{
	return worldY - (CameraY * SpriteData::LEVEL_SPRITE_HEIGHT) - CameraTransitionY + CAMERA_VERTICAL_SHIFT;
}

bool MapManager::IsOnScreen(int x, int y, unsigned char spriteWidth, unsigned char spriteHeight)
{
	// translate global coord to coord local to the screen
	int xOnScreen = MapManager::GetXOnScreen(x);
	int yOnScreen = MapManager::GetYOnScreen(y);
	// check that the part of the main character (including the sprite width and height) is inside the screen dimension
	return (xOnScreen + spriteWidth >= 0) && (xOnScreen < WIDTH) && (yOnScreen + spriteHeight >= 0) && (yOnScreen < HEIGHT);
}

bool MapManager::IsThereStaticCollisionAt(int xWorld, int yWorld)
{
	return GetLevelSpriteAt(xWorld, yWorld) < SpriteData::WallId::LADDER;
}

bool MapManager::IsThereLadderAt(int xWorld, int yWorld)
{
	unsigned char spriteId = GetLevelSpriteAt(xWorld, yWorld);
	return (spriteId == SpriteData::WallId::LADDER) || (spriteId == SpriteData::WallId::PLATFORM_WITH_LADDER);
}

unsigned char MapManager::GetLevelSpriteAt(int xWorld, int yWorld)
{
	// convert the world coordinate into index for the sprite map
	int mapX = xWorld / SpriteData::LEVEL_SPRITE_WIDTH;
	int mapY = yWorld / SpriteData::LEVEL_SPRITE_HEIGHT;
	// check if we are inside the map. If not, consider that there is collision
	// to avoid the main character to exit the map and navigate into random memory
	if ((mapX < 0) || (mapX >= MapManager::LEVEL_SIZE_X) || (mapY < 0) || (mapY >= MapManager::LEVEL_SIZE_Y))
		return SpriteData::BLOCK_8_8;
	// check if the specific sprite id on the map if empty or not
	return pgm_read_byte(&(Level[mapY][mapX]));
}

bool MapManager::IsDestroyableBlockAlive(unsigned char spriteLevelX, unsigned char spriteLevelY, unsigned char spriteId)
{
	for (int i = 0; i < ItemsToUpdateCount; i++)
		if (ItemsToUpdate[i]->IsPropertySet(Item::PropertyFlags::DESTROYABLE_BLOCK))
		{
			DestroyableBlock * block = (DestroyableBlock*)ItemsToUpdate[i];
			if (block->IsLocatedAt(spriteLevelX, spriteLevelY, spriteId))
				return block->IsAlive();
		}
	return false;
}

/**
 * Tell if there is any horizontal collision (i.e. ground or ceiling) at the specified world vertical coordinate,
 * and in between specified x world coordinates.
 * This function will test two pixels on the left and the right as specified in parameter.
 * If the specified y coordinate is outside the screen, then this function will ask the MapManager to check if there is
 * a sprite at that place in the level, to still have accurate collision event if the ground or ceiling is outside the
 * the screen.
 */
bool MapManager::IsThereAnyHorizontalCollisionAt(int leftWorld, int rightWorld, int yWorld)
{
	// get the coordinates to check on screen
	int leftOnScreen = MapManager::GetXOnScreen(leftWorld);
	int rightOnScreen = MapManager::GetXOnScreen(rightWorld);
	int yOnScreen = MapManager::GetYOnScreen(yWorld);
	// check if the Y coordinate is out of the screen, if yes ask the map manager if there is a sprite below the scrren
	if ((yOnScreen < 0) || (yOnScreen >= HEIGHT))
		return MapManager::IsThereStaticCollisionAt(leftWorld, yWorld) || 
				MapManager::IsThereStaticCollisionAt(rightWorld, yWorld);
	// for the x coordinate, check individualy and if on screen check the pixel
	bool isLeftOnScreen = (leftOnScreen >= 0) && (leftOnScreen < WIDTH);
	bool isRightOnScreen = (rightOnScreen >= 0) && (rightOnScreen < WIDTH);
	// if the coordinates are on screen, check the frame buffer
	return (isLeftOnScreen && (arduboy.getPixel(leftOnScreen, yOnScreen) == WHITE)) ||
			(isRightOnScreen && (arduboy.getPixel(rightOnScreen, yOnScreen) == WHITE));
}

/**
 * @param step the current step in the scrolling between 0 and 8
 * @param subStep the current subStep bewteen 0 and 7
 */
int MapManager::GetCameraSpeed(int step, int subStep)
{
	// check if we need to move every frame or not
	if (step > 1)
	{
		if (step > 8)
			step = 8;
		// this array return the number of pixel the camera should move this frame
		char speed[] = { 1, 1, 1, 2, 2, 3, 4, 4, 4 };
		return speed[step];
	}
	else
	{
		// use an array to declare the number of frame to wait
		char frame[] = { 1, 2, 3, 4 };
		// check if we need to wait or if we can advance the camera transition
		if (arduboy.everyXFrames(frame[subStep >> 1]))
			return 1;
		else
			return 0;
	}
}

/**
 * this function first check if the main charactert has exited the screen.
 * If yes, that means we need to start an animation of the camera to switch to the next puzzle screen.
 * Then the function will calculate the difference between the current position of the camera
 * and the target position, and animate the camera position to reach the target.
 */
void MapManager::AnimateCameraTransition()
{
	if (Rick::IsAlive())
	{
		// Check if we should start a camera transition (if the main character exit the screen)
		// because NB_VERTICAL_SPRITE_PER_SCREEN=8 then the masking if equivalent to the computation
		int screenPuzzleY = CameraY & 0xFFF8; // i.e. (CameraY / NB_VERTICAL_SPRITE_PER_SCREEN) * NB_VERTICAL_SPRITE_PER_SCREEN
		if (Rick::GetBottomForScreenTransition() <= (screenPuzzleY * SpriteData::LEVEL_SPRITE_HEIGHT))
		{
			TargetCameraY = screenPuzzleY - NB_VERTICAL_SPRITE_PER_SCREEN;
		}
		else
		{
			int nextScreenPuzzleY = screenPuzzleY + NB_VERTICAL_SPRITE_PER_SCREEN;
			if (Rick::GetTopForScreenTransition() >= (nextScreenPuzzleY * SpriteData::LEVEL_SPRITE_HEIGHT) - CAMERA_VERTICAL_SHIFT)
			{
				TargetCameraY = nextScreenPuzzleY;
			}
			else
			{
				int screenPuzzleX = CameraX & 0xFFF0; // i.e. (CameraX / NB_HORIZONTAL_SPRITE_PER_SCREEN) * NB_HORIZONTAL_SPRITE_PER_SCREEN
				if (Rick::GetRightForScreenTransition() <= (screenPuzzleX * SpriteData::LEVEL_SPRITE_WIDTH))
				{
					TargetCameraX = screenPuzzleX - NB_HORIZONTAL_SPRITE_PER_SCREEN;
				}
				else
				{
					int nextScreenPuzzleX = screenPuzzleX + NB_HORIZONTAL_SPRITE_PER_SCREEN;
					if (Rick::GetLeftForScreenTransition() >= (nextScreenPuzzleX * SpriteData::LEVEL_SPRITE_WIDTH))
					{
						TargetCameraX = nextScreenPuzzleX;
					}
				}
			}
		}
	}
	
	// Now check if the target is different from the current position of the camera
	int xDiff = TargetCameraX - CameraX;
	if (xDiff > 0)
	{
		CameraTransitionX += GetCameraSpeed(xDiff, CameraTransitionX);
		StartDrawSpriteX = 0;
		EndDrawSpriteX = 1;
		if (CameraTransitionX >= SpriteData::LEVEL_SPRITE_WIDTH)
		{
			CameraTransitionX -= SpriteData::LEVEL_SPRITE_WIDTH;
			CameraX++;
		}
	}
	else if (xDiff < 0)
	{
		CameraTransitionX -= GetCameraSpeed(-xDiff, -CameraTransitionX);
		StartDrawSpriteX = -1;
		EndDrawSpriteX = 0;
		if (CameraTransitionX <= -SpriteData::LEVEL_SPRITE_WIDTH)
		{
			CameraTransitionX += SpriteData::LEVEL_SPRITE_WIDTH;
			CameraX--;
		}
	}
	else
	{
		StartDrawSpriteX = 0;
		EndDrawSpriteX = 0;
	}
	
	int yDiff = TargetCameraY - CameraY;
	if (yDiff > 0)
	{
		CameraTransitionY += GetCameraSpeed(yDiff, CameraTransitionY);
		StartDrawSpriteY = 0;
		if (CameraTransitionY >= SpriteData::LEVEL_SPRITE_HEIGHT)
		{
			CameraTransitionY -= SpriteData::LEVEL_SPRITE_HEIGHT;
			CameraY++;
		}
	}
	else if (yDiff < 0)
	{
		CameraTransitionY -= GetCameraSpeed(-yDiff, -CameraTransitionY);
		StartDrawSpriteY = -1;
		if (CameraTransitionY <= -SpriteData::LEVEL_SPRITE_HEIGHT)
		{
			CameraTransitionY += SpriteData::LEVEL_SPRITE_HEIGHT;
			CameraY--;
		}
	}
	else
	{
		StartDrawSpriteY = 0;
	}
}

/**
 * This function draw the map based on the current position of the camera.
 */
void MapManager::Draw(unsigned char minSpriteIndex, unsigned char maxSpriteIndex, unsigned char rickFeetOnScreen)
{
	for (int y = StartDrawSpriteY; y < NB_VERTICAL_SPRITE_PER_SCREEN; ++y)
	{
		// compute the sprite y coordinate
		int spriteY = (SpriteData::LEVEL_SPRITE_HEIGHT * y) + CAMERA_VERTICAL_SHIFT - CameraTransitionY;
		// determines if we need to draw the platforms.
		// If we are not specifically drawing the platforms (the min sprite index is not platforms),
		// then we should only draw the platforms below the feet
		// Otherwise, if we are in the drawing platform step, we only draw those above the feet,
		// since the below ones as already been drawn
		bool shouldDrawPlatforms = ((minSpriteIndex == SpriteData::BLOCK_8_8) && (spriteY > rickFeetOnScreen)) ||
									((minSpriteIndex == SpriteData::PLATFORM) && (spriteY <= rickFeetOnScreen));
		for (int x = StartDrawSpriteX; x < NB_HORIZONTAL_SPRITE_PER_SCREEN + EndDrawSpriteX; ++x)
		{
			unsigned char spriteLevelX = x + CameraX;
			unsigned char spriteLevelY = y + CameraY;
			unsigned char spriteId = pgm_read_byte(&(Level[spriteLevelY][spriteLevelX]));
			// special case for the mix of ladder and platform, draw either a platform or a ladder depending on the drawing state
			if (spriteId == SpriteData::PLATFORM_WITH_LADDER)
			{
				if (minSpriteIndex == SpriteData::LADDER)
					spriteId = SpriteData::LADDER;
				else
					spriteId = SpriteData::PLATFORM;
			}

			// check if we need to draw or not the destroyable block (in case they have been destroyed)
			if (((spriteId == SpriteData::DESTROYABLE_BLOCK_LEFT) || (spriteId == SpriteData::DESTROYABLE_BLOCK_RIGHT)) && 
				!IsDestroyableBlockAlive(spriteLevelX, spriteLevelY, spriteId))
				continue;

			// draw the sprite if we need to
			if ((spriteId >= minSpriteIndex) && (spriteId <= maxSpriteIndex) &&
				((spriteId != SpriteData::PLATFORM) || shouldDrawPlatforms))
				arduboy.drawBitmap(SpriteData::LEVEL_SPRITE_WIDTH * x - CameraTransitionX,
					spriteY,
					SpriteData::Walls[spriteId],
					SpriteData::LEVEL_SPRITE_WIDTH, SpriteData::LEVEL_SPRITE_HEIGHT, WHITE);
		}
	}
}
