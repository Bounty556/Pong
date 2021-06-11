#include "Keyboard.h"

namespace Soul
{
	Keyboard::Keyboard(const char* controlsFile) :
		Controller(controlsFile)
	{
	}

	Keyboard::Keyboard(Keyboard&& other) noexcept :
		Controller(std::move(other)),
		m_MouseStates(other.m_MouseStates),
		m_KeyboardStates(std::move(other.m_KeyboardStates))
	{
		other.m_MouseStates = nullptr;
	}

	Keyboard::~Keyboard()
	{
		if (!m_MouseStates)
			MemoryManager::FreeMemory(m_MouseStates);
	}

	Keyboard& Keyboard::operator=(Keyboard&& other) noexcept
	{
		Controller::operator=(std::move(other));
		m_MouseStates = other.m_MouseStates;
		m_KeyboardStates = std::move(other.m_KeyboardStates);
		other.m_MouseStates = nullptr;

		return *this;
	}

	void Keyboard::ButtonEvent(sf::Event event)
	{
		// TODO: Update m_MouseStates and m_KeyboardStates
	}

	Controller::ControlState Keyboard::GetControlState(const char* control)
	{
		// TODO: Get state
		Controller::ControlState state{};

		return state;
	}
}