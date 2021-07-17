#include "QuadTreeTests.h"

#include <Structures/QuadTree.h>
#include <Structures/Vector.h>
#include <Nodes/Node.h>

#include "../TestMacros.h"

void BasicInsertionTest()
{
	START_MEMORY_CHECK();

	Soul::QuadTree quadTree(0.0f, 0.0f, 100.0f, 100.0f, 4, nullptr);

	sf::Vector2f nodesArea(10.0f, 10.0f);
	Soul::Node node("Node");
	Soul::Node node0("Node");
	Soul::Node node1("Node");

	node.setPosition(0.0f, 0.0f);
	node0.setPosition(0.0f, 0.0f);
	node1.setPosition(0.0f, 0.0f);

	quadTree.Insert(&node, nodesArea);
	quadTree.Insert(&node0, nodesArea);
	quadTree.Insert(&node1, nodesArea);

	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(0.0f, 0.0f), nodesArea).Count(), 3, "Failed to detect colliding nodes.");
	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(11.0f, 11.0f), nodesArea).Count(), 3, "Failed to detect colliding nodes.");

	END_MEMORY_CHECK();
}

void QuadSplitTest()
{
	START_MEMORY_CHECK();

	Soul::QuadTree quadTree(0.0f, 0.0f, 100.0f, 100.0f, 4, nullptr);

	sf::Vector2f nodesArea(10.0f, 10.0f);
	Soul::Node node("Node");
	Soul::Node node0("Node");
	Soul::Node node1("Node");
	Soul::Node node2("Node");
	Soul::Node node3("Node");

	node.setPosition(0.0f, 0.0f);
	node0.setPosition(60.0f, 0.0f);
	node1.setPosition(60.0f, 60.0f);
	node2.setPosition(0.0f, 0.0f);
	node3.setPosition(60.0f, 0.0f);

	quadTree.Insert(&node, nodesArea);
	quadTree.Insert(&node0, nodesArea);
	quadTree.Insert(&node1, nodesArea);
	quadTree.Insert(&node2, nodesArea);
	quadTree.Insert(&node3, nodesArea);

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
	Soul::Node node("Node");
	Soul::Node node0("Node");
	Soul::Node node1("Node");
	Soul::Node node2("Node");
	Soul::Node node3("Node");

	node.setPosition(0.0f, 0.0f);
	node0.setPosition(60.0f, 0.0f);
	node1.setPosition(60.0f, 60.0f);
	node2.setPosition(0.0f, 0.0f);
	node3.setPosition(60.0f, 0.0f);

	quadTree.Insert(&node, nodesArea);
	quadTree.Insert(&node0, nodesArea);
	quadTree.Insert(&node1, nodesArea);
	quadTree.Insert(&node2, nodesArea);
	quadTree.Insert(&node3, nodesArea);

	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(45.0f, 45.0f), nodesArea).Count(), 5, "Failed to detect colliding nodes.");
	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(110.0f, 110.0f), nodesArea).Count(), 0, "Incorrectly detected colliding nodes.");

	END_MEMORY_CHECK();
}

void RemoveQuadNodeTest()
{
	START_MEMORY_CHECK();

	Soul::QuadTree quadTree(0.0f, 0.0f, 100.0f, 100.0f, 4, nullptr);

	sf::Vector2f nodesArea(10.0f, 10.0f);
	Soul::Node node("Node");
	Soul::Node node0("Node");
	Soul::Node node1("Node");
	Soul::Node node2("Node");
	Soul::Node node3("Node");

	node.setPosition(0.0f, 0.0f);
	node0.setPosition(60.0f, 0.0f);
	node1.setPosition(60.0f, 60.0f);
	node2.setPosition(0.0f, 0.0f);
	node3.setPosition(60.0f, 0.0f);

	quadTree.Insert(&node, nodesArea);
	quadTree.Insert(&node0, nodesArea);
	quadTree.Insert(&node1, nodesArea);
	quadTree.Insert(&node2, nodesArea);
	quadTree.Insert(&node3, nodesArea);

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
	Soul::Node node("Node");
	Soul::Node node0("Node");
	Soul::Node node1("Node");
	Soul::Node node2("Node");
	Soul::Node node3("Node");

	node.setPosition(0.0f, 0.0f);
	node0.setPosition(60.0f, 0.0f);
	node1.setPosition(60.0f, 60.0f);
	node2.setPosition(0.0f, 0.0f);
	node3.setPosition(60.0f, 0.0f);

	quadTree.Insert(&node, nodesArea);
	quadTree.Insert(&node0, nodesArea);
	quadTree.Insert(&node1, nodesArea);
	quadTree.Insert(&node2, nodesArea);
	quadTree.Insert(&node3, nodesArea);

	node.setPosition(60.0f, 60.0f);
	node0.setPosition(60.0f, 60.0f);
	node2.setPosition(60.0f, 60.0f);
	node3.setPosition(60.0f, 60.0f);

	quadTree.Move(&node);
	quadTree.Move(&node0);
	quadTree.Move(&node1);
	quadTree.Move(&node2);
	quadTree.Move(&node3);

	ASSERT_EQUAL(quadTree.GetNodes(sf::Vector2f(60.0f, 60.0f), nodesArea).Count(), 5, "Failed to move nodes.");

	END_MEMORY_CHECK();
}

void QuadTreeTests::RunAllTests()
{
	RUN_TEST(BasicInsertionTest);
	RUN_TEST(QuadSplitTest);
	RUN_TEST(QueryMultipleQuadsTest);
	RUN_TEST(RemoveQuadNodeTest);
	RUN_TEST(MoveQuadNodeTest);
}