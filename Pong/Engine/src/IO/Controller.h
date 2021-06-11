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
			Pressed,
			Down,
			Released,
			None
		};

		struct ControlState
		{
			ButtonState state;
			f32 axis;
		};

	public:
		Controller(const char* controlsFile);

		Controller(const Controller&) = delete;
		Controller(Controller&& other);

		virtual ~Controller();

		Controller& operator=(const Controller&) = delete;
		Controller& operator=(Controller&& other);

		void UpdateControlsFile(const char* controlsFile);

		virtual void ButtonEvent(sf::Event event) = 0;

		virtual ControlState GetControlState(const char* control) = 0;

	protected:
		ControlsMap m_ControlsMap;
	};
}