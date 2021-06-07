#include "Platform.h"

#include <Windows.h>

#ifdef WIN32

namespace Soul
{
	bool isInitialized = false;
	f64 performanceFrequency; // Divide performance counter by this to get time
	PlatformTime startTime; // Start time as microseconds
	const f64 TO_FREQUENCY = 1000000.0; // Microseconds

	bool PlatformInitialize()
	{
		isInitialized = true;

		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		performanceFrequency = (f64)frequency.QuadPart / TO_FREQUENCY; // We want this in microseconds, not seconds

		startTime = PlatformCurrentTime();

		return true;
	}

	void PlatformWriteToConsole(const char* message, i32 messageLength, i8 color)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);

		WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, messageLength, NULL, NULL);
	}

	void PlatformWriteErrorToConsole(const char* message, i32 messageLength, i8 color)
	{
		HANDLE hConsole = GetStdHandle(STD_ERROR_HANDLE);
		SetConsoleTextAttribute(hConsole, color);

		WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, messageLength, NULL, NULL);
	}

	void* PlatformAllocateMemory(i32 size)
	{
		return malloc(size);
	}

	void PlatformFreeMemory(void* location)
	{
		free(location);
	}

	void PlatformCopyMemory(void* from, void* to, i32 size)
	{
		memcpy(from, to, size);
	}

	void PlatformSetMemory(void* location, i8 value, i32 size)
	{
		memset(location, value, size);
	}

	void PlatformZeroMemory(void* location, i32 size)
	{
		memset(location, 0, size);
	}

	PlatformTime PlatformCurrentTime()
	{
		LARGE_INTEGER performanceCount;
		QueryPerformanceCounter(&performanceCount);

		return (PlatformTime)(performanceCount.QuadPart / performanceFrequency);
	}
}

#endif