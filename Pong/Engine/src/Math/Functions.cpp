#include "Functions.h"

#include <Math/Constants.h>

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
			if (number % 2 == 0 && number > 3)
				number++;
			while (!IsPrime(number))
				number += 2;

			return number;
		}

		/*
		From https://en.wikipedia.org/wiki/Primality_test
		*/
		bool IsPrime(u32 n)
		{
			if (n == 2 || n == 3)
				return true;

			if (n <= 1 || n % 2 == 0 || n % 3 == 0)
				return false;
			
			for (u32 i = 5; i * i <= n; i += 6)
			{
				if (n % i == 0 || n % (i + 2) == 0)
					return false;
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
			i8 negative = (number < 0.0f) ? -1 : 1;
			number *= negative;
			f32 remainder = number - (i32)number;
			if (remainder >= 0.5f)
				return (i32)(negative * (number + 1.0f));
			else
				return (i32)(negative * number);
		}

		/*
		From https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
		*/
		f32 Sqrt(const f32 x)
		{
			union
			{
				i32 i;
				f32 x;
			} u;
			u.x = x;
			u.i = (1 << 29) + (u.i >> 1) - (1 << 22);

			u.x = u.x + x / u.x;
			u.x = 0.25f * u.x + x / u.x;

			return u.x;
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

		i32 Max(i32 a, i32 b)
		{
			if (a >= b)
				return a;
			else
				return b;
		}

		i32 Min(i32 a, i32 b)
		{
			if (a <= b)
				return a;
			else
				return b;
		}

		f32 ToRadians(f32 deg)
		{
			return deg * TO_RAD;
		}

		f32 ToDegrees(f32 rad)
		{
			return rad * TO_DEG;
		}

		// TODO: Make more accurate
		f64 Cos(f32 rad)
		{
			rad = FLOAT_MOD(rad, PI2);
			i8 sign = 1;
			if (rad > PI)
			{
				rad -= PI;
				sign = -1;
			}
			f64 xx = rad * rad;

			return sign * (1 - (xx * 0.5) + (xx * xx * 0.04166666666) - (xx * xx * xx * 0.00138888888) + (xx * xx * xx * xx * 0.00002480158) - (xx * xx * xx * xx * xx * 2.75573192e-7) + (xx * xx * xx * xx * xx * xx * 2.0876757e-9) - (xx * xx * xx * xx * xx * xx * xx * 1.1470746e-11));
		}

		f64 Sin(f32 rad)
		{
			return Cos(rad - HALF_PI);
		}

		f32 Acos(f32 x)
		{
			f32 negate = f32(x < 0.0f);
			x = Abs(x);
			f32 ret = -0.0187293f;
			ret = ret * x;
			ret = ret + 0.0742610f;
			ret = ret * x;
			ret = ret - 0.2121144f;
			ret = ret * x;
			ret = ret + 1.5707288f;
			ret = ret * Sqrt(1.0f - x);
			ret = ret - 2.0f * negate * ret;
			return negate * PI + ret;
		}

		f32 Asin(f32 x)
		{
			f32 negate = f32(x < 0.0f);
			x = Abs(x);
			f32 ret = -0.0187293f;
			ret *= x;
			ret += 0.0742610f;
			ret *= x;
			ret -= 0.2121144f;
			ret *= x;
			ret += 1.5707288f;
			ret = HALF_PI - Sqrt(1.0f - x) * ret;
			return ret - 2 * negate * ret;
		}

		f32 Atan2(f32 y, f32 x)
		{
			f32 t0, t1, t3, t4;

			t3 = Abs(x);
			t1 = Abs(y);
			t0 = Max(t3, t1);
			t1 = Min(t3, t1);
			t3 = 1.0f / t0;
			t3 = t1 * t3;

			t4 = t3 * t3;
			t0 = -0.013480470f;
			t0 = t0 * t4 + 0.057477314f;
			t0 = t0 * t4 - 0.121239071f;
			t0 = t0 * t4 + 0.195635925f;
			t0 = t0 * t4 - 0.332994597f;
			t0 = t0 * t4 + 0.999995630f;
			t3 = t0 * t3;

			t3 = (Abs(y) > Abs(x)) ? HALF_PI - t3 : t3;
			t3 = (x < 0.0f) ? PI - t3 : t3;
			t3 = (y < 0.0f) ? -t3 : t3;

			return t3;
		}
	}
}