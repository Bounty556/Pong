#pragma once

#include "Engine.h"

#include <Core/Logger.h>
#include <Core/MessageBus.h>
#include <Core/SceneManager.h>
#include <IO/InputManager.h>
#include <Math/Random.h>
#include <Memory/MemoryManager.h>
#include <Physics/PhysicsSystem.h>
#include <Platform/Platform.h>
#include <Platform/Timer.h>
#include <Rendering/Renderer.h>
#include <Resources/ResourceManager.h>

#include <SFML/Graphics.hpp>

#define TARGET_FRAMERATE 6.94f // 144 FPS // TODO: Make configurable

namespace Soul
{
	EngineInfo engineInfo = {};
	// TODO: Replace with more sophisticated window?
	sf::RenderWindow* window;

	bool InitializeEngine(u32 windowWidth, u32 windowHeight, const char* windowName)
	{
		LOG_INFO("Starting engine");

		engineInfo.windowWidth = windowWidth;
		engineInfo.windowHeight = windowHeight;
		engineInfo.hasFocus = true;

		// Startup systems
		if (!PlatformInitialize())
		{
			LOG_FATAL("Failed to initialize platform layer.");
			return false;
		}
		if (!MemoryManager::Initialize(MEGABYTES(4))) // TODO: Make configurable
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
		if (!PhysicsSystem::Initialize(5000, 5000)) // TODO: Make configurable
		{
			LOG_FATAL("Failed to initialize PhysicsSystem.");
			return false;
		}
		if (!ResourceManager::Initialize())
		{
			LOG_FATAL("Failed to initialize ResourceManager.");
			return false;
		}

		window = NEW(sf::RenderWindow, sf::VideoMode(windowWidth, windowHeight), windowName, sf::Style::Close | sf::Style::Titlebar);

		if (!Renderer::Initialize(window))
		{
			LOG_FATAL("Failed to initial renderer.");
			return false;
		}

		// Seed the PRNG
		Math::SetSeed(PlatformGetTime());

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
				// Input
				InputManager::Update();
				ProcessEvents();

				// Updates
				SceneManager::ConsumeCommands();
				SceneManager::Update(TARGET_FRAMERATE);
				
				PhysicsSystem::Update(TARGET_FRAMERATE);
				SceneManager::LateUpdate(TARGET_FRAMERATE);

				// Rendering
				window->clear();
				SceneManager::Draw(sf::RenderStates::Default);
				window->display();

				MessageBus::PumpQueue(TARGET_FRAMERATE);

				accumulatedTime -= TARGET_FRAMERATE;
				if (accumulatedTime > 1000.0f)
					accumulatedTime = 0.0f;
			}
		}
	}

	void ShutdownEngine()
	{
		LOG_INFO("Shutting down engine");

		SceneManager::Shutdown();
		Renderer::Shutdown();

		DELETE(window);
		
		ResourceManager::Shutdown();
		PhysicsSystem::Shutdown();
		InputManager::Shutdown();
		MessageBus::Shutdown();
		ShutdownLogger();
		ASSERT(MemoryManager::GetTotalPartitionedMemory() == 0);
		MemoryManager::Shutdown();
	}

	const EngineInfo& GetEngineInfo()
	{
		return engineInfo;
	}

	void ProcessEvents()
	{
		sf::Event e;
		while (window->pollEvent(e))
		{
			InputManager::ProcessInput(e);
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