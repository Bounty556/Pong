#include "Platform.h"

#ifdef WIN32

#include <Windows.h>

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

	void PlatformWriteToConsole(const char* message, u32 messageLength, i8 color)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);

		WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, messageLength, NULL, NULL);
	}

	void PlatformWriteErrorToConsole(const char* message, u32 messageLength, i8 color)
	{
		HANDLE hConsole = GetStdHandle(STD_ERROR_HANDLE);
		SetConsoleTextAttribute(hConsole, color);

		WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, messageLength, NULL, NULL);
	}

	void* PlatformAllocateMemory(u32 size)
	{
		return malloc(size);
	}

	void PlatformFreeMemory(void* location)
	{
		free(location);
	}

	void PlatformCopyMemory(void* from, const void* to, u32 size)
	{
		memcpy(from, to, size);
	}

	void PlatformSetMemory(void* location, i8 value, u32 size)
	{
		memset(location, value, size);
	}

	void PlatformZeroMemory(void* location, u32 size)
	{
		memset(location, 0, size);
	}

	void PlatformWriteFile(const char* fileName, const char* contents, u64 bytesToWrite)
	{
		HANDLE fileHandle = CreateFileA(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		ASSERT(fileHandle != INVALID_HANDLE_VALUE);

		DWORD bytesWritten;
		ASSERT(WriteFile(fileHandle, contents, (DWORD)bytesToWrite, &bytesWritten, 0));

		CloseHandle(fileHandle);
	}

	void* PlatformOpenFile(const char* fileName)
	{
		// TODO: Error check? ASSERT(fileHandle != INVALID_HANDLE_VALUE);
		return CreateFileA(fileName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	u64 PlatformGetOpenFileSize(void* handle)
	{
		LARGE_INTEGER fileSize;
		ASSERT(GetFileSizeEx((HANDLE)handle, &fileSize));
		return (u64)fileSize.QuadPart;
	}

	void PlatformReadOpenFile(void* handle, char* buffer, u64 bytesToRead)
	{
		DWORD bytesRead;
		ASSERT(ReadFile((HANDLE)handle, (void*)buffer, (DWORD)bytesToRead, &bytesRead, 0));
		buffer[bytesRead] = '\0';
	}

	void PlatformCloseFile(void* handle)
	{
		CloseHandle((HANDLE)handle);
	}

	PlatformTime PlatformCurrentTime()
	{
		LARGE_INTEGER performanceCount;
		QueryPerformanceCounter(&performanceCount);

		return (PlatformTime)(performanceCount.QuadPart / performanceFrequency);
	}
}

#endif