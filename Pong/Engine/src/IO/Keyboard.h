#pragma once

#include <Defines.h>
#include <IO/Controller.h>
#include <Structures/Map.h>

namespace Soul
{
	class Keyboard : public Controller
	{
	public:
		Keyboard(const char* controlsFile);

		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&& other) noexcept;

		~Keyboard();

		Keyboard& operator=(const Keyboard&) = delete;
		Keyboard& operator=(Keyboard&& other) noexcept;

		virtual void ButtonEvent(sf::Event event) override;
		virtual ControlState GetControlState(const char* control) override;

	private:
		ControlState* m_MouseStates;
		Map<u32, ControlState> m_KeyboardStates;
	};
}