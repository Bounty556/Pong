#include "Keyboard.h"

namespace Soul
{
	Keyboard::Keyboard(const char* controlsFile) :
		Controller(controlsFile),
		m_MouseStates(),
		m_KeyboardStates()
	{
		LoadMappings(m_ControlsMap);
	}

	Keyboard::Keyboard(Keyboard&& other) noexcept :
		Controller(std::move(other)),
		m_MouseStates(std::move(other.m_MouseStates)),
		m_KeyboardStates(std::move(other.m_KeyboardStates))
	{
	}

	Keyboard& Keyboard::operator=(Keyboard&& other) noexcept
	{
		Controller::operator=(std::move(other));
		m_MouseStates = std::move(other.m_MouseStates);
		m_KeyboardStates = std::move(other.m_KeyboardStates);

		return *this;
	}

	void Keyboard::LoadMappings(ControlsMap& mappings)
	{
		Vector<ControlsMap::ControlMapping*> maps = m_ControlsMap.GetAllMappings();

		for (u32 i = 0; i < maps.Count(); ++i)
		{
			ControlsMap::ControlMapping& current = *maps[i];

			ControlState temp = {};

			if (current.mButton != -1)
				m_MouseStates.AddPair(current.mButton, temp);
			if (current.key != -1)
				m_KeyboardStates.AddPair(current.key, temp);
		}
	}

	void Keyboard::UpdateStates()
	{
		Vector<u32*> mouseButtons = m_MouseStates.GetKeys();
		for (u32 i = 0; i < mouseButtons.Count(); ++i)
		{
			ControlState* buttonState = m_MouseStates.GetValue(*mouseButtons[i]);
		
			if (sf::Mouse::isButtonPressed((sf::Mouse::Button)*mouseButtons[i]))
				PressButton(buttonState->state);
			else
				ReleaseButton(buttonState->state);
		}

		Vector<u32*> keys = m_KeyboardStates.GetKeys();
		for (u32 i = 0; i < keys.Count(); ++i)
		{
			ControlState* buttonState = m_KeyboardStates.GetValue(*keys[i]);

			if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)*keys[i]))
				PressButton(buttonState->state);
			else
				ReleaseButton(buttonState->state);
		}
	}

	Controller::ControlState Keyboard::GetControlState(const char* control)
	{
		ControlsMap::ControlMapping mapping = m_ControlsMap.GetControlMapping(control);
		ControlState* keyState = m_KeyboardStates.GetValue(mapping.key);
		ControlState* mouseState = m_MouseStates.GetValue(mapping.jButton);

		ControlState finalState = {};

		if (keyState && mouseState)
			finalState.state = (Controller::ButtonState)Math::Max((i32)keyState->state, (i32)mouseState->state);
		else if (keyState)
			finalState.state = keyState->state;
		else if (mouseState)
			finalState.state = mouseState->state;
		
		return finalState;
	}
}