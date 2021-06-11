#pragma once

#include <Defines.h>

#include <SFML/Graphics.hpp>

namespace Soul
{
	class SOULAPI Renderer
	{
	public:
		Renderer() = delete;

		static bool Initialize(sf::RenderWindow* window);
		static void Shutdown();

		static void Render(const sf::Drawable& toRender, sf::RenderStates states, sf::RenderTarget* target = nullptr);

	private:
		static sf::RenderWindow* m_Window;
	};
}