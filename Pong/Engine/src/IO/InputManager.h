#pragma once

#include <Defines.h>
#include <IO/Controller.h>
#include <IO/ControlsMap.h>

namespace Soul
{
	class SOULAPI InputManager
	{
	public:
		enum ControllerId
		{
			Keyboard = 0,
			Controller1,
			Controller2,
			Controller3,
			Controller4,
			Controller5,
			Controller6,
			Controller7,
			Controller8,
			MaxControllers
		};

	public:
		InputManager() = delete;

		static bool Initialize();
		static void Shutdown();

		static ControllerId RegisterGamepad();
		static ControllerId RegisterGamepad(const char* controlsFile);

		static void UpdateControllerControls(ControllerId id, const char* controlsFile);

		static void DisconnectController(ControllerId id);

		static void UpdateControllerState(ControllerId id, sf::Event input);

		static Controller::ControlState GetControlState(ControllerId id, const char* control);

	private:
		static Controller* m_Controllers;
		static u8 m_ControllerCount;
		static ControlsMap* m_DefaultControls;
	};
}