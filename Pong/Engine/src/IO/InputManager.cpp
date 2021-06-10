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
	}

	void InputManager::Shutdown()
	{

	}

	InputManager::ControllerId InputManager::RegisterKeyboard()
	{

	}

	InputManager::ControllerId InputManager::RegisterKeyboard(const char* controlsFile)
	{

	}
	
	InputManager::ControllerId InputManager::RegisterController()
	{

	}

	InputManager::ControllerId InputManager::RegisterController(const char* controlsFile)
	{

	}

	void InputManager::DisconnectController(ControllerId id)
	{

	}

	void InputManager::UpdateControllerStates()
	{

	}

	InputManager::ControlState InputManager::GetControlState(const char* control)
	{

	}
}