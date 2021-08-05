#include "UIText.h"

#include <Rendering/Renderer.h>
#include <Resources/ResourceManager.h>
#include <Resources/FontResource.h>

namespace Soul
{
	UIText::UIText(const char* text, const char* font) :
		UI(0, 0),
		m_Text(text, *ResourceManager::GetResource<sf::Font>(font)),
		m_Font(),
		m_RestrictedSize(false)
	{
		m_Size = m_Text.getLocalBounds().getSize();
	}

	UIText::UIText(const UIText& other) :
		UI(other),
		m_Text(other.m_Text),
		m_RestrictedSize(other.m_RestrictedSize)
	{
	}

	UIText::UIText(UIText&& other) noexcept :
		UI(other),
		m_Text(std::move(other.m_Text)),
		m_RestrictedSize(other.m_RestrictedSize)
	{
	}

	UIText& UIText::operator=(const UIText& other)
	{
		UI::operator=(other);
		m_Text = other.m_Text;
		m_RestrictedSize = other.m_RestrictedSize;
		
		return *this;
	}

	UIText& UIText::operator=(UIText&& other) noexcept
	{
		UI::operator=(other);
		m_Text = std::move(other.m_Text);
		m_RestrictedSize = other.m_RestrictedSize;

		return *this;
	}

	void UIText::ResetSize()
	{
		m_RestrictedSize = false;
	}

	void UIText::SetSize(sf::Vector2f size)
	{
		m_RestrictedSize = true;
		m_Size = size;

		if (m_Parent)
			m_Parent->Redraw();
	}

	void UIText::SetSize(f32 width, f32 height)
	{
		m_RestrictedSize = true;
		m_Size = sf::Vector2f(width, height);

		if (m_Parent)
			m_Parent->Redraw();
	}

	void UIText::SetText(const char* text)
	{
		m_Text.setString(text);

		if (!m_RestrictedSize)
			Resize(m_Text.getLocalBounds().getSize());
	}

	void UIText::SetFont(const char* font)
	{
		m_Text.setFont(*ResourceManager::GetResource<sf::Font>(font));

		if (!m_RestrictedSize)
			Resize(m_Text.getLocalBounds().getSize());
	}

	void UIText::SetFontSize(u32 fontSize)
	{
		m_Text.setCharacterSize(fontSize);

		if (!m_RestrictedSize)
			Resize(m_Text.getLocalBounds().getSize());
	}

	void UIText::SetOutlineThickness(f32 size)
	{
		m_Text.setOutlineThickness(size);

		if (!m_RestrictedSize)
			Resize(m_Text.getLocalBounds().getSize());
	}

	void UIText::Resize(sf::Vector2f newSize)
	{
		m_Size = newSize;

		if (m_Parent)
			m_Parent->Redraw();
	}

	void UIText::Resize(f32 width, f32 height)
	{
		m_Size = sf::Vector2f(width, height);

		if (m_Parent)
			m_Parent->Redraw();
	}

	void UIText::ResetColors()
	{
		m_Text.setFillColor(m_Palette.GetColor(0));
		m_Text.setOutlineColor(m_Palette.GetColor(1));
	}

	bool UIText::UpdateSelf(f32 dt)
	{
		return true;
	}

	void UIText::DrawSelf(sf::RenderStates states) const
	{
		Renderer::Render(m_Text, states);
	}
}