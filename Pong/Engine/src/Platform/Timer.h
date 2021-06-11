#pragma once

#include <Defines.h>

namespace Soul
{
	/*
	Used to keep track of an elapsed amount of time - useful for profiling code.

	The timer only starts with Start() is called, and can be stopped with Stop(). At any time,
	whether the timer is running or not, GetElapsedMilliseconds() can be called to get the current number
	of elapsed milliseconds.
	*/
	class Timer
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
		Returns the length of time this timer has been running in (floating point) milliseconds
		and resets the counter to 0.
		*/
		f32 GetDeltaTime();

		/*
		Returns the length of time this timer has been running in milliseconds.
		*/
		i64 GetElapsedMilliseconds();

		/*
		Returns the length of time this timer has been running in microseconds.
		*/
		i64 GetElapsedMicroseconds();

	private:
		i64 m_ElapsedPerformanceCounts;
		i64 m_LastCounterCheckpoint;
		bool m_IsRunning;
	};
}