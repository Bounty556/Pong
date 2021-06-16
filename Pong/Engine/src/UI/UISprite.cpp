#include "UISprite.h"

#include <Rendering/Renderer.h>

namespace Soul
{
	UISprite::UISprite(const sf::Texture& texture, u32 width, u32 height) :
		UIComponent([]() {}),
		m_Sprite(texture)
	{
		f32 newScaleX = (f32)width / texture.getSize().x;
		f32 newScaleY = (f32)height / texture.getSize().y;
		m_Sprite.setScale(newScaleX, newScaleY);
	}

	void UISprite::Draw(sf::RenderStates states) const
	{
		states.transform *= getTransform();

		Renderer::Render(m_Sprite, states);
	}
}