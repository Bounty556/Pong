#pragma once

#include <Resources/FontManager.h>
#include <UI/UIComponent.h>

#include <SFML/Graphics/Text.hpp>

namespace Soul
{
	/*
	A UI Button. This must be provided a callback function that gets called when the button is
	activated.
	*/
	class SOULAPI UIButton : public UIComponent
	{
	public:
		UIButton(const char* buttonText, FontManager& fontManager, std::function<void()> activate);

		virtual void Update(f32 dt) override;

		virtual void Draw(sf::RenderStates states) const override;

	private:
		sf::Text m_Text;
	};
}