#pragma once

#include <IO/ControlsMap.h>
#include <SFML/Window/Event.hpp>

namespace Soul
{
	class Controller
	{
	public:
		enum ControllerType
		{
			Keyboard,
			Gamepad
		};

		enum ButtonState
		{
			Pressed,
			Down,
			Released,
			None
		};

		struct ControlState
		{
			ButtonState state;
			f32 xAxis;
			f32 yAxis;
		};

	public:
		Controller(const ControlsMap& map, ControllerType type);
		Controller(const char* controlsFile, ControllerType type);

		void UpdateControlsFile(const char* controlsFile);

		void UpdateState(sf::Event input);

		ControlState GetControlState(const char* control);

	private:
		ControlsMap m_ControlsMap;
		ControllerType m_ControllerType;
	};
}