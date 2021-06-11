#include "UIButton.h"

#include <Rendering/Renderer.h>

namespace Soul
{
	UIButton::UIButton(const char* buttonText, FontManager& fontManager, std::function<void()> activate) :
		UIComponent(activate),
		m_Text(buttonText, *(fontManager.RequestFont("res/font.otf")))
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