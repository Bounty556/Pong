#include "InputManager.h"

#include <Memory/MemoryManager.h>

namespace Soul
{
	Controller* InputManager::m_Controllers;
	u8 InputManager::m_ControllerCount;
	ControlsMap* InputManager::m_DefaultControls;

	bool InputManager::Initialize()
	{
		m_Controllers = PARTITION_ARRAY(Controller, InputManager::MaxControllers);
		m_ControllerCount = 0;

		m_DefaultControls = PARTITION(ControlsMap, "res/defaultControls.controls");

		// Set the keyboard up to use the default controls
		new (m_Controllers) Controller(*m_DefaultControls, Controller::ControllerType::Keyboard);
	}

	void InputManager::Shutdown()
	{
		MemoryManager::FreeMemory(m_Controllers);
		MemoryManager::FreeMemory(m_DefaultControls);
	}
	
	InputManager::ControllerId InputManager::RegisterGamepad()
	{
		ASSERT(m_ControllerCount < MaxControllers);

		new (&m_Controllers[m_ControllerCount++]) Controller(*m_DefaultControls, Controller::ControllerType::Gamepad);

		return (InputManager::ControllerId)m_ControllerCount;
	}

	InputManager::ControllerId InputManager::RegisterGamepad(const char* controlsFile)
	{
		ASSERT(m_ControllerCount < MaxControllers);

		new (&m_Controllers[m_ControllerCount++]) Controller(controlsFile, Controller::ControllerType::Gamepad);

		return (InputManager::ControllerId)m_ControllerCount;
	}

	void InputManager::UpdateControllerControls(ControllerId id, const char* controlsFile)
	{
		m_Controllers[id].UpdateControlsFile(controlsFile);
	}

	void InputManager::DisconnectController(ControllerId id)
	{
		// TODO: Figure out
	}

	void InputManager::UpdateControllerState(ControllerId id, sf::Event input)
	{
		m_Controllers[id].UpdateState(input);
	}

	Controller::ControlState InputManager::GetControlState(ControllerId id, const char* control)
	{
		return m_Controllers[id].GetControlState(control);
	}
}