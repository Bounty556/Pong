#include "TextFileReader.h"

#include <Platform/Platform.h>

namespace Soul
{
	TextFileReader::TextFileReader() :
		m_FileOpened(false),
		m_FilePath(),
		m_FileContents()
	{
	}

	TextFileReader::TextFileReader(const char* fileName) :
		m_FileOpened(false),
		m_FilePath(),
		m_FileContents()
	{
		ReadFile(fileName);
	}

	TextFileReader::TextFileReader(TextFileReader&& other) noexcept :
		m_FileOpened(other.m_FileOpened),
		m_FilePath(std::move(other.m_FilePath)),
		m_FileContents(std::move(other.m_FileContents))
	{
		other.m_FileOpened = false;
	}

	TextFileReader& TextFileReader::operator=(TextFileReader&& other) noexcept
	{
		m_FileOpened = other.m_FileOpened;
		m_FilePath = std::move(other.m_FilePath);
		m_FileContents = std::move(other.m_FileContents);
		other.m_FileOpened = false;

		return *this;
	}

	void TextFileReader::ReadFile(const char* fileName)
	{
		m_FilePath = fileName;
		void* fileHandle = PlatformOpenFile(fileName);
		u64 fileSize = PlatformGetOpenFileSize(fileHandle);
		m_FileContents.ReserveCapacity((u32)fileSize);
		m_FileContents.SetLength((u32)fileSize);
		PlatformReadOpenFile(fileHandle, m_FileContents.GetBufferStart(), fileSize);
		PlatformCloseFile(fileHandle);
		m_FileOpened = true;
	}

	void TextFileReader::WriteToCurrentFile()
	{
		if (m_FileOpened)
			PlatformOverwriteFile(m_FilePath.GetCString(), m_FileContents.GetCString(), m_FileContents.Length());
	}

	String& TextFileReader::GetString()
	{
		return m_FileContents;
	}

	const char* TextFileReader::GetCString()
	{
		return m_FileContents.GetCString();
	}
}