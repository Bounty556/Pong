#include "SceneManager.h"

// TODO: Write Queue class and then finish implementing

namespace Soul
{
	bool SceneManager::m_Initialized = false;
	Stack<SceneManager::ScenePtr>* SceneManager::m_SceneStack;

	void SceneManager::Initialize(ScenePtr  initialScene)
	{
		ASSERT(!m_Initialized);

		// TODO: Initialization

		m_Initialized = true;
	}

	void SceneManager::Shutdown()
	{
		ASSERT(m_Initialized);

		// TODO: Shutdown
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

	void SceneManager::Draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		ASSERT(m_Initialized);

		// Find the first scene that disallows draw passing, if any
		auto i = m_SceneStack->Begin();
		for (; i != m_SceneStack->End(); i++)
		{
			if ((*i)->DrawPass())
				break;
		}

		// From there, draw the scenes in reverse so the early ones get drawn
		// over
		i.Flip();
		for (; i != m_SceneStack->REnd(); i++)
		{
			(*i)->Draw(target, states);
		}
	}

	void SceneManager::PushCommand(SceneCommand command)
	{
		ASSERT(m_Initialized);

		// TODO: Push command to queue
	}

	void SceneManager::ConsumeCommands()
	{
		ASSERT(m_Initialized);

		// TODO: Consume all commands in queue
	}

	bool SceneManager::HasScenes()
	{
		ASSERT(m_Initialized);

		return !m_SceneStack->Empty();
	}
}