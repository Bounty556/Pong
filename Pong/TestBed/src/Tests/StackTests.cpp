#include "StackTests.h"

#include <Defines.h>
#include <Structures/Stack.h>

#include "TestClass.h"
#include "../TestMacros.h"

void PodStackTest()
{
	START_MEMORY_CHECK();

	Soul::Stack<u32> intStack;

	for (u32 i = 0; i < 1000; ++i)
		intStack.Push(i * 10);

	for (i32 i = 999; i >= 0; --i)
		ASSERT_EQUAL(intStack.Pop(), i * 10, "Failed to add ints to stack.");

	END_MEMORY_CHECK();
}

void ObjectStackTest()
{
	START_MEMORY_CHECK();

	Soul::Stack<TestClass> classStack;

	for (u32 i = 0; i < 1000; ++i)
		classStack.Push(TestClass(i * 3 - 2, i * 3 - 1, i * 3));

	for (i32 i = 999; i >= 0; --i)
		ASSERT_EQUAL(classStack.Pop(), TestClass(i * 3 - 2, i * 3 - 1, i * 3), "Failed to add objects to stack.");

	END_MEMORY_CHECK();
}

void MoveStackTest()
{
	START_MEMORY_CHECK();

	Soul::Stack<TestClass> classStack;

	classStack.Push(TestClass(1, 2, 3));
	classStack.Push(TestClass(4, 5, 6));
	classStack.Push(TestClass(7, 8, 9));

	Soul::Stack<TestClass> classStack2(std::move(classStack));

	ASSERT_EQUAL(classStack2.Pop(), TestClass(7, 8, 9), "Failed to move stack.");
	ASSERT_EQUAL(classStack2.Pop(), TestClass(4, 5, 6), "Failed to move stack.");
	ASSERT_EQUAL(classStack2.Pop(), TestClass(1, 2, 3), "Failed to move stack.");

	Soul::Stack<TestClass> classStack3;

	classStack3.Push(TestClass(1, 2, 3));
	classStack3.Push(TestClass(4, 5, 6));
	classStack3.Push(TestClass(7, 8, 9));

	Soul::Stack<TestClass> classStack4;
	classStack4 = std::move(classStack3);

	ASSERT_EQUAL(classStack4.Pop(), TestClass(7, 8, 9), "Failed to move queue.");
	ASSERT_EQUAL(classStack4.Pop(), TestClass(4, 5, 6), "Failed to move queue.");
	ASSERT_EQUAL(classStack4.Pop(), TestClass(1, 2, 3), "Failed to move queue.");

	END_MEMORY_CHECK();
}

void StackTests::RunAllTests()
{
	RUN_TEST(PodStackTest);
	RUN_TEST(ObjectStackTest);
	RUN_TEST(MoveStackTest);
}