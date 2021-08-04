#pragma once

#include <Defines.h>
#include <Memory/UniquePointer.h>

#include <SFML/Graphics/Color.hpp>

namespace Soul
{
	/*
	Class to be used with UI elements. Contains a list of predefined colors for
	the UI element to query and use.
	*/
	class SOULAPI UIPalette
	{
	public:
		UIPalette(u8 count, ...);
		UIPalette(u8 count, sf::Color* colorArray);

		UIPalette(const UIPalette& other);
		UIPalette(UIPalette&& other) noexcept;

		UIPalette& operator=(const UIPalette& other);
		UIPalette& operator=(UIPalette&& other) noexcept;

		~UIPalette();

		const sf::Color& GetColor(u8 index) const;
		void SetColor(u8 index, sf::Color color);

	private:
		UniquePointer<sf::Color> m_Colors;
		u8 m_Count;
	};
}