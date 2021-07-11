#include "Random.h"

namespace Soul
{
	u32 xorshift32(u32 state)
	{
		u32 x = state;
		x ^= x << 13;
		x ^= x >> 17;
		x ^= x << 5;
		return x;
	}

	u64 xorshift64(u64 state)
	{
		u64 x = state;
		x ^= x << 13;
		x ^= x >> 7;
		x ^= x << 17;
		return x;
	}

	static u32 state32;
	static u64 state64;

	namespace Math
	{
		void SetSeed(u64 seed)
		{
			state32 = (u32)seed;
			state64 = seed;
		}

		u64 Rand()
		{
			state64 = xorshift64(state64);
			return state64;
		}

		u64 Rand(u64 max)
		{
			state64 = xorshift64(state64);
			return state64 % max;
		}

		u64 Rand(u64 min, u64 max)
		{
			ASSERT(min < max);
			state64 = xorshift64(state64);
			return (state64 % (max - min)) + min;
		}

		u32 Rand32()
		{
			state32 = xorshift32(state32);
			return state32;
		}

		u32 Rand32(u32 max)
		{
			state32 = xorshift32(state32);
			return state32 % max;
		}

		u32 Rand32(u32 min, u32 max)
		{
			ASSERT(min < max);
			state32 = xorshift32(state32);
			return (state32 % (max - min)) + min;
		}
	}
}