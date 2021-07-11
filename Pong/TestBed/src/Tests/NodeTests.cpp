#include "NodeTests.h"

#include <Memory/UniquePointer.h>

#include "../TestMacros.h"
#include "TestClass.h"

void NodeTests::RunAllTests()
{
	RUN_TEST(BasicListeningTest);
	RUN_TEST(ObjectListeningTest);
}