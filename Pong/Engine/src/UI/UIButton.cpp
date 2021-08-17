#include "UIButton.h"

#include <Resources/ResourceManager.h>
#include <Rendering/Renderer.h>

#include <SFML/Graphics/Font.hpp>

namespace Soul
{
	UIButton::UIButton(const char* text, const char* font, std::function<void()> callback, f32 paddingLeft/*= 0*/, f32 paddingTop/*= 0*/, f32 paddingRight/*= 0*/, f32 paddingBottom/*= 0*/) :
		UI(0.0f, 0.0f),
		m_IsHovered(false),
		m_Callback(callback),
		m_Text(text, *ResourceManager::GetResource<sf::Font>(font)),
		m_Background(sf::Vector2f(0.0f, 0.0f)),
		m_PaddingLeft(paddingLeft),
		m_PaddingTop(paddingTop),
		m_PaddingRight(paddingRight),
		m_PaddingBottom(paddingBottom)
	{
		Resize(m_Text.getLocalBounds().getSize() + sf::Vector2f(paddingLeft + paddingRight, paddingTop + paddingBottom));

		ResetColors();
	}

	UIButton::UIButton(const UIButton& other) :
		UI(other),
		m_IsHovered(false),
		m_Callback(other.m_Callback),
		m_Text(other.m_Text),
		m_Background(other.m_Background),
		m_PaddingLeft(other.m_PaddingLeft),
		m_PaddingTop(other.m_PaddingTop),
		m_PaddingRight(other.m_PaddingRight),
		m_PaddingBottom(other.m_PaddingBottom)
	{
		ResetColors();
	}

	UIButton::UIButton(UIButton&& other) noexcept :
		UI(other),
		m_IsHovered(other.m_IsHovered),
		m_Callback(std::move(other.m_Callback)),
		m_Text(std::move(other.m_Text)),
		m_Background(std::move(other.m_Background)),
		m_PaddingLeft(other.m_PaddingLeft),
		m_PaddingTop(other.m_PaddingTop),
		m_PaddingRight(other.m_PaddingRight),
		m_PaddingBottom(other.m_PaddingBottom)
	{
		ResetColors();
	}

	UIButton& UIButton::operator=(const UIButton& other)
	{
		UI::operator=(other);
		m_IsHovered = false;
		m_Callback = other.m_Callback;
		m_Text = other.m_Text;
		m_Background = other.m_Background;
		m_PaddingLeft = other.m_PaddingLeft;
		m_PaddingTop = other.m_PaddingTop;
		m_PaddingRight = other.m_PaddingRight;
		m_PaddingBottom = other.m_PaddingBottom;

		ResetColors();
	
		return *this;
	}

	UIButton& UIButton::operator=(UIButton&& other) noexcept
	{
		UI::operator=(other);
		m_IsHovered = other.m_IsHovered;
		m_Callback = std::move(other.m_Callback);
		m_Text = std::move(other.m_Text);
		m_Background = std::move(other.m_Background);
		m_PaddingLeft = other.m_PaddingLeft;
		m_PaddingTop = other.m_PaddingTop;
		m_PaddingRight = other.m_PaddingRight;
		m_PaddingBottom = other.m_PaddingBottom;

		ResetColors();

		return *this;
	}

	void UIButton::SetPaddingLeft(f32 padding)
	{
		m_Size.x += padding - m_PaddingLeft;
		m_PaddingLeft = padding;
		m_Background.setSize(m_Size);
		m_Text.setPosition(m_PaddingLeft, m_PaddingTop);
	}

	void UIButton::SetPaddingTop(f32 padding)
	{
		m_Size.y += padding - m_PaddingTop;
		m_PaddingTop = padding;
		m_Background.setSize(m_Size);
		m_Text.setPosition(m_PaddingLeft, m_PaddingTop);
	}

	void UIButton::SetPaddingRight(f32 padding)
	{
		m_Size.x += padding - m_PaddingRight;
		m_PaddingRight = padding;
		m_Background.setSize(m_Size);
	}

	void UIButton::SetPaddingBottom(f32 padding)
	{
		m_Size.y += padding - m_PaddingBottom;
		m_PaddingBottom = padding;
		m_Background.setSize(m_Size);
	}

	void UIButton::SetHovered(bool hovered)
	{
		m_IsHovered = hovered;

		ResetColors();
	}

	void UIButton::Activate()
	{
		m_Callback();
	}

	void UIButton::Resize(sf::Vector2f newSize)
	{
		m_Size = newSize;
		m_PaddingLeft = (m_Size.x - m_Text.getLocalBounds().getSize().x) / 2.0f;
		m_PaddingRight = m_PaddingLeft;
		m_PaddingTop = (m_Size.y - m_Text.getLocalBounds().getSize().y) / 2.0f;
		m_PaddingBottom = m_PaddingTop;
		m_Background.setSize(m_Size);
		m_Text.setPosition(m_PaddingLeft, m_PaddingTop);
	}

	void UIButton::Resize(f32 width, f32 height)
	{
		Resize(sf::Vector2f(width, height));
	}

	void UIButton::ResetColors()
	{
		if (m_IsHovered)
		{
			m_Text.setFillColor(m_Palette.GetColor(2));
			m_Background.setFillColor(m_Palette.GetColor(3));
		}
		else
		{
			m_Text.setFillColor(m_Palette.GetColor(0));
			m_Background.setFillColor(m_Palette.GetColor(1));
		}
	}

	bool UIButton::UpdateSelf(f32 dt)
	{
		return true;
	}

	void UIButton::DrawSelf(sf::RenderStates states) const
	{
		Renderer::Render(m_Background, states);
		Renderer::Render(m_Text, states);
	}
}