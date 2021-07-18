#include "Logger.h"

#include <Platform/Platform.h>
#include <IO/LoggerFile.h>
#include <Memory/MemoryManager.h>

#include <stdarg.h>

// TODO: Get rid of this
#include <string>

namespace Soul
{
	LoggerFile* loggerFile = nullptr;
	bool logFileInitialized = false;

	bool InitializeLogger(const char* logFile)
	{
		logFileInitialized = true;
		loggerFile = PARTITION(LoggerFile, logFile, 3000);
		loggerFile->LogInfo("-----------------------------");

		return true;
	}

	bool ShutdownLogger()
	{
		if (logFileInitialized)
		{
			loggerFile->OutputToFile();
			MemoryManager::FreeMemory(loggerFile);
		}
		
		return true;
	}

	void LogMessage(LogLevel logLevel, const char* message, ...)
	{
		static const char* LOG_LEVEL_PREFIXES[LogLevel::LogLevelCount] =
		{
			"[DEBUG]:",
			"[INFO]: ",
			"[WARN]: ",
			"[ERROR]:",
			"[FATAL]:"
		};
		static const i8 LOG_LEVEL_COLORS[LogLevel::LogLevelCount] = { 8, 2, 6, 4, 64 };
		bool isError = logLevel >= LogLevel::Error;
		const i32 MAX_LENGTH = 1024;
		char tempMessage[MAX_LENGTH];
		PlatformSetMemory(tempMessage, 0, sizeof(tempMessage));

		va_list args;
		va_start(args, message);
		vsnprintf(tempMessage, MAX_LENGTH, message, args);
		va_end(args);

		char finalMessage[MAX_LENGTH];

		// TODO: Use our own string library
		sprintf_s(finalMessage, "%s %s\n", LOG_LEVEL_PREFIXES[logLevel], tempMessage);

		if (isError)
			PlatformWriteErrorToConsole(finalMessage, strlen(finalMessage), LOG_LEVEL_COLORS[logLevel]);
		else
			PlatformWriteToConsole(finalMessage, strlen(finalMessage), LOG_LEVEL_COLORS[logLevel]);
	
		if (logFileInitialized)
			loggerFile->LogInfo(finalMessage);
	}
}