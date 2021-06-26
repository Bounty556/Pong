#pragma once

#include <Defines.h>

#include <Core/Scene.h>

// TODO: Add functionality for changing engine settings, such as window size, window mode, graphics settings, etc.

namespace Soul
{
	struct SOULAPI EngineInfo
	{
		u32 windowHeight;
		u32 windowWidth;
		bool hasFocus;
		// TODO: Add other info, such as current runtime, system info, etc.
	};

	bool SOULAPI InitializeEngine(u32 windowWidth, u32 windowHeight, const char* windowName);
	void SOULAPI SetScene(Scene* initialScene);
	void SOULAPI ShutdownEngine();
	const EngineInfo& GetEngineInfo();
	void ProcessEvents();
}