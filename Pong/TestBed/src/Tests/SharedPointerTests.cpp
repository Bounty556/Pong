#include "SharedPointerTests.h"

#include <Defines.h>
#include <Memory/SharedPointer.h>

#include "../TestMacros.h"
#include "TestClass.h"

void PrimitiveSharedPointer()
{
	START_MEMORY_CHECK();

	Soul::SharedPointer<u32> sharedInt = NEW(u32, 1);

	ASSERT_EQUAL(*sharedInt, 1, "SharedPointer dereferencing failed.");

	{
		Soul::SharedPointer<u32> sharedInt1 = NEW(u32, 2);

		ASSERT_EQUAL(*sharedInt1, 2, "SharedPointer dereferencing failed.");
	
		sharedInt1 = sharedInt;

		ASSERT_EQUAL(*sharedInt1, 1, "SharedPointer copy failed.");
	}

	ASSERT_EQUAL(*sharedInt, 1, "SharedPointer freed too early.");

	END_MEMORY_CHECK();
}

void ObjectSharedPointer()
{
	START_MEMORY_CHECK();

	TestClass fakeClass(1, 39, 43);
	TestClass fakeClass2(0, 121, 96);

	Soul::SharedPointer<TestClass> sharedClass = NEW(TestClass, fakeClass);

	ASSERT_EQUAL(*sharedClass, fakeClass, "SharedPointer dereferencing failed.");

	{
		Soul::SharedPointer<TestClass> sharedClass1 = NEW(TestClass, fakeClass2);

		ASSERT_EQUAL(*sharedClass1, fakeClass2, "SharedPointer dereferencing failed.");

		sharedClass1 = sharedClass;

		ASSERT_EQUAL(*sharedClass1, fakeClass, "SharedPointer copy failed.");
	}

	ASSERT_EQUAL(*sharedClass, fakeClass, "SharedPointer freed too early.");

	END_MEMORY_CHECK();
}

void SharedPointerSharedPointer()
{
	START_MEMORY_CHECK();

	Soul::SharedPointer<Soul::SharedPointer<u32>> sharedSharedInt = NEW(Soul::SharedPointer<u32>, NEW(u32, 1));

	ASSERT_EQUAL(**sharedSharedInt, 1, "SharedPointer dereferencing failed.");

	{
		Soul::SharedPointer<Soul::SharedPointer<u32>> sharedSharedInt1 = NEW(Soul::SharedPointer<u32>, NEW(u32, 2));

		ASSERT_EQUAL(**sharedSharedInt1, 2, "SharedPointer dereferencing failed.");

		sharedSharedInt1 = sharedSharedInt;

		ASSERT_EQUAL(**sharedSharedInt1, 1, "SharedPointer copy failed.");
	}

	ASSERT_EQUAL(**sharedSharedInt, 1, "SharedPointer freed too early.");

	END_MEMORY_CHECK();
}

void MoveSharedPointerTest()
{
	START_MEMORY_CHECK();

	Soul::SharedPointer<u32> sharedInt = NEW(u32, 1);

	{
		Soul::SharedPointer<u32> sharedInt1 = std::move(sharedInt);

		ASSERT_EQUAL(*sharedInt1, 1, "Failed to reassign sharedPointer.");
	}

	ASSERT_FALSE(sharedInt.IsValid(), "Failed to move pointer.");

	END_MEMORY_CHECK();
}

void ReassignNormalPointerTest()
{
	START_MEMORY_CHECK();

	Soul::SharedPointer<u32> sharedInt = NEW(u32, 1);

	u32* otherInt = NEW(u32, 5);

	sharedInt = otherInt;

	ASSERT_EQUAL(*sharedInt, 5, "Failed to reassign SharedPointer to regular pointer.");

	END_MEMORY_CHECK();
}

void SharedPointerTests::RunAllTests()
{
	RUN_TEST(PrimitiveSharedPointer);
	RUN_TEST(ObjectSharedPointer);
	RUN_TEST(SharedPointerSharedPointer);
	RUN_TEST(MoveSharedPointerTest);
	RUN_TEST(ReassignNormalPointerTest);
}