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

void ManySubscriptionsTest()
{
	Soul::Listener listener;

	i32 testInt = 10;
	listener.Subscribe("ChangeIntThing",
		[&](void* data)
		{
			testInt = 0;
		});
	listener.Subscribe("ChangeIntThat",
		[&](void* data)
		{
			testInt = 1;
		});
	listener.Subscribe("ChangeIntDoes",
		[&](void* data)
		{
			testInt = 2;
		});
	listener.Subscribe("ChangeIntStuff",
		[&](void* data)
		{
			testInt = 3;
		});
	listener.Subscribe("ChangeIntBut",
		[&](void* data)
		{
			testInt = 4;
		});
	listener.Subscribe("ChangeIntWhat",
		[&](void* data)
		{
			testInt = 5;
		});
	listener.Subscribe("ChangeIntElse?",
		[&](void* data)
		{
			testInt = 6;
		});


	START_MEMORY_CHECK();

	Soul::MessageBus::QueueMessage("ChangeIntThing");
	Soul::MessageBus::PumpQueue(0.0f);
	ASSERT_EQUAL(testInt, 0, "Failed to change int via message.");

	Soul::MessageBus::QueueMessage("ChangeIntThat");
	Soul::MessageBus::PumpQueue(0.0f);
	ASSERT_EQUAL(testInt, 1, "Failed to change int via message.");

	Soul::MessageBus::QueueMessage("ChangeIntDoes");
	Soul::MessageBus::PumpQueue(0.0f);
	ASSERT_EQUAL(testInt, 2, "Failed to change int via message.");

	Soul::MessageBus::QueueMessage("ChangeIntStuff");
	Soul::MessageBus::PumpQueue(0.0f);
	ASSERT_EQUAL(testInt, 3, "Failed to change int via message.");

	Soul::MessageBus::QueueMessage("ChangeIntBut");
	Soul::MessageBus::PumpQueue(0.0f);
	ASSERT_EQUAL(testInt, 4, "Failed to change int via message.");

	Soul::MessageBus::QueueMessage("ChangeIntWhat");
	Soul::MessageBus::PumpQueue(0.0f);
	ASSERT_EQUAL(testInt, 5, "Failed to change int via message.");

	Soul::MessageBus::QueueMessage("ChangeIntElse?");
	Soul::MessageBus::PumpQueue(0.0f);
	ASSERT_EQUAL(testInt, 6, "Failed to change int via message.");

	END_MEMORY_CHECK();
}

void MessageBusTests::RunAllTests()
{
	RUN_TEST(BasicListeningTest);
	RUN_TEST(ObjectListeningTest);
	RUN_TEST(ManySubscriptionsTest);
}