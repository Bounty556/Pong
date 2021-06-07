#pragma once

// Unsigned int types.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// Signed int types.
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

// Floating point types
typedef float f32;
typedef double f64;

#define KILOBYTES(x) (x * 1024)
#define MEGABYTES(x) (KILOBYTES(x) * 1024)
#define GIGABYTES(x) (MEGABYTES(x) * 1024)

#define BYTE_DISTANCE(x, y) ((unsigned int)y - (unsigned int)x)

#define FLOAT_MAX 3.40282346e+38F

#define ASSERT(x) \
if (x) \
	{} \
else {*((int*)0) = 0;}

#ifdef SOULEXPORT
// Exports
#ifdef _MSC_VER
#define SOULAPI __declspec(dllexport)
#else
#define SOULAPI __attribute__((visibility("default")))
#endif
#else
// Imports
#ifdef _MSC_VER
#define SOULAPI __declspec(dllimport)
#else
#define SOULAPI
#endif
#endif