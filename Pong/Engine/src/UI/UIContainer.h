#pragma once

#include <Defines.h>
#include <Structures/Vector.h>
#include <UI/UI.h>

#include <SFML/Graphics/RectangleShape.hpp>

namespace Soul
{
	class SOULAPI UIContainer : public UI
	{
	public:
		UIContainer(sf::Vector2f position, sf::Vector2f size);
		UIContainer(f32 x, f32 y, f32 width, f32 height);

		UIContainer(sf::Vector2f size, UI* parent, UIAnchor mainAnchor, f32 anchorWeight = 100.0f, UIAnchor weightingAnchor = UIAnchor::MiddleMiddle);
		UIContainer(f32 width, f32 height, UI* parent, UIAnchor mainAnchor, f32 anchorWeight = 100.0f, UIAnchor weightingAnchor = UIAnchor::MiddleMiddle);
	
		UIContainer(const UIContainer& other) = delete;
		UIContainer(UIContainer&& other) noexcept;

		UIContainer& operator=(const UIContainer& other) = delete;
		UIContainer& operator=(UIContainer&& other) noexcept;

		virtual void AddChild(UI* child) override;

		virtual void Redraw() override;

	protected:
		virtual void ResetColors() override;

		virtual void Resize(sf::Vector2f newSize) override;
		virtual void Resize(f32 width, f32 height) override;

		virtual void UpdateSelf(f32 dt) override;
		virtual void DrawSelf(sf::RenderStates states) const override;

	private:
		Vector<UniquePointer<UI>> m_Children;
		sf::RectangleShape m_Rect;
	};
}