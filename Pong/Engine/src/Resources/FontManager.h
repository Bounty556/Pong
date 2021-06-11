#pragma once

#include <Defines.h>
#include <Core/String.h>
#include <Structures/Map.h>

#include <SFML/Graphics/Font.hpp>

#define FontMap Map<Soul::String, sf::Font*>

namespace Soul
{
	/*
	Handles the loading and unloading of Font files which can be requested to be used by
	any sf::Text object via RequestFont(...). Fonts can be cleared at any time via
	ClearAllFonts().
	*/
	class SOULAPI FontManager
	{
	public:
		FontManager();

		FontManager(const FontManager&) = delete;
		FontManager(FontManager&& other) noexcept;

		~FontManager();

		FontManager& operator=(const FontManager&) = delete;
		FontManager& operator=(FontManager&& other) noexcept;

		const sf::Font* RequestFont(const char* fontName);

		void ClearAllFonts();

		u32 Count() const;

	private:
		FontMap m_FontMap;
	};
}