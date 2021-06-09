#pragma once

#include <Core/String.h>

namespace Soul
{
	/*
	Uses the Polynomial Rolling Hash function
	(https://cp-algorithms.com/string/string-hashing.html) to convert a String object into
	a hash.
	*/
	u64 Hash(const String& string);

	/*
	Uses the Polynomial Rolling Hash function
	(https://cp-algorithms.com/string/string-hashing.html) to convert a String object into
	a hash.
	*/
	u64 Hash(const char* string);

	/*
	Hashes integer by simply converting to an unsigned long long.
	*/
	u64 Hash(u32 integer);
}