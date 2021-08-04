#include "UIPalette.h"

#include <cstdarg>

namespace Soul
{
	UIPalette::UIPalette(u8 count, sf::Color colors, ...) :
		m_Colors(NEW_ARRAY(sf::Color, count)),
		m_Count(count)
	{
		ASSERT(count > 0);

		std::va_list args;
		va_start(args, colors);
		for (u8 i = 0; i < count; ++i)
			new (&m_Colors[i]) sf::Color(va_arg(args, sf::Color));
		va_end(args);
	}

	UIPalette::UIPalette(u8 count, sf::Color* colorArray) :
		m_Colors(NEW_ARRAY(sf::Color, count)),
		m_Count(count)
	{
		ASSERT(count > 0);

		for (u8 i = 0; i < count; ++i)
			new (&m_Colors[i]) sf::Color(colorArray[i]);
	}

	UIPalette::UIPalette(const UIPalette& other) :
		m_Colors(NEW_ARRAY(sf::Color, other.m_Count)),
		m_Count(other.m_Count)
	{
		for (u8 i = 0; i < m_Count; ++i)
			new (&m_Colors[i]) sf::Color(other.m_Colors[i]);
	}

	UIPalette::UIPalette(UIPalette&& other) noexcept :
		m_Colors(std::move(other.m_Colors)),
		m_Count(other.m_Count)
	{
	}

	UIPalette& UIPalette::operator=(const UIPalette& other)
	{
		for (u8 i = 0; i < m_Count; ++i)
			DELETE(&m_Colors[i]);

		m_Colors = NEW_ARRAY(sf::Color, other.m_Count);
		m_Count = other.m_Count;

		for (u8 i = 0; i < m_Count; ++i)
			new (&m_Colors[i]) sf::Color(other.m_Colors[i]);

		return *this;
	}

	UIPalette& UIPalette::operator=(UIPalette&& other) noexcept
	{
		for (u8 i = 0; i < m_Count; ++i)
			DELETE(&m_Colors[i]);

		m_Colors = std::move(other.m_Colors);
		m_Count = other.m_Count;
	}

	UIPalette::~UIPalette()
	{
		for (u8 i = 0; i < m_Count; ++i)
			DELETE(&m_Colors[i]);
	}

	const sf::Color& UIPalette::GetColor(u8 index) const
	{
		if (index >= m_Count)
			index = m_Count - 1;
	
		return m_Colors[index];
	}

	void UIPalette::SetColor(u8 index, sf::Color color)
	{
		ASSERT(index < m_Count);
		m_Colors[index] = color;
	}
}