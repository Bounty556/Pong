#include "TestClass.h"

TestClass::TestClass(u32 x, u32 y, u32 z) :
	m_X(x),
	m_Y(y),
	m_Z(z)
{
}

TestClass::TestClass(const TestClass& other) :
	m_X(other.m_X),
	m_Y(other.m_Y),
	m_Z(other.m_Z)
{
}

TestClass::~TestClass()
{
}

bool TestClass::operator==(const TestClass& other) const
{
	return other.m_X == m_X && other.m_Y == m_Y && other.m_Z == m_Z;
}

bool TestClass::operator!=(const TestClass& other) const
{
	return other.m_X != m_X || other.m_Y != m_Y || other.m_Z != m_Z;
}