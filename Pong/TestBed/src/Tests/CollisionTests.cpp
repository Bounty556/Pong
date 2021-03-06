#include "CollisionTests.h"

#include <Defines.h>
#include <Physics/CollisionChecks.h>

#include "../TestMacros.h"

void CircleCircleCollisions()
{
	Soul::CollisionInfo collisionInfo = Soul::CircleCircleCollision(sf::Vector2f(15.0f, 15.0f), 10.0f, sf::Vector2f(20.0f, 20.0f), 5.0f);
	ASSERT_CLOSE(collisionInfo.correctionVector.x, 5.6066f, 0.0001f, "Failed to calculate correction vector.");
	ASSERT_CLOSE(collisionInfo.correctionVector.y, 5.6066f, 0.0001f, "Failed to calculate correction vector.");
	ASSERT_TRUE(collisionInfo.collided, "Failed to detect circle circle collision.");

	Soul::CollisionInfo collisionInfo2 = Soul::CircleCircleCollision(sf::Vector2f(15.0f, 15.0f), 2.0f, sf::Vector2f(20.0f, 20.0f), 2.0f);
	ASSERT_FALSE(collisionInfo2.collided, "Incorrectly detected circle circle collision.");
}

void CircleAABBCollisions()
{
	Soul::CollisionInfo collisionInfo = Soul::CircleAABBCollision(sf::Vector2f(15.0f, 15.0f), 10.0f, sf::Vector2f(20.0f, 20.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_TRUE(collisionInfo.collided, "Failed to detect circle AABB collision.");

	Soul::CollisionInfo collisionInfo2 = Soul::CircleAABBCollision(sf::Vector2f(15.0f, 15.0f), 5.0f, sf::Vector2f(25.0f, 25.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_FALSE(collisionInfo2.collided, "Incorrectly detected circle AABB collision.");

	Soul::CollisionInfo collisionInfo3 = Soul::CircleAABBCollision(sf::Vector2f(25.0f, 15.0f), 10.0f, sf::Vector2f(20.0f, 20.0f), sf::Vector2f(10.0f, 5.0f));
	ASSERT_TRUE(collisionInfo3.collided, "Failed to detect circle AABB collision.");

	Soul::CollisionInfo collisionInfo4 = Soul::CircleAABBCollision(sf::Vector2f(15.0f, 20.0f), 10.0f, sf::Vector2f(20.0f, 20.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_TRUE(collisionInfo4.collided, "Failed to detect circle AABB collision.");

	Soul::CollisionInfo collisionInfo5 = Soul::CircleAABBCollision(sf::Vector2f(22.5f, 22.5f), 10.0f, sf::Vector2f(21.0f, 21.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_TRUE(collisionInfo5.collided, "Failed to detect circle AABB collision.");

	Soul::CollisionInfo collisionInfo6 = Soul::CircleAABBCollision(sf::Vector2f(21.0f, 21.0f), 10.0f, sf::Vector2f(20.0f, 20.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_TRUE(collisionInfo6.collided, "Failed to detect circle AABB collision.");
}

void AABBAABBCollisions()
{
	Soul::CollisionInfo collisionInfo = Soul::AABBAABBCollision(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(10.0f, 10.0f), sf::Vector2f(6.0f, 5.0f), sf::Vector2f(10.0f, 10.0f));
	ASSERT_TRUE(collisionInfo.collided, "Failed to detect AABB AABB collision.");
	ASSERT_CLOSE(collisionInfo.correctionVector.x, -4.0f, 0.001f, "Calculated incorrect correction vector.");

	Soul::CollisionInfo collisionInfo2 = Soul::AABBAABBCollision(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(2.0f, 2.0f), sf::Vector2f(5.0f, 5.0f), sf::Vector2f(10.0f, 10.0f));
	ASSERT_FALSE(collisionInfo2.collided, "Incorrectly detected AABB AABB collision.");

	Soul::CollisionInfo collisionInfo3 = Soul::AABBAABBCollision(sf::Vector2f(10.0f, 10.0f), sf::Vector2f(10.0f, 10.0f), sf::Vector2f(6.0f, 5.0f), sf::Vector2f(10.0f, 10.0f));
	ASSERT_TRUE(collisionInfo3.collided, "Failed to detect AABB AABB collision.");
	ASSERT_CLOSE(collisionInfo3.correctionVector.y, 5.0f, 0.001f, "Calculated incorrect correction vector.");
}

void AABBIsInAABBTest()
{
	ASSERT_TRUE(Soul::AABBIsInAABB(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(5.0f, 5.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(5.1f, 5.1f)), "Failed to correctly detect AABB in AABB.");
	ASSERT_TRUE(Soul::AABBIsInAABB(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(5.0f, 5.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(5.0f, 5.0f)), "Failed to correctly detect AABB in AABB.");
	ASSERT_FALSE(Soul::AABBIsInAABB(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(5.2f, 5.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(5.1f, 5.1f)), "Incorrectly detected AABB in AABB.");
	ASSERT_FALSE(Soul::AABBIsInAABB(sf::Vector2f(0.2f, 0.0f), sf::Vector2f(5.0f, 5.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(5.1f, 5.1f)), "Incorrectly detected AABB in AABB.");
	ASSERT_FALSE(Soul::AABBIsInAABB(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(5.0f, 5.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(4.9f, 5.1f)), "Incorrectly detected AABB in AABB.");
}

void CollisionTests::RunAllTests()
{
	RUN_TEST(CircleCircleCollisions);
	RUN_TEST(CircleAABBCollisions);
	RUN_TEST(AABBAABBCollisions);
	RUN_TEST(AABBIsInAABBTest);
}