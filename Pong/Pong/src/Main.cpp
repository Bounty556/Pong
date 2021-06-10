#include <EntryPoint.h>
#include <Memory/MemoryManager.h>
#include <Core/Listener.h>
#include <Core/MessageBus.h>
#include <Core/String.h>

#include "TestScene.h"

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Pong!"))
	{
		// Test for immediate messages
		int testInt = 1;
		Soul::String testString = "Testing!";

		Soul::Listener listener;

		listener.Subscribe("TestMessage", [&](void* data) { testInt = 2; });
		listener.Subscribe("TestMessage2", [&](void* data) { testString = (const char*)(data); });

		const char* testCString = "This works!";

		Soul::MessageBus::ImmediateMessage("TestMessage", nullptr);
		Soul::MessageBus::ImmediateMessage("TestMessage2", (void*)testCString);

		LOG_DEBUG("%d", testInt);
		LOG_DEBUG("%s", testString);

		TestScene* scene = PARTITION(TestScene);

		Soul::SetScene(scene);
	}

	Soul::ShutdownEngine();
	return 0;
}