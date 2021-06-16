#pragma once

#include <Resources/FontManager.h>
#include <UI/UIComponent.h>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Soul
{
	/*
	This must be provided a callback function that gets called when the button is
	activated.
	*/
	class SOULAPI UILabel : public UIComponent
	{
	public:
		UILabel(const char* text, const sf::Font& font);

		virtual void Draw(sf::RenderStates states) const override;

		void SetText(const char* text);

	private:
		sf::Text m_Text;
	};
}