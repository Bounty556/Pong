#include "RectSpriteNode.h"

#include <Rendering/Renderer.h>

namespace Soul
{
	RectSpriteNode::RectSpriteNode(f32 width, f32 height, sf::Color color) :
		Node("RectSpriteNode"),
		m_Rect(sf::Vector2f(width, height))
	{
		m_Rect.setFillColor(color);
	}

	void RectSpriteNode::DrawSelf(sf::RenderStates states) const
	{
		Soul::Renderer::Render(m_Rect, states);
	}
}