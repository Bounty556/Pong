#pragma once

#include <Defines.h>
#include <IO/ControlsMap.h>

#include <SFML/Window/Event.hpp>

namespace Soul
{
	class Controller
	{
	public:
		enum ButtonState
		{
			None = 0,
			Released = 1,
			Pressed = 2,
			Down = 3
		};

		struct ControlState
		{
			ButtonState state;
			ButtonState axisHeld;
			f32 axis;
		};

	public:
		Controller(const char* controlsFile);

		Controller(const Controller&) = delete;
		Controller(Controller&& other) noexcept;

		virtual ~Controller();

		Controller& operator=(const Controller&) = delete;
		Controller& operator=(Controller&& other) noexcept;

		void UpdateControlsFile(const char* controlsFile);

		virtual void LoadMappings(ControlsMap& mappings) = 0;
		virtual void UpdateStates() = 0;
		virtual ControlState GetControlState(const char* control) = 0;

	protected:
		void PressButton(ButtonState& state);
		void ReleaseButton(ButtonState& state);

	protected:
		ControlsMap m_ControlsMap;
	};
}