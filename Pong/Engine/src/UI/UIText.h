#pragma once

#include <Defines.h>
#include <UI/UI.h>

#include <SFML/Graphics/Text.hpp>

namespace Soul
{
	class SOULAPI UIText : public UI
	{
	public:
		UIText(const char* text, const char* font);

		UIText(const UIText& other);
		UIText(UIText&& other) noexcept;

		UIText& operator=(const UIText& other);
		UIText& operator=(UIText&& other) noexcept;

		/*
		If the size of this text object was set manually, this will revert it
		back to being automatically sized.
		*/
		void ResetSize();

		/*
		Sets the size of this text object. This also prevents the text object
		from being automatically size if we changed the font, font size, or 
		the text contained in the string.
		*/
		void SetSize(sf::Vector2f size);

		/*
		Sets the size of this text object. This also prevents the text object
		from being automatically size if we changed the font, font size, or
		the text contained in the string.
		*/
		void SetSize(f32 width, f32 height);

		void SetText(const char* text);
		void SetFont(const char* font);
		void SetFontSize(u32 fontSize);

		virtual void Resize(sf::Vector2f newSize) override;
		virtual void Resize(f32 width, f32 height) override;

	protected:
		virtual void ResetColors() override;

		virtual bool UpdateSelf(f32 dt) override;
		virtual void DrawSelf(sf::RenderStates states) const override;

	private:
		sf::Text m_Text;
		bool m_RestrictedSize;
	};
}