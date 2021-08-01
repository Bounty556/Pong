#pragma once

#include <Resources/IResource.h>
#include <Memory/UniquePointer.h>

#include <SFML/Graphics/Font.hpp>

namespace Soul
{
	class SOULAPI FontResource : public IResource
	{
	public:
		FontResource(const char* filePath);

		FontResource(const FontResource& other) = delete;
		FontResource(FontResource&& other) noexcept;

		FontResource& operator=(const FontResource& other) = delete;
		FontResource& operator=(FontResource&& other) noexcept;

		const sf::Font* GetFont() const;

	private:
		UniquePointer<sf::Font> m_Font;
	};
}