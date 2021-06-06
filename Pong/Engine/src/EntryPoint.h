#pragma once

#include <Defines.h>

#include <Core/Logger.h>
#include <Memory/MemoryManager.h>

namespace Soul
{

	/*
	Various systems that can be passed to the application
	*/
	struct SOULAPI Context
	{

	};

	Context SOULAPI InitializeEngine(i16 WindowWidth, i16 WindowHeight, const char* WindowName);
	void SOULAPI SetScene();
	void SOULAPI ShutdownEngine();
}