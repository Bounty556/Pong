#include "Controller.h"

#include <IO/TextFileReader.h>
#include <IO/StringReader.h>

#define ButtonAliasMap Soul::Map<Soul::String, u32>
#define AxisAliasMap Soul::Map<Soul::String, sf::Joystick::Axis>

namespace Soul
{
	Controller::Controller(u8 joystickId, u8 playerId, const char* aliasFile/*= "res/Controls/defaultControls.controls"*/) :
		m_JoystickId(joystickId),
		m_PlayerId(playerId),
		m_ButtonStates(NEW_ARRAY(InputManager::KeyState, sf::Joystick::getButtonCount(joystickId))),
		m_ButtonAliases(NEW(ButtonAliasMap)),
		m_AxisAliases(NEW(AxisAliasMap))
	{
		for (u8 i = 0; i < sf::Keyboard::KeyCount; ++i)
			m_ButtonStates[i] = InputManager::KeyState::Up;

		LoadAliases(aliasFile);
	}

	Controller::Controller(Controller&& other) noexcept :
		m_JoystickId(other.m_JoystickId),
		m_PlayerId(other.m_PlayerId),
		m_ButtonStates(std::move(other.m_ButtonStates)),
		m_ButtonAliases(std::move(other.m_ButtonAliases)),
		m_AxisAliases(std::move(other.m_AxisAliases))
	{
	}

	Controller& Controller::operator=(Controller&& other) noexcept
	{
		m_JoystickId = other.m_JoystickId;
		m_PlayerId = other.m_PlayerId;
		m_ButtonStates = std::move(other.m_ButtonStates);
		m_ButtonAliases = std::move(other.m_ButtonAliases);
		m_AxisAliases = std::move(other.m_AxisAliases);
	}

	bool Controller::IsButtonUp(u32 button) const
	{
		return m_ButtonStates[button] & InputManager::KeyState::Up;
	}

	bool Controller::IsButtonPressed(u32 button) const
	{
		return m_ButtonStates[button] & InputManager::KeyState::Pressed;
	}

	bool Controller::IsButtonDown(u32 button) const
	{
		return m_ButtonStates[button] & InputManager::KeyState::Down;
	}

	bool Controller::IsButtonReleased(u32 button) const
	{
		return m_ButtonStates[button] & InputManager::KeyState::Released;
	}

	f32 Controller::GetAxisPos(sf::Joystick::Axis axis) const
	{
		return sf::Joystick::getAxisPosition(m_JoystickId, axis);
	}

	void Controller::AddButtonAlias(const char* alias, u32 button)
	{
		u32* found = m_ButtonAliases->GetValue(alias);

		if (!found)
			m_ButtonAliases->AddPair(alias, button);
	}

	void Controller::RemoveButtonAlias(const char* alias)
	{
		m_ButtonAliases->RemovePair(alias);
	}

	void Controller::AddAxisAlias(const char* alias, sf::Joystick::Axis axis)
	{
		sf::Joystick::Axis* found = m_AxisAliases->GetValue(alias);

		if (!found)
			m_AxisAliases->AddPair(alias, axis);
	}

	void Controller::RemoveAxisAlias(const char* alias)
	{
		m_AxisAliases->RemovePair(alias);
	}

	bool Controller::IsAliasUp(const char* alias)
	{
		u32* foundButton = m_ButtonAliases->GetValue(alias);

		return foundButton && IsButtonUp(*foundButton);
	}

	bool Controller::IsAliasPressed(const char* alias)
	{
		u32* foundButton = m_ButtonAliases->GetValue(alias);

		return foundButton && IsButtonPressed(*foundButton);
	}

	bool Controller::IsAliasDown(const char* alias)
	{
		u32* foundButton = m_ButtonAliases->GetValue(alias);

		return foundButton && IsButtonDown(*foundButton);
	}

	bool Controller::IsAliasReleased(const char* alias)
	{
		u32* foundButton = m_ButtonAliases->GetValue(alias);

		return foundButton && IsButtonReleased(*foundButton);
	}

	f32 Controller::GetAliasPosition(const char* alias)
	{
		sf::Joystick::Axis* foundAxis = m_AxisAliases->GetValue(alias);

		if (foundAxis)
			return sf::Joystick::getAxisPosition(m_JoystickId, *foundAxis);

		return 0.0f;
	}

	u8 Controller::GetJoystickId() const
	{
		return m_JoystickId;
	}

	u8 Controller::GetPlayerId() const
	{
		return m_PlayerId;
	}

	void Controller::Update()
	{
		for (u8 i = 0; i < sf::Joystick::getButtonCount(m_JoystickId); ++i)
		{
			if (m_ButtonStates[i] & InputManager::KeyState::Pressed)
				m_ButtonStates[i] = InputManager::KeyState::Down;
			else if (m_ButtonStates[i] & InputManager::KeyState::Released)
				m_ButtonStates[i] = InputManager::KeyState::Up;
		}
	}

	void Controller::LoadAliases(const char* controlsFile)
	{
		TextFileReader file(controlsFile);
		StringReader stringReader(file.GetString());
		String line;
		String alias;

		while (!stringReader.IsAtEnd())
		{
			line = stringReader.GetNextLine();

			if (line.FindFirstOf(':') != -1)
				alias = line.Substring(0, line.FindFirstOf(':'));
			else
			{
				if (line[0] == 'b')
					AddButtonAlias(alias.GetCString(), (u32)line.Substring(1).ToInt());
				else if (line[0] == 'a')
					AddAxisAlias(alias.GetCString(), (sf::Joystick::Axis)line.Substring(1).ToInt());
			}
		}
	}
}