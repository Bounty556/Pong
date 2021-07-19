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

	Soul::RectColliderNode node0(sf::Vector2f(15.0f, 15.0f));
	node0.setPosition(200.0f, 200.0f);
	Soul::RectColliderNode node1(sf::Vector2f(15.0f, 15.0f));
	node1.setPosition(200.0f, 200.0f);

	Soul::RectColliderNode node2(sf::Vector2f(15.0f, 15.0f));
	Soul::RectColliderNode node3(sf::Vector2f(15.0f, 15.0f));
	Soul::RectColliderNode node4(sf::Vector2f(15.0f, 15.0f));
	Soul::RectColliderNode node5(sf::Vector2f(15.0f, 15.0f));
	Soul::RectColliderNode node6(sf::Vector2f(15.0f, 15.0f));
	Soul::RectColliderNode node7(sf::Vector2f(15.0f, 15.0f));
	Soul::RectColliderNode node8(sf::Vector2f(15.0f, 15.0f));
	Soul::RectColliderNode node9(sf::Vector2f(15.0f, 15.0f));

	Soul::PhysicsSystem::Update(0.0f); // Move the nodes

	Soul::Vector<Soul::CollisionInfo> collisions = node0.CheckCollisions();

	ASSERT_EQUAL(collisions.Count(), 1, "Detected an incorrect number of collisions.");
	ASSERT_EQUAL(collisions[0].node, &node1, "Incorrect node found during collision.");

	Soul::Vector<Soul::CollisionInfo> collisions2 = node2.CheckCollisions();
	
	ASSERT_EQUAL(collisions2.Count(), 7, "Detected an incorrect number of collisions.");

	END_MEMORY_CHECK();
}

void CircleCircleTest()
{
	START_MEMORY_CHECK();

	Soul::CircleColliderNode node0(5.0f);
	Soul::CircleColliderNode node1(0.0001f);

	Soul::Vector<Soul::CollisionInfo> collisions = node0.CheckCollisions();

	ASSERT_EQUAL(collisions.Count(), 0, "Incorrectly detected collisions.");

	END_MEMORY_CHECK();
}

void CircleRectTest()
{
	START_MEMORY_CHECK();

	Soul::CircleColliderNode node0(5.0f);
	Soul::RectColliderNode node1(sf::Vector2f(5.0f, 5.0f));
	node1.setPosition(9.9f, 9.9f);

	Soul::PhysicsSystem::Update(0.0f);
	Soul::Vector<Soul::CollisionInfo> collisions = node0.CheckCollisions();
	ASSERT_EQUAL(collisions.Count(), 0, "Incorrectly detected collisions.");

	node1.setPosition(9.9f, 5.0f);

	Soul::PhysicsSystem::Update(0.0f);
	Soul::Vector<Soul::CollisionInfo> collisions2 = node0.CheckCollisions();
	ASSERT_EQUAL(collisions2.Count(), 1, "Incorrectly detected collisions.");
	ASSERT_EQUAL(collisions2[0].node, &node1, "Incorrectly detected collisions.");

	END_MEMORY_CHECK();
}

void RectRectTest()
{
	START_MEMORY_CHECK();

	Soul::RectColliderNode node0(sf::Vector2f(5.0f, 5.0f));
	Soul::RectColliderNode node1(sf::Vector2f(15.0f, 15.0f));
	Soul::RectColliderNode node2(sf::Vector2f(100.0f, 100.0f));

	node1.setPosition(95.0f, 95.0f);

	Soul::Vector<Soul::CollisionInfo> collisions0 = node0.CheckCollisions();

	ASSERT_EQUAL(collisions0.Count(), 1, "Failed to detect rectangle collisions.");
	ASSERT_EQUAL(collisions0[0].node, &node2, "Wrong node collided.");

	Soul::Vector<Soul::CollisionInfo> collisions1 = node1.CheckCollisions();

	ASSERT_EQUAL(collisions1.Count(), 1, "Failed to detect rectangle collisions.");
	ASSERT_EQUAL(collisions1[0].node, &node2, "Wrong node collided.");

	Soul::Vector<Soul::CollisionInfo> collisions2 = node2.CheckCollisions();

	ASSERT_EQUAL(collisions2.Count(), 2, "Failed to detect rectangle collisions.");

	END_MEMORY_CHECK();
}

void PhysicsSystemsTests::RunAllTests()
{
	RUN_TEST(AddRemoveNodesTest);
	RUN_TEST(QuadTreeSplitTest);
	RUN_TEST(CircleCircleTest);
	RUN_TEST(CircleRectTest);
	RUN_TEST(RectRectTest);
}