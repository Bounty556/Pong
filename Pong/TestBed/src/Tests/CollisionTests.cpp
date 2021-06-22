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
	ASSERT_FALSE(collisionInfo2.collided, "Failed to detect circle circle collision.");
}

void CollisionTests::RunAllTests()
{
	RUN_TEST(CircleCircleCollisions);
}