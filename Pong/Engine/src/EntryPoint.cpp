#pragma once

#include "EntryPoint.h"

namespace Soul
{
	Context InitializeEngine(i16 WindowWidth, i16 WindowHeight, const char* WindowName)
	{
		LOG_DEBUG("Starting engine");

		// Startup systems
		InitializeMemoryManager(Megabytes(512));

		Context newContext;
		return newContext;
	}

	// TODO: Add scene
	void SetScene()
	{
		LOG_DEBUG("Scene added");
	}

	void ShutdownEngine()
	{
		LOG_DEBUG("Shutting down engine");

		ShutdownMemoryManager();
	}
}