#include <EntryPoint.h>
#include <Memory/MemoryManager.h>
#include <Core/String.h>
#include <IO/TextFileReader.h>

#include "TestScene.h"

// TODO: unsubscribe listeners on destroy

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Pong!"))
	{
		{
			Soul::TextFileReader fileReader;
			fileReader.ReadFile("res/guestControls.controls");
			fileReader.ReadFile("res/newFile.txt");

			fileReader.GetString() = "Ayo the pizza here";
			fileReader.WriteToCurrentFile();
		}

		Soul::TextFileReader fileReader("res/newFile.txt");

		LOG_INFO("%s", fileReader.GetCString());

		TestScene* scene = PARTITION(TestScene);

		Soul::SetScene(scene);
	}

	Soul::ShutdownEngine();
	return 0;
}