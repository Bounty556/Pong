#include "SceneManager.h"

namespace Soul
{
	bool SceneManager::m_Initialized = false;
	Stack<Scene*>* SceneManager::m_SceneStack;
	Queue<SceneManager::SceneCommand>* SceneManager::m_CommandQueue;

	void SceneManager::Initialize(Scene* initialScene)
	{
		ASSERT(!m_Initialized);

		m_SceneStack = NEW(Stack<Scene*>);
		m_CommandQueue = NEW(Queue<SceneManager::SceneCommand>);

		m_Initialized = true;

		PushScene(initialScene);
	}

	void SceneManager::Shutdown()
	{
		ASSERT(m_Initialized);

		for (u32 i = 0 ; i < m_SceneStack->Count(); ++i)
			DELETE((*m_SceneStack)[i]);

		DELETE(m_SceneStack);
		DELETE(m_CommandQueue);
	}

	void SceneManager::Update(f32 dt)
	{
		ASSERT(m_Initialized);

		for (i32 i = (i32)m_SceneStack->Count() - 1; i >= 0; --i)
		{
			(*m_SceneStack)[i]->Update(dt);

			if (!(*m_SceneStack)[i]->UpdatePass())
				break;
		}
	}

	void SceneManager::Draw(sf::RenderStates states)
	{
		ASSERT(m_Initialized);

		// Find the first scene that disallows draw passing, if any
		i32 i = m_SceneStack->Count() - 1;
		for (; i > 0; --i)
			if (!(*m_SceneStack)[i]->DrawPass())
				break;

		if (i < 0)
			i = 0;

		// From here, draw the scenes in reverse so the early ones get drawn
		// over
		for (; i < (i32)m_SceneStack->Count(); ++i)
			(*m_SceneStack)[i]->Draw(states);
	}

	void SceneManager::PushCommand(SceneCommand command)
	{
		ASSERT(m_Initialized);

		m_CommandQueue->Que(command);
	}

	void SceneManager::ConsumeCommands()
	{
		ASSERT(m_Initialized);

		while (!m_CommandQueue->IsEmpty())
		{
			SceneCommand command = m_CommandQueue->Deque();

			switch (command.command)
			{
				case Commands::Push:
				{
					PushScene(command.scene);
				} break;

				case Commands::Pop:
				{
					PopScene();
				} break;

				case Commands::Clear:
				{
					ClearScenes();
				} break;
			}
		}
	}

	bool SceneManager::HasScenes()
	{
		// TODO: See if we have commands queued to push scenes?
		ASSERT(m_Initialized);

		return !m_SceneStack->IsEmpty();
	}

	void SceneManager::PushScene(Scene* scene)
	{
		m_SceneStack->Push(scene);
	}

	void SceneManager::PopScene()
	{
		m_SceneStack->Pop();
	}

	void SceneManager::ClearScenes()
	{
		while (!m_SceneStack->IsEmpty())
		{
			Scene* s = m_SceneStack->Pop();
			MemoryManager::FreeMemory(s);
		}
	}
}