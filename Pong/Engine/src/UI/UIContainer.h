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

		UIContainer(sf::Vector2f size, UIAnchor mainAnchor, f32 anchorWeight = 1.0f, UIAnchor weightingAnchor = UIAnchor::MiddleMiddle);
		UIContainer(f32 width, f32 height, UIAnchor mainAnchor, f32 anchorWeight = 1.0f, UIAnchor weightingAnchor = UIAnchor::MiddleMiddle);
	
		UIContainer(const UIContainer& other) = delete;
		UIContainer(UIContainer&& other) noexcept;

		UIContainer& operator=(const UIContainer& other) = delete;
		UIContainer& operator=(UIContainer&& other) noexcept;

		void AddChild(UI* child);

		virtual void Redraw() override;

		virtual void Resize(sf::Vector2f newSize) override;
		virtual void Resize(f32 width, f32 height) override;

	protected:
		virtual void ResetColors() override;

		virtual bool UpdateSelf(f32 dt) override;
		virtual void DrawSelf(sf::RenderStates states) const override;
		virtual bool UpdateChildren(f32 dt) override;
		virtual void DrawChildren(sf::RenderStates states) const override;

	private:
		Vector<UniquePointer<UI>> m_Children;
		sf::RectangleShape m_Rect;
		bool m_IsDragged;
	};
}