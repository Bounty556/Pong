#pragma once

#include <Defines.h>
#include <Core/Scene.h>
#include <Memory/UniquePointer.h>
#include <Structures/Stack.h>
#include <Structures/Queue.h>

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
	class SOULAPI SceneManager
	{
	public:
		typedef UniquePointer<Scene> ScenePtr;

		enum Commands
		{
			Push,
			Pop,
			Clear
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
		static void Initialize(Scene* initialScene);
		static void Shutdown();

		/*
		For keeping the scenes in the stack drawn and updated.
		*/
		static void Update(f32 dt);
		static void Draw(sf::RenderStates states);

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

		/*
		Reinstantiates the scene with the provided data and constructor args.
		*/
		template <class T, class ...Args>
		static void ResetScene(T* scene, void* data, Args&& ...args);

	private:
		static void PushScene(Scene* scene);
		static void PopScene();
		static void ClearScenes();

	private:
		static bool m_Initialized;
		static Stack<Scene*>* m_SceneStack;
		static Queue<SceneCommand>* m_CommandQueue;
	};

	template <class T, class ...Args>
	void SceneManager::ResetScene(T* scene, void* data, Args&& ...args)
	{
		for (u32 i = 0; i < m_SceneStack->Count(); ++i)
		{
			if ((*m_SceneStack)[i] == scene)
			{
				MemoryManager::FreeMemory((*m_SceneStack)[i]);
				(*m_SceneStack)[i] = PARTITION(T, std::forward<Args>(args)...);
				(*m_SceneStack)[i]->ResetSceneData(data);
				break;
			}
		}
	}
}