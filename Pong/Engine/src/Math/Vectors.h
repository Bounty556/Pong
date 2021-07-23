#pragma once

#include <Defines.h>

#include <SFML/System/Vector2.hpp>

namespace Soul
{
	namespace Math
	{
		SOULAPI f32 Distance(const sf::Vector2f& a, const sf::Vector2f& b);
		SOULAPI f32 Magnitude(const sf::Vector2f& a);
		SOULAPI sf::Vector2f Normalize(const sf::Vector2f& a);
		SOULAPI sf::Vector2f Normal(const sf::Vector2f& a);
		SOULAPI sf::Vector2f AngleToVector(f32 degrees); // 0 degrees/360 degrees = facing right
		SOULAPI f32 VectorToAngle(const sf::Vector2f& v); // 0 degrees/360 degrees = facing right
		SOULAPI f32 Dot(const sf::Vector2f& a, const sf::Vector2f b);
		SOULAPI sf::Vector2f Reflect(const sf::Vector2f& incoming, const sf::Vector2f& normal);
	}
}