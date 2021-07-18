#include "PhysicsSystemsTests.h"

#include <Memory/MemoryManager.h>
#include <Physics/PhysicsSystem.h>
#include <Physics/CircleColliderNode.h>
#include <Physics/RectColliderNode.h>
#include <Structures/Vector.h>

#include "../TestMacros.h"

void AddRemoveNodesTest()
{
	START_MEMORY_CHECK();

	Soul::RectColliderNode node(sf::Vector2f(15.0f, 15.0f));
	Soul::RectColliderNode node0(sf::Vector2f(15.0f, 15.0f));

	Soul::Vector<Soul::CollisionInfo> collisions = node.CheckCollisions();

	ASSERT_EQUAL(collisions.Count(), 1, "Failed to detect collisions.");
	ASSERT_EQUAL(collisions[0].node, &node0, "Incorrect node found during collision.");

	END_MEMORY_CHECK();
}

void QuadTreeSplitTest()
{
	START_MEMORY_CHECK();

	Soul::Vector<Soul::RectColliderNode> nodes;

	nodes.Push(Soul::RectColliderNode(sf::Vector2f(15.0f, 15.0f)));
	nodes[0].setPosition(200.0f, 200.0f);
	nodes.Push(Soul::RectColliderNode(sf::Vector2f(15.0f, 15.0f)));
	nodes[1].setPosition(200.0f, 200.0f);

	for (u32 i = 0; i < 15; ++i)
	{
		nodes.Push(Soul::RectColliderNode(sf::Vector2f(15.0f, 15.0f)));
	}

	Soul::PhysicsSystem::Update(0.0f); // Move the nodes

	Soul::Vector<Soul::CollisionInfo> collisions = nodes[0].CheckCollisions();

	ASSERT_EQUAL(collisions.Count(), 1, "Detected an incorrect number of collisions.");
	ASSERT_EQUAL(collisions[0].node, &nodes[1], "Incorrect node found during collision.");

	END_MEMORY_CHECK();
}

void PhysicsSystemsTests::RunAllTests()
{
	RUN_TEST(AddRemoveNodesTest);
	RUN_TEST(QuadTreeSplitTest);
}