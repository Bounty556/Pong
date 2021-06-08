#pragma once

#include <Defines.h>

#include <Core/Scene.h>

namespace Soul
{
	bool SOULAPI InitializeEngine(u32 windowWidth, u32 windowHeight, const char* windowName);
	void SOULAPI SetScene(Scene* initialScene);
	void SOULAPI ShutdownEngine();
	void ProcessEvents();
}