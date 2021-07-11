#include "NodeTests.h"

#include <Memory/MemoryManager.h>
#include <Memory/UniquePointer.h>

#include "../TestMacros.h"
#include "TestNode.h"

void BasicNodes()
{
	START_MEMORY_CHECK();
	
	TestNode node;

	for (u32 i = 0; i < 10; ++i)
		node.AddChild(PARTITION(TestNode));

	ASSERT_EQUAL(node.GetChildren().Count(), 10, "Failed to add children to Node.");

	END_MEMORY_CHECK();
}

void NodeTypes()
{
	START_MEMORY_CHECK();

	TestNode node;

	for (u32 i = 0; i < 10; ++i)
		node.AddChild(PARTITION(TestNode));

	ASSERT_TRUE(node.HasChildOfType("TestNode"), "Failed to detect child types.");
	ASSERT_EQUAL(node.GetChildrenOfType("TestNode").Count(), 10, "Failed to detect child types.");
	END_MEMORY_CHECK();
}

void RemoveNode()
{
	START_MEMORY_CHECK();

	TestNode node;
	Soul::UniquePointer<TestNode> childNode = PARTITION(TestNode);
	node.AddChild(childNode.Raw());

	ASSERT_EQUAL(node.GetChildren().Count(), 1, "Failed to detect child.");
	ASSERT_TRUE(node.HasChildOfType("TestNode"), "Failed to detect child.");
	ASSERT_EQUAL(node.GetChildrenOfType("TestNode").Count(), 1, "Failed to detect child.");

	node.RemoveChild(childNode.Raw());

	ASSERT_EQUAL(node.GetChildren().Count(), 0, "Incorrectly detected child.");
	ASSERT_FALSE(node.HasChildOfType("TestNode"), "Incorrectly detected child.");
	ASSERT_EQUAL(node.GetChildrenOfType("TestNode").Count(), 0, "Incorrectly detected child.");

	END_MEMORY_CHECK();
}

void NodeParent()
{
	START_MEMORY_CHECK();

	TestNode node;
	Soul::UniquePointer<TestNode> childNode = PARTITION(TestNode);
	node.AddChild(childNode.Raw());

	ASSERT_EQUAL(childNode->GetParent(), &node, "Failed to add parent to child.");

	node.RemoveChild(childNode.Raw());

	ASSERT_EQUAL(childNode->GetParent(), nullptr, "Failed to remove parent from child.");

	END_MEMORY_CHECK();
}

void NodeTests::RunAllTests()
{
	RUN_TEST(BasicNodes);
	RUN_TEST(NodeTypes);
	RUN_TEST(RemoveNode);
	RUN_TEST(NodeParent);
}