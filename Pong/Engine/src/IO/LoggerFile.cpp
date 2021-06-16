#include "LoggerFile.h"

#include <Platform/Platform.h>

namespace Soul
{
	LoggerFile::LoggerFile(const char* outputFile, u32 bufferLimit) :
		m_OutputFile(outputFile),
		m_LogBuffer(bufferLimit),
		m_BufferLimit(bufferLimit),
		m_Mutex()
	{
	}

	LoggerFile::~LoggerFile()
	{
		OutputToFile();
	}

	void LoggerFile::LogInfo(const char* message)
	{
		m_Mutex.lock();

		m_LogBuffer += message;

		if (m_LogBuffer.Length() > (u32)(m_BufferLimit * 0.9f))
			OutputToFile();

		m_Mutex.unlock();
	}

	void LoggerFile::OutputToFile()
	{
		m_Mutex.lock();

		PlatformAppendFile(m_OutputFile, m_LogBuffer.GetCString(), m_LogBuffer.Length());
		m_LogBuffer = "";

		m_Mutex.unlock();
	}
}