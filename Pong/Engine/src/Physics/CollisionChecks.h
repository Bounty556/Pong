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

	//CollisionInfo SOULAPI CircleCircleCollision()
}