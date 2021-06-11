#include "InputManager.h"

#include <Memory/MemoryManager.h>

namespace Soul
{
	Keyboard* InputManager::m_Keyboard;
	Map<ControllerId, Gamepad>* InputManager::m_Gamepads;

	bool InputManager::Initialize()
	{
		typedef Map<ControllerId, Gamepad> GamepadMap;
		m_Gamepads = PARTITION(GamepadMap, 8);

		m_Keyboard = PARTITION(Keyboard, "res/defaultControls.controls");

		return true;
	}

	void InputManager::Shutdown()
	{
		MemoryManager::FreeMemory(m_Keyboard);
		MemoryManager::FreeMemory(m_Gamepads);
	}

	void InputManager::UpdateControllerControls(ControllerId id, const char* controlsFile)
	{
		if (id == -1)
			m_Keyboard->UpdateControlsFile(controlsFile);
		else
			m_Gamepads->GetValue(id)->UpdateControlsFile(controlsFile);
	}

	void InputManager::UpdateControllers()
	{
		m_Keyboard->UpdateStates();

		Vector<ControllerId*> ids = m_Gamepads->GetKeys();
		for (u32 i = 0; i < ids.Count(); i++)
			m_Gamepads->GetValue(*ids[i])->UpdateStates();
	}

	void InputManager::ReceivedInput(sf::Event input)
	{
		switch (input.type)
		{
			case sf::Event::JoystickButtonPressed:
			case sf::Event::JoystickButtonReleased:
			{
				ControllerId id = input.joystickButton.joystickId;
				if (!m_Gamepads->GetValue(id))
					RegisterGamepad(id);
			} break;

			case sf::Event::JoystickMoved:
			{
				ControllerId id = input.joystickButton.joystickId;
				if (!m_Gamepads->GetValue(id))
					RegisterGamepad(id);
			} break;
			case sf::Event::JoystickConnected:
			{
				RegisterGamepad(input.joystickConnect.joystickId);
			} break;
			case sf::Event::JoystickDisconnected:
			{
				DisconnectGamepad(input.joystickConnect.joystickId);
			} break;
		}
	}

	Controller::ControlState InputManager::GetControlState(ControllerId id, const char* control)
	{
		if (id == -1)
			return m_Keyboard->GetControlState(control);
		else
		{
			Gamepad* gamepad = m_Gamepads->GetValue(id);

			if (gamepad)
				return gamepad->GetControlState(control);
			else
				return Controller::ControlState{};
		}
	}

	void InputManager::RegisterGamepad(ControllerId id)
	{
		m_Gamepads->AddPair(id, Gamepad("res/defaultControls.controls", id));
		LOG_DEBUG("Gamepad %d added", id);
	}

	void InputManager::DisconnectGamepad(ControllerId id)
	{
		m_Gamepads->RemovePair(id);
		LOG_DEBUG("Gamepad %d disconnected", id);
	}
}