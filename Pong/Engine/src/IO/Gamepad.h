#pragma once

#include <Defines.h>
#include <IO/Controller.h>
#include <Structures/Map.h>

namespace Soul
{
	class Gamepad : public Controller
	{
	public:
		Gamepad(const char* controlsFile);

		Gamepad(const Gamepad&) = delete;
		Gamepad(Gamepad&& other) noexcept;

		Gamepad& operator=(const Gamepad&) = delete;
		Gamepad& operator=(Gamepad&& other) noexcept;

		virtual void ButtonEvent(sf::Event event) override;
		void AxisEvent(sf::Event event);

		virtual ControlState GetControlState(const char* control) override;

	private:
		Map<u32, ControlState> m_ButtonStates;
		Map<u32, ControlState> m_AxisStates;
	};
}