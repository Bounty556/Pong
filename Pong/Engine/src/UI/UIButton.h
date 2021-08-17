#pragma once

#include <Defines.h>
#include <UI/UI.h>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <functional>

namespace Soul
{
	class SOULAPI UIButton : public UI
	{
	public:
		UIButton(const char* text, const char* font, std::function<void()> callback, f32 paddingLeft = 0, f32 paddingTop = 0, f32 paddingRight = 0, f32 paddingBottom = 0);

		UIButton(const UIButton& other);
		UIButton(UIButton&& other) noexcept;

		UIButton& operator=(const UIButton& other);
		UIButton& operator=(UIButton&& other) noexcept;

		void SetPaddingLeft(f32 padding);
		void SetPaddingTop(f32 padding);
		void SetPaddingRight(f32 padding);
		void SetPaddingBottom(f32 padding);

		void SetHovered(bool hovered);
		void Activate();

		virtual void Resize(sf::Vector2f newSize) override;
		virtual void Resize(f32 width, f32 height) override;

	protected:
		virtual void ResetColors() override;

		virtual bool UpdateSelf(f32 dt) override;
		virtual void DrawSelf(sf::RenderStates states) const override;

	private:
		bool m_IsHovered;
		std::function<void()> m_Callback;
		sf::Text m_Text;
		sf::RectangleShape m_Background;
		f32 m_PaddingLeft;
		f32 m_PaddingTop;
		f32 m_PaddingRight;
		f32 m_PaddingBottom;
	};
}