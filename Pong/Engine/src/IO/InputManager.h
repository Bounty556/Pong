#pragma once

#include <Defines.h>
#include <Core/String.h>
#include <Structures/Map.h>
#include <Structures/Vector.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Soul
{
	class InputManager
	{
	public:
		enum KeyState
		{
			Up,
			Pressed,
			Down,
			Released
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

		static sf::Vector2f GetMousePosition(bool relativeToWindow);
		static sf::Vector2f GetMouseDelta();

		static void AddControlAlias(const char* alias, sf::Keyboard::Key key);
		static void RemoveControlAlias(const char* alias, sf::Keyboard::Key key);

		static bool IsAliasUp(const char* alias);
		static bool IsAliasPressed(const char* alias);
		static bool IsAliasDown(const char* alias);
		static bool IsAliasReleased(const char* alias);

		static void LoadAliases(const char* controlsFile);

		static void Update();

	private:
		static bool m_IsInitialized;
		static sf::Vector2i m_LastMousePos;
		static sf::Vector2i m_MouseDelta;
		static Map<String, sf::Keyboard::Key>* m_KeyboardAliases;
		static Map<String, sf::Mouse::Button>* m_MouseAliases;
		static Vector<KeyState>* m_KeyStates;
		static Vector<KeyState>* m_MouseStates;
	};
}