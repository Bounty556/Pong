#include <EntryPoint.h>
#include <Memory/MemoryManager.h>

#include "TestScene.h"

#include <SFML/Window/Context.hpp>

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Pong!"))
	{
		TestScene* scene = PARTITION(TestScene);

		Soul::SetScene(scene);
	}

	Soul::ShutdownEngine();
	return 0;
}