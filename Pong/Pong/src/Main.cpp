#include <EntryPoint.h>
#include <Memory/MemoryManager.h>
#include <Structures/Vector.h>
#include <Core/String.h>

#include "TestScene.h"

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Pong!"))
	{
		Soul::Vector<Soul::String> stringVector;

		for (u8 i = 0; i < 15; ++i)
		{
			stringVector.Push(Soul::String::IntToString(i));
		}

		stringVector.Clear();

		for (u8 i = 0; i < 15; ++i)
		{
			stringVector.Push(Soul::String::IntToString(i));
		}

		for (u8 i = 0; i < 15; ++i)
		{
			LOG_DEBUG("%s", stringVector[i].GetCString());
		}

		TestScene* scene = PARTITION(TestScene);

		Soul::SetScene(scene);
	}

	Soul::ShutdownEngine();
	return 0;
}