#include "Renderer.h"

namespace Soul
{
	sf::RenderWindow* Renderer::m_Window;
	
	bool Renderer::Initialize(sf::RenderWindow* window)
	{
		m_Window = window;

		return true;
	}

	void Renderer::Shutdown()
	{
		// Currently nothing
	}

	void Renderer::Render(const sf::Drawable& toRender, sf::RenderStates states, sf::RenderTarget* target)
	{
		if (!target)
			target = m_Window;

		target->draw(toRender, states);
	}

	const sf::RenderWindow& Renderer::GetWindow()
	{
		return *m_Window;
	}
}