#include "QueueTests.h"

#include <Defines.h>
#include <Structures/Queue.h>

#include "TestClass.h"
#include "../TestMacros.h"

void PodQueueTest()
{
	START_MEMORY_CHECK();

	Soul::Queue<u32> intQueue;

	for (u32 i = 0; i < 1000; ++i)
		intQueue.Que(i * 10);

	for (u32 i = 0; i < 1000; ++i)
		ASSERT_EQUAL(intQueue.Deque(), i * 10, "Failed to add ints to queue.");

	END_MEMORY_CHECK();
}

void ObjectQueueTest()
{
	START_MEMORY_CHECK();

	Soul::Queue<TestClass> classQueue;

	for (u32 i = 0; i < 1000; ++i)
		classQueue.Que(TestClass(i * 3 - 2, i * 3 - 1, i * 3));

	for (u32 i = 0; i < 1000; ++i)
		ASSERT_EQUAL(classQueue.Deque(), TestClass(i * 3 - 2, i * 3 - 1, i * 3), "Failed to add objects to queue.");

	END_MEMORY_CHECK();
}

void MoveQueueTest()
{
	START_MEMORY_CHECK();

	Soul::Queue<TestClass> classQueue;

	classQueue.Que(TestClass(1, 2, 3));
	classQueue.Que(TestClass(4, 5, 6));
	classQueue.Que(TestClass(7, 8, 9));

	Soul::Queue<TestClass> classQueue2(std::move(classQueue));

	ASSERT_EQUAL(classQueue2.Deque(), TestClass(1, 2, 3), "Failed to move queue.");
	ASSERT_EQUAL(classQueue2.Deque(), TestClass(4, 5, 6), "Failed to move queue.");
	ASSERT_EQUAL(classQueue2.Deque(), TestClass(7, 8, 9), "Failed to move queue.");

	Soul::Queue<TestClass> classQueue3;

	classQueue3.Que(TestClass(1, 2, 3));
	classQueue3.Que(TestClass(4, 5, 6));
	classQueue3.Que(TestClass(7, 8, 9));

	Soul::Queue<TestClass> classQueue4;
	classQueue4 = std::move(classQueue3);

	ASSERT_EQUAL(classQueue4.Deque(), TestClass(1, 2, 3), "Failed to move queue.");
	ASSERT_EQUAL(classQueue4.Deque(), TestClass(4, 5, 6), "Failed to move queue.");
	ASSERT_EQUAL(classQueue4.Deque(), TestClass(7, 8, 9), "Failed to move queue.");

	END_MEMORY_CHECK();
}

void PeekTest()
{
	START_MEMORY_CHECK();

	Soul::Queue<u32> classQueue;

	classQueue.Que(3);
	classQueue.Que(6);
	classQueue.Que(9);

	ASSERT_EQUAL(classQueue.PeekEnd(), 9, "Failed to peek at end of queue.");
	ASSERT_EQUAL(classQueue.Peek(), 3, "Failed to peek at end of queue.");

	classQueue.Deque();
	
	ASSERT_EQUAL(classQueue.PeekEnd(), 9, "Failed to peek at end of queue.");
	ASSERT_EQUAL(classQueue.Peek(), 6, "Failed to peek at end of queue.");

	classQueue.Deque();

	ASSERT_EQUAL(classQueue.PeekEnd(), 9, "Failed to peek at end of queue.");
	ASSERT_EQUAL(classQueue.Peek(), 9, "Failed to peek at end of queue.");

	END_MEMORY_CHECK();
}

void QueueTests::RunAllTests()
{
	RUN_TEST(PodQueueTest);
	RUN_TEST(ObjectQueueTest);
	RUN_TEST(MoveQueueTest);
	RUN_TEST(PeekTest);
}