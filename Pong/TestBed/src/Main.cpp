#include "TestMacros.h"

#include <Engine.h>
#include <Memory/MemoryManager.h>

#include "TestScene.h"

#include "Tests/CollisionTests.h"
#include "Tests/MathTests.h"
#include "Tests/MapTests.h"
#include "Tests/MessageBusTests.h"
#include "Tests/NodeTests.h"
#include "Tests/PhysicsSystemTests.h"
#include "Tests/QuadTreeTests.h"
#include "Tests/QueueTests.h"
#include "Tests/StackTests.h"
#include "Tests/StringTests.h"
#include "Tests/UniquePointerTests.h"
#include "Tests/VectorTests.h"

void RunTestSuite(ITestSuite* suite)
{
	suite->RunAllTests();
	delete suite;
}

void RunAllTestSuites()
{
	CREATE_TEST_SUITE(CollisionTests);
	CREATE_TEST_SUITE(MathTests);
	CREATE_TEST_SUITE(MapTests);
	CREATE_TEST_SUITE(MessageBusTests);
	CREATE_TEST_SUITE(NodeTests);
	CREATE_TEST_SUITE(PhysicsSystemTests);
	CREATE_TEST_SUITE(QuadTreeTests);
	CREATE_TEST_SUITE(QueueTests);
	CREATE_TEST_SUITE(StackTests);
	CREATE_TEST_SUITE(StringTests);
	CREATE_TEST_SUITE(UniquePointerTests);
	CREATE_TEST_SUITE(VectorTests);
}

int main()
{
	if (Soul::InitializeEngine(1280, 720, "Soul Tests"))
	{
		RunAllTestSuites();
		LOG_INFO("All tests finished.");

		TestScene* scene = NEW(TestScene);
		Soul::SetScene(scene);
	}
	Soul::ShutdownEngine();
	return 0;
}