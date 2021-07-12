#pragma once

#include <Defines.h>

#include <Nodes/Node.h>

#include <SFML/Graphics/RectangleShape.hpp>

class Paddle : public Soul::Node
{
public:
	Paddle();

	virtual void UpdateSelf(f32 dt) override;
	virtual void DrawSelf(sf::RenderStates states) const override;

private:
	sf::RectangleShape m_Paddle;
	f32 m_MoveSpeed;
};