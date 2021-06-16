#pragma once

#include <UI/UIComponent.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace Soul
{
	/*
	This must be provided a callback function that gets called when the button is
	activated.
	*/
	class SOULAPI UISprite : public UIComponent
	{
	public:
		UISprite(const sf::Texture& texture, u32 width, u32 height);

		virtual void Draw(sf::RenderStates states) const override;

	private:
		sf::Sprite m_Sprite;
	};
}