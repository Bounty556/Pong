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
		InputManager() = delete;

		static bool Initialize();
		static void Shutdown();

		static ControllerId RegisterKeyboard();
		static ControllerId RegisterKeyboard(const char* controlsFile);
		static ControllerId RegisterController();
		static ControllerId RegisterController(const char* controlsFile);

		static void DisconnectController(ControllerId id);

		static void UpdateControllerStates();

		static ControlState GetControlState(const char* control);

	private:
		static Controller* m_Controllers;
		static u8 m_ControllerCount;
		static ControlsMap* m_DefaultControls;
	};
}