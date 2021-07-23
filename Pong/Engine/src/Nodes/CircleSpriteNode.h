#pragma once

#include <Nodes/Node.h>

#include <SFML/Graphics/CircleShape.hpp>

namespace Soul
{
	class SOULAPI CircleSpriteNode : public Node
	{
	public:
		CircleSpriteNode(f32 radius, sf::Color color);

		virtual void DrawSelf(sf::RenderStates states) const override;
	
	private:
		sf::CircleShape m_Circle;
	};
}