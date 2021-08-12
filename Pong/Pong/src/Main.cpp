#include <Engine.h>
#include <Memory/MemoryManager.h>
#include <Core/String.h>

#include "Scenes/FieldScene.h"
#include "Scenes/MainMenuScene.h"

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Pong!"))
	{
		MainMenuScene* scene = NEW(MainMenuScene);

		Soul::SetScene(scene);
	}

	Soul::ShutdownEngine();
	return 0;
}