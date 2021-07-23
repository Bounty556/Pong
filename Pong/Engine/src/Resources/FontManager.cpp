#include "FontManager.h"

namespace Soul
{
	FontManager::FontManager() :
		m_FontMap()
	{
	}

	FontManager::FontManager(FontManager&& other) noexcept :
		m_FontMap(std::move(other.m_FontMap))
	{
	}

	FontManager::~FontManager()
	{
		Vector<sf::Font**> fonts = m_FontMap.GetValues();
		for (u32 i = 0; i < fonts.Count(); ++i)
			DELETE(*(fonts[i]));
	}

	FontManager& FontManager::operator=(FontManager&& other) noexcept
	{
		m_FontMap = std::move(other.m_FontMap);

		return *this;
	}

	const sf::Font* FontManager::RequestFont(const char* fontName)
	{
		// Check to see if the sound is already allocated.
		sf::Font** result = m_FontMap.GetValue(fontName);

		if (result)
			return *result;
		else
		{
			sf::Font* font = NEW(sf::Font);
			if (font->loadFromFile(fontName))
			{
				m_FontMap.AddPair(fontName, font);
				return font;
			}
			else
				DELETE(font);
		}

		return nullptr;
	}

	void FontManager::ClearAllFonts()
	{
		Vector<sf::Font**> fonts = m_FontMap.GetValues();
		for (u32 i = 0; i < fonts.Count(); ++i)
			DELETE(*(fonts[i]));

		m_FontMap.Clear();
	}

	u32 FontManager::Count() const
	{
		return m_FontMap.Count();
	}
}