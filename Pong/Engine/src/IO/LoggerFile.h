#pragma once

#include <Defines.h>
#include <Core/String.h>

#include <SFML/System/Mutex.hpp>

namespace Soul
{
	class LoggerFile
	{
	public:
		LoggerFile(const char* outputFile, u32 bufferLimit);

		LoggerFile(const LoggerFile&) = delete;
		LoggerFile(LoggerFile&& other) = delete;

		~LoggerFile();

		LoggerFile& operator=(const LoggerFile&) = delete;
		LoggerFile& operator=(LoggerFile&& other) = delete;

		void LogInfo(const char* message);
		void OutputToFile();

	private:
		const char* m_OutputFile;
		Soul::String m_LogBuffer;
		u32 m_BufferLimit;
		sf::Mutex m_Mutex;
	};
}