#pragma once

#include <Defines.h>

#include <UI/UIPalette.h>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

namespace Soul
{
	class SOULAPI UI : public sf::Transformable
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
		UI(sf::Vector2f size);
		UI(f32 width, f32 height);

		UI(const UI& other);
		UI(UI&& other) noexcept;

		UI& operator=(const UI& other);
		UI& operator=(UI&& other) noexcept;

		virtual ~UI();

		const sf::Vector2f& GetSize() const;
		const UI* GetParent() const;

		bool Update(f32 dt);
		void Draw(sf::RenderStates states) const;

		const UIAnchor& GetMainAnchor() const;
		const UIAnchor& GetWeightingAnchor() const;
		f32 GetAnchorWeight() const;
		sf::Vector2f GetAnchorPosition(UIAnchor anchor) const;
		void SetAnchor(UIAnchor anchor);
		void SetWeightingAnchor(UIAnchor anchor);
		void SetAnchorWeight(f32 weight);

		const UIAnchor& GetOrigin() const;
		void SetOrigin(UIAnchor anchor);

		void SetUIPalette(const UIPalette& palette);
		const UIPalette& GetUIPalette() const;

		void SetParent(UI* parent);

		sf::Vector2f GetWorldPosition();

		virtual void Redraw();

		virtual void Resize(sf::Vector2f newSize) = 0;
		virtual void Resize(f32 width, f32 height) = 0;
	
	protected:
		virtual void ResetColors() = 0;

		virtual bool UpdateSelf(f32 dt) = 0;
		virtual void DrawSelf(sf::RenderStates states) const = 0;
		virtual bool UpdateChildren(f32 dt);
		virtual void DrawChildren(sf::RenderStates states) const;

	protected:
		sf::Vector2f m_Size;
		UI* m_Parent;
		UIAnchor m_MainAnchor;
		UIAnchor m_WeightingAnchor;
		f32 m_AnchorWeight;
		UIPalette m_Palette;
		UIAnchor m_Origin;
	};
}