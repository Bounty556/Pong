#pragma once

#include "EntryPoint.h"

#include <Core/Logger.h>
#include <Memory/MemoryManager.h>
#include <Platform/Platform.h>

namespace Soul
{
	bool InitializeEngine(i16 WindowWidth, i16 WindowHeight, const char* WindowName)
	{
		LOG_DEBUG("Starting engine");

		// Startup systems
		if (!PlatformInitialize())
		{
			LOG_FATAL("Failed to initialize platform layer.");
			return false;
		}
		if (!MemoryManager::Initialize(MEGABYTES(512)))
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

		MemoryManager::Shutdown();
	}
}