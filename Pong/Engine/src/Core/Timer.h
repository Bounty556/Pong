#pragma once

#include <Defines.h>
#include <Platform/Platform.h>

namespace Soul
{
	/*
	Used to keep track of an elapsed amount of time - useful for profiling
	code.

	The timer only starts with Start() is called, and can be stopped with
	Stop(). At any time, whether the timer is running or not, 
	GetElapsedMilliseconds() can be called to get the current number
	of elapsed milliseconds, or GetDeltaTime() can be called to get the current
	number of elapsed milliseconds as well as reset the timer to 0 and keep it
	running (useful for game loops)!
	*/
	class SOULAPI Timer
	{
	public:
		Timer();

		/*
		Starts the timer.
		*/
		void Start();

		/*
		Stops the timer.
		*/
		void Stop();

		/*
		Sets the current accumulated performance counts to 0.
		*/
		void Reset();

		/*
		Returns the length of time this timer has been running in (floating 
		point) milliseconds and resets the timer to 0.
		*/
		PlatformTime GetDeltaTime();

		/*
		Returns the length of time this timer has been running in milliseconds.
		*/
		PlatformTime GetElapsedMilliseconds();

	private:
		bool m_IsRunning;
		PlatformTime m_RecordedTime; // Actual time in milliseconds
		PlatformTime m_LastCheckpoint; // Updated everytime we start, stop, or get current time
	};
}