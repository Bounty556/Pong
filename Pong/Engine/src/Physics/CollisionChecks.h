#pragma once

#include <Defines.h>

#include <SFML/System/Vector2.hpp>

namespace Soul
{
	struct SOULAPI CollisionInfo
	{
		bool collided;
		sf::Vector2f correctionVector;
	};

	/*
	Checks for a collisions between circles, returning a CollisionInfo object
	containing the relevant collision info. Positions refer to the center of
	the circles.
	*/
	CollisionInfo SOULAPI CircleCircleCollision(sf::Vector2f posA, f32 radiusA, sf::Vector2f posB, f32 radiusB);

	/*
	Checks for a collisions between a circle and a rectangle, returning a
	CollisionInfo object containing the relevant collision info. Positions refer
	to the center of the circle and the top left corner of the rectangle.
	*/
	CollisionInfo SOULAPI CircleRectangleCollision(sf::Vector2f posA, f32 radiusA, sf::Vector2f posB, sf::Vector2f dimensionsB);

	/*
	Checks for a collisions between rectangles, returning a CollisionInfo object
	containing the relevant collision info. Positions refer to the top left of
	the rectangles.
	*/
	CollisionInfo SOULAPI RectangleRectangleCollision(sf::Vector2f posA, sf::Vector2f dimensionsA, sf::Vector2f posB, sf::Vector2f dimensionsB);
}