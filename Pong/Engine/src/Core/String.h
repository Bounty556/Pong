#pragma once

#include <Defines.h>

namespace Soul
{
	/*
	This is to be used in place of the C Standard Template Library strings. They should behave
	almost identically, but instead use our built-in memory arena.
	*/
	class SOULAPI String
	{
	public:
		String(const char* initialString = "");
		String(const char initialChar);
		String(u32 capacity);

		String(const String& otherString); // Copy constructor
		String(String&& otherString); // Move constructor

		~String();

		String& operator=(const String& otherString);
		String& operator=(String&& otherString);
		String& operator=(const char* otherString);
		String& operator=(const char otherChar);

		String& operator+=(const String& otherString);
		String& operator+=(const char* otherString);
		String& operator+=(const char otherChar);

		bool operator==(const String& otherString) const;
		bool operator==(const char* otherString) const;

		bool operator!=(const String& otherString) const;
		bool operator!=(const char* otherString) const;

		const char operator[](u32 index) const;

		/*
		Returns the length of the string. Does not include the null terminator.
		*/
		u32 Length() const;

		/*
		Sets the length of this string. Should only be used if directly editing the buffer
		itself, such as when loading file contents into the string.
		*/
		void SetLength(u32 length);

		/*
		Returns:
		< 0 if this string is lexicographically less than the provided string.
		0 if this string is lexicographically equivalent to the provided string.
		> 0 if this string is lexicographically larger than the provided string.
		*/
		i32 CompareTo(const String& otherString) const;

		/*
		Returns:
		< 0 if this string is lexicographically less than the provided string.
		0 if this string is lexicographically equivalent to the provided string.
		> 0 if this string is lexicographically larger than the provided string.
		*/
		i32 CompareTo(const char* otherString) const;

		/*
		Returns the C-Style string underlying this String object.
		*/
		const char* GetCString() const;

		/*
		Returns the address of the start of the buffer in the MemoryArena that holds the string.
		USE WITH CAUTION!!!
		*/
		char* GetBufferStart() const;

		/*
		Attempts to convert the contents of this String into an integer. Will return -1 if no
		integer is found.
		*/
		i32 ToInt() const;

		/*
		Reverses the characters in this String.
		*/
		void Reverse();

		/*
		Utility function that converts an integer into a Soul::String.
		*/
		static String IntToString(i32 value);

	private:
		char* m_CString;
		u32 m_StringCapacity;
		u32 m_StringLength;
		const u32 m_MINIMUM_CAPACITY = 32;
	};
}