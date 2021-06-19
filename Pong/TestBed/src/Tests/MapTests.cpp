#include "MapTests.h"

#include <Defines.h>
#include <Memory/MemoryManager.h>
#include <Structures/Map.h>

#include "TestClass.h"
#include "../TestMacros.h"

void PodMapTest()
{
	START_MEMORY_CHECK();

	Soul::Map<u32, u32> intMap;

	intMap.AddPair(1, 135843);
	intMap.AddPair(2, 7234);
	intMap.AddPair(3, 42734);

	ASSERT_EQUAL(*intMap.GetValue(1), 135843, "Failed to retrieve value from map.");
	ASSERT_EQUAL(*intMap.GetValue(2), 7234, "Failed to retrieve value from map.");
	ASSERT_EQUAL(*intMap.GetValue(3), 42734, "Failed to retrieve value from map.");

	for (u32 i = 4; i < 1000; ++i)
		intMap.AddPair(i, i * 10);

	for (u32 i = 4; i < 1000; ++i)
		ASSERT_EQUAL(*intMap.GetValue(i), i * 10, "Failed to expand map.");

	END_MEMORY_CHECK();
}

void ObjectMapTest()
{
	START_MEMORY_CHECK();

	Soul::Map<u32, TestClass> classMap;

	classMap.AddPair(1, TestClass(1, 2, 3));
	classMap.AddPair(2, TestClass(4, 5, 6));
	classMap.AddPair(3, TestClass(7, 8, 9));

	ASSERT_EQUAL(*classMap.GetValue(1), TestClass(1, 2, 3), "Failed to retrieve value from map.");
	ASSERT_EQUAL(*classMap.GetValue(2), TestClass(4, 5, 6), "Failed to retrieve value from map.");
	ASSERT_EQUAL(*classMap.GetValue(3), TestClass(7, 8, 9), "Failed to retrieve value from map.");

	for (u32 i = 4; i < 1000; ++i)
		classMap.AddPair(i, TestClass(i * 3 - 2, i * 3 - 1, i * 3));

	for (u32 i = 4; i < 1000; ++i)
		ASSERT_EQUAL(*classMap.GetValue(i), TestClass(i * 3 - 2, i * 3 - 1, i * 3), "Failed to expand map.");

	END_MEMORY_CHECK();
}

void MoveMapTest()
{
	START_MEMORY_CHECK();

	Soul::Map<u32, TestClass> classMap;

	classMap.AddPair(1, TestClass(1, 2, 3));
	classMap.AddPair(2, TestClass(4, 5, 6));
	classMap.AddPair(3, TestClass(7, 8, 9));

	Soul::Map<u32, TestClass> classMap2(std::move(classMap));

	ASSERT_EQUAL(*classMap2.GetValue(1), TestClass(1, 2, 3), "Failed to retrieve value from map.");
	ASSERT_EQUAL(*classMap2.GetValue(2), TestClass(4, 5, 6), "Failed to retrieve value from map.");
	ASSERT_EQUAL(*classMap2.GetValue(3), TestClass(7, 8, 9), "Failed to retrieve value from map.");

	Soul::Map<u32, TestClass> classMap3;

	classMap3.AddPair(1, TestClass(1, 2, 3));
	classMap3.AddPair(2, TestClass(4, 5, 6));
	classMap3.AddPair(3, TestClass(7, 8, 9));

	Soul::Map<u32, TestClass> classMap4;

	classMap4 = std::move(classMap3);

	ASSERT_EQUAL(*classMap4.GetValue(1), TestClass(1, 2, 3), "Failed to retrieve value from map.");
	ASSERT_EQUAL(*classMap4.GetValue(2), TestClass(4, 5, 6), "Failed to retrieve value from map.");
	ASSERT_EQUAL(*classMap4.GetValue(3), TestClass(7, 8, 9), "Failed to retrieve value from map.");

	END_MEMORY_CHECK();
}

void CompareMapsTest()
{
	START_MEMORY_CHECK();

	Soul::Map<u32, TestClass> classMap;

	classMap.AddPair(1, TestClass(1, 2, 3));
	classMap.AddPair(2, TestClass(4, 5, 6));
	classMap.AddPair(3, TestClass(7, 8, 9));

	Soul::Map<u32, TestClass>& classMapRef = classMap;

	ASSERT_TRUE(classMap == classMapRef, "Failed to compare maps.");

	END_MEMORY_CHECK();
}

void RemovePairsTest()
{
	START_MEMORY_CHECK();

	Soul::Map<u32, TestClass> classMap;

	classMap.AddPair(1, TestClass(1, 2, 3));
	classMap.AddPair(2, TestClass(4, 5, 6));
	classMap.AddPair(3, TestClass(7, 8, 9));

	classMap.RemovePair(1);
	classMap.RemovePair(2);
	classMap.RemovePair(3);

	ASSERT_EQUAL(classMap.Count(), 0, "Failed to remove pairs.");

	END_MEMORY_CHECK();
}

void ClearTest()
{
	START_MEMORY_CHECK();

	Soul::Map<u32, TestClass> classMap;

	classMap.AddPair(1, TestClass(1, 2, 3));
	classMap.AddPair(2, TestClass(4, 5, 6));
	classMap.AddPair(3, TestClass(7, 8, 9));

	classMap.Clear();

	ASSERT_EQUAL(classMap.Count(), 0, "Failed to remove pairs.");

	END_MEMORY_CHECK();
}

void MapTests::RunAllTests()
{
	RUN_TEST(PodMapTest);
	RUN_TEST(ObjectMapTest);
	RUN_TEST(MoveMapTest);
	RUN_TEST(CompareMapsTest);
	RUN_TEST(RemovePairsTest);
	RUN_TEST(ClearTest);
}