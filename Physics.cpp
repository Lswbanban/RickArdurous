/*
* This file handle everything related to the physics simulation
*/

#include "Physics.h"

namespace Physics
{
	const char JUMP_AND_FALL_VERTICAL_MOVE[] 		= { 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1 };
	const char JUMP_AND_FALL_VERTICAL_ANIM_SPEED[]	= { 1, 1, 1, 1, 1, 2, 2, 3, 3, 4, 5, 6 };

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
	
	const int MAX_PARABOLIC_PARAMTER = 4;
	const int INVALID_PARABOLIC_TRAJECTORY_ID = 255;
	ParabolicParameter ParabolicParameterBuffer[MAX_PARABOLIC_PARAMTER];
}

unsigned char Physics::StartParabolicTrajectory(int startX, int startY, char velocityX)
{
	// search for a free parameter 
	unsigned char returnId = INVALID_PARABOLIC_TRAJECTORY_ID;
	for (int i = 0; i < MAX_PARABOLIC_PARAMTER; ++i)
		if (ParabolicParameterBuffer[i].StartX == INVALID_PARABOLIC_TRAJECTORY_START_X)
			returnId = i;
	
	// if we found free id, set the values
	if (returnId != INVALID_PARABOLIC_TRAJECTORY_ID)
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
	if (id < MAX_PARABOLIC_PARAMTER)
		ParabolicParameterBuffer[id].StartX = INVALID_PARABOLIC_TRAJECTORY_START_X;
}

void Physics::UpdateParabolicTrajectory(unsigned char id, int &x, int &y)
{
	if (id != INVALID_PARABOLIC_TRAJECTORY_ID)
	{
		// increase the death timer
		unsigned char frameCounter = ParabolicParameterBuffer[id].FrameCounter + 1;
		ParabolicParameterBuffer[id].FrameCounter = frameCounter;
		
		// move the main character according to a projectile trajectory
		x = ParabolicParameterBuffer[id].StartX + (ParabolicParameterBuffer[id].VelocityX * frameCounter) / PARABOLIC_MOVING_SPEED;
		y = ParabolicParameterBuffer[id].StartY + ((PARABOLIC_VELOCITY_Y * frameCounter) + (HALF_GRAVITY * frameCounter * frameCounter)) / PARABOLIC_MOVING_SPEED;
	}
}