#include "Gamepad.h"

#include <IO/ControlsMap.h>
#include <Math/Functions.h>

namespace Soul
{
	Gamepad::Gamepad(const char* controlsFile) :
		Controller(controlsFile)
	{
	}

	Gamepad::Gamepad(Gamepad&& other) noexcept :
		Controller(std::move(other)),
		m_ButtonStates(std::move(other.m_ButtonStates)),
		m_AxisStates(std::move(other.m_AxisStates))
	{
	}

	Gamepad& Gamepad::operator=(Gamepad&& other) noexcept
	{
		Controller::operator=(std::move(other));
		m_ButtonStates = std::move(other.m_ButtonStates);
		m_AxisStates = std::move(other.m_AxisStates);

		return *this;
	}

	void Gamepad::ButtonEvent(sf::Event event)
	{
		u32 button = event.joystickButton.button;
		ControlState* controlState = m_ButtonStates.GetValue(button);
		i8 difference = (event.type == sf::Event::JoystickButtonPressed) ? 1 : -1;


		if (!controlState)
		{
			m_ButtonStates.AddPair(button, { (Controller::ButtonState)difference, 0.0f });
			return;
		}

		controlState->state = (Controller::ButtonState)difference;
	}

	void Gamepad::AxisEvent(sf::Event event)
	{
		u32 axis = event.joystickMove.axis;
		f32 position = event.joystickMove.position;
		ControlState* controlState = m_AxisStates.GetValue(axis);

		if (!controlState)
		{
			m_AxisStates.AddPair(axis, { Controller::None, position });
			return;
		}

		controlState->axis = position;
	}

	Controller::ControlState Gamepad::GetControlState(const char* control)
	{
		ControlsMap::ControlMapping mapping = m_ControlsMap.GetControlMapping(control);
		ControlState* buttonState = m_ButtonStates.GetValue(mapping.jButton);
		ControlState* axisState = m_AxisStates.GetValue(mapping.axis);

		ControlState finalState = {};

		if (buttonState)
			finalState.state = buttonState->state;
		if (axisState)
			finalState.axis = axisState->axis;

		return finalState;
	}
}