#include <EntryPoint.h>
#include <Core/String.h>
#include <Memory/MemoryManager.h>

#include "TestScene.h"

#include <SFML/Window/Context.hpp>

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Pong!"))
	{
		Soul::String testString1 = "Hello!";
		Soul::String testString(std::move(testString1));

		LOG_DEBUG(testString.GetCString());

		TestScene* scene = PARTITION(TestScene);

		Soul::SetScene(scene);
	}

	Soul::ShutdownEngine();
	return 0;
}