#pragma once

#include <Defines.h>
#include <Nodes/Node.h>

#include <SFML/Graphics/CircleShape.hpp>

class Ball : public Soul::Node
{
public:
	Ball(f32 radius, f32 speed);

	virtual void Update(f32 dt);
	virtual void Draw(sf::RenderStates states) const;

private:
	sf::CircleShape m_Ball;
	sf::Vector2f m_Direction;
	f32 m_Speed;
};