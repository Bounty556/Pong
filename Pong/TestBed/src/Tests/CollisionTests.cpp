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
	// Collided with center outside on upper left
	Soul::CollisionInfo collisionInfo = Soul::CircleAABBCollision(sf::Vector2f(15.0f, 15.0f), 10.0f, sf::Vector2f(20.0f, 20.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_TRUE(collisionInfo.collided, "Failed to detect circle AABB collision.");

	// No collision
	Soul::CollisionInfo collisionInfo2 = Soul::CircleAABBCollision(sf::Vector2f(15.0f, 15.0f), 10.0f, sf::Vector2f(25.0f, 25.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_FALSE(collisionInfo2.collided, "Incorrectly detected circle AABB collision.");

	// Collided with center outside on upper right
	Soul::CollisionInfo collisionInfo3 = Soul::CircleAABBCollision(sf::Vector2f(30.0f, 15.0f), 10.0f, sf::Vector2f(20.0f, 20.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_TRUE(collisionInfo3.collided, "Failed to detect circle AABB collision.");

	// Collided with center outside on lower left
	Soul::CollisionInfo collisionInfo4 = Soul::CircleAABBCollision(sf::Vector2f(15.0f, 30.0f), 10.0f, sf::Vector2f(20.0f, 20.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_TRUE(collisionInfo4.collided, "Failed to detect circle AABB collision.");

	// Collided with center outside on lower right
	Soul::CollisionInfo collisionInfo5 = Soul::CircleAABBCollision(sf::Vector2f(30.0f, 30.0f), 10.0f, sf::Vector2f(20.0f, 20.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_TRUE(collisionInfo5.collided, "Failed to detect circle AABB collision.");

	// Collided with center inside on upper left
	Soul::CollisionInfo collisionInfo6 = Soul::CircleAABBCollision(sf::Vector2f(21.0f, 21.0f), 10.0f, sf::Vector2f(20.0f, 20.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_TRUE(collisionInfo6.collided, "Failed to detect circle AABB collision.");

	// Collided with center inside on upper right
	Soul::CollisionInfo collisionInfo7 = Soul::CircleAABBCollision(sf::Vector2f(24.0f, 21.0f), 10.0f, sf::Vector2f(20.0f, 20.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_TRUE(collisionInfo7.collided, "Failed to detect circle AABB collision.");

	// Collided with center inside on lower left
	Soul::CollisionInfo collisionInfo8 = Soul::CircleAABBCollision(sf::Vector2f(21.0f, 24.0f), 10.0f, sf::Vector2f(20.0f, 20.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_TRUE(collisionInfo8.collided, "Failed to detect circle AABB collision.");

	// Collided with center inside on lower right
	Soul::CollisionInfo collisionInfo9 = Soul::CircleAABBCollision(sf::Vector2f(24.0f, 24.0f), 10.0f, sf::Vector2f(20.0f, 20.0f), sf::Vector2f(5.0f, 5.0f));
	ASSERT_TRUE(collisionInfo9.collided, "Failed to detect circle AABB collision.");
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

void CollisionTests::RunAllTests()
{
	RUN_TEST(CircleCircleCollisions);
	RUN_TEST(CircleAABBCollisions);
	RUN_TEST(AABBAABBCollisions);
}