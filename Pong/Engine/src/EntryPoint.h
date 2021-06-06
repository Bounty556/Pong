#pragma once

#include <Defines.h>


namespace Soul
{
	bool SOULAPI InitializeEngine(i16 WindowWidth, i16 WindowHeight, const char* WindowName);
	void SOULAPI SetScene();
	void SOULAPI ShutdownEngine();
}