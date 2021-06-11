#include "Gamepad.h"

#include <IO/ControlsMap.h>
#include <Math/Functions.h>

namespace Soul
{
	Gamepad::Gamepad(const char* controlsFile, i32 controllerId) :
		Controller(controlsFile),
		m_ControllerId(controllerId)
	{
		LoadMappings(m_ControlsMap);
	}

	Gamepad::Gamepad(Gamepad&& other) noexcept :
		Controller(std::move(other)),
		m_ButtonStates(std::move(other.m_ButtonStates)),
		m_AxisStates(std::move(other.m_AxisStates)),
		m_ControllerId(other.m_ControllerId)
	{
	}

	Gamepad& Gamepad::operator=(Gamepad&& other) noexcept
	{
		Controller::operator=(std::move(other));
		m_ButtonStates = std::move(other.m_ButtonStates);
		m_AxisStates = std::move(other.m_AxisStates);
		m_ControllerId = other.m_ControllerId;

		return *this;
	}

	void Gamepad::LoadMappings(ControlsMap& mappings)
	{
		Vector<ControlsMap::ControlMapping*> maps = m_ControlsMap.GetAllMappings();

		for (u32 i = 0; i < maps.Count(); ++i)
		{
			ControlsMap::ControlMapping& current = *maps[i];

			ControlState temp = {};

			if (current.axis != -1)
				m_AxisStates.AddPair(current.axis, temp);
			if (current.jButton != -1)
				m_ButtonStates.AddPair(current.jButton, temp);
		}
	}

	void Gamepad::UpdateStates()
	{
		Vector<u32*> axes = m_AxisStates.GetKeys();
		for (u32 i = 0; i < axes.Count(); ++i)
		{
			ControlState* buttonState = m_AxisStates.GetValue(*axes[i]);

			f32 axisPos = sf::Joystick::getAxisPosition((u32)m_ControllerId, (sf::Joystick::Axis) * axes[i]);
			if (axisPos != 0.0f)
			{
				buttonState->axis = axisPos;
				PressButton(buttonState->axisHeld);
			}
			else
			{
				axisPos = 0.0f;
				ReleaseButton(buttonState->axisHeld);
			}
		}

		Vector<u32*> buttons = m_ButtonStates.GetKeys();
		for (u32 i = 0; i < buttons.Count(); ++i)
		{
			ControlState* buttonState = m_ButtonStates.GetValue(*buttons[i]);

			if (sf::Joystick::isButtonPressed(m_ControllerId, *buttons[i]))
				PressButton(buttonState->state);
			else
				ReleaseButton(buttonState->state);
		}
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
		{
			finalState.axis = axisState->axis;
			finalState.axisHeld = axisState->axisHeld;
		}

		return finalState;
	}
}