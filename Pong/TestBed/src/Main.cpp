#include "TestMacros.h"

#include <EntryPoint.h>
#include <Memory/MemoryManager.h>

#include "TestScene.h"

#include "Tests/MessageBusTests.h"

void RunTestSuite(ITestSuite* suite)
{
	suite->RunAllTests();
	delete suite;
}

void RunAllTestSuites()
{
	CREATE_TEST_SUITE(MessageBusTests);
}

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Soul Tests"))
	{
		RunAllTestSuites();
		LOG_INFO("All tests finished.");

		TestScene* scene = PARTITION(TestScene);
		Soul::SetScene(scene);
	}
	Soul::ShutdownEngine();
	return 0;
}