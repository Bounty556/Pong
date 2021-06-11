#pragma once

#include <Defines.h>
#include <IO/Controller.h>
#include <Structures/Map.h>

namespace Soul
{
	class Gamepad : public Controller
	{
	public:
		Gamepad(const char* controlsFile, i32 controllerId);

		Gamepad(const Gamepad&) = delete;
		Gamepad(Gamepad&& other) noexcept;

		Gamepad& operator=(const Gamepad&) = delete;
		Gamepad& operator=(Gamepad&& other) noexcept;

		virtual void LoadMappings(ControlsMap& mappings) override;
		virtual void UpdateStates() override;
		virtual ControlState GetControlState(const char* control) override;

	private:
		Map<u32, ControlState> m_ButtonStates;
		Map<u32, ControlState> m_AxisStates;
		i32 m_ControllerId;
	};
}