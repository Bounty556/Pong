#include "InputManager.h"

#include <Memory/MemoryManager.h>

namespace Soul
{
	sf::Vector2i InputManager::m_LastMousePos;
	sf::Vector2i InputManager::m_MouseDelta;
	Keyboard* InputManager::m_Keyboard;
	Map<ControllerId, Gamepad>* InputManager::m_Gamepads;

	bool InputManager::Initialize()
	{
		typedef Map<ControllerId, Gamepad> GamepadMap;
		m_Gamepads = NEW(GamepadMap, 8);
		m_Keyboard = NEW(Keyboard, "res/Controls/defaultControls.controls");
		m_LastMousePos = sf::Mouse::getPosition();
		m_MouseDelta = sf::Vector2i(0, 0);

		return true;
	}

	void InputManager::Shutdown()
	{
		DELETE(m_Keyboard);
		DELETE(m_Gamepads);
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
		m_MouseDelta = sf::Mouse::getPosition() - m_LastMousePos;
		m_LastMousePos = sf::Mouse::getPosition();
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

	sf::Vector2i InputManager::GetMouseDelta()
	{
		return m_MouseDelta;
	}

	void InputManager::RegisterGamepad(ControllerId id)
	{
		m_Gamepads->AddPair(id, Gamepad("res/Controls/defaultControls.controls", id));
		LOG_DEBUG("Gamepad %d added", id);
	}

	void InputManager::DisconnectGamepad(ControllerId id)
	{
		m_Gamepads->RemovePair(id);
		LOG_DEBUG("Gamepad %d disconnected", id);
	}
}