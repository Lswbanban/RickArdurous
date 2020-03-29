#ifndef _PHYSICS_H_
#define _PHYSICS_H_

namespace Physics
{
	extern const char JUMP_AND_FALL_VERTICAL_MOVE[];
	extern const char JUMP_AND_FALL_VERTICAL_ANIM_SPEED[];
	static constexpr int JUMP_AND_FALL_VERTICAL_ANIM_SPEED_COUNT = 12;
	static constexpr int FALL_VERTICAL_MIN_INDEX = 3; // this variable is used to limite the falling speed on a very long fall
	static constexpr int INVALID_FALL_ID = 4;
	static constexpr int INVALID_PARABOLIC_ID = 4;

	// init
	void ResetAll();
	
	// function for the fall
	unsigned char StartFall();
	unsigned char UpdateFall(unsigned char id, int &y);
	void StopFall(unsigned char id);
	unsigned char GetCurrentFallSpeed(unsigned char id);
	void LimitFallSpeed(unsigned char id, unsigned char maxSpeed);

	// function for parabolic trajectories
	unsigned char StartParabolicTrajectory(int startX, int startY, char velocityX);
	void StopParabolicTrajectory(unsigned char id);
	void UpdateParabolicTrajectory(unsigned char id, int &x, int &y);
}
#endif