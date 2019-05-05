/*
* This file handle everything related to the physics simulation
*/

#include "Physics.h"

namespace Physics
{
	// array for the fall
	const char JUMP_AND_FALL_VERTICAL_MOVE[] 		= { 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1 };
	const char JUMP_AND_FALL_VERTICAL_ANIM_SPEED[]	= { 1, 1, 1, 1, 1, 2, 2, 3, 3, 4, 5, 6 };
	
	const int INVALID_FALL_ANIM_SPEED_INDEX = 255;
	class FallParameter
	{
	public:
		unsigned char FrameCounter = 0;
		unsigned char FallAnimSpeedIndex = INVALID_FALL_ANIM_SPEED_INDEX;
	};
	const int MAX_FALL_PARAMETER = 4;
	FallParameter FallParameterBuffer[MAX_FALL_PARAMETER];

	// values for the parabolic trajectory
	const int PARABOLIC_MOVING_SPEED = 16;
	const int PARABOLIC_VELOCITY_Y = -30;
	const int HALF_GRAVITY = 1;

	const int INVALID_PARABOLIC_TRAJECTORY_START_X = -5000;
	class ParabolicParameter
	{
	public:
		int StartX = INVALID_PARABOLIC_TRAJECTORY_START_X;
		int StartY = 0;
		unsigned char FrameCounter = 0;
		char VelocityX = 0;
	};
	
	const int MAX_PARABOLIC_PARAMETER = 4;
	ParabolicParameter ParabolicParameterBuffer[MAX_PARABOLIC_PARAMETER];
}

unsigned char Physics::StartFall()
{
	// search for a free parameter 
	unsigned char returnId = MAX_FALL_PARAMETER;
	for (int i = 0; i < MAX_FALL_PARAMETER; ++i)
		if (FallParameterBuffer[i].FallAnimSpeedIndex == INVALID_FALL_ANIM_SPEED_INDEX)
			returnId = i;
	
	// if we found free id, set the values
	if (returnId != MAX_FALL_PARAMETER)
	{
		// memorize the data
		FallParameterBuffer[returnId].FrameCounter = 0;
		FallParameterBuffer[returnId].FallAnimSpeedIndex = Physics::JUMP_AND_FALL_VERTICAL_ANIM_SPEED_COUNT - 1;
	}
	
	// return the id found (or not)
	return returnId;
}

void Physics::StopFall(unsigned char id)
{
	if (id < MAX_FALL_PARAMETER)
		FallParameterBuffer[id].FallAnimSpeedIndex = INVALID_FALL_ANIM_SPEED_INDEX;
}

/**
 * Update a simple fall y value, according to the two ref parameters and the physics array of values
 * @param id the id returned by the StarFall function
 * @param y a reference to the y parameter to modify due to the fall
 * @return 0 if the y was not updated, otherwise, the number of time it was updated since the beggining of the fall
 */
unsigned char Physics::UpdateFall(unsigned char id, int &y)
{
	if (id < MAX_FALL_PARAMETER)
	{
		// increase the frame counter
		FallParameterBuffer[id].FrameCounter++;
		// get the current fall anim index
		unsigned char fallAnimSpeedIndex = FallParameterBuffer[id].FallAnimSpeedIndex;
		// check if it is time to move
		if (FallParameterBuffer[id].FrameCounter >= Physics::JUMP_AND_FALL_VERTICAL_ANIM_SPEED[fallAnimSpeedIndex])
		{
			// reset the frame counter
			FallParameterBuffer[id].FrameCounter = 0;
			// in fall state, move down
			y += Physics::JUMP_AND_FALL_VERTICAL_MOVE[fallAnimSpeedIndex];
			// decrease the fall counter
			if (fallAnimSpeedIndex > Physics::FALL_VERTICAL_MIN_INDEX)
				FallParameterBuffer[id].FallAnimSpeedIndex--;
			return (Physics::JUMP_AND_FALL_VERTICAL_ANIM_SPEED_COUNT - 1) - FallParameterBuffer[id].FallAnimSpeedIndex;
		}
	}
	return 0;
}

unsigned char Physics::GetCurrentFallSpeed(unsigned char id)
{
	if (id < MAX_FALL_PARAMETER)
		return Physics::JUMP_AND_FALL_VERTICAL_MOVE[FallParameterBuffer[id].FallAnimSpeedIndex];
	return 0;
}

void Physics::LimitFallSpeed(unsigned char id, unsigned char maxSpeed)
{
	if ((id < MAX_FALL_PARAMETER) && (maxSpeed > 0))
	{
		unsigned char fallAnimSpeedIndex = FallParameterBuffer[id].FallAnimSpeedIndex;
		while (Physics::JUMP_AND_FALL_VERTICAL_MOVE[fallAnimSpeedIndex] > maxSpeed )
			fallAnimSpeedIndex++;
		FallParameterBuffer[id].FallAnimSpeedIndex = fallAnimSpeedIndex;
	}
}

unsigned char Physics::StartParabolicTrajectory(int startX, int startY, char velocityX)
{
	// search for a free parameter 
	unsigned char returnId = MAX_PARABOLIC_PARAMETER;
	for (int i = 0; i < MAX_PARABOLIC_PARAMETER; ++i)
		if (ParabolicParameterBuffer[i].StartX == INVALID_PARABOLIC_TRAJECTORY_START_X)
			returnId = i;
	
	// if we found free id, set the values
	if (returnId != MAX_PARABOLIC_PARAMETER)
	{
		// memorize the data
		ParabolicParameterBuffer[returnId].StartX = startX;
		ParabolicParameterBuffer[returnId].StartY = startY;
		ParabolicParameterBuffer[returnId].FrameCounter = 0;
		ParabolicParameterBuffer[returnId].VelocityX = velocityX;
	}
	
	// return the id found (or not)
	return returnId;
}

void Physics::StopParabolicTrajectory(unsigned char id)
{
	if (id < MAX_PARABOLIC_PARAMETER)
		ParabolicParameterBuffer[id].StartX = INVALID_PARABOLIC_TRAJECTORY_START_X;
}

void Physics::UpdateParabolicTrajectory(unsigned char id, int &x, int &y)
{
	if (id < MAX_PARABOLIC_PARAMETER)
	{
		// increase the death timer
		unsigned char frameCounter = ParabolicParameterBuffer[id].FrameCounter + 1;
		ParabolicParameterBuffer[id].FrameCounter = frameCounter;
		
		// move the main character according to a projectile trajectory
		x = ParabolicParameterBuffer[id].StartX + (ParabolicParameterBuffer[id].VelocityX * frameCounter) / PARABOLIC_MOVING_SPEED;
		y = ParabolicParameterBuffer[id].StartY + ((PARABOLIC_VELOCITY_Y * frameCounter) + (HALF_GRAVITY * frameCounter * frameCounter)) / PARABOLIC_MOVING_SPEED;
	}
}
