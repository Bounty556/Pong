#pragma once

#include <Defines.h>

#include <SFML/System/Vector2.hpp>

namespace Soul
{
	struct SOULAPI Collision
	{
		bool collided;
		sf::Vector2f collisionPoint;
	};
}