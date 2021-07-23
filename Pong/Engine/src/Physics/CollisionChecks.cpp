#include "CollisionChecks.h"

#include <Core/String.h>
#include <Math/Functions.h>
#include <Math/Vectors.h>
#include <Physics/IColliderNode.h>
#include <Physics/RectColliderNode.h>
#include <Physics/CircleColliderNode.h>

namespace Soul
{

	CollisionInfo SOULAPI CircleCircleCollision(sf::Vector2f posA, f32 radiusA, sf::Vector2f posB, f32 radiusB)
	{
		posA += sf::Vector2f(radiusA, radiusA);
		posB += sf::Vector2f(radiusB, radiusB);

		CollisionInfo collision = {};
		f32 distance = Math::Distance(posA, posB);

		if (distance <= radiusA + radiusB)
		{
			collision.collided = true;
			sf::Vector2f direction = Math::Normalize(posA - posB);
			collision.fromCenterOfMass = direction;
			direction *= (radiusA + radiusB) - distance;
			collision.correctionVector = direction;
		}

		return collision;
	}

	CollisionInfo SOULAPI CircleAABBCollision(sf::Vector2f posA, f32 radiusA, sf::Vector2f posB, sf::Vector2f dimensionsB)
	{
		posA += sf::Vector2f(radiusA, radiusA);

		CollisionInfo collision = {};

		sf::Vector2f closest(Math::Clamp(posA.x, posB.x, posB.x + dimensionsB.x),
			Math::Clamp(posA.y, posB.y, posB.y + dimensionsB.y));
		f32 distance = Math::Distance(posA, closest);

		if (distance < radiusA)
		{
			collision.collided = true;
			sf::Vector2f direction = Math::Normalize(posA - closest);
			collision.correctionVector = direction * distance;
			collision.fromCenterOfMass = Math::Normalize(posA - (posB + dimensionsB * 0.5f));
		}

		return collision;
	}

	CollisionInfo SOULAPI AABBAABBCollision(sf::Vector2f posA, sf::Vector2f dimensionsA, sf::Vector2f posB, sf::Vector2f dimensionsB)
	{
		CollisionInfo collision = {};

		if (posA.x >= posB.x - dimensionsA.x && posA.x <= posB.x + dimensionsB.x &&
			posA.y >= posB.y - dimensionsA.y && posA.y <= posB.y + dimensionsB.y)
		{
			collision.collided = true;
			collision.fromCenterOfMass = Math::Normalize(posA + (dimensionsA * 0.5f) - posB + (dimensionsB * 0.5f));

			// Colliding, find smallest correction vector
			sf::Vector2f middleA = posA + (dimensionsA * 0.5f);
			sf::Vector2f middleB = posB + (dimensionsB * 0.5f);
			sf::Vector2f middleDifference = middleA - middleB;

			sf::Vector2f effort = dimensionsA + dimensionsB + middleDifference;

			// Find the smallest effort, as that will point us to the
			// smallest correction vector
			if (Math::Abs(effort.x) < Math::Abs(effort.y))
			{
				if (middleDifference.x >= 0)
					collision.correctionVector = sf::Vector2f(dimensionsB.x - (posB.x - posA.x), 0.0f);
				else if (middleDifference.x < 0)
					collision.correctionVector = sf::Vector2f(posB.x - (dimensionsA.x - posA.x), 0.0f);
			}
			else
			{
				if (middleDifference.y >= 0)
					collision.correctionVector = sf::Vector2f(0.0f , dimensionsB.y + (posB.y - posA.y));
				else if (middleDifference.y < 0)
					collision.correctionVector = sf::Vector2f(0.0f, posB.y - (dimensionsA.y + posA.y));
			}
		}

		return collision;
	}

	CollisionInfo PolygonPolygonCollision(sf::Vector2f posA, const Vector<sf::Vector2f>& polygons, sf::Vector2f posB, const Vector<sf::Vector2f>& polygonB)
	{
		// TODO: Actually implement
		CollisionInfo info = {};
		return info;
	}

	bool AABBIsInAABB(sf::Vector2f posA, sf::Vector2f dimensionsA, sf::Vector2f posB, sf::Vector2f dimensionsB)
	{
		f32 xCalc = posA.x - posB.x + dimensionsA.x;
		f32 yCalc = posA.y - posB.y + dimensionsA.y;

		return (xCalc <= dimensionsB.x && xCalc >= dimensionsA.x) &&
			(yCalc <= dimensionsB.y && yCalc >= dimensionsA.y);
	}

	bool SOULAPI PointIsInAABB(sf::Vector2f point, sf::Vector2f posB, sf::Vector2f dimensionsB)
	{
		return point.x > posB.x && point.x < posB.x + dimensionsB.x &&
			point.y > posB.y && point.y < posB.y + dimensionsB.y;
	}

	CollisionInfo SOULAPI CalculateCollisionType(const IColliderNode* a, const IColliderNode* b)
	{
		String aType = a->GetType();
		String bType = b->GetType();

		if (aType == "RectColliderNode" && bType == "RectColliderNode")
		{
			RectColliderNode* specificTypeA = (RectColliderNode*)a;
			RectColliderNode* specificTypeB = (RectColliderNode*)b;
			return AABBAABBCollision(specificTypeA->GetWorldPosition(), specificTypeA->GetBoundingBox(),
				specificTypeB->GetWorldPosition(), specificTypeB->GetBoundingBox());
		}
		else if (aType == "CircleColliderNode" && bType == "RectColliderNode")
		{
			CircleColliderNode* specificTypeA = (CircleColliderNode*)a;
			RectColliderNode* specificTypeB = (RectColliderNode*)b;
			return CircleAABBCollision(specificTypeA->GetWorldPosition(), specificTypeA->GetRadius(),
				specificTypeB->GetWorldPosition(), specificTypeB->GetBoundingBox());
		}
		else if (bType == "RectColliderNode" && aType == "CircleColliderNode")
		{
			RectColliderNode* specificTypeA = (RectColliderNode*)a;
			CircleColliderNode* specificTypeB = (CircleColliderNode*)b;
			return CircleAABBCollision(specificTypeB->GetWorldPosition(), specificTypeB->GetRadius(),
				specificTypeA->GetWorldPosition(), specificTypeA->GetBoundingBox());
		}
		else
		{
			return PolygonPolygonCollision(a->GetWorldPosition(), a->GetPolygonList(), b->GetWorldPosition(), b->GetPolygonList());
		}
		// TODO: Add other types

		return CollisionInfo{};
	}
}