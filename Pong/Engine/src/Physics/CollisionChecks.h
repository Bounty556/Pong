#pragma once

#include <Defines.h>
#include <Structures/Vector.h>

#include <SFML/System/Vector2.hpp>

namespace Soul
{
	class IColliderNode;

	struct SOULAPI CollisionInfo
	{
		bool collided;
		sf::Vector2f correctionVector;
		sf::Vector2f fromCenterOfMass;
		IColliderNode* node;
	};

	/*
	Checks for a collision between circles, returning a CollisionInfo object
	containing the relevant collision info. Positions refer to the top left
	of the boundary of the circles.
	*/
	CollisionInfo SOULAPI CircleCircleCollision(sf::Vector2f posA, f32 radiusA, sf::Vector2f posB, f32 radiusB);

	/*
	Checks for a collision between a circle and a AABB rectangle, returning a
	CollisionInfo object containing the relevant collision info. Positions refer
	to the top left of the boundary of the circle and the top left corner of
	the rectangle.
	*/
	CollisionInfo SOULAPI CircleAABBCollision(sf::Vector2f posA, f32 radiusA, sf::Vector2f posB, sf::Vector2f dimensionsB);

	/*
	Checks for a collision between AABB rectangles, returning a CollisionInfo
	object containing the relevant collision info. Positions refer to the top
	left of the rectangles.
	*/
	CollisionInfo SOULAPI AABBAABBCollision(sf::Vector2f posA, sf::Vector2f dimensionsA, sf::Vector2f posB, sf::Vector2f dimensionsB);

	/*
	Checks for a collision between two sets of convex polygons, returning a
	CollisionInfo object containing the relevant collision info.
	*/
	CollisionInfo SOULAPI PolygonPolygonCollision(sf::Vector2f posA, const Vector<sf::Vector2f>& polygons, sf::Vector2f posB, const Vector<sf::Vector2f>& polygonB);

	/*
	Check to see if rectangle A is completely inside rectangle B. If the rectangles
	share boundaries, it is considered inside.
	*/
	bool SOULAPI AABBIsInAABB(sf::Vector2f posA, sf::Vector2f dimensionsA, sf::Vector2f posB, sf::Vector2f dimensionsB);

	/*
	Check to see if the provided point is completely in the provided AABB.
	*/
	bool SOULAPI PointIsInAABB(sf::Vector2f point, sf::Vector2f posB, sf::Vector2f dimensionsB);

	/*
	Gets the specific node type of the provided nodes, and calculates their
	collision info using correct algorithm.
	*/
	CollisionInfo SOULAPI CalculateCollisionType(const IColliderNode* a, const IColliderNode* b);
}