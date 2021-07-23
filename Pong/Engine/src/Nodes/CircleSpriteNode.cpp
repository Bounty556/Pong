#include "CircleSpriteNode.h"

#include <Rendering/Renderer.h>

namespace Soul
{
	CircleSpriteNode::CircleSpriteNode(f32 radius, sf::Color color) :
		Node("CircleSpriteNode"),
		m_Circle(radius)
	{
		m_Circle.setFillColor(color);
	}

	void CircleSpriteNode::DrawSelf(sf::RenderStates states) const
	{
		Soul::Renderer::Render(m_Circle, states);
	}
}