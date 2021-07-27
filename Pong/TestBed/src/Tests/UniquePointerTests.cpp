#include "UniquePointerTests.h"

#include "../TestMacros.h"
#include "TestClass.h"

#include <Memory/MemoryManager.h>
#include <Memory/UniquePointer.h>

void PrimitiveUniquePointer()
{
	START_MEMORY_CHECK();

	Soul::UniquePointer<u32> uniqueInt = NEW(u32, 0);

	ASSERT_EQUAL(*uniqueInt, 0, "UniquePointer dereferencing failed.");

	Soul::UniquePointer<u32> uniqueInt2 = NEW(u32, 1);
			
	uniqueInt = std::move(uniqueInt2);

	ASSERT_EQUAL(*uniqueInt, 1, "Failed to move UniquePointer.");

	END_MEMORY_CHECK();
}

void ObjectUniquePointer()
{
	START_MEMORY_CHECK();

	TestClass fakeClass(1, 39, 43);
	TestClass fakeClass2(0, 121, 96);

	Soul::UniquePointer<TestClass> uniqueClass = NEW(TestClass, fakeClass);

	ASSERT_EQUAL(*uniqueClass, fakeClass, "UniquePointer dereferencing failed.");

	Soul::UniquePointer<TestClass> uniqueClass2 = NEW(TestClass, fakeClass2);

	uniqueClass = std::move(uniqueClass2);

	ASSERT_EQUAL(*uniqueClass, fakeClass2, "Failed to move handle.");

	END_MEMORY_CHECK();
}

void UniquePointerUniquePointer()
{
	START_MEMORY_CHECK();

	Soul::UniquePointer<Soul::UniquePointer<u32>> handleToUniqueInt =
		NEW(Soul::UniquePointer<u32>, NEW(u32, 0));

	ASSERT_EQUAL(**handleToUniqueInt, 0, "Handle dereferencing failed.");

	Soul::UniquePointer<Soul::UniquePointer<u32>> handleToUniqueInt2 =
		NEW(Soul::UniquePointer<u32>, NEW(u32, 1));

	handleToUniqueInt = std::move(handleToUniqueInt2);

	ASSERT_EQUAL(**handleToUniqueInt, 1, "Failed to move handle.");

	END_MEMORY_CHECK();
}

void PrimitiveArrayUniquePointer()
{
	START_MEMORY_CHECK();

	Soul::UniquePointer<u32> uniqueArray = NEW_ARRAY(u32, 100);

	for (u8 i = 0; i < 100; ++i)
		uniqueArray[i] = i;

	ASSERT_EQUAL(uniqueArray[0], 0, "Primitive array indexing failed.");

	Soul::UniquePointer<u32> uniqueArray2 = NEW_ARRAY(u32, 100);

	for (u8 i = 0; i < 100; ++i)
		uniqueArray2[i] = i + 1;

	uniqueArray = std::move(uniqueArray2);

	ASSERT_EQUAL(uniqueArray[0], 1, "Primitive array moving failed.");
	
	END_MEMORY_CHECK();
}

void ObjectArrayUniquePointer()
{
	START_MEMORY_CHECK();

	TestClass fakeClass(1, 39, 43);
	TestClass fakeClass2(0, 121, 96);

	Soul::UniquePointer<TestClass> uniqueArray = NEW_ARRAY(TestClass, 100);

	for (u8 i = 0; i < 100; ++i)
		uniqueArray[i] = fakeClass;

	ASSERT_EQUAL(uniqueArray[0], fakeClass, "Object array indexing failed.");

	Soul::UniquePointer<TestClass> uniqueArray2 = NEW_ARRAY(TestClass, 100);

	for (u8 i = 0; i < 100; ++i)
		uniqueArray2[i] = fakeClass2;

	uniqueArray = std::move(uniqueArray2);

	ASSERT_EQUAL(uniqueArray[0], fakeClass2, "Object array moving failed.");

	END_MEMORY_CHECK();
}

void UniquePointerArrayUniquePointer()
{
	START_MEMORY_CHECK();

	Soul::UniquePointer<Soul::UniquePointer<u32>> handleToUniqueArray = NEW_ARRAY(Soul::UniquePointer<u32>, 100);

	for (u8 i = 0; i < 100; ++i)
		handleToUniqueArray[i] = NEW(u32, 0);

	ASSERT_EQUAL(*(handleToUniqueArray[0]), 0, "Handle array indexing failed.");

	Soul::UniquePointer<Soul::UniquePointer<u32>> handleToUniqueArray2 = NEW_ARRAY(Soul::UniquePointer<u32>, 100);

	for (u8 i = 0; i < 100; ++i)
		handleToUniqueArray2[i] = NEW(u32, 1);

	for (u8 i = 0; i < 100; ++i)
		handleToUniqueArray[i].~UniquePointer();

	handleToUniqueArray = std::move(handleToUniqueArray2);

	ASSERT_EQUAL(*(handleToUniqueArray[0]), 1, "Handle array moving failed.");

	for (u8 i = 0; i < 100; ++i)
		handleToUniqueArray[i].~UniquePointer();

	END_MEMORY_CHECK();
}

void MoveUniquePointerTest()
{
	START_MEMORY_CHECK();

	Soul::UniquePointer<u32> uniqueInt = NEW(u32, 1);
	Soul::UniquePointer<u32> uniqueInt2 = std::move(uniqueInt);

	ASSERT_EQUAL(*uniqueInt2, 1, "Failed to reassign handle.");

	END_MEMORY_CHECK();
}

void UniquePointerTests::RunAllTests()
{
	RUN_TEST(PrimitiveUniquePointer);
	RUN_TEST(ObjectUniquePointer);
	RUN_TEST(UniquePointerUniquePointer);
	RUN_TEST(PrimitiveArrayUniquePointer);
	RUN_TEST(ObjectArrayUniquePointer);
	RUN_TEST(UniquePointerArrayUniquePointer);
	RUN_TEST(MoveUniquePointerTest);
}