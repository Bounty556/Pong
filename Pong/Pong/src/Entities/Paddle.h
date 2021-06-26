#pragma once

#include <Defines.h>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Paddle : public sf::Transformable
{
public:
	Paddle();

	void Update(f32 dt);
	void Draw(sf::RenderStates states) const;

private:
	sf::RectangleShape m_Paddle;
	f32 m_MoveSpeed;
};