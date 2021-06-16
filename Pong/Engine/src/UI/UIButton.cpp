#include "UIButton.h"

#include <Rendering/Renderer.h>

namespace Soul
{
	UIButton::UIButton(const char* buttonText, const sf::Font& font, std::function<void()> activate) :
		UIComponent(activate),
		m_Text(buttonText, font)
	{
	}

	void UIButton::Update(f32 dt)
	{
		if (m_UIState == UIComponent::Hovered)
			m_Text.setFillColor(sf::Color::White);
		else if (m_UIState == UIComponent::Neutral)
			m_Text.setFillColor(sf::Color(150, 150, 150));
	}

	void UIButton::Draw(sf::RenderStates states) const
	{
		states.transform *= getTransform();

		Renderer::Render(m_Text, states);
	}
}