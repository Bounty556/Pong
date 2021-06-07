#include "Timer.h"

namespace Soul
{
	Timer::Timer() :
		m_IsRunning(false),
		m_RecordedTime(0.0f),
		m_LastCheckpoint(0.0f)
	{

	}

	void Timer::Start()
	{
		if (!m_IsRunning)
		{
			m_IsRunning = true;

			m_LastCheckpoint = PlatformCurrentTime();
		}
	}

	void Timer::Stop()
	{
		if (m_IsRunning)
		{
			m_IsRunning = false;

			m_RecordedTime += PlatformCurrentTime() - m_LastCheckpoint;
		}
	}

	void Timer::Reset()
	{
		m_LastCheckpoint = PlatformCurrentTime();
		m_RecordedTime = 0;
	}

	PlatformTime Timer::GetDeltaTime()
	{
		if (m_IsRunning)
		{
			m_RecordedTime += PlatformCurrentTime() - m_LastCheckpoint;
		}

		f32 elapsedTime = m_RecordedTime;

		Reset();

		return elapsedTime / 1000.0f;
	}

	PlatformTime Timer::GetElapsedMilliseconds()
	{
		if (m_IsRunning)
		{
			m_RecordedTime += PlatformCurrentTime() - m_LastCheckpoint;
		}

		return m_RecordedTime / 1000.0f;
	}
}