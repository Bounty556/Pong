#include "SceneManager.h"

namespace Soul
{
	bool SceneManager::m_Initialized = false;
	Stack<SceneManager::ScenePtr>* SceneManager::m_SceneStack;
	Queue<SceneManager::SceneCommand>* SceneManager::m_CommandQueue;

	void SceneManager::Initialize(Scene* initialScene)
	{
		ASSERT(!m_Initialized);

		m_SceneStack = PARTITION(Stack<SceneManager::ScenePtr>);
		m_CommandQueue = PARTITION(Queue<SceneManager::SceneCommand>);

		m_Initialized = true;

		PushScene(initialScene);
	}

	void SceneManager::Shutdown()
	{
		ASSERT(m_Initialized);

		MemoryManager::FreeMemory(m_SceneStack);
		MemoryManager::FreeMemory(m_CommandQueue);
	}


	void SceneManager::Update(f32 dt)
	{
		ASSERT(m_Initialized);

		for (auto i = m_SceneStack->Begin(); i != m_SceneStack->End(); i++)
		{
			(*i)->Update(dt);

			if ((*i)->UpdatePass())
				break;
		}
	}

	void SceneManager::Draw(sf::RenderStates states)
	{
		ASSERT(m_Initialized);

		// Find the first scene that disallows draw passing, if any
		auto i = m_SceneStack->RBegin();
		bool blocked = false;
		for (; i != m_SceneStack->REnd(); i++)
		{
			if ((*i)->DrawPass())
			{
				blocked = true;
				break;
			}
		}

		if (blocked)
			i.Flip();
		else
			i = m_SceneStack->Begin();

		// From there, draw the scenes in reverse so the early ones get drawn
		// over
		for (; i != m_SceneStack->End(); i++)
		{
			(*i)->Draw(states);
		}
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
		ASSERT(m_Initialized);

		return !m_SceneStack->IsEmpty();
	}

	void SceneManager::PushScene(Scene* scene)
	{
		m_SceneStack->Push(ScenePtr(scene));
	}

	void SceneManager::PopScene()
	{
		m_SceneStack->Pop();
	}

	void SceneManager::ClearScenes()
	{
		while (!m_SceneStack->IsEmpty())
		{
			m_SceneStack->Pop();
		}
	}
}