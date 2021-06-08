#pragma once

#include <Defines.h>
#include <Core/Scene.h>
#include <Memory/UniquePointer.h>
#include <Structures/Stack.h>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Soul
{
	/*
	Manages the stack of scenes that are running in the engine at any given time.
	Every part of the engine from the application layer's point of view should
	be running inside of a scene, it's the only way to do anything inside the
	engine.

	The SceneManager must be initialized with a Scene to start, and a scene
	must be either active or in the Scene Command Queue at any given time in
	order for the engine to be running.
	*/
	class SceneManager
	{
	public:
		typedef UniquePointer<Scene> ScenePtr;

		enum Commands
		{
			Push,
			Pop,
			Clear,
			CommandCount
		};

		struct SceneCommand
		{
			Commands command;
			Scene* scene;
		};

	public:
		SceneManager() = delete;

		/*
		SceneManager lifetime management
		*/
		static void Initialize(ScenePtr initialScene);
		static void Shutdown();

		/*
		For keeping the scenes in the stack drawn and updated.
		*/
		static void Update(f32 dt);
		static void Draw(sf::RenderTarget& target, sf::RenderStates states);

		/*
		Adds a command to the Scene Command Queue
		*/
		static void PushCommand(SceneCommand command);

		/*
		Clears the command queue and executes the commands in the order they
		were added.
		*/
		static void ConsumeCommands();

		/*
		Returns whether there is a scene currently loaded, or if there is a scene that is ready
		to be loaded.
		*/
		static bool HasScenes();

	private:
		static bool m_Initialized;
		static Stack<ScenePtr>* m_SceneStack;
	};
}