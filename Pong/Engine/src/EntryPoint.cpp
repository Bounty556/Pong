#pragma once

#include "EntryPoint.h"

#include <Core/Logger.h>
#include <Core/Timer.h>
#include <Core/SceneManager.h>
#include <Memory/MemoryManager.h>
#include <Platform/Platform.h>

#include <SFML/Graphics.hpp>

#define TARGET_FRAMERATE 6.94f // 144 FPS

namespace Soul
{
	// TODO: Replace with more sophisticated window
	sf::RenderWindow* window;

	bool InitializeEngine(u32 windowWidth, u32 windowHeight, const char* windowName)
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

		window = PARTITION(sf::RenderWindow, sf::VideoMode(windowWidth, windowHeight), windowName);
		
		return true;
	}

	void SetScene(Scene* initialScene)
	{
		SceneManager::Initialize(initialScene);

		Timer gameTimer;
		PlatformTime accumulatedTime = 0.0f;
		gameTimer.Start();
		while (SceneManager::HasScenes())
		{
			accumulatedTime += gameTimer.GetDeltaTime();
			while (accumulatedTime >= TARGET_FRAMERATE)
			{
				accumulatedTime -= TARGET_FRAMERATE;

				// Ensure we don't try to process a ton of frames at once
				if (accumulatedTime > 1.0f)
					accumulatedTime = 0.0f;

				ProcessEvents(); // Input, window events, etc.

				SceneManager::ConsumeCommands();

				SceneManager::Update(TARGET_FRAMERATE);

				// Rendering
				window->setActive(true);
				window->clear();

				SceneManager::Draw(*window, sf::RenderStates::Default);

				window->display();
			}
		}
	}

	void ShutdownEngine()
	{
		LOG_DEBUG("Shutting down engine");

		SceneManager::Shutdown();
		
		MemoryManager::FreeMemory(window);

		MemoryManager::Shutdown();
	}

	void ProcessEvents()
	{
		sf::Event e;
		while (window->pollEvent(e))
		{
			switch (e.type)
			{
				case sf::Event::Closed:
				{
					SceneManager::PushCommand({ SceneManager::Clear, nullptr });
				} break;

				case sf::Event::KeyPressed:
				{
					if (e.key.code == sf::Keyboard::Escape)
						SceneManager::PushCommand({ SceneManager::Clear, nullptr });
				} break;
			}
		}
	}
}