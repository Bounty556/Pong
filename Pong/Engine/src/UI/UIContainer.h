#pragma once

#include <Structures/Vector.h>
#include <UI/UIComponent.h>

#include <SFML/Graphics.hpp>

namespace Soul
{
	class SOULAPI UIContainer
	{
	public:
		UIContainer();
		
		~UIContainer();

		/*
		Adds a new UI Component to this UI Container, which will automatically be drawn and
		updated.
		*/
		void AddUIComponent(UIComponent* component);
		
		void Update(f32 dt);
		
		void Draw(sf::RenderStates states) const;
		
		/*
		Sets the provided UI Component to be the hovered component in this UI Container.
		*/
		void SelectComponent(UIComponent* component);

	private:
		Vector<UIComponent*> m_Components;
		UIComponent* m_HoveredComponent;
	};
}