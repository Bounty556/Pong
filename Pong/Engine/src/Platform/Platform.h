#pragma once

#include <Defines.h>

typedef f32 PlatformTime;

namespace Soul
{
	bool PlatformInitialize();
	void PlatformWriteToConsole(const char* message, i32 messageLength, i8 color);
	void PlatformWriteErrorToConsole(const char* message, i32 messageLength, i8 color);
	void* PlatformAllocateMemory(i32 size);
	void PlatformFreeMemory(void* location);
	void PlatformCopyMemory(void* from, void* to, i32 size);
	void PlatformSetMemory(void* location, i8 value, i32 size);
	void PlatformZeroMemory(void* location, i32 size);
	PlatformTime PlatformCurrentTime();
}