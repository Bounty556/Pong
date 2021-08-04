#pragma once

#include <Defines.h>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

namespace Soul
{
	class UI : public sf::Transformable
	{
	public:
		enum UIAnchor
		{
			None = -1,
			TopLeft = 0,
			TopMiddle,
			TopRight,
			MiddleLeft,
			MiddleMiddle,
			MiddleRight,
			BottomLeft,
			BottomMiddle,
			BottomRight
		};

	public:
		UI(sf::Vector2f size, UI* parent = nullptr);
		UI(f32 width, f32 height, UI* parent = nullptr);

		UI(const UI& other);
		UI(UI&& other) noexcept;

		UI& operator=(const UI& other);
		UI& operator=(UI&& other) noexcept;

		const sf::Vector2f& GetSize() const;
		const UI* GetParent() const;

		void Update(f32 dt);
		void Draw(sf::RenderStates states) const;

		sf::Vector2f GetAnchorPosition(UIAnchor anchor) const;
		
		void SetAnchor(UIAnchor anchor);
		void SetWeightingAnchor(UIAnchor anchor);
		void SetAnchorWeight(f32 weight);

		virtual void AddChild(UI* child) = 0;

	protected:
		void SetParent(UI* parent);
	
		virtual void SetSize(sf::Vector2f size) = 0;
		virtual void SetSize(f32 width, f32 height) = 0;

		virtual void Resize(sf::Vector2f newSize) = 0;
		virtual void Resize(f32 width, f32 height) = 0;

		virtual void UpdateSelf(f32 dt) = 0;
		virtual void DrawSelf(sf::RenderStates states) const = 0;
		virtual void UpdateChildren(f32 dt);
		virtual void DrawChildren(sf::RenderStates states) const;

	private:
		sf::Vector2f m_Size;
		UI* m_Parent;
		UIAnchor m_MainAnchor;
		UIAnchor m_WeightingAnchor;
		f32 m_AnchorWeight;
	};
}