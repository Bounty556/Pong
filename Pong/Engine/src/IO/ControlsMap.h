#pragma once

#include <Defines.h>
#include <Structures/Map.h>
#include <Structures/Vector.h>

#include <SFML/Window.hpp>

namespace Soul
{
	class ControlsMap
	{
	public:
		struct ControlMapping
		{
			sf::Keyboard::Key key;
			sf::Mouse::Button mButton;
			sf::Joystick::Axis axis;
			u32 jButton;
		};

	public:
		ControlsMap(const char* fileName);

		ControlsMap(const ControlsMap& other) = delete;
		ControlsMap(ControlsMap&& other) noexcept;

		ControlsMap& operator=(const ControlsMap& other) = delete;
		ControlsMap& operator=(ControlsMap&& other) noexcept;

		ControlMapping& GetControlMapping(const char* control);

		Vector<ControlMapping*> GetAllMappings();

	private:
		void LoadControlsFromFile(const char* fileName);

	private:
		Map<String, ControlMapping> m_ControlMappings;
	};
}