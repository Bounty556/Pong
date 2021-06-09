#include "Hashes.h"

#include <string>

namespace Soul
{
	u64 hashPowers[] = {1,53,2809,148877,7890481,418195493,22164361129,1174711139837,62259690411361,3299763591802133,174887470365513060,9269035929372193000};

	// TODO: Convert to u32
	u64 Hash(const String& string)
	{
		u32 power = 0;
		u64 hashValue = 0;
		u64 m = 1000000009;

		for (u32 i = 0; i < string.Length(); ++i)
		{
			hashValue += (string[i] * hashPowers[power]) % m;

			power = (power + 1) % 12;
		}

		return hashValue;
	}

	u64 Hash(const char* string)
	{
		u32 power = 0;
		u64 hashValue = 0;
		u64 m = 1000000009;
		u32 stringLength = strlen(string); // TODO: Get rid of strlen

		for (u32 i = 0; i < stringLength; ++i)
		{
			hashValue += (string[i] * hashPowers[power]) % m;

			power = (power + 1) % 12;
		}

		if (hashValue == 0)
			hashValue = 1;

		return hashValue;
	}

	u64 Hash(u32 integer)
	{
		return (u64)integer;
	}
}