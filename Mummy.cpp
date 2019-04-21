/*
 * Implement the logic and drawing of the mummy ennemies
*/

#include "RickArdurous.h"
#include "Mummy.h"
#include "SpriteData.h"
#include "Rick.h"
#include "MapManager.h"

const char WALK_ANIM_SPEED[] = { 8, 12, 6, 8 };

Mummy::Mummy(int startX, int startY) : Item(startX, startY, Item::PropertyFlags::ENEMIES | Item::PropertyFlags::STATIC_COLLISION_NEEDED)
{
	AnimFrameId = 0;
	AnimFrameCount = 0;
	SetProperty(PropertyFlags::MIRROR_X);
};

bool Mummy::Update(UpdateStep step)
{
	switch (step)
	{
		case Item::UpdateStep::DRAW_ENEMIES:
		{
			switch (AnimState)
			{
				case State::WALK:
					UpdateWalk();
					break;
				case State::HALF_TURN:
					UpdateHalfTurn();
					break;
				case State::FALL:
					UpdateFall();
					break;
			}
			
			// draw the statuette and check the collision with eventual lethal stuff
			int collision = Draw(WHITE);
									
			// if we have a collision, that means we hit a lethal pixel
			if (collision != 0)
			{
				ClearProperty(Item::PropertyFlags::ALIVE);
				MapManager::RemoveItem(this);
				return true;
			}
			break;
		}
		case Item::UpdateStep::CHECK_STATIC_COLLISION:
		{
			// check the ground collision
			int yUnderFeet = Y + 13;
			if (!MapManager::IsThereAnyHorizontalCollisionAt(X+1, X+7, yUnderFeet))
			{
				AnimState = State::FALL;
			}
			else
			{
				// there is ground, check if I was falling
				if (AnimState == State::FALL)
				{
					InitWalk();
				}
				else
				{
					// compute the world coordinate of the map level block to test
					bool isWalkingLeft = IsPropertySet(PropertyFlags::MIRROR_X);
					int wallX = isWalkingLeft ? X - WALL_COLLISION_DETECTION_DISTANCE : X + SpriteData::MUMMY_SPRITE_WIDTH + WALL_COLLISION_DETECTION_DISTANCE;
					if (MapManager::IsThereStaticCollisionAt(wallX, Y) || 
						MapManager::IsThereStaticCollisionAt(wallX, Y + SpriteData::LEVEL_SPRITE_HEIGHT) ||
						!MapManager::IsThereStaticCollisionAt(wallX, Y + (SpriteData::LEVEL_SPRITE_HEIGHT << 1)))
					{
						// reverse the walking direction imediately for the next frame to test the collision at the right place
						if (isWalkingLeft)
							ClearProperty(PropertyFlags::MIRROR_X);
						else
							SetProperty(PropertyFlags::MIRROR_X);
						// init the half turn state
						AnimState = State::HALF_TURN;
						AnimFrameId = SpriteData::MummyAnimFrameId::MUMMY_HALF_TURN;
						AnimFrameCount = 0;
					}
				}
			}
			break;
		}
	}
	return false;
}

void Mummy::InitWalk()
{
	AnimState = State::WALK;
	AnimFrameId = SpriteData::MummyAnimFrameId::MUMMY_WALK_START;
	AnimFrameCount = 0;
}

void Mummy::UpdateWalk()
{
	// update the animation
	AnimFrameCount++;
	if (AnimFrameCount == WALK_ANIM_SPEED[AnimFrameId])
	{
		// move the X depending on the direction
		if (IsPropertySet(PropertyFlags::MIRROR_X))
			X--;
		else
			X++;
		// go to the next frame id
		AnimFrameId++;
		AnimFrameCount = 0;
		if (AnimFrameId == SpriteData::MummyAnimFrameId::MUMMY_WALK_END)
			AnimFrameId = SpriteData::MummyAnimFrameId::MUMMY_WALK_START;
	}
}

void Mummy::UpdateHalfTurn()
{
	// update the animation
	AnimFrameCount++;
	if (AnimFrameCount == HALF_TURN_ANIM_SPEED)
		InitWalk();
}

void Mummy::UpdateFall()
{
	Y++;
}

int Mummy::Draw(unsigned char color)
{
	return arduboy.drawBitmapExtended(MapManager::GetXOnScreen(X),
									MapManager::GetYOnScreen(Y),
									SpriteData::Mummy[AnimFrameId],
									SpriteData::MUMMY_SPRITE_WIDTH, SpriteData::MUMMY_SPRITE_HEIGHT,
									color, IsPropertySet(PropertyFlags::MIRROR_X));
}