#include "String.h"

#include <Math/Functions.h>
#include <Memory/MemoryManager.h>
#include <Platform/Platform.h>

// TODO: Maybe replace this with our own
#include <cstring>

namespace Soul
{
	String::String(const char* initialString) :
		m_StringLength(strlen(initialString))
	{
		// We do this so that the string length is always a power of 2, or, if
		// represented in binary form, something like 00010000 or 00001000...
		if (m_StringLength + 1 > m_MINIMUM_CAPACITY / 2)
		{
			// Determine capacity through doubling highest bit
			u32 bits = m_StringLength + 1;
			u32 halfCount = 0;
			while (bits > 0)
			{
				bits /= 2;
				halfCount++;
			}

			m_StringCapacity = 1 << halfCount;
		}
		else
			m_StringCapacity = m_MINIMUM_CAPACITY; // The minimum is 64 bytes

		m_CString = (char*)MemoryManager::PartitionMemory(m_StringCapacity);
		PlatformCopyMemory(m_CString, initialString, m_StringLength);
		m_CString[m_StringLength] = '\0';
	}

	String::String(const char initialChar) :
		m_StringLength(1),
		m_StringCapacity(m_MINIMUM_CAPACITY)
	{
		m_CString = (char*)MemoryManager::PartitionMemory(m_StringCapacity);
		m_CString[0] = initialChar;
		m_CString[1] = '\0';
	}

	String::String(u32 capacity) :
		m_StringLength(0)
	{
		if (capacity < m_MINIMUM_CAPACITY)
			m_StringCapacity = capacity;
		else
		{
			u32 tempCapacity = m_MINIMUM_CAPACITY;
			while (tempCapacity <= capacity)
				tempCapacity *= 2;
			m_StringCapacity = tempCapacity;
		}

		m_CString = (char*)MemoryManager::PartitionMemory(m_StringCapacity);
		m_CString[0] = '\0';
	}

	String::String(const String& otherString) :
		m_StringLength(otherString.m_StringLength),
		m_StringCapacity(otherString.m_StringCapacity)
	{
		m_CString = (char*)MemoryManager::PartitionMemory(m_StringCapacity);

		PlatformCopyMemory(m_CString, otherString.GetCString(), m_StringLength);
		m_CString[m_StringLength] = '\0';
	}

	String::String(String&& otherString) :
		m_StringLength(otherString.m_StringLength),
		m_StringCapacity(otherString.m_StringCapacity),
		m_CString(otherString.m_CString)
	{
		otherString.m_CString = nullptr;
		otherString.m_StringCapacity = 0;
		otherString.m_StringLength = 0;
	}

	String::~String()
	{
		if (m_CString)
			MemoryManager::FreeMemory(m_CString);
	}

	String& String::operator=(const String& otherString)
	{
		m_StringLength = otherString.m_StringLength;

		if (m_StringCapacity < otherString.m_StringCapacity)
		{
			m_StringCapacity = otherString.m_StringCapacity;
			MemoryManager::FreeMemory(m_CString);
			m_CString = (char*)MemoryManager::PartitionMemory(m_StringCapacity);
		}

		PlatformCopyMemory(m_CString, otherString.m_CString, m_StringLength);
		m_CString[m_StringLength] = '\0';

		return *this;
	}

	// TODO: Free our memory first
	String& String::operator=(String&& otherString)
	{
		m_CString = otherString.m_CString;
		m_StringCapacity = otherString.m_StringCapacity;
		m_StringLength = otherString.m_StringLength;
		otherString.m_CString = nullptr;
		otherString.m_StringCapacity = 0;
		otherString.m_StringLength = 0;

		return *this;
	}

	String& String::operator=(const char* otherString)
	{
		m_StringLength = strlen(otherString);

		bool didCapacityIncrease = false;
		while (m_StringCapacity <= m_StringLength)
		{
			didCapacityIncrease = true;
			m_StringCapacity *= 2;
		}

		if (didCapacityIncrease)
		{
			MemoryManager::FreeMemory(m_CString);
			m_CString = (char*)MemoryManager::PartitionMemory(m_StringCapacity);
		}

		PlatformCopyMemory(m_CString, otherString, m_StringLength);
		m_CString[m_StringLength] = '\0';

		return *this;
	}

	String& String::operator=(const char otherChar)
	{
		if (otherChar != '\0')
		{
			m_StringLength = 1;
			m_CString[1] = '\0';
			m_CString[0] = otherChar;
		}
		else
		{
			m_StringLength = 0;
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
		u32 otherLength = strlen(otherString);
		u32 tempLength = m_StringLength + otherLength;

		// There are 2 scenarios here: one where we don't exceed our current string capacity,
		// and one where we do. If we exceed our string capacity, we need to repartition memory
		// for our string and move things over
		bool isOverCapacity = false;

		while (m_StringCapacity <= tempLength + 1)
		{
			m_StringCapacity *= 2;
			isOverCapacity = true;
		}

		if (isOverCapacity)
		{
			char* tempPointer = (char*)MemoryManager::PartitionMemory(m_StringCapacity);

			// Put the values of both the strings at the temp pointer
			u32 stringIndex = 0;
			for (u32 i = 0; i < m_StringLength; ++i)
			{
				tempPointer[stringIndex] = m_CString[i];
				++stringIndex;
			}

			// Add 1 to get the null terminator
			for (u32 i = 0; i < otherLength + 1; ++i)
			{
				tempPointer[stringIndex] = otherString[i];
				++stringIndex;
			}

			// Clean up and reassign
			MemoryManager::FreeMemory(m_CString);
			m_StringLength = tempLength;
			m_CString = tempPointer;
		}
		else
		{
			// Add the other string's characters to the end of our string
			for (u32 i = 0; i < otherLength + 1; ++i)
				m_CString[m_StringLength + i] = otherString[i];

			m_StringLength = tempLength;
		}

		return *this;
	}

	String& String::operator+=(const char otherChar)
	{
		// There are 2 scenarios here: one where we don't exceed our current string capacity,
		// and one where we do. If we exceed our string capacity, we need to repartition memory
		// for our string and move things over
		bool isOverCapacity = false;
		if (m_StringCapacity <= m_StringLength + 2)
		{
			m_StringCapacity *= 2;
			isOverCapacity = true;
		}

		if (isOverCapacity)
		{
			char* tempPointer = (char*)MemoryManager::PartitionMemory(m_StringCapacity);

			// Put the values of both the strings at the temp pointer
			u32 stringIndex = 0;
			for (u32 i = 0; i < m_StringLength; ++i)
			{
				tempPointer[stringIndex] = m_CString[i];
				++stringIndex;
			}

			tempPointer[stringIndex] = otherChar;
			tempPointer[stringIndex + 1] = '\0';

			// Clean up and reassign
			MemoryManager::FreeMemory(m_CString);
			m_CString = tempPointer;
		}
		else
		{
			m_CString[m_StringLength] = otherChar;
			m_CString[m_StringLength + 1] = '\0';
		}

		if (otherChar != '\0')
			m_StringLength += 1;

		return *this;
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
		ASSERT(index >= 0 && index < m_StringLength)
		return m_CString[index];
	}

	u32 String::Length() const
	{
		return m_StringLength;
	}

	i32 String::CompareTo(const String& otherString) const
	{
		return strcmp(m_CString, otherString.m_CString);
	}

	i32 String::CompareTo(const char* otherString) const
	{
		return strcmp(m_CString, otherString);
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
		for (u32 i = 0; i < m_StringLength; ++i)
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
		u32 stringEnd = m_StringLength - 1;
		for (u32 i = 0; i < m_StringLength / 2; ++i)
		{
			char tempChar = m_CString[i];
			m_CString[i] = m_CString[stringEnd - i];
			m_CString[stringEnd - i] = tempChar;
		}
	}

	void String::ReserveCapacity(u32 capacity)
	{
		bool isOverCapacity = false;
		u32 oldStringCapacity = m_StringCapacity;
		while(m_StringCapacity <= capacity + 1)
		{
			m_StringCapacity *= 2;
			isOverCapacity = true;
		}

		if (isOverCapacity)
		{
			char* tempString = (char*)MemoryManager::PartitionMemory(m_StringCapacity);

			PlatformCopyMemory(m_CString, tempString, oldStringCapacity);

			MemoryManager::FreeMemory(m_CString);
			m_CString = tempString;
		}
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
}