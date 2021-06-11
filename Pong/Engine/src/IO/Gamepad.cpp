#include "Gamepad.h"

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
		// TODO: Update button state in ControlsMap
	}

	void Gamepad::AxisEvent(sf::Event event)
	{
		// TODO: Update axis state in ControlsMap
	}

	Controller::ControlState Gamepad::GetControlState(const char* control)
	{
		// TODO: DO
		Controller::ControlState state{};

		return state;
	}
}