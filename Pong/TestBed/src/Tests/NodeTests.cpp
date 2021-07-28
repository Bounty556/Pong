#include "NodeTests.h"

#include <Memory/MemoryManager.h>
#include <Memory/UniquePointer.h>
#include <Nodes/Node.h>
#include <Structures/Vector.h>

#include "../TestMacros.h"
#include "TestNode.h"

void BasicNodes()
{
	START_MEMORY_CHECK();
	
	TestNode node;

	for (u32 i = 0; i < 10; ++i)
		node.AddChild(NEW(TestNode));

	ASSERT_EQUAL(node.GetChildren().Count(), 10, "Failed to add children to Node.");

	END_MEMORY_CHECK();
}

void NodeTypes()
{
	START_MEMORY_CHECK();

	TestNode node;

	for (u32 i = 0; i < 10; ++i)
		node.AddChild(NEW(TestNode));

	ASSERT_TRUE(node.HasChildOfType("TestNode"), "Failed to detect child types.");
	ASSERT_EQUAL(node.GetChildrenOfType("TestNode").Count(), 10, "Failed to detect child types.");
	END_MEMORY_CHECK();
}

void RemoveNode()
{
	START_MEMORY_CHECK();

	TestNode node;
	Soul::UniquePointer<TestNode> childNode = NEW(TestNode);
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
	Soul::UniquePointer<TestNode> childNode = NEW(TestNode);
	node.AddChild(childNode.Raw());

	ASSERT_EQUAL(childNode->GetParent(), &node, "Failed to add parent to child.");

	node.RemoveChild(childNode.Raw());

	ASSERT_EQUAL(childNode->GetParent(), nullptr, "Failed to remove parent from child.");

	END_MEMORY_CHECK();
}

void ChildrenOfTypeTest()
{
	START_MEMORY_CHECK();

	Soul::Node node0("Node");
	TestNode* node1 = NEW(TestNode);

	node0.AddChild(node1);

	ASSERT_TRUE(node0.HasChildOfType("TestNode"), "Failed to detect child type.");
	ASSERT_TRUE(node1->HasParentOfType("Node"), "Failed to detect parent type.");

	END_MEMORY_CHECK();
}

void VectorOfNodesTest()
{
	START_MEMORY_CHECK();

	Soul::Vector<TestNode> nodeVector(10);

	for (u32 i = 0; i < 10; ++i)
		nodeVector.Push(TestNode());

	END_MEMORY_CHECK();
}

void TagTest()
{
	START_MEMORY_CHECK();

	// Parent has tag
	TestNode node;
	node.AddTag("Tag1");

	ASSERT_TRUE(node.HasTag("Tag1"), "Failed to add tag to node.");
	
	// Parent remove tag
	node.RemoveTag("Tag1");

	ASSERT_FALSE(node.HasTag("Tag1"), "Failed to remove tag from node.");

	// Add tag back in
	node.AddTag("Tag1");

	// Make child with tag
	Soul::UniquePointer<TestNode> childNode(NEW(TestNode));
	childNode->AddTag("Tag2");
	
	// Parent should now have Tag2 as well
	node.AddChild(childNode.Raw());

	ASSERT_TRUE(childNode->HasTag("Tag2"), "Failed to add tag to node.");
	ASSERT_TRUE(childNode->HasTag("Tag1"), "Failed to inherit parent tag.");
	ASSERT_TRUE(node.HasTag("Tag1"), "Failed to add tag to node.");
	ASSERT_TRUE(node.HasTag("Tag2"), "Failed to inherit child tag.");

	node.RemoveChild(childNode.Raw());

	ASSERT_TRUE(node.HasTag("Tag1"), "Incorrectly removed tag.");
	ASSERT_TRUE(node.HasTag("Tag2"), "Incorrectly removed tag.");

	ASSERT_FALSE(childNode->HasTag("Tag2"), "Incorrectly kept tag.");
	ASSERT_FALSE(childNode->HasTag("Tag1"), "Incorrectly kept tag.");

	END_MEMORY_CHECK();
}

void NodeTests::RunAllTests()
{
	RUN_TEST(BasicNodes);
	RUN_TEST(NodeTypes);
	RUN_TEST(RemoveNode);
	RUN_TEST(NodeParent);
	RUN_TEST(ChildrenOfTypeTest);
	RUN_TEST(VectorOfNodesTest);
	RUN_TEST(TagTest);
}