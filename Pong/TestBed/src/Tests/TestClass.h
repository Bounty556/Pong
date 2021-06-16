#pragma once

#include <Defines.h>

namespace Soul
{
	class TestClass
	{
	public:
		TestClass(u32 x, u32 y, u32 z);
		TestClass(const TestClass& other);

		bool operator==(const TestClass& other) const;
		bool operator!=(const TestClass& other) const;

	private:
		u32 m_X;
		u32 m_Y;
		u32 m_Z;
	};
}