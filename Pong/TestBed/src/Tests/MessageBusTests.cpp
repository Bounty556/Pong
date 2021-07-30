#include "MessageBusTests.h"

#include <Core/Listener.h>
#include <Core/MessageBus.h>
#include <Memory/UniquePointer.h>

#include "../TestMacros.h"
#include "TestClass.h"

void BasicListeningTest()
{
	Soul::Listener listener;

	i32 testInt = 10;
	listener.Subscribe("ChangeInt",
		[&](void* data)
		{
			testInt = *(i32*)data;
		});


	START_MEMORY_CHECK();
	
	Soul::MessageBus::QueueMessage("ChangeInt", NEW(i32, 50));
	Soul::MessageBus::PumpQueue(0.0f);

	ASSERT_EQUAL(testInt, 50, "Failed to change int via message.");

	END_MEMORY_CHECK();
}

void ObjectListeningTest()
{
	Soul::Listener listener;

	TestClass testClass(1, 2, 3);

	listener.Subscribe("ChangeValues",
		[&](void* data)
		{
			TestClass* other = (TestClass*)data;
			testClass.m_X = other->m_X;
			testClass.m_Y = other->m_Y;
			testClass.m_Z = other->m_Z;
		});

	START_MEMORY_CHECK();

	Soul::MessageBus::QueueMessage("ChangeValues", NEW(TestClass, 4, 5, 6));
	Soul::MessageBus::PumpQueue(0.0f);

	ASSERT_EQUAL(testClass.m_X, 4, "Failed to change object via message.");
	ASSERT_EQUAL(testClass.m_Y, 5, "Failed to change object via message.");
	ASSERT_EQUAL(testClass.m_Z, 6, "Failed to change object via message.");

	END_MEMORY_CHECK();
}

void MessageBusTests::RunAllTests()
{
	RUN_TEST(BasicListeningTest);
	RUN_TEST(ObjectListeningTest);
}