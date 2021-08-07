#include "InputManager.h"

#include <SFML/Window/Mouse.hpp>

#define KeyAliasMap Soul::Map<Soul::String, sf::Keyboard::Key>
#define MouseAliasMap Soul::Map<Soul::String, sf::Mouse::Button>

namespace Soul
{
	bool InputManager::m_IsInitialized = false;
	sf::Vector2i InputManager::m_LastMousePos;
	sf::Vector2i InputManager::m_MouseDelta;
	KeyAliasMap* InputManager::m_KeyboardAliases;
	MouseAliasMap* InputManager::m_MouseAliases;
	Vector<InputManager::KeyState>* InputManager::m_KeyStates;
	Vector<InputManager::KeyState>* InputManager::m_MouseDelta;

	bool InputManager::Initialize()
	{
		ASSERT(!m_IsInitialized);

		m_LastMousePos = sf::Mouse::getPosition();
		m_MouseDelta = sf::Vector2i(0, 0);
		m_KeyboardAliases = NEW(KeyAliasMap);
		m_MouseAliases = NEW(MouseAliasMap);
		m_KeyStates = NEW(Vector<InputManager::KeyState>, sf::Keyboard::KeyCount);
		m_MouseStates = NEW(Vector<InputManager::KeyState>, sf::Mouse::ButtonCount);

		m_IsInitialized = true;
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

	}

	bool InputManager::IsKeyPressed(sf::Keyboard::Key key)
	{

	}

	bool InputManager::IsKeyDown(sf::Keyboard::Key key)
	{

	}

	bool InputManager::IsKeyReleased(sf::Keyboard::Key key)
	{

	}

	bool InputManager::IsMouseButtonUp(sf::Mouse::Button button)
	{

	}

	bool InputManager::IsMouseButtonPressed(sf::Mouse::Button button)
	{

	}

	bool InputManager::IsMouseButtonDown(sf::Mouse::Button button)
	{

	}

	bool InputManager::IsMouseButtonReleased(sf::Mouse::Button button)
	{

	}

	sf::Vector2f InputManager::GetMousePosition(bool relativeToWindow)
	{

	}

	sf::Vector2f InputManager::GetMouseDelta()
	{

	}

	void InputManager::AddControlAlias(const char* alias, sf::Keyboard::Key key)
	{

	}

	void InputManager::RemoveControlAlias(const char* alias, sf::Keyboard::Key key)
	{

	}

	bool InputManager::IsAliasUp(const char* alias)
	{

	}

	bool InputManager::IsAliasPressed(const char* alias)
	{

	}

	bool InputManager::IsAliasDown(const char* alias)
	{

	}

	bool InputManager::IsAliasReleased(const char* alias)
	{

	}

	void InputManager::LoadAliases(const char* controlsFile)
	{

	}

	void InputManager::Update()
	{

	}
}