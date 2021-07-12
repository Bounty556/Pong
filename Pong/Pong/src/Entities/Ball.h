#pragma once

#include <Defines.h>
#include <Nodes/Node.h>

#include <SFML/Graphics/CircleShape.hpp>

class Ball : public Soul::Node
{
public:
	Ball(f32 radius, f32 speed);

	virtual void UpdateSelf(f32 dt) override;
	virtual void DrawSelf(sf::RenderStates states) const override;

private:
	sf::CircleShape m_Ball;
	sf::Vector2f m_Direction;
	f32 m_Speed;
};