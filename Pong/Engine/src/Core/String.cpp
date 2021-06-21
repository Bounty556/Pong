#include "String.h"

#include <Math/Functions.h>
#include <Memory/MemoryManager.h>
#include <Platform/Platform.h>

namespace Soul
{
	String::String(const char* initialString) :
		m_Length(StringLength(initialString)),
		m_Capacity(m_Length + 1)
	{
		m_CString = (char*)PARTITION_ARRAY(char, m_Capacity);
		PlatformCopyMemory(m_CString, initialString, m_Length);
		m_CString[m_Length] = '\0';
	}

	String::String(const char initialChar) :
		m_Length(1),
		m_Capacity(32)
	{
		m_CString = (char*)PARTITION_ARRAY(char, m_Capacity);
		m_CString[0] = initialChar;
		m_CString[1] = '\0';
	}

	String::String(u32 capacity) :
		m_Length(0),
		m_Capacity(capacity)
	{
		ASSERT(capacity > 0);

		m_CString = PARTITION_ARRAY(char, m_Capacity);
		m_CString[0] = '\0';
	}

	String::String(const String& otherString) :
		m_Length(otherString.m_Length),
		m_Capacity(otherString.m_Capacity)
	{
		m_CString = PARTITION_ARRAY(char, m_Capacity);

		PlatformCopyMemory(m_CString, otherString.GetCString(), m_Length);
		m_CString[m_Length] = '\0';
	}

	String::String(String&& otherString) noexcept :
		m_Length(otherString.m_Length),
		m_Capacity(otherString.m_Capacity),
		m_CString(otherString.m_CString)
	{
		otherString.m_CString = nullptr;
		otherString.m_Capacity = 0;
		otherString.m_Length = 0;
	}

	String::~String()
	{
		if (m_CString)
			MemoryManager::FreeMemory(m_CString);
	}

	String& String::operator=(const String& otherString)
	{
		m_Length = otherString.m_Length;

		if (m_Capacity < otherString.m_Capacity)
		{
			m_Capacity = otherString.m_Capacity;
			MemoryManager::FreeMemory(m_CString);
			m_CString = PARTITION_ARRAY(char, m_Capacity);
		}

		PlatformCopyMemory(m_CString, otherString.m_CString, m_Length);
		m_CString[m_Length] = '\0';

		return *this;
	}

	String& String::operator=(String&& otherString) noexcept
	{
		// Clear our memory first
		MemoryManager::FreeMemory(m_CString);

		m_CString = otherString.m_CString;
		m_Capacity = otherString.m_Capacity;
		m_Length = otherString.m_Length;
		otherString.m_CString = nullptr;
		otherString.m_Capacity = 0;
		otherString.m_Length = 0;

		return *this;
	}

	String& String::operator=(const char* otherString)
	{
		m_Length = StringLength(otherString);

		if (m_Capacity < m_Length)
		{
			m_Capacity = m_Length;
			MemoryManager::FreeMemory(m_CString);
			m_CString = PARTITION_ARRAY(char, m_Capacity);
		}

		PlatformCopyMemory(m_CString, otherString, m_Length);
		m_CString[m_Length] = '\0';

		return *this;
	}

	String& String::operator=(const char otherChar)
	{
		if (otherChar != '\0')
		{
			m_Length = 1;
			m_CString[1] = '\0';
			m_CString[0] = otherChar;
		}
		else
		{
			m_Length = 0;
			m_CString[0] = '\0';
		}

		return *this;
	}

	String& String::operator+=(const String& otherString)
	{
		return operator+=(otherString.m_CString);
	}

	String& String::operator+=(const char* otherString)
	{
		u32 otherLength = StringLength(otherString);
		u32 tempLength = m_Length + otherLength;

		if (m_Capacity <= tempLength)
		{
			m_Capacity = tempLength + 1;
			char* tempPointer = PARTITION_ARRAY(char, m_Capacity);

			// Put the values of both the strings at the temp pointer
			PlatformCopyMemory(tempPointer, m_CString, m_Length);
			PlatformCopyMemory(tempPointer + m_Length, otherString, otherLength);
			tempPointer[tempLength] = '\0';

			// Clean up and reassign
			MemoryManager::FreeMemory(m_CString);
			m_Length = tempLength;
			m_CString = tempPointer;
		}
		else
		{
			// Add the other string's characters to the end of our string
			PlatformCopyMemory(m_CString + m_Length, otherString, otherLength);
			m_CString[tempLength] = '\0';

			m_Length = tempLength;
		}

		return *this;
	}

	String& String::operator+=(const char otherChar)
	{
		if (m_Length + 1 >= m_Capacity)
		{
			m_Capacity += 32; // Add another 4 bytes onto the memory
			char* tempPointer = PARTITION_ARRAY(char, m_Capacity);

			// Put the values of both the strings at the temp pointer
			PlatformCopyMemory(tempPointer, m_CString, m_Length);

			tempPointer[m_Length] = otherChar;
			tempPointer[m_Length + 1] = '\0';

			// Clean up and reassign
			MemoryManager::FreeMemory(m_CString);
			m_CString = tempPointer;
		}
		else
		{
			m_CString[m_Length] = otherChar;
			m_CString[m_Length + 1] = '\0';
		}

		if (otherChar != '\0')
			m_Length += 1;

		return *this;
	}

	String String::operator+(const String& otherString)
	{
		String newString(*this);
		newString += otherString;
		return newString;
	}

	String String::operator+(const char* otherString)
	{
		String newString(*this);
		newString += otherString;
		return newString;
	}

	String String::operator+(const char otherChar)
	{
		String newString(*this);
		newString += otherChar;
		return newString;
	}

	bool String::operator==(const String& otherString) const
	{
		return CompareTo(otherString) == 0;
	}

	bool String::operator==(const char* otherString) const
	{
		return CompareTo(otherString) == 0;
	}

	bool String::operator!=(const String& otherString) const
	{
		return CompareTo(otherString) != 0;
	}

	bool String::operator!=(const char* otherString) const
	{
		return CompareTo(otherString) != 0;
	}

	const char String::operator[](u32 index) const
	{
		ASSERT(index >= 0 && index < m_Length)
		return m_CString[index];
	}

	char& String::operator[](u32 index)
	{
		ASSERT(index >= 0 && index < m_Length);
		return m_CString[index];
	}

	u32 String::Length() const
	{
		return m_Length;
	}

	i32 String::CompareTo(const String& otherString) const
	{
		return StringCompare(m_CString, otherString.m_CString);
	}

	i32 String::CompareTo(const char* otherString) const
	{
		return StringCompare(m_CString, otherString);
	}

	const char* String::GetCString() const
	{
		return m_CString;
	}

	char* String::GetBufferStart() const
	{
		return m_CString;
	}

	i32 String::ToInt() const
	{
		// Extract only the number
		String number;
		bool encounteredNumber = false;
		bool isNegative = false;
		for (u32 i = 0; i < m_Length; ++i)
		{
			// If this is a numerical character
			if (m_CString[i] >= 48 && m_CString[i] <= 57)
			{
				// Check to see if this is negative
				if (encounteredNumber == false && i > 0 && m_CString[i - 1] == '-')
					isNegative = true;
				encounteredNumber = true;
				number += m_CString[i];
			}
			else if (!encounteredNumber && m_CString[i] == '.')
			{
				encounteredNumber = true;
				number += '0';
				break;
			}
			else if (encounteredNumber)
				break;
		}

		if (encounteredNumber)
		{
			i32 convertedInt = 0;

			for (u32 i = 0; i < number.Length(); ++i)
			{
				u8 charValue = number[i] - 48;
				convertedInt += charValue * Math::PowInt(10, number.Length() - (i + 1));
			}

			if (isNegative)
				convertedInt *= -1;

			return convertedInt;
		}

		return -1;
	}

	void String::Reverse()
	{
		u32 stringEnd = m_Length - 1;
		for (u32 i = 0; i < m_Length / 2; ++i)
		{
			char tempChar = m_CString[i];
			m_CString[i] = m_CString[stringEnd - i];
			m_CString[stringEnd - i] = tempChar;
		}
	}

	void String::ReserveCapacity(u32 capacity)
	{
		bool isOverCapacity = false;
		u32 oldStringCapacity = m_Capacity;
		while(m_Capacity <= capacity + 1)
		{
			m_Capacity *= 2;
			isOverCapacity = true;
		}

		if (isOverCapacity)
		{
			char* tempString = (char*)MemoryManager::PartitionMemory(m_Capacity);

			PlatformCopyMemory(m_CString, tempString, oldStringCapacity);

			MemoryManager::FreeMemory(m_CString);
			m_CString = tempString;
		}
	}

	void String::SetLength(u32 stringLength)
	{
		m_Length = stringLength;
	}

	i32 String::FindFirstOf(char character) const
	{
		for (u32 i = 0; i < m_Length; ++i)
			if (m_CString[i] == character)
				return (i32)i;

		return -1;
	}

	String String::Substring(u32 start, u32 end) const
	{
		ASSERT(end > start);
		ASSERT(end >= 0 && end <= m_Length);
		ASSERT(start >= 0 && start < m_Length);
		String newString(end - start + 1);
		PlatformCopyMemory(newString.m_CString, m_CString + start, end - start);
		newString.m_Length = end - start;
		newString.m_CString[newString.m_Length] = '\0';

		return newString;
	}

	String String::Substring(u32 start) const
	{
		ASSERT(start >= 0 && start < m_Length);
		String newString(m_CString + start);

		return newString;
	}

	String String::IntToString(i32 value)
	{
		String converted;
		bool isNegative = false;
		if (value < 0)
		{
			isNegative = true;
			value = -value;
		}
		else if (value == 0)
		{
			converted += '0';
			return converted;
		}

		while (value > 0)
		{
			u32 digit = value % 10;
			converted += (char)(digit + 48);
			value = value / 10;
		}

		if (isNegative)
			converted += '-';

		converted.Reverse();

		return converted;
	}

	// OpenBSD implementation
	u32 String::StringLength(const char* str)
	{
		const char* s;
		for (s = str; *s; s++);
		return s - str;
	}

	i32 String::StringCompare(const char* a, const char* b)
	{
		const char* ac;
		const char* bc;
		for (ac = a, bc = b; *ac && *bc; ac++, bc++)
		{
			if (*ac < *bc)
				return -1;
			if (*ac > *bc)
				return 1;
		}

		if (*ac)
			return 1;
		if (*bc)
			return -1;

		return 0;
	}
}