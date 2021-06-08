#pragma once

#include <Defines.h>

#include <Core/Scene.h>

namespace Soul
{
	bool SOULAPI InitializeEngine(u32 WindowWidth, u32 WindowHeight, const char* WindowName);
	void SOULAPI SetScene(Scene* initialScene);
	void SOULAPI ShutdownEngine();
	void ProcessEvents();
}