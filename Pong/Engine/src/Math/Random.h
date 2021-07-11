#pragma once

#include <Defines.h>

namespace Soul
{
	namespace Math
	{
		void SOULAPI SetSeed(u64 seed);
		u64 SOULAPI Rand();
		u64 SOULAPI Rand(u64 max);
		u64 SOULAPI Rand(u64 min, u64 max);
		u32 SOULAPI Rand32();
		u32 SOULAPI Rand32(u32 max);
		u32 SOULAPI Rand32(u32 min, u32 max);
	}
}