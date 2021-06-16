#pragma once

#include <Defines.h>

typedef f32 PlatformTime;

namespace Soul
{
	bool PlatformInitialize();
	void PlatformWriteToConsole(const char* message, u32 messageLength, i8 color);
	void PlatformWriteErrorToConsole(const char* message, u32 messageLength, i8 color);
	void* PlatformAllocateMemory(u32 size);
	void PlatformFreeMemory(void* location);
	SOULAPI void PlatformCopyMemory(void* from, const void* to, u32 size);
	SOULAPI void PlatformSetMemory(void* location, i8 value, u32 size);
	SOULAPI void PlatformZeroMemory(void* location, u32 size);
	void PlatformOverwriteFile(const char* fileName, const char* contents, u64 bytesToWrite);
	void PlatformAppendFile(const char* fileName, const char* contents, u64 bytesToWrite);
	void* PlatformOpenFile(const char* fileName);
	u64 PlatformGetOpenFileSize(void* handle);
	void PlatformReadOpenFile(void* handle, char* buffer, u64 bytesToRead);
	void PlatformCloseFile(void* handle);
}