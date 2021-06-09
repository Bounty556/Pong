#pragma once

#include <Defines.h>

namespace Soul
{
	// TODO: Look into turning these into constexpr functions
	namespace Math
	{
		/*
		Sets the provided value to be between min and max if outside range.
		*/
		SOULAPI void Clamp(f32& outVal, f32 min, f32 max);

		/*
		Computes the value of value^power.
		*/
		SOULAPI i32 PowInt(i32 value, u32 power);

		/*
		Computes the value of value^power.
		*/
		SOULAPI f32 PowFloat(f32 value, i32 power);

		/*
		Finds the nearest prime that is >= to the provided number.
		*/
		SOULAPI u32 FindNextPrime(u32 number);

		/*
		Checks to see if this number is prime.
		*/
		SOULAPI bool IsPrime(u32 number);

		/*
		Returns the absolute value of this number.
		*/
		SOULAPI f32 Abs(f32 number);

		/*
		Rounds the provided float to the nearest integer.
		*/
		SOULAPI i32 Round(f32 number);

		/*
		Calculates fast square root of number.
		From: https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
		*/
		SOULAPI f32 Sqrt(f32 number);

		/*
		Returns the max of the two values.
		*/
		SOULAPI f32 Max(f32 a, f32 b);

		/*
		Returns the max of the two values.
		*/
		SOULAPI i32 Max(i32 a, i32 b);

		/*
		Returns the min of the two values.
		*/
		SOULAPI f32 Min(f32 a, f32 b);

		/*
		Returns the min of the two values.
		*/
		SOULAPI i32 Min(i32 a, i32 b);
	}
}