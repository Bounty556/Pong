#include "UI.h"

namespace Soul
{
	UI::UI(sf::Vector2f size) :
		m_Size(size),
		m_Parent(nullptr),
		m_MainAnchor(UIAnchor::None),
		m_WeightingAnchor(UIAnchor::MiddleMiddle),
		m_AnchorWeight(0.0f),
		m_Palette(1, sf::Color::White)
	{
	}

	UI::UI(f32 width, f32 height) :
		m_Size(sf::Vector2f(width, height)),
		m_Parent(nullptr),
		m_MainAnchor(UIAnchor::None),
		m_WeightingAnchor(UIAnchor::MiddleMiddle),
		m_AnchorWeight(0.0f),
		m_Palette(1, sf::Color::White)
	{
	}

	UI::UI(const UI& other) :
		m_Size(other.m_Size),
		m_Parent(nullptr),
		m_MainAnchor(other.m_MainAnchor),
		m_WeightingAnchor(other.m_WeightingAnchor),
		m_AnchorWeight(other.m_AnchorWeight),
		m_Palette(other.m_Palette)
	{
	}

	UI::UI(UI&& other) noexcept :
		m_Size(other.m_Size),
		m_Parent(nullptr),
		m_MainAnchor(other.m_MainAnchor),
		m_WeightingAnchor(other.m_WeightingAnchor),
		m_AnchorWeight(other.m_AnchorWeight),
		m_Palette(std::move(other.m_Palette))
	{
	}

	UI& UI::operator=(const UI& other)
	{
		m_Size = other.m_Size;
		m_Parent = nullptr;
		m_MainAnchor = other.m_MainAnchor;
		m_WeightingAnchor = other.m_WeightingAnchor;
		m_AnchorWeight = other.m_AnchorWeight;
		m_Palette = other.m_Palette;
		
		ResetColors();

		return *this;
	}

	UI& UI::operator=(UI&& other) noexcept
	{
		m_Size = other.m_Size;
		m_Parent = nullptr;
		m_MainAnchor = other.m_MainAnchor;
		m_WeightingAnchor = other.m_WeightingAnchor;
		m_AnchorWeight = other.m_AnchorWeight;
		m_Palette = other.m_Palette;
		
		ResetColors();

		return *this;
	}

	UI::~UI()
	{
	}

	const sf::Vector2f& UI::GetSize() const
	{
		return m_Size;
	}

	const UI* UI::GetParent() const
	{
		return m_Parent;
	}

	bool UI::Update(f32 dt)
	{
		if (UpdateChildren(dt))
			return UpdateSelf(dt);
		else
			return false;
	}

	void UI::Draw(sf::RenderStates states) const
	{
		states.transform *= getTransform();
		DrawSelf(states);
		DrawChildren(states);
	}

	const UI::UIAnchor& UI::GetMainAnchor() const
	{
		return m_MainAnchor;
	}

	const UI::UIAnchor& UI::GetWeightingAnchor() const
	{
		return m_WeightingAnchor;
	}

	f32 UI::GetAnchorWeight() const
	{
		return m_AnchorWeight;
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

	void UI::SetUIPalette(const UIPalette& palette)
	{
		m_Palette = palette;
		ResetColors();
	}

	const UIPalette& UI::GetUIPalette() const
	{
		return m_Palette;
	}

	void UI::SetParent(UI* parent)
	{
		m_Parent = parent;
	}

	sf::Vector2f UI::GetWorldPosition()
	{
		sf::Transform transform = getTransform();

		const UI* current = this;

		while (current->m_Parent)
		{
			transform *= m_Parent->getTransform();
			current = current->m_Parent;
		}

		return transform * sf::Vector2f();
	}

	void UI::Redraw()
	{
	}

	bool UI::UpdateChildren(f32 dt)
	{
		return true;
	}

	void UI::DrawChildren(sf::RenderStates states) const
	{
	}
}