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
#include "Physics.h"

namespace MapManager
{
	// the vertical shift value in pixel that should be aplied to the camera when drawing the level
	const int CAMERA_VERTICAL_SHIFT = 6;
	const int NB_HORIZONTAL_SPRITE_PER_SCREEN = 16;
	const int NB_VERTICAL_SPRITE_PER_SCREEN = 8;
	const int SHUTTER_SPEED = 5;
	
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
	static const unsigned int MAX_UPDATABLE_ITEM_COUNT = 20;
	Item * ItemsToUpdate[MAX_UPDATABLE_ITEM_COUNT];
	unsigned char ItemsToUpdateCount = 0;
	
	// variable for managing puzzle screen
	// the id of the puzzle screen where the last checkpoint is
	unsigned char LastCheckPointPuzzleScreenId = 0;
	// the id of the puzzle screen currently player by the player
	unsigned char CurrentPuzzleScreenId = 0;
	// the id of the farest puzzle screen reached by the player
	unsigned char FarestPuzzleScreenIdReached = 0;
	// a variable to indicate in which direction the player goes when traversing the puzzle screens
	char PuzzleScreenMoveDirection = 1;
	// coordinates of the edge between the current puzzle screen and the previous screen
	int LastPuzzleScreenEdgeCoordX = 0;
	int LastPuzzleScreenEdgeCoordY = 0;
	int LastCheckPointPuzzleScreenEdgeCoordX = 0;
	int LastCheckPointPuzzleScreenEdgeCoordY = 0;
	bool WasLastTransitionHorizontal = false;
	bool WasLastCheckPointLastTransitionHorizontal = false;
	
	// variable use the draw the Shutter animation after a Respawn
	char ShutterHeight = 0;
	char ShutterDirection = 1;
	
	// debug draw state
	unsigned char DebugDrawStep = 255;
	
	void RemoveItem(int index);
	void RemoveAllItemsOutsideOfTheScreen();
	void UpdateItems(Item::UpdateStep updateStep);
	void TeleportAndRespawnToLastCheckpoint();
	void AnimateCameraTransition();
	void AnimateShutterTransition();
	void BeginSwitchPuzzleScreen(int newTargetCameraX, int newTargetCameraY);
	void EndSwitchPuzzleScreen();
	int GetCameraSpeed(int step, int subStep);
	void Draw(unsigned char minSpriteIndex, unsigned char maxSpriteIndex, unsigned char rickFeetOnScreen);
	unsigned char GetLevelSpriteAtWorldCoordinate(int xWorld, int yWorld);
	unsigned char GetLevelSpriteAt(unsigned char xMap, unsigned char yMap);
	bool IsDestroyableBlockAlive(unsigned char xMap, unsigned char yMap);
}

void MapManager::AddItem(Item * item)
{
	if (ItemsToUpdateCount < MAX_UPDATABLE_ITEM_COUNT)
	{
		// search if the item is not already inside the array
		for (int i = 0; i < ItemsToUpdateCount; ++i)
			if (ItemsToUpdate[i] == item)
				return;
		// add the item to the last position of the array
		ItemsToUpdate[ItemsToUpdateCount++] = item;
	}
	
	//Serial.print("Item Added, Count:");
	//Serial.println(ItemsToUpdateCount);
}

void MapManager::RemoveItem(int index)
{
	// decrease the item count
	ItemsToUpdateCount--;
	// if the array is not empty, move the last item to the empty place
	ItemsToUpdate[index] = ItemsToUpdate[ItemsToUpdateCount];
	
	//Serial.print("Item Removed, Count:");
	//Serial.println(ItemsToUpdateCount);
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

void MapManager::RemoveAllItemsOutsideOfTheScreen()
{
	// remove items outside of the screen
	for (int i = 0; i < ItemsToUpdateCount; i++)
	{
		Item * currentItem = ItemsToUpdate[i];
		if (!IsOnScreen(currentItem->GetX(), currentItem->GetY(), 8, 8))
		{
			RemoveItem(i);
			i--;
		}
	}
}

void MapManager::CallMeBackForEachTrapTriggerer(Item* caller, ItemCallback callback)
{
	for (int i = 0; i < ItemsToUpdateCount; i++)
		if (ItemsToUpdate[i]->IsPropertySet(Item::PropertyFlags::TRAP_TRIGERER))
			(*callback)(caller, ItemsToUpdate[i]);
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

void MapManager::Update()
{
	// debug code
	if (Input::IsDown(B_BUTTON) && Input::IsJustPressed(UP_BUTTON))
		DebugDrawStep++;
	if (Input::IsDown(B_BUTTON) && Input::IsJustPressed(DOWN_BUTTON))
		DebugDrawStep--;
	
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
	Draw(SpriteData::BLOCK_16_8_RIGHT, SpriteData::PLATFORM, rickFeetOnScreen);

	// Draw static collision items
	MapManager::UpdateItems(Item::UpdateStep::DRAW_STATIC_COLLISION);

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
	
	// animate the shutter transition (at the beginning of the game, or after a checkpoint respawn)
	AnimateShutterTransition();
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
	unsigned char spriteId = GetLevelSpriteAtWorldCoordinate(xWorld, yWorld);
	// if the sprite is a destroyable block, check if it is destroyed
	if (spriteId == SpriteData::DESTROYABLE_BLOCK)
		return IsDestroyableBlockAlive(xWorld / SpriteData::LEVEL_SPRITE_WIDTH, yWorld / SpriteData::LEVEL_SPRITE_HEIGHT);
	// otherwise it depends on the type of sprite
	return (spriteId < SpriteData::WallId::LADDER) || ((spriteId > SpriteData::WallId::PLATFORM_WITH_LADDER) && (spriteId != SpriteData::NOTHING));
}

bool MapManager::IsThereLadderAt(int xWorld, int yWorld)
{
	unsigned char spriteId = GetLevelSpriteAtWorldCoordinate(xWorld, yWorld);
	return (spriteId == SpriteData::WallId::LADDER) || (spriteId == SpriteData::WallId::PLATFORM_WITH_LADDER);
}

unsigned char MapManager::GetLevelSpriteAtWorldCoordinate(int xWorld, int yWorld)
{
	// convert the world coordinate into index for the sprite map
	int xMap = xWorld / SpriteData::LEVEL_SPRITE_WIDTH;
	int yMap = yWorld / SpriteData::LEVEL_SPRITE_HEIGHT;
	// check if we are inside the map. If not, consider that there is collision
	// to avoid the main character to exit the map and navigate into random memory
	if ((xMap < 0) || (xMap >= MapManager::LEVEL_SIZE_X) || (yMap < 0) || (yMap >= MapManager::LEVEL_SIZE_Y))
		return SpriteData::BLOCK_16_8_RIGHT;
	// call the function to get the sprite inside the map
	return GetLevelSpriteAt(xMap, yMap);
}

unsigned char MapManager::GetLevelSpriteAt(unsigned char xMap, unsigned char yMap)
{
	// compute start and end index in the array of sprite ids
	int startLineIndex = pgm_read_byte(&(LevelLineIndex[yMap]));
	int endLineIndex = pgm_read_byte(&(LevelLineIndex[yMap + 1]));
	
	// get the index of the sprite in the one dimentionnal array
	int targetSpriteIndex = xMap + 1;
	// iterate through the array to find the correct index
	int spriteIndex = 0;
	bool readNothingCount = false;
	for (int i = startLineIndex; i < endLineIndex; ++i)
	{
		unsigned char packedId = pgm_read_byte(&(Level[i]));
		unsigned char id1 = packedId >> 4;
		unsigned char id2 = packedId & 0x0F;
		// check the first id
		if (readNothingCount)
		{
			spriteIndex += id1;
			readNothingCount = false;
			if (spriteIndex >= targetSpriteIndex)
				return SpriteData::NOTHING;
		}
		else if (id1 == SpriteData::NOTHING)
			readNothingCount = true;
		else
		{
			spriteIndex++;
			if (spriteIndex == targetSpriteIndex)
				return id1;
		}
		
		// check the second id
		if (readNothingCount)
		{
			spriteIndex += id2;
			readNothingCount = false;
			if (spriteIndex >= targetSpriteIndex)
				return SpriteData::NOTHING;
		}
		else if (id2 == SpriteData::NOTHING)
			readNothingCount = true;
		else
		{
			spriteIndex++;
			if (spriteIndex == targetSpriteIndex)
				return id2;
		}
	}
	
	// by default return a collision
	return SpriteData::BLOCK_16_8_RIGHT;
}

bool MapManager::IsDestroyableBlockAlive(unsigned char xMap, unsigned char yMap)
{
	for (int i = 0; i < ItemsToUpdateCount; i++)
		if (ItemsToUpdate[i]->IsPropertySet(Item::PropertyFlags::DESTROYABLE_BLOCK))
		{
			DestroyableBlock * block = (DestroyableBlock*)ItemsToUpdate[i];
			if (block->IsLocatedAt(xMap, yMap))
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
 * Init the current puzzle screen id, by adding all the items of this screen into the array of items to update.
 * This function will call the pointer on the specific Init function for the correct screen.
 * You can specify if you want the items to be initialized or not. If the player goes back in previous screen, you
 * don't want to respawn all the items, just add them to the list to update.
 * @param shouldInitItem if true all the items in the current screen will be initialized (so respwaned)
 */
void MapManager::Init(bool shouldInitItem)
{
	if ((CurrentPuzzleScreenId >= 0) && (CurrentPuzzleScreenId < PUZZLE_SCREEN_COUNT))
		(*MapManager::ItemInitFunctions[CurrentPuzzleScreenId])(shouldInitItem);
}

/**
 * This function is called from the Map Data init functions, to indicated that the current screen initialized
 * should become the new checkpoint. This function specifies the coordinates of where Rick should respawn if he dies.
 * @param rickX the X location where Rick should respawn in world coordinate
 * @param rickY the Y location where Rick should respawn in world coordinate
 */
void MapManager::MemorizeCheckPoint(int rickX, int rickY)
{
	// check if we reach a NEW checkpoint (farer than the last one memorized)
	if (CurrentPuzzleScreenId > LastCheckPointPuzzleScreenId)
	{
		// memorize the current screen id
		LastCheckPointPuzzleScreenId = CurrentPuzzleScreenId;
		// memorize also the edge transition from the previous screen
		LastCheckPointPuzzleScreenEdgeCoordX = LastPuzzleScreenEdgeCoordX;
		LastCheckPointPuzzleScreenEdgeCoordY = LastPuzzleScreenEdgeCoordY;
		WasLastCheckPointLastTransitionHorizontal = WasLastTransitionHorizontal;
	}
	//Serial.print("memo checkpoint:");
	//Serial.println(CurrentPuzzleScreenId);
	//Serial.print("last checkpoint:");
	//Serial.println(LastCheckPointPuzzleScreenId);
	//Serial.print("last edge coord:");
	//Serial.println(LastCheckPointPuzzleScreenEdgeCoord);
	//Serial.print("last edge horiz:");
	//Serial.println(IsLastCheckPointPuzzleScreenEdgeHorisontal);
	
	// respawn the player at the correct location
	Rick::CheckPointRespawn(rickX, rickY);
}

/**
 * This function is called when the player as finished his death animation, and that the game should restart
 * from the last checkpoint. This function will teleport the camera to skip the transition, and will call
 * a Init with full initialization to respawn the dead enemies
 */
void MapManager::RestartToLastCheckpoint()
{
	// start the shutter animation by giving a non zero value
	ShutterHeight = SHUTTER_SPEED;
	ShutterDirection = SHUTTER_SPEED;
}

void MapManager::TeleportAndRespawnToLastCheckpoint()
{
	//Serial.print("Restart to screen id:");
	//Serial.println(LastCheckPointPuzzleScreenId);
	
	// set the current puzzle id to the last checkpoint puzzle id
	CurrentPuzzleScreenId = LastCheckPointPuzzleScreenId;
	FarestPuzzleScreenIdReached = LastCheckPointPuzzleScreenId;
	PuzzleScreenMoveDirection = 1;
	
	// reset the edge transition to the previous screen before last checkpoint
	LastPuzzleScreenEdgeCoordX = LastCheckPointPuzzleScreenEdgeCoordX;
	LastPuzzleScreenEdgeCoordY = LastCheckPointPuzzleScreenEdgeCoordY;
	WasLastTransitionHorizontal = WasLastCheckPointLastTransitionHorizontal;

	// teleport the camera to avoid a transition when restarting to last checkpoint
	TargetCameraX = LastCheckPointPuzzleScreenEdgeCoordX;
	TargetCameraY = LastCheckPointPuzzleScreenEdgeCoordY;
	CameraX = LastCheckPointPuzzleScreenEdgeCoordX;
	CameraY = LastCheckPointPuzzleScreenEdgeCoordY;

	// remove all the items, by clearing the whole array
	ItemsToUpdateCount = 0;
	
	// reset all the physics
	Physics::ResetAll();
	
	// call the init
	Init(true);
}

void MapManager::AnimateShutterTransition()
{
	if (ShutterHeight > 0)
	{
		// draw the two shutter parts
		arduboy.fillRect(0, 0, WIDTH, ShutterHeight, BLACK);
		arduboy.fillRect(0, HEIGHT - ShutterHeight, WIDTH, ShutterHeight, BLACK);
		
		// increase the shutter height
		ShutterHeight += ShutterDirection;
		
		// check if the shutter is closed
		if (ShutterHeight >= (HEIGHT / 2))
		{
			// if the shutter is closed, call the teleport
			TeleportAndRespawnToLastCheckpoint();
			// reverse the shutter direction to reopen it
			ShutterDirection = -SHUTTER_SPEED;
		}
	}
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

void MapManager::BeginSwitchPuzzleScreen(int newTargetCameraX, int newTargetCameraY)
{
	bool isHorizontalTransition = (newTargetCameraX != TargetCameraX);
	bool isVerticalTransition = (newTargetCameraY != TargetCameraY);
	if (isHorizontalTransition || isVerticalTransition)
	{
		// get the edge of the transition (which is the max of the two target camera)
		int newEdgeCoordX = (newTargetCameraX > TargetCameraX) ? newTargetCameraX : TargetCameraX;
		int newEdgeCoordY = (newTargetCameraY > TargetCameraY) ? newTargetCameraY : TargetCameraY;
		
		// if Rick just crossed the same edge as before, he is returning back
		bool isRickReturning = (WasLastTransitionHorizontal == isHorizontalTransition) && 
								(LastPuzzleScreenEdgeCoordX == newEdgeCoordX) &&
								(LastPuzzleScreenEdgeCoordY == newEdgeCoordY);

		// memorise the new edge coordinates
		LastPuzzleScreenEdgeCoordX = newEdgeCoordX;
		LastPuzzleScreenEdgeCoordY = newEdgeCoordY;
		WasLastTransitionHorizontal = isHorizontalTransition;
		
		// set the new target camera
		TargetCameraX = newTargetCameraX;
		TargetCameraY = newTargetCameraY;

		// if the player return to the previous screen, inverse the direction
		if (isRickReturning)
			PuzzleScreenMoveDirection = -PuzzleScreenMoveDirection;
		
		// increase the puzzle screen according to the direction
		CurrentPuzzleScreenId += PuzzleScreenMoveDirection;
		
		// check if the player reach a new puzzle, and if yes, memorize it
		bool isRickReachedANewPuzzle = CurrentPuzzleScreenId > FarestPuzzleScreenIdReached;
		if (isRickReachedANewPuzzle)
			FarestPuzzleScreenIdReached = CurrentPuzzleScreenId;
		
		//Serial.println("---------------------");
		//Serial.print("Switch to screen id:");
		//Serial.println(CurrentPuzzleScreenId);
		//Serial.print("Current screen dir:");
		//Serial.println((int)PuzzleScreenMoveDirection);

		// init the items of the new puzzle screen
		Init(isRickReachedANewPuzzle);
	}
}

void MapManager::EndSwitchPuzzleScreen()
{
	RemoveAllItemsOutsideOfTheScreen();
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
			BeginSwitchPuzzleScreen(TargetCameraX, screenPuzzleY - NB_VERTICAL_SPRITE_PER_SCREEN);
		}
		else
		{
			int nextScreenPuzzleY = screenPuzzleY + NB_VERTICAL_SPRITE_PER_SCREEN;
			if (Rick::GetTopForScreenTransition() >= (nextScreenPuzzleY * SpriteData::LEVEL_SPRITE_HEIGHT) - CAMERA_VERTICAL_SHIFT)
			{
				BeginSwitchPuzzleScreen(TargetCameraX, nextScreenPuzzleY);
			}
			else
			{
				int screenPuzzleX = CameraX & 0xFFF0; // i.e. (CameraX / NB_HORIZONTAL_SPRITE_PER_SCREEN) * NB_HORIZONTAL_SPRITE_PER_SCREEN
				if (Rick::GetRightForScreenTransition() <= (screenPuzzleX * SpriteData::LEVEL_SPRITE_WIDTH))
				{
					BeginSwitchPuzzleScreen(screenPuzzleX - NB_HORIZONTAL_SPRITE_PER_SCREEN, TargetCameraY);
				}
				else
				{
					int nextScreenPuzzleX = screenPuzzleX + NB_HORIZONTAL_SPRITE_PER_SCREEN;
					if (Rick::GetLeftForScreenTransition() >= (nextScreenPuzzleX * SpriteData::LEVEL_SPRITE_WIDTH))
					{
						BeginSwitchPuzzleScreen(nextScreenPuzzleX, TargetCameraY);
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
			// check if we reach the end of the transition
			if (TargetCameraX == CameraX)
				EndSwitchPuzzleScreen();
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
			// check if we reach the end of the transition
			if (TargetCameraX == CameraX)
				EndSwitchPuzzleScreen();
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
			// check if we reach the end of the transition
			if (TargetCameraY == CameraY)
				EndSwitchPuzzleScreen();
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
			// check if we reach the end of the transition
			if (TargetCameraY == CameraY)
				EndSwitchPuzzleScreen();
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
		bool shouldDrawPlatforms = ((minSpriteIndex == SpriteData::BLOCK_16_8_RIGHT) && (spriteY > rickFeetOnScreen)) ||
									((minSpriteIndex == SpriteData::PLATFORM) && (spriteY <= rickFeetOnScreen));
		for (int x = StartDrawSpriteX; x < NB_HORIZONTAL_SPRITE_PER_SCREEN + EndDrawSpriteX; ++x)
		{
			unsigned char spriteLevelX = x + CameraX;
			unsigned char spriteLevelY = y + CameraY;
			unsigned char spriteId = GetLevelSpriteAt(spriteLevelX, spriteLevelY);
			// special case for the mix of ladder and platform, draw either a platform or a ladder depending on the drawing state
			if (spriteId == SpriteData::PLATFORM_WITH_LADDER)
			{
				if (minSpriteIndex == SpriteData::LADDER)
					spriteId = SpriteData::LADDER;
				else
					spriteId = SpriteData::PLATFORM;
			}

			// draw the sprite if we need to
			if ((spriteId >= minSpriteIndex) && (spriteId <= maxSpriteIndex) &&
				((spriteId != SpriteData::PLATFORM) || shouldDrawPlatforms))
			{
				// choose a random mirror flag for some sprite that can be mirrored, for display variation
				// and for the big statue, they are mirror if they are the right one (i.e. if there is the same sprite on their left)
				bool isMirror = false;
				if (spriteId <= SpriteData::ROCK_GROUND)
					isMirror = (spriteLevelX * spriteLevelY) % 2;
				else if (spriteId == SpriteData::STAIR)
					isMirror = (GetLevelSpriteAt(spriteLevelX - 1, spriteLevelY) == SpriteData::NOTHING);
				else if ((spriteId == SpriteData::BIG_STATUE_TOP) || (spriteId == SpriteData::BIG_STATUE_BOTTOM))
					isMirror = (GetLevelSpriteAt(spriteLevelX - 1, spriteLevelY) == spriteId);

				// call the draw function
				arduboy.drawBitmapExtended(SpriteData::LEVEL_SPRITE_WIDTH * x - CameraTransitionX,
					spriteY,
					SpriteData::Walls[spriteId],
					SpriteData::LEVEL_SPRITE_WIDTH, SpriteData::LEVEL_SPRITE_HEIGHT, WHITE, isMirror);
			}
		}
	}
}
