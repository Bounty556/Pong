#pragma once

#include <Defines.h>
#include <Core/String.h>
#include <Structures/Map.h>
#include <Structures/Vector.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Soul
{
	class SOULAPI InputManager
	{
	public:
		enum KeyState
		{
			Up = 1,
			Pressed = 2,
			Down = 4,
			Released = 8
		};

	public:
		InputManager() = delete;

		static bool Initialize();
		
		static void Shutdown();

		static bool IsKeyUp(sf::Keyboard::Key key);
		static bool IsKeyPressed(sf::Keyboard::Key key);
		static bool IsKeyDown(sf::Keyboard::Key key);
		static bool IsKeyReleased(sf::Keyboard::Key key);

		static bool IsMouseButtonUp(sf::Mouse::Button button);
		static bool IsMouseButtonPressed(sf::Mouse::Button button);
		static bool IsMouseButtonDown(sf::Mouse::Button button);
		static bool IsMouseButtonReleased(sf::Mouse::Button button);

		static sf::Vector2i GetMousePosition(bool relativeToWindow);
		static sf::Vector2i GetMouseDelta();

		static void AddKeyboardAlias(const char* alias, sf::Keyboard::Key key);
		static void RemoveKeyboardAlias(const char* alias);
		static void AddMouseAlias(const char* alias, sf::Mouse::Button button);
		static void RemoveMouseAlias(const char* alias);
		
		static bool IsAliasUp(const char* alias);
		static bool IsAliasPressed(const char* alias);
		static bool IsAliasDown(const char* alias);
		static bool IsAliasReleased(const char* alias);

		static void LoadAliases(const char* controlsFile);

		static void Update();
		static void ProcessInput(sf::Event e);

	private:
		static bool m_IsInitialized;
		static sf::Vector2i m_LastMousePos;
		static sf::Vector2i m_MouseDelta;
		static Map<String, sf::Keyboard::Key>* m_KeyboardAliases;
		static Map<String, sf::Mouse::Button>* m_MouseAliases;
		static KeyState* m_KeyStates;
		static KeyState* m_MouseStates;
	};
}