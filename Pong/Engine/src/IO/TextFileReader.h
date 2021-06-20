#pragma once

#include <Defines.h>
#include <Core/String.h>
#include <Memory/UniquePointer.h>

namespace Soul
{
	/*
	A file reader that uses a Soul::String as it's underlying buffer. Solely to be
	used for text files.
	*/
	class SOULAPI TextFileReader
	{
	public:
		TextFileReader();
		TextFileReader(const char* fileName);

		TextFileReader(const TextFileReader&) = delete;
		TextFileReader(TextFileReader&& other) noexcept;

		TextFileReader& operator=(const TextFileReader&) = delete;
		TextFileReader& operator=(TextFileReader&& other) noexcept;

		void ReadFile(const char* fileName);
		void WriteToCurrentFile();
		String& GetString();
		const char* GetCString();

	private:
		bool m_FileOpened;
		String m_FilePath;
		String m_FileContents;
	};
}