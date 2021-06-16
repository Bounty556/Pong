#include "UILabel.h"

#include <Rendering/Renderer.h>

namespace Soul
{
	UILabel::UILabel(const char* text, const sf::Font& font) :
		UIComponent([]() {}),
		m_Text(text, font)
	{
	}

	void UILabel::Draw(sf::RenderStates states) const
	{
		states.transform *= getTransform();

		Renderer::Render(m_Text, states);
	}

	void UILabel::SetText(const char* text)
	{
		m_Text.setString(text);
	}
}