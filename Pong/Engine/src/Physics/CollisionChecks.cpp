#include "CollisionChecks.h"

#include <Core/String.h>
#include <Math/Functions.h>
#include <Math/Vectors.h>
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
			direction *= (radiusA + radiusB) - distance;
			collision.correctionVector = direction;
		}

		return collision;
	}

	CollisionInfo SOULAPI CircleAABBCollision(sf::Vector2f posA, f32 radiusA, sf::Vector2f posB, sf::Vector2f dimensionsB)
	{
		posA += sf::Vector2f(radiusA, radiusA);

		CollisionInfo collision = {};

		sf::Vector2f closestEdge(posB.x - posA.x, posB.y - posA.y);

		if (Math::Abs(posB.x + dimensionsB.x - posA.x) < Math::Abs(closestEdge.x))
			closestEdge.x = posB.x + dimensionsB.x - posA.x;
		if (Math::Abs(posB.y + dimensionsB.y - posA.y) < Math::Abs(closestEdge.y))
			closestEdge.y = posB.y + dimensionsB.y - posA.y;

		// Check if we're inside the rectangle, calculate accordingly
		if (posA.x > posB.x && posA.x < posB.x + dimensionsB.x &&
			posA.y > posB.y && posA.y < posB.y + dimensionsB.y)
			collision.collided = true;
		else if (Math::Distance(closestEdge, posA) < radiusA)
		{
			collision.collided = true;
			radiusA = -radiusA;
		}

		// TODO: This seems really hacky...
		if (collision.collided)
		{
			if (Math::Abs(closestEdge.x) < Math::Abs(closestEdge.y))
			{
				if (closestEdge.x < 0)
					closestEdge = sf::Vector2f(closestEdge.x - radiusA, 0.0f);
				else
					closestEdge = sf::Vector2f(closestEdge.x + radiusA, 0.0f);
			}
			else
			{
				if (closestEdge.y < 0)
					closestEdge = sf::Vector2f(0.0f, closestEdge.y - radiusA);
				else
					closestEdge = sf::Vector2f(0.0f, closestEdge.y + radiusA);
			}
		}

		collision.correctionVector = closestEdge;

		return collision;
	}

	CollisionInfo SOULAPI AABBAABBCollision(sf::Vector2f posA, sf::Vector2f dimensionsA, sf::Vector2f posB, sf::Vector2f dimensionsB)
	{
		CollisionInfo collision = {};

		if (posA.x >= posB.x - dimensionsA.x && posA.x <= posB.x + dimensionsB.x &&
			posA.y >= posB.y - dimensionsA.y && posA.y <= posB.y + dimensionsB.y)
		{
			collision.collided = true;

			// Colliding, find smallest correction vector
			sf::Vector2f middleA(posA + (dimensionsA * 0.5f));
			sf::Vector2f middleB(posB + (dimensionsB * 0.5f));
			sf::Vector2f middleDifference = middleA - middleB;

			// Find the biggest middle difference, as that will point us to the
			// smallest correction vector
			if (Math::Abs(middleDifference.x) >= Math::Abs(middleDifference.y))
			{
				if (middleDifference.x >= 0)
					collision.correctionVector = sf::Vector2f(dimensionsA.x - (posA.x - posB.x), 0.0f);
				else if (middleDifference.x < 0)
					collision.correctionVector = sf::Vector2f(-dimensionsA.x - (posA.x - posB.x), 0.0f);
			}
			else
			{
				if (middleDifference.y >= 0)
					collision.correctionVector = sf::Vector2f(dimensionsA.y - (posA.y - posB.y), 0.0f);
				else if (middleDifference.y < 0)
					collision.correctionVector = sf::Vector2f(-dimensionsA.y - (posA.y - posB.y), 0.0f);
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

	CollisionInfo SOULAPI CalculateCollisionType(Node* a, Node* b)
	{
		String aType = a->GetType();
		String bType = b->GetType();

		if (aType == "RectColliderNode" && bType == "RectColliderNode")
		{
			RectColliderNode* specificTypeA = (RectColliderNode*)a;
			RectColliderNode* specificTypeB = (RectColliderNode*)b;
			return AABBAABBCollision(specificTypeA->getPosition(), specificTypeA->GetBoundingBox(),
				specificTypeB->getPosition(), specificTypeB->GetBoundingBox());
		}
		else if (aType == "CircleColliderNode" && bType == "RectColliderNode")
		{
			CircleColliderNode* specificTypeA = (CircleColliderNode*)a;
			RectColliderNode* specificTypeB = (RectColliderNode*)b;
			return CircleAABBCollision(specificTypeA->getPosition(), specificTypeA->GetRadius(),
				specificTypeB->getPosition(), specificTypeB->GetBoundingBox());
		}
		else if (bType == "RectColliderNode" && aType == "CircleColliderNode")
		{
			RectColliderNode* specificTypeA = (RectColliderNode*)a;
			CircleColliderNode* specificTypeB = (CircleColliderNode*)b;
			return CircleAABBCollision(specificTypeB->getPosition(), specificTypeB->GetRadius(),
				specificTypeA->getPosition(), specificTypeA->GetBoundingBox());
		}
		// TODO: Add other types

		return CollisionInfo{};
	}
}