#pragma once

#include <Defines.h>
#include <IO/Controller.h>
#include <IO/ControlsMap.h>
#include <IO/Gamepad.h>
#include <IO/Keyboard.h>
#include <Structures/Map.h>

typedef i8 ControllerId;

namespace Soul
{
	class SOULAPI InputManager
	{
	public:
		InputManager() = delete;

		static bool Initialize();
		static void Shutdown();


		/*
		Used to update an already-connected controller's controls. If the
		keyboard controls are being updated, id should be -1.
		*/
		static void UpdateControllerControls(ControllerId id, const char* controlsFile);

		/*
		Called every frame to update control states.
		*/
		static void UpdateControllers();
		
		/*
		Called every time input is detected to update all connected
		controllers.
		*/
		static void ReceivedInput(sf::Event input);

		/*
		Get the input information about a specific control, e.g. "Jump".
		*/
		static Controller::ControlState GetControlState(ControllerId id, const char* control);

		/*
		Gets the change in mouse position from last frame.
		*/
		static sf::Vector2i GetMouseDelta();

	private:
		static void RegisterGamepad(ControllerId id);
		static void DisconnectGamepad(ControllerId id);

	private:
		static sf::Vector2i m_MouseDelta;
		static sf::Vector2i m_LastMousePos;
		static Keyboard* m_Keyboard;
		static Map<ControllerId, Gamepad>* m_Gamepads;
	};
}