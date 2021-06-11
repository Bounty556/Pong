#include "ControlsMap.h"

namespace Soul
{
	ControlsMap::ControlsMap(const char* fileName) :
		m_ControlMappings()
	{
		LoadControlsFromFile(fileName);
	}

	ControlsMap::ControlsMap(ControlsMap&& other) noexcept :
		m_ControlMappings(std::move(other.m_ControlMappings))
	{
	}

	ControlsMap& ControlsMap::operator=(ControlsMap&& other) noexcept
	{
		m_ControlMappings = std::move(other.m_ControlMappings);

		return *this;
	}

	ControlsMap::ControlMapping& ControlsMap::GetControlMapping(const char* control)
	{
		return *m_ControlMappings.GetValue(control);
	}

	void ControlsMap::LoadControlsFromFile(const char* fileName)
	{
		// TODO:
	}
}