#include "VectorTests.h"

#include <Memory/MemoryManager.h>
#include <Structures/Vector.h>

#include "../TestMacros.h"
#include "TestClass.h"

void VectorOfPrimitives()
{
	START_MEMORY_CHECK();

	Soul::Vector<u32> intVector(255);

	for (u8 i = 0; i < 255; ++i)
		intVector.Push(i);

	ASSERT_EQUAL(intVector.Count(), 255, "Incorrect Vector length.");

	for (u8 i = 0; i < 255; ++i)
		ASSERT_EQUAL(intVector.Pop(), 254 - i,
			"Failed to store primitive in Vector.");

	Soul::Vector<u32> intVector2(255);

	for (u8 i = 0; i < 255; ++i)
		intVector2.Push(i + 1);

	intVector = std::move(intVector2);

	ASSERT_EQUAL(intVector.Count(), 255, "Incorrect Vector length.");

	for (u8 i = 0; i < 255; ++i)
		ASSERT_EQUAL(intVector.Pop(), 255 - i,
			"Failed to move primitive Vector.");

	END_MEMORY_CHECK();
}

void VectorOfObjects()
{
	START_MEMORY_CHECK();

	TestClass fakeClass = { 0, 'a', (u32)1.5f };
	TestClass fakeClass2 = { 1, 'b', (u32)1.8f };

	Soul::Vector<TestClass> classVector(255);

	for (u8 i = 0; i < 255; ++i)
		classVector.Push(fakeClass);

	ASSERT_EQUAL(classVector.Count(), 255, "Incorrect Vector length.");

	for (u8 i = 0; i < 255; ++i)
		ASSERT_EQUAL(classVector.Pop(), fakeClass,
			"Failed to store object in Vector.");

	Soul::Vector<TestClass> classVector2(255);

	for (u8 i = 0; i < 255; ++i)
		classVector2.Push(fakeClass2);

	classVector = std::move(classVector2);

	ASSERT_EQUAL(classVector.Count(), 255, "Incorrect Vector length.");

	for (u8 i = 0; i < 255; ++i)
		ASSERT_EQUAL(classVector.Pop(), fakeClass2,
			"Failed to move object Vector.");

	END_MEMORY_CHECK();
}

void VectorOfVectors()
{
	START_MEMORY_CHECK();

	Soul::Vector<Soul::Vector<u32>> intVectorVector(255);

	for (u8 i = 0; i < 255; ++i)
	{
		Soul::Vector<u32> tempIntVector(255);

		for (u8 j = 0; j < 255; ++j)
			tempIntVector.Push(j);

		intVectorVector.Push(std::move(tempIntVector));
	}

	ASSERT_EQUAL(intVectorVector.Count(), 255, "Incorrect Vector length.");

	Soul::Vector<u32> tempIntVector(intVectorVector.Pop());

	ASSERT_EQUAL(tempIntVector.Count(), 255, "Incorrect Vector length.");

	ASSERT_EQUAL(tempIntVector.Pop(), 254, "Failed to store Vector in Vector.");

	Soul::Vector<Soul::Vector<u32>> intVectorVector2(255);

	for (u8 i = 0; i < 255; ++i)
	{
		Soul::Vector<u32> innerTempVector(255);

		for (u8 j = 0; j < 255; ++j)
			innerTempVector.Push(j + 1);

		intVectorVector2.Push(std::move(innerTempVector));
	}

	intVectorVector = std::move(intVectorVector2);

	tempIntVector = std::move(intVectorVector.Pop());

	ASSERT_EQUAL(tempIntVector.Pop(), 255, "Failed to move Vector of Vectors.");

	END_MEMORY_CHECK();
}

void ResizeVector()
{
	START_MEMORY_CHECK();

	Soul::Vector<u8> smallVector(3);

	for (u8 i = 0; i < 255; ++i)
		smallVector.Push(i);

	ASSERT_EQUAL(smallVector.Count(), 255, "Could not resize Vector");

	for (u8 i = 0; i < 255; ++i)
		ASSERT_EQUAL(smallVector.Pop(), 254 - i, "Incorrect values in resized Vector.");

	Soul::Vector<TestClass> smallVector2(3);
	TestClass fakeClass = { 1, 2, 3 };

	for (u8 i = 0; i < 255; ++i)
		smallVector2.Push(fakeClass);

	for (u8 i = 0; i < 255; ++i)
		ASSERT_EQUAL(smallVector2.Pop(), fakeClass, "Failed to resize Vector of objects.");

	Soul::Vector<Soul::Vector<u32>> smallVector3(3);

	for (u8 i = 0; i < 255; ++i)
	{
		Soul::Vector<u32> tempVector(3);

		for (u32 i = 0; i < 255; ++i)
			tempVector.Push(i);

		smallVector3.Push(std::move(tempVector));
	}

	for (u8 i = 0; i < 255; ++i)
	{
		Soul::Vector<u32> tempVector(smallVector3.Pop());
		ASSERT_EQUAL(tempVector.Pop(), 254, "Failed to resize Vector of Vectors");
	}

	END_MEMORY_CHECK();
}

void RemoveElements()
{
	START_MEMORY_CHECK();

	Soul::Vector<u32> smallVector(5);

	// Test without keeping order
	for (u8 i = 0; i < 5; ++i)
		smallVector.Push(i);

							 // 0 1 2 3 4
	smallVector.RemoveAt(0); // 4 1 2 3
	smallVector.RemoveAt(3); // 4 1 2  

	ASSERT_EQUAL(smallVector.Count(), 3, "Incorrect Vector length after removing elements.");

	ASSERT_EQUAL(smallVector.Pop(), 2, "Incorrect element in Vector.");
	ASSERT_EQUAL(smallVector.Pop(), 1, "Incorrect element in Vector.");
	ASSERT_EQUAL(smallVector.Pop(), 4, "Incorrect element in Vector.");

	// Test with keeping order

	for (u8 i = 0; i < 5; ++i)
		smallVector.Push(i);

							       // 0 1 2 3 4
	smallVector.RemoveAt(0, true); // 1 2 3 4
	smallVector.RemoveAt(3, true); // 1 2 3

	ASSERT_EQUAL(smallVector.Count(), 3, "Incorrect Vector length after removing elements.");

	ASSERT_EQUAL(smallVector.Pop(), 3, "Incorrect element in Vector.");
	ASSERT_EQUAL(smallVector.Pop(), 2, "Incorrect element in Vector.");
	ASSERT_EQUAL(smallVector.Pop(), 1, "Incorrect element in Vector.");

	Soul::Vector<TestClass> smallVector2(5);

	TestClass fakeClass = { 1, 2, 3 };

	for (u8 i = 0; i < 5; ++i)
		smallVector2.Push(fakeClass);

	smallVector2.RemoveAt(0);
	smallVector2.RemoveAt(3);

	ASSERT_EQUAL(smallVector2.Pop(), fakeClass, "Incorrect object in Vector.");
	ASSERT_EQUAL(smallVector2.Pop(), fakeClass, "Incorrect object in Vector.");
	ASSERT_EQUAL(smallVector2.Pop(), fakeClass, "Incorrect object in Vector.");

	Soul::Vector<Soul::Vector<u32>> smallVector3(5);

	// Test without keeping order

	for (u8 i = 0; i < 5; ++i)
	{
		Soul::Vector<u32> tempVector(5);

		for (u8 i = 0; i < 5; ++i)
			tempVector.Push(i);

		tempVector.RemoveAt(i);
		smallVector3.Push(std::move(tempVector));
	}
							  // {4123}{0423}{0143}{0124}{0123}
	smallVector3.RemoveAt(0); // {0123}{0423}{0143}{0124}
	smallVector3.RemoveAt(3); // {0123}{0423}{0143}

	Soul::Vector<u32> oTemp(smallVector3.Pop());
	ASSERT_EQUAL(oTemp.Pop(), 3, "Incorrect Vector removed.");
	ASSERT_EQUAL(oTemp.Pop(), 4, "Incorrect Vector removed.");
	ASSERT_EQUAL(oTemp.Pop(), 1, "Incorrect Vector removed.");
	ASSERT_EQUAL(oTemp.Pop(), 0, "Incorrect Vector removed.");

	smallVector3.Clear();

	// Test with keeping order

	for (u8 i = 0; i < 5; ++i)
	{
		Soul::Vector<u32> tempVector(5);

		for (u8 i = 0; i < 5; ++i)
			tempVector.Push(i);

		tempVector.RemoveAt(i, true);
		smallVector3.Push(std::move(tempVector));
	}
	                                // {1234}{0234}{0134}{0124}{0123}
	smallVector3.RemoveAt(0, true); // {0234}{0134}{0124}{0123}
	smallVector3.RemoveAt(3, true); // {0234}{0134}{0124}

	oTemp = smallVector3.Pop();

	ASSERT_EQUAL(oTemp.Pop(), 4, "Incorrect Vector removed.");
	ASSERT_EQUAL(oTemp.Pop(), 2, "Incorrect Vector removed.");
	ASSERT_EQUAL(oTemp.Pop(), 1, "Incorrect Vector removed.");
	ASSERT_EQUAL(oTemp.Pop(), 0, "Incorrect Vector removed.");
	END_MEMORY_CHECK();
}

void VectorTests::RunAllTests()
{
	RUN_TEST(VectorOfPrimitives);
	RUN_TEST(VectorOfObjects);
	RUN_TEST(VectorOfVectors);
	RUN_TEST(ResizeVector);
	RUN_TEST(RemoveElements);
}