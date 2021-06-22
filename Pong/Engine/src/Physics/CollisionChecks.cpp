#include "CollisionChecks.h"

#include <Math/Vectors.h>

namespace Soul
{

	CollisionInfo SOULAPI CircleCircleCollision(sf::Vector2f posA, f32 radiusA, sf::Vector2f posB, f32 radiusB)
	{
		CollisionInfo collision = {};
		f32 distance = Math::Distance(posA, posB);

		if (distance <= radiusA + radiusB)
		{
			collision.collided = true;
			sf::Vector2f direction = Math::Normalize(posA - posB);
			direction *= (radiusA + radiusB) - distance;
			collision.correctionVector = direction;
		}

		return collision;
	}

	CollisionInfo SOULAPI CircleRectangleCollision(sf::Vector2f posA, f32 radiusA, sf::Vector2f posB, sf::Vector2f dimensionsB)
	{
		return CollisionInfo{};
	}

	CollisionInfo SOULAPI RectangleRectangleCollision(sf::Vector2f posA, sf::Vector2f dimensionsA, sf::Vector2f posB, sf::Vector2f dimensionsB)
	{
		return CollisionInfo{};
	}
}