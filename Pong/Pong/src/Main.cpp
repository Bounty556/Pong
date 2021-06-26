#include <Engine.h>
#include <Memory/MemoryManager.h>
#include <Core/String.h>

#include "Scenes/FieldScene.h"

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Pong!"))
	{
		FieldScene* scene = PARTITION(FieldScene);

		Soul::SetScene(scene);
	}

	Soul::ShutdownEngine();
	return 0;
}