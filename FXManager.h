#ifndef _FX_MANAGER_H_
#define _FX_MANAGER_H_

namespace FXManager
{
	struct FXCommand
	{
		unsigned int Red			:1;
		unsigned int Green			:1;
		unsigned int Blue			:1;
		unsigned int OnDuration		:6;
		unsigned int OffDuration	:7;
		unsigned char BaseNote;		
		char NoteIncrement			:4; // increment can be negative
		unsigned char RepeatTime	:4;
	};

	enum BufferId
	{
		GAME = 0,
		RICK,
		BUFFER_COUNT,
	};

	// a variable to turn on/off the sound FX
	extern bool IsSoundOn;
	
	// set the command in the specified buffer
	void StartFXCommand(BufferId id, FXCommand command);

	// clear the specified buffer and stop the LED and sound. If id equals BUFFER_COUNT, this will clear all the buffers.
	void ClearFXCommand(BufferId id);

	// update that should be called every frame
	void Update();
}

#endif