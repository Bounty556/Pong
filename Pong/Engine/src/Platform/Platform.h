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
	SOULAPI void PlatformCopyMemory(void* from, const void* to, i32 size);
	SOULAPI void PlatformSetMemory(void* location, i8 value, i32 size);
	SOULAPI void PlatformZeroMemory(void* location, i32 size);
	PlatformTime PlatformCurrentTime();
}