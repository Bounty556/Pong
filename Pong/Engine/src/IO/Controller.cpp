#include "Controller.h"

namespace Soul
{
	Controller::Controller(const char* controlsFile) :
		m_ControlsMap(controlsFile)
	{
	}

	Controller::Controller(Controller&& other) noexcept :
		m_ControlsMap(std::move(other.m_ControlsMap))
	{
	}

	Controller::~Controller()
	{
	}

	Controller& Controller::operator=(Controller&& other) noexcept
	{
		m_ControlsMap = std::move(other.m_ControlsMap);

		return *this;
	}

	void Controller::UpdateControlsFile(const char* controlsFile)
	{
		m_ControlsMap = ControlsMap(controlsFile);
	}

	void Controller::PressButton(ButtonState& state)
	{
		switch (state)
		{
			case ButtonState::None:
			case ButtonState::Released:
			{
				state = ButtonState::Pressed;
			} break;
			case ButtonState::Pressed:
			{
				state = ButtonState::Down;
			} break;
		}
	}

	void Controller::ReleaseButton(ButtonState& state)
	{
		switch (state)
		{
			case ButtonState::Pressed:
			case ButtonState::Down:
			{
				state = ButtonState::Released;
			} break;
			case ButtonState::Released:
			{
				state = ButtonState::None;
			} break;
		}
	}
}