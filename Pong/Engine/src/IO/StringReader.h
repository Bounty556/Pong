#pragma once

#include <Defines.h>
#include <Core/String.h>

namespace Soul
{
	/*
	Helper class that aids in reading CString and Soul::Strings line by line. This works quite
	differently from a typical StringStream. First, one of the get functions is called, which
	stores the resulting string into a variable within this StringReader. This string can then
	be accessed at anytime via GetLastValue().
	Ex:

	String string(...);
	StringReader stringReader(string);

	while (!stringReader.IsAtEnd())
		SoulLogInfo("%s", stringReader.GetNextLine();)
	*/
	class StringReader
	{
	public:
		StringReader(const String& string);

		String GetNextLine();
		String GetUntil(char toFind);
		String GetIncluding(char toFind);
		String GetRest();
		
		char GetNextChar();

		bool IsAtEnd() const;

	private:
		const char* m_StringStart; // The start of the string this StringReader is reading.
		u32 m_CurrentIndex; // The current index of the string this StringReader is at.
		u32 m_LastIndex;// The last index this StringReader is allowed to reach.
	};
}