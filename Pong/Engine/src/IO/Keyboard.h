#pragma once

#include <Defines.h>
#include <IO/Controller.h>
#include <Structures/Map.h>

namespace Soul
{
	class Keyboard : public Controller
	{
	public:
		Keyboard(const char* controlsFile);

		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&& other) noexcept;

		Keyboard& operator=(const Keyboard&) = delete;
		Keyboard& operator=(Keyboard&& other) noexcept;

		virtual void LoadMappings(ControlsMap& mappings) override;
		virtual void UpdateStates() override;
		virtual ControlState GetControlState(const char* control) override;

	private:
		Map<u32, ControlState> m_MouseStates;
		Map<u32, ControlState> m_KeyboardStates;
	};
}