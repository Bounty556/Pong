#pragma once

#include <Defines.h>
#include <Nodes/Node.h>

#include <SFML/Graphics/RectangleShape.hpp>

namespace Soul
{
	class SOULAPI RectSpriteNode : public Node
	{
	public:
		RectSpriteNode(f32 width, f32 height, sf::Color color);

		virtual void DrawSelf(sf::RenderStates states) const override;

	private:
		sf::RectangleShape m_Rect;
	};
}