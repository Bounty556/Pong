#include "InputManager.h"

#include <Rendering/Renderer.h>
#include <IO/TextFileReader.h>
#include <IO/StringReader.h>

#define KeyAliasMap Soul::Map<Soul::String, sf::Keyboard::Key>
#define MouseAliasMap Soul::Map<Soul::String, sf::Mouse::Button>

namespace Soul
{
	bool InputManager::m_IsInitialized = false;
	sf::Vector2i InputManager::m_LastMousePos;
	sf::Vector2i InputManager::m_MouseDelta;
	KeyAliasMap* InputManager::m_KeyboardAliases;
	MouseAliasMap* InputManager::m_MouseAliases;
	InputManager::KeyState* InputManager::m_KeyStates;
	InputManager::KeyState* InputManager::m_MouseStates;

	bool InputManager::Initialize()
	{
		ASSERT(!m_IsInitialized);

		m_LastMousePos = sf::Mouse::getPosition();
		m_MouseDelta = sf::Vector2i(0, 0);
		m_KeyboardAliases = NEW(KeyAliasMap);
		m_MouseAliases = NEW(MouseAliasMap);
		m_KeyStates = NEW_ARRAY(KeyState, sf::Keyboard::KeyCount);
		m_MouseStates = NEW_ARRAY(KeyState, sf::Mouse::ButtonCount);

		for (u8 i = 0; i < sf::Keyboard::KeyCount; ++i)
			m_KeyStates[i] = KeyState::Up;
		for (u8 i = 0; i < sf::Mouse::ButtonCount; ++i)
			m_MouseStates[i] = KeyState::Up;

		m_IsInitialized = true;

		return true;
	}

	void InputManager::Shutdown()
	{
		ASSERT(m_IsInitialized);

		DELETE(m_KeyboardAliases);
		DELETE(m_MouseAliases);
		DELETE(m_KeyStates);
		DELETE(m_MouseStates);

		m_IsInitialized = false;
	}

	bool InputManager::IsKeyUp(sf::Keyboard::Key key)
	{
		return m_KeyStates[(u32)key] & KeyState::Up;
	}

	bool InputManager::IsKeyPressed(sf::Keyboard::Key key)
	{
		return m_KeyStates[(u32)key] & KeyState::Pressed;
	}

	bool InputManager::IsKeyDown(sf::Keyboard::Key key)
	{
		return m_KeyStates[(u32)key] & KeyState::Down;
	}

	bool InputManager::IsKeyReleased(sf::Keyboard::Key key)
	{
		return m_KeyStates[(u32)key] & KeyState::Released;
	}

	bool InputManager::IsMouseButtonUp(sf::Mouse::Button button)
	{
		return m_MouseStates[(u32)button] & KeyState::Up;
	}

	bool InputManager::IsMouseButtonPressed(sf::Mouse::Button button)
	{
		return m_MouseStates[(u32)button] & KeyState::Pressed;
	}

	bool InputManager::IsMouseButtonDown(sf::Mouse::Button button)
	{
		return m_MouseStates[(u32)button] & KeyState::Down;
	}

	bool InputManager::IsMouseButtonReleased(sf::Mouse::Button button)
	{
		return m_MouseStates[(u32)button] & KeyState::Released;
	}

	sf::Vector2i InputManager::GetMousePosition(bool relativeToWindow)
	{
		if (relativeToWindow)
			return sf::Mouse::getPosition(Renderer::GetWindow());
		else
			return sf::Mouse::getPosition();
	}

	sf::Vector2i InputManager::GetMouseDelta()
	{
		return m_MouseDelta;
	}

	void InputManager::AddKeyboardAlias(const char* alias, sf::Keyboard::Key key)
	{
		sf::Keyboard::Key* found = m_KeyboardAliases->GetValue(alias);

		if (!found)
			m_KeyboardAliases->AddPair(alias, key);
	}

	void InputManager::RemoveKeyboardAlias(const char* alias)
	{
		m_KeyboardAliases->RemovePair(alias);
	}

	void InputManager::AddMouseAlias(const char* alias, sf::Mouse::Button button)
	{
		sf::Mouse::Button* found = m_MouseAliases->GetValue(alias);

		if (!found)
			m_MouseAliases->AddPair(alias, button);
	}

	void InputManager::RemoveMouseAlias(const char* alias)
	{
		m_MouseAliases->RemovePair(alias);
	}

	bool InputManager::IsAliasUp(const char* alias)
	{
		sf::Keyboard::Key* foundKey = m_KeyboardAliases->GetValue(alias);
		sf::Mouse::Button* foundButton = m_MouseAliases->GetValue(alias);

		return (foundKey && IsKeyUp(*foundKey)) || (foundButton && IsMouseButtonUp(*foundButton));
	}

	bool InputManager::IsAliasPressed(const char* alias)
	{
		sf::Keyboard::Key* foundKey = m_KeyboardAliases->GetValue(alias);
		sf::Mouse::Button* foundButton = m_MouseAliases->GetValue(alias);

		return (foundKey && IsKeyPressed(*foundKey)) || (foundButton && IsMouseButtonPressed(*foundButton));
	}

	bool InputManager::IsAliasDown(const char* alias)
	{
		sf::Keyboard::Key* foundKey = m_KeyboardAliases->GetValue(alias);
		sf::Mouse::Button* foundButton = m_MouseAliases->GetValue(alias);

		return (foundKey && IsKeyDown(*foundKey)) || (foundButton && IsMouseButtonDown(*foundButton));
	}

	bool InputManager::IsAliasReleased(const char* alias)
	{
		sf::Keyboard::Key* foundKey = m_KeyboardAliases->GetValue(alias);
		sf::Mouse::Button* foundButton = m_MouseAliases->GetValue(alias);

		return (foundKey && IsKeyReleased(*foundKey)) || (foundButton && IsMouseButtonReleased(*foundButton));
	}

	// Example controlsFile:
	// Jump:
	// k 10
	void InputManager::LoadAliases(const char* controlsFile)
	{
		TextFileReader file(controlsFile);
		StringReader stringReader(file.GetString());
		String line;
		String alias;
		
		while (!stringReader.IsAtEnd())
		{
			line = stringReader.GetNextLine();
			
			if (line.FindFirstOf(':') != -1)
			{
				alias = line.Substring(0, line.FindFirstOf(':'));
			}
			else
			{
				if (line[0] == 'k')
					AddKeyboardAlias(alias.GetCString(), (sf::Keyboard::Key)line.Substring(1).ToInt());
				else if (line[0] == 'm')
					AddMouseAlias(alias.GetCString(), (sf::Mouse::Button)line.Substring(1).ToInt());
			}
		}
	}

	void InputManager::Update()
	{
		// Loop through keyboard keys and update
		for (u8 i = 0; i < sf::Keyboard::KeyCount; ++i)
		{
			if (m_KeyStates[i] & KeyState::Pressed)
				m_KeyStates[i] = KeyState::Down;
			else if (m_KeyStates[i] & KeyState::Released)
				m_KeyStates[i] = KeyState::Up;
		}

		//// Loop through mouse buttons and update
		for (u8 i = 0; i < sf::Mouse::ButtonCount; ++i)
		{
			if (m_MouseStates[i] & KeyState::Pressed)
				m_MouseStates[i] = KeyState::Down;
			else if (m_MouseStates[i] & KeyState::Released)
				m_MouseStates[i] = KeyState::Up;
		}

		// TODO: Loop through and update controllers
	}

	void InputManager::ProcessInput(sf::Event e)
	{
		switch (e.type)
		{
			case sf::Event::KeyPressed:
			{
				if (!(m_KeyStates[e.key.code] & KeyState::Down))
					m_KeyStates[e.key.code] = (KeyState)(KeyState::Pressed | KeyState::Down);
			} break;

			case sf::Event::KeyReleased:
			{
				if (!(m_KeyStates[e.key.code] & KeyState::Up))
					m_KeyStates[e.key.code] = (KeyState)(KeyState::Released | KeyState::Up);
			} break;

			case sf::Event::MouseButtonPressed:
			{
				if (!(m_MouseStates[e.key.code] & KeyState::Down))
					m_MouseStates[e.mouseButton.button] = (KeyState)(KeyState::Pressed | KeyState::Down);
			} break;

			case sf::Event::MouseButtonReleased:
			{
				if (!(m_MouseStates[e.key.code] & KeyState::Up))
					m_MouseStates[e.mouseButton.button] = (KeyState)(KeyState::Released | KeyState::Up);
			} break;
		}
	}
}