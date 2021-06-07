#pragma once

#include "EntryPoint.h"

#include <Core/Logger.h>
#include <Memory/MemoryManager.h>

namespace Soul
{
	bool InitializeEngine(i16 WindowWidth, i16 WindowHeight, const char* WindowName)
	{
		LOG_DEBUG("Starting engine");

		// Startup systems
		if (!InitializeMemoryManager(MEGABYTES(512)))
		{
			LOG_FATAL("Failed to initialize memory.");
			return false;
		}

		return true;
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