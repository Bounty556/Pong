#pragma once

#include <Structures/Map.h>
#include <Structures/Vector.h>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <functional>

namespace Soul
{
	/*
	This class is a base UI class, which can be used to hold other UI
	components, or be inherited to have specific rendering/updating behavior.

	UI components can contain other UI components, and have a few useful
	behaviors about them. They can be in one of several states:
	Hovered,
	Disabled,
	Neutral

	And may have different behaviors/ways of being rendered for each state.

	UI components are also "linked", so moving from one UI component to
	another is automatic based on the direction the controller thumbstick
	moved, or the key on the keyboard pressed (generally left, right, up,
	down).
	
	UI can also block input to it's parents. This is done through setting a UI
	component as "capturing input".
	*/
	class SOULAPI UIComponent : public sf::Transformable
	{
	public:
		enum UIState
		{
			Hovered,
			Disabled,
			Neutral
		};

		enum UIConnection
		{
			Up = 0,
			Right = 1,
			Down = 2,
			Left = 3,
			Count = 4
		};

	public:
		UIComponent(std::function<void()> activate);
		virtual ~UIComponent();

		virtual void Update(f32 dt);
		
		virtual void Draw(sf::RenderStates states) const;
		
		void Activate();

		void AddConnection(UIConnection direction, UIComponent* connectedComponent);

		// Getters
		
		UIState GetState() const;

		UIComponent* GetConnection(UIConnection connection) const;

		// Setters
		
		void SetState(UIState uiState);

	protected:
		UIState m_UIState;

	private:
		UIComponent* m_Connections[4];

		std::function<void()> m_Activate;
	};
}