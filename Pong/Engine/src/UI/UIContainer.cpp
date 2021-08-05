#include "UIContainer.h"

#include <Rendering/Renderer.h>
#include <IO/InputManager.h>
#include <Physics/CollisionChecks.h>

namespace Soul
{
	UIContainer::UIContainer(sf::Vector2f position, sf::Vector2f size) :
		UI(size),
		m_Children(),
		m_Rect(size),
		m_IsDragged(false)
	{
		setPosition(position);
		ResetColors();
	}

	UIContainer::UIContainer(f32 x, f32 y, f32 width, f32 height) :
		UI(width, height),
		m_Children(),
		m_Rect(sf::Vector2f(width, height)),
		m_IsDragged(false)
	{
		setPosition(x, y);
		ResetColors();
	}

	UIContainer::UIContainer(sf::Vector2f size, UIAnchor mainAnchor, f32 anchorWeight /*= 100.0f*/, UIAnchor weightingAnchor /*= UIAnchor::MiddleMiddle*/) :
		UI(size),
		m_Children(),
		m_Rect(size),
		m_IsDragged(false)
	{
		SetAnchor(mainAnchor);
		SetWeightingAnchor(weightingAnchor);
		SetAnchorWeight(anchorWeight);
		ResetColors();
	}

	UIContainer::UIContainer(f32 width, f32 height, UIAnchor mainAnchor, f32 anchorWeight /*= 100.0f*/, UIAnchor weightingAnchor /*= UIAnchor::MiddleMiddle*/) :
		UI(width, height),
		m_Children(),
		m_Rect(sf::Vector2f(width, height)),
		m_IsDragged(false)
	{
		SetAnchor(mainAnchor);
		SetWeightingAnchor(weightingAnchor);
		SetAnchorWeight(anchorWeight);
		ResetColors();
	}
	
	UIContainer::UIContainer(UIContainer&& other) noexcept :
		UI(other),
		m_Children(std::move(other.m_Children)),
		m_Rect(std::move(other.m_Rect)),
		m_IsDragged(false)
	{
		ResetColors();
	}

	UIContainer& UIContainer::operator=(UIContainer&& other) noexcept
	{
		UI::operator=(other);
		m_Children = std::move(other.m_Children);
		m_Rect = std::move(other.m_Rect);
		m_IsDragged = false;

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
			if (m_Children[i]->GetMainAnchor() != UIAnchor::None)
			{
				sf::Vector2f anchorA = GetAnchorPosition(m_Children[i]->GetMainAnchor());
				sf::Vector2f anchorB = GetAnchorPosition(m_Children[i]->GetWeightingAnchor());
				sf::Vector2f anchorDiff = anchorA - anchorB;
				sf::Vector2f smallAnchorA = m_Children[i]->GetAnchorPosition(m_Children[i]->GetMainAnchor());
				sf::Vector2f smallAnchorB = m_Children[i]->GetAnchorPosition(m_Children[i]->GetWeightingAnchor());
				sf::Vector2f smallAnchorDiff = smallAnchorA - smallAnchorB;
				sf::Vector2f smallAnchorOffset = smallAnchorB + (smallAnchorDiff * m_Children[i]->GetAnchorWeight());
				m_Children[i]->setPosition(anchorB + (anchorDiff * m_Children[i]->GetAnchorWeight()) - smallAnchorOffset);
			}
			
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

	bool UIContainer::UpdateSelf(f32 dt)
	{
		if (m_MainAnchor == UIAnchor::None && InputManager::GetControlState(-1, "Select").state == Controller::Pressed &&
			PointIsInAABB((sf::Vector2f)sf::Mouse::getPosition(Renderer::GetWindow()), GetWorldPosition(), m_Size))
			m_IsDragged = true;
		else if (InputManager::GetControlState(-1, "Select").state == Controller::Released)
			m_IsDragged = false;

		// Drag
		if (m_IsDragged)
		{
			move((sf::Vector2f)Soul::InputManager::GetMouseDelta());
			Redraw();

			return false;
		}
		// TODO: detect edge drags

		return true;
	}

	void UIContainer::DrawSelf(sf::RenderStates states) const
	{
		// TODO: Draw 9slice
		Soul::Renderer::Render(m_Rect, states);
	}

	bool UIContainer::UpdateChildren(f32 dt)
	{
		bool blockedUpdate = false;
		for (u8 i = 0; i < m_Children.Count(); ++i)
		{
			if (!m_Children[i]->Update(dt))
				blockedUpdate = true;
		}

		return !blockedUpdate;
	}

	void UIContainer::DrawChildren(sf::RenderStates states) const
	{
		for (u8 i = 0; i < m_Children.Count(); ++i)
			m_Children[i]->Draw(states);
	}
}