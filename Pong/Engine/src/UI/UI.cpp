#include "UI.h"

namespace Soul
{
	UI::UI(sf::Vector2f size, UI* parent /*= nullptr*/) :
		m_Size(size),
		m_Parent(parent),
		m_MainAnchor(UIAnchor::None),
		m_WeightingAnchor(UIAnchor::MiddleMiddle),
		m_AnchorWeight(0.0f),
		m_Palette(1, sf::Color::White)
	{
	}

	UI::UI(f32 width, f32 height, UI* parent /*= nullptr*/) :
		m_Size(sf::Vector2f(width, height)),
		m_Parent(parent),
		m_MainAnchor(UIAnchor::None),
		m_WeightingAnchor(UIAnchor::MiddleMiddle),
		m_AnchorWeight(0.0f),
		m_Palette(1, sf::Color::White)
	{
	}

	UI::UI(const UI& other) :
		m_Size(other.m_Size),
		m_Parent(other.m_Parent),
		m_MainAnchor(other.m_MainAnchor),
		m_WeightingAnchor(other.m_WeightingAnchor),
		m_AnchorWeight(other.m_AnchorWeight),
		m_Palette(other.m_Palette)
	{
	}

	UI::UI(UI&& other) noexcept :
		m_Size(other.m_Size),
		m_Parent(other.m_Parent),
		m_MainAnchor(other.m_MainAnchor),
		m_WeightingAnchor(other.m_WeightingAnchor),
		m_AnchorWeight(other.m_AnchorWeight),
		m_Palette(std::move(other.m_Palette))
	{
	}

	UI& UI::operator=(const UI& other)
	{
		m_Size = other.m_Size;
		m_Parent = other.m_Parent;
		m_MainAnchor = other.m_MainAnchor;
		m_WeightingAnchor = other.m_WeightingAnchor;
		m_AnchorWeight = other.m_AnchorWeight;
		m_Palette = other.m_Palette;

		return *this;
	}

	UI& UI::operator=(UI&& other) noexcept
	{
		m_Size = other.m_Size;
		m_Parent = other.m_Parent;
		m_MainAnchor = other.m_MainAnchor;
		m_WeightingAnchor = other.m_WeightingAnchor;
		m_AnchorWeight = other.m_AnchorWeight;
		m_Palette = std::move(other.m_Palette);
		
		return *this;
	}

	const sf::Vector2f& UI::GetSize() const
	{
		return m_Size;
	}

	const UI* UI::GetParent() const
	{
		return m_Parent;
	}

	void UI::Update(f32 dt)
	{
		UpdateSelf(dt);
		UpdateChildren(dt);
	}

	void UI::Draw(sf::RenderStates states) const
	{
		states.transform *= getTransform();
		DrawSelf(states);
		DrawChildren(states);
	}

	sf::Vector2f UI::GetAnchorPosition(UIAnchor anchor) const
	{
		ASSERT(anchor != UIAnchor::None);

		u8 y = (u8)anchor / 3;
		u8 x = (u8)anchor % 3;

		sf::Vector2f pos;
		pos.x = x * (m_Size.x / 2.0f);
		pos.y = y * (m_Size.y / 2.0f);

		return pos;
	}

	void UI::SetAnchor(UIAnchor anchor)
	{
		m_MainAnchor = anchor;
	}

	void UI::SetWeightingAnchor(UIAnchor anchor)
	{
		m_WeightingAnchor = anchor;
	}

	void UI::SetAnchorWeight(f32 weight)
	{
		m_AnchorWeight = weight;
	}

	void UI::SetUIPalette(UIPalette palette)
	{
		m_Palette = palette;
	}

	void UI::SetParent(UI* parent)
	{
		m_Parent = parent;
	}

	void UI::UpdateChildren(f32 dt)
	{
	}

	void UI::DrawChildren(sf::RenderStates states) const
	{
	}
}