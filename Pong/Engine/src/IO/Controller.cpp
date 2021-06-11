#include "Controller.h"

namespace Soul
{
	Controller::Controller(const char* controlsFile) :
		m_ControlsMap(controlsFile)
	{
	}

	Controller::Controller(Controller&& other) :
		m_ControlsMap(std::move(other.m_ControlsMap))
	{
	}

	Controller::~Controller()
	{
	}

	Controller& Controller::operator=(Controller&& other)
	{
		m_ControlsMap = std::move(other.m_ControlsMap);

		return *this;
	}

	void Controller::UpdateControlsFile(const char* controlsFile)
	{
		m_ControlsMap = ControlsMap(controlsFile);
	}
}