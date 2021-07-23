#include "PhysicsSystem.h"

#include <Memory/MemoryManager.h>

namespace Soul
{
	QuadTree* PhysicsSystem::m_QuadTree;
	bool PhysicsSystem::m_IsInitialized = false;
	bool PhysicsSystem::m_IsActive = true;

	bool PhysicsSystem::Initialize(f32 width, f32 height)
	{
		m_IsInitialized = true;
		m_QuadTree = NEW(QuadTree, 0.0f, 0.0f, width, height, 8, nullptr);
		return true;
	}

	void PhysicsSystem::Shutdown()
	{
		ASSERT(m_IsInitialized);
		DELETE(m_QuadTree);
	}

	void PhysicsSystem::Update(f32 dt)
	{
		ASSERT(m_IsInitialized);
		m_QuadTree->Move();
	}

	void PhysicsSystem::RegisterCollider(IColliderNode* node)
	{
		ASSERT(m_IsInitialized);
		if (m_IsActive)
			m_QuadTree->Insert(node);
	}

	void PhysicsSystem::UnregisterCollider(IColliderNode* node)
	{
		ASSERT(m_IsInitialized);
		if (m_IsActive)
			m_QuadTree->Remove(node);
	}

	Vector<IColliderNode*> PhysicsSystem::GetPotentialCollisions(sf::Vector2f position, sf::Vector2f area)
	{
		ASSERT(m_IsInitialized);
		return m_QuadTree->GetNodes(position, area);
	}

	void PhysicsSystem::TogglePhysics()
	{
		m_IsActive = !m_IsActive;
	}
}