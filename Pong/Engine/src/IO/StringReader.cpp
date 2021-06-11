#include "StringReader.h"

namespace Soul
{
	StringReader::StringReader(const String& string) :
		m_StringStart(string.GetCString()),
		m_CurrentIndex(0),
		m_LastIndex(string.Length())
	{
	}

	String StringReader::GetNextLine()
	{
		return GetUntil('\n');
	}

	char StringReader::GetNextChar()
	{
		while (m_CurrentIndex < m_LastIndex)
		{
			if (m_StringStart[m_CurrentIndex] != '\r')
				return m_StringStart[m_CurrentIndex++];
			++m_CurrentIndex;
		}

		return 0;
	}

	String StringReader::GetUntil(char toFind)
	{
		String accum = "";
		while (m_StringStart[m_CurrentIndex] != toFind && m_CurrentIndex != m_LastIndex)
		{
			if (m_StringStart[m_CurrentIndex] != '\r')
				accum += m_StringStart[m_CurrentIndex];
			m_CurrentIndex++;
		}

		if (m_CurrentIndex < m_LastIndex)
			m_CurrentIndex++; // Skip over the character we want to stop at

		return accum;
	}

	String StringReader::GetIncluding(char toFind)
	{
		String accum = "";
		while (m_StringStart[m_CurrentIndex] != toFind && m_CurrentIndex < m_LastIndex)
		{
			if (m_StringStart[m_CurrentIndex] != '\r')
				accum += m_StringStart[m_CurrentIndex];
			m_CurrentIndex++;
		}

		if (m_CurrentIndex < m_LastIndex)
			accum += m_StringStart[m_CurrentIndex++];// Add the character we wanted to stop at
	
		return accum;
	}

	String StringReader::GetRest()
	{
		String accum = "";
		while (m_CurrentIndex < m_LastIndex)
		{
			if (m_StringStart[m_CurrentIndex] != '\r')
				accum += m_StringStart[m_CurrentIndex];
			m_CurrentIndex++;
		}

		return accum;
	}

	bool StringReader::IsAtEnd() const
	{
		return m_CurrentIndex == m_LastIndex;
	}
}