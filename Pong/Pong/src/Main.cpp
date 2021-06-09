#include <EntryPoint.h>
#include <Memory/MemoryManager.h>
#include <Structures/Map.h>
#include <Core/String.h>

#include "TestScene.h"

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Pong!"))
	{
		Soul::Map<Soul::String, Soul::String> stringMap;

		Soul::String keyTest = "Key test";
		Soul::String keyTest1 = "Key test 2";
		Soul::String keyTest2 = "Key test 3";
		Soul::String keyTest3 = "Key test 4";

		stringMap.AddPair(keyTest, "Hello");
		stringMap.AddPair(keyTest1, "I");
		stringMap.AddPair(keyTest2, "Am");
		stringMap.AddPair(keyTest3, "stringMap");

		LOG_DEBUG("%d pairs", stringMap.Count());

		stringMap.Clear();

		LOG_DEBUG("%d pairs after clearing", stringMap.Count());

		stringMap.AddPair(keyTest, "You");
		stringMap.AddPair(keyTest1, "Are");
		stringMap.AddPair(keyTest2, "Not");
		stringMap.AddPair(keyTest3, "Dumb");

		stringMap.RemovePair(keyTest2);

		LOG_DEBUG("%s %s %s", stringMap.GetValue(keyTest)->GetCString
			(), stringMap.GetValue(keyTest1)->GetCString(), stringMap.GetValue(keyTest3)->GetCString());

		TestScene* scene = PARTITION(TestScene);

		Soul::SetScene(scene);
	}

	Soul::ShutdownEngine();
	return 0;
}