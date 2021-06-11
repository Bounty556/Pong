#pragma once

#include "EntryPoint.h"

#include <Core/Logger.h>
#include <Core/MessageBus.h>
#include <Core/Timer.h>
#include <Core/SceneManager.h>
#include <IO/InputManager.h>
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
		LOG_INFO("Starting engine");

		// Startup systems
		if (!PlatformInitialize())
		{
			LOG_FATAL("Failed to initialize platform layer.");
			return false;
		}
		if (!MemoryManager::Initialize(MEGABYTES(32)))
		{
			LOG_FATAL("Failed to initialize memory.");
			return false;
		}
		if (!MessageBus::Initialize())
		{
			LOG_FATAL("Failed to initialize MessageBus.");
			return false;
		}
		if (!InputManager::Initialize())
		{
			LOG_FATAL("Failed to initialize InputManager.");
			return false;
		}

		window = PARTITION(sf::RenderWindow, sf::VideoMode(windowWidth, windowHeight), windowName);
		window->setVerticalSyncEnabled(false);

		return true;
	}

	void SetScene(Scene* initialScene)
	{
		SceneManager::Initialize(initialScene);

		Timer gameTimer;
		PlatformTime accumulatedTime = 0.0f;
		PlatformTime accumulatedTime2 = 0.0f;
		u32 frames = 0;
		gameTimer.Start();
		while (SceneManager::HasScenes())
		{
			PlatformTime time = gameTimer.GetDeltaTime();
			accumulatedTime += time;
			while (accumulatedTime >= TARGET_FRAMERATE)
			{
				accumulatedTime -= TARGET_FRAMERATE;

				ProcessEvents(); // Input, window events, etc.

				SceneManager::ConsumeCommands();

				SceneManager::Update(TARGET_FRAMERATE);

				// Rendering
				window->setActive(true);
				window->clear();

				SceneManager::Draw(*window, sf::RenderStates::Default);

				window->display();

				MessageBus::PumpQueue();
			}
		}
	}

	void ShutdownEngine()
	{
		LOG_INFO("Shutting down engine");

		SceneManager::Shutdown();
		
		MemoryManager::FreeMemory(window);
		
		MessageBus::Shutdown();
		MemoryManager::Shutdown();
	}

	void ProcessEvents()
	{
		sf::Event e;
		while (window->pollEvent(e))
		{
			InputManager::ReceivedInput(e);
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