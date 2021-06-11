#include "ControlsMap.h"

#include <IO/StringReader.h>
#include <IO/TextFileReader.h>

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

	Vector<ControlsMap::ControlMapping*> ControlsMap::GetAllMappings()
	{
		return m_ControlMappings.GetValues();
	}

	void ControlsMap::LoadControlsFromFile(const char* fileName)
	{
		TextFileReader controlsFile(fileName);
		StringReader reader(controlsFile.GetString());

		// TODO: Make more robust
		while (!reader.IsAtEnd())
		{
			// First line is the name of the control
			String control = reader.GetNextLine();

			// Lines should be in order of keyboard, mouse, axis, button
			i32 keyboard = reader.GetNextLine().ToInt();
			i32 mouse = reader.GetNextLine().ToInt();
			i32 axis = reader.GetNextLine().ToInt();
			i32 button = reader.GetNextLine().ToInt();

			// Create mapping
			ControlMapping mapping{};

			mapping.key = keyboard;
			mapping.mButton = mouse;
			mapping.axis = axis;
			mapping.jButton = button;

			m_ControlMappings.AddPair(control.GetCString(), mapping);
		}
	}
}