#pragma once

#include <Defines.h>
#include <IO/InputManager.h>
#include <Memory/UniquePointer.h>

#include <SFML/Window/Joystick.hpp>

namespace Soul
{
	class SOULAPI Controller
	{
	public:
		Controller(u8 joystickId, u8 playerId, const char* aliasFile = "res/Controls/defaultControls.controls");

		Controller(const Controller& other) = delete;
		Controller(Controller&& other) noexcept;

		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) noexcept;

		bool IsButtonUp(u32 button) const;
		bool IsButtonPressed(u32 button) const;
		bool IsButtonDown(u32 button) const;
		bool IsButtonReleased(u32 button) const;

		f32 GetAxisPos(sf::Joystick::Axis axis) const;

		void AddButtonAlias(const char* alias, u32 button);
		void RemoveButtonAlias(const char* alias);
		void AddAxisAlias(const char* alias, sf::Joystick::Axis axis);
		void RemoveAxisAlias(const char* alias);

		bool IsAliasUp(const char* alias);
		bool IsAliasPressed(const char* alias);
		bool IsAliasDown(const char* alias);
		bool IsAliasReleased(const char* alias);
		f32 GetAliasPosition(const char* alias);

		u8 GetJoystickId() const;
		u8 GetPlayerId() const;

		void Update();

		void LoadAliases(const char* controlsFile);

	private:
		u8 m_JoystickId;
		u8 m_PlayerId;
		UniquePointer<InputManager::KeyState> m_ButtonStates;
		UniquePointer<Map<String, u32>> m_ButtonAliases;
		UniquePointer<Map<String, sf::Joystick::Axis>> m_AxisAliases;
	};
}