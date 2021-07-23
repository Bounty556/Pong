#include "QuadTreeTests.h"

#include <Structures/QuadTree.h>
#include <Structures/Vector.h>
#include <Physics/RectColliderNode.h>
#include <Physics/PhysicsSystem.h>

#include "../TestMacros.h"

void BasicInsertionTest()
{
	START_MEMORY_CHECK();

	Soul::QuadTree quadTree(0.0f, 0.0f, 100.0f, 100.0f, 4, nullptr);

	sf::Vector2f nodesArea(10.0f, 10.0f);
	Soul::RectColliderNode node(nodesArea);
	Soul::RectColliderNode node0(nodesArea);
	Soul::RectColliderNode node1(nodesArea);

	node.setPosition(0.0f, 0.0f);
	node0.setPosition(0.0f, 0.0f);
	node1.setPosition(0.0f, 0.0f);

	quadTree.Insert(&node);
	quadTree.Insert(&node0);
	quadTree.Insert(&node1);

	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(0.0f, 0.0f), nodesArea).Count(), 3, "Failed to detect colliding nodes.");
	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(11.0f, 11.0f), nodesArea).Count(), 3, "Failed to detect colliding nodes.");

	END_MEMORY_CHECK();
}

void QuadSplitTest()
{
	START_MEMORY_CHECK();

	Soul::QuadTree quadTree(0.0f, 0.0f, 100.0f, 100.0f, 4, nullptr);

	sf::Vector2f nodesArea(10.0f, 10.0f);
	Soul::RectColliderNode node (nodesArea);
	Soul::RectColliderNode node0(nodesArea);
	Soul::RectColliderNode node1(nodesArea);
	Soul::RectColliderNode node2(nodesArea);
	Soul::RectColliderNode node3(nodesArea);

	node.setPosition(0.0f, 0.0f);
	node0.setPosition(60.0f, 0.0f);
	node1.setPosition(60.0f, 60.0f);
	node2.setPosition(0.0f, 0.0f);
	node3.setPosition(60.0f, 0.0f);

	quadTree.Insert(&node);
	quadTree.Insert(&node0);
	quadTree.Insert(&node1);
	quadTree.Insert(&node2);
	quadTree.Insert(&node3);

	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(0.0f, 0.0f), nodesArea).Count(), 2, "Failed to detect colliding nodes.");
	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(60.0f, 0.0f), nodesArea).Count(), 2, "Failed to detect colliding nodes.");
	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(60.0f, 60.0f), nodesArea).Count(), 1, "Failed to detect colliding nodes.");
	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(0.0f, 60.0f), nodesArea).Count(), 0, "Incorrectly detected colliding nodes.");

	END_MEMORY_CHECK();
}

void QueryMultipleQuadsTest()
{
	START_MEMORY_CHECK();

	Soul::QuadTree quadTree(0.0f, 0.0f, 100.0f, 100.0f, 4, nullptr);

	sf::Vector2f nodesArea(10.0f, 10.0f);
	Soul::RectColliderNode node(nodesArea);
	Soul::RectColliderNode node0(nodesArea);
	Soul::RectColliderNode node1(nodesArea);
	Soul::RectColliderNode node2(nodesArea);
	Soul::RectColliderNode node3(nodesArea);

	node.setPosition(0.0f, 0.0f);
	node0.setPosition(60.0f, 0.0f);
	node1.setPosition(60.0f, 60.0f);
	node2.setPosition(0.0f, 0.0f);
	node3.setPosition(60.0f, 0.0f);

	quadTree.Insert(&node);
	quadTree.Insert(&node0);
	quadTree.Insert(&node1);
	quadTree.Insert(&node2);
	quadTree.Insert(&node3);

	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(0.0f, 0.0f), nodesArea).Count(), 2, "Failed to detect colliding nodes.");
	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(45.0f, 45.0f), nodesArea).Count(), 5, "Failed to detect colliding nodes.");
	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(110.0f, 110.0f), nodesArea).Count(), 0, "Incorrectly detected colliding nodes.");

	END_MEMORY_CHECK();
}

void RemoveQuadNodeTest()
{
	START_MEMORY_CHECK();

	Soul::QuadTree quadTree(0.0f, 0.0f, 100.0f, 100.0f, 4, nullptr);

	sf::Vector2f nodesArea(10.0f, 10.0f);
	Soul::RectColliderNode node(nodesArea);
	Soul::RectColliderNode node0(nodesArea);
	Soul::RectColliderNode node1(nodesArea);
	Soul::RectColliderNode node2(nodesArea);
	Soul::RectColliderNode node3(nodesArea);

	node.setPosition(0.0f, 0.0f);
	node0.setPosition(60.0f, 0.0f);
	node1.setPosition(60.0f, 60.0f);
	node2.setPosition(0.0f, 0.0f);
	node3.setPosition(60.0f, 0.0f);

	quadTree.Insert(&node);
	quadTree.Insert(&node0);
	quadTree.Insert(&node1);
	quadTree.Insert(&node2);
	quadTree.Insert(&node3);

	quadTree.Remove(&node);
	quadTree.Remove(&node0);
	quadTree.Remove(&node1);
	quadTree.Remove(&node2);
	quadTree.Remove(&node3);

	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(45.0f, 45.0f), nodesArea).Count(), 0, "Failed to remove nodes.");

	END_MEMORY_CHECK();
}

void MoveQuadNodeTest()
{
	START_MEMORY_CHECK();

	Soul::QuadTree quadTree(0.0f, 0.0f, 100.0f, 100.0f, 4, nullptr);

	sf::Vector2f nodesArea(10.0f, 10.0f);
	Soul::RectColliderNode node(nodesArea);
	Soul::RectColliderNode node0(nodesArea);
	Soul::RectColliderNode node1(nodesArea);
	Soul::RectColliderNode node2(nodesArea);
	Soul::RectColliderNode node3(nodesArea);

	node.setPosition(0.0f, 0.0f);
	node0.setPosition(60.0f, 0.0f);
	node1.setPosition(60.0f, 60.0f);
	node2.setPosition(0.0f, 0.0f);
	node3.setPosition(60.0f, 0.0f);

	quadTree.Insert(&node);
	quadTree.Insert(&node0);
	quadTree.Insert(&node1);
	quadTree.Insert(&node2);
	quadTree.Insert(&node3);

	node.setPosition(60.0f, 60.0f);
	node0.setPosition(60.0f, 60.0f);
	node2.setPosition(60.0f, 60.0f);
	node3.setPosition(60.0f, 60.0f);

	quadTree.Move();

	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(60.0f, 60.0f), nodesArea).Count(), 5, "Failed to move nodes.");

	END_MEMORY_CHECK();
}

void FlattenTreeTest()
{
	START_MEMORY_CHECK();

	Soul::QuadTree quadTree(0.0f, 0.0f, 100.0f, 100.0f, 4, nullptr);

	sf::Vector2f nodesArea(49.0f, 49.0f);
	Soul::RectColliderNode node(nodesArea);
	Soul::RectColliderNode node0(nodesArea);
	Soul::RectColliderNode node1(nodesArea);
	Soul::RectColliderNode node2(nodesArea);
	Soul::RectColliderNode node3(nodesArea);

	quadTree.Insert(&node);
	quadTree.Insert(&node0);
	quadTree.Insert(&node1);
	quadTree.Insert(&node2);
	quadTree.Insert(&node3);

	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(60.0f, 60.0f), nodesArea).Count(), 0, "Incorrectly found nodes.");

	quadTree.Remove(&node);
	quadTree.Remove(&node0);
	
	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(0.0f, 0.0f), nodesArea).Count(), 3, "Failed to remove nodes.");

	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(60.0f, 60.0f), nodesArea).Count(), 3, "Failed to flatten tree.");

	END_MEMORY_CHECK();
}

void QuadTreeTests::RunAllTests()
{
	Soul::PhysicsSystem::TogglePhysics();
	RUN_TEST(BasicInsertionTest);
	RUN_TEST(QuadSplitTest);
	RUN_TEST(QueryMultipleQuadsTest);
	RUN_TEST(RemoveQuadNodeTest);
	RUN_TEST(MoveQuadNodeTest);
	RUN_TEST(FlattenTreeTest);
	Soul::PhysicsSystem::TogglePhysics();
}