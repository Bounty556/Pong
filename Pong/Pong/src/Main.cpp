#include <EntryPoint.h>
#include <Memory/MemoryManager.h>
#include <Structures/Map.h>
#include <Core/String.h>

#include "TestScene.h"

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