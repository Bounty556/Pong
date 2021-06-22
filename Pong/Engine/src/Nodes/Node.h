#pragma once

#include <Defines.h>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace Soul
{
	class SOULAPI Node : public sf::Transformable
	{
	public:
		Node();
		
		virtual ~Node();

		virtual void Update(f32 dt) = 0;
		virtual void Draw(sf::RenderStates states) const = 0;

		sf::Vector2f GetWorldPosition() const;

	private:
		// TODO: Add children
		Node* m_Parent;
	};
}