#pragma once

#include <Defines.h>

#define LOG_LEVEL 0 // 0 - Debug, 1 - Info...

namespace Soul
{
	enum LogLevel
	{
		Debug = 0,
		Info,
		Warn,
		Error,
		Fatal,
		LogLevelCount
	};

	bool InitiateLogger(const char* logFile);
	bool ShutdownLogger();

	void SOULAPI LogMessage(LogLevel logLevel, const char* message, ...);
}

#ifdef _DEBUG
#if LOG_LEVEL <= 0
#define LOG_DEBUG(message, ...) Soul::LogMessage(Soul::LogLevel::Debug, message, __VA_ARGS__)
#else
#define LOG_DEBUG(message, ...)
#endif
#else
#define LOG_DEBUG(message, ...)
#endif

#if LOG_LEVEL <= 1
#define LOG_INFO(message, ...) Soul::LogMessage(Soul::LogLevel::Info, message, __VA_ARGS__)
#else
#define LOG_INFO(message, ...)
#endif

#if LOG_LEVEL <= 2
#define LOG_WARN(message, ...) Soul::LogMessage(Soul::LogLevel::Warn, message, __VA_ARGS__)
#else
#define LOG_WARN(message, ...)
#endif

#define LOG_ERROR(message, ...) Soul::LogMessage(Soul::LogLevel::Error, message, __VA_ARGS__)
#define LOG_FATAL(message, ...) Soul::LogMessage(Soul::LogLevel::Fatal, message, __VA_ARGS__)