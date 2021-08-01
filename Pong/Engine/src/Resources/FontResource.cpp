#include "FontResource.h"

namespace Soul
{
	FontResource::FontResource(const char* filePath) :
		m_Font(NEW(sf::Font))
	{
		if (!m_Font->loadFromFile(filePath))
		{
			LOG_ERROR("Failed to load font from path %s", filePath);
			m_Font = nullptr;
		}
	}

	FontResource::FontResource(FontResource&& other) noexcept :
		m_Font(std::move(other.m_Font))
	{
	}

	FontResource& FontResource::operator=(FontResource&& other) noexcept
	{
		m_Font = std::move(other.m_Font);

		return *this;
	}

	const sf::Font* FontResource::GetFont() const
	{
		return m_Font.Raw();
	}
}