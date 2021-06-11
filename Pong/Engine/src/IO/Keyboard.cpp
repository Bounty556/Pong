#include "Keyboard.h"

namespace Soul
{
	Keyboard::Keyboard(const char* controlsFile) :
		Controller(controlsFile),
		m_MouseStates(PARTITION_ARRAY(ControlState, sf::Mouse::ButtonCount)),
		m_KeyboardStates()
	{
		for (u8 i = 0; i < sf::Mouse::ButtonCount; ++i)
			new (&m_MouseStates[i]) ControlState{};
	}

	Keyboard::Keyboard(Keyboard&& other) noexcept :
		Controller(std::move(other)),
		m_MouseStates(other.m_MouseStates),
		m_KeyboardStates(std::move(other.m_KeyboardStates))
	{
		other.m_MouseStates = nullptr;
	}

	Keyboard::~Keyboard()
	{
		if (!m_MouseStates)
			MemoryManager::FreeMemory(m_MouseStates);
	}

	Keyboard& Keyboard::operator=(Keyboard&& other) noexcept
	{
		Controller::operator=(std::move(other));
		m_MouseStates = other.m_MouseStates;
		m_KeyboardStates = std::move(other.m_KeyboardStates);
		other.m_MouseStates = nullptr;

		return *this;
	}

	void Keyboard::ButtonEvent(sf::Event event)
	{
		if (event.type == sf::Event::MouseButtonPressed ||
			event.type == sf::Event::MouseButtonReleased)
			MouseEvent(event);
		else
			KeyboardEvent(event);
	}

	void Keyboard::KeyboardEvent(sf::Event event)
	{
		u32 key = event.key.code;
		ControlState* controlState = m_KeyboardStates.GetValue(key);
		i8 difference = (event.type == sf::Event::KeyPressed) ? 1 : -1;

		if (!controlState)
		{
			m_KeyboardStates.AddPair(key, { (Controller::ButtonState)difference, 0.0f });
			return;
		}

		controlState->state = (Controller::ButtonState)difference;
	}

	void Keyboard::MouseEvent(sf::Event event)
	{
		u32 button = event.mouseButton.button;
		ControlState& controlState = m_MouseStates[button];
		i8 difference = (event.type == sf::Event::MouseButtonPressed) ? 1 : -1;

		controlState.state = (Controller::ButtonState)difference;
	}

	Controller::ControlState Keyboard::GetControlState(const char* control)
	{
		ControlsMap::ControlMapping mapping = m_ControlsMap.GetControlMapping(control);
		ControlState* keyState = m_KeyboardStates.GetValue(mapping.key);
		ControlState& mouseState = m_MouseStates[mapping.mButton];

		ControlState finalState = {};

		if (mouseState.state != Controller::None)
			finalState.state = mouseState.state;
		if (keyState)
		{
			switch (finalState.state)
			{
				case Controller::None:
				{
					finalState.state = keyState->state;
				} break;
				case Controller::Released:
				{
					if (keyState->state == Controller::Pressed)
						finalState.state = keyState->state;
				}
			}
		}

		return finalState;
	}
}