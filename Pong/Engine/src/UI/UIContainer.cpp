#include "UIContainer.h"

#include <Rendering/Renderer.h>

namespace Soul
{
	UIContainer::UIContainer(sf::Vector2f position, sf::Vector2f size) :
		UI(size),
		m_Children(),
		m_Rect(size)
	{
		setPosition(position);
		ResetColors();
	}

	UIContainer::UIContainer(f32 x, f32 y, f32 width, f32 height) :
		UI(width, height),
		m_Children(),
		m_Rect(sf::Vector2f(width, height))
	{
		setPosition(x, y);
		ResetColors();
	}

	UIContainer::UIContainer(sf::Vector2f size, UIAnchor mainAnchor, f32 anchorWeight /*= 100.0f*/, UIAnchor weightingAnchor /*= UIAnchor::MiddleMiddle*/) :
		UI(size),
		m_Children(),
		m_Rect(size)
	{
		SetAnchor(mainAnchor);
		SetWeightingAnchor(weightingAnchor);
		SetAnchorWeight(anchorWeight);
		ResetColors();
	}

	UIContainer::UIContainer(f32 width, f32 height, UIAnchor mainAnchor, f32 anchorWeight /*= 100.0f*/, UIAnchor weightingAnchor /*= UIAnchor::MiddleMiddle*/) :
		UI(width, height),
		m_Children(),
		m_Rect(sf::Vector2f(width, height))
	{
		SetAnchor(mainAnchor);
		SetWeightingAnchor(weightingAnchor);
		SetAnchorWeight(anchorWeight);
		ResetColors();
	}
	
	UIContainer::UIContainer(UIContainer&& other) noexcept :
		UI(other),
		m_Children(std::move(other.m_Children)),
		m_Rect(std::move(other.m_Rect))
	{
		ResetColors();
	}

	UIContainer& UIContainer::operator=(UIContainer&& other) noexcept
	{
		UI::operator=(other);
		m_Children = std::move(other.m_Children);
		m_Rect = std::move(other.m_Rect);

		ResetColors();

		return *this;
	}

	void UIContainer::AddChild(UI* child)
	{
		m_Children.Push(child);
		child->SetParent(this);

		Redraw();
	}

	void UIContainer::Redraw()
	{
		for (u8 i = 0; i < m_Children.Count(); ++i)
		{
			// TODO: take into account origins on children
			sf::Vector2f anchorA = GetAnchorPosition(m_Children[i]->GetMainAnchor());
			sf::Vector2f anchorB = GetAnchorPosition(m_Children[i]->GetWeightingAnchor());
			sf::Vector2f anchorDiff = anchorA - anchorB;
			sf::Vector2f smallAnchorA = m_Children[i]->GetAnchorPosition(m_Children[i]->GetMainAnchor());
			sf::Vector2f smallAnchorB = m_Children[i]->GetAnchorPosition(m_Children[i]->GetWeightingAnchor());
			sf::Vector2f smallAnchorDiff = smallAnchorA - smallAnchorB;
			sf::Vector2f smallAnchorOffset = smallAnchorB + (smallAnchorDiff * m_Children[i]->GetAnchorWeight());
			m_Children[i]->setPosition(anchorB + (anchorDiff * m_Children[i]->GetAnchorWeight()) - smallAnchorOffset);
			
			// Redraw child container
			m_Children[i]->Redraw();
		}
	}

	void UIContainer::Resize(sf::Vector2f newSize)
	{
		m_Size = newSize;
		m_Rect.setSize(newSize);

		if (m_Parent)
			m_Parent->Redraw();
		else
			Redraw();
	}

	void UIContainer::Resize(f32 width, f32 height)
	{
		m_Size = sf::Vector2f(width, height);
		m_Rect.setSize(sf::Vector2f(width, height));

		if (m_Parent)
			m_Parent->Redraw();
		else
			Redraw();
	}

	void UIContainer::ResetColors()
	{
		m_Rect.setFillColor(m_Palette.GetColor(0));
	}

	void UIContainer::UpdateSelf(f32 dt)
	{
		// TODO: detect edge drags
	}

	void UIContainer::DrawSelf(sf::RenderStates states) const
	{
		// TODO: Draw 9slice
		Soul::Renderer::Render(m_Rect, states);
	}

	void UIContainer::UpdateChildren(f32 dt)
	{
		for (u8 i = 0; i < m_Children.Count(); ++i)
			m_Children[i]->Update(dt);
	}

	void UIContainer::DrawChildren(sf::RenderStates states) const
	{
		for (u8 i = 0; i < m_Children.Count(); ++i)
			m_Children[i]->Draw(states);
	}
}