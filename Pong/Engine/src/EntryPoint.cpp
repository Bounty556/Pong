#pragma once

#include "EntryPoint.h"

#include <Core/Logger.h>
#include <Core/MessageBus.h>
#include <Core/SceneManager.h>
#include <IO/InputManager.h>
#include <Memory/MemoryManager.h>
#include <Platform/Platform.h>
#include <Platform/Timer.h>
#include <Rendering/Renderer.h>

#include <SFML/Graphics.hpp>

#define TARGET_FRAMERATE 6.94f // 144 FPS

namespace Soul
{
	// TODO: Replace with more sophisticated window?
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
		if (!MemoryManager::Initialize(MEGABYTES(4)))
		{
			LOG_FATAL("Failed to initialize memory.");
			return false;
		}
		if (!InitializeLogger("debugLogs.txt"))
		{
			LOG_FATAL("Failed to initialize logger.");
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

		window = PARTITION(sf::RenderWindow, sf::VideoMode(windowWidth, windowHeight), windowName, sf::Style::Close | sf::Style::Titlebar);
		window->setVerticalSyncEnabled(false);
		window->setFramerateLimit(0);

		if (!Renderer::Initialize(window))
		{
			LOG_FATAL("Failed to initial renderer.");
			return false;
		}

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
				if (accumulatedTime > 1000.0f)
					accumulatedTime = 0.0f;

				// Input
				ProcessEvents();
				InputManager::UpdateControllers();

				// Updates
				SceneManager::ConsumeCommands();
				SceneManager::Update(TARGET_FRAMERATE);

				// Rendering
				window->clear();
				SceneManager::Draw(sf::RenderStates::Default);
				window->display();

				MessageBus::PumpQueue();

				accumulatedTime -= TARGET_FRAMERATE;
			}
		}
	}

	void ShutdownEngine()
	{
		LOG_INFO("Shutting down engine");

		SceneManager::Shutdown();
		Renderer::Shutdown();

		MemoryManager::FreeMemory(window);
		
		InputManager::Shutdown();
		MessageBus::Shutdown();
		ShutdownLogger();
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
			}
		}
	}
}