#include "Functions.h"

// TODO: A lot of these functions can benefit from parallel programming and branchless programming

namespace Soul
{
	namespace Math
	{
		void Clamp(f32& value, f32 min, f32 max)
		{
			value = Max(Min(value, max), min);
		}

		i32 PowInt(i32 value, u32 power)
		{
			i32 total = 1;

			for (u32 i = 0; i < power; i++)
				total *= value;

			return total;
		}

		f32 PowFloat(f32 value, i32 power)
		{
			f32 total = 1.0f;
			bool isNegative = false;

			if (power < 0)
			{
				isNegative = true;
				power = -power;
			}

			for (i32 i = 0; i < power; i++)
				total *= value;

			if (isNegative)
				total = 1.0f / total;

			return total;
		}

		u32 FindNextPrime(u32 number)
		{
			while (!IsPrime(number))
				number++;

			return number;
		}

		bool IsPrime(u32 number)
		{
			// Check to see if even
			if (number % 2 == 0)
				return false;

			// Start at half, and divide by all numbers below to check for prime
			u32 divisor = number / 2;
			while (divisor >= 3)
			{
				if (number % divisor == 0)
					return false;
				divisor -= 1;
			}

			return true;
		}

		f32 Abs(f32 number)
		{
			if (number < 0.0f)
				return -number;
			return number;
		}

		i32 Round(f32 number)
		{
			f32 num = number - (i32)number;

			if (num > 0.5f)
				return (i32)(number + 1.0f);
			else
				return (i32)(number);
		}

		f32 Sqrt(f32 x)
		{
			u32 i = *(u32*)&x;
			// Adjust bias
			i += 127 << 23;
			// Approximation of square root
			i >>= 1;
			return *(f32*)&i;
		}

		f32 Max(f32 a, f32 b)
		{
			if (a >= b)
				return a;
			else
				return b;
		}

		f32 Min(f32 a, f32 b)
		{
			if (a <= b)
				return a;
			else
				return b;
		}
	}
}